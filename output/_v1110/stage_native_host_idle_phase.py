"""Run observed process-timer draws before the original character idle callbacks."""
import argparse
import re

from stage_native_mega_clover_rng import SIM, replace_one


def lower_idle_phase(native):
    anchor = "Gd__gd_core__CoreCombat::fn_physicsTick("
    matches = [(path, body) for path in (native / "gen/shards").glob("*.cpp")
               if anchor in (body := path.read_text("utf8"))]
    assert len(matches) == 1
    shard, source = matches[0]
    start = source.index(anchor)
    end = source.index("\n}", start)
    method = source[start:end]
    for pattern in (r"^    \(void\).*SYM_GEN_flushIdleFrameCalls_\d+, nullptr, 0\);\n",
                    r"^            \(void\).*SYM_GEN_runOpeningSceneDelays_\d+, nullptr, 0\);\n"):
        matches = list(re.finditer(pattern, method, flags=re.MULTILINE))
        assert len(matches) == 1, pattern
        match = matches[0]
        matched = match.group()
        indent = matched[:len(matched) - len(matched.lstrip())]
        dispatch = (indent + "if (_argc > 1) replay_host_before_idle(\n" +
                    indent + "    _args[1].as_int(), this->f_ctx.obj, this->f_combat_time.as_float());\n")
        replacement = dispatch + matched if "runOpeningSceneDelays" in matched else matched + dispatch
        method = method[:match.start()] + replacement + method[match.end():]
    updated = source[:start] + method + source[end:]
    includes = list(re.finditer(r"^#include .+\n", updated, flags=re.MULTILINE))
    assert includes
    at = includes[-1].end()
    declaration = "\nvoid replay_host_before_idle(int64_t control, gd::GdObj* context, double combat_time);\n"
    shard.write_text(updated[:at] + declaration + updated[at:], encoding="utf8", newline="\n")


def install_host_phases(native):
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = replace_one(source, "struct ReplayHostDraw {\n    int32_t tick;\n",
                         "struct ReplayHostDraw {\n    int32_t tick;\n    int32_t phase;\n")
    anchor = "static void run_one_internal("
    source = replace_one(source, anchor, """static void apply_host_draws(ReplayHostRng& host, Gd__gd_core__CoreContext& context,
                             double combat_time, int32_t phase) {
    if (host.invalid || host.next >= host.count || gd::gd_truth(context.f_fight_ended)) return;
    const auto tick = std::llround(combat_time * 60.0);
    while (host.next < host.count) {
        const auto& draw = host.draws[host.next];
        if (draw.tick > tick || (draw.tick == tick && draw.phase > phase)) return;
        auto* util = static_cast<Gd__gd_core__CoreRng*>(context.f_rng.obj)->f_rng.rng;
        if (draw.tick != tick || draw.phase != phase || util->get_state() != draw.before) {
            host.invalid = true;
            return;
        }
        util->randf_range(10.0, 30.0);
        if (util->get_state() != draw.after) {
            host.invalid = true;
            return;
        }
        ++host.next;
    }
}

""" + anchor)
    start = source.index("        combat_obj->fn_physicsTick(&dt, 1);\n")
    end = source.index("        ticks += 1;\n", start)
    assert "host->draws[host->next]" in source[start:end]
    source = source[:start] + """        combat_obj->fn_physicsTick(tick_args, host ? 2 : 1);
        if (host && gd::gd_truth(combat_obj->f_activated)) {
            apply_host_draws(*host, *ctx_obj, combat_obj->f_combat_time.as_float(), 1);
        }
""" + source[end:]
    anchor = "    int32_t ticks = 0;\n    bool ev_capped = false;\n"
    source = replace_one(source, anchor, """    const gd::GdVal tick_args[] = {
        dt, gd::GdVal::from_int(reinterpret_cast<intptr_t>(host))
    };
""" + anchor)
    anchor = 'extern "C" {\n\nvoid gd_sim_run_one('
    source = replace_one(source, anchor, """void replay_host_before_idle(int64_t control, gd::GdObj* context, double combat_time) {
    auto& host = *reinterpret_cast<ReplayHostRng*>(static_cast<intptr_t>(control));
    auto& ctx = *static_cast<Gd__gd_core__CoreContext*>(context);
    apply_host_draws(host, ctx, combat_time, 0);
}

""" + anchor)
    source = replace_one(source, "int32_t gd_sim_run_one_replay_host_rng(",
                         "int32_t gd_sim_run_one_replay_host_phases(")
    anchor = "        if (draws[index].tick < 0 || draws[index].tick < previous_tick) return -1;\n"
    source = replace_one(source, anchor, """        if (draws[index].tick < 0 || draws[index].tick < previous_tick ||
            draws[index].phase < 0 || draws[index].phase > 1) return -1;
""")

    binding = native / "sim.py"
    py = binding.read_text("utf8").replace("gd_sim_run_one_replay_host_rng", "gd_sim_run_one_replay_host_phases")
    anchor = '    _fields_ = [("tick", ctypes.c_int32), ("before", ctypes.c_uint64), ("after", ctypes.c_uint64)]'
    py = replace_one(py, anchor, '''    _fields_ = [("tick", ctypes.c_int32), ("phase", ctypes.c_int32),
                ("before", ctypes.c_uint64), ("after", ctypes.c_uint64)]''')
    anchor = "                rows = [ReplayHostDraw(int(tick), int(before), int(after)) for tick, before, after in host_draws]"
    py = replace_one(py, anchor, """                rows = [ReplayHostDraw(int(tick), int(phase), int(before), int(after))
                        for tick, phase, before, after in host_draws]""")

    verifier = SIM / "tools/_cpp_verify_events.py"
    check = verifier.read_text("utf8")
    anchor = '    observed_host = [[round(float(row["combat_time"]) * 60), row["before"], row["after"]]'
    check = replace_one(check, anchor, '''    observed_host = [[round(float(row["combat_time"]) * 60),
                      {"process_timer": 0, "focus_out": 1}[row["kind"]], row["before"], row["after"]]''')
    wrapper.write_text(source, encoding="utf8", newline="\n")
    binding.write_text(py, encoding="utf8", newline="\n")
    verifier.write_text(check, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--generated-only", action="store_true")
    args = parser.parse_args()
    native = SIM / "native_sim_cpp/native_sim"
    if not args.generated_only:
        install_host_phases(native)
    lower_idle_phase(native)

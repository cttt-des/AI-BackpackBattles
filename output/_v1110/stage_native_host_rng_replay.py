"""Replay observed host draws between native battle frames."""
from stage_native_mega_clover_rng import SIM, replace_one


def install_host_replay_checks():
    binding = SIM / "native_sim_cpp/native_sim/sim.py"
    py = binding.read_text("utf8")
    anchor = "class ReplayHostDraw(ctypes.Structure):"
    py = replace_one(py, anchor, """class HostRngReplayMismatch(RuntimeError):
    def __init__(self, draw_index, result):
        super().__init__(f"RNG state disagrees at recorded host draw {draw_index}")
        self.draw_index = draw_index
        self.result = result


""" + anchor)
    py = replace_one(py, '                    raise RuntimeError(f"RNG state disagrees at recorded host draw {-status - 1}")',
                     "                    raise HostRngReplayMismatch(-status - 1, res)")

    verifier = SIM / "tools/_cpp_verify_events.py"
    source = verifier.read_text("utf8")
    source = replace_one(source, "from native_sim.sim import NativeSimulator ",
                         "from native_sim.sim import HostRngReplayMismatch, NativeSimulator ")
    source = replace_one(source, '    boundaries = json.loads((original / "boundaries.json").read_bytes())\n',
                         '''    boundary_bytes = (original / "boundaries.json").read_bytes()
    boundaries = json.loads(boundary_bytes)
    observed_host = [[round(float(row["combat_time"]) * 60), row["before"], row["after"]]
                     for row in boundaries.get("host_rng_draws", [])]
''')
    anchor = '            or controls["replay_initial"] != fx.get("replay_initial")\n'
    source = replace_one(source, anchor, anchor +
                         '            or (fx.get("replay_initial") or {}).get("host_rng_draws", []) != observed_host\n')
    anchor = "    result = run_cpp_fixture(sim, fx, player_path, opponent_path, order, below_master, rng_state)\n"
    source = replace_one(source, anchor, """    try:
        result = run_cpp_fixture(sim, fx, player_path, opponent_path, order, below_master, rng_state)
    except HostRngReplayMismatch as error:
        result = error.result
        rec["host_draw_mismatch"] = error.draw_index
        rec["notes"].append(str(error))
""")
    anchor = '    rec["original_events_sha256"] = hashlib.sha256(event_bytes).hexdigest()\n'
    source = replace_one(source, anchor, anchor +
                         '    rec["original_boundaries_sha256"] = hashlib.sha256(boundary_bytes).hexdigest()\n')
    anchor = '    if rec["missing_fields"]:\n        rec["category"] = "missing_event_metadata"\n'
    source = replace_one(source, anchor, '''    if "host_draw_mismatch" in rec:
        rec["category"] = "replay_control_mismatch"
    elif rec["missing_fields"]:
        rec["category"] = "missing_event_metadata"
''')
    binding.write_text(py, encoding="utf8", newline="\n")
    verifier.write_text(source, encoding="utf8", newline="\n")


def main():
    native = SIM / "native_sim_cpp/native_sim"
    wrapper = native / "engine_wrapper.cpp"
    cpp = wrapper.read_text("utf8")
    anchor = "static void run_one_internal("
    cpp = replace_one(cpp, anchor, """struct ReplayHostDraw {
    int32_t tick;
    uint64_t before;
    uint64_t after;
};
static_assert(sizeof(ReplayHostDraw) == 24);

struct ReplayHostRng {
    const ReplayHostDraw* draws;
    int32_t count;
    int32_t next = 0;
    bool invalid = false;
};

""" + anchor)
    cpp = replace_one(cpp, "    double util_time = 0.0\n) {",
                      "    double util_time = 0.0,\n    ReplayHostRng* host = nullptr\n) {")
    anchor = "        combat_obj->fn_physicsTick(&dt, 1);\n"
    cpp = replace_one(cpp, anchor, anchor + """        if (host && !host->invalid && host->next < host->count &&
            gd::gd_truth(combat_obj->f_activated) && !gd::gd_truth(combat_obj->f_fight_ended)) {
            const auto tick = std::llround(combat_obj->f_combat_time.as_float() * 60.0);
            while (host->next < host->count && host->draws[host->next].tick <= tick) {
                const auto& draw = host->draws[host->next];
                auto* util = static_cast<Gd__gd_core__CoreRng*>(ctx_obj->f_rng.obj)->f_rng.rng;
                if (draw.tick != tick || util->get_state() != draw.before) {
                    host->invalid = true;
                    break;
                }
                util->randf_range(10.0, 30.0);
                if (util->get_state() != draw.after) {
                    host->invalid = true;
                    break;
                }
                ++host->next;
            }
        }
""")
    anchor = "void gd_sim_set_dbg_events(int32_t on) {"
    cpp = replace_one(cpp, anchor, """int32_t gd_sim_run_one_replay_host_rng(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine,
    int32_t scene_delays, double util_time, const ReplayHostDraw* draws, int32_t count
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine)) ||
        !std::isfinite(util_time) || util_time < 0.0 || !draws || count <= 0) {
        return -1;
    }
    int32_t previous_tick = -1;
    for (int32_t index = 0; index < count; ++index) {
        if (draws[index].tick < 0 || draws[index].tick < previous_tick) return -1;
        previous_tick = draws[index].tick;
    }
    gd_sim_init();
    ReplayHostRng host{draws, count};
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine,
                     scene_delays != 0, util_time, &host);
    return host.invalid || host.next != count ? -host.next - 2 : 0;
}

""" + anchor)

    binding = native / "sim.py"
    py = binding.read_text("utf8")
    anchor = "class BattleOptions(ctypes.Structure):"
    py = replace_one(py, anchor, """class ReplayHostDraw(ctypes.Structure):
    _fields_ = [("tick", ctypes.c_int32), ("before", ctypes.c_uint64), ("after", ctypes.c_uint64)]


""" + anchor)
    anchor = "            lib.gd_sim_run_one_replay_native_clock.restype = None\n"
    py = replace_one(py, anchor, anchor + """        if hasattr(lib, "gd_sim_run_one_replay_host_rng"):
            lib.gd_sim_run_one_replay_host_rng.argtypes = lib.gd_sim_run_one_replay_native_clock.argtypes + [
                ctypes.POINTER(ReplayHostDraw), ctypes.c_int32]
            lib.gd_sim_run_one_replay_host_rng.restype = ctypes.c_int32
""")
    anchor = '            util_time = initial.get("util_time")\n            if util_time is not None:'
    py = replace_one(py, anchor, """            util_time = initial.get("util_time")
            host_draws = initial.get("host_rng_draws")
            if host_draws:
                if not hasattr(self.lib, "gd_sim_run_one_replay_host_rng"):
                    raise RuntimeError("This DLL does not support observed host draws")
                if util_time is None:
                    raise ValueError("Observed host draws require the original process clock")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                rows = [ReplayHostDraw(int(tick), int(before), int(after)) for tick, before, after in host_draws]
                packed_draws = (ReplayHostDraw * len(rows))(*rows)
                status = self.lib.gd_sim_run_one_replay_host_rng(
                    *arguments, ctypes.byref(replay), buff_arg, engine_arg, int(native_scene_delays),
                    float(util_time), packed_draws, len(rows))
                if status == -1:
                    raise ValueError("Invalid host draw schedule")
                if status:
                    raise RuntimeError(f"RNG state disagrees at recorded host draw {-status - 1}")
            elif util_time is not None:""")

    wrapper.write_text(cpp, encoding="utf8", newline="\n")
    binding.write_text(py, encoding="utf8", newline="\n")
    install_host_replay_checks()


if __name__ == "__main__":
    main()

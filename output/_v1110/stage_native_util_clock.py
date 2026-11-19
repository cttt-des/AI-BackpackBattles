"""Replay the original Util clock for the combat trigger-count check."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        anchor = "func setReplayInitial(activation_state, idle_left: Array, flickers = null, buff_state = null, engine_rng = null, scene_delays: bool = false) -> void:\n"
        source = replace_one(source, anchor, "var replay_util_time := 0.0\n\n" + anchor.replace(
            "scene_delays: bool = false)", "scene_delays: bool = false, util_time: float = 0.0)"))
        anchor = "\treplay_native_scene_delays = scene_delays\n"
        changes[context] = replace_one(source, anchor, anchor + "\treplay_util_time = util_time\n")

        item = root / "gd_core/CoreItem.gd"
        source = item.read_text("utf8")
        start = source.index("func checkTriggerCount(limit: int) -> bool:")
        finish = source.index("\n\nfunc trigger():", start)
        changes[item] = source[:start] + """func checkTriggerCount(limit: int) -> bool:
	# The original compares the process physics clock with the trigger count.
	var util_time: float = ctx.replay_util_time + ctx.time
	if util_time > triggersThisFrame:
		triggersThisFrame = 1
		lastTriggerTime = util_time
	else:
		triggersThisFrame += 1
		if triggersThisFrame > limit:
			return false
	return true
""" + source[finish:]

    native = SIM / "native_sim_cpp/native_sim"
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = replace_one(source, "    bool scene_delays = false\n", "    bool scene_delays = false,\n    double util_time = 0.0\n")
    source = replace_one(source, "        gd::GdVal initial[6] = {", "        gd::GdVal initial[7] = {")
    source = replace_one(source, "gd::GdVal::from_bool(scene_delays)\n", "gd::GdVal::from_bool(scene_delays),\n            gd::GdVal::from_float(util_time)\n")
    source = replace_one(source, "fn_setReplayInitial(initial, 6)", "fn_setReplayInitial(initial, 7)")
    anchor = "void gd_sim_set_dbg_events(int32_t on) {"
    changes[wrapper] = replace_one(source, anchor, """void gd_sim_run_one_replay_native_clock(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine,
    int32_t scene_delays, double util_time
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine)) ||
        !std::isfinite(util_time) || util_time < 0.0) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine,
                     scene_delays != 0, util_time);
}

""" + anchor)

    binding = native / "sim.py"
    source = binding.read_text("utf8")
    anchor = "            lib.gd_sim_run_one_replay_scene_delays.restype = None\n"
    source = replace_one(source, anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay_native_clock"):
            lib.gd_sim_run_one_replay_native_clock.argtypes = lib.gd_sim_run_one_replay_engine_rng.argtypes + [ctypes.c_int32, ctypes.c_double]
            lib.gd_sim_run_one_replay_native_clock.restype = None
''')
    anchor = "            if native_scene_delays:\n                if not hasattr"
    changes[binding] = replace_one(source, anchor, '''            util_time = initial.get("util_time")
            if util_time is not None:
                if not hasattr(self.lib, "gd_sim_run_one_replay_native_clock"):
                    raise RuntimeError("This DLL does not support the original Util clock")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                self.lib.gd_sim_run_one_replay_native_clock(
                    *arguments, ctypes.byref(replay), buff_arg, engine_arg, int(native_scene_delays), float(util_time))
            elif native_scene_delays:
                if not hasattr''')

    for path in (SIM / "gd_core_test/OracleAlignBattle.gd", SIM / "tools/verify_oracle.py"):
        source = path.read_text("utf8")
        line = next(line for line in source.splitlines() if "setReplayInitial(" in line)
        parent = 'c["replay_initial"]' if path.suffix == ".gd" else "native_initial"
        changes[path] = replace_one(source, line, line[:-1] + f', float({parent}.get("util_time", 0.0)))')

    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

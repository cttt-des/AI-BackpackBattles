"""Replay SceneTreeTimer ordering, precision and the opening idle pass."""
from pathlib import Path


stage = Path(__file__).resolve().parent
sim = stage / "sim_native"


def replace(path, old, new):
    text = path.read_text("utf8")
    assert text.count(old) == 1, (path, old)
    path.write_text(text.replace(old, new), encoding="utf8", newline="\n")


model = (stage / "native_scene_delay.gd.inc").read_text("utf8")
for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    context = root / "gd_core/CoreContext.gd"
    replace(context, "\t_timed.push_back([obj, methodName, delay, binds])\n", '''\tif replay_native_scene_delays:
\t\tdelay = _nativeF32(delay)
\t_timed.push_back([obj, methodName, delay, binds])
''')
    anchor = "func _flushTimed() -> void :\n"
    replace(context, anchor, model + "\n\n" + anchor + '''\tif replay_native_scene_delays:
\t\t_step_native_delays(PHYSICS_DELTA)
\t\treturn
''')
    replace(context, "var replay_engine_rng = null\n", "var replay_engine_rng = null\nvar replay_native_scene_delays := false\nvar _opening_delay_ready := []\n")
    replace(context, "engine_rng = null) -> void:\n", "engine_rng = null, scene_delays: bool = false) -> void:\n")
    replace(context, "\treplay_engine_rng = engine_rng\n", "\treplay_engine_rng = engine_rng\n\treplay_native_scene_delays = scene_delays\n")
    replace(context, "\tfor snapshot in flicker_initial:\n", "\t_opening_delay_ready.clear()\n\tvar restored_delays := []\n\tfor snapshot in flicker_initial:\n")
    replace(context, '\t\t\tcallDelayed(flicker, "playAni", float(pending["left"]))\n', '''\t\t\tif replay_native_scene_delays:
\t\t\t\trestored_delays.append([pending["order"], flicker, float(pending["left_at_first_physics"])])
\t\t\telse:
\t\t\t\tcallDelayed(flicker, "playAni", float(pending["left"]))
\trestored_delays.sort_custom(self, "_scene_delay_created_before")
\tfor entry in restored_delays:
\t\tif entry[2] < 0:
\t\t\t_opening_delay_ready.append(entry[1])
\t\telse:
\t\t\tcallDelayed(entry[1], "playAni", entry[2])

func _scene_delay_created_before(left, right) -> bool:
\treturn left[0] < right[0]

func runOpeningSceneDelays() -> void:
\tfor flicker in _opening_delay_ready:
\t\tflicker.playAni()
\t_opening_delay_ready.clear()
''')
    combat = root / "gd_core/CoreCombat.gd"
    anchor = "\t\t\tactivateItems(ordered_items)\n"
    replace(combat, anchor, anchor + "\t\t\tctx.runOpeningSceneDelays()\n")

gd = sim / "gd_core_test/OracleAlignBattle.gd"
replace(gd, 'c["replay_initial"].get("engine_rng"))', 'c["replay_initial"].get("engine_rng"), c["replay_initial"].get("native_scene_delays", false))')
anchor = '\tif ctx.replay_engine_rng != null:\n'
replace(gd, anchor, '\tif ctx.replay_native_scene_delays:\n\t\tpayload["replay_initial"]["native_scene_delays"] = true\n' + anchor)

py = sim / "tools/verify_oracle.py"
replace(py, 'native_initial.get("engine_rng"))', 'native_initial.get("engine_rng"), native_initial.get("native_scene_delays", False))')
anchor = '        if eng.ctx.replay_engine_rng is not None:\n'
replace(py, anchor, '        if eng.ctx.replay_native_scene_delays:\n            replay_initial["native_scene_delays"] = True\n' + anchor)

cpp = sim / "native_sim_cpp/native_sim/engine_wrapper.cpp"
replace(cpp, '    const ReplayEngineRng* engine_rng = nullptr\n', '    const ReplayEngineRng* engine_rng = nullptr,\n    bool scene_delays = false\n')
replace(cpp, '                    auto* call = gd::GdDict::create(battle.arena, 2);\n', '                    auto* call = gd::GdDict::create(battle.arena, scene_delays ? 4 : 2);\n')
replace(cpp, '                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left"), gd::GdVal::from_float(f.pending[j]));\n', '''                    const auto offset = scene_delays ? 3 * j : j;
                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left"), gd::GdVal::from_float(f.pending[offset]));
                    if (scene_delays) {
                        call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "order"), gd::GdVal::from_int(static_cast<int64_t>(f.pending[offset + 1])));
                        call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left_at_first_physics"), gd::GdVal::from_float(f.pending[offset + 2]));
                    }
''')
replace(cpp, '        gd::GdVal initial[5] = {\n', '        gd::GdVal initial[6] = {\n')
replace(cpp, '            gd::GdVal::from_arr(idle), flicker_initial, buff_initial, engine_initial\n', '            gd::GdVal::from_arr(idle), flicker_initial, buff_initial, engine_initial, gd::GdVal::from_bool(scene_delays)\n')
replace(cpp, '        ctx_obj->fn_setReplayInitial(initial, 5);\n', '        ctx_obj->fn_setReplayInitial(initial, 6);\n')
anchor = 'void gd_sim_run_one_replay_engine_rng(\n'
replace(cpp, anchor, '''static bool valid_engine_rng(const ReplayEngineRng& engine) {
    return engine.prepare_offset >= 0 && engine.prepare_offset < 8192 &&
           engine.activate_offset >= 0 && engine.activate_offset < 8192 &&
           engine.label_mode >= 0 && engine.label_mode <= 3;
}

''' + anchor)
replace(cpp, '''    if (!initial || !engine || (buffs && !valid_replay_buffs(*buffs)) ||
        engine->prepare_offset < 0 || engine->prepare_offset >= 8192 ||
        engine->activate_offset < 0 || engine->activate_offset >= 8192 ||
        engine->label_mode < 0 || engine->label_mode > 3) {
''', '''    if (!initial || !engine || (buffs && !valid_replay_buffs(*buffs)) || !valid_engine_rng(*engine)) {
''')
anchor = '// 调试导出：最近一场的 canonical 事件行'
replace(cpp, anchor, '''// With this entry point each PackedFlicker timer is three doubles:
// activation remaining time, creation order and first-physics remaining time.
void gd_sim_run_one_replay_scene_delays(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine))) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine, true);
}

''' + anchor)

binding = sim / "native_sim_cpp/native_sim/sim.py"
anchor = '            lib.gd_sim_run_one_replay_engine_rng.restype = None\n'
replace(binding, anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay_scene_delays"):
            lib.gd_sim_run_one_replay_scene_delays.argtypes = lib.gd_sim_run_one_replay_engine_rng.argtypes
            lib.gd_sim_run_one_replay_scene_delays.restype = None
''')
anchor = '            flickers = initial.get("flickers")\n'
replace(binding, anchor, anchor + '            native_scene_delays = initial.get("native_scene_delays", False)\n')
replace(binding, '                pending = (ctypes.c_double * len(calls))(*(float(call["left"]) for call in calls))\n', '''                fields = ("left", "order", "left_at_first_physics") if native_scene_delays else ("left",)
                pending = (ctypes.c_double * (len(calls) * len(fields)))(
                    *(float(call[key]) for call in calls for key in fields))
''')
replace(binding, '            if observed_engine is not None:\n', '            engine = None\n            if observed_engine is not None:\n')
anchor = '''                buff_arg = ctypes.byref(buffs) if buffs is not None else None
                self.lib.gd_sim_run_one_replay_engine_rng(*arguments, ctypes.byref(replay), buff_arg, ctypes.byref(engine))
'''
replace(binding, anchor, '''            buff_arg = ctypes.byref(buffs) if buffs is not None else None
            if native_scene_delays:
                if not hasattr(self.lib, "gd_sim_run_one_replay_scene_delays"):
                    raise RuntimeError("This DLL does not support observed SceneTreeTimer delays")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                self.lib.gd_sim_run_one_replay_scene_delays(*arguments, ctypes.byref(replay), buff_arg, engine_arg)
            elif engine is not None:
                self.lib.gd_sim_run_one_replay_engine_rng(*arguments, ctypes.byref(replay), buff_arg, ctypes.byref(engine))
''')

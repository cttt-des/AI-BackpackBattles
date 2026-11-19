"""Optional native replay entry; preserve the existing packed ABI and fast path."""
from pathlib import Path

stage = Path.cwd() / "output/_v1110"
src = stage / "sim/native_sim_cpp/native_sim"
dest = stage / "sim_native/native_sim_cpp/native_sim"
cpp = (src / "engine_wrapper.cpp").read_text("utf8")
anchor = "struct BattleOptions {\n"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, '''struct ReplayInitial {
    int32_t has_activation_state;
    uint64_t activation_state;
    double player_idle_left;
    double opponent_idle_left;
};

''' + anchor)
anchor = "    BattleResult& out\n) {\n"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, "    BattleResult& out,\n    const ReplayInitial* replay = nullptr\n) {\n")
anchor = "    // ★ 夹具 activation_order 直通"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, '''    if (replay) {
        auto* idle = gd::GdArr::create(battle.arena, 2);
        idle->push_back(battle.arena, gd::GdVal::from_float(replay->player_idle_left));
        idle->push_back(battle.arena, gd::GdVal::from_float(replay->opponent_idle_left));
        gd::GdVal initial[2] = {
            replay->has_activation_state
                ? gd::GdVal::from_int(static_cast<int64_t>(replay->activation_state))
                : gd::GdVal(),
            gd::GdVal::from_arr(idle)
        };
        ctx_obj->fn_setReplayInitial(initial, 2);
    }

''' + anchor)
cpp = cpp.replace("gd::GdVal::from_float(1.0 / 60.0)", "gd::GdVal::from_float(0.01666666753590107)")
anchor = "// 调试导出：最近一场的 canonical 事件行"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, '''void gd_sim_run_one_replay(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial
) {
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial);
}

''' + anchor)
(dest / "engine_wrapper.cpp").write_text(cpp, encoding="utf8", newline="\n")

binding = (src / "sim.py").read_text("utf8")
anchor = "class BattleOptions(ctypes.Structure):\n"
assert binding.count(anchor) == 1
binding = binding.replace(anchor, '''class ReplayInitial(ctypes.Structure):
    _fields_ = [
        ("has_activation_state", ctypes.c_int32),
        ("activation_state", ctypes.c_uint64),
        ("player_idle_left", ctypes.c_double),
        ("opponent_idle_left", ctypes.c_double),
    ]


''' + anchor)
anchor = "        lib.gd_sim_run_one.restype = None\n"
assert binding.count(anchor) == 1
binding = binding.replace(anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay"):
            lib.gd_sim_run_one_replay.argtypes = lib.gd_sim_run_one.argtypes + [ctypes.POINTER(ReplayInitial)]
            lib.gd_sim_run_one_replay.restype = None
''')
anchor = "        opts = self.make_options(**opt_kwargs)\n"
assert binding.count(anchor) == 1
binding = binding.replace(anchor, '        initial = opt_kwargs.pop("replay_initial", None)\n' + anchor)
anchor = '''        self.lib.gd_sim_run_one(
            ctypes.byref(ph.side), ctypes.byref(oh.side), ctypes.byref(opts), ctypes.byref(res)
        )
'''
assert binding.count(anchor) == 1
binding = binding.replace(anchor, '''        arguments = [ctypes.byref(ph.side), ctypes.byref(oh.side), ctypes.byref(opts), ctypes.byref(res)]
        if initial is None:
            self.lib.gd_sim_run_one(*arguments)
        else:
            if not hasattr(self.lib, "gd_sim_run_one_replay"):
                raise RuntimeError("This DLL does not support the observed initial replay context")
            idle = initial["idle_left"]
            if len(idle) != 2:
                raise ValueError("idle_left must contain player and opponent timer values")
            state = initial.get("activation_rng_state")
            replay = ReplayInitial(int(state is not None), int(state or 0) & 0xFFFFFFFFFFFFFFFF,
                                   float(idle[0]), float(idle[1]))
            self.lib.gd_sim_run_one_replay(*arguments, ctypes.byref(replay))
''')
(dest / "sim.py").write_text(binding, encoding="utf8", newline="\n")
print(dest)

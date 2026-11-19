"""Optional native replay entry; preserve the existing packed ABI and fast path."""
from pathlib import Path

stage = Path.cwd() / "output/_v1110"
src = stage / "sim/native_sim_cpp/native_sim"
dest = stage / "sim_native/native_sim_cpp/native_sim"
cpp = (src / "engine_wrapper.cpp").read_text("utf8")
anchor = "struct BattleOptions {\n"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, '''struct PackedFlicker {
    double position, speed, length, min_dist, max_dist, min_speed, max_speed;
    int32_t playing, inside_tree, loop, n_pending;
    const double* pending;
};

struct ReplayInitial {
    int32_t has_activation_state;
    uint64_t activation_state;
    double player_idle_left;
    double opponent_idle_left;
    int32_t n_flickers;
    const PackedFlicker* flickers;
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
        gd::GdVal flicker_initial;
        if (replay->n_flickers >= 0) {
            auto* states = gd::GdArr::create(battle.arena, replay->n_flickers);
            for (int32_t i = 0; i < replay->n_flickers; ++i) {
                const auto& f = replay->flickers[i];
                auto* state = gd::GdDict::create(battle.arena, 8);
                auto put = [&](const char* key, gd::GdVal value) {
                    state->set(battle.arena, gd::GdVal::from_cstr(battle.arena, key), value);
                };
                put("position", gd::GdVal::from_float(f.position));
                put("speed", gd::GdVal::from_float(f.speed));
                put("length", gd::GdVal::from_float(f.length));
                put("playing", gd::GdVal::from_bool(f.playing != 0));
                put("inside_tree", gd::GdVal::from_bool(f.inside_tree != 0));
                put("loop", gd::GdVal::from_bool(f.loop != 0));
                auto* limits = gd::GdArr::create(battle.arena, 4);
                for (double value : {f.min_dist, f.max_dist, f.min_speed, f.max_speed})
                    limits->push_back(battle.arena, gd::GdVal::from_float(value));
                put("limits", gd::GdVal::from_arr(limits));
                auto* pending = gd::GdArr::create(battle.arena, f.n_pending);
                for (int32_t j = 0; j < f.n_pending; ++j) {
                    auto* call = gd::GdDict::create(battle.arena, 2);
                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "method"), gd::GdVal::from_cstr(battle.arena, "playAni"));
                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left"), gd::GdVal::from_float(f.pending[j]));
                    pending->push_back(battle.arena, gd::GdVal::from_dict(call));
                }
                put("pending", gd::GdVal::from_arr(pending));
                states->push_back(battle.arena, gd::GdVal::from_dict(state));
            }
            flicker_initial = gd::GdVal::from_arr(states);
        }
        gd::GdVal initial[3] = {
            replay->has_activation_state
                ? gd::GdVal::from_int(static_cast<int64_t>(replay->activation_state))
                : gd::GdVal(),
            gd::GdVal::from_arr(idle), flicker_initial
        };
        ctx_obj->fn_setReplayInitial(initial, 3);
    }

''' + anchor)
cpp = cpp.replace("gd::GdVal::from_float(1.0 / 60.0)", "gd::GdVal::from_float(0.01666666753590107)")
anchor = "// 调试导出：最近一场的 canonical 事件行"
assert cpp.count(anchor) == 1
cpp = cpp.replace(anchor, '''void gd_sim_run_one_replay_v2(
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
binding = binding.replace(anchor, '''class PackedFlicker(ctypes.Structure):
    _fields_ = [(name, ctypes.c_double) for name in
               ("position", "speed", "length", "min_dist", "max_dist", "min_speed", "max_speed")] + [
        (name, ctypes.c_int32) for name in ("playing", "inside_tree", "loop", "n_pending")] + [
        ("pending", ctypes.POINTER(ctypes.c_double))]


class ReplayInitial(ctypes.Structure):
    _fields_ = [
        ("has_activation_state", ctypes.c_int32),
        ("activation_state", ctypes.c_uint64),
        ("player_idle_left", ctypes.c_double),
        ("opponent_idle_left", ctypes.c_double),
        ("n_flickers", ctypes.c_int32),
        ("flickers", ctypes.POINTER(PackedFlicker)),
    ]


''' + anchor)
anchor = "        lib.gd_sim_run_one.restype = None\n"
assert binding.count(anchor) == 1
binding = binding.replace(anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay_v2"):
            lib.gd_sim_run_one_replay_v2.argtypes = lib.gd_sim_run_one.argtypes + [ctypes.POINTER(ReplayInitial)]
            lib.gd_sim_run_one_replay_v2.restype = None
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
            if not hasattr(self.lib, "gd_sim_run_one_replay_v2"):
                raise RuntimeError("This DLL does not support the observed initial replay context")
            idle = initial["idle_left"]
            if len(idle) != 2:
                raise ValueError("idle_left must contain player and opponent timer values")
            state = initial.get("activation_rng_state")
            flickers = initial.get("flickers")
            packed = (PackedFlicker * len(flickers))() if flickers is not None else None
            pending_arrays = []
            for i, flicker in enumerate(flickers or []):
                calls = flicker["pending"]
                if any(call["method"] != "playAni" for call in calls):
                    raise ValueError("Unsupported initial flicker callback")
                pending = (ctypes.c_double * len(calls))(*(float(call["left"]) for call in calls))
                pending_arrays.append(pending)
                packed[i] = PackedFlicker(float(flicker.get("position_precise", flicker["position"])),
                                          float(flicker.get("speed_precise", flicker["speed"])),
                                          float(flicker["length"]), *map(float, flicker["limits"]),
                                          int(flicker["playing"]), int(flicker["inside_tree"]), int(flicker["loop"]),
                                          len(calls), pending)
            replay = ReplayInitial(int(state is not None), int(state or 0) & 0xFFFFFFFFFFFFFFFF,
                                   float(idle[0]), float(idle[1]),
                                   len(flickers) if flickers is not None else -1, packed)
            self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))
''')
(dest / "sim.py").write_text(binding, encoding="utf8", newline="\n")
print(dest)

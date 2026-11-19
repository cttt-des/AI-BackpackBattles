"""Stage observed engine RNG boundaries and compact critical-label draw timing."""
from pathlib import Path


stage = Path(__file__).resolve().parent
sim = stage / "sim_native"


def replace(path, old, new):
    text = path.read_text("utf8")
    assert text.count(old) == 1, (path, old)
    path.write_text(text.replace(old, new), encoding="utf8", newline="\n")


shake_schedule = (stage / "native_critical_shake.gd.inc").read_text("utf8")
for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    context = root / "gd_core/CoreContext.gd"
    replace(context, "func setReplayInitial(activation_state, idle_left: Array, flickers = null, buff_state = null) -> void:\n",
            "var replay_engine_rng = null\n\nfunc setReplayInitial(activation_state, idle_left: Array, flickers = null, buff_state = null, engine_rng = null) -> void:\n")
    replace(context, "\treplay_buff_state = buff_state\n", '''\treplay_buff_state = buff_state
\treplay_engine_rng = engine_rng

func restoreEngineRng(activating: bool) -> void:
\tif replay_engine_rng == null:
\t\treturn
\tvar base := 2 if activating else 0
\tseed(int(replay_engine_rng[base]))
\tfor i in range(int(replay_engine_rng[base + 1])):
\t\trandi()

func collectCriticalLabels(has_item: bool) -> void:
\tvar mode := int(replay_engine_rng[4])
\tif mode == 0 or mode == 1:
\t\tcollectCriticalShake(false)
\tif has_item and (mode == 0 or mode == 2):
\t\tcollectCriticalShake(true)
''' + "\n" + shake_schedule)
    combat = root / "gd_core/CoreCombat.gd"
    replace(combat, "\tprepareItems(ordered_items)\n", "\tctx.restoreEngineRng(false)\n\tctx.resetCriticalShake()\n\tprepareItems(ordered_items)\n")
    replace(combat, "\tctx.restoreReplayBuffs()\n", "\tctx.restoreEngineRng(true)\n\tctx.restoreReplayBuffs()\n")
    replace(combat, "\tctx.timer_pass_epoch += 1\n", "\tif ctx.replay_engine_rng != null:\n\t\tctx.beginCriticalShakeFrame()\n\tctx.timer_pass_epoch += 1\n")
    replace(combat, "\tctx.tickFlickers(delta)\n", "\tctx.tickFlickers(delta)\n\tif ctx.replay_engine_rng != null:\n\t\tctx.stepCriticalShake()\n")
    character = root / "gd_core/CoreCharacter.gd"
    replace(character, "\tctx.hooks.spawnLabel_character(self, type, damage, item)\n", '''\tif ctx.replay_engine_rng != null and type == CoreConst.EventType.CriticalDamage:
\t\tctx.collectCriticalLabels(item is CoreItem)
\tctx.hooks.spawnLabel_character(self, type, damage, item)
''')

gd = sim / "gd_core_test/OracleAlignBattle.gd"
replace(gd, 'c["replay_initial"].get("buff_state"))', 'c["replay_initial"].get("buff_state"), c["replay_initial"].get("engine_rng"))')
anchor = '\tif ctx.replay_buff_state != null:\n'
replace(gd, anchor, '\tif ctx.replay_engine_rng != null:\n\t\tpayload["replay_initial"]["engine_rng"] = ctx.replay_engine_rng\n' + anchor)

py = sim / "tools/verify_oracle.py"
replace(py, 'native_initial.get("buff_state"))', 'native_initial.get("buff_state"), native_initial.get("engine_rng"))')
anchor = '        if eng.ctx.replay_buff_state is not None:\n'
replace(py, anchor, '        if eng.ctx.replay_engine_rng is not None:\n            replay_initial["engine_rng"] = eng.ctx.replay_engine_rng\n' + anchor)

py_generator = sim / "tools/gd_to_py.py"
anchor = '            (r"(?<![\\w.])randomize\\s*\\(", "randomize(", "randomize→垫片"),\n'
replace(py_generator, anchor, anchor + r'''            (r"(?<![\w.])seed\s*\(", "_math_rng().set_seed(", "global seed"),
            (r"(?<![\w.])randi\s*\(", "_math_rng().randi(", "global randi"),
''')
replace(sim / "gd_core_py/_rt.py", '    "RandomNumberGenerator", "PCG32",\n', '    "RandomNumberGenerator", "PCG32", "_math_rng",\n')

cpp_generator = sim / "native_sim_cpp/tools/gd_to_cpp.py"
anchor = '            if fn == "randomize":\n'
replace(cpp_generator, anchor, '''            if fn == "seed":
                return f"(gd_ctx.math_rng.set_seed(static_cast<uint64_t>({args_cpp[0]}.as_int())), gd::GdVal::null())"
            if fn == "randi":
                return "gd::GdVal::from_int(gd_ctx.math_rng.randi())"
''' + anchor)

cpp = sim / "native_sim_cpp/native_sim/engine_wrapper.cpp"
anchor = 'struct BattleOptions {\n'
replace(cpp, anchor, '''struct ReplayEngineRng {
    int64_t prepare_seed, activate_seed;
    int32_t prepare_offset, activate_offset, label_mode;
};

''' + anchor)
replace(cpp, '    const ReplayBuffState* buffs = nullptr\n',
        '    const ReplayBuffState* buffs = nullptr,\n    const ReplayEngineRng* engine_rng = nullptr\n')
replace(cpp, '        gd::GdVal initial[4] = {\n', '''        gd::GdVal engine_initial;
        if (engine_rng) {
            auto* engine = gd::GdArr::create(battle.arena, 5);
            for (int64_t value : {engine_rng->prepare_seed, int64_t{engine_rng->prepare_offset},
                                  engine_rng->activate_seed, int64_t{engine_rng->activate_offset},
                                  int64_t{engine_rng->label_mode}}) {
                engine->push_back(battle.arena, gd::GdVal::from_int(value));
            }
            engine_initial = gd::GdVal::from_arr(engine);
        }
        gd::GdVal initial[5] = {
''')
replace(cpp, '            gd::GdVal::from_arr(idle), flicker_initial, buff_initial\n',
        '            gd::GdVal::from_arr(idle), flicker_initial, buff_initial, engine_initial\n')
replace(cpp, '        ctx_obj->fn_setReplayInitial(initial, 4);\n', '        ctx_obj->fn_setReplayInitial(initial, 5);\n')
anchor = 'void gd_sim_run_one_replay_buff_state(\n'
replace(cpp, anchor, '''static bool valid_replay_buffs(const ReplayBuffState& buffs) {
    if (buffs.count < 0 || buffs.count > 22 || (buffs.count && !buffs.rows)) return false;
    for (int32_t i = 0; i < buffs.count; ++i) {
        const auto& row = buffs.rows[i];
        if (row.side < 0 || row.side > 1 || row.type < 100 || row.type > 110) return false;
    }
    return true;
}

''' + anchor)
replace(cpp, '''    if (!initial || !buffs || buffs->count < 0 || buffs->count > 22 || (buffs->count && !buffs->rows)) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    for (int32_t i = 0; i < buffs->count; ++i) {
        const auto& row = buffs->rows[i];
        if (row.side < 0 || row.side > 1 || row.type < 100 || row.type > 110) {
            *out = {};
            out->timed_out = 1;
            return;
        }
    }
''', '''    if (!initial || !buffs || !valid_replay_buffs(*buffs)) {
        *out = {};
        out->timed_out = 1;
        return;
    }
''')
anchor = '// 调试导出：最近一场的 canonical 事件行'
replace(cpp, anchor, '''void gd_sim_run_one_replay_engine_rng(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine
) {
    if (!initial || !engine || (buffs && !valid_replay_buffs(*buffs)) ||
        engine->prepare_offset < 0 || engine->prepare_offset >= 8192 ||
        engine->activate_offset < 0 || engine->activate_offset >= 8192 ||
        engine->label_mode < 0 || engine->label_mode > 3) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine);
}

''' + anchor)

binding = sim / "native_sim_cpp/native_sim/sim.py"
anchor = "class BattleOptions(ctypes.Structure):\n"
replace(binding, anchor, '''class ReplayEngineRng(ctypes.Structure):
    _fields_ = [("prepare_seed", ctypes.c_int64), ("activate_seed", ctypes.c_int64),
                ("prepare_offset", ctypes.c_int32), ("activate_offset", ctypes.c_int32),
                ("label_mode", ctypes.c_int32)]


''' + anchor)
anchor = '            lib.gd_sim_run_one_replay_buff_state.restype = None\n'
replace(binding, anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay_engine_rng"):
            lib.gd_sim_run_one_replay_engine_rng.argtypes = lib.gd_sim_run_one_replay_buff_state.argtypes + [ctypes.POINTER(ReplayEngineRng)]
            lib.gd_sim_run_one_replay_engine_rng.restype = None
''')
replace(binding, '''            if observed_buffs is None:
                self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))
            else:
''', '''            buffs = None
            if observed_buffs is not None:
''')
replace(binding, '                self.lib.gd_sim_run_one_replay_buff_state(*arguments, ctypes.byref(replay), ctypes.byref(buffs))\n',
        '''            observed_engine = initial.get("engine_rng")
            if observed_engine is not None:
                if not hasattr(self.lib, "gd_sim_run_one_replay_engine_rng"):
                    raise RuntimeError("This DLL does not support observed global RNG state")
                prepare_seed, prepare_offset, activate_seed, activate_offset, label_mode = map(int, observed_engine)
                if not (0 <= prepare_offset < 8192 and 0 <= activate_offset < 8192 and 0 <= label_mode <= 3):
                    raise ValueError("Invalid replay RNG offset or damage-number mode")
                engine = ReplayEngineRng(prepare_seed, activate_seed, prepare_offset, activate_offset, label_mode)
                buff_arg = ctypes.byref(buffs) if buffs is not None else None
                self.lib.gd_sim_run_one_replay_engine_rng(*arguments, ctypes.byref(replay), buff_arg, ctypes.byref(engine))
            elif buffs is not None:
                self.lib.gd_sim_run_one_replay_buff_state(*arguments, ctypes.byref(replay), ctypes.byref(buffs))
            else:
                self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))
''')

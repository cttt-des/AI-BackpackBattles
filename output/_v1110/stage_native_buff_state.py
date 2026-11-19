"""Carry observed permanent stacks into deterministic replay at activation."""
from pathlib import Path


sim = Path(__file__).resolve().parent / "sim_native"


def replace(path, old, new):
    source = path.read_text("utf8")
    assert source.count(old) == 1, (path, old)
    path.write_text(source.replace(old, new), encoding="utf8", newline="\n")


for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    context = root / "gd_core/CoreContext.gd"
    replace(context, "func setReplayInitial(activation_state, idle_left: Array, flickers = null) -> void:\n",
            "var replay_buff_state = null\n\nfunc setReplayInitial(activation_state, idle_left: Array, flickers = null, buff_state = null) -> void:\n")
    replace(context, "\tflicker_initial = flickers\n", '''\tflicker_initial = flickers
\treplay_buff_state = buff_state

func restoreReplayBuffs() -> void:
\tif replay_buff_state == null:
\t\treturn
\tassert(replay_buff_state.size() == 2)
\tvar characters = [player, opponent]
\tfor side in range(2):
\t\tfor row in replay_buff_state[side]:
\t\t\tvar buff = characters[side].buffs[int(row[0])]
\t\t\tassert(buff.current == int(row[1]))
\t\t\tassert(int(row[3]) == 0 and buff.temporaryStacks.empty())
\t\t\tbuff.permanentStacks = int(row[2])

''')
    combat = root / "gd_core/CoreCombat.gd"
    replace(combat, 'func activateItems(items: Array) -> void :\n',
            'func activateItems(items: Array) -> void :\n\tctx.restoreReplayBuffs()\n')

gd = sim / "gd_core_test/OracleAlignBattle.gd"
replace(gd, 'c["replay_initial"].get("flickers"))',
        'c["replay_initial"].get("flickers"), c["replay_initial"].get("buff_state"))')
anchor = '\tif fh.open(dir.plus_file("events.json"), File.WRITE) == OK:\n'
replace(gd, anchor, '\tif ctx.replay_buff_state != null:\n\t\tpayload["replay_initial"]["buff_state"] = ctx.replay_buff_state\n' + anchor)

py = sim / "tools/verify_oracle.py"
replace(py, 'native_initial.get("flickers"))', 'native_initial.get("flickers"), native_initial.get("buff_state"))')
start = '    return {\n        "case_id": case_id, "seed": int(seed),\n'
replace(py, start, '''    replay_initial = None
    if eng.ctx.activation_rng_state is not None:
        replay_initial = {"activation_rng_state": eng.ctx.activation_rng_state,
                          "idle_left": list(eng.ctx.idle_timer_initial), "flickers": eng.ctx.flicker_initial}
        if eng.ctx.replay_buff_state is not None:
            replay_initial["buff_state"] = eng.ctx.replay_buff_state
''' + start)
replace(py, '''        "replay_initial": {"activation_rng_state": eng.ctx.activation_rng_state,
                           "idle_left": list(eng.ctx.idle_timer_initial), "flickers": eng.ctx.flicker_initial} if eng.ctx.activation_rng_state is not None else None,
''', '        "replay_initial": replay_initial,\n')

cpp = sim / "native_sim_cpp/native_sim/engine_wrapper.cpp"
anchor = "struct BattleOptions {\n"
replace(cpp, anchor, '''struct PackedReplayBuff {
    int32_t side, type, current, permanent;
};

struct ReplayBuffState {
    int32_t count;
    const PackedReplayBuff* rows;
};

''' + anchor)
replace(cpp, "    const ReplayInitial* replay = nullptr\n", "    const ReplayInitial* replay = nullptr,\n    const ReplayBuffState* buffs = nullptr\n")
replace(cpp, "        gd::GdVal initial[3] = {\n", '''        gd::GdVal buff_initial;
        if (buffs) {
            gd::GdArr* sides[2] = {gd::GdArr::create(battle.arena, 0), gd::GdArr::create(battle.arena, 0)};
            for (int32_t i = 0; i < buffs->count; ++i) {
                const auto& buff = buffs->rows[i];
                auto* row = gd::GdArr::create(battle.arena, 4);
                for (int32_t field : {buff.type, buff.current, buff.permanent, 0})
                    row->push_back(battle.arena, gd::GdVal::from_int(field));
                sides[buff.side]->push_back(battle.arena, gd::GdVal::from_arr(row));
            }
            auto* state = gd::GdArr::create(battle.arena, 2);
            for (auto* side : sides) state->push_back(battle.arena, gd::GdVal::from_arr(side));
            buff_initial = gd::GdVal::from_arr(state);
        }
        gd::GdVal initial[4] = {
''')
replace(cpp, '            gd::GdVal::from_arr(idle), flicker_initial\n', '            gd::GdVal::from_arr(idle), flicker_initial, buff_initial\n')
replace(cpp, '        ctx_obj->fn_setReplayInitial(initial, 3);\n', '        ctx_obj->fn_setReplayInitial(initial, 4);\n')
anchor = "// 调试导出：最近一场的 canonical 事件行"
replace(cpp, anchor, '''void gd_sim_run_one_replay_buff_state(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs
) {
    if (!initial || !buffs || buffs->count < 0 || buffs->count > 22 || (buffs->count && !buffs->rows)) {
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
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs);
}

''' + anchor)

binding = sim / "native_sim_cpp/native_sim/sim.py"
anchor = "class BattleOptions(ctypes.Structure):\n"
replace(binding, anchor, '''class PackedReplayBuff(ctypes.Structure):
    _fields_ = [(name, ctypes.c_int32) for name in ("side", "type", "current", "permanent")]


class ReplayBuffState(ctypes.Structure):
    _fields_ = [("count", ctypes.c_int32), ("rows", ctypes.POINTER(PackedReplayBuff))]


''' + anchor)
anchor = "            lib.gd_sim_run_one_replay_v2.restype = None\n"
replace(binding, anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_replay_buff_state"):
            lib.gd_sim_run_one_replay_buff_state.argtypes = lib.gd_sim_run_one_replay_v2.argtypes + [ctypes.POINTER(ReplayBuffState)]
            lib.gd_sim_run_one_replay_buff_state.restype = None
''')
replace(binding, "            self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))\n", '''            observed_buffs = initial.get("buff_state")
            if observed_buffs is None:
                self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))
            else:
                if not hasattr(self.lib, "gd_sim_run_one_replay_buff_state"):
                    raise RuntimeError("This DLL does not support observed permanent stacks")
                if len(observed_buffs) != 2:
                    raise ValueError("buff_state must have two sides")
                rows = []
                for side, observed in enumerate(observed_buffs):
                    for type_id, current, permanent, temporary_count in observed:
                        if int(temporary_count) != 0:
                            raise ValueError("Replay does not import active temporary stacks")
                        rows.append(PackedReplayBuff(side, int(type_id), int(current), int(permanent)))
                packed_buffs = (PackedReplayBuff * len(rows))(*rows)
                buffs = ReplayBuffState(len(rows), packed_buffs)
                self.lib.gd_sim_run_one_replay_buff_state(*arguments, ctypes.byref(replay), ctypes.byref(buffs))
''')

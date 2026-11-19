"""Advance idle RNG timers in the order of the original character subtrees."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        source = replace_one(source, "var _flickers: Array = []\n",
                             "var _flickers: Array = []\nvar _opponent_flickers: Array = []\n")
        source = replace_one(source, "\t_flickers = []\n\t_opening_delay_ready.clear()",
                             "\t_flickers = []\n\t_opponent_flickers = []\n\t_opening_delay_ready.clear()")
        source = replace_one(source, "\t\t_flickers.append(flicker)\n",
                             "\t\tif snapshot.get(\"native_opponent\", false):\n"
                             "\t\t\t_opponent_flickers.append(flicker)\n"
                             "\t\telse:\n\t\t\t_flickers.append(flicker)\n")
        changes[context] = replace_one(source, "func tickFlickers(delta: float) -> void:\n",
                                       "func tickOpponentFlickers(delta: float) -> void:\n"
                                       "\tfor flicker in _opponent_flickers:\n\t\tflicker.tick(delta)\n\n"
                                       "func tickFlickers(delta: float) -> void:\n")

        combat = root / "gd_core/CoreCombat.gd"
        source = combat.read_text("utf8")
        anchor = "\topponent.tickIdleAnimation(delta)\n"
        changes[combat] = replace_one(source, anchor,
                                      "\t# Internal idle processing traverses Opponent before Player.\n" +
                                      anchor + "\tctx.tickOpponentFlickers(delta)\n")

    native = SIM / "native_sim_cpp/native_sim"
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = replace_one(source, "    int32_t playing, inside_tree, loop, n_pending;\n",
                         "    int32_t playing;\n"
                         "    int32_t attachment;  // 0 off tree, 1 attached, 2 attached under Opponent\n"
                         "    int32_t loop, n_pending;\n")
    changes[wrapper] = replace_one(source, '                put("inside_tree", gd::GdVal::from_bool(f.inside_tree != 0));\n',
                                   '                put("inside_tree", gd::GdVal::from_bool(f.attachment != 0));\n'
                                   '                if (f.attachment == 2) put("native_opponent", gd::GdVal::from_bool(true));\n')
    binding = native / "sim.py"
    source = binding.read_text("utf8")
    source = replace_one(source, '("playing", "inside_tree", "loop", "n_pending")',
                         '("playing", "attachment", "loop", "n_pending")')
    source = replace_one(source, "                packed[i] = PackedFlicker",
                         "                attachment = 2 if flicker.get(\"native_opponent\") else int(flicker[\"inside_tree\"])\n"
                         "                packed[i] = PackedFlicker")
    changes[binding] = replace_one(source, 'int(flicker["playing"]), int(flicker["inside_tree"]), int(flicker["loop"]),',
                                   'int(flicker["playing"]), attachment, int(flicker["loop"]),')
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

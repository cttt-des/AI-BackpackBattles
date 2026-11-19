"""Restore source stamina and temporary-stack behavior in the native path."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    changes = {}
    wrapper = SIM / "native_sim_cpp/native_sim/engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    anchor = "    if (player_side.snapshot_stamina >= 0.0) {\n"
    changes[wrapper] = replace_one(source, anchor, '''    if (training_start) {
        if (player_side.snapshot_stamina < 0.0) p_chr->fn_recalculateMaxStamina(nullptr, 0);
        if (opponent_side.snapshot_stamina < 0.0) o_chr->fn_recalculateMaxStamina(nullptr, 0);
    }

''' + anchor)
    for root in (SIM, SIM / "native_sim_cpp"):
        buff = root / "gd_core/CoreBuff.gd"
        source = buff.read_text("utf8")
        start = source.index("\t# ★ np25（run1132_r18 定谳", source.index("func onTimeout():\n"))
        stop = source.index("\tif not temporaryStacks.empty():\n", start)
        changes[buff] = source[:start] + '''\t# Removing other stacks can invalidate the cached index. The shipping
\t# engine still searches the remaining slots for the next valid expiry.
\tif nextTemporaryTimeout >= 0 and nextTemporaryTimeout < temporaryStacks.size():
\t\tvar timedOutStacks = temporaryStacks[nextTemporaryTimeout]
\t\tchangeCurrentLogShowLabel(true, timedOutStacks.amount, timedOutStacks.item)
\t\ttemporaryStacks.remove(nextTemporaryTimeout)
\t\t_blnd_snap("timeout", str(nextTemporaryTimeout))
\telif not ctx.native_frame_rng:
\t\treturn

''' + source[stop:]
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

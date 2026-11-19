"""Restore the source fatigue advance in the isolated native-aligned build."""
from pathlib import Path


stage = Path(__file__).resolve().parent
sim = stage / "sim_native"


def update(relative, transform):
    path = sim / relative
    source = path.read_text("utf8")
    updated = transform(source)
    assert updated != source, relative
    for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
        (root / relative).write_text(updated, encoding="utf8", newline="\n")


def restore_moon(source):
    start = source.index("func onPostCombatStart():\n")
    end = source.index("func onPrepare():\n", start)
    return source[:start] + "func onPostCombatStart():\n\tctx.combat.advanceTime(timeAdvance)\n\n\n" + source[end:]


def restore_fatigue(source):
    anchor = "\tif fatigue_next_tick > 0:\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, "\tif fatigue_next_tick >= 0.0:\n")
    anchor = "\tvar time_left = fatigue_next_tick\n"
    assert source.count(anchor) == 1
    # The source reads the start timer, which is stopped once the tick timer runs.
    source = source.replace(anchor, "\tvar time_left = 0.0 if fatigue_started else ctx._nativeF32(max(0.0, fatigue_next_tick))\n")
    anchor = "\t\tfatigue_next_tick = new_time\n"
    assert source.count(anchor) == 1
    return source.replace(anchor, "\t\tfatigue_next_tick = ctx._nativeF32(new_time)\n")


update("gd_core/CoreCombat.gd", restore_fatigue)
update("gd_core_items/Exclusive/PoweroftheMoon.gd", restore_moon)

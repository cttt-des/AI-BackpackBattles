"""Use the concrete C++ timer pass and skip empty item timer arrays."""
from pathlib import Path
import re
import sys

from optimize_native_cooldowns import SHARDS


ENTRY = "gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers("
METHOD = """gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers(const gd::GdVal* args, int argc) {
    auto* character = static_cast<Gd__gd_core__CoreCharacter*>(args[0].obj);
    const auto delta = gd::gd_coerce_float(argc > 1 ? args[1] : gd::GdVal::null());
    character->fn_tickPhysicsTimers(&delta, 1);
    character->fn_tickBuffs(&delta, 1);
    const auto* inventory = static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);
    const auto* items = inventory->f_items.arr;
    for (uint32_t i = 0, count = items->len; i < count; ++i) {
        auto* item = static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        if (item->f_timers.arr->len) item->fn__tickTimers(&delta, 1);
        const auto* gems = item->f_gems.arr;
        for (uint32_t j = 0, sockets = gems->len; j < sockets; ++j) {
            const auto& slot = gems->data[j];
            if (slot.kind == gd::GdVal::Kind::Obj && slot.obj) {
                auto* gem = static_cast<Gd__gd_core__CoreItem*>(slot.obj);
                if (gem->f_timers.arr->len) gem->fn__tickTimers(&delta, 1);
            }
        }
    }
    return gd::GdVal::null();
}
"""


def main():
    core = SHARDS.parents[2] / "gd_core"
    combat = (core / "CoreCombat.gd").read_text("utf8")
    assert combat.count("_tickCharacterTimers(") == 3
    assert all(f"\t_tickCharacterTimers({side}, delta)\n" in combat for side in ("opponent", "player"))
    assert "\tcharacter.tickPhysicsTimers(delta)\n\tcharacter.tickBuffs(delta)\n" in combat
    assert "func getItems() -> Array:\n\treturn items\n" in (core / "CoreGrid.gd").read_text("utf8")
    item = (core / "CoreItem.gd").read_text("utf8")
    assert "func _tickTimers(delta: float) -> void :\n\tfor t in timers:\n\t\tt.tick(delta)" in item
    assert "\t_tickTimers(delta)\n\tfor gem in gems:\n\t\tif gem != null:\n\t\t\tgem._tickTimers(delta)" in item
    entries = {p.stem for p in (SHARDS.parent / "hdrs").glob("*.hpp")
               if re.search(r"\bfn_(?:tickTimersPass|_tickTimers)\s*\(", p.read_text("utf8"))}
    assert entries == {"Gd__gd_core__CoreItem"}, entries

    source, = (p for p in SHARDS.glob("*.cpp") if ENTRY in p.read_text("utf8"))
    text = source.read_text("utf8")
    start = text.index(ENTRY)
    end = text.index("\n}\n", start) + 3
    previous = text[start:end]
    assert previous.count("gd::call_method") == 4 and previous.count("gd::gd_iter_seq") == 1
    text = text[:start] + METHOD + text[end:]
    for name in ("CoreCharacter", "CoreGrid", "CoreItem"):
        header = f'#include "../hdrs/Gd__gd_core__{name}.hpp"\n'
        if header not in text:
            text = text.replace("\n#include ", "\n" + header + "#include ", 1)
    target = Path(sys.argv[1]) if len(sys.argv) > 1 else source
    target.write_text(text, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

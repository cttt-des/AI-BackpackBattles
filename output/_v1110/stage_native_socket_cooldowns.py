"""Advance socketed gems after their host in the native physics node order."""
from optimize_native_cooldowns import FUNCTION, SHARDS, SIM


def main():
    sources = [root / "gd_core/CoreCombat.gd" for root in (SIM, SIM / "native_sim_cpp")]
    anchor = "\t\titem.physicsTick(delta)\n"
    replacement = anchor + "\t\tfor gem in item.gems:\n\t\t\tif gem != null:\n\t\t\t\tgem.physicsTick(delta)\n"
    updated = {}
    for path in sources:
        script = path.read_text("utf8")
        assert script.count(anchor) == 2 and replacement not in script, path
        updated[path] = script.replace(anchor, replacement)

    # Keep the already lowered native loop. Gem physicsTick is the same
    # inherited method as the host callback. Nil entries are unused sockets.
    path, = [p for p in SHARDS.glob("*.cpp") if FUNCTION in p.read_text("utf8")]
    source = path.read_text("utf8")
    anchor = "            if (gd::gd_truth(item->f__cooldown_active)) item->fn_physicsTick(&lv_delta, 1);\n"
    assert source.count(anchor) == 2, "Run the native cooldown lowering first"
    replacement = anchor + """            const auto& gems = item->f_gems;
            if (gems.kind == gd::GdVal::Kind::Arr && gems.arr) {
                for (uint32_t i = 0; i < gems.arr->len; ++i) {
                    const auto& value = gems.arr->data[i];
                    if (value.kind == gd::GdVal::Kind::Obj && value.obj) {
                        auto* gem = static_cast<Gd__gd_core__CoreItem*>(value.obj);
                        if (gd::gd_truth(gem->f__cooldown_active)) gem->fn_physicsTick(&lv_delta, 1);
                    }
                }
            }
"""
    assert replacement not in source
    updated[path] = source.replace(anchor, replacement)
    for path, text in updated.items():
        path.write_text(text, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

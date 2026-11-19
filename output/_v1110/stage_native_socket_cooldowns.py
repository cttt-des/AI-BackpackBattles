"""Advance socketed gems after their host in the native physics node order."""
from optimize_native_cooldowns import SIM


def main():
    sources = [root / "gd_core/CoreCombat.gd" for root in (SIM, SIM / "native_sim_cpp")]
    anchor = "\t\titem.physicsTick(delta)\n"
    replacement = anchor + "\t\tfor gem in item.gems:\n\t\t\tif gem != null:\n\t\t\t\tgem.physicsTick(delta)\n"
    updated = {}
    for path in sources:
        script = path.read_text("utf8")
        assert script.count(anchor) == 2 and replacement not in script, path
        updated[path] = script.replace(anchor, replacement)

    for path, text in updated.items():
        path.write_text(text, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

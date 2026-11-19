"""Lower the C++ inventory cooldown loop to the concrete CoreItem entry."""
from pathlib import Path
import re


SIM = Path(__file__).resolve().parent / "sim_native"
SHARDS = SIM / "native_sim_cpp/native_sim/gen/shards"
FUNCTION = "gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick("
CALL = re.compile(
    r"(?P<indent> +)\(void\)\(\[&\]\(\) \{ gd::GdVal _ca\[\] = \{lv_delta\}; "
    r"return gd::call_method\(gd_ctx, (?P<value>lv_item|lv_gem), SYM_GEN_physicsTick_\d+, _ca, 1\); \}\)\(\);"
)


def lower_call(match):
    indent, value = match.group("indent", "value")
    name = "cooldown_" + value.removeprefix("lv_")
    return (f"{indent}auto* {name} = static_cast<Gd__gd_core__CoreItem*>({value}.obj);\n"
            f"{indent}if (gd::gd_truth({name}->f__cooldown_active)) {name}->fn_physicsTick(&lv_delta, 1);")


def main():
    # The inventory holds only CoreItem-derived nodes. No item script may
    # override the entry we devirtualize or add work before the active check.
    entry_classes = {path.stem for path in (SHARDS.parent / "hdrs").glob("*.hpp")
                     if re.search(r"\bfn_physicsTick\s*\(", path.read_text("utf8"))}
    assert entry_classes == {"Gd__gd_core__CoreCombat", "Gd__gd_core__CoreItem"}, entry_classes
    item = (SIM / "gd_core/CoreItem.gd").read_text("utf8")
    start = item.index("func physicsTick(")
    first = next(line.strip() for line in item[start:].splitlines()[1:]
                 if line.strip() and not line.lstrip().startswith("#"))
    assert first == "if not _cooldown_active:"
    candidates = [path for path in SHARDS.glob("*.cpp") if FUNCTION in path.read_text("utf8")]
    assert len(candidates) == 1
    path, = candidates
    source = path.read_text("utf8")
    left = source.index(FUNCTION)
    right = source.index("\ngd::GdVal Gd__gd_core__CoreCombat::", left + 1)
    combat = (SIM / "gd_core/CoreCombat.gd").read_text("utf8")
    body, changes = CALL.subn(lower_call, source[left:right])
    gem_loops = combat.count("gem.physicsTick(delta)")
    assert changes == combat.count("item.physicsTick(delta)") + gem_loops, "The generated loop changed"
    body, changes = re.subn(r"gd::gd_iter_seq\(gd_ctx.arena, gd::get_prop\(gd_ctx, lv_item, SYM_GEN_gems_\d+\)\)",
                            "cooldown_item->f_gems", body)
    assert changes == gem_loops, "The generated gem iterator changed"
    source = source[:left] + body + source[right:]
    header = '#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'
    if header not in source:
        source = source.replace("\n#include ", "\n" + header + "#include ", 1)
    path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

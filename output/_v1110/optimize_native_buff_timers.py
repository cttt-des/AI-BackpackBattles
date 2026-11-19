"""Traverse the C++ character's fixed live buffs in insertion order."""
from pathlib import Path
import re
import sys

from optimize_native_cooldowns import SHARDS


ENTRY = "gd::GdVal Gd__gd_core__CoreCharacter::fn_tickBuffs("


def main():
    core = SHARDS.parents[2] / "gd_core"
    character = (core / "CoreCharacter.gd").read_text("utf8")
    assert len(re.findall(r"(?m)^\s*buffs\[.+?\]\s*=(?!=)", character)) == 1
    assert "\tfor buffType in buffs:\n\t\tbuffs[buffType]._tick(delta)" in character
    buff = (core / "CoreBuff.gd").read_text("utf8")
    assert "func _tick(delta: float) -> void:\n\tif not _timer_active " in buff
    entries = {p.stem for p in (SHARDS.parent / "hdrs").glob("*.hpp")
               if re.search(r"\bfn__tick\s*\(", p.read_text("utf8"))}
    assert entries == {"Gd__gd_core__CoreBuff"}, entries

    source, = (p for p in SHARDS.glob("*.cpp") if ENTRY in p.read_text("utf8"))
    text = source.read_text("utf8")
    start = text.index(ENTRY)
    end = text.index("\ngd::GdVal Gd__gd_core__CoreCharacter::", start + len(ENTRY))
    method = text[start:end]
    assert method.count("gd::gd_iter_seq") == method.count("gd::get_index") == 1
    updated = """gd::GdVal Gd__gd_core__CoreCharacter::fn_tickBuffs(const gd::GdVal* args, int argc) {
    const auto delta = gd::gd_coerce_float(argc > 0 ? args[0] : gd::GdVal::null());
    const auto* buffs = this->f_buffs.dict;
    const auto* entries = buffs->entries;
    for (uint32_t i = 0, count = buffs->len; i < count; ++i) {
        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        if (gd::gd_truth(buff->f__timer_active)) buff->fn__tick(&delta, 1);
    }
    return gd::GdVal::null();
}
"""
    text = text[:start] + updated + text[end:]
    header = '#include "../hdrs/Gd__gd_core__CoreBuff.hpp"\n'
    if header not in text:
        text = text.replace("\n#include ", "\n" + header + "#include ", 1)
    target = Path(sys.argv[1]) if len(sys.argv) > 1 else source
    target.write_text(text, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()

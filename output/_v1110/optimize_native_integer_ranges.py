"""Avoid materializing three integer ranges in Buff gain while retaining snapshot lengths."""
import argparse
import hashlib
from pathlib import Path

from optimize_native_serial_paths import method_body

METHOD_HASH = "06caa727976b8903fa12ccd0c5f9bb5e1b2e5ca935aa3d36b1d7abb758d6962c"
ITERATOR_HASH = "5abe43157825fcacfa38306d35a855f87f46c81d460381f82372feeaac6079d9"
SITES = ((330, 331, 332, 16), (333, 334, 335, 16), (336, 337, 338, 20))


def blocks(site, expression="lv_amount"):
    value, array, index, spaces = site
    indent = " " * spaces
    lines = [
        f"gd::GdVal _t{value} = gd::gd_iter_seq(gd_ctx.arena, {expression});",
        f"gd::GdArr* _t{array} = (_t{value}.kind == gd::GdVal::Kind::Arr) ? _t{value}.arr : nullptr;",
        f"uint32_t _len__t{index} = _t{array} ? _t{array}->len : 0u;",
        f"for (uint32_t _t{index} = 0; _t{index} < _len__t{index}; ++_t{index}) {{",
        f"    gd::GdVal lv_i = _t{array}->data[_t{index}];",
    ]
    old = "".join(indent + line + "\n" for line in lines)
    new_lines = [
        f"const gd::GdVal integer_source_t{value} = {expression};",
        f"const bool integer_range_t{value} = integer_source_t{value}.kind == gd::GdVal::Kind::Int &&",
        f"    integer_source_t{value}.i <= 4294967295LL;",
        f"gd::GdVal _t{value} = integer_range_t{value} ? gd::GdVal::null() :",
        f"    gd::gd_iter_seq(gd_ctx.arena, integer_source_t{value});",
        lines[1],
        f"uint32_t _len__t{index} = integer_range_t{value} ?",
        f"    (integer_source_t{value}.i > 0 ? static_cast<uint32_t>(integer_source_t{value}.i) : 0u) :",
        f"    (_t{array} ? _t{array}->len : 0u);",
        lines[3],
        f"    gd::GdVal lv_i = integer_range_t{value} ? gd::GdVal::from_int(static_cast<int64_t>(_t{index})) : _t{array}->data[_t{index}];",
    ]
    return old, "".join(indent + line + "\n" for line in new_lines)


def original(native):
    runtime = (native / "gd_rt.cpp").read_text("utf8")
    begin = runtime.index("GdVal gd_iter_seq(")
    end = runtime.index("// ─", begin)
    if hashlib.sha256(runtime[begin:end].encode()).hexdigest() != ITERATOR_HASH:
        raise ValueError("The integer iteration semantics changed")
    path = native / "gen/shards/shard_00.cpp"
    source = path.read_text("utf8")
    method = method_body(source, "CoreBuff", "gainTemporary")
    body = method[0]
    for site in SITES:
        old, new = blocks(site)
        if new in body:
            body = body.replace(new, old, 1)
    if hashlib.sha256(body.encode()).hexdigest() != METHOD_HASH:
        raise ValueError("The Buff gain method changed")
    for site in SITES:
        old, _ = blocks(site)
        if body.count(old) != 1:
            raise ValueError("An integer range prefix changed")
    return path, source, method, body


def optimize(native):
    path, source, method, body = original(native)
    for site in SITES:
        old, new = blocks(site)
        body = body.replace(old, new, 1)
    source = source[:method.start()] + body + source[method.end():]
    path.write_text(source, encoding="utf8", newline="\n")
    print("Removed three Buff integer range arrays; retained snapshot lengths and noninteger fallback", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

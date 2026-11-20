"""Apply isolated serial performance passes to generated simulator code."""
import argparse
from collections import Counter
from pathlib import Path
import re


ENUM_MEMBERS = re.compile(r'^static const gd::GdEnum::KV (\w+)\[\] = \{\{(.*)\}\};$', re.M)
ENUM_INITIALIZER = re.compile(r'^static const gd::GdEnum (\w+) = \{"\w+", (\w+), (\d+)u\};$', re.M)
STATIC_ACCESSOR = re.compile(r"^gd::GdVal (Gd__\w+)::get_static_const_or_enum\([^\n]*\n(.*?)^\}", re.M | re.S)
ENUM_RETURN = re.compile(r"case (\w+): return gd::GdVal::from_enum\(&(\w+)\);")
ENUM_READ = re.compile(
    r"gd::get_prop\(gd_ctx, (Gd__\w+)::get_static_const_or_enum\(gd_ctx, (\w+)\), (\w+)\)"
)
QUEUE_METHODS = {
    "flushIdleFrameCalls": "_idle_frame_calls",
    "_step_native_delays": "_timed",
    "tickMotion": "_motion_queue",
}


def fold_enum_reads(generated, sources):
    symbols = dict(re.findall(r'gd::register_sym\((\w+), "(\w+)"\)',
                              (generated / "sym_ids.cpp").read_text("utf8")))
    enums, accessors = {}, {}
    for source in sources.values():
        members = {}
        for array, entries in ENUM_MEMBERS.findall(source):
            parsed = re.fullmatch(r'"\w+", -?\d+LL(?:\}, \{"\w+", -?\d+LL)*', entries)
            if parsed:
                pairs = re.findall(r'"(\w+)", (-?\d+)LL', entries)
                if len(dict(pairs)) == len(pairs):
                    members[array] = dict(pairs)
        for enum, array, count in ENUM_INITIALIZER.findall(source):
            if array in members and len(members[array]) == int(count):
                enums[enum] = members[array]
        for owner, accessor in STATIC_ACCESSOR.findall(source):
            switch = re.match(r"    switch \(prop\) \{\n(.*?)^    \}", accessor, re.M | re.S)
            if not switch:
                continue
            for prop, enum in ENUM_RETURN.findall(switch[1]):
                accessors[owner, prop] = enum

    counts = Counter()

    def fold(match):
        owner, prop, member = match.groups()
        value = enums.get(accessors.get((owner, prop)), {}).get(symbols.get(member))
        if value is None:
            return match[0]
        counts[owner, symbols.get(prop, prop)] += 1
        return f"gd::GdVal::from_int({value}LL)"

    for path, source in sources.items():
        sources[path] = ENUM_READ.sub(fold, source)
    return counts


def patch_queues(source, instrument=False):
    for index, (method, field) in enumerate(QUEUE_METHODS.items()):
        match = method_body(source, "CoreContext", method)
        body = match[1]
        if method == "flushIdleFrameCalls":
            anchor = f"    gd::GdVal lv_batch = this->f_{field};"
            if f"this->f_{field} = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {{}}));" not in body:
                raise ValueError("Unexpected idle callback snapshot")
        else:
            anchor = f"    gd::GdVal lv_limit = gd::call_method(gd_ctx, this->f_{field}, gd::SYM_size, nullptr, 0);"
        if body.count(anchor) != 1:
            raise ValueError(f"Unexpected queue access in {method}")
        code = (f"    const auto& queue = this->f_{field};\n"
                "    const bool queue_empty = queue.kind == gd::GdVal::Kind::Arr && queue.arr && queue.arr->len == 0;\n")
        if instrument:
            code += f"    gd_serial_probe_queue({index}, queue_empty);\n"
        else:
            code += "    if (queue_empty) return gd::GdVal::null();\n"
        changed = body.replace(anchor, code + anchor)
        source = source[:match.start(1)] + changed + source[match.end(1):]
    if instrument:
        return "void gd_serial_probe_queue(unsigned, bool);\n" + source
    return source


def check_queue_owners(sources, context):
    fields = "|".join(QUEUE_METHODS.values())
    reference = re.compile(rf"\b(?:f_(?:{fields})|SYM_GEN_(?:{fields})_\d+)\b")
    for path, source in sources.items():
        if path != context and reference.search(source):
            raise ValueError(f"A different generated shard accesses a CoreContext queue: {path}")
    owner = None
    for line in sources[context].splitlines():
        if match := re.match(r"^[\w: *&]* (Gd__\w+)::\w+\(", line):
            owner = match[1]
        if reference.search(line) and owner != "Gd__gd_core__CoreContext":
            raise ValueError(f"Unexpected CoreContext queue access by {owner}")


def method_body(source, owner, method):
    match = re.search(rf"^gd::GdVal Gd__gd_core__{owner}::fn_{method}\([^\n]*\n(.*?)^\}}\n",
                      source, re.M | re.S)
    if not match:
        raise ValueError(f"Missing {owner}.{method}")
    return match


def defer_item_diagnostics(source, rng_source):
    rng = method_body(rng_source, "CoreRng", "trace_diag")[1]
    trace_guard = ("if (gd::gd_truth((gd::gd_truth(this->f_oracle_trace) ? gd::GdVal::from_bool("
                   "gd::gd_truth(this->f__stacktrace)) : gd::GdVal::from_bool(false)))) {")
    if trace_guard not in rng or len(rng.splitlines()) != 9:
        raise ValueError("Unexpected diagnostic trace predicate")
    receiver = "gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)"
    speed = "gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0)"
    for method in ("trigger", "doCooldownEffect"):
        match = method_body(source, "CoreItem", method)
        lines = match[1].splitlines(keepends=True)
        line = lines[1]
        dispatch = f"gd::call_method(gd_ctx, {receiver}, SYM_GEN_trace_diag_1741, _ca, 4)"
        calls = set(re.findall(r"gd::call_method\([^;]+?(?=;|\})", line))
        if calls != ({dispatch, speed} if method == "trigger" else {dispatch}):
            raise ValueError(f"Unexpected diagnostic arguments in {method}")
        lines[1] = (
            f"    const gd::GdVal trace_rng = {receiver};\n"
            "    if (gd::gd_truth(gd::get_prop(gd_ctx, trace_rng, SYM_GEN_oracle_trace_1729)) &&\n"
            "        gd::gd_truth(gd::get_prop(gd_ctx, trace_rng, SYM_GEN__stacktrace_1731))) {\n"
            "    " + line + "    }\n"
        )
        if method == "trigger":
            # Keep the existing dynamic getter call even when trace output is disabled.
            lines[1] = lines[1].removesuffix("\n") + f" else {{\n        (void){speed};\n    }}\n"
        source = source[:match.start(1)] + "".join(lines) + source[match.end(1):]
    return source


def lower_buff_dispatch(source, headers):
    for header in headers.glob("*.hpp"):
        if re.search(r"^(?:struct|class) \w+\s*:\s*public Gd__gd_core__CoreBuff\b", header.read_text("utf8"), re.M):
            raise ValueError(f"CoreBuff has a generated subclass in {header}")
    dispatch = "case SYM_GEN_gainTemporary_1031: out = fn_gainTemporary(args, argc); return true;"
    if source.count(dispatch) != 1:
        raise ValueError("Unexpected CoreBuff dispatch target")
    match = method_body(source, "CoreBuff", "gainStacks")
    old = "gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainTemporary_1031, _ca, 5)"
    if match[1].count(old) != 1:
        raise ValueError("Unexpected Buff self-call")
    body = match[1].replace(old, "this->fn_gainTemporary(_ca, 5)")
    return source[:match.start(1)] + body + source[match.end(1):]


def optimize(native, mode):
    generated = native / "gen"
    sources = {path: path.read_text("utf8") for path in sorted((generated / "shards").glob("*.cpp"))}
    if mode == "enums":
        counts = fold_enum_reads(generated, sources)
        if not counts:
            raise ValueError("No proven enum reads found")
        print(f"Folded {counts.total()} enum reads. Most common: {counts.most_common(8)}")
    if mode in ("queues", "probe"):
        path = generated / "shards/shard_07.cpp"
        check_queue_owners(sources, path)
        sources[path] = patch_queues(sources[path], instrument=mode == "probe")
    if mode in ("diagnostics", "buff"):
        path = generated / "shards/shard_00.cpp"
        if mode == "diagnostics":
            sources[path] = defer_item_diagnostics(sources[path], sources[generated / "shards/shard_03.cpp"])
        else:
            sources[path] = lower_buff_dispatch(sources[path], generated / "hdrs")
    for path, source in sources.items():
        if path.read_text("utf8") != source:
            path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--part", choices=("enums", "queues", "probe", "diagnostics", "buff"), required=True)
    args = parser.parse_args()
    optimize(args.native, args.part)

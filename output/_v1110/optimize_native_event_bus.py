"""Lower native event-bus dispatch while preserving the callback and trace paths."""
import argparse
import hashlib
from pathlib import Path
import re


OWNER = "Gd__gd_core__CoreEventBus"
BODIES = {
    "emitSignal": "28463c791b03efdeb87fe09bb70344ac4f682b3c2025388f255c6d359805ec7a",
    "emitEvent": "5bf56fca3130ebc5baabe067a52a1b72b6f535d2c3bbb9307fff685077135bb5",
    "logEvent": "7da6c35656212f8c63f776fb6d875e450f2157127533097602a97a280758d2f6",
    "emitAndLog": "358aa19741f1d05bfcc3c591e758026b0c1c76e6d6b8f4907de2b89a1fa371ae",
}
DIRECT = {
    "SYM_GEN_emitEvent_1593": "emitEvent",
    "SYM_GEN_queueSignal_1590": "queueSignal",
    "SYM_GEN_emitAndLog_1594": "emitAndLog",
    "SYM_GEN_getEmissionID_1596": "getEmissionID",
}
MODE = "gd::get_prop(gd_ctx, Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd_ctx, SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)"
LOGGING_ENUM = '_ekv_Gd__gd_core__CoreEventBus_LoggingMode[] = {{"None", 0LL}, {"Instant", 1LL}, {"Delayed", 2LL}};'

SIGNAL_LOOKUP = """    if (lv_emitter.is_null()) return gd::GdVal::null();
    gd::GdVal lv_signalID;
    if (this->f_signalIDs.kind == gd::GdVal::Kind::Dict && this->f_signalIDs.dict) {
        const auto* signals = this->f_signalIDs.dict;
        const auto index = signals->find_index(lv_signalName);
        if (index < 0) return gd::GdVal::null();
        lv_signalID = signals->entries[index].val;
    } else {
        if (!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))) return gd::GdVal::null();
        lv_signalID = gd::get_index(gd_ctx, this->f_signalIDs, lv_signalName);
    }
"""

LIST_LOOKUP = """    const auto bus_trace_enabled = [&] {
        const auto rng = gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406);
        return gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN_oracle_trace_1729))
            && gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN__stacktrace_1731));
    };
    gd::GdVal lv__bus_list;
    if (this->f_connections.kind == gd::GdVal::Kind::Dict && this->f_connections.dict) {
        const auto* connections = this->f_connections.dict;
        const auto index = connections->find_index(lv_emissionID);
        if (index < 0) {
            if (!bus_trace_enabled()) return gd::GdVal::null();
            lv__bus_list = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        } else {
            lv__bus_list = connections->entries[index].val;
            if (lv__bus_list.kind == gd::GdVal::Kind::Arr && lv__bus_list.arr
                    && lv__bus_list.arr->len == 0 && !bus_trace_enabled()) return gd::GdVal::null();
        }
    } else {
        @FALLBACK@
    }
"""


def lower_body(body, method):
    for symbol, name in DIRECT.items():
        body = re.sub(rf"gd::call_method\(gd_ctx, gd::GdVal::from_obj\(this\), {symbol}, _ca, (\d+)\)",
                      rf"this->fn_{name}(_ca, \1)", body)
    body = body.replace(MODE, "gd::GdVal::from_int(2)")
    if method == "emitAndLog":
        start = body.index("    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_emitter,")
        end = body.index("    gd::GdVal lv_emissionID", start)
        body = body[:start] + SIGNAL_LOOKUP + body[end:]
        start = body.index("    gd::GdVal lv__bus_list")
        end = body.index("\n", start) + 1
        fallback = body[start:end].strip().removeprefix("gd::GdVal ")
        body = body[:start] + LIST_LOOKUP.replace("@FALLBACK@", fallback) + body[end:]
    return body


def optimize(native):
    generated = native / "gen"
    path = generated / "shards/shard_12.cpp"
    source = path.read_text("utf8")
    if LOGGING_ENUM not in source:
        raise ValueError("Unexpected event-bus logging mode enum")
    headers = {header.stem: header.read_text("utf8") for header in (generated / "hdrs").glob("*.hpp")}
    for symbol, name in DIRECT.items():
        declaration = re.compile(rf"\bfn_{name}\(")
        owners = {owner for owner, body in headers.items() if declaration.search(body)}
        if owners != {OWNER} or f"case {symbol}: out = fn_{name}(args, argc); return true;" not in source:
            raise ValueError(f"Unexpected dispatch for {name}")
    if any(re.search(r"\bfn_has_method\(", body) for body in headers.values()):
        raise ValueError("Event-bus diagnostic lookup may invoke a user method")
    for name, expected_hash in BODIES.items():
        match = re.search(rf"^gd::GdVal {OWNER}::fn_{name}\([^\n]*\n.*?^\}}\n", source, re.M | re.S)
        checked = match[0] if match else ""
        if name == "emitAndLog":
            fixed = "for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {"
            original = "for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {"
            if checked.count(fixed) != 1:
                raise ValueError("EventBus requires the Godot live-listener generator")
            checked = checked.replace(fixed, original, 1)
        if not match or hashlib.sha256(checked.encode()).hexdigest() != expected_hash:
            raise ValueError(f"Unexpected generated body for {OWNER}::{name}")
        source = source[:match.start()] + lower_body(match[0], name) + source[match.end():]
    path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

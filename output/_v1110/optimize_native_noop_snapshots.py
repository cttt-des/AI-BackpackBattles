"""Omit event snapshot preparation only for the final native hooks' empty implementation."""
import argparse
import hashlib
from pathlib import Path
import re

from optimize_native_serial_paths import method_body


NAME = "gd_native_character_snapshots_are_noop"
HELPER = '''
bool gd_native_character_snapshots_are_noop(const gd::GdVal& context) {
    if (g_syms.logEvent == SYM_GEN_snapshotCharacterStat_1387) return false;
    if (context.kind != gd::GdVal::Kind::Obj || !context.obj ||
            &typeid(*context.obj) != &typeid(Gd__gd_core__CoreContext)) return false;
    const auto& hooks = static_cast<Gd__gd_core__CoreContext*>(context.obj)->f_hooks;
    return hooks.kind == gd::GdVal::Kind::Obj && hooks.obj &&
        &typeid(*hooks.obj) == &typeid(NativeBattleHooks);
}
'''
GUARD = "    if (!gd_native_character_snapshots_are_noop(this->f__ctx)) {\n"
ORIGINAL_HASH = "5bb97e842c3913fdffb7e9a20ab21335c2a77b6ece1d5577481aa9a1b8b94287"


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


def optimize(native):
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    begin = source.index("struct NativeBattleHooks final")
    end = source.index("// ─────────────────────────── Helper: Build CoreItemData", begin)
    dispatch = re.search(r"^    bool call_method\([^\n]*\n.*?^    \}\n", source[begin:end], re.M | re.S)
    if not dispatch or digest(dispatch[0]) != "11e4cbd3a5e86fac1beb230a77cd401d3af3fca4f328d2ff7a1f07bed2138ec7":
        raise ValueError("The native hooks dispatch implementation changed")
    hooks = (native / "gen/shards/shard_14.cpp").read_text("utf8")
    snapshot = method_body(hooks, "CoreHooks", "snapshotCharacterStat")
    if digest(snapshot[0]) != "04e5b148fd226c9596b49141958a516fed3d46e57b504825a9dc520f9c89bc04":
        raise ValueError("The native character snapshot is no longer the verified empty method")
    context = (native / "gen/shards/shard_07.cpp").read_text("utf8")
    for symbol, field in (("SYM_GEN_player_1302", "player"), ("SYM_GEN_opponent_75", "opponent"),
                          ("SYM_GEN_hooks_1409", "hooks")):
        if f"case {symbol}: out = this->f_{field}; return true;" not in context:
            raise ValueError(f"The context getter for {field} changed")
    if source.count(HELPER) == 1:
        pass
    elif NAME in source:
        raise ValueError("A different native snapshot predicate is already installed")
    else:
        source = '#include <typeinfo>\n' + source + HELPER

    path = native / "gen/shards/shard_05.cpp"
    generated = path.read_text("utf8")
    event = method_body(generated, "CoreCombatLog", "createEvent")
    body = event[0]
    if GUARD in body:
        if digest(body.replace(GUARD, "    {\n", 1)) != ORIGINAL_HASH:
            raise ValueError("The guarded event snapshot code changed")
    else:
        if digest(body) != ORIGINAL_HASH:
            raise ValueError("The event creation method changed")
        anchor = "    {\n        gd::GdVal _t957 = gd::gd_iter_seq"
        if body.count(anchor) != 1:
            raise ValueError("Expected one character snapshot loop")
        lowered = body.replace(anchor, GUARD + "        gd::GdVal _t957 = gd::gd_iter_seq", 1)
        generated = generated[:event.start()] + lowered + generated[event.end():]
    declaration = "extern bool gd_native_character_snapshots_are_noop(const gd::GdVal& context);\n"
    if declaration not in generated:
        generated = '#include "../../gd_rt.hpp"\n' + declaration + generated
    wrapper.write_text(source, encoding="utf8", newline="\n")
    path.write_text(generated, encoding="utf8", newline="\n")
    print("Guarded event snapshot preparation with exact native context and final-hook RTTI", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

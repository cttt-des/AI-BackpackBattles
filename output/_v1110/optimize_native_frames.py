"""Use concrete C++ receivers in the verified 1.1.10 frame scheduler."""
import argparse
import hashlib
from pathlib import Path
import re


COMBAT = "Gd__gd_core__CoreCombat"
CHARACTER = "Gd__gd_core__CoreCharacter"
CONTEXT = "Gd__gd_core__CoreContext"
GRID = "Gd__gd_core__CoreGrid"

RECEIVERS = {
    "gd::GdVal::from_obj(this)": ("this", COMBAT),
    "this->f_ctx": ("context()", CONTEXT),
    "this->f_opponent": ("opponent()", CHARACTER),
    "this->f_player": ("player()", CHARACTER),
}
TYPED_RECEIVERS = """    // The native battle constructs exact CoreContext and CoreCharacter objects.
    const auto context = [this] { return static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj); };
    const auto opponent = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_opponent.obj); };
    const auto player = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_player.obj); };
"""


def lower_frame(body, dispatch_sources):
    for receiver, (typed, owner) in RECEIVERS.items():
        original = re.escape(receiver)

        def direct_method(match):
            symbol, name, arguments = match.groups()
            forwarding = f"case {symbol}: out = fn_{name}(args, argc); return true;"
            if forwarding not in dispatch_sources[owner]:
                raise ValueError(f"Unexpected {owner} dispatch for {symbol}")
            return f"{typed}->fn_{name}({arguments})"

        body = re.sub(
            rf"gd::call_method\(gd_ctx, {original}, (SYM_GEN_(\w+)_\d+), ((?:_ca|nullptr), \d+)\)",
            direct_method, body,
        )

    def context_property(match):
        symbol, name = match.groups()
        getter = f"case {symbol}: out = this->f_{name}; return true;"
        if getter not in dispatch_sources[CONTEXT]:
            return match[0]
        return f"context()->f_{name}"

    body = re.sub(r"gd::get_prop\(gd_ctx, this->f_ctx, (SYM_GEN_(\w+)_\d+)\)",
                  context_property, body)

    def set_context_property(match):
        symbol, name, expression = match.groups()
        setter = f"case {symbol}: this->f_{name} = val; return true;"
        if setter not in dispatch_sources[CONTEXT]:
            raise ValueError(f"Unexpected context setter for {symbol}")
        return f"context()->f_{name} = {expression};"

    body = re.sub(r"gd::set_prop\(gd_ctx, this->f_ctx, (SYM_GEN_(\w+)_\d+), ([^\n]+)\);",
                  set_context_property, body)

    inventory = r"gd::call_method\(gd_ctx, gd::get_prop\(gd_ctx, this->f_(opponent|player), SYM_GEN_inventory_\d+\), SYM_GEN_getItems_\d+, nullptr, 0\)"
    if not re.search(
        r"::fn_getItems\([^\n]*\n    gd::BattleCtx& gd_ctx = \*this->rt_ctx_;\n    return this->f_items;",
        dispatch_sources[GRID],
    ):
        raise ValueError("Unexpected CoreGrid inventory accessor")
    body = re.sub(inventory, rf"static_cast<{GRID}*>(\1()->f_inventory.obj)->f_items", body)
    body = re.sub(r"gd::gd_truth\(gd::GdVal::from_bool\(gd::gd_ne\(lv_gem, gd::GdVal::null\(\)\)\)\)",
                  "!lv_gem.is_null()", body)
    body = re.sub(r"gd::get_prop\(gd_ctx, this->f_ctx, (SYM_GEN_PHYSICS_DELTA_\d+)\)",
                  rf"{CONTEXT}::get_static_const_or_enum(gd_ctx, \1)", body)
    return body.replace("    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n",
                        "    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n" + TYPED_RECEIVERS, 1)


def optimize(native):
    shards = native / "gen/shards"
    path = shards / "shard_03.cpp"
    source = path.read_text("utf8")
    dispatch_sources = {owner: (shards / shard).read_text("utf8") for owner, shard in (
        (COMBAT, "shard_03.cpp"), (CHARACTER, "shard_02.cpp"),
        (CONTEXT, "shard_07.cpp"), (GRID, "shard_13.cpp"),
    )}
    functions = {
        "physicsTick": "11fc7eb9a75067a3dfee503f1ca4ff0a8fd9d8310d5ae1a0d66d4c05ed9cda2e",
        "stepCharacterIdle": "2d35d644edcc499b288c040d5096c8a753a0f6175f07fe62b92e11583062d5e1",
    }
    for name, expected in functions.items():
        method = re.search(rf"^gd::GdVal {COMBAT}::fn_{name}\([^\n]*\n.*?^\}}\n", source, re.M | re.S)
        if not method or hashlib.sha256(method[0].encode()).hexdigest() != expected:
            raise ValueError(f"Unexpected generated frame body for {name}")
        lower = lower_frame(method[0], dispatch_sources)
        source = source[:method.start()] + lower + source[method.end():]

    # A constant read should use the context's accessor rather than building
    # the static-property dispatcher's thread-local arena each frame.
    old = "gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_PHYSICS_DELTA_1404)"
    new = f"{CONTEXT}::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)"
    accessor = "case SYM_GEN_PHYSICS_DELTA_1404: return gd::GdVal::from_float(0.01666666753590107);"
    if accessor not in dispatch_sources[CONTEXT] or old not in source:
        raise ValueError("Unexpected physics step accessor")
    source = source.replace(old, new)
    context_header = f'#include "../hdrs/{CONTEXT}.hpp"\n'
    if context_header not in source:
        start = source.index("#include ")
        source = source[:start] + context_header + source[start:]
    path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

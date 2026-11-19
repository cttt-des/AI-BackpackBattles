"""Lower immutable generated values and the frame-critical cooldown arithmetic."""
import ast
import re

from optimize_native_cooldowns import SHARDS


CONST_ENUM = re.compile(r'^static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_(\w+)\[\] = \{(.*)\};$', re.M)
ENUM_MEMBER = re.compile(r'\{"(\w+)", (-?\d+)LL\}')
CONST_ACCESS = re.compile(
    r"gd::get_prop\(gd_ctx, gd::get_prop\(gd_ctx, gd::GdVal::from_cls\(&META_Gd__gd_core__CoreConst\), "
    r"(\w+)\), (\w+)\)"
)
LITERAL = re.compile(r'gd::make_str\(gd_ctx\.arena, ("(?:[^"\\]|\\.)*"), (\d+)u\)')
ITEM_TICK = "gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick("


COOLDOWN = """gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(const gd::GdVal* args, int argc) {
    if (!gd::gd_truth(this->f__cooldown_active)) return gd::GdVal::null();
    auto& context = *static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj);
    const auto blocked = this->f__cooldown_blocked_epoch.as_int();
    if (blocked >= 0 && blocked == context.f_timer_pass_epoch.as_int()) return gd::GdVal::null();

    const auto receiver = this->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)
        ? static_cast<Gd__gd_core_items__Gems__Gem*>(this)->fn_character(nullptr, 0)
        : this->f_character_;
    const auto* character = receiver.kind == gd::GdVal::Kind::Obj
        ? static_cast<const Gd__gd_core__CoreCharacter*>(receiver.obj) : nullptr;
    if (character && character->f_stunnedDuration.as_float() > 0.0) return gd::GdVal::null();

    const auto* display = this->f_statDisplayOverrides.arr;
    const auto override = display && display->len > @SPEED@ ? display->data[@SPEED@] : gd::GdVal::null();
    double speed = 1.0;
    const bool uses_override = !override.is_null() && gd::gd_truth(override);
    if (uses_override) {
        speed = override.as_float();
    } else if (gd::gd_truth(this->f_placed) && !this->f_character_.is_null()) {
        if (character) {
            const auto* buffs = character->f_buffs.dict;
            const auto stacks = [&](int64_t type) {
                const auto slot = static_cast<uint32_t>(type - @BLOCK@);
                const auto* entries = buffs->entries;
                if (slot < buffs->len && entries[slot].key.i == type)
                    return static_cast<const Gd__gd_core__CoreBuff*>(entries[slot].val.obj)->f_current.as_int();
                const auto stack = buffs->get(gd::GdVal::from_int(type));
                return stack.kind == gd::GdVal::Kind::Obj && stack.obj
                    ? static_cast<const Gd__gd_core__CoreBuff*>(stack.obj)->f_current.as_int() : int64_t{0};
            };
            const auto bonus = this->f_speedScale.as_float() + static_cast<double>(stacks(@HEAT@) - stacks(@COLD@)) * 0.02;
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);
        } else {
            speed = this->fn_getSpeed(nullptr, 0).as_float();
        }
    }

    const auto delta = argc > 0 ? args[0].as_float() : 0.0;
    const auto left = uses_override && !override.is_num() ? 0.0 : this->f_triggerTime.as_float() - delta * speed;
    this->f_triggerTime = gd::GdVal::from_float(left);
    auto& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(context.f_show_cooldown_progress)) {
        const gd::GdVal progress[] = {gd::GdVal::from_obj(this), gd::GdVal::from_float(1.0 - left / this->f_iterationCooldown.as_float())};
        gd::call_method(gd_ctx, context.f_hooks, @SHOW@, progress, 2);
    }
    if (this->f_triggerTime.as_float() <= 0.0) gd::call_method(gd_ctx, gd::GdVal::from_obj(this), @TRIGGER@, nullptr, 0);
    return gd::GdVal::null();
}
"""


def fold_literals(source):
    indices = {}
    declarations = []

    def use_shared(match):
        text, length = match.groups()
        if "\\x" in text:
            return match[0]
        data = ast.literal_eval(text).encode("ascii")
        assert len(data) == int(length)
        if text not in indices:
            indices[text] = len(declarations)
            digest = 2166136261
            for byte in data:
                digest = ((digest ^ byte) * 16777619) & 0xFFFFFFFF
            declarations.append(f"    {{{text}, {length}u, {digest}u}},")
        return f"&battle_string_literals[{indices[text]}]"

    source = LITERAL.sub(use_shared, source)
    if declarations:
        end = list(re.finditer(r"^#include [^\n]+\n", source, re.M))[-1].end()
        pool = "\nnamespace {\nconstexpr gd::GdStr battle_string_literals[] = {\n"
        source = source[:end] + pool + "\n".join(declarations) + "\n};\n}\n" + source[end:]
    return source


def lower_cooldown(source, enums, symbols):
    core = SHARDS.parents[2] / "gd_core"
    expected = {
        "hasCharacter": {"CoreItem"}, "getSpeed": {"CoreItem"}, "getStackSpeedMods": {"CoreItem"},
        "speed": {"CoreItem"}, "character": {"CoreItem", "Gem"}, "isStunned": {"CoreCharacter"},
        "getStacks": {"CoreCharacter", "CoreBuff"}, "getHeat": {"CoreCharacter"}, "getCold": {"CoreCharacter"},
    }
    headers = [(path.stem.split("__")[-1], path.read_text("utf8"))
               for path in (SHARDS.parent / "hdrs").glob("*.hpp")]
    for method, classes in expected.items():
        pattern = re.compile(rf"\bfn_{method}\(")
        declarations = {name for name, header in headers if pattern.search(header)}
        assert declarations == classes, (method, declarations)
    item = (core / "CoreItem.gd").read_text("utf8")
    char = (core / "CoreCharacter.gd").read_text("utf8")
    buff = (core / "CoreBuff.gd").read_text("utf8")
    assert "return (ch.getHeat() - ch.getCold()) * 0.02" in item
    assert "return placed and character_ != null" in item
    assert "modifiedSpeed = clamp(modifiedSpeed, 0.1, 10.0)" in item
    assert "func speed() -> float:\n\treturn speedScale" in item
    assert "func isStunned() -> bool:\n\treturn stunnedDuration > 0" in char
    assert "for stackType in CoreConst.getStacks():" in char and "buffs[stackType] = buff" in char
    assert "func getStacks():\n\treturn current" in buff
    start = source.index(ITEM_TICK)
    end = source.index("\n}\n", start) + 3
    assert all(token in source[start:end] for token in ("_cooldown_blocked_epoch", "getSpeed_", "isStunned_"))
    rewrite = COOLDOWN.replace("@SPEED@", str(enums["ItemStat"]["Speed"]))
    for k in ("Block", "Heat", "Cold"):
        rewrite = rewrite.replace(f"@{k.upper()}@", str(enums["EventType"][k]))
    for placeholder, name in (("@SHOW@", "showCooldown"), ("@TRIGGER@", "trigger")):
        rewrite = rewrite.replace(placeholder, symbols[name])
    source = source[:start] + rewrite + source[end:]
    for class_path in ("gd_core__CoreBuff", "gd_core__CoreCharacter", "gd_core__CoreContext", "gd_core_items__Gems__Gem"):
        header = f'#include "../hdrs/Gd__{class_path}.hpp"\n'
        if header not in source:
            source = source.replace("\n#include ", "\n" + header + "#include ", 1)
    return source


def main():
    sources = {path: path.read_text("utf8") for path in SHARDS.glob("*.cpp")}
    enums = {name: {member: int(value) for member, value in ENUM_MEMBER.findall(body)}
             for source in sources.values() for name, body in CONST_ENUM.findall(source)}
    symbols = dict(re.findall(r'gd::register_sym\((\w+), "(\w+)"\)',
                              (SHARDS.parent / "sym_ids.cpp").read_text("utf8")))
    names = {name: symbol for symbol, name in symbols.items()}
    folded = 0

    def enum_constant(match):
        nonlocal folded
        enum, member = (symbols.get(symbol) for symbol in match.groups())
        if member in enums.get(enum, {}):
            folded += 1
            return f"gd::GdVal::from_int({enums[enum][member]}LL)"
        return match[0]

    for path, source in sources.items():
        if ITEM_TICK in source:
            source = lower_cooldown(source, enums, names)
        updated = fold_literals(CONST_ACCESS.sub(enum_constant, source))
        if updated != sources[path]:
            path.write_text(updated, encoding="utf8", newline="\n")
    assert folded > 100, folded
    print(f"Folded {folded} CoreConst enum reads and lowered the cooldown loop")


if __name__ == "__main__":
    main()

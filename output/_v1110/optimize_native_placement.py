"""Lower the verified 1.1.10 generated placement path without changing callback order."""
import argparse
import hashlib
from pathlib import Path
import re


ITEM = "Gd__gd_core__CoreItem"

ON_ITEM_ADDED = """gd::GdVal Gd__gd_core__CoreItem::fn_onItemAdded(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const auto item = argc > 0 ? args[0] : gd::GdVal::null();
    constexpr int color_count = 4;
    bool affected[color_count]{};
    // Complete every query before invoking any callback. A callback may change
    // the inventory or affected sets before the next color is committed.
    for (int color = 0; color < color_count; ++color) {
        const gd::GdVal query[] = {item, gd::GdVal::from_int(color)};
        const auto current = gd::get_index(ctx, this->f_currentAffectedItems, query[1]);
        if (!gd::gd_truth(gd::gd_in(item, current))) {
            affected[color] = gd::gd_truth(this->fn_isItemAffected(query, 2));
        }
    }
    for (int color = 0; color < color_count; ++color) {
        if (!affected[color]) continue;
        const gd::GdVal event[] = {item, gd::GdVal::from_int(color)};
        auto current = gd::get_index(ctx, this->f_currentAffectedItems, event[1]);
        gd::set_index(ctx, current, item, gd::GdVal::from_bool(true));
        gd::call_method(ctx, gd::GdVal::from_obj(this), @CALLBACK@, event, 2);
    }
    return gd::GdVal::null();
}
"""

CACHED_CELLS = """gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsInInventory_cached(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const auto color = argc > 0 ? args[0] : gd::GdVal::null();
    const auto cache = this->f_affectedCellsCache;
    if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
        const auto index = cache.dict->find_index(color);
        if (index >= 0) return cache.dict->entries[index].val;
        return gd::GdVal::from_arr(gd::GdArr::from_init(ctx.arena, {}));
    }
    const gd::GdVal query[] = {color, gd::GdVal::from_arr(gd::GdArr::from_init(ctx.arena, {}))};
    return gd::call_method(ctx, cache, gd::SYM_get, query, 2);
}
"""

PREDICATES = {
    "canAffect": "2c783ddcb52cd2d06ff5e30b22b05f15731c70ab9dc1bc44465b9be718f98c81",
    "canAffect_secondary": "b8bfc7ea6243c6e551df0bbf8e02394731335b2f6e5b98ad5a14af1e0bc90bae",
    "canAffect_tertiary": "5346a0a23c0aee716ce706bc735e5439a4f2081cca2f16d048d2035ea9887788",
    "canAffect_lightning": "3bd2813e8e01e6874baa19d402eb6f6b28df53cd1ea579167768f79ec2b01c1a",
}

AFFECTED_QUERY = """gd::GdVal Gd__gd_core__CoreItem::fn_isItemAffected(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const gd::GdVal query[] = {
        argc > 0 ? args[0] : gd::GdVal::null(),
        argc > 1 ? args[1] : gd::GdVal::from_int(0),
    };
    if (gd::gd_truth(gd::call_method(ctx, query[0], @IS_BAG@, nullptr, 0))
            || !gd::gd_truth(this->fn_canAffect_color(query, 2))) {
        return gd::GdVal::from_bool(false);
    }
    const auto tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);
    const auto cells = gd::gd_iter_seq(ctx.arena, gd::get_prop(ctx, query[0], @OCCUPIED@));
    const auto* occupied = cells.kind == gd::GdVal::Kind::Arr ? cells.arr : nullptr;
    for (uint32_t i = 0, count = occupied ? occupied->len : 0; i < count; ++i) {
        if (gd::gd_truth(gd::gd_in(occupied->data[i], tiles))) return gd::GdVal::from_bool(true);
    }
    return gd::GdVal::from_bool(false);
}
"""


def method_definition(source, name, expected_hash):
    pattern = re.compile(rf"^gd::GdVal {ITEM}::fn_{name}\([^\n]*\n.*?^\}}\n", re.M | re.S)
    match = pattern.search(source)
    if not match or hashlib.sha256(match[0].encode()).hexdigest() != expected_hash:
        raise ValueError(f"Unexpected generated body for {ITEM}::{name}")
    return match


def replace_method(source, name, expected_hash, replacement):
    match = method_definition(source, name, expected_hash)
    return source[:match.start()] + replacement + source[match.end():]


def predicate_fast_paths(source, headers):
    if any(re.search(r"\bfn__hasBehaviorMethod\(", body) for name, body in headers.items() if name != ITEM):
        raise ValueError("A subclass overrides the behavior probe")
    method_definition(source, "_hasBehaviorMethod", "68d58dcf7c4d288d7fead2afc6407403b4a231edd94b8cd149e6f583f97efd75")
    literals = re.search(r"constexpr gd::GdStr battle_string_literals\[\] = \{(.*?)^\};", source, re.S | re.M)[1]
    texts = re.findall(r'^    \{("(?:[^"\\]|\\.)*"), \d+u, \d+u\},$', literals, re.M)
    whitelist = re.search(r"case SYM_GEN_SELF_BEHAVIOR_METHODS_\d+: return [^\n]*", source)[0]
    indices = re.findall(r"gd::GdVal::from_str\(&battle_string_literals\[(\d+)\]\)", whitelist)
    allowed = {texts[int(index)] for index in indices}
    if not allowed or any(f'"{name}"' in allowed for name in PREDICATES):
        raise ValueError("An affect predicate appears in SELF_BEHAVIOR_METHODS")

    for name, expected_hash in PREDICATES.items():
        match = method_definition(source, name, expected_hash)
        test = re.search(
            r"if \(gd::gd_truth\(\(\[&\]\(\) \{ gd::GdVal _ca\[\] = "
            r"\{gd::GdVal::from_str\(&battle_string_literals\[(\d+)\]\)\}; return "
            r"gd::call_method\(gd_ctx, gd::GdVal::from_obj\(this\), SYM_GEN__hasBehaviorMethod_\d+, _ca, 1\);",
            match[0],
        )
        if not test or texts[int(test[1])] != f'"{name}"':
            raise ValueError(f"Unexpected fallback probe for {name}")
        line_end = source.index("\n", match.start()) + 1
        # Concrete overrides still receive virtual calls. Only the fallback
        # wrappers can use the whitelist result when no injected behavior exists.
        source = (source[:line_end]
                  + "    if (this->f__behavior.is_null()) return gd::GdVal::from_bool(false);\n"
                  + source[line_end:])
    return source


def single_implementation(headers, method):
    declaration = re.compile(rf"\bfn_{method}\(")
    owners = {name for name, body in headers.items() if declaration.search(body)}
    if owners != {ITEM}:
        raise ValueError(f"Unexpected {method} implementations {sorted(owners)}")


def optimize(native, fast_predicates=False):
    generated = native / "gen"
    shards = generated / "shards"
    constants = (shards / "shard_06.cpp").read_text("utf8")
    colors = re.search(r"_ekv_Gd__gd_core__CoreConst_Affected\[\] = \{([^\n]*)\};", constants)
    expected = [("Primary", "0"), ("Secondary", "1"), ("Tertiary", "2"), ("Lightning", "3")]
    if not colors or re.findall(r'\{"(\w+)", (\d+)LL\}', colors[1]) != expected:
        raise ValueError("Unexpected affected color order")

    headers = {header.stem: header.read_text("utf8") for header in (generated / "hdrs").glob("*.hpp")}
    single_implementation(headers, "isItemAffected")

    path = shards / "shard_00.cpp"
    source = path.read_text("utf8")
    callback = re.search(r"\bSYM_GEN_onAffectedItemAdded_\d+\b", source)[0]
    source = replace_method(
        source, "onItemAdded", "e821f370de631e5977097a066853d21a54ad7166318fcdeb02998391d8ffe09a",
        ON_ITEM_ADDED.replace("@CALLBACK@", callback),
    )
    source = replace_method(
        source, "getAffectedCellsInInventory_cached",
        "098b124f019299faf338cecbfa502f0b2710623773c6681a91d7117177ddfb3c", CACHED_CELLS,
    )
    if fast_predicates:
        for name in ("canAffect_color", "getAffectedCellsInInventory_cached"):
            single_implementation(headers, name)
        query = AFFECTED_QUERY.replace("@IS_BAG@", re.search(r"\bSYM_GEN_isBag_\d+\b", source)[0])
        query = query.replace("@OCCUPIED@", re.search(r"\bSYM_GEN_occupiedCells_\d+\b", source)[0])
        source = replace_method(
            source, "isItemAffected", "7407921b2cc68af31fdf47ad4fe7be7704bb3875883d10956ba16d9467b2a32a", query,
        )
        source = predicate_fast_paths(source, headers)
    path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--fast-predicates", action="store_true")
    args = parser.parse_args()
    optimize(args.native, fast_predicates=args.fast_predicates)

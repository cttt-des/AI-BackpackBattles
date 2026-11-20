"""Avoid allocating absent affected-cell arrays during placement queries."""
import argparse
import hashlib
from pathlib import Path

from optimize_native_placement import single_implementation
from optimize_native_serial_paths import method_body


def optimize(native, fused=False):
    generated = native / 'gen'
    headers = {p.stem: p.read_text('utf8') for p in (generated/'hdrs').glob('*.hpp')}
    single_implementation(headers, 'getAffectedCellsInInventory_cached')
    path = generated/'shards/shard_00.cpp'
    source = path.read_text('utf8')
    match = method_body(source, 'CoreItem', 'isItemAffected')
    if hashlib.sha256(match[0].encode()).hexdigest() != '2c5126e5a585bdb38dd67ed827a45a52e96319e380574e052c059be92ebc00d5':
        raise ValueError('Unexpected affected-item predicate')
    old = '    const auto tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);'
    new = '''    gd::GdVal tiles;
    const auto cache = this->f_affectedCellsCache;
    if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
        const auto index = cache.dict->find_index(query[1]);
        if (index < 0) return gd::GdVal::from_bool(false);
        tiles = cache.dict->entries[index].val;
    } else {
        tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);
    }
    if (tiles.kind == gd::GdVal::Kind::Arr && tiles.arr && tiles.arr->len == 0)
        return gd::GdVal::from_bool(false);'''
    if match[1].count(old) != 1:
        raise ValueError('Unexpected placement query implementation')
    cached = method_body(source, 'CoreItem', 'getAffectedCellsInInventory_cached')[0]
    if hashlib.sha256(cached.encode()).hexdigest() != '2fe1c088aa05f9effa5534c873ef6620fbd01c45ea89f579b4e8305800640868':
        raise ValueError('Unexpected affected-cell cache lookup')
    source = source[:match.start(1)] + match[1].replace(old, new) + source[match.end(1):]
    if fused:
        import re
        bodies = []
        for shard in (generated/'shards').glob('*.cpp'):
            bodies.extend(re.findall(r'^gd::GdVal (Gd__\w+)::fn_isBag\([^\n]*\n(.*?)^\}', shard.read_text('utf8'), re.M | re.S))
        expected = {'Gd__gd_core__CoreItem': 'false', 'Gd__gd_core__Bag': 'true', 'Gd__gd_core_items__Bag': 'true'}
        if len(bodies) != len(expected):
            raise ValueError('Unexpected bag implementations')
        for owner, body in bodies:
            if body.strip() != ('gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n'
                                f'    return gd::GdVal::from_bool({expected[owner]});\n'
                                '    return gd::GdVal::null();'):
                raise ValueError('Bag query has observable effects')
        method = method_body(source, 'CoreItem', 'onItemAdded')
        if hashlib.sha256(method[0].encode()).hexdigest() != '0435e37f1ea4167fc31bdb2ce7d685130b4abb4fed3d7bea4d27a24208dc6f29':
            raise ValueError('Unexpected placement callback implementation')
        body = method[1].replace('    constexpr int color_count = 4;', '''    if (gd::gd_truth(gd::call_method(ctx, item, SYM_GEN_isBag_83, nullptr, 0)))
        return gd::GdVal::null();
    const auto affected_query = [&](const gd::GdVal* query) {
        if (!gd::gd_truth(this->fn_canAffect_color(query, 2))) return false;
        gd::GdVal tiles;
        const auto cache = this->f_affectedCellsCache;
        if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
            const auto index = cache.dict->find_index(query[1]);
            if (index < 0) return false;
            tiles = cache.dict->entries[index].val;
        } else {
            tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);
        }
        if (tiles.kind == gd::GdVal::Kind::Arr && tiles.arr && tiles.arr->len == 0) return false;
        const auto cells = gd::gd_iter_seq(ctx.arena, gd::get_prop(ctx, item, SYM_GEN_occupiedCells_52));
        const auto* occupied = cells.kind == gd::GdVal::Kind::Arr ? cells.arr : nullptr;
        for (uint32_t i = 0, count = occupied ? occupied->len : 0; i < count; ++i) {
            if (gd::gd_truth(gd::gd_in(occupied->data[i], tiles))) return true;
        }
        return false;
    };
    constexpr int color_count = 4;''')
        body = body.replace('gd::gd_truth(this->fn_isItemAffected(query, 2))', 'affected_query(query)')
        source = source[:method.start(1)] + body + source[method.end(1):]
    path.write_text(source, encoding='utf8', newline='\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native', type=Path)
    parser.add_argument('--fused', action='store_true')
    args = parser.parse_args()
    optimize(args.native, fused=args.fused)

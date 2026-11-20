"""Inline array size and empty queries with the original generic fallback."""
import argparse
from pathlib import Path
import re


HELPERS = '''
inline GdVal gd_size(BattleCtx& ctx, const GdVal& receiver) {
    if (receiver.kind == GdVal::Kind::Arr && receiver.arr)
        return GdVal::from_int(receiver.arr->len);
    return call_method(ctx, receiver, SYM_size, nullptr, 0);
}

inline GdVal gd_empty(BattleCtx& ctx, const GdVal& receiver) {
    if (receiver.kind == GdVal::Kind::Arr && receiver.arr)
        return GdVal::from_bool(receiver.arr->len == 0);
    return call_method(ctx, receiver, SYM_empty, nullptr, 0);
}
'''
HOT_SHARDS = {'shard_00', 'shard_02', 'shard_03', 'shard_06', 'shard_07'}


def optimize(native):
    header = native/'gd_rt.hpp'
    source = header.read_text('utf8')
    anchor = 'GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId method, const GdVal* args, int argc);\n'
    installed = HELPERS in source
    if source.count(anchor) != 1 or ('inline GdVal gd_size(' in source and not installed):
        raise ValueError('Unexpected array-query declarations')
    runtime = (native/'gd_rt.cpp').read_text('utf8')
    for implementation in ('case SYM_size: return GdVal::from_int(a->len);',
                           'case SYM_empty: return GdVal::from_bool(a->len == 0);'):
        if implementation not in runtime:
            raise ValueError('Array query semantics changed')
    pattern = re.compile(r'gd::call_method\(gd_ctx, (this->f_\w+|\(?lv_\w+\)?), '
                         r'gd::SYM_(size|empty), nullptr, 0\)')
    updated, total = {}, 0
    for path in (native/'gen/shards').glob('*.cpp'):
        if path.stem not in HOT_SHARDS:
            continue
        text = path.read_text('utf8')
        text, count = pattern.subn(lambda m: f'gd::gd_{m[2]}(gd_ctx, {m[1]})', text)
        if count:
            updated[path] = text
            total += count
    if not total:
        if installed:
            print('Array query helpers are already applied', flush=True)
            return
        raise ValueError('No array query call sites found')
    if not installed:
        header.write_text(source.replace(anchor, anchor+HELPERS), encoding='utf8', newline='\n')
    for path, text in updated.items():
        path.write_text(text, encoding='utf8', newline='\n')
    print(f'Inlined {total} size/empty call sites across {len(updated)} shards', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native', type=Path)
    optimize(parser.parse_args().native)

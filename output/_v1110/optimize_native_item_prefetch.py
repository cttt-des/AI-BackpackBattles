"""Prefetch future item fields without caching values or changing callback order."""
import argparse
import hashlib
from pathlib import Path
from optimize_native_serial_paths import method_body

ORIGINAL_HASH="f48751d83b9e40527fd5350de62d34da54f4aab30dccf3f3aca9011f82f61489"
HELPER='''#include "../../gd_rt.hpp"
#include "../hdrs/Gd__gd_core__CoreItem.hpp"
namespace {
inline void native_prefetch_timer_item(const gd::GdArr* items, uint32_t index,
                                       uint32_t captured_count, const Gd__gd_core__CoreItem* current) {
    constexpr uint32_t distance=2;
    if (captured_count-index <= distance || index+distance >= items->len) return;
    const auto& future=items->data[index+distance];
    if (future.kind != gd::GdVal::Kind::Obj || !future.obj) return;
    const auto current_base=reinterpret_cast<uintptr_t>(static_cast<const gd::GdObj*>(current));
    const auto future_base=reinterpret_cast<uintptr_t>(future.obj);
    // Derive offsets from the valid current item. Never dereference the future object.
    const auto timers_offset=reinterpret_cast<uintptr_t>(&current->f_timers)-current_base;
    const auto gems_offset=reinterpret_cast<uintptr_t>(&current->f_gems)-current_base;
    __builtin_prefetch(reinterpret_cast<const void*>(future_base+timers_offset),0,3);
    __builtin_prefetch(reinterpret_cast<const void*>(future_base+gems_offset),0,3);
}
}
'''
CALL="        native_prefetch_timer_item(items, i, count, item);\n"

def optimize(native):
    path=native/'gen/shards/shard_03.cpp';source=path.read_text('utf8')
    method=method_body(source,'CoreCombat','_tickCharacterTimers')
    body=method[0];original=body.replace(CALL,'',1) if CALL in body else body
    if hashlib.sha256(original.encode()).hexdigest()!=ORIGINAL_HASH:
        raise ValueError('The native character timer traversal changed')
    anchor='        auto* item = static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);\n'
    if original.count(anchor)!=1:raise ValueError('Unexpected item loop')
    body=original.replace(anchor,anchor+CALL,1)
    source=source[:method.start()]+body+source[method.end():]
    if HELPER not in source:
        if 'native_prefetch_timer_item' in source.replace(CALL,''):
            raise ValueError('A different item prefetch helper exists')
        source=HELPER+source
    path.write_text(source,encoding='utf8',newline='\n')
    print('Prefetching timer and gem fields two items ahead; all traversal reads remain live',flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('native',type=Path)
    optimize(parser.parse_args().native)

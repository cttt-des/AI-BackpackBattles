"""Expose constant method slots to callers, keeping lazy resolution and fallback."""
import json
from pathlib import Path
import re
from prototype_native_scalar_builtin_bundle import optimize as previous_bundle

STAGE=Path(__file__).resolve().parent
TOKEN=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|gd::call_method(?=\s*\()')

def optimize(native):
    report=previous_bundle(native)
    path=native/'native_resolved_dispatch.hpp';private=path.read_text('utf8')
    declarations='using NativeResolvedFn = GdVal (*)(GdObj*, const GdVal*, int);\nstruct NativeMethodRow { std::array<NativeResolvedFn,112> methods; };\n'
    assert private.count(declarations)==1
    slot=re.search(r'static constexpr auto native_resolved_slots=\[\] \{.*?    return value; \}\(\);',private,re.S)
    assert slot and slot[0].count('    value[')==112
    header='''#pragma once
#include "gd_rt.hpp"
#include "gen/sym_ids.hpp"
#include <array>
namespace gd {
'''+declarations+slot[0].replace('static constexpr auto','inline constexpr auto',1)+'''
bool native_resolved_row_matches(const GdObj*,const NativeMethodRow*);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_inline_call(BattleCtx& ctx,const GdVal& recv,SymId method,const GdVal* args,int argc) {
    const int slot=method<native_resolved_slots.size()?native_resolved_slots[method]:-1;
    if(slot>=0 && ctx.native_resolved_dispatch && recv.kind==GdVal::Kind::Obj && recv.obj) {
        const NativeMethodRow* row=recv.obj->native_call_row_;
        // Audit before reading the row, just like the original dispatcher.
        if(row && (!ctx.native_resolved_audit || native_resolved_row_matches(recv.obj,row))) {
            const auto function=row->methods[slot];
            if(function) {
                if(ctx.native_resolved_collect)++ctx.native_resolved_counts[0];
                return function(recv.obj,args,argc);
            }
        }
    }
    // No virtual/user call has happened yet; fallback performs it exactly once.
    return gd::call_method(ctx,recv,method,args,argc);
}
} // namespace gd
'''
    assert not (native/'native_inline_dispatch.hpp').exists()
    (native/'native_inline_dispatch.hpp').write_text(header,encoding='utf8',newline='\n')
    private=private.replace(declarations,'',1).replace(slot[0],'',1)
    private=private.replace('#pragma once\n','#pragma once\n#include "native_inline_dispatch.hpp"\n',1)
    anchor='bool try_native_resolved_dispatch('
    assert private.count(anchor)==1
    private=private.replace(anchor,'''bool native_resolved_row_matches(const GdObj* object,const NativeMethodRow* row) {
    return row==native_resolved_exact_row(object);
}
'''+anchor,1)
    path.write_text(private,encoding='utf8',newline='\n')
    sites={}
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        count=0
        def rewrite(match):
            nonlocal count
            if match[0]=='gd::call_method':count+=1;return 'gd::native_inline_call'
            return match[0]
        text=TOKEN.sub(rewrite,path.read_text('utf8'));assert count>0
        text='#include "../../native_inline_dispatch.hpp"\n'+text
        path.write_text(text,encoding='utf8',newline='\n')
        sites[path.relative_to(native).as_posix()]=count
    report.update({'inline_dispatch_sites':sites,'total_inline_dispatch_sites':sum(sites.values()),
        'constant_slot_scope':'Compile-time method IDs can fold method bounds/slot checks at each generated call site',
        'row_definition':'Same112-function row, moved to a shared header; GdObj and BattleCtx layouts unchanged',
        'fast_path':'Already cached exact-type row and supported method, direct original function return; per-site indirect target profiling',
        'fallback':'Original call_method once on uncached/missing/unsupported/non-object/disabled cases; FuncRef untouched',
        'audit':'Exact RTTI row match checked before dereferencing a cached row; mismatch is delegated to the original audit',
        'arithmetic_rng_argument_order':'Original argument expressions, binds, method bodies and floating options unchanged'})
    print('Inlined dispatch wrappers at',sum(sites.values()),'generated call sites; row layout unchanged',flush=True)
    return report

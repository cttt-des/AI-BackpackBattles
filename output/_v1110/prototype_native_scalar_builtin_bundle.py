"""Compose retained scalar/array changes with proven Null and builtin paths."""
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze
from prototype_native_scalar_array_bundle import optimize as scalar_array

STAGE=Path(__file__).resolve().parent

def optimize(native):
    # First reproduce the retained candidate from the whole deployed inventory.
    report=scalar_array(native)
    profile=json.loads((STAGE/'native_perf50/post_dispatch_array_profile/profile_depth64.json').read_bytes())
    proof=analyze(native,profile,limit=0)
    assert proof['generated_classes']==proof['eligible_classes_with_pure_inheritance']==674
    bodies=[]
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        bodies.extend(re.findall(r'^bool Gd__\w+::call_method\([^\n]*\n(.*?)^\}',path.read_text('utf8'),re.M|re.S))
    assert len(bodies)==674
    for name in ('has_method','get_instance_id'):
        assert not any(re.search(r'case (?:gd::)?SYM_'+name+r'\s*:',body) for body in bodies)
        assert not any(re.search(r'\b(?:fn|sf)_'+name+r'\(',body) for body in bodies)
    # Validate the two builtin bodies we reuse verbatim, including argument guards.
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    has='return GdVal::from_bool(argc >= 1 && recv.obj->has_own_method(val_to_sym(args[0])));'
    identity='return GdVal::from_int(static_cast<int64_t>(recv.obj->get_instance_id()));'
    assert runtime.count(has)==runtime.count(identity)==1
    path=native/'native_scalar_equal.hpp';text=path.read_text('utf8')
    old='    return gd::gd_eq(a,b);';assert text.count(old)==1
    text=text.replace(old,'    if(a.kind==GdVal::Kind::Null || b.kind==GdVal::Kind::Null)return false;\n'+old,1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_resolved_dispatch.hpp';text=path.read_text('utf8')
    old='    const int slot=native_resolved_slots[method]; if(slot<0)return false;'
    assert text.count(old)==1
    text=text.replace(old,'''    const int slot=native_resolved_slots[method];
    // FuncRef has no builtin fallback in the original runtime.
    if(slot<0 && !(route==0 && (method==SYM_has_method || method==SYM_get_instance_id)))return false;''',1)
    old='    const auto function=row->methods[slot];';assert text.count(old)==1
    body='''    if(slot<0) {
        // Only exact generated types are proven to have pure, nonmatching dispatch.
        if(row==&native_resolved_empty) {
            if(ctx.native_resolved_collect)++ctx.native_resolved_counts[5];
            return false;
        }
        if(ctx.native_resolved_collect)++ctx.native_resolved_counts[0];
        if(method==SYM_has_method)
            out=GdVal::from_bool(argc >= 1 && object->has_own_method(val_to_sym(args[0])));
        else
            out=GdVal::from_int(static_cast<int64_t>(object->get_instance_id()));
        return true;
    }
'''
    text=text.replace(old,body+old,1)
    path.write_text(text,encoding='utf8',newline='\n')
    report.update({'composed_from_retained_trial':'464add2eef3eba164c16c8db741d8d335e83b99c67b661d9e6a52203d715ae88',
        'null_mismatch':'After same-kind cases, either Null implies original false; other coercion unchanged',
        'builtin_fast_methods':['has_method','get_instance_id'],
        'builtin_source_proof':{'pure_generated_dispatchers_and_parent_fallbacks':len(bodies),'matching_builtin_cases':0},
        'builtin_scope':'Generic object calls only, exact known generated receiver; same original builtin implementation',
        'builtin_fallback':'Custom C++ type or FuncRef route retains original method dispatch, no new FuncRef semantics',
        'coverage_note':'generic_hits now also includes builtin fast calls; audit/collect remain disabled for performance'})
    print('Composed Null mismatch and two builtins;674 pure nonmatching dispatchers proved',flush=True)
    return report

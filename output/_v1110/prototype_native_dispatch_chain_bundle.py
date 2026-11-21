"""Flatten proven generated behavior calls and unbound event callback dispatch."""
import hashlib
import json
from pathlib import Path
from prepare_native_dispatch_chain import prepare
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/static_setup_bundle'
PROBE=STAGE/'native_perf50/dispatch_chain_probe'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'screen_hash_guard.json').read_bytes());extended=json.loads((PROBE/'extended_cases.json').read_bytes())
    assert screen['passed'] and screen['cases']==341604 and extended['passed'] and extended['cases']==310500
    assert sha(STAGE/'test_native_dispatch_chain.cpp')==screen['test_source_sha256']
    design=prepare(native)
    for name,key in [('behavior_helper.hpp','helper'),('callback_helper.hpp','callback')]:
        assert (PROBE/name).read_text('utf8')==design[key]
        assert sha(PROBE/name)==screen['helper_sha256' if key=='helper' else 'callback_sha256']
    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    assert 'native_try_behavior_chain' not in text and 'native_try_flat_funcref' not in text
    text+='\nnamespace gd { bool native_try_behavior_chain(BattleCtx&,GdObj*,const GdVal&,const GdVal&,bool,GdVal&); }\n'+design['callback']
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_resolved_dispatch.hpp'
    text=path.read_text('utf8')+'\n'+design['helper']+'''
namespace gd {
static thread_local uint64_t native_dispatch_chain_counts[4]{};
void native_dispatch_chain_hit(unsigned field){if(field<4)++native_dispatch_chain_counts[field];}
}
extern "C" uint64_t gd_diag_native_dispatch_chain_stat(unsigned field){return field<4?gd::native_dispatch_chain_counts[field]:0;}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp';text=path.read_text('utf8')
    old='''inline gd::GdVal native_event_funcv(gd::BattleCtx& ctx,const gd::GdVal& value,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && argc>=1)
        return value.fr->call_funcv(ctx,args[0]);
    return gd::call_method(ctx,value,gd::SYM_call_funcv,args,argc);
}'''
    new='''inline gd::GdVal native_event_funcv(gd::BattleCtx& ctx,const gd::GdVal& value,const gd::GdVal* args,int argc) {
    if(value.kind==gd::GdVal::Kind::FuncRef && value.fr && argc>=1) {
        gd::GdVal result;
        if(gd::native_try_flat_funcref(ctx,value,args[0],result))return result;
        return value.fr->call_funcv(ctx,args[0]);
    }
    return gd::call_method(ctx,value,gd::SYM_call_funcv,args,argc);
}'''
    assert text.count(old)==1 and text.count('#include "native_inline_dispatch.hpp"')==3
    text=text.replace(old,new,1).replace('#include "native_inline_dispatch.hpp"\n','')
    text=text.replace('#include "gd_rt.hpp"\n','#include "gd_rt.hpp"\n#include "native_inline_dispatch.hpp"\n',1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8')
    for name,original in design['originals'].items():assert text.count(original)==1;text=text.replace(original,design['updates'][name],1)
    path.write_text(text,encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name])
    assert changed==['gen/shards/shard_00.cpp','native_event_kernel.hpp','native_inline_dispatch.hpp','native_resolved_dispatch.hpp']
    result=json.loads((BASE/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=screen['baseline_dll_sha256'],components=['exact-class behavior dispatch for the original nine-method whitelist','flat unbound FuncRef event callback chain'],modified_native_files=changed,
        class_dispatch_and_has_method_source_proofs=674,behavior_names=design['names'],local_differential_cases=341604,
        original_method_table_and_object_context_funcref_layouts_unchanged=True,original_arithmetic_rng_and_target_method_bodies_unchanged=True,
        unknown_uncached_disabled_poison_audited_rows_bound_refs_and_symbol_reregistration_fallbacks=True,
        original_call_counters_preserved_in341604_differentials=True,stored_string_hash_comparison_preserved=True,no_whole_fight_gain_claim=True)
    return result

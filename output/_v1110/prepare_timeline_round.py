"""Prepare the isolated, live-read typed timeline candidate on CEA."""
import json,shutil
from pathlib import Path
from prepare_ordering_correctness import STAGE,REPO,BASE,sha,inventory
from install_ordering_correctness import boundary
ACCEPTED=STAGE/'native_perf50/frame_guard_reuse_bundle'
WORK=STAGE/'native_perf50/architecture_three_bundle/typed_timeline_candidate'
EXPECTED='cea3c1c81a9294e05f0aac3b609ee4e474aa7019a1bf766ad12c22d876fe4b52'
ARCHIVE='710e7602a4ed886432a34f6a8be3c0b7c7a64c01'
TAIL_OLD="""if(write!=limit){const auto end=gd::native_inline_call(b,ctx.f__timed,gd::SYM_size,nullptr,0).as_int();while(read<end){auto q=ctx.f__timed;gd::native_array_set_index(b,q,V::from_int(write++),gd::native_array_index(b,ctx.f__timed,V::from_int(read++)));}const V n=V::from_int(write);gd::native_inline_call(b,ctx.f__timed,gd::SYM_resize,&n,1);}return V::null();"""
TAIL_NEW="""if(write!=limit){const auto end=gd::native_inline_call(b,ctx.f__timed,gd::SYM_size,nullptr,0);V tail_read=V::from_int(read),tail_write=V::from_int(write);while(gd::gd_lt(tail_read,end)){auto q=ctx.f__timed;gd::native_array_set_index(b,q,tail_write,gd::native_array_index(b,ctx.f__timed,tail_read));tail_write=gd::gd_add(b,tail_write,V::from_int(1));tail_read=gd::gd_add(b,tail_read,V::from_int(1));}gd::native_inline_call(b,ctx.f__timed,gd::SYM_resize,&tail_write,1);}return V::null();"""

def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def once(text,old,new):assert text.count(old)==1,old[:100];return text.replace(old,new,1)
def verify_projection(source):
    actual=inventory(source);assert actual==json.loads((WORK/'source_before_build.json').read_bytes())
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert len(old)==715 and len(actual)==716
    assert set(actual)-set(old)=={'native_typed_timeline.hpp'}
    changed=[n for n in old if old[n]!=actual[n]];assert changed==['gen/shards/shard_07.cpp'],changed
    inverse=(source/'gen/shards/shard_07.cpp').read_text('utf8')
    for a,b in reversed(json.loads((WORK/'source_changes.json').read_bytes())):inverse=once(inverse,b,a)
    assert inverse==(ACCEPTED/'bundle_src/gen/shards/shard_07.cpp').read_text('utf8')
    return dict(passed=True,unchanged_files=714,all674_object_headers_unchanged=True,exact_inverse_to_CEA=True)

def main():
    boundary();assert not WORK.exists();assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert inventory(BASE)==old
    WORK.mkdir();src=WORK/'bundle_src'
    for n,digest in old.items():
        target=src/n;target.parent.mkdir(parents=True,exist_ok=True);assert sha(ACCEPTED/'bundle_src'/n)==digest;shutil.copyfile(ACCEPTED/'bundle_src'/n,target)
    probe=(STAGE/'test_timeline_step_resume_probe.cpp').read_text('utf8')
    extra=probe[probe.index('// Every F32 boundary'):probe.index('__attribute__((noinline)) static void typed(Scene& s')]
    # Integer qualification avoids speculative floating comparisons before the
    # original elapsed store, including signaling-NaN/unmasked environments.
    extra=once(extra,'!(c->f__visual_back.f>0)','(std::bit_cast<uint64_t>(c->f__visual_back.f)>>63) || !(std::bit_cast<uint64_t>(c->f__visual_back.f)&0x7fffffffffffffffULL) || ((std::bit_cast<uint64_t>(c->f__visual_back.f)>>52)&2047)==2047')
    extra=once(extra,'c->f__visual_elapsed=V::from_float(f32(c->f__visual_elapsed.f+delta->as_float()));','hit(1);\n    c->f__visual_elapsed=V::from_float(f32(c->f__visual_elapsed.f+delta->as_float()));')
    extra=once(extra,'c->f_elapsed=V::from_float(f32(c->f_elapsed.f+args[1].as_float()));','hit(2);\n    c->f_elapsed=V::from_float(f32(c->f_elapsed.f+args[1].as_float()));')
    delay=(STAGE/'test_delay_resume_probe.cpp').read_text('utf8')
    delay=delay[delay.index('__attribute__((noinline)) static V typed_delay('):delay.index('\nstatic uint64_t signature(')]
    delay=once(delay,TAIL_OLD,TAIL_NEW)
    delay=once(delay,'const auto entry=gd::native_array_index(b,ctx.f__timed,V::from_int(read));','hit(3);const auto entry=gd::native_array_index(b,ctx.f__timed,V::from_int(read));')
    entry='''
inline bool motion_entry(BattleCtx& b,const V& entry,const V& delta,bool& keep){
    if(!b.native_resolved_dispatch || b.native_resolved_audit || b.native_event_audit || b.native_resolved_collect || (_mm_getcsr()&~63u)!=0x1f80u || entry.kind!=V::Kind::Arr || !entry.arr || entry.arr->len!=3)return false;
    const auto* data=entry.arr->data;
    if(data[0].kind!=V::Kind::Int || data[1].kind!=V::Kind::Obj || !data[1].obj)return false;
    const auto* row=data[1].obj->native_call_row_;
    if(!row || (data[0].i==0 ? row->metadata!=&META_Gd__gd_core__CoreCharacter : row->methods[native_resolved_slots[SYM_GEN__tickChargePath_506]]!=&native_resolved_invoke<Item,&Item::fn__tickChargePath>))return false;
    hit(0);keep=false;
    if(data[0].i==0){auto* c=static_cast<Character*>(data[1].obj);
        if(native_scalar_eq(c->f__visual_generation,data[2]) && native_scalar_ne(c->f__visual_kind,V::from_int(0))){typed_visual(c,&delta);keep=native_scalar_ne(c->f__visual_kind,V::from_int(0));}
    }else{const V args[]={data[2],delta};typed_charge(static_cast<Item*>(data[1].obj),args);keep=native_scalar_truth(native_inline_get_prop(b,args[0],SYM_GEN_active_1653));}
    return true;
}
'''
    header='''#pragma once
#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreElectricalCharge.hpp"
#include <bit>
#include <xmmintrin.h>
namespace gd {template<class C,GdVal(C::*Method)(const GdVal*,int)> GdVal native_resolved_invoke(GdObj*,const GdVal*,int);}
namespace gd::typed_timeline {
using V=GdVal;using Context=Gd__gd_core__CoreContext;using Character=Gd__gd_core__CoreCharacter;using Item=Gd__gd_core__CoreItem;using Charge=Gd__gd_core__CoreItem__INNER__CoreElectricalCharge;
inline thread_local bool collect=false;
inline thread_local uint64_t counts[4]{};
inline void hit(unsigned n){if(collect)++counts[n];}
'''+extra+'\n'+entry+'\n'+delay+'\n}\n'
    (src/'native_typed_timeline.hpp').write_text(header,encoding='utf8',newline='\n')
    shard=src/'gen/shards/shard_07.cpp';text=shard.read_text('utf8');changes=[]
    def change(a,b):
        nonlocal text
        text=once(text,a,b);changes.append([a,b])
    change('#include "../../native_event_kernel.hpp"','#include "../../native_event_kernel.hpp"\n#include "../../native_typed_timeline.hpp"')
    change('gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(const gd::GdVal* _args, int _argc) {','''gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(const gd::GdVal* _args, int _argc) {
    if(rt_ctx_->native_resolved_dispatch && !rt_ctx_->native_resolved_audit && !rt_ctx_->native_event_audit && !rt_ctx_->native_resolved_collect && (_mm_getcsr()&~63u)==0x1f80u && f__timed.kind==gd::GdVal::Kind::Arr && f__timed.arr){
        const auto delta=gd::gd_coerce_float(_argc>0?_args[0]:gd::GdVal::null());
        return gd::typed_timeline::typed_delay(*this,delta);
    }''')
    start=text.index('gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion(');end=text.index('\n}',start)+2
    old_method=text[start:end];new_method=once(old_method,'        bool native_keep = false;\n        if (','        bool native_keep = false;\n        if (gd::typed_timeline::motion_entry(gd_ctx,lv_entry,lv_delta,native_keep)) {}\n        else if (')
    change(old_method,new_method)
    change('extern "C" uint64_t gd_diag_native_motion_index_stat(unsigned field){return field<3?gd::native_motion_index_counts[field]:0;}','''extern "C" uint64_t gd_diag_native_motion_index_stat(unsigned field){return field<3?gd::native_motion_index_counts[field]:0;}
extern "C" void gd_diag_native_timeline_collect(int enabled){gd::typed_timeline::collect=enabled!=0;}
extern "C" uint64_t gd_diag_native_timeline_stat(unsigned field){return field<4?gd::typed_timeline::counts[field]:0;}''')
    shard.write_text(text,encoding='utf8',newline='\n');save('source_changes.json',changes);save('source_before_build.json',inventory(src));save('source_projection.json',verify_projection(src))
    shutil.copyfile(ACCEPTED/'bundle.dll',WORK/'baseline.dll')
    profile=STAGE/'native_perf50/measurement_structure_bundle'
    for name in ['formal_ab_protocol.json','calibration_plan.json','aa_analysis.json','fixed200_reference.json']:shutil.copyfile(profile/name,WORK/name)
    save('architecture_selection.json',dict(selected='Live typed timeline entry qualification and exact original per-step FP32 lowering',frozen_AB_protocol_sha256=sha(WORK/'formal_ab_protocol.json'),no_persistent_raw_operand_cache=True,callbacks_and_live_queue_tail_preserved=True,screen_only_projected_whole_gain_pct=[2,3],normal_full20_before_fresh_full_PGO=True))
    save('user_boundary_before.json',json.loads((ACCEPTED/'user_boundary_before.json').read_bytes()))
    print('Prepared isolated typed timeline candidate; exact inverse verified',flush=True)

if __name__=='__main__':main()

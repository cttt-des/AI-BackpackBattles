"""Count equivalent speed work between callbacks, without skipping any work."""
import ctypes
import hashlib
import json
from pathlib import Path
from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases

DECL='''
void native_speed_probe_reset_phase();
void native_speed_probe_invalidate(unsigned);
void native_speed_probe_value(const void*,int64_t,double,double);
'''
PROBE='''
namespace {
thread_local uint64_t native_speed_counts[10]{};
struct NativeSpeedProbeRow { const void* character=nullptr; int64_t difference=0; uint64_t scale=0; double speed=0; };
thread_local NativeSpeedProbeRow native_speed_row;
struct NativeSpeedProbeScope {
    NativeSpeedProbeScope(){native_speed_probe_reset_phase();}
    ~NativeSpeedProbeScope(){native_speed_row={};}
};
}
void native_speed_probe_reset_phase(){++native_speed_counts[0];native_speed_row={};}
void native_speed_probe_invalidate(unsigned reason){++native_speed_counts[4+reason];native_speed_row={};}
void native_speed_probe_value(const void* character,int64_t difference,double scale,double speed){
    ++native_speed_counts[1];
    if(native_speed_row.character==character){
        ++native_speed_counts[2];
        native_speed_counts[8]+=native_speed_row.difference!=difference;
        if(native_speed_row.scale==std::bit_cast<uint64_t>(scale)){
            ++native_speed_counts[3];
            native_speed_counts[9]+=std::bit_cast<uint64_t>(native_speed_row.speed)!=std::bit_cast<uint64_t>(speed);
        }
    }
    native_speed_row={character,difference,std::bit_cast<uint64_t>(scale),speed};
}
extern "C" uint64_t gd_sim_speed_stat(unsigned index){return index<10?native_speed_counts[index]:0;}
extern "C" void gd_sim_speed_reset(){for(auto& value:native_speed_counts)value=0;native_speed_row={};}
'''

def once(s,old,new):
    assert s.count(old)==1,(old[:100],s.count(old))
    return s.replace(old,new)

def instrument(native):
    p=native/'gen/shards/shard_00.cpp';s=p.read_text('utf8')
    if DECL in s:
        assert PROBE in (native/'gen/shards/shard_03.cpp').read_text('utf8')
        return
    start=s.index('gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(')
    end=s.index('\ngd::GdVal ',start+1);body=s[start:end]
    body=once(body,'    const auto receiver =',
              '    if(this->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)) native_speed_probe_invalidate(0);\n    const auto receiver =')
    body=once(body,'    const auto* character =','    if(this->meta()->is_subclass_of(&META_Gd__gd_core_items__Gems__Gem)) native_speed_probe_invalidate(0);\n    const auto* character =')
    old='            const auto bonus = this->f_speedScale.as_float() + static_cast<double>(stacks(107) - stacks(110)) * 0.02;'
    body=once(body,old,'            const auto native_probe_difference=stacks(107) - stacks(110);\n            const auto bonus = this->f_speedScale.as_float() + static_cast<double>(native_probe_difference) * 0.02;')
    anchor='            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);'
    body=once(body,anchor,anchor+'\n            native_speed_probe_value(character,native_probe_difference,this->f_speedScale.as_float(),speed);')
    anchor='            speed = this->fn_getSpeed(nullptr, 0).as_float();'
    body=once(body,anchor,'            native_speed_probe_invalidate(1);\n'+anchor+'\n            native_speed_probe_invalidate(1);')
    anchor='        gd::call_method(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);'
    body=once(body,anchor,'        native_speed_probe_invalidate(2);\n'+anchor+'\n        native_speed_probe_invalidate(2);')
    anchor='    if (this->f_triggerTime.as_float() <= 0.0) gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);'
    body=once(body,anchor,'    if (this->f_triggerTime.as_float() <= 0.0) {native_speed_probe_invalidate(3); gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);native_speed_probe_invalidate(3);}')
    s=s[:start]+body+s[end:]
    p.write_text('#include "../../gd_rt.hpp"\n'+DECL+s,encoding='utf8',newline='\n')
    p=native/'gen/shards/shard_03.cpp';s=p.read_text('utf8')
    for array,length in (('_t757','_len__t758'),('_t763','_len__t764')):
        anchor=f'        uint32_t {length} = {array} ? {array}->len : 0u;'
        s=once(s,anchor,anchor+'\n        NativeSpeedProbeScope native_speed_scope;')
    p.write_text('#include "../../gd_rt.hpp"\n#include <bit>\n'+DECL+PROBE+s,encoding='utf8',newline='\n')

def inspect(dll,out):
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    reset=sim.lib.gd_sim_speed_reset;reset.argtypes=[];reset.restype=None
    read=sim.lib.gd_sim_speed_stat;read.argtypes=[ctypes.c_uint];read.restype=ctypes.c_uint64
    reset();result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    names=('role_phases','normal_speed_calculations','reusable_character_stats','reusable_final_speed',
           'gem_getter_boundaries','fallback_speed_boundaries','display_boundaries','trigger_boundaries',
           'unexpected_stat_changes_between_boundaries','unexpected_speed_changes_with_same_key')
    values=dict(zip(names,(read(i) for i in range(len(names))),strict=True))
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
            'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],'counts':values,
            'stat_reuse_fraction':values['reusable_character_stats']/values['normal_speed_calculations'],
            'final_speed_reuse_fraction':values['reusable_final_speed']/values['normal_speed_calculations'],
            'no_timing_claim':True}
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(report,indent=2))

if __name__=='__main__':
    import argparse
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True)
    a=p.parse_args();inspect(a.dll,a.out)

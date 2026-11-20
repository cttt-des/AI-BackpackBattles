"""Count cooldown parent eligibility and same-phase invalidations; no timing claims."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from probe_native_selective_timer_scan import replace_one

PROBE = '''
namespace {
thread_local uint64_t cooldown_counts[12]{};
thread_local uint64_t cooldown_epoch=1;
struct CooldownCheckpoint {
    const void* character=nullptr;
    const gd::GdArr* items=nullptr;
    uint32_t length=0;
    uint64_t arrays=0, active=0;
};
thread_local CooldownCheckpoint cooldown_checkpoints[2];
void cooldown_new_combat() {for(auto& row:cooldown_checkpoints)row={};}
bool cooldown_eligible(const gd::GdVal& value) {
    if(value.kind!=gd::GdVal::Kind::Bool) {++cooldown_counts[11];return true;}
    return gd::gd_truth(value);
}
uint64_t cooldown_visit(gd::BattleCtx& battle,const void* character,gd::GdArr* items) {
    if(!items->native_timer_scan_tracked)gd::native_timer_scan_mark(battle,gd::GdVal::from_arr(items));
    const auto arrays=gd::native_timer_scan_epoch();
    auto* row=&cooldown_checkpoints[0];
    for(auto& candidate:cooldown_checkpoints)if(!candidate.character || candidate.character==character){row=&candidate;break;}
    ++cooldown_counts[0];
    cooldown_counts[1]+=row->character==character && row->items==items && row->length==items->len &&
        row->arrays==arrays && row->active==cooldown_epoch;
    *row={character,items,items->len,arrays,cooldown_epoch};
    for(uint32_t i=0;i<items->len;++i) {
        ++cooldown_counts[2];
        const auto* item=static_cast<const Gd__gd_core__CoreItem*>(items->data[i].obj);
        const bool own=cooldown_eligible(item->f__cooldown_active);
        cooldown_counts[3]+=own;
        bool any=own;
        const auto* gems=item->f_gems.arr;
        cooldown_counts[5]+=gems->len;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& gem=gems->data[j];
            if(!gem.is_null()) {
                ++cooldown_counts[6];
                const bool active=cooldown_eligible(static_cast<const Gd__gd_core__CoreItem*>(gem.obj)->f__cooldown_active);
                cooldown_counts[7]+=active;any|=active;
            }
        }
        cooldown_counts[4]+=any;
    }
    return arrays;
}
void cooldown_after(uint64_t arrays,uint64_t active) {
    cooldown_counts[8]+=gd::native_timer_scan_epoch()!=arrays || cooldown_epoch!=active;
}
}
void native_cooldown_probe_assignment(const gd::GdVal& before,const gd::GdVal& after) {
    ++cooldown_counts[9];
    if(before.kind!=gd::GdVal::Kind::Bool || after.kind!=gd::GdVal::Kind::Bool || !gd::gd_eq(before,after)) {
        ++cooldown_counts[10];++cooldown_epoch;
    }
}
extern "C" uint64_t gd_sim_cooldown_stat(unsigned index) {return index<12?cooldown_counts[index]:0;}
extern "C" void gd_sim_cooldown_reset() {for(auto& value:cooldown_counts)value=0;cooldown_new_combat();}
'''


def instrument(native):
    path=native/'gen/shards/shard_00.cpp';s=path.read_text('utf8')
    for value in ('gd::GdVal::from_bool(false)','val','lv_active'):
        anchor=f'this->f__cooldown_active = {value};'
        count=s.count(anchor);assert count==(2 if value.endswith('(false)') else 1),(value,count)
        s=s.replace(anchor,f'native_cooldown_probe_assignment(this->f__cooldown_active,{value}); '+anchor)
    path.write_text('#include "../../gd_rt.hpp"\nvoid native_cooldown_probe_assignment(const gd::GdVal&,const gd::GdVal&);\n'+s,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_03.cpp';s=path.read_text('utf8')
    anchor='void Gd__gd_core__CoreCombat::init_fields(gd::BattleCtx& gd_ctx) {\n    selective_timer_new_combat();\n'
    s=replace_one(s,anchor,anchor+'    cooldown_new_combat();\n')
    for suffix,character,array,length in (('opponent','opponent()','_t757','_len__t758'),('player','player()','_t763','_len__t764')):
        anchor=f'        uint32_t {length} = {array} ? {array}->len : 0u;\n'
        at=s.index(anchor);start=s.rfind('    {\n',0,at);opening=s.index('{',start);depth=1;end=opening+1
        while depth:
            if s[end]=='{':depth+=1
            elif s[end]=='}':depth-=1
            end+=1
        closing=end-1
        s=s[:closing]+f'    cooldown_after(cooldown_arrays_{suffix},cooldown_active_{suffix});\n    '+s[closing:]
        addition=f'        const auto cooldown_arrays_{suffix}=cooldown_visit(gd_ctx,{character},{array});\n        const auto cooldown_active_{suffix}=cooldown_epoch;\n'
        s=replace_one(s,anchor,anchor+addition)
    s='#include "../../gd_rt.hpp"\n#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'+PROBE+s
    path.write_text(s,encoding='utf8',newline='\n')
    print('Instrumented all four cooldown-active assignments and both ordered cooldown scans',flush=True)


def inspect(dll,out):
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    reset=sim.lib.gd_sim_cooldown_reset;reset.argtypes=[];reset.restype=None
    read=sim.lib.gd_sim_cooldown_stat;read.argtypes=[ctypes.c_uint];read.restype=ctypes.c_uint64
    reset();result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    names=('character_passes','reusable_epoch_passes','parent_visits','own_active_parents','any_active_parents',
           'socket_visits','nonnull_gems','active_gems','passes_with_midpass_mutation','active_assignments','active_changes','nonbool_active_values')
    values=dict(zip(names,(read(i) for i in range(len(names))),strict=True))
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
            'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],'counts':values,
            'parent_eligible_fraction':values['any_active_parents']/values['parent_visits'],
            'epoch_reuse_fraction':values['reusable_epoch_passes']/values['character_passes'],
            'array_epoch_scope':'Conservative: timer, gem and physical item arrays; active bool changes tracked separately'}
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True)
    a=p.parse_args();inspect(a.dll,a.out)

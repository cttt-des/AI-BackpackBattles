"""Count timer-owner sparsity and net structural changes; never deploy this DLL."""
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/motion_indices_bundle'
WORK=STAGE/'native_perf50/targeted_timer_probe'
EXPECTED='7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058'
ARCHIVE='4a5388b7161d765cafe5515f263ee0f762fe7c88'
FIELDS=('passes','item_slots','gem_slots','nonempty_item_owners','nonempty_gem_owners','timer_entries',
        'between_pass_timer_shape_changes','between_pass_membership_changes','between_pass_presence_changes',
        'same_pass_timer_shape_changes','same_pass_membership_changes','same_pass_presence_changes','previous_pass_comparisons')

HELPER=r'''
#include <unordered_map>
namespace {
struct TimerShape {
    uint64_t membership=1469598103934665603ULL,shape=1469598103934665603ULL,presence=1469598103934665603ULL;
    uint64_t items=0,gems=0,item_owners=0,gem_owners=0,timers=0;
};
static thread_local uint64_t timer_shape_stats[13]{};
static uint64_t timer_shape_mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static void timer_shape_owner(TimerShape& s,Gd__gd_core__CoreItem* item,bool gem){
    const auto* timers=item->f_timers.arr;
    const auto n=timers?timers->len:0;
    const auto pointer=reinterpret_cast<uintptr_t>(item);
    s.shape=timer_shape_mix(timer_shape_mix(timer_shape_mix(s.shape,pointer),reinterpret_cast<uintptr_t>(timers)),n);
    s.presence=timer_shape_mix(timer_shape_mix(s.presence,pointer),n!=0);
    if(n){if(gem)++s.gem_owners;else ++s.item_owners;s.timers+=n;}
}
static TimerShape timer_shape_snapshot(Gd__gd_core__CoreCharacter* character){
    TimerShape s;
    const auto* grid=static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);
    const auto* items=grid->f_items.arr;
    s.membership=timer_shape_mix(timer_shape_mix(s.membership,reinterpret_cast<uintptr_t>(grid)),reinterpret_cast<uintptr_t>(items));
    s.membership=timer_shape_mix(s.membership,items->len);s.items=items->len;
    for(uint32_t i=0;i<items->len;++i){
        auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);
        s.membership=timer_shape_mix(s.membership,reinterpret_cast<uintptr_t>(item));
        timer_shape_owner(s,item,false);
        const auto* gems=item->f_gems.arr;s.gems+=gems->len;
        s.membership=timer_shape_mix(timer_shape_mix(s.membership,reinterpret_cast<uintptr_t>(gems)),gems->len);
        for(uint32_t j=0;j<gems->len;++j){
            const auto& v=gems->data[j];s.membership=timer_shape_mix(s.membership,unsigned(v.kind));
            if(v.kind==gd::GdVal::Kind::Obj&&v.obj){s.membership=timer_shape_mix(s.membership,reinterpret_cast<uintptr_t>(v.obj));timer_shape_owner(s,static_cast<Gd__gd_core__CoreItem*>(v.obj),true);}
        }
    }return s;
}
struct TimerPrevious {const gd::BattleCtx* context=nullptr;uint64_t epoch=0;TimerShape end;};
static thread_local std::unordered_map<Gd__gd_core__CoreCharacter*,TimerPrevious> timer_shape_previous;
static TimerShape timer_shape_begin(Gd__gd_core__CoreCharacter* character){
    const auto s=timer_shape_snapshot(character);auto& old=timer_shape_previous[character];
    ++timer_shape_stats[0];timer_shape_stats[1]+=s.items;timer_shape_stats[2]+=s.gems;
    timer_shape_stats[3]+=s.item_owners;timer_shape_stats[4]+=s.gem_owners;timer_shape_stats[5]+=s.timers;
    if(old.context==character->rt_ctx_&&old.epoch==character->rt_ctx_->gid_epoch){
        ++timer_shape_stats[12];timer_shape_stats[6]+=old.end.shape!=s.shape;
        timer_shape_stats[7]+=old.end.membership!=s.membership;timer_shape_stats[8]+=old.end.presence!=s.presence;
    }return s;
}
static void timer_shape_end(Gd__gd_core__CoreCharacter* character,const TimerShape& before){
    const auto after=timer_shape_snapshot(character);
    timer_shape_stats[9]+=before.shape!=after.shape;timer_shape_stats[10]+=before.membership!=after.membership;timer_shape_stats[11]+=before.presence!=after.presence;
    timer_shape_previous[character]={character->rt_ctx_,character->rt_ctx_->gid_epoch,after};
}
}
'''

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    WORK.mkdir(exist_ok=True);assert not (WORK/'diagnostic.dll').exists()
    source=WORK/'diagnostic_src';assert not source.exists()
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    p=source/'gen/shards/shard_03.cpp';text=p.read_text('utf8')
    signature='gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers('
    begin=text.index(signature);end=text.index('\n}',begin)+2
    old=text[begin:end]
    boundary='    const auto* inventory = static_cast<Gd__gd_core__CoreGrid*>(character->f_inventory.obj);'
    assert old.count(boundary)==1 and old.count('    return gd::GdVal::null();')==1
    new=old.replace(boundary,'    const auto native_shape = timer_shape_begin(character);\n'+boundary,1)
    new=new.replace('    return gd::GdVal::null();','    timer_shape_end(character,native_shape);\n    return gd::GdVal::null();',1)
    # The helper requires the exact generated class declarations, so insert it
    # immediately before this method, after all includes and metadata definitions.
    text=text[:begin]+HELPER+'\n'+new+text[end:]
    text+='\nextern "C" uint64_t gd_diag_timer_shape_stat(unsigned i){return i<13?timer_shape_stats[i]:0;}\n'
    p.write_text(text,encoding='utf8',newline='\n')
    original_objects=Path((ACCEPTED/'bundle_objects.txt').read_text('utf8'))
    objects=sorted(original_objects.glob('*.o'));assert len(objects)==20
    before={p.name:sha(p) for p in objects}
    directory=Path(tempfile.mkdtemp(prefix='native-timer-shape-'))
    for obj in objects:shutil.copyfile(obj,directory/obj.name)
    module=runpy.run_path(str(source/'build_windows.py'))
    compiler='D:/mingw64/bin/g++.exe';flags=module['COMMON']
    (WORK/'build_objects.txt').write_text(str(directory),encoding='utf8')
    print('Compiling only diagnostic shard03; reusing19 byte-verified final objects; no throughput claim',flush=True)
    subprocess.run([compiler,*flags,'-flto=2','-c',str(p),'-o',str(directory/'shard_03.o')],check=True)
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(directory/'diagnostic.dll'),*[str(directory/obj.name) for obj in objects]],check=True)
    shutil.copyfile(directory/'diagnostic.dll',WORK/'diagnostic.dll')
    assert before=={p.name:sha(p) for p in objects},'Never change accepted build objects'
    report=dict(diagnostic_only=True,baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,diagnostic_dll_sha256=sha(WORK/'diagnostic.dll'),
        reused_accepted_objects={k:v for k,v in before.items() if k!='shard_03.o'},modified_source=['gen/shards/shard_03.cpp'],
        original_method_sha256=hashlib.sha256(old.encode()).hexdigest(),helper_sha256=hashlib.sha256(HELPER.encode()).hexdigest(),
        fields=FIELDS,limitation='Counts compare net shapes at pass boundaries, not every mutation; transient changes may cancel. Not a throughput benchmark or sufficient cache-invalidation proof.')
    (WORK/'diagnostic_build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    sys.path.insert(0,str(STAGE))
    import ctypes
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'diagnostic.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_diag_timer_shape_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    initial=[stat(i) for i in range(len(FIELDS))]
    result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    counts=dict(zip(FIELDS,[stat(i)-initial[i] for i in range(len(FIELDS))]))
    report.update(inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,counts=counts,
        nonempty_item_ratio=counts['nonempty_item_owners']/counts['item_slots'],
        nonempty_gem_slot_ratio=counts['nonempty_gem_owners']/counts['gem_slots'] if counts['gem_slots'] else None)
    (WORK/'sparsity_fixed200.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps({k:v for k,v in report.items() if k!='reused_accepted_objects'},indent=2))

if __name__=='__main__':main()

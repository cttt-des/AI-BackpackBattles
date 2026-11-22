"""Measure active cooldown slots and eligibility writes without changing the deployed DLL."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import re
import runpy
import shutil
import subprocess
import tempfile
from concurrent.futures import ThreadPoolExecutor
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/closed_timer_bundle'
WORK=STAGE/'native_perf50/cooldown_sparsity_probe'
EXPECTED='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'
FIELDS=('writes','same_bool','bool_flips','nonbool_transitions','flips_after_activation','flips_in_item_pass','flips_in_timer_pass','writes_after_activation',
        'init_site','setter_site','set_active_site','reset_site','item_slots','active_items','inactive_items','nonbool_items',
        'nonnull_gems','active_gems','inactive_gems','nonbool_gems','gem_slots','null_gems','other_gem_kinds','unknown_contexts',
        'flips_to_true','flips_to_false','writes_in_item_pass','writes_in_timer_pass','same_true_after_activation','same_false_after_activation')
HELPER=r'''
namespace gd {
static thread_local uint64_t native_cooldown_probe_counts[30]{};
void native_cooldown_probe_write(BattleCtx&,GdObj* object,const GdVal& old_value,const GdVal& value,unsigned site) {
    auto* item=static_cast<Gd__gd_core__CoreItem*>(object);auto* counts=native_cooldown_probe_counts;
    ++counts[0];if(site<4)++counts[8+site];
    const bool both_bool=old_value.kind==GdVal::Kind::Bool && value.kind==GdVal::Kind::Bool;
    const bool flip=both_bool && old_value.b!=value.b;
    if(both_bool){if(flip){++counts[2];++counts[value.b?24:25];}else ++counts[1];}else ++counts[3];
    if(item->f_ctx.kind!=GdVal::Kind::Obj || !item->f_ctx.obj || typeid(*item->f_ctx.obj)!=typeid(Gd__gd_core__CoreContext)){++counts[23];return;}
    auto* context=static_cast<Gd__gd_core__CoreContext*>(item->f_ctx.obj);
    const auto& item_pass=context->f_in_item_physics_pass;const auto& timer_pass=context->f_in_physics_timer_pass;
    const bool in_item=item_pass.kind==GdVal::Kind::Bool && item_pass.b;
    const bool in_timer=timer_pass.kind==GdVal::Kind::Bool && timer_pass.b;
    counts[26]+=in_item;counts[27]+=in_timer;counts[5]+=flip&&in_item;counts[6]+=flip&&in_timer;
    const auto& combat_value=context->f_combat;
    if(combat_value.kind==GdVal::Kind::Obj && combat_value.obj && typeid(*combat_value.obj)==typeid(Gd__gd_core__CoreCombat)) {
        const auto& active=static_cast<Gd__gd_core__CoreCombat*>(combat_value.obj)->f_activated;
        const bool activated=active.kind==GdVal::Kind::Bool && active.b;
        counts[7]+=activated;counts[4]+=flip&&activated;
        if(activated&&both_bool&&!flip)++counts[value.b?28:29];
    }
}
void native_cooldown_probe_read(unsigned gem,const GdVal& value) {
    auto* c=native_cooldown_probe_counts;const unsigned base=gem?16:12;++c[base];
    if(value.kind==GdVal::Kind::Bool)++c[base+(value.b?1:2)];else ++c[base+3];
}
void native_cooldown_probe_slot(const GdVal& value) {
    ++native_cooldown_probe_counts[20];native_cooldown_probe_counts[21]+=value.kind==GdVal::Kind::Null;
    native_cooldown_probe_counts[22]+=value.kind!=GdVal::Kind::Null && value.kind!=GdVal::Kind::Obj;
}
}
extern "C" uint64_t gd_diag_native_cooldown_probe_stat(unsigned i){return i<30?gd::native_cooldown_probe_counts[i]:0;}
extern "C" void gd_diag_native_cooldown_probe_reset(){for(auto& i:gd::native_cooldown_probe_counts)i=0;}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'diagnostic_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    header=src/'gd_rt.hpp';header.write_text(header.read_text('utf8')+'''
namespace gd {
void native_cooldown_probe_write(BattleCtx&,GdObj*,const GdVal&,const GdVal&,unsigned);
void native_cooldown_probe_read(unsigned,const GdVal&);
void native_cooldown_probe_slot(const GdVal&);
}
''',encoding='utf8',newline='\n')
    item=src/'gen/shards/shard_00.cpp';text=item.read_text('utf8');pattern=re.compile(r'this->f__cooldown_active = ([^;]+);')
    stores=[]
    def instrument(match):
        site=len(stores);stores.append(match[0]);return '([&] { const auto native_new_active=('+match[1]+');gd::native_cooldown_probe_write(gd_ctx,this,this->f__cooldown_active,native_new_active,'+str(site)+');this->f__cooldown_active=native_new_active; })();'
    text=pattern.sub(instrument,text);assert len(stores)==4,len(stores);item.write_text(text,encoding='utf8',newline='\n')
    combat=src/'gen/shards/shard_03.cpp';combat_source=combat.read_text('utf8')
    begin=combat_source.index('gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(');end=combat_source.index('\n}',begin)+2
    text=combat_source[begin:end]
    marker='            auto* cooldown_item = static_cast<Gd__gd_core__CoreItem*>(lv_item.obj);'
    assert text.count(marker)==2;text=text.replace(marker,marker+'\n            gd::native_cooldown_probe_read(0,cooldown_item->f__cooldown_active);')
    marker='                        auto* cooldown_gem = static_cast<Gd__gd_core__CoreItem*>(lv_gem.obj);'
    # Source indentation may differ between the opponent/player copies.
    pattern=re.compile(r'(?P<indent> +)auto\* cooldown_gem = static_cast<Gd__gd_core__CoreItem\*>\(lv_gem.obj\);')
    assert len(pattern.findall(text))==2
    text=pattern.sub(lambda m:m[0]+'\n'+m['indent']+'gd::native_cooldown_probe_read(1,cooldown_gem->f__cooldown_active);',text)
    pattern=re.compile(r'(?P<indent> +)gd::GdVal lv_gem = (_t\d+)->data\[(_t\d+)\];')
    assert len(pattern.findall(text))==2
    text=pattern.sub(lambda m:m[0]+'\n'+m['indent']+'gd::native_cooldown_probe_slot(lv_gem);',text)
    combat.write_text(combat_source[:begin]+text+combat_source[end:],encoding='utf8',newline='\n')
    runtime=src/'gd_rt.cpp';runtime.write_text(runtime.read_text('utf8')+HELPER,encoding='utf8',newline='\n')
    objects=Path(tempfile.mkdtemp(prefix='native-cooldown-sparsity-'));(WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    original=Path((ACCEPTED/'bundle_objects.txt').read_text('utf8'));names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02}' for i in range(16)]]
    old_objects={n:sha(original/(n+'.o')) for n in names};changed={'gd_rt':'gd_rt.cpp','shard_00':'gen/shards/shard_00.cpp','shard_03':'gen/shards/shard_03.cpp'}
    for name in names:
        if name not in changed:shutil.copyfile(original/(name+'.o'),objects/(name+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    os.environ['MAKE']='D:/mingw64/bin/mingw32-make.exe'
    def compile_unit(row):
        name,file=row;subprocess.run([compiler,*flags,'-c',str(src/file),'-o',str(objects/(name+'.o'))],check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_unit,changed.items()))
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert old_objects=={n:sha(original/(n+'.o')) for n in names}
    assert all(sha(objects/(n+'.o'))==old_objects[n] for n in names if n not in changed)
    dll=WORK/'diagnostic.dll';shutil.copyfile(objects/'libgdcore.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_diag_native_cooldown_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    reset=sim.lib.gd_diag_native_cooldown_probe_reset;reset.argtypes=[];reset.restype=None;reset()
    result=measure(sim,jobs,1,0,continuous=True);reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    counts=dict(zip(FIELDS,[stat(i) for i in range(len(FIELDS))]))
    assert counts['item_slots']==counts['active_items']+counts['inactive_items']+counts['nonbool_items']
    assert counts['nonnull_gems']==counts['active_gems']+counts['inactive_gems']+counts['nonbool_gems']
    assert counts['writes']==sum(counts[k] for k in ('init_site','setter_site','set_active_site','reset_site'))
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(diagnostic_only=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(dll),verified_remote_backup=ARCHIVE,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,counts=counts,
        reused_objects=17,recompiled_units=3,all_original_objects_unchanged=True,header_only_adds_free_function_declarations=True,
        source_store_sites=stores,no_throughput_claim=True,production_unchanged=True)
    (WORK/'fixed200_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()

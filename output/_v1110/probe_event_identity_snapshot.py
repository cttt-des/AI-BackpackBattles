"""Measure eager event identity materialization without changing production or timing it."""
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
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/object_routes_bundle'
WORK=STAGE/'native_perf50/event_identity_snapshot_prototype'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
FIELDS=['attempts','successes','fallbacks','bytes','max_length','bounded64','bounded128','bounded256','bounded512','end_trace_uses','early_returns']

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

COUNTER=r'''
namespace {
static thread_local uint64_t identity_snapshot_probe[11]{};
static bool identity_snapshot_probe_try(gd::BattleCtx& ctx,const gd::GdVal& emitter,const gd::GdStr* delimiter,gd::GdVal& out) {
    auto* p=identity_snapshot_probe;++p[0];
    const bool ok=gd::native_try_event_identity(ctx,emitter,delimiter,out);
    if(!ok){++p[2];return false;}
    ++p[1];const uint64_t n=out.str?out.str->len:0;p[3]+=n;if(n>p[4])p[4]=n;
    if(n<=64)++p[5];if(n<=128)++p[6];if(n<=256)++p[7];if(n<=512)++p[8];
    return true;
}
}
extern "C" void gd_identity_snapshot_probe_reset(){std::memset(identity_snapshot_probe,0,sizeof(identity_snapshot_probe));}
extern "C" uint64_t gd_identity_snapshot_probe_stat(unsigned field){return field<11?identity_snapshot_probe[field]:0;}
'''

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['production_dll_sha256']==EXPECTED
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'probe_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    path=source/'gen/shards/shard_12.cpp';text=path.read_text('utf8')
    needle='gd::native_try_event_identity(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)'
    start=text.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(')
    split=text.index('    gd::GdVal lv_emitter =',text.index('    return gd::GdVal::null();',start)+1)
    body=text[start:split]
    assert body.count(needle)==1;body=body.replace(needle,'identity_snapshot_probe_try(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)')
    marker='        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])'
    assert body.count(marker)==1;body=body.replace(marker,'        ++identity_snapshot_probe[9];\n'+marker)
    early='                return gd::GdVal::null();'
    assert body.count(early)==1;body=body.replace(early,'                ++identity_snapshot_probe[10];\n'+early)
    text=text[:start]+body+text[split:]
    includes=list(re.finditer(r'^#include [^\n]+\n',text,re.M));position=max(m.end() for m in includes)
    assert position<text.index('\ngd::GdVal ')
    text=text[:position]+COUNTER+text[position:];path.write_text(text,encoding='utf8',newline='\n')
    (WORK/'probe_sites.json').write_text(json.dumps(dict(original_source_sha256=frozen['gen/shards/shard_12.cpp'],probe_source_sha256=sha(path),counts_only=True),indent=2)+'\n',encoding='utf8')
    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds';cache.mkdir(exist_ok=True)
    root=Path(tempfile.mkdtemp(prefix='event-identity-count-',dir=cache));objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    assert str(root).isascii()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe')
    tempfile.tempdir=str(scratch)
    (WORK/'live_probe.json').write_text(json.dumps(dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve()),build_root=str(root)))+'\n',encoding='utf8')
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    previous=Path(json.loads((ACCEPTED/'live_recovered_build.json').read_bytes())['object_directory'])
    previous_receipt=json.loads((ACCEPTED/'recovered_release_objects.json').read_bytes())
    old_hashes=previous_receipt['objects_sha256']
    assert old_hashes=={name:sha(previous/(name+'.o')) for name in old_hashes}
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    profile=previous/'pgo'
    with (WORK/'compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(path),'-o',str(objects/'shard_12.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-flto=2',f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction',
            '-save-temps=obj','-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if name=='shard_12' else previous)/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert old_hashes=={name:sha(previous/(name+'.o')) for name in names}
    dll=WORK/'probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    legacy=sim.lib.gd_diag_native_resolved_stat;legacy.argtypes=[ctypes.c_uint];legacy.restype=ctypes.c_uint64
    reset=sim.lib.gd_identity_snapshot_probe_reset;reset.argtypes=[];reset.restype=None;reset()
    stat=sim.lib.gd_identity_snapshot_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[legacy(i) for i in range(6)];result=measure(sim,jobs,1,0,continuous=True)
    counts=[legacy(i)-before[i] for i in range(6)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' and result['matched_original_terminal']==200
    totals={name:stat(i) for i,name in enumerate(FIELDS)}
    assert totals['attempts']==totals['successes']+totals['fallbacks'] and totals['successes']>0
    report=dict(passed=True,probe_only=True,no_throughput_claim=True,not_for_deployment=True,
        baseline_dll_sha256=EXPECTED,verified_backup_commit=backup['remote_verified_commit'],probe_dll_sha256=sha(dll),
        source_proof_sha256=sha(WORK/'probe_sites.json'),baseline_source_manifest_sha256=sha(ACCEPTED/'source_before_build.json'),
        recompiled_units=1,unchanged_baseline_objects=19,old_six_counters=counts,matched_original_terminal=200,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],totals=totals,
        previous_objects_sha256=old_hashes,measurements_are_identity_counts_not_speed=True)
    (WORK/'identity_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps({k:v for k,v in report.items() if k!='previous_objects_sha256'},indent=2))

if __name__=='__main__':main()

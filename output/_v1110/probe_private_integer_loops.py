"""Measure private integer iteration shapes without changing production or timing it."""
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
WORK=STAGE/'native_perf50/private_integer_loops_prototype'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
FIELDS=['calls','int_calls','nonpositive_calls','positive_calls','positive_cells','maximum_positive_length',
    'bounded1024_calls','bounded1024_cells','bounded4096_calls','bounded4096_cells','sum_overflows','noninteger_calls']
HISTOGRAM=['nonpositive','1','2_to4','5_to16','17_to64','65_to256','257_to1024','1025_to4096','above4096']

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

COUNTER=r'''
namespace {
static thread_local uint64_t private_integer_probe[14][53]{};
static void private_integer_probe_hit(unsigned site,const gd::GdVal& value) {
    auto* p=private_integer_probe[site];++p[0];const auto kind=unsigned(value.kind);
    if(kind<32)++p[21+kind];
    if(value.kind!=gd::GdVal::Kind::Int){++p[11];return;}
    ++p[1];const int64_t n=value.i;
    if(n<=0){++p[2];++p[6];++p[8];++p[12];return;}
    ++p[3];const auto positive=uint64_t(n);
    if(UINT64_MAX-p[4]<positive)++p[10];else p[4]+=positive;
    if(positive>p[5])p[5]=positive;
    if(n<=1024){++p[6];p[7]+=positive;}
    if(n<=4096){++p[8];p[9]+=positive;}
    const unsigned bucket=n==1?1:n<=4?2:n<=16?3:n<=64?4:n<=256?5:n<=1024?6:n<=4096?7:8;
    ++p[12+bucket];
}
}
extern "C" void gd_private_integer_probe_reset(){std::memset(private_integer_probe,0,sizeof(private_integer_probe));}
extern "C" uint64_t gd_private_integer_probe_stat(unsigned site,unsigned field){return site<14 && field<53?private_integer_probe[site][field]:0;}
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
    path=source/'gen/shards/shard_00.cpp';text=path.read_text('utf8');sites=[]
    function=re.compile(r'^gd::GdVal Gd__gd_core__CoreBuff::fn_(gainTemporary|loseStacks|onTimeout)\([^\n]*\n(.*?)^}',re.M|re.S)
    loop=re.compile(r'^(\s*)gd::GdVal (_t\d+) = gd::gd_iter_seq\(gd_ctx.arena, (.*)\);$',re.M)
    def rewrite_function(match):
        def rewrite_loop(row):
            index=len(sites);name=row[2]+'_probe_input_'+str(index)
            sites.append(dict(index=index,method=match[1],original_sequence_variable=row[2],input_expression=row[3]))
            return row[1]+'gd::GdVal '+name+' = '+row[3]+';\n'+row[1]+f'private_integer_probe_hit({index},{name});\n'+row[1]+f'gd::GdVal {row[2]} = gd::gd_iter_seq(gd_ctx.arena, {name});'
        body,count=loop.subn(rewrite_loop,match[2]);assert count==(2 if match[1]=='onTimeout' else 6)
        return match[0].replace(match[2],body,1)
    text,n=function.subn(rewrite_function,text);assert n==3 and len(sites)==14
    includes=list(re.finditer(r'^#include [^\n]+\n',text,re.M));position=max(m.end() for m in includes)
    assert position<text.index('\ngd::GdVal ')
    text=text[:position]+COUNTER+text[position:];path.write_text(text,encoding='utf8',newline='\n')
    (WORK/'probe_sites.json').write_text(json.dumps(dict(sites=sites,probe_source_sha256=sha(path),original_source_sha256=frozen['gen/shards/shard_00.cpp']),indent=2)+'\n',encoding='utf8')
    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds';cache.mkdir(exist_ok=True)
    root=Path(tempfile.mkdtemp(prefix='private-integer-count-',dir=cache));objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
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
        subprocess.run([compiler,*flags,'-c',str(path),'-o',str(objects/'shard_00.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-flto=2',f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction',
            '-save-temps=obj','-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if name=='shard_00' else previous)/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert old_hashes=={name:sha(previous/(name+'.o')) for name in names}
    dll=WORK/'probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    legacy=sim.lib.gd_diag_native_resolved_stat;legacy.argtypes=[ctypes.c_uint];legacy.restype=ctypes.c_uint64
    reset=sim.lib.gd_private_integer_probe_reset;reset.argtypes=[];reset.restype=None;reset()
    stat=sim.lib.gd_private_integer_probe_stat;stat.argtypes=[ctypes.c_uint,ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[legacy(i) for i in range(6)];result=measure(sim,jobs,1,0,continuous=True)
    counts=[legacy(i)-before[i] for i in range(6)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' and result['matched_original_terminal']==200
    rows=[]
    for site in sites:
        row=dict(site,**{name:stat(site['index'],i) for i,name in enumerate(FIELDS)})
        row['histogram']={name:stat(site['index'],12+i) for i,name in enumerate(HISTOGRAM)}
        row['kind_counts']={str(i):stat(site['index'],21+i) for i in range(32) if stat(site['index'],21+i)}
        assert row['sum_overflows']==0 and row['calls']==row['int_calls']+row['noninteger_calls']
        assert row['int_calls']==sum(row['histogram'].values())==row['nonpositive_calls']+row['positive_calls']
        rows.append(row)
    totals={name:(max(r[name] for r in rows) if name=='maximum_positive_length' else sum(r[name] for r in rows)) for name in FIELDS}
    assert totals['calls']>0
    report=dict(passed=True,probe_only=True,no_throughput_claim=True,not_for_deployment=True,
        baseline_dll_sha256=EXPECTED,verified_backup_commit=backup['remote_verified_commit'],probe_dll_sha256=sha(dll),
        source_proof_sha256=sha(WORK/'probe_sites.json'),baseline_source_manifest_sha256=sha(ACCEPTED/'source_before_build.json'),
        recompiled_units=1,unchanged_baseline_objects=19,old_six_counters=counts,matched_original_terminal=200,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],totals=totals,sites=rows,
        previous_objects_sha256=old_hashes,measurements_are_iteration_counts_not_saved_allocations_or_speed=True)
    (WORK/'iteration_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps({k:v for k,v in report.items() if k not in ('sites','previous_objects_sha256')},indent=2))

if __name__=='__main__':main()

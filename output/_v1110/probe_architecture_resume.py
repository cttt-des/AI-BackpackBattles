"""Run one small architecture screen in a disposable D: workspace."""
import argparse,json,shutil,subprocess,tempfile,re
from pathlib import Path
import psutil
from native_build_storage import isolated_build,sha

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/architecture_three_bundle'
BASE=STAGE/'native_perf50/frame_guard_reuse_bundle'
EXPECTED='cea3c1c81a9294e05f0aac3b609ee4e474aa7019a1bf766ad12c22d876fe4b52'

@isolated_build
def main():
    p=argparse.ArgumentParser();p.add_argument('probe',choices=['invariant','timeline','timeline_step','delay','frontier','row_guard']);p.add_argument('--dll',type=Path);p.add_argument('--tag');a=p.parse_args()
    prefix=(a.tag or a.probe)+'_resume_probe';source=STAGE/('test_'+a.probe+'_resume_probe.cpp')
    assert not (WORK/(prefix+'_receipt.json')).exists()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert psutil.virtual_memory().available>2*1024**3
    root=Path(tempfile.mkdtemp(prefix=prefix+'-'))
    tested=(a.dll or BASE/'bundle.dll').resolve();shutil.copyfile(tested,root/'libgdcore.dll');assert sha(root/'libgdcore.dll')==sha(tested)
    if not a.dll:assert sha(tested)==EXPECTED
    # Keep a literal local copy of the production method for a matched-code
    # cost control; the independent semantic reference is still the real DLL.
    shard=BASE/'bundle_src/gen/shards/shard_07.cpp'
    text=shard.read_text('utf8');start=text.index('gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion(')
    method=text[start:text.index('\n}',start)+2]
    method=method.replace('gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion(', 'gd::GdVal local_tick_motion(Context* self,').replace('this->','self->')
    (root/'local_motion.hpp').write_text('namespace gd {static thread_local uint64_t native_motion_index_counts[3]{};}\n'+method+'\n',encoding='utf8')
    start=text.index('gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(')
    method=text[start:text.index('\n}',start)+2].replace('gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(', 'gd::GdVal local_delay(Context* self,').replace('this->','self->')
    (root/'local_delay.hpp').write_text(method+'\n',encoding='utf8')
    if a.probe=='row_guard':
        names=re.findall(r'extern const gd::GdClassMeta (META_\w+);',(BASE/'bundle_src/gen/class_metas.hpp').read_text('utf8'))
        assert len(names)==674
        (root/'timeline_meta_list.hpp').write_text('static const gd::GdClassMeta* timeline_metas[]={'+','.join('&'+n for n in names)+'};\n',encoding='utf8')
    flags=['-O3','-std=c++20','-march=native','-ffp-contract=off','-static']
    command=['D:/mingw64/bin/g++.exe',*flags,'-I',str(root),'-I',str(STAGE),'-I',str(BASE/'bundle_src'),str(source),str(root/'libgdcore.dll'),'-o',str(root/'probe.exe')]
    attempt=1
    while (WORK/f'{prefix}_compile_{attempt}.log').exists():attempt+=1
    with (WORK/f'{prefix}_compile_{attempt}.log').open('xb') as log:
        subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True,cwd=root)
    process=psutil.Popen([str(root/'probe.exe')],stdout=subprocess.PIPE,stderr=subprocess.PIPE,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS)
    process.cpu_affinity([2]);out,error=process.communicate(timeout=180)
    raw=WORK/f'{prefix}_raw_{attempt}.json';raw.write_bytes(out)
    (WORK/f'{prefix}_stderr_{attempt}.log').write_bytes(error)
    if process.returncode:raise RuntimeError(f'{prefix} failed {process.returncode}: '+error.decode('utf8','replace')[-2000:])
    result=json.loads(out);assert result['passed']
    (WORK/(prefix+'_receipt.json')).write_text(json.dumps(dict(passed=True,attempt=attempt,source_sha256=sha(source),driver_sha256=sha(__file__),baseline_dll_sha256=EXPECTED,tested_dll_sha256=sha(tested),raw_path=raw.name,raw_sha256=sha(raw),flags=flags,semantic_cases=result['semantic_cases'],small_mechanism_probe_only=True,not_a_release_gain=True),indent=2)+'\n',encoding='utf8')
    print(f'{prefix}: {result["semantic_cases"]} semantic cases; raw timings retained',flush=True)

if __name__=='__main__':main()

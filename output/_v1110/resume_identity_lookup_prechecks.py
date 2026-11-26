"""Continue unexecuted checks after an exact inverse-source pin repair; no rebuild."""
import ast
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_identity_lookup import STAGE,ACCEPTED,sha,verify_projection,IDENTITY,LOOKUP

WORK=STAGE/'native_perf50/identity_lookup_bundle'

def write(path,data):path.write_text(json.dumps(data,indent=2)+'\n',encoding='utf8')
def unchanged():
    before=json.loads((WORK/'pre_timing_source_pin_repair/before.json').read_bytes())
    for name,key in [('bundle.dll','dll_sha256'),('source_before_build.json','source_manifest_sha256'),
            ('fresh_profile_source.json','fresh_profile_source_sha256'),('frozen_pgo_manifest.json','frozen_pgo_manifest_sha256')]:
        assert sha(WORK/name)==before[key],name
    assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']
    pgo=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())
    assert len(pgo['counts'])==18
    for name,digest in pgo['counts'].items():assert sha(WORK/'frozen_pgo_counts'/(name+'.gcda'))==digest
    return before
def launch(script,log,role,rows,*args):
    path=WORK/log;assert not path.exists();print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as output:
        child=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        rows[role]=dict(pid=child.pid,created=psutil.Process(child.pid).create_time())
        write(WORK/'live_formal_driver.json',rows)
        while child.poll() is None:
            try:child.wait(timeout=30)
            except subprocess.TimeoutExpired:continue
        assert child.returncode==0,(script,child.returncode,'Inspect its original log; do not repeat observed samples')
    print('Passed '+script,flush=True)
def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    rows=json.loads((WORK/'live_formal_driver.json').read_bytes())
    for row in rows.values():
        try:
            other=psutil.Process(row['pid']);assert other.create_time()!=row['created'] or not other.is_running()
        except psutil.NoSuchProcess:pass
    assert not any(WORK.glob('ab_*.json')) and not (WORK/'comparison.log').exists()
    before=unchanged();screen=json.loads((WORK.parent/'motion_indices_probe/screen_matched.json').read_bytes())
    current=(WORK/'bundle_src/native_scalar_equal.hpp').read_text('utf8')
    assert current.count(IDENTITY)==current.count(LOOKUP)==1
    original=current.replace(IDENTITY,'',1).replace(LOOKUP,'',1)
    import hashlib
    assert hashlib.sha256(original.encode()).hexdigest()==screen['dependency_sha256']['native_scalar_equal.hpp']==sha(ACCEPTED/'bundle_src/native_scalar_equal.hpp')
    # Retain all runtime state/legacy-counter comparisons and all remaining checks.
    original_runner=(WORK/'validate_then_compare.py').read_text('utf8')
    start=original_runner.index("    run('verify_motion_indices.py'")
    end=original_runner.index("\nif __name__=='__main__':main()")
    tail=original_runner[start:end]
    tail=tail.replace("'motion_indices_tests.log'","'motion_indices_tests_after_source_pin_repair.log'",1)
    script='''import json
from pathlib import Path
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent
def run(script,log,*args):
    path=WORK/log;assert not path.exists(),path
    print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as output:subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    dll=WORK/'bundle.dll'
'''+tail+"\nif __name__=='__main__':main()\n"
    ast.parse(script);remaining=WORK/'run_remaining_prechecks.py';assert not remaining.exists();remaining.write_text(script,encoding='utf8',newline='\n')
    review=WORK/'pre_timing_source_pin_repair/repair_review.json';assert not review.exists()
    write(review,dict(passed=True,strict_inverse_reproduces_original_dependency=True,
        original_motion5840_state_and_counter_hash_assertions_retained=True,all_remaining_checks_retained=True,
        dll_sha256=before['dll_sha256'],source_manifest_sha256=before['source_manifest_sha256'],
        source_dll_objects_and_profiles_unchanged=True,no_formal_samples_observed_before_repair=True,
        repaired_verifier_sha256=sha(WORK/'verify_motion_indices.py')))
    rows['resumed_driver']=dict(pid=p.pid,created=p.create_time());write(WORK/'live_formal_driver.json',rows)
    launch('run_remaining_prechecks.py','prechecks_remaining_first.log','resumed_validation',rows)
    before=unchanged();ab=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert all(r['pairs']==24 for r in ab['metrics'].values())
    ready=WORK/'remaining_prechecks_ready.json';assert not ready.exists()
    write(ready,dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=before['dll_sha256'],source_manifest_sha256=before['source_manifest_sha256'],
        ab_assessment_sha256=sha(WORK/'ab_assessment.json'),repair_review_sha256=sha(review)))
    launch('qualify_when_ready.py','qualification_after_source_pin_repair.log','resumed_qualifier',rows,
        '--pid','0','--created','0','--ready-receipt',ready)
    print('Completed remaining checks and original qualification; deployment remains gated',flush=True)

if __name__=='__main__':main()

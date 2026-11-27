"""Assess the repaired production DLL before selecting one new optimization."""
import hashlib,json,runpy,sys
from pathlib import Path
import psutil
from prepare_ordering_correctness import REPO,STAGE,BASE,sha
from install_ordering_correctness import boundary
WORK=STAGE/'native_perf50/next_two_assessment'
def main():
    boundary();previous=STAGE/'native_perf50/frame_guard_reuse_bundle'
    receipt=json.loads((previous/'checkpoint_receipt.json').read_bytes());assert receipt['remote_upload_verified']
    expected=receipt['production_dll_sha256'];assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==expected
    assert not WORK.exists();WORK.mkdir()
    p=psutil.Process();p.nice(psutil.NORMAL_PRIORITY_CLASS);p.cpu_affinity(list(range(psutil.cpu_count())))
    out=WORK/'profile_depth64.json'
    sys.argv=[str(STAGE/'profile_native_windows.py'),'--dll',str(BASE/'libgdcore.dll'),'--corpus','--min-samples','2000','--max-depth','64','--full-output','--instruction-locations','--out',str(out)]
    runpy.run_path(str(STAGE/'profile_native_windows.py'),run_name='__main__')
    result=json.loads(out.read_bytes());assert result['dll_sha256']==expected and result['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert sha(BASE/'libgdcore.dll')==expected;boundary()
    (WORK/'profile_receipt.json').write_text(json.dumps(dict(dll_sha256=expected,parent_verified_commit=receipt['remote_verified_commit'],samples=result['samples'],source_profile_sha256=sha(out),no_candidate_or_speed_claim=True),indent=2)+'\n',encoding='utf8')
    print('Fresh repaired-production profile saved',flush=True)
if __name__=='__main__':main()

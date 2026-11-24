"""Refresh deployed-binary stacks after compilation, before isolated A/B warmup."""
import hashlib
import json
from pathlib import Path
import runpy
import sys
import psutil

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))

def main():
    process=psutil.Process();process.nice(psutil.NORMAL_PRIORITY_CLASS)
    assert psutil.cpu_count()==8;process.cpu_affinity(list(range(8)))
    dll=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    sha=hashlib.sha256(dll.read_bytes()).hexdigest()
    assert sha=='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'
    out=WORK.parent/'post_hot_coverage_profile/profile_depth64.json'
    assert not out.exists(),'Retain the first complete diagnostic sample report'
    sys.argv=[str(STAGE/'profile_native_windows.py'),'--dll',str(dll),'--corpus',
        '--min-samples','2000','--max-depth','64','--full-output','--instruction-locations','--out',str(out)]
    runpy.run_path(str(STAGE/'profile_native_windows.py'),run_name='__main__')
    report=json.loads(out.read_bytes())
    roots=sum(row['samples'] for row in report['resolved_stacks'] if any('run_one_internal' in name for name in row['functions']))
    assert roots>=1000 and report['dll_sha256']==sha
    assert report['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert hashlib.sha256(dll.read_bytes()).hexdigest()==sha
    receipt={'dll_sha256':sha,'samples':report['samples'],'valid_replay_roots':roots,
        'normal_priority_all8':True,'before_formal_warmup_and_no_compilers':True,
        'report_sha256':hashlib.sha256(out.read_bytes()).hexdigest()}
    (WORK/'baseline_profile_receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    print(json.dumps(receipt),flush=True)

if __name__=='__main__':main()

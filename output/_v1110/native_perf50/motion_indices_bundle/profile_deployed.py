"""Refresh the accepted deployment profile after all formal timing has ended."""
import hashlib
import json
from pathlib import Path
import runpy
import sys
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
EXPECTED='7a57d09b81ba62fcd985fbb14a5999c72ff550ba328d5cae3add6167e4fbc058'

def main():
    process=psutil.Process();process.nice(psutil.NORMAL_PRIORITY_CLASS)
    assert psutil.cpu_count()==8;process.cpu_affinity(list(range(8)))
    dll=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    assert hashlib.sha256(dll.read_bytes()).hexdigest()==EXPECTED
    assert json.loads((WORK/'post_install_verification.json').read_bytes())['passed']
    out=WORK/'profile_depth64.json';assert not out.exists()
    sys.argv=[str(STAGE/'profile_native_windows.py'),'--dll',str(dll),'--corpus','--min-samples','2000','--max-depth','64','--full-output','--instruction-locations','--out',str(out)]
    runpy.run_path(str(STAGE/'profile_native_windows.py'),run_name='__main__')
    profile=json.loads(out.read_bytes())
    roots=sum(row['samples'] for row in profile['resolved_stacks'] if any('run_one_internal' in name for name in row['functions']))
    assert roots>=1000 and profile['dll_sha256']==EXPECTED and profile['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert hashlib.sha256(dll.read_bytes()).hexdigest()==EXPECTED
    report=dict(dll_sha256=EXPECTED,samples=profile['samples'],valid_replay_roots=roots,normal_priority_all8=True,after_deployment_and_all_formal_timing=True,report_sha256=hashlib.sha256(out.read_bytes()).hexdigest())
    (WORK/'profile_receipt.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report))

if __name__=='__main__':main()

"""Check new dispatch coverage together with the fixed200 result signature."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
from bench_native_corpus import STAGE,load_simulator,measure,prepare,select_cases

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True)
    args=p.parse_args()
    sim=load_simulator(args.dll);signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    audit(1);before=[stat(i) for i in range(6)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(6)]
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(args.dll.read_bytes()).hexdigest(),
        'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
        'coverage':dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),counts))}
    args.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))
    assert all(counts[i]>0 for i in (0,1,2)) and counts[4]==0,report

if __name__=='__main__':main()

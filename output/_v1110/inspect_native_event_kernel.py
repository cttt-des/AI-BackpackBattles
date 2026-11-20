"""Validate typed receiver assumptions and actual native-path coverage."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
from bench_native_corpus import STAGE,load_simulator,measure,prepare,select_cases

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True);p.add_argument('--audit',action='store_true');a=p.parse_args()
    sim=load_simulator(a.dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_event_audit;audit.argtypes=[ctypes.c_int];audit.restype=None
    stat=sim.lib.gd_diag_native_event_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    audit(a.audit);before=[stat(i) for i in range(5)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(5)]
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    report={'diagnostic_only':True,'audit':a.audit,'dll_sha256':hashlib.sha256(a.dll.read_bytes()).hexdigest(),
            'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
            'coverage':dict(zip(('event_bus','take_damage','temporary_buff','create_event','type_mismatch'),counts,strict=True))}
    a.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(report,indent=2))
    assert all(x>0 for x in counts[:4]) and counts[4]==0,report

if __name__=='__main__':main()

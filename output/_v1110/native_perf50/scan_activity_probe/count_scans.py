"""Observe original eligibility decisions in the fixed200, with golden hashes."""
import ctypes
import hashlib
import json
from pathlib import Path
import sys
STAGE=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(STAGE))
from bench_native_corpus import load_simulator,measure,prepare,select_cases

def main():
    work=Path(__file__).resolve().parent
    dll=work/'scan_activity.dll'
    sim=load_simulator(dll)
    stat=sim.lib.gd_diag_native_scan_stat
    stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    before=[stat(i) for i in range(11)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(11)]
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    names=['buff_scan_calls','buff_entries','buff_ticks','buff_nonbool_flags','buff_full_chunks8',
           'buff_all_inactive_chunks8','items_scanned','items_with_timers','gem_slots_scanned',
           'gem_objects_scanned','gems_with_timers']
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
        'counts':dict(zip(names,counts)),
        'note':'No eligibility is cached. Counts follow original live reads and callbacks; this build is not a timing candidate.'}
    (work/'scan_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

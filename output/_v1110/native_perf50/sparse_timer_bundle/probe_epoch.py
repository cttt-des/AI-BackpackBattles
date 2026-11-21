"""Read the existing exported TLS epoch without changing the measured DLL."""
import ctypes
import hashlib
import json
from pathlib import Path
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from bench_native_corpus import load_simulator,prepare,select_cases,measure

class State(ctypes.Structure):
    _fields_=[('epoch',ctypes.c_uint64),('depth',ctypes.c_uint),('sorting',ctypes.c_uint)]

def main():
    dll=WORK/'bundle.dll'
    sim=load_simulator(dll)
    state=getattr(sim.lib,'_ZN2gd23native_timer_scan_stateEv')
    state.argtypes=[];state.restype=ctypes.POINTER(State)
    signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    before=state().contents.epoch
    result=measure(sim,jobs,1,0,continuous=True)
    after=state().contents
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert after.depth==after.sorting==0 and after.epoch>=before
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
        'epoch_before':before,'epoch_after':after.epoch,'invalidations':after.epoch-before,
        'reference_fixed200_character_timer_passes':386704,
        'invalidations_per_character_timer_pass':(after.epoch-before)/386704,
        'scope_depth_after':after.depth,'sorting_depth_after':after.sorting,
        'interpretation':'Epoch increments include assembly, tracked mutations and unknown/unresolved callbacks. This count is not an exact rebuild count or a speed measurement.'}
    (WORK/'epoch_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

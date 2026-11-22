"""Check actual prototype coverage and the fixed200 original result signature."""
import ctypes
import hashlib
import json
import sys
from prepare_native_targeted_timers import STAGE,WORK,BASE,EXPECTED,sha
from bench_native_corpus import load_simulator,measure,prepare,select_cases

FIELDS=('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries')

def main():
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_targeted_timer_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[stat(i) for i in range(len(FIELDS))]
    result=measure(sim,jobs,1,0,continuous=True)
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256'] and result['matched_original_terminal']==200
    counts=dict(zip(FIELDS,[stat(i)-before[i] for i in range(len(FIELDS))]))
    report=dict(diagnostic_only=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,coverage=counts,
        no_throughput_claim=True,original_deployed_dll_unchanged=sha(BASE/'libgdcore.dll')==EXPECTED)
    path=WORK/('fixed200_coverage_revision2.json' if '--revision2' in sys.argv else 'fixed200_coverage.json')
    assert not path.exists();path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))
    assert counts['indexed_passes']>0 and counts['cache_hits']>0 and counts['indexed_owners']>0

if __name__=='__main__':main()

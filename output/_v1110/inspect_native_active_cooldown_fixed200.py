"""Confirm real indexed coverage and old signatures; diagnostic timings are discarded."""
import ctypes
import hashlib
import json
from prepare_native_active_cooldowns import STAGE,BASE,WORK,EXPECTED,sha
from bench_native_corpus import load_simulator,measure,prepare,select_cases

FIELDS=('indexed_phases','rebuilds','cache_hits','indexed_owners','build_fallbacks','same_pass_resumes','eligibility_changes','build_slots','build_active_owners','reserved')
TIMER_FIELDS=('indexed_phases','rebuilds','cache_hits','indexed_owners','fallbacks','same_pass_resumes','structure_changes','build_slots','build_active_owners','unknown')

def main():
    out=WORK/'fixed200_coverage.json';assert not out.exists()
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    funcs=[]
    for symbol in ['gd_diag_native_active_cooldown_stat','gd_diag_native_targeted_timer_stat']:
        fn=getattr(sim.lib,symbol);fn.argtypes=[ctypes.c_uint];fn.restype=ctypes.c_uint64;funcs.append(fn)
    before=[[fn(i) for i in range(10)] for fn in funcs]
    result=measure(sim,jobs,1,0,continuous=True)
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256'] and result['matched_original_terminal']==200
    stats=[dict(zip(fields,[fn(i)-old[i] for i in range(10)])) for fields,fn,old in zip([FIELDS,TIMER_FIELDS],funcs,before)]
    assert stats[0]['indexed_phases']>0 and stats[0]['cache_hits']>0 and stats[0]['indexed_owners']>0 and stats[0]['same_pass_resumes']>0
    # Cooldown eligibility changes must not force the deployed timer-owner index to rebuild.
    assert stats[1]['rebuilds']==400 and stats[1]['cache_hits']==386304
    report=dict(passed=True,diagnostic_only=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        cooldown=stats[0],timer=stats[1],no_throughput_claim=True,production_unchanged=sha(BASE/'libgdcore.dll')==EXPECTED)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()

"""Actual fixed200 replay coverage gate before spending fresh PGO cost."""
import argparse,ctypes,json,runpy,sys
from pathlib import Path
import psutil
from prepare_timeline_round import STAGE,WORK,sha,save
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--formal',action='store_true');a=parser.parse_args();tag='formal' if a.formal else 'prototype';dll=WORK/('bundle.dll' if a.formal else 'prototype.dll');report=WORK/(tag+'_real200.json');assert not report.exists();psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    lib=ctypes.CDLL(str(dll));enable=lib.gd_diag_native_timeline_collect;enable.argtypes=[ctypes.c_int];enable.restype=None;enable(1);stat=lib.gd_diag_native_timeline_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64;before=[stat(i) for i in range(4)]
    sys.argv=[str(STAGE/'bench_native_corpus.py'),'--dll',str(dll),'--workers','1','--out',str(report)];runpy.run_path(str(STAGE/'bench_native_corpus.py'),run_name='__main__')
    r=json.loads(report.read_bytes());ref=json.loads((WORK/'fixed200_reference.json').read_bytes());assert r['dll_sha256']==sha(dll)
    for k in ['inputs_sha256','results_sha256']:assert r[k]==ref[k]
    counts=dict(zip(['motion_entries','typed_visual_steps','typed_charge_steps','delay_entries'],[stat(i)-before[i] for i in range(4)]));assert all(v>0 for v in counts.values()),counts
    save(tag+'_real200_coverage.json',dict(passed=True,dll_sha256=sha(dll),source_manifest_sha256=sha(WORK/'source_before_build.json'),cases=200,coverage=counts,report_sha256=sha(report),fixed_reference_SHA_verified=True,diagnostic_not_speed_evidence=True));print('Real200 path coverage passed',counts,flush=True)
if __name__=='__main__':main()

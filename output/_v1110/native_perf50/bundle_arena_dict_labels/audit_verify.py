"""Run the unchanged strict verifier with typed-receiver auditing enabled."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import sys

STAGE=Path(__file__).resolve().parents[2]
args=sys.argv[1:]
dll=Path(args[args.index('--dll')+1]).resolve()
out=Path(args[args.index('--out')+1]).resolve()
lib=ctypes.CDLL(str(dll))
audit=lib.gd_diag_native_event_audit
audit.argtypes=[ctypes.c_int];audit.restype=None
stat=lib.gd_diag_native_event_stat
stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
audit(1)
before=[stat(i) for i in range(5)]
target=STAGE/'sim_native/tools/_cpp_verify_events.py'
sys.argv=[str(target),*args]
exit_code=0
try:
    runpy.run_path(str(target),run_name='__main__')
except SystemExit as exc:
    exit_code=exc.code
counts=[stat(i)-before[i] for i in range(5)]
report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'verifier_unchanged':str(target),'verifier_exit_code':exit_code,
        'coverage':dict(zip(('event_bus','take_damage','temporary_buff','create_event','type_mismatch'),counts))}
(out/'native_type_audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
assert counts[0]>0 and counts[3]>0 and counts[4]==0,report
raise SystemExit(exit_code)

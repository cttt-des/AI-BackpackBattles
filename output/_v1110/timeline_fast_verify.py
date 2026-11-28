"""Run the unchanged original-event verifier with typed timeline paths enabled."""
import ctypes,hashlib,json,runpy,sys
from pathlib import Path
import psutil
STAGE=Path(__file__).resolve().parent
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
args=sys.argv[1:];dll=Path(args[args.index('--dll')+1]).resolve();out=Path(args[args.index('--out')+1]).resolve();lib=ctypes.CDLL(str(dll))
for name in ('gd_diag_native_event_audit','gd_diag_native_resolved_audit'):
    fn=getattr(lib,name);fn.argtypes=[ctypes.c_int];fn.restype=None;fn(0)
enable=lib.gd_diag_native_timeline_collect;enable.argtypes=[ctypes.c_int];enable.restype=None;enable(1)
stat=lib.gd_diag_native_timeline_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
before=[stat(i) for i in range(4)];target=STAGE/'sim_native/tools/_cpp_verify_events.py';sys.argv=[str(target),*args];code=0
try:runpy.run_path(str(target),run_name='__main__')
except SystemExit as exc:code=exc.code
counts=[stat(i)-before[i] for i in range(4)]
(out/'timeline_coverage.json').write_text(json.dumps(dict(verifier_exit_code=code,dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(),counts=dict(zip(['motion_entries','typed_visual_steps','typed_charge_steps','delay_entries'],counts)),verifier_source_sha256=hashlib.sha256(target.read_bytes()).hexdigest(),original_strict_verifier_unchanged=True),indent=2)+'\n',encoding='utf8')
raise SystemExit(code)

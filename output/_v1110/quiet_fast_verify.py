"""Unchanged strict event verifier with the release fast path exercised."""
import ctypes,hashlib,json,runpy,sys
from pathlib import Path
STAGE=Path(__file__).resolve().parent
args=sys.argv[1:];dll=Path(args[args.index('--dll')+1]).resolve();out=Path(args[args.index('--out')+1]).resolve()
lib=ctypes.CDLL(str(dll))
for name in ('gd_diag_native_event_audit','gd_diag_native_resolved_audit'):
    fn=getattr(lib,name);fn.argtypes=[ctypes.c_int];fn.restype=None;fn(0)
enable=lib.gd_diag_quiet_core_enable;enable.argtypes=[ctypes.c_int];enable.restype=None;enable(1)
stat=lib.gd_diag_quiet_core_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
before=[stat(i) for i in range(5)];target=STAGE/'sim_native/tools/_cpp_verify_events.py';sys.argv=[str(target),*args]
code=0
try:runpy.run_path(str(target),run_name='__main__')
except SystemExit as exc:code=exc.code
counts=[stat(i)-before[i] for i in range(5)]
(out/'quiet_core_coverage.json').write_text(json.dumps(dict(verifier_exit_code=code,dll_sha256=hashlib.sha256(dll.read_bytes()).hexdigest(),counts=dict(zip(['attempts','rejected','segments','frames','lanes'],counts)),verifier_source_sha256=hashlib.sha256(target.read_bytes()).hexdigest(),original_strict_verifier_unchanged=True),indent=2)+'\n',encoding='utf8')
raise SystemExit(code)

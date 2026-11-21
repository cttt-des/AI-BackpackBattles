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
resolved_audit=lib.gd_diag_native_resolved_audit
resolved_audit.argtypes=[ctypes.c_int];resolved_audit.restype=None
resolved_stat=lib.gd_diag_native_resolved_stat
resolved_stat.argtypes=[ctypes.c_uint];resolved_stat.restype=ctypes.c_uint64
property_stat=lib.gd_diag_native_property_stat;property_stat.argtypes=[ctypes.c_uint];property_stat.restype=ctypes.c_uint64
property_before=[property_stat(i) for i in range(2)]
resolved_audit(1);resolved_before=[resolved_stat(i) for i in range(6)]
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
resolved_counts=[resolved_stat(i)-resolved_before[i] for i in range(6)]
resolved_report={'diagnostic_only':True,'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,
    'coverage':dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),resolved_counts))}
(out/'native_resolved_audit.json').write_text(json.dumps(resolved_report,indent=2)+'\n',encoding='utf8',newline='\n')
assert resolved_counts[0]>0 and resolved_counts[4]==0,resolved_report
property_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('field_hits','selected_fallback'),[property_stat(i)-property_before[i] for i in range(2)]))}
(out/'native_property_audit.json').write_text(json.dumps(property_report,indent=2)+'\n',encoding='utf8')
raise SystemExit(exit_code)

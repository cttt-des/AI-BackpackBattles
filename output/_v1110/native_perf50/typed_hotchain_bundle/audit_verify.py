"""Run the unchanged strict verifier with identity-receiver auditing enabled."""
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
type_constructor_stat=lib.gd_diag_native_type_constructor_stat;type_constructor_stat.argtypes=[ctypes.c_uint];type_constructor_stat.restype=ctypes.c_uint64
type_constructor_before=[type_constructor_stat(i) for i in range(4)]
hot_slot_stat=lib.gd_diag_native_hot_slot_stat;hot_slot_stat.argtypes=[ctypes.c_uint];hot_slot_stat.restype=ctypes.c_uint64
hot_slot_before=[hot_slot_stat(i) for i in range(2)]
identity_stat=lib.gd_diag_native_event_identity_stat;identity_stat.argtypes=[ctypes.c_uint];identity_stat.restype=ctypes.c_uint64
identity_before=[identity_stat(i) for i in range(4)]
lazy_stat=lib.gd_diag_native_lazy_diagnostic_stat;lazy_stat.argtypes=[ctypes.c_uint];lazy_stat.restype=ctypes.c_uint64
lazy_before=[lazy_stat(i) for i in range(14)]
constant_stat=lib.gd_diag_native_static_collection_stat;constant_stat.argtypes=[ctypes.c_uint];constant_stat.restype=ctypes.c_uint64
constant_before=[constant_stat(i) for i in range(3)]
setup_stat=lib.gd_diag_native_static_setup_stat;setup_stat.argtypes=[ctypes.c_uint];setup_stat.restype=ctypes.c_uint64
setup_before=[setup_stat(i) for i in range(4)]
chain_stat=lib.gd_diag_native_dispatch_chain_stat;chain_stat.argtypes=[ctypes.c_uint];chain_stat.restype=ctypes.c_uint64
chain_before=[chain_stat(i) for i in range(4)]
spatial_stat=lib.gd_diag_native_spatial_stat;spatial_stat.argtypes=[ctypes.c_uint];spatial_stat.restype=ctypes.c_uint64
spatial_before=[spatial_stat(i) for i in range(4)]
motion_stat=lib.gd_diag_native_motion_index_stat;motion_stat.argtypes=[ctypes.c_uint];motion_stat.restype=ctypes.c_uint64
motion_before=[motion_stat(i) for i in range(3)]
typed_stat=lib.gd_diag_native_typed_damage_stat;typed_stat.argtypes=[ctypes.c_uint];typed_stat.restype=ctypes.c_uint64
typed_before=[typed_stat(i) for i in range(12)]
targeted_stat=lib.gd_diag_native_targeted_timer_stat;targeted_stat.argtypes=[ctypes.c_uint];targeted_stat.restype=ctypes.c_uint64
targeted_before=[targeted_stat(i) for i in range(10)]
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
type_constructor_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),[type_constructor_stat(i)-type_constructor_before[i] for i in range(4)]))}
(out/'native_type_constructor_audit.json').write_text(json.dumps(type_constructor_report,indent=2)+'\n',encoding='utf8')
assert type_constructor_report['coverage']['type_hits']>0 and type_constructor_report['coverage']['fused_initializations']>0
hot_slot_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('new_method_hits','new_field_hits'),[hot_slot_stat(i)-hot_slot_before[i] for i in range(2)]))}
(out/'native_hot_slot_audit.json').write_text(json.dumps(hot_slot_report,indent=2)+'\n',encoding='utf8')
identity_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('fast_identities','fallbacks','fast_emissions','emission_fallbacks'),[identity_stat(i)-identity_before[i] for i in range(4)]))}
(out/'native_event_identity_audit.json').write_text(json.dumps(identity_report,indent=2)+'\n',encoding='utf8')
lazy_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[lazy_stat(i)-lazy_before[i] for i in range(14)]}
(out/'native_lazy_diagnostic_audit.json').write_text(json.dumps(lazy_report,indent=2)+'\n',encoding='utf8')
constant_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[constant_stat(i)-constant_before[i] for i in range(3)]}
(out/'native_static_collection_audit.json').write_text(json.dumps(constant_report,indent=2)+'\n',encoding='utf8')
setup_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[setup_stat(i)-setup_before[i] for i in range(4)]}
(out/'native_static_setup_audit.json').write_text(json.dumps(setup_report,indent=2)+'\n',encoding='utf8')
chain_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[chain_stat(i)-chain_before[i] for i in range(4)]}
(out/'native_dispatch_chain_audit.json').write_text(json.dumps(chain_report,indent=2)+'\n',encoding='utf8')
spatial_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[spatial_stat(i)-spatial_before[i] for i in range(4)]}
(out/'native_spatial_audit.json').write_text(json.dumps(spatial_report,indent=2)+'\n',encoding='utf8')
motion_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[motion_stat(i)-motion_before[i] for i in range(3)]}
(out/'native_motion_index_audit.json').write_text(json.dumps(motion_report,indent=2)+'\n',encoding='utf8')
targeted_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[targeted_stat(i)-targeted_before[i] for i in range(10)]}
(out/'native_targeted_timer_audit.json').write_text(json.dumps(targeted_report,indent=2)+'\n',encoding='utf8')
(out/'native_typed_damage_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[typed_stat(i)-typed_before[i] for i in range(12)]),indent=2)+'\n',encoding='utf8')
raise SystemExit(exit_code)

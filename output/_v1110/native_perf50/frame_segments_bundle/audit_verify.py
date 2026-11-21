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
type_constructor_stat=lib.gd_diag_native_type_constructor_stat;type_constructor_stat.argtypes=[ctypes.c_uint];type_constructor_stat.restype=ctypes.c_uint64
type_constructor_before=[type_constructor_stat(i) for i in range(4)]
hot_slot_stat=lib.gd_diag_native_hot_slot_stat;hot_slot_stat.argtypes=[ctypes.c_uint];hot_slot_stat.restype=ctypes.c_uint64
hot_slot_before=[hot_slot_stat(i) for i in range(2)]
typed_read_stat=lib.gd_diag_native_typed_read_stat;typed_read_stat.argtypes=[ctypes.c_uint];typed_read_stat.restype=ctypes.c_uint64
typed_read_before=[typed_read_stat(i) for i in range(2)]
segment=lib.gd_diag_native_frame_segment_stat;segment.argtypes=[ctypes.c_uint];segment.restype=ctypes.c_uint64
segment_before=[segment(i) for i in range(17)]
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
typed_read_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('property_reads','pure_method_reads'),[typed_read_stat(i)-typed_read_before[i] for i in range(2)]))}
(out/'native_typed_read_audit.json').write_text(json.dumps(typed_read_report,indent=2)+'\n',encoding='utf8')
segment_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('fast_items', 'stun_misses', 'stun_hits', 'speed_misses', 'speed_hits', 'original_fallbacks', 'gem_character_barriers', 'cooldown_hook_barriers', 'trigger_barriers', 'timer_passes', 'timer_original_parents', 'timer_chunk_attempts', 'timer_chunks_skipped', 'timer_parents_skipped', 'timer_live_parents', 'timer_probe_parents', 'timer_probe_sockets'),[segment(i)-segment_before[i] for i in range(17)]))}
(out/'native_frame_segment_audit.json').write_text(json.dumps(segment_report,indent=2)+'\n',encoding='utf8')
raise SystemExit(exit_code)

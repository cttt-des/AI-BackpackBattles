"""Prepare the fresh loop candidate and unchanged publication gates."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/typed_read_bundle'
WORK=STAGE/'native_perf50/frame_segments_bundle'
KEYS=('fast_items','stun_misses','stun_hits','speed_misses','speed_hits','original_fallbacks',
      'gem_character_barriers','cooldown_hook_barriers','trigger_barriers','timer_passes',
      'timer_original_parents','timer_chunk_attempts','timer_chunks_skipped','timer_parents_skipped',
      'timer_live_parents','timer_probe_parents','timer_probe_sockets')


def main():
    assert json.loads((WORK/'frame_preflight.json').read_bytes())['passed']
    assert json.loads((WORK/'timer_preflight.json').read_bytes())['passed']
    assert not (WORK/'build_bundle.py').exists()
    for path in OLD.glob('*.py'):
        text=path.read_text('utf8').replace('typed_read_bundle','frame_segments_bundle').replace('native-typed-read-','native-frame-segments-')
        if path.name=='resume_build.py':
            text=text.replace("exports.add('gd_diag_native_typed_read_stat')", "exports.add('gd_diag_native_typed_read_stat')\n    exports.add('gd_diag_native_frame_segment_stat')")
        if path.name=='inspect_variant.py':
            text=text.replace('    audit(1);before=', "    segment=sim.lib.gd_diag_native_frame_segment_stat;segment.argtypes=[ctypes.c_uint];segment.restype=ctypes.c_uint64\n    segment_before=[segment(i) for i in range(17)]\n    audit(1);before=")
            text=text.replace("    assert all(value>0 for value in report['hot_slot_coverage'].values())", f"    report['frame_segment_coverage']=dict(zip({KEYS!r},[segment(i)-segment_before[i] for i in range(17)]))\n    for key in ('fast_items','stun_hits','speed_hits','timer_chunks_skipped'):assert report['frame_segment_coverage'][key]>0,key\n    assert report['frame_segment_coverage']['timer_original_parents']==report['frame_segment_coverage']['timer_parents_skipped']+report['frame_segment_coverage']['timer_live_parents']\n    assert all(value>0 for value in report['hot_slot_coverage'].values())")
        if path.name=='audit_verify.py':
            text=text.replace('typed_read_before=[typed_read_stat(i) for i in range(2)]', 'typed_read_before=[typed_read_stat(i) for i in range(2)]\nsegment=lib.gd_diag_native_frame_segment_stat;segment.argtypes=[ctypes.c_uint];segment.restype=ctypes.c_uint64\nsegment_before=[segment(i) for i in range(17)]')
            text=text.replace('raise SystemExit(exit_code)', f"segment_report={{'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip({KEYS!r},[segment(i)-segment_before[i] for i in range(17)]))}}\n(out/'native_frame_segment_audit.json').write_text(json.dumps(segment_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if path.name=='finish_gate.py':
            text=text.replace('typed_counts=[0,0]','typed_counts=[0,0];segment_counts=[0]*17')
            text=text.replace('        summary=json.loads', f"        segment=json.loads((root/'native_frame_segment_audit.json').read_bytes());assert segment['dll_sha256']==dll and segment['verifier_exit_code']==0\n        for i,key in enumerate({KEYS!r}):segment_counts[i]+=segment['coverage'][key]\n        summary=json.loads",1)
            text=text.replace('    assert all(value>0 for value in typed_counts)', '    assert all(segment_counts[i]>0 for i in (0,2,4,12))\n    assert segment_counts[10]==segment_counts[13]+segment_counts[14]\n    assert all(value>0 for value in typed_counts)')
            text=text.replace("'typed_read_coverage':dict", f"'frame_segment_coverage':dict(zip({KEYS!r},segment_counts)),\n        'typed_read_coverage':dict",1)
        if path.name=='validate_then_compare.py':
            text=text.replace("    run('verify_resolved.py','verify.log')", "    run('verify_frame_segments.py','frame_segment_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='verify_installed.py':
            text=text.replace("'typed_read_test.json','property_test.json'", "'typed_read_test.json','frame_segment_tests.json','property_test.json'")
            text=text.replace("    assert all(value>0 for value in audit['typed_read_coverage'].values())", "    assert all(audit['frame_segment_coverage'][key]>0 for key in ('fast_items','stun_hits','speed_hits','timer_chunks_skipped'))\n    assert all(value>0 for value in audit['typed_read_coverage'].values())")
            text=text.replace("'typed_read_coverage':audit['typed_read_coverage'],", "'typed_read_coverage':audit['typed_read_coverage'],'frame_segment_coverage':audit['frame_segment_coverage'],")
        if path.name=='save_checkpoint.py':
            text=text.replace("'native_typed_read_audit.json','summary.json'", "'native_typed_read_audit.json','native_frame_segment_audit.json','summary.json'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_typed_read_bundle.py','setup_typed_read_bundle.py','prototype_native_frame_segments_bundle.py','setup_frame_segments_bundle.py','run_frame_segments_preflight.py','test_native_frame_segments.cpp','test_native_timer_chunks.cpp','prototype_native_scalar_math_bundle.py','setup_scalar_math_bundle.py','setup_scalar_math_qualification.py','test_native_numeric_math.cpp','prototype_native_scalar_math_ordered_bundle.py','setup_scalar_math_ordered_bundle.py','test_native_numeric_math_ordered.cpp','test_native_nan_order.cpp'))\n    for label in ('typed_read_bundle','scalar_math_bundle','scalar_math_ordered_bundle'):\n        prior=WORK.parent/label\n        paths.update(p for p in prior.iterdir() if p.is_file())\n        paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: deploy typed pure reads with full replay validation','perf: reuse callback-bounded character reads and skip empty timer chunks')
            text=text.replace('backup: preserve verified typed reads and all strict receipts','backup: preserve verified frame segments and rejected numeric experiments')
        ast.parse(text,filename=path.name)
        (WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    # Actual source provenance for the regeneration helper remains the retained
    # typed-read predecessor, rather than the new work directory itself.
    p=WORK/'prepare_regeneration.py';text=p.read_text('utf8')
    assert "OLD=WORK.parent/'hot_coverage_bundle'" in text or "OLD=WORK.parent/'frame_segments_bundle'" in text
    text=text.replace("OLD=WORK.parent/'frame_segments_bundle'", "OLD=WORK.parent/'typed_read_bundle'")
    # The typed predecessor originally inherited hot coverage; use its complete
    # manifest and corresponding helper when preserving intermediate states.
    text=text.replace("OLD=WORK.parent/'hot_coverage_bundle'", "OLD=WORK.parent/'typed_read_bundle'")
    text=text.replace('native_perf50/hot_coverage_bundle','native_perf50/typed_read_bundle')
    p.write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan['components']=['retained typed pure reads','callback-bounded character stun/shared speed snapshots','stateless short-circuit timer chunks8']
    plan['new_object_or_context_layout']=False
    plan['preflight']={'frame_cases':6912,'timer_cases':9554,'actual_deployed_dll_as_oracle':True}
    plan['arithmetic_inline_package_removed']=True
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared frame-segment candidate with fixed200/2604/24-batch gates')


if __name__=='__main__':main()

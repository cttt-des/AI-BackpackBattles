"""Compare every event hash with the actual deployment and aggregate audits."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def main():
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'compare_native_event_receipts.py'),
        '--baseline',str(WORK.parent/'hot_coverage_bundle/bundle_full_gate.json'),
        '--candidate',str(WORK/'bundle_full_gate.json'),
        '--baseline-prefix','native_hot_coverage_bundle_bundle_',
        '--candidate-prefix','native_frame_segments_bundle_bundle_',
        '--out',str(WORK/'bundle_vs_deployed_hashes.json')],check=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict.fromkeys(fields,0);fights=0;old_mismatches=0;receipts=[];property_counts=[0,0];tc_counts=[0]*4;hot_counts=[0,0];typed_counts=[0,0];segment_counts=[0]*17
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    for folder in sorted(STAGE.glob('native_frame_segments_bundle_bundle_*')):
        if not folder.is_dir():continue
        root=folder/'cpp' if (folder/'cpp').is_dir() else folder
        audit=json.loads((root/'native_resolved_audit.json').read_bytes())
        legacy=json.loads((root/'native_type_audit.json').read_bytes())
        prop=json.loads((root/'native_property_audit.json').read_bytes());assert prop['dll_sha256']==dll and prop['verifier_exit_code']==0
        property_counts[0]+=prop['coverage']['field_hits'];property_counts[1]+=prop['coverage']['selected_fallback']
        tc=json.loads((root/'native_type_constructor_audit.json').read_bytes());assert tc['dll_sha256']==dll and tc['verifier_exit_code']==0
        for i,key in enumerate(('type_hits','type_fallback','fused_initializations','factory_fallback')):tc_counts[i]+=tc['coverage'][key]
        hot=json.loads((root/'native_hot_slot_audit.json').read_bytes());assert hot['dll_sha256']==dll and hot['verifier_exit_code']==0
        for i,key in enumerate(('new_method_hits','new_field_hits')):hot_counts[i]+=hot['coverage'][key]
        typed=json.loads((root/'native_typed_read_audit.json').read_bytes());assert typed['dll_sha256']==dll and typed['verifier_exit_code']==0
        for i,key in enumerate(('property_reads','pure_method_reads')):typed_counts[i]+=typed['coverage'][key]
        segment=json.loads((root/'native_frame_segment_audit.json').read_bytes());assert segment['dll_sha256']==dll and segment['verifier_exit_code']==0
        for i,key in enumerate(('fast_items', 'stun_misses', 'stun_hits', 'speed_misses', 'speed_hits', 'original_fallbacks', 'gem_character_barriers', 'cooldown_hook_barriers', 'trigger_barriers', 'timer_passes', 'timer_original_parents', 'timer_chunk_attempts', 'timer_chunks_skipped', 'timer_parents_skipped', 'timer_live_parents', 'timer_probe_parents', 'timer_probe_sockets')):segment_counts[i]+=segment['coverage'][key]
        summary=json.loads((root/'summary.json').read_bytes())
        assert audit['dll_sha256']==legacy['dll_sha256']==summary['dll_sha256']==dll
        assert audit['verifier_exit_code']==legacy['verifier_exit_code']==0
        assert summary['passed']==summary['total']
        fights+=summary['total'];receipts.append(str(root))
        for field in fields:counts[field]+=audit['coverage'][field]
        old_mismatches+=legacy['coverage']['type_mismatch']
    assert all(segment_counts[i]>0 for i in (0,2,4,12))
    assert segment_counts[10]==segment_counts[13]+segment_counts[14]
    assert all(value>0 for value in typed_counts) and typed_counts[0]==property_counts[0]
    assert all(value>0 for value in hot_counts)
    assert property_counts[0]>0 and tc_counts[0]>0 and tc_counts[2]>0
    assert fights==2604 and counts['audit_mismatch']==old_mismatches==0
    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,
        'frame_segment_coverage':dict(zip(('fast_items', 'stun_misses', 'stun_hits', 'speed_misses', 'speed_hits', 'original_fallbacks', 'gem_character_barriers', 'cooldown_hook_barriers', 'trigger_barriers', 'timer_passes', 'timer_original_parents', 'timer_chunk_attempts', 'timer_chunks_skipped', 'timer_parents_skipped', 'timer_live_parents', 'timer_probe_parents', 'timer_probe_sockets'),segment_counts)),
        'typed_read_coverage':dict(zip(('property_reads','pure_method_reads'),typed_counts)),
        'hot_slot_coverage':dict(zip(('new_method_hits','new_field_hits'),hot_counts)),
        'type_constructor_coverage':dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),tc_counts)),
        'old_event_kernel_type_mismatches':old_mismatches,'receipts':receipts,'property_coverage':dict(zip(('field_hits','selected_fallback'),property_counts))}
    (WORK/'full_type_audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

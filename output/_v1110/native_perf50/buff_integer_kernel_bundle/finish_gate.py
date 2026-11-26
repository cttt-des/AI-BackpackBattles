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
        '--baseline',str(WORK.parent/'container_builtins_bundle/bundle_full_gate.json'),
        '--candidate',str(WORK/'bundle_full_gate.json'),
        '--baseline-prefix','native_container_builtins_bundle_bundle_',
        '--candidate-prefix','native_buff_integer_kernel_bundle_bundle_',
        '--out',str(WORK/'bundle_vs_deployed_hashes.json')],check=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict.fromkeys(fields,0);fights=0;old_mismatches=0;receipts=[];property_counts=[0,0];tc_counts=[0]*4;hot_counts=[0,0];identity_counts=[0]*4
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    lazy_counts=[0]*14
    constant_counts=[0]*3
    setup_counts=[0]*4
    chain_counts=[0]*4
    spatial_counts=[0]*4
    motion_counts=[0]*3
    targeted_counts=[0]*10
    active_counts=[0]*10
    grid_counts=[0]*6
    object_counts=[0]*2
    for folder in sorted(STAGE.glob('native_buff_integer_kernel_bundle_bundle_*')):
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
        identity=json.loads((root/'native_event_identity_audit.json').read_bytes());assert identity['dll_sha256']==dll and identity['verifier_exit_code']==0
        for i,key in enumerate(('fast_identities','fallbacks','fast_emissions','emission_fallbacks')):identity_counts[i]+=identity['coverage'][key]
        lazy=json.loads((root/'native_lazy_diagnostic_audit.json').read_bytes());assert lazy['dll_sha256']==dll and lazy['verifier_exit_code']==0
        for i,value in enumerate(lazy['counts']):lazy_counts[i]+=value
        constant=json.loads((root/'native_static_collection_audit.json').read_bytes());assert constant['dll_sha256']==dll and constant['verifier_exit_code']==0
        for i,value in enumerate(constant['counts']):constant_counts[i]+=value
        setup=json.loads((root/'native_static_setup_audit.json').read_bytes());assert setup['dll_sha256']==dll and setup['verifier_exit_code']==0
        for i,value in enumerate(setup['counts']):setup_counts[i]+=value
        chain=json.loads((root/'native_dispatch_chain_audit.json').read_bytes());assert chain['dll_sha256']==dll and chain['verifier_exit_code']==0
        for i,value in enumerate(chain['counts']):chain_counts[i]+=value
        spatial=json.loads((root/'native_spatial_audit.json').read_bytes());assert spatial['dll_sha256']==dll and spatial['verifier_exit_code']==0
        for i,value in enumerate(spatial['counts']):spatial_counts[i]+=value
        motion=json.loads((root/'native_motion_index_audit.json').read_bytes());assert motion['dll_sha256']==dll and motion['verifier_exit_code']==0 and len(motion['counts'])==3
        for i,value in enumerate(motion['counts']):motion_counts[i]+=value
        targeted=json.loads((root/'native_targeted_timer_audit.json').read_bytes());assert targeted['dll_sha256']==dll and targeted['verifier_exit_code']==0 and len(targeted['counts'])==10
        for i,value in enumerate(targeted['counts']):targeted_counts[i]+=value
        active=json.loads((root/'native_active_cooldown_audit.json').read_bytes());assert active['dll_sha256']==dll and active['verifier_exit_code']==0 and len(active['counts'])==10
        for i,value in enumerate(active['counts']):active_counts[i]+=value
        grid=json.loads((root/'native_integer_grid_audit.json').read_bytes());assert grid['dll_sha256']==dll and grid['verifier_exit_code']==0 and len(grid['counts'])==6
        for i,value in enumerate(grid['counts']):grid_counts[i]+=value
        summary=json.loads((root/'summary.json').read_bytes())
        assert audit['dll_sha256']==legacy['dll_sha256']==summary['dll_sha256']==dll
        assert audit['verifier_exit_code']==legacy['verifier_exit_code']==0
        assert summary['passed']==summary['total']
        obj=json.loads((root/'native_object_route_audit.json').read_bytes())
        assert obj['dll_sha256']==dll and obj['verifier_exit_code']==0 and len(obj['counts'])==2
        for i,count in enumerate(obj['counts']):object_counts[i]+=count
        fights+=summary['total'];receipts.append(str(root))
        for field in fields:counts[field]+=audit['coverage'][field]
        old_mismatches+=legacy['coverage']['type_mismatch']
    assert identity_counts[0]>0 and identity_counts[2]>0
    assert all(value>0 for value in hot_counts)
    assert property_counts[0]>0 and tc_counts[0]>0 and tc_counts[2]>0
    assert fights==2604 and counts['audit_mismatch']==old_mismatches==0
    assert lazy_counts[0]>0 and sum(lazy_counts[2::2])>0
    assert constant_counts[0]>0 and constant_counts[2]>0
    assert all(setup_counts[i]>0 for i in (0,2,3))
    assert all(chain_counts[i]>0 for i in (0,2,3))
    assert all(spatial_counts[i]>0 for i in (0,1,2))
    assert all(value>0 for value in motion_counts) and motion_counts[2]<=motion_counts[1]
    assert grid_counts[0]>0 and grid_counts[2]>0
    assert all(active_counts[i]>0 for i in (0,1,2,3,5))
    assert all(targeted_counts[i]>0 for i in (0,1,2,3))
    baseline=json.loads((WORK.parent/'container_builtins_bundle/full_type_audit.json').read_bytes())
    assert counts==baseline['coverage'],'A spatial representation change must not skip original dispatches'
    (WORK/'legacy_counter_equivalence.json').write_text(json.dumps(dict(passed=True,baseline=baseline['coverage'],candidate=counts),indent=2)+'\n',encoding='utf8')
    assert all(n>0 for n in object_counts)
    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,'object_route_coverage':dict(zip(('instance_methods','static_context_f32'),object_counts)),
        'integer_grid_coverage':dict(zip(('fast_queries', 'ordinary_queries', 'enabled_dicts', 'rejected_dicts', 'mode_conversions', 'reserved'),grid_counts)),
        'active_cooldown_coverage':dict(zip(('indexed_phases', 'rebuilds', 'cache_hits', 'indexed_owners', 'build_fallbacks', 'same_pass_resumes', 'eligibility_changes', 'build_slots', 'build_active_owners', 'reserved'),active_counts)),
        'targeted_timer_coverage':dict(zip(('indexed_passes','rebuilds','cache_hits','indexed_owners','fallback_passes','same_pass_resumes','watched_invalidations','build_slots','build_eligible_owners','unknown_boundaries'),targeted_counts)),
        'motion_index_coverage':dict(zip(('native_runs','native_entries','kept_entries'),motion_counts)),
        'spatial_coverage':dict(zip(('lookups','hits','object_dedup','fallbacks'),spatial_counts)),
        'dispatch_chain_coverage':dict(zip(('behavior_methods','behavior_empty','behavior_probes','flat_callbacks'),chain_counts)),
        'static_setup_coverage':dict(zip(('bulk_stack_tables','ordered_stack_fallback','metric_counts','affected_loops'),setup_counts)),
        'event_identity_coverage':dict(zip(('fast_identities','fallbacks','fast_emissions','emission_fallbacks'),identity_counts)),
        'lazy_diagnostic_coverage':{str(site):{'skipped':lazy_counts[site*2],'retained':lazy_counts[site*2+1]} for site in range(7)},
        'static_collection_coverage':dict(zip(('attack_lookup','round_lookup','stack_count'),constant_counts)),
        'hot_slot_coverage':dict(zip(('new_method_hits','new_field_hits'),hot_counts)),
        'type_constructor_coverage':dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),tc_counts)),
        'old_event_kernel_type_mismatches':old_mismatches,'receipts':receipts,'property_coverage':dict(zip(('field_hits','selected_fallback'),property_counts))}
    (WORK/'full_type_audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

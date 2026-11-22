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
        '--baseline',str(WORK.parent/'spatial_bundle/bundle_full_gate.json'),
        '--candidate',str(WORK/'bundle_full_gate.json'),
        '--baseline-prefix','native_spatial_bundle_bundle_',
        '--candidate-prefix','native_damage_combo_bundle_bundle_',
        '--out',str(WORK/'bundle_vs_deployed_hashes.json')],check=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict.fromkeys(fields,0);fights=0;old_mismatches=0;receipts=[];property_counts=[0,0];tc_counts=[0]*4;hot_counts=[0,0];identity_counts=[0]*4
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    lazy_counts=[0]*14
    constant_counts=[0]*3
    setup_counts=[0]*4
    chain_counts=[0]*4
    spatial_counts=[0]*4
    damage_counts=[0]*6;legacy_damage=0
    for folder in sorted(STAGE.glob('native_damage_combo_bundle_bundle_*')):
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
        damage=json.loads((root/'native_damage_record_audit.json').read_bytes());assert damage['dll_sha256']==dll and damage['verifier_exit_code']==0
        for i,value in enumerate(damage['counts']):damage_counts[i]+=value
        legacy_damage+=legacy['coverage']['take_damage']
        summary=json.loads((root/'summary.json').read_bytes())
        assert audit['dll_sha256']==legacy['dll_sha256']==summary['dll_sha256']==dll
        assert audit['verifier_exit_code']==legacy['verifier_exit_code']==0
        assert summary['passed']==summary['total']
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
    assert all(damage_counts[i]>0 for i in (0,1,3)) and damage_counts[0]==legacy_damage
    baseline=json.loads((WORK.parent/'spatial_bundle/full_type_audit.json').read_bytes())
    assert counts==baseline['coverage'],'A spatial representation change must not skip original dispatches'
    (WORK/'legacy_counter_equivalence.json').write_text(json.dumps(dict(passed=True,baseline=baseline['coverage'],candidate=counts),indent=2)+'\n',encoding='utf8')
    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,
        'spatial_coverage':dict(zip(('lookups','hits','object_dedup','fallbacks'),spatial_counts)),
        'damage_record_coverage':dict(zip(('records','integer_flags','flag_fallback','array_types','type_fallback','classifier_fallback'),damage_counts)),
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

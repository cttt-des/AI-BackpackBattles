"""Verify deployed bytes and actual evidence for the full optimization goal."""
import hashlib
import json
import math
from pathlib import Path
import statistics
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
BASE='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
INPUT='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
RESULT='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
ROOT='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
DATA='55bdd068cf3308547de78b45abbed4bf4f57e8253fbec82313a99578defa00ae'


def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def read(name):return json.loads((WORK/name).read_bytes())


def main():
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    runtime=REPO/'dist/native_1_1_10'
    actual=sha(WORK/'bundle.dll')
    assert actual==sha(native/'libgdcore.dll')==sha(runtime/'libgdcore.dll') and actual!=BASE
    manifest=json.loads((runtime/'manifest.json').read_bytes())
    assert manifest['verified_fights']==2604 and manifest['gate_sha256']==sha(WORK/'bundle_full_gate.json')
    for name,expected in manifest['sha256'].items():assert sha(runtime/name)==expected,name
    inventory={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')}
    expected=read('source_before_build.json')
    assert len(inventory)==704
    for name,digest in inventory.items():assert digest==expected[name]==sha(WORK/'bundle_src'/name),name
    # This round changes internal dispatch rows, never any generated object layout.
    old=WORK.parent/'hot_coverage_bundle/bundle_src'
    headers=list((native/'gen/hdrs').glob('*.hpp'));assert len(headers)==674
    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers)
    assert (STAGE/'optimize_native_verified_bundle.py').read_bytes()==(WORK/'verified_bundle_pending.py').read_bytes()
    for name in ('regeneration_test.json','full_regeneration_test.json','type_constructor_test.json','hot_coverage_test.json','typed_read_test.json','frame_segment_tests.json','property_test.json','buff_chunk_differential.json','addspeed_trace_differential.json'):
        record=read(name);assert record['passed'],name
        if 'dll_sha256' in record:assert record['dll_sha256']==actual,name
    profile=read('fresh_profile_source.json')
    assert profile['dll_sha256']==actual and profile['profile_training_and_release_source_identical'] and profile['floating_options_unchanged']
    assert profile['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    gate=read('bundle_full_gate.json');hashes=read('bundle_vs_deployed_hashes.json');audit=read('full_type_audit.json')
    assert gate['complete'] and gate['dll_sha256']==actual and gate['runtime_data_sha256']==DATA
    for name,count in (('base',914),('expand',1690)):
        row=gate['cohorts'][name]
        assert row['expected']==row['recorded']==row['verified']==row['passed']==count
        assert row['winner_mismatch']==0 and not row['pending']
    assert hashes['candidate_dll_sha256']==actual and hashes['baseline_dll_sha256']==BASE
    assert hashes['unchanged_cpp_event_streams']==2604 and hashes['ordered_case_and_cpp_event_hashes_sha256']==ROOT
    sys.path.insert(0,str(STAGE))
    from compare_native_event_receipts import read_gate,reference_index,FIELDS
    _,before=read_gate(WORK.parent/'hot_coverage_bundle/bundle_full_gate.json','native_hot_coverage_bundle_bundle_')
    _,after=read_gate(WORK/'bundle_full_gate.json','native_frame_segments_bundle_bundle_')
    references=reference_index(STAGE/'native_host_observed_reference_plan.json')
    checked=0;event_digest=hashlib.sha256()
    for cohort,cases in references.items():
        for case_id,reference in sorted(cases.items()):
            old=before[reference['path']][case_id];new=after[reference['path']][case_id]
            assert new['category']=='pass' and new['cpp_events_sha256']
            for field in FIELDS:assert old.get(field)==new.get(field),(case_id,field)
            event_digest.update(f"{case_id} {new['cpp_events_sha256']}\n".encode())
            checked+=1
    assert checked==2604 and event_digest.hexdigest()==ROOT
    assert audit['candidate_dll_sha256']==actual and audit['fights']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    assert all(audit['frame_segment_coverage'][key]>0 for key in ('fast_items','stun_hits','speed_hits','timer_chunks_skipped'))
    assert all(value>0 for value in audit['typed_read_coverage'].values())
    assert audit['typed_read_coverage']['property_reads']==audit['property_coverage']['field_hits']
    assert all(value>0 for value in audit['hot_slot_coverage'].values())
    assert audit['type_constructor_coverage']['type_hits']>0 and audit['type_constructor_coverage']['fused_initializations']>0
    installed=read('bundle_installation.json')
    ab_path=Path(installed['ab_assessment_path'])
    assert sha(ab_path)==installed['ab_assessment_sha256']
    ab=json.loads(ab_path.read_bytes())
    assert ab['baseline_dll_sha256']==BASE and ab['candidate_dll_sha256']==actual
    assert ab['status']=='positive_combined_evidence' and installed['ab_pairs'] in (24,32) and len(ab['reports'])==installed['ab_pairs']//8
    for report in ab['reports']:assert sha(Path(report['path']))==report['sha256']
    for metric in ab['metrics'].values():assert metric['pairs']==installed['ab_pairs'] and metric['paired_median_time_reduction_pct']>0
    serial=read('bundle_serial.json');calibration=read('bundle_load_calibration.json');fit=read('bundle_load20.json')
    measurement=read('measurements_summary.json')
    for name,digest in measurement['report_sha256'].items():assert sha(WORK/name)==digest,name
    for record in (serial,calibration):
        assert record['dll_sha256']==actual and record['workers']==1 and record['fights']==200
        assert record['inputs_sha256']==INPUT and record['results_sha256']==RESULT
        assert len(record['samples'])==record['repeat']==24
        for row in record['samples']:
            assert row['matched_original_terminal']==200 and row['on_ac_before'] is True and row['on_ac_after'] is True
            assert math.isclose(row['fights_per_second'],200/row['wall_s'],rel_tol=1e-12)
    assert min(row['fights_per_second'] for row in serial['samples'])>=50
    assert fit['dll_sha256']==actual and fit['reference_load_pct']==20
    xs=[row['background_load_pct'] for row in calibration['samples']]
    ys=[math.log(row['wall_s']) for row in calibration['samples']]
    slope,intercept=statistics.linear_regression(xs,ys)
    recalculated=200/math.exp(intercept+20*slope)
    assert math.isclose(recalculated,fit['fitted_fights_per_second_at_reference_load'],rel_tol=1e-10)
    assert min(xs)<=20<=max(xs),'Reference load must be covered by actual observations'
    installed=read('bundle_installation.json')
    assert installed['dll_sha256']==actual and installed['gate_sha256']==sha(WORK/'bundle_full_gate.json')
    assert installed['speed_report_sha256']==sha(WORK/'bundle_serial.json')
    assert installed['training_matched_baseline']==12 and len(installed['training_outcomes'])==12
    assert installed['training_evaluation']['total_sims']==12 and installed['training_evaluation']['sim_errors']==0
    assert sha(REPO/installed['backup_runtime']/'libgdcore.dll')==BASE
    result={'passed':True,'dll_sha256':actual,'production_source_files':704,'unchanged_object_headers':674,
        'strict_event_cases':2604,'event_hash_root':ROOT,'raw_batches':24,'training_cases':12,
        'type_constructor_coverage':audit['type_constructor_coverage'],'hot_slot_coverage':audit['hot_slot_coverage'],'typed_read_coverage':audit['typed_read_coverage'],'frame_segment_coverage':audit['frame_segment_coverage'],
        'target_at20_fps':recalculated,'goal140_reached':recalculated>=140,
        'load_range_pct':[min(xs),max(xs)],'fit_validation':fit['validation'],
        'evidence_sha256':{name:sha(WORK/name) for name in ('source_before_build.json','bundle_full_gate.json','bundle_vs_deployed_hashes.json','ab_assessment.json','bundle_serial.json','bundle_load_calibration.json','bundle_load20.json','bundle_installation.json')}}
    out=WORK/'post_install_verification.json';assert not out.exists()
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(result,indent=2))


if __name__=='__main__':main()

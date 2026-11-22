"""Declare one bounded-motion candidate using the unchanged release protocol."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/spatial_bundle'
WORK=STAGE/'native_perf50/motion_indices_bundle'
BASE='3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520'
ARCHIVE='fcfe317116882ad80e2dd59611c38c01690ba004'

def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old));return text.replace(old,new,1)

def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    for path in OLD.glob('*.py'):
        if path.name in ('summarize_profile_for_brainstorm.py','profile_deployed.py'):continue
        text=path.read_text('utf8').replace('spatial_bundle','motion_indices_bundle').replace('dispatch_chain_bundle','spatial_bundle')
        text=text.replace('69cab46bc048500927ca4ed82104e78f7f8818b6',ARCHIVE).replace('39c559a0bc4ef04f89444be63b42b842884a7d2fee1d59c4332fcdc7367d8e0b',BASE).replace('native-spatial-','native-motion-indices-')
        if path.name=='resume_build.py':text=once(text,"    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_motion_index_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='validate_then_compare.py':text=once(text,"    run('verify_spatial.py','spatial_tests.log')","    run('verify_spatial.py','spatial_tests.log')\n    run('verify_motion_indices.py','motion_indices_tests.log')")
        if path.name=='inspect_variant.py':
            text=once(text,'    audit(1);before=',"    motion=sim.lib.gd_diag_native_motion_index_stat;motion.argtypes=[ctypes.c_uint];motion.restype=ctypes.c_uint64\n    motion_before=[motion(i) for i in range(3)]\n    audit(1);before=")
            text=once(text,'    args.out.write_text',"    report['motion_index_coverage']=dict(zip(('native_runs','native_entries','kept_entries'),[motion(i)-motion_before[i] for i in range(3)]))\n    assert all(value>0 for value in report['motion_index_coverage'].values())\n    assert report['motion_index_coverage']['kept_entries']<=report['motion_index_coverage']['native_entries']\n    args.out.write_text")
        if path.name=='audit_verify.py':
            text=once(text,'resolved_audit(1);resolved_before=',"motion_stat=lib.gd_diag_native_motion_index_stat;motion_stat.argtypes=[ctypes.c_uint];motion_stat.restype=ctypes.c_uint64\nmotion_before=[motion_stat(i) for i in range(3)]\nresolved_audit(1);resolved_before=")
            text=once(text,'raise SystemExit(exit_code)',"motion_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'counts':[motion_stat(i)-motion_before[i] for i in range(3)]}\n(out/'native_motion_index_audit.json').write_text(json.dumps(motion_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if path.name=='finish_gate.py':
            text=once(text,'    spatial_counts=[0]*4','    spatial_counts=[0]*4\n    motion_counts=[0]*3')
            text=once(text,"        summary=json.loads((root/'summary.json').read_bytes())","        motion=json.loads((root/'native_motion_index_audit.json').read_bytes());assert motion['dll_sha256']==dll and motion['verifier_exit_code']==0 and len(motion['counts'])==3\n        for i,value in enumerate(motion['counts']):motion_counts[i]+=value\n        summary=json.loads((root/'summary.json').read_bytes())")
            text=once(text,"    baseline=json.loads((WORK.parent/", "    assert all(value>0 for value in motion_counts) and motion_counts[2]<=motion_counts[1]\n    baseline=json.loads((WORK.parent/")
            text=once(text,"        'spatial_coverage':dict(zip(","        'motion_index_coverage':dict(zip(('native_runs','native_entries','kept_entries'),motion_counts)),\n        'spatial_coverage':dict(zip(")
        if path.name=='verify_installed.py':
            text=text.replace("'spatial_tests.json'","'spatial_tests.json','motion_indices_tests.json'").replace("'spatial_production_cases.json'","'spatial_production_cases.json','motion_indices_production_cases.json'")
            text=once(text,"    assert read('legacy_counter_equivalence.json')['passed']", "    motion_counts=[0]*3\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_motion_index_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0 and len(row['counts'])==3\n        for index,count in enumerate(row['counts']):motion_counts[index]+=count\n    assert all(value>0 for value in motion_counts) and motion_counts[2]<=motion_counts[1]\n    assert dict(zip(('native_runs','native_entries','kept_entries'),motion_counts))==audit['motion_index_coverage']\n    assert read('motion_indices_tests.json')['cases']==5840\n    assert read('legacy_counter_equivalence.json')['passed']")
            text=once(text,"        'spatial_coverage':audit['spatial_coverage'],","        'spatial_coverage':audit['spatial_coverage'],'motion_index_coverage':audit['motion_index_coverage'],")
        if path.name=='save_checkpoint.py':
            text=once(text,'    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_motion_indices.py','test_native_motion_indices.cpp','probe_native_motion_indices.py','prototype_native_motion_indices_bundle.py','preflight_native_motion_indices_bundle.py','setup_motion_indices_bundle.py'))\n    paths.update(p for p in (WORK.parent/'motion_indices_probe').iterdir() if p.is_file())\n    # Preserve the rejected damage bundle's exact measurements and local probes.\n    paths.update(STAGE/p for p in ('prepare_native_damage_records.py','test_native_damage_records.cpp','probe_native_damage_records.py','test_native_damage_records_extended.cpp','probe_native_damage_records_extended.py','prepare_native_damage_combo.py','probe_native_damage_combo.py','test_native_damage_source_helpers.cpp','probe_native_damage_source_helpers.py','test_native_damage_active_helpers.cpp','probe_native_damage_active_helpers.py','prototype_native_damage_combo_bundle.py','preflight_native_damage_combo_bundle.py','setup_damage_combo_bundle.py'))\n    for folder in ('damage_records_probe','damage_combo_probe','damage_combo_bundle'):\n        paths.update(p for p in (WORK.parent/folder).iterdir() if p.is_file())\n    audit=json.loads")
            text=text.replace('perf: combine spatial lookup and stable object deduplication','perf: specialize bounded motion queue controls').replace('backup: preserve verified spatial queries','backup: preserve verified bounded motion controls')
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['bounded motion read/write/limit','native Bool keep flag'],local_original_dll_cases=5840,
        excluded=['persistent record cache','layout changes','entry or property snapshots across callbacks','public arithmetic changes','callback or RNG reordering'])
    plan['required'][0]='5840 actual3a92 DLL motion differentials including callback queue mutation, nested invocation, fallback kinds and four rounding modes'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared motion candidate: fresh full20/PGO18, fixed200x4 and3x8AB, 2604 truth, raw24 and calibration24 unchanged')

if __name__=='__main__':main()

"""Declare one damage-chain bundle with the existing unchanged formal gates."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/spatial_bundle'
WORK=STAGE/'native_perf50/damage_combo_bundle'
BASE='3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520'
ARCHIVE='fcfe317116882ad80e2dd59611c38c01690ba004'
def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    for path in OLD.glob('*.py'):
        if path.name in ('summarize_profile_for_brainstorm.py','profile_deployed.py'):continue
        source=path.read_text('utf8').replace('spatial_bundle','damage_combo_bundle').replace('dispatch_chain_bundle','spatial_bundle')
        source=source.replace('69cab46bc048500927ca4ed82104e78f7f8818b6',ARCHIVE).replace('39c559a0bc4ef04f89444be63b42b842884a7d2fee1d59c4332fcdc7367d8e0b',BASE)
        source=source.replace('native-spatial-','native-damage-combo-')
        if path.name=='resume_build.py':source=source.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_damage_record_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='validate_then_compare.py':source=source.replace("    run('verify_spatial.py','spatial_tests.log')","    run('verify_spatial.py','spatial_tests.log')\n    run('verify_damage_combo.py','damage_combo_tests.log')")
        if path.name=='inspect_variant.py':
            source=source.replace('    audit(1);before=',"    damage=sim.lib.gd_diag_native_damage_record_stat;damage.argtypes=[ctypes.c_uint];damage.restype=ctypes.c_uint64\n    damage_before=[damage(i) for i in range(6)]\n    audit(1);before=")
            source=source.replace('    args.out.write_text',"    report['damage_record_coverage']=dict(zip(('records','integer_flags','flag_fallback','array_types','type_fallback','classifier_fallback'),[damage(i)-damage_before[i] for i in range(6)]))\n    assert all(report['damage_record_coverage'][key]>0 for key in ('records','integer_flags','array_types'))\n    args.out.write_text")
        if path.name=='verify_installed.py':
            source=source.replace("'spatial_tests.json'","'spatial_tests.json','damage_combo_tests.json'")
            source=source.replace("'spatial_production_cases.json'","'spatial_production_cases.json','damage_parent_production_cases.json','damage_active_production_cases.json','damage_source_production_cases.json'")
        if path.name=='save_checkpoint.py':
            source=source.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_damage_records.py','test_native_damage_records.cpp','probe_native_damage_records.py','test_native_damage_records_extended.cpp','probe_native_damage_records_extended.py','prepare_native_damage_combo.py','probe_native_damage_combo.py','test_native_damage_source_helpers.cpp','probe_native_damage_source_helpers.py','test_native_damage_active_helpers.cpp','probe_native_damage_active_helpers.py','prototype_native_damage_combo_bundle.py','preflight_native_damage_combo_bundle.py','setup_damage_combo_bundle.py'))\n    for folder in ('damage_records_probe','damage_combo_probe'):paths.update(p for p in (WORK.parent/folder).iterdir() if p.is_file())\n    audit=json.loads",1)
            source=source.replace('perf: combine spatial lookup and stable object deduplication','perf: specialize local damage records and source probes').replace('backup: preserve verified spatial queries','backup: preserve verified damage record kernel')
        ast.parse(source,filename=path.name);(WORK/path.name).write_text(source,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['local exact damage records','typed integer flags','ordered type probes'],
        local_original_dll_cases=29864,retained_deployed_components=['member pointers','character state reuse','static consumers','fixed setup tables','behavior/callback chains','spatial queries'],
        excluded=['layout changes','public arithmetic changes','callback or RNG reordering','probe RTTI compatibility helper in production'])
    plan['required'][0]='19400 parent damage cases and10464 helper boundaries against actual3a92 DLL, plus all retained regressions'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared one damage-chain bundle; fixed200x4,3x8 AB/BA,2604 truth, raw24 and calibration24 unchanged')
if __name__=='__main__':main()

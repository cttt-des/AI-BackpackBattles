"""Retain the rejected PGO build, then prepare the ordered-FP correction."""
import json,shutil
from pathlib import Path
import prepare_quiet_round as p
from install_ordering_correctness import boundary

def main():
    boundary();p.verify_projection(p.WORK/'bundle_src')
    failure=json.loads((p.WORK/'floating_flags_diagnostic.json').read_bytes());assert not failure['passed'] and failure['mismatch_count']==192
    assert p.sha(p.WORK/'bundle.dll')==failure['candidate_dll_sha256'] and failure['independent_production_DLL_confirms_all_mismatches']
    barrier=json.loads((p.WORK/'fp_dependency_barrier_tests.json').read_bytes());assert barrier['passed'] and barrier['actual_fragment_sha256']==p.sha(p.STAGE/'quiet_core_kernel.cpp')
    assert not (p.WORK/'formal_timing_inputs.json').exists() and not (p.WORK/'installation.json').exists()
    for name in ('normal_object_paths.json','release_objects.json'):
        r=json.loads((p.WORK/name).read_bytes());paths=r.values() if name.startswith('normal') else [str(Path(r['object_directory'])/n) for n in r['objects_sha256']]
        assert all(not Path(path).exists() for path in paths)
    archive=p.WORK/'development_versions/v2';assert not archive.exists();archive.mkdir(parents=True)
    cpp=p.WORK/'bundle_src/engine_wrapper.cpp';original_cpp=cpp.read_text('utf8');shutil.copyfile(cpp,archive/'engine_wrapper.cpp')
    changes=json.loads((p.WORK/'source_changes.json').read_bytes())
    exact={'prototype.dll','bundle.dll','prototype_build.json','prototype_build.log','normal_object_paths.json','candidate_syntax_preflight.json','source_changes.json','source_before_build.json','transform.json','regeneration_manifest.json','verified_bundle_pending.py','full_regeneration_test.json','full_regeneration_directory.json','full_regeneration_1.log','full_regeneration_2.log','regeneration_driver.log','before_runtime','release_objects.json','compiled_option_receipt.json','compiled_options','live_formal_build.json','persistent_build_directory.json','bundle_objects.txt','instrumented_export_policy.json','fresh_profile_source.json','frozen_pgo_manifest.json','frozen_pgo_counts','pre_timing_revision_plan.json','development_revision.json','floating_flags_diagnostic.json','flags_diagnostic_v2','flags_diagnostic_v2.log','quiet_goal_driver_first.log','quiet_goal_driver_attempt2.log'}
    exact.update(s.name for s in p.WORK.glob('prototype_*'))
    exact.update(s.name for s in p.WORK.glob('formal_*') if s.name!='formal_ab_protocol.json')
    root=p.WORK.resolve();retained={}
    for name in sorted(exact):
        source=p.WORK/name
        if not source.exists():continue
        target=archive/name;assert source.resolve().is_relative_to(root) and target.resolve().is_relative_to(root) and source.resolve()!=root
        if source.is_file():retained[name]=p.sha(source)
        shutil.move(source,target)
    reports=archive/'prototype_fast_reports';reports.mkdir()
    for source in sorted(p.STAGE.glob('native_quiet_fast_prototype_*')):
        assert source.resolve().is_relative_to(p.STAGE.resolve()) and source.name.startswith('native_quiet_fast_prototype_')
        target=reports/source.name;assert target.resolve().is_relative_to(root)
        shutil.move(source,target)
    operations=changes['engine_wrapper.cpp'];marker='static void run_one_internal;'
    assert operations[1][0]=='static void run_one_internal('
    suffix='\nstatic void run_one_internal(';old=operations[1][1][:-len(suffix)];assert operations[1][1].endswith(suffix)
    new=(p.STAGE/'quiet_core_kernel.cpp').read_text('utf8');assert original_cpp.count(old)==1 and old!=new
    cpp.write_text(original_cpp.replace(old,new),encoding='utf8',newline='\n');operations[1][1]=new+suffix
    p.save('source_changes.json',changes);p.save('source_before_build.json',p.inventory(p.WORK/'bundle_src'))
    p.save('transform.json',dict(baseline_dll_sha256=p.EXPECTED,source_sha256=p.inventory(p.WORK/'bundle_src'),modified_files=['engine_wrapper.cpp'],projection=p.verify_projection(p.WORK/'bundle_src')))
    selection=json.loads((p.WORK/'architecture_selection.json').read_bytes());selection['floating_flags_revision']=dict(rejected_dll_sha256=failure['candidate_dll_sha256'],independent_original_mismatches=192,mismatches_by_mode=failure['mismatches_by_mode'],all_game_fields_and_RNG_were_equal=True,fix='Explicit pointer/scalar dependencies order arithmetic around MXCSR capture; no compiler flag changes',SSE_reference_cases=barrier['cases'],no_AB_or_deployment_before_correction=True)
    p.save('architecture_selection.json',selection)
    p.save('development_revision.json',dict(passed=True,archive=str(archive),retained_file_sha256=retained,normal_and_PGO_objects_already_cleaned=True,no_AB_samples=True,new_fragment_sha256=p.sha(p.STAGE/'quiet_core_kernel.cpp'),new_source_manifest_sha256=p.sha(p.WORK/'source_before_build.json'),full20_normal_and_full20_fresh18_PGO_required=True))
    print('Retained rejected v2 and all event reports; prepared explicit FP-order correction',flush=True)
if __name__=='__main__':main()

"""Archive the first untimed development build before a reviewed revision."""
import json,shutil
from pathlib import Path
import prepare_quiet_round as p
from install_ordering_correctness import boundary

def main():
    boundary();p.verify_projection(p.WORK/'bundle_src')
    report=json.loads((p.WORK/'development1_quiet_core_tests.json').read_bytes());assert report['passed'] and report['dll_sha256']==p.sha(p.WORK/'prototype.dll')
    assert not (p.WORK/'formal_timing_inputs.json').exists() and not (p.WORK/'bundle.dll').exists()
    paths=json.loads((p.WORK/'normal_object_paths.json').read_bytes());assert all(not Path(path).exists() for path in paths.values())
    archive=p.WORK/'development_versions/v1';assert not archive.exists();archive.mkdir(parents=True)
    cpp=p.WORK/'bundle_src/engine_wrapper.cpp';shutil.copyfile(cpp,archive/'engine_wrapper.cpp')
    files=['prototype.dll','prototype_build.json','prototype_build.log','normal_object_paths.json','candidate_syntax_preflight.json','source_changes.json','source_before_build.json','transform.json','regeneration_manifest.json','verified_bundle_pending.py','full_regeneration_test.json','full_regeneration_directory.json','full_regeneration_1.log','full_regeneration_2.log','regeneration_driver.log','before_runtime']
    retained={}
    root=p.WORK.resolve()
    for name in files:
        source=p.WORK/name;target=archive/name
        assert source.resolve().is_relative_to(root) and target.resolve().is_relative_to(root) and source.resolve()!=root
        if source.is_file():retained[name]=p.sha(source)
        shutil.move(source,target)
    changes=json.loads((archive/'source_changes.json').read_bytes())
    operations=changes['engine_wrapper.cpp'];marker='static void run_one_internal(';assert operations[1][0]==marker and operations[1][1].endswith('\n'+marker)
    before=operations[1][1][:-len('\n'+marker)];after=(p.STAGE/'quiet_core_kernel.cpp').read_text('utf8');text=cpp.read_text('utf8');assert text.count(before)==1 and before!=after
    cpp.write_text(text.replace(before,after),encoding='utf8',newline='\n');operations[1][1]=after+'\n'+marker
    p.save('source_changes.json',changes);p.save('source_before_build.json',p.inventory(p.WORK/'bundle_src'))
    p.save('transform.json',dict(baseline_dll_sha256=p.EXPECTED,source_sha256=p.inventory(p.WORK/'bundle_src'),modified_files=['engine_wrapper.cpp'],projection=p.verify_projection(p.WORK/'bundle_src')))
    selection=json.loads((p.WORK/'architecture_selection.json').read_bytes());selection['pre_timing_revision']=dict(first_development_dll_sha256=report['dll_sha256'],first_development_cases=report['cases'],first_development_coverage=report['exercised_core_counts'],changes=['accumulate sticky expression flags as integer bits, one frame-boundary restoration','reject known short intervals and blocked tails before remaining graph validation','avoid repeated RTTI proof for the same item','reject opening/audit frames before creating the numerical plan'],no_candidate_speed_observations=True)
    p.save('architecture_selection.json',selection)
    p.save('development_revision.json',dict(passed=True,previous=retained,archive=str(archive),new_fragment_sha256=p.sha(p.STAGE/'quiet_core_kernel.cpp'),source_manifest_sha256=p.sha(p.WORK/'source_before_build.json'),old20_objects_already_removed=True,no_candidate_timing_has_been_run=True,full20_normal_rebuild_required=True))
    print('Archived untimed first development build; prepared reviewed revision',flush=True)
if __name__=='__main__':main()

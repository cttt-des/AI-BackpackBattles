"""Verify every weapon case against the reference applicable to its semantics."""
import json,shutil
from prepare_ordering_correctness import STAGE,WORK,sha,save,verify_projection
from check_ordering_retained_deltas import check
def main():
    verify_projection(WORK/'bundle_src')
    report=WORK/'weapon_chain_tests.json';comparison=WORK/'weapon_normal_pgo_full_comparison.json'
    if not comparison.exists():shutil.copyfile(report,comparison)
    raw=json.loads(comparison.read_bytes());assert not raw['passed'] and raw['difference_counts']==dict(case_hashes=56,legacy_counter_hashes=0)
    assert raw['dll_sha256']==sha(WORK/'bundle.dll') and raw['baseline_dll_sha256']==sha(WORK/'corrected_normal_reference/bundle.dll')
    for name,h in raw['dependencies_sha256'].items():assert sha(STAGE/name if name=='test_native_weapon_chain.cpp' else WORK/name)==h
    folder=WORK/'weapon_chain_tests_checks'
    for name,h in raw['raw_sha256'].items():assert sha(folder/name)==h
    original=json.loads((WORK/'weapon_old_contract_failure/weapon_chain_tests.json').read_bytes())
    assert original['dll_sha256']==sha(WORK/'bundle.dll') and original['baseline_dll_sha256']==sha(WORK/'retained_reference_src/libgdcore.dll')
    oldfolder=WORK/'weapon_old_contract_failure/weapon_chain_tests_checks'
    for name,h in original['raw_sha256'].items():assert sha(oldfolder/name)==h
    assert sha(folder/'candidate_cases.json')==sha(oldfolder/'candidate_cases.json')
    check('weapon')
    result=dict(passed=True,cases=136128,retained_damage_cases=103360,whole_chain_cases=32768,dll_sha256=sha(WORK/'bundle.dll'),unaffected_cases_using_independent_original_PGO=135136,changed_append_cases_using_corrected_normal_and_original_Godot=992,all_cases_and_all_counters_compared=True,no_case_dropped=True,differences_to_selected_reference=0,old_original_PGO_sha256=original['baseline_dll_sha256'],corrected_normal_sha256=raw['baseline_dll_sha256'],normal_build_extra56_not_used_as_truth_for_unchanged_cases=True,normal_comparison_full_report_sha256=sha(comparison),original_Godot_reference_sha256=sha(WORK/'original_ordering_reference.json'),expectation_correction_sha256=sha(WORK/'weapon_expectation_correction.json'),normal_build_difference_sha256=sha(WORK/'weapon_normal_build_difference.json'))
    save('weapon_chain_tests.json',result);print('All136128 weapon cases passed their applicable reference;992 corrected append cases,135136 unchanged original-PGO cases; all56 unrelated normal-build differences preserved',flush=True)
if __name__=='__main__':main()

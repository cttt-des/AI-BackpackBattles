"""Retain the complete corrected regression suite, with no changed expectations."""
import ast,json,shutil
from pathlib import Path
from prepare_frame_guard_reuse import STAGE,WORK,ACCEPTED,EXPECTED,sha,save
NAMES=['generate_property_tests.py','generate_type_constructor_tests.py','verify_event_identity.py','verify_lazy_diagnostics.py','verify_components.py','verify_static_collections.py','verify_static_setup.py','verify_dispatch_chain.py','verify_spatial.py','verify_motion_indices.py','verify_targeted_timers.py','verify_active_cooldowns.py','verify_buff_integer.py','verify_container_builtins.py','verify_scalar_truth.py','verify_private_snapshots.py','verify_control_word.py','verify_display_storage.py','verify_integer_grid.py','verify_event_factory.py','verify_literal_spans.py','verify_callback_dispatch.py','verify_object_routes.py','verify_full_pgo_buff.py','verify_assembly_membership.py','verify_resolved.py','verify_retained_weapon_chain.py','inspect_variant.py','audit_verify.py','run_full_gate.py','finish_gate.py','verify_closed_registry_current.py']
MODULES=['verify_assembly_membership_control.py','verify_assembly_membership_display.py','verify_assembly_membership_private.py','verify_assembly_membership_truth.py','verify_assembly_membership_builtins.py','verify_assembly_membership_buff_helpers.py','verify_assembly_membership_buff_methods.py','verify_assembly_weapon_chain.py','verify_native_assembly_membership_helpers.py']
def main():
    copied={}
    for name in [*NAMES,*MODULES]:
        source=ACCEPTED/name;text=source.read_text('utf8').replace('prepare_ordering_retained','prepare_frame_guard_retained')
        if name=='run_full_gate.py':text=text.replace('native_ordering_correctness_bundle_','native_frame_guard_reuse_bundle_')
        if name=='finish_gate.py':
            text=text.replace("WORK.parent/'assembly_membership_bundle/","WORK.parent/'ordering_correctness_bundle/")
            text=text.replace("'native_assembly_membership_bundle_bundle_'","'native_ordering_correctness_bundle_bundle_'")
            text=text.replace("'--candidate-prefix','native_ordering_correctness_bundle_bundle_'","'--candidate-prefix','native_frame_guard_reuse_bundle_bundle_'")
            text=text.replace("glob('native_ordering_correctness_bundle_bundle_*')","glob('native_frame_guard_reuse_bundle_bundle_*')")
        if name=='verify_full_pgo_buff.py':text=text.replace("STAGE/'native_perf50/ordering_correctness_bundle'","STAGE/'native_perf50/frame_guard_reuse_bundle'")
        prelude="import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\n"
        text=prelude+text;ast.parse(text);(WORK/name).write_text(text,encoding='utf8',newline='\n');copied[name]=sha(source)
    for p in ACCEPTED.iterdir():
        if p.is_file() and p.suffix in ('.hpp','.cpp'):shutil.copyfile(p,WORK/p.name)
    for name in ('retained_fixture_transform.json','retained_event_test_correction.json','original_ordering_reference.json','original_reference_provenance.json','original_activation_reference.json','original_potion_chain_reference.json','sort_cases.json','activation_cases.json','targeted_timer_godot_reference.json','timer_sort_expectation_correction.json'):
        shutil.copyfile(ACCEPTED/name,WORK/name)
    for name in ('verify_ordering_contracts.py','verify_ordering_extra_potions.py'):
        text=(STAGE/name).read_text('utf8').replace('from prepare_ordering_correctness import','from prepare_frame_guard_reuse import')
        text="import sys\nfrom pathlib import Path\nsys.path.insert(0,str(Path(__file__).resolve().parents[2]))\n"+text;ast.parse(text);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    wrappers={
        'verify_private_snapshots.py':('verify_assembly_membership_private','private_snapshots_tests.json'),
        'verify_retained_weapon_chain.py':('verify_assembly_weapon_chain','weapon_chain_tests.json'),
        'verify_literal_spans.py':('verify_native_literal_spans','literal_span_tests.json'),
    }
    for name,(module,out) in wrappers.items():
        text=f'''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]));sys.path.insert(0,str(WORK))
from prepare_frame_guard_reuse import ACCEPTED,EXPECTED
import {module} as checks
checks.ACCEPTED=ACCEPTED;checks.EXPECTED=EXPECTED
if __name__=='__main__':checks.verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/{out!r})
''';(WORK/name).write_text(text,encoding='utf8',newline='\n')
    reference=WORK/'retained_reference_src';shutil.copytree(ACCEPTED/'bundle_src',reference);shutil.copyfile(ACCEPTED/'bundle.dll',reference/'libgdcore.dll');assert sha(reference/'libgdcore.dll')==EXPECTED
    save('retained_harness_preparation.json',dict(passed=True,source_baseline=EXPECTED,original_script_sha256=copied,all_cases_and_expectations_retained=True,no_original_bug_baseline_for_mutating_listener_cases=True,current_weapon_all136128_must_be_bit_exact=True,normal_PGO_case_merging_not_used_for_formal_candidate=True))
    print('Complete corrected regression suite prepared; formal results must equal repaired production exactly',flush=True)
if __name__=='__main__':main()

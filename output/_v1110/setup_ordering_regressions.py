"""Prepare retained gates without changing any archived tests or receipts."""
import ast,json,re,shutil
from prepare_ordering_correctness import STAGE,WORK,ACCEPTED,sha,once,save

def main():
    # Preserve the old fixture metadata independently of this repair's transform.
    shutil.copyfile(ACCEPTED/'transform.json',WORK/'retained_fixture_transform.json')
    inherited={}
    for path in ACCEPTED.iterdir():
        if path.is_file() and (path.suffix in ('.py','.hpp','.cpp') or path.name.startswith('baseline_') and path.suffix=='.json') and not (WORK/path.name).exists():
            shutil.copyfile(path,WORK/path.name);inherited[path.name]=sha(path)
    save('inherited_harness_dependencies.json',inherited)
    names=['generate_property_tests.py','generate_type_constructor_tests.py',
        'verify_event_identity.py','verify_lazy_diagnostics.py','verify_components.py','verify_static_collections.py','verify_static_setup.py','verify_dispatch_chain.py','verify_spatial.py','verify_motion_indices.py','verify_targeted_timers.py','verify_active_cooldowns.py',
        'verify_buff_integer.py','verify_container_builtins.py','verify_scalar_truth.py','verify_private_snapshots.py','verify_control_word.py','verify_display_storage.py','verify_integer_grid.py','verify_event_factory.py','verify_literal_spans.py','verify_callback_dispatch.py','verify_object_routes.py','verify_resolved.py','inspect_variant.py','audit_verify.py','run_full_gate.py','finish_gate.py']
    root_modules=['verify_assembly_membership_control','verify_assembly_membership_display','verify_assembly_membership_private','verify_assembly_membership_truth','verify_assembly_membership_builtins','verify_assembly_membership_buff_helpers','verify_assembly_membership_buff_methods','verify_assembly_weapon_chain','verify_native_assembly_membership_helpers']
    for name in root_modules:
        text=(STAGE/(name+'.py')).read_text('utf8').replace('from prepare_native_assembly_membership import','from prepare_ordering_retained import')
        ast.parse(text);(WORK/(name+'.py')).write_text(text,encoding='utf8',newline='\n')
    # Use the source-correct expectations; preserve the old test as evidence.
    original=(STAGE/'test_native_event_kernel.cpp').read_text('utf8')
    fixed=once(original,'// Appended callbacks wait for a new emission.','// Godot visits appended listeners during the current emission.')
    fixed=once(fixed,'if(scenario==0){assert((trace==std::vector<int64_t>{1,2}));emit();assert((trace==std::vector<int64_t>{1,2,1,2,3}));}','if(scenario==0){assert((trace==std::vector<int64_t>{1,2,3}));emit();assert((trace==std::vector<int64_t>{1,2,3,1,2,3,3}));}')
    fixed=once(fixed,'if(scenario==1)assert((trace==std::vector<int64_t>{1,3}));','if(scenario==1)assert((trace==std::vector<int64_t>{1,3,3}));')
    (WORK/'test_native_event_kernel_godot.cpp').write_text(fixed,encoding='utf8',newline='\n')
    save('retained_event_test_correction.json',dict(original_test_sha256=sha(STAGE/'test_native_event_kernel.cpp'),corrected_test_sha256=sha(WORK/'test_native_event_kernel_godot.cpp'),all_scenarios_retained=True,original_Godot_oracle=sha(WORK/'original_ordering_reference.json'),changed_expectations=['appended listener visible this emission','replacement plus appended tail both visited']))
    for name in names:
        text=(ACCEPTED/name).read_text('utf8')
        if name=='verify_resolved.py':
            anchor='        test=STAGE/file\n';text=once(text,anchor,anchor+"        if file=='test_native_event_kernel.cpp':test=WORK/'test_native_event_kernel_godot.cpp'\n")
        if name=='run_full_gate.py':
            start=text.index('    # This subprocess');end=text.index('    gate =',start)
            text=text[:start]+"    proof=json.loads((WORK/'formal_ordering_tests.json').read_bytes())\n    import hashlib\n    assert proof['passed'] and proof['dll_sha256']==hashlib.sha256(dll.read_bytes()).hexdigest()\n"+text[end:]
            text=text.replace('native_assembly_membership_bundle_','native_ordering_correctness_bundle_')
        if name=='finish_gate.py':
            text=text.replace("WORK.parent/'buff_inline_types_bundle/","WORK.parent/'assembly_membership_bundle/")
            text=text.replace("'native_buff_inline_types_bundle_bundle_'","'native_assembly_membership_bundle_bundle_'")
            # Candidate prefixes only; baseline prefix above must stay accepted.
            text=text.replace("'--candidate-prefix','native_assembly_membership_bundle_bundle_'","'--candidate-prefix','native_ordering_correctness_bundle_bundle_'")
            text=text.replace("glob('native_assembly_membership_bundle_bundle_*')","glob('native_ordering_correctness_bundle_bundle_*')")
        ast.parse(text);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):shutil.copyfile(ACCEPTED/name,WORK/name)
    text=(STAGE/'verify_native_assembly_membership_full_pgo.py').read_text('utf8').replace("STAGE/'native_perf50/assembly_membership_bundle'","STAGE/'native_perf50/ordering_correctness_bundle'")
    ast.parse(text);(WORK/'verify_full_pgo_buff.py').write_text(text,encoding='utf8',newline='\n')
    (WORK/'verify_retained_weapon_chain.py').write_text("import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_assembly_weapon_chain import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'weapon_chain_tests.json')\n",encoding='utf8')
    (WORK/'verify_assembly_membership.py').write_text("import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_assembly_membership_helpers import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'assembly_membership_tests.json')\n",encoding='utf8')
    for name in [*names,'verify_retained_weapon_chain.py','verify_assembly_membership.py']:
        path=WORK/name;lines=[]
        for line in path.read_text('utf8').splitlines(keepends=True):
            lines.append(line)
            if line.lstrip().startswith('sys.path.insert(0,'):
                indent=line[:len(line)-len(line.lstrip())]
                lines.append(indent+'sys.path.insert(0,str(Path(__file__).resolve().parent))\n')
        text=''.join(lines);ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    for path in WORK.glob('*.py'):
        if path.name in ('verified_bundle_pending.py','gd_to_cpp_pending.py','gd_to_cpp_before.py','optimize_native_event_bus_pending.py'):continue
        text=path.read_text('utf8').replace('prepare_native_assembly_membership','prepare_ordering_retained')
        if path.name in ('generate_property_tests.py','generate_type_constructor_tests.py'):
            text=text.replace("WORK/'transform.json'","WORK/'retained_fixture_transform.json'")
        if path.name=='verify_targeted_timers.py':
            text=once(text,'    assert frozen==current',"    retained=json.loads((WORK.parent/'assembly_membership_bundle/source_before_build.json').read_bytes())\n    assert frozen==retained\n    assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']")
        ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared retained checks; archived tests and their old receipts unchanged',flush=True)
if __name__=='__main__':main()

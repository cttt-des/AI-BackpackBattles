"""Direct incremental frame comparison using a byte-identical existing candidate."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/member_only_bundle'
COMBINED=STAGE/'native_perf50/member_frame_bundle'
WORK=STAGE/'native_perf50/frame_ablation_bundle'
BASE='6cb258ec1baf335d3bc8e9da1538b2edd8aee87669b05249728f4829b1c47785'
def main():
    checkpoint=json.loads((OLD/'checkpoint.log').read_text('utf8').splitlines()[-1])
    assert checkpoint['dll_sha256']==BASE
    archive=checkpoint['remote_verified_commit']
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        text=p.read_text('utf8').replace('member_only_bundle','frame_ablation_bundle').replace('lazy_diagnostics_bundle','member_only_bundle')
        text=text.replace('native-member-only-','native-frame-ablation-').replace('c9bebb76a9f8cbbef0be3653b8ce448147ace3a4',archive)
        text=text.replace('593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670',BASE)
        if p.name=='build_bundle.py':
            text=text.split("    objects=Path(tempfile.mkdtemp",1)[0]+'''    prior=WORK.parent/'member_frame_bundle'
    expected=json.loads((prior/'source_before_build.json').read_bytes())
    assert expected==json.loads((WORK/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(prior/'bundle_src').as_posix():digest(p) for p in (prior/'bundle_src').rglob('*') if p.is_file()}
    (WORK/'source_before_build.json').write_bytes((prior/'source_before_build.json').read_bytes())
    assert digest(prior/'bundle.dll')=='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14'
    profile=json.loads((prior/'fresh_profile_source.json').read_bytes())
    assert profile['dll_sha256']==digest(prior/'bundle.dll') and profile['source_manifest_sha256']==digest(WORK/'source_before_build.json')
    assert profile['profile_training_and_release_source_identical'] and profile['floating_options_unchanged']
    shutil.copyfile(prior/'bundle.dll',WORK/'bundle.dll')
    save('fresh_profile_source.json',profile)
    save('candidate_reuse_proof.json',{'passed':True,'dll_sha256':digest(WORK/'bundle.dll'),'source_files':len(expected),
        'all_cpp_and_runtime_source_bytes_equal_to_original_compiled_candidate':True,
        'same_original_source_identical_fresh_PGO_reused':True,'no_new_compilation_or_PGO':True,
        'incremental_baseline_dll_sha256':BASE_SHA,'original_comparison_baseline':'593acaf3',
        'reason':'Directly isolate frame reuse relative to newly deployed member reads; no whole-DLL recompilation when every source byte is identical.'})
    print('Reused exactly matched original candidate and PGO; validating before incremental AB/BA',flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),'--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
'''
        if p.name=='verify_components.py':
            text=text.replace("(('member','test_native_member_fields.cpp',['-DGD_MEMBER_PRODUCTION']),)","(('member','test_native_member_fields.cpp',['-DGD_MEMBER_PRODUCTION']),('frame','test_native_frame_segments.cpp',[]))")
            text=text.replace("    result={'passed'", "    assert reports['frame']['cases']==6912\n    result={'passed'")
        if p.name=='save_checkpoint.py':
            text=text.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prototype_native_frame_ablation_bundle.py','setup_frame_ablation_bundle.py'))\n    audit=json.loads",1)
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    inspector=(COMBINED/'inspect_variant.py').read_text('utf8').replace('member_frame_bundle','frame_ablation_bundle')
    (WORK/'inspect_variant.py').write_text(inspector,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=archive,
        components=['retained deployed member reads','independent frame state reuse'],
        excluded=['empty timer chunks','field tags','global NaN guards','arithmetic inlining'],
        reused_candidate_dll='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14',
        reason='Incremental paired ablation against member-only6cb, not a rerun of d3versus593. Reuse the already built candidate only if every source byte and its original fresh PGO receipt matches. Preserve both previous comparisons.')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared frame incremental comparison with exact-source candidate reuse')
if __name__=='__main__':main()

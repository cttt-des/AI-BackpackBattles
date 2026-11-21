"""Declare one frozen literal-collection consumer experiment."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/frame_ablation_bundle'
WORK=STAGE/'native_perf50/static_collections_bundle'
BASE='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14'
ARCHIVE='03d2f106572f05d5c5d654e24e164ed45a09b591'
def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    for path in OLD.glob('*.py'):
        text=path.read_text('utf8').replace('frame_ablation_bundle','static_collections_bundle').replace('member_only_bundle','frame_ablation_bundle')
        text=text.replace('42be0c4610c7d93fc8eb0f260269e1ab9725613f',ARCHIVE).replace('6cb258ec1baf335d3bc8e9da1538b2edd8aee87669b05249728f4829b1c47785',BASE)
        if path.name=='build_bundle.py':
            text=(STAGE/'native_perf50/member_only_bundle/build_bundle.py').read_text('utf8')
            text=text.replace('member_only_bundle','static_collections_bundle').replace('native-member-only-','native-static-collections-')
            text=text.replace('593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670',BASE).replace('c9bebb76a9f8cbbef0be3653b8ce448147ace3a4',ARCHIVE)
        if path.name=='resume_build.py':text=text.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_static_collection_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='validate_then_compare.py':text=text.replace("    run('verify_resolved.py','verify.log')","    run('verify_static_collections.py','static_collections_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='verify_installed.py':text=text.replace("'member_frame_tests.json'","'member_frame_tests.json','static_collections_tests.json'")
        if path.name=='save_checkpoint.py':
            text=text.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_static_collections.py','test_native_static_collections.cpp','probe_native_static_collections.py','prototype_native_static_collections_bundle.py','preflight_native_static_bundle.py','setup_static_collections_bundle.py'))\n    paths.update(p for p in (WORK.parent/'static_collections_probe').iterdir() if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: deploy equivalent callback-bounded character state reuse','perf: fold proven static collection numeric consumers')
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    for name in ('reused_candidate_dll','reason'):plan.pop(name,None)
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,
        components=['literal class sound numeric consumers','literal number of stack types'],
        retained_deployed_components=['member pointers','callback-bounded frame state reuse'],
        excluded=['global mutable constant sharing','changed public arithmetic','changed object/context layout'],
        local_original_dll_cases=13440,
        no_whole_fight_gain_claim=True,
        build='full20 instrumentation plus new18unit same-source PGO; max2 below-normal jobs')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared static collection consumer experiment; same fixed200x4,3x8 AB/BA,2604 truth and24 raw batches')
if __name__=='__main__':main()

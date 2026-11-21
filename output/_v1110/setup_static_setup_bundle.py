"""Declare and prepare one fixed-baseline static getter/setup experiment."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/static_collections_bundle'
WORK=STAGE/'native_perf50/static_setup_bundle'
BASE='541238b57e2e18ce258a0afa9f548115761da28f4a1c119812277b4c0dae2983'
ARCHIVE='209b5711b0c405a677d97336343d3e3a3b182e2f'

def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    excluded={'summarize_profile_for_brainstorm.py'}
    for path in OLD.glob('*.py'):
        if path.name in excluded:continue
        source=path.read_text('utf8').replace('static_collections_bundle','static_setup_bundle').replace('frame_ablation_bundle','static_collections_bundle')
        source=source.replace('03d2f106572f05d5c5d654e24e164ed45a09b591',ARCHIVE).replace('d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14',BASE)
        source=source.replace('native-static-collections-','native-static-setup-')
        if path.name=='resume_build.py':source=source.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_static_setup_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='validate_then_compare.py':source=source.replace("    run('verify_resolved.py','verify.log')","    run('verify_static_setup.py','static_setup_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='verify_installed.py':source=source.replace("'static_collections_tests.json'","'static_collections_tests.json','static_setup_tests.json'")
        if path.name=='save_checkpoint.py':
            source=source.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_static_setup.py','test_native_static_setup.cpp','probe_native_static_setup.py','prototype_native_static_setup_bundle.py','preflight_native_static_setup_bundle.py','setup_static_setup_bundle.py'))\n    paths.update(p for p in (WORK.parent/'static_setup_probe').iterdir() if p.is_file())\n    audit=json.loads",1)
            source=source.replace('perf: fold proven static collection numeric consumers','perf: eliminate constant getter TLS and batch fixed setup tables')
        ast.parse(source,filename=path.name);(WORK/path.name).write_text(source,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,
        components=['144 pure static getter branches in34 classes','constant metric counts','fixed setup loops','empty independent stack-table bulk construction'],
        retained_deployed_components=['member pointers','callback-bounded frame state reuse','static numeric collection consumers'],
        excluded=['dense dictionary representation','changed public arithmetic','changed object or context layout','callback or RNG reordering'],
        local_original_dll_cases=6436,no_whole_fight_gain_claim=True,
        build='full20 instrumentation plus new18unit same-source PGO; max2 below-normal jobs',
        goal_fps_at20_load=200,retain_first_and_all_results=True)
    plan['required'][0]='6436 new cases against actual5412 DLL plus retained independent593a component regressions'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared one static getter/setup candidate; fixed200x4,3x8 AB/BA,2604 truth and first24 raw batches retained')

if __name__=='__main__':main()

"""Declare the first full dispatch-chain candidate and unchanged acceptance gates."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/static_setup_bundle'
WORK=STAGE/'native_perf50/dispatch_chain_bundle'
BASE='00cbcf9d9467feab8d8d99aa437683af507c5f924ee90a9b9f076b661d5c6a60'
ARCHIVE='1bf22370f344d8379b33d6c4d31629e178549ab7'

def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    for path in OLD.glob('*.py'):
        if path.name=='summarize_profile_for_brainstorm.py':continue
        source=path.read_text('utf8').replace('static_setup_bundle','dispatch_chain_bundle').replace('static_collections_bundle','static_setup_bundle')
        source=source.replace('209b5711b0c405a677d97336343d3e3a3b182e2f',ARCHIVE).replace('541238b57e2e18ce258a0afa9f548115761da28f4a1c119812277b4c0dae2983',BASE)
        source=source.replace('native-static-setup-','native-dispatch-chain-')
        if path.name=='resume_build.py':source=source.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_dispatch_chain_stat')\n    definition=objects/'instrumented_exports.def'")
        if path.name=='validate_then_compare.py':source=source.replace("    run('verify_resolved.py','verify.log')","    run('verify_dispatch_chain.py','dispatch_chain_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='verify_installed.py':source=source.replace("'static_setup_tests.json'","'static_setup_tests.json','dispatch_chain_tests.json'")
        if path.name=='save_checkpoint.py':
            source=source.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_dispatch_chain.py','test_native_dispatch_chain.cpp','probe_native_dispatch_chain.py','extend_dispatch_chain_cases.py','prototype_native_dispatch_chain_bundle.py','preflight_native_dispatch_chain_bundle.py','setup_dispatch_chain_bundle.py'))\n    paths.update(p for p in (WORK.parent/'dispatch_chain_probe').iterdir() if p.is_file())\n    audit=json.loads",1)
            source=source.replace('perf: eliminate constant getter TLS and batch fixed setup tables','perf: flatten behavior and event callback dispatch chains')
        ast.parse(source,filename=path.name);(WORK/path.name).write_text(source,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['nine-name exact generated behavior routing','flat unbound event callbacks'],
        retained_deployed_components=['member pointers','character state reuse','static consumers','TLS-free constants and fixed setup tables'],
        excluded=['new object or method-row layout','callback reordering','changed arithmetic or RNG','general bound-argument rewrite'],
        local_original_dll_cases=341604,no_whole_fight_gain_claim=True,goal_fps_at20_load=200)
    plan['required'][0]='341604 new cases against actual00cb DLL plus retained component regressions'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared one behavior/callback-chain candidate; fixed200x4,3x8 AB/BA,2604 truth and first24 raw batches')

if __name__=='__main__':main()

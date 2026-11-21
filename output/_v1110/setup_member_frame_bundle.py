"""Set up one frozen two-component experiment, without inherited failed changes."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/lazy_diagnostics_bundle'
WORK=STAGE/'native_perf50/member_frame_bundle'
BASE='593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670'
ARCHIVE='c9bebb76a9f8cbbef0be3653b8ce448147ace3a4'
def main():
    assert not (WORK/'build_bundle.py').exists()
    for p in OLD.glob('*.py'):
        if p.name in ('audit_goal_completion.py','run_followup.py'):continue
        text=p.read_text('utf8').replace('lazy_diagnostics_bundle','member_frame_bundle').replace('event_emission_bundle','lazy_diagnostics_bundle')
        text=text.replace('native-lazy-diagnostics-','native-member-frame-').replace('674fff4fdee8bcf5a408659750e3677a2b6790d6',ARCHIVE)
        if p.name!='verify_event_identity.py':text=text.replace('b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588',BASE)
        if p.name=='validate_then_compare.py':text=text.replace("    run('verify_resolved.py','verify.log')","    run('verify_components.py','component_tests.log')\n    run('verify_resolved.py','verify.log')")
        if p.name=='resume_build.py':text=text.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_frame_segment_stat')\n    definition=objects/'instrumented_exports.def'")
        if p.name=='verify_installed.py':text=text.replace("'lazy_diagnostics_tests.json'","'lazy_diagnostics_tests.json','member_frame_tests.json'")
        if p.name=='save_checkpoint.py':
            text=text.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prototype_native_member_frame_bundle.py','preflight_native_member_frame.py','setup_member_frame_bundle.py','test_native_member_fields.cpp','test_native_frame_segments.cpp'))\n    audit=json.loads",1)
            text=text.replace('perf: omit proven unobserved diagnostic formatting','perf: compose member field reads and bounded frame state reuse')
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    plan={'baseline_dll_sha256':BASE,'verified_remote_backup':ARCHIVE,
        'components':['member pointers for43 pure property rows','callback-bounded character stun/shared-speed reuse'],
        'excluded':['empty timer chunks','typed getter tags','global NaN guards','arithmetic inlining'],
        'measurement':{'fixed_fights':200,'single_thread':True,'groups':3,'pairs_per_group':8,'batch_repetitions':4,'warmup_seconds':120,'quiet':True,'retain_all_results':True},
        'required':['component differentials against released593a','existing full regression','same-source fresh PGO','regeneration twice','2604 strict original event cases','every old/new CPP event hash equal','one raw24 all>=50fps','one calibration24 report','guarded deployment and normal training smoke'],
        'no_auto_deploy':True,'small_components_judged_as_bundle':True}
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared two-component experiment and unchanged timing/truth gates')
if __name__=='__main__':main()

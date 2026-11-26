"""Keep normal-build diagnostics distinct from required actual PGO equality."""
import json
import psutil
from prepare_native_weapon_inline_chain import STAGE,WORK,sha,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    identity=WORK/'live_semantic_suite.json';assert not identity.exists()
    identity.write_text(json.dumps(dict(pid=p.pid,created=p.create_time()))+'\n',encoding='utf8')
    row=json.loads((WORK/'live_semantic_build.json').read_bytes())
    try:
        q=psutil.Process(row['pid'])
        if q.create_time()==row['created']:q.wait()
    except psutil.NoSuchProcess:pass
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    source=WORK/'prototype_src';dll=WORK/'prototype.dll';reports={}
    from verify_native_weapon_inline_chain import verify as chain
    out=WORK/'weapon_inline_chain_tests.json'
    try:chain(source,dll,out)
    except AssertionError:
        assert out.exists()
        diagnostic=json.loads(out.read_bytes())
        assert diagnostic['cases']==136128 and diagnostic['dll_sha256']==sha(dll) and not diagnostic['passed']
        print('Normal-versus-production differences retained; requiring matched normal proof and later complete actual PGO equality',flush=True)
    normal=WORK.parent/'buff_inline_types_prototype'
    chain(source,dll,WORK/'matched_normal_diagnostic.json',normal/'prototype_src',normal/'prototype.dll')
    from verify_weapon_inline_chain_buff_helpers import verify as helpers
    from verify_weapon_inline_chain_buff_methods import verify as methods
    from verify_weapon_inline_chain_builtins import verify as builtins
    from verify_weapon_inline_chain_truth import verify as truth
    from verify_weapon_inline_chain_private import verify as private
    from verify_weapon_inline_chain_display import verify as display
    from verify_weapon_inline_chain_control import verify as control
    for name,func,filename in [('helpers',helpers,'typed_helper_tests.json'),('methods',methods,'buff_integer_methods_tests.json'),
        ('builtins',builtins,'container_builtins_tests.json'),('truth',truth,'scalar_truth_tests.json'),
        ('private',private,'private_tests.json'),('display',display,'retained_display.json'),('control',control,'retained_control.json')]:
        print('Starting '+name,flush=True);r=func(source,dll,WORK/filename);assert r['passed'];reports[name]=dict(cases=r['cases'],report=filename,sha256=sha(WORK/filename));print('Passed '+name,flush=True)
    assert sum(r['cases'] for r in reports.values())==682304
    direct=json.loads(out.read_bytes());matched=json.loads((WORK/'matched_normal_diagnostic.json').read_bytes())
    assert matched['passed'] and matched['cases']==136128
    result=dict(passed=True,cases=818432,dll_sha256=sha(dll),retained_cases=682304,retained_reports=reports,
        production_comparison_report_sha256=sha(out),production_comparison_passed=direct['passed'],
        normal_vs_production_difference_cases=direct['difference_counts'],matched_normal_baseline_dll_sha256=matched['baseline_dll_sha256'],
        matched_normal_chain_cases=136128,matched_normal_diagnostic_sha256=sha(WORK/'matched_normal_diagnostic.json'),
        requires_actual_production_pgo_comparison_before_timing=True,source_projection=verify_projection(source),no_speed_claim=True)
    target=WORK/'semantic_preflight.json';assert not target.exists();target.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()

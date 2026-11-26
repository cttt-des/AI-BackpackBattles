"""Verify the entire retained simulator plus the new builtin differential cases."""
import json
import psutil
from prepare_native_buff_integer_kernel import WORK,sha,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    identity=WORK/'live_semantic_suite.json';assert not identity.exists()
    identity.write_text(json.dumps(dict(pid=p.pid,created=p.create_time()))+'\n',encoding='utf8')
    row=json.loads((WORK/'live_semantic_build.json').read_bytes())
    try:
        build=psutil.Process(row['pid'])
        if build.create_time()==row['created']:
            print('Awaiting exact semantic build '+str(build.pid),flush=True);build.wait()
    except psutil.NoSuchProcess:pass
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    from verify_buff_integer_builtins import verify as builtins
    from verify_buff_integer_truth import verify as truth
    from verify_buff_integer_private import verify as private
    from verify_buff_integer_display import verify as display
    from verify_buff_integer_control import verify as control
    from verify_native_buff_integer_methods import verify as methods
    source=WORK/'prototype_src';dll=WORK/'prototype.dll';rows={}
    for name,func,filename in [('methods',methods,'buff_integer_methods_tests.json'),('builtins',builtins,'container_builtins_tests.json'),('scalar_truth',truth,'scalar_truth_tests.json'),
            ('private',private,'private_tests.json'),('display',display,'retained_display.json'),('control',control,'retained_control.json')]:
        print('Starting '+name,flush=True);rows[name]=func(source,dll,WORK/filename)
        assert rows[name]['passed'];print('Passed '+name,flush=True)
    assert {k:r['cases'] for k,r in rows.items()}==dict(methods=14112,builtins=128128,scalar_truth=34400,private=234880,display=21888,control=44608)
    verify_projection(source)
    result=dict(passed=True,dll_sha256=sha(dll),cases={k:r['cases'] for k,r in rows.items()},total_cases=sum(r['cases'] for r in rows.values()),
        fixed200_and_original_counters_verified=True,all_prior_optimizations_retained=True,no_layout_changes=True,no_speed_claim=True)
    helper=json.loads((WORK/'typed_helper_tests.json').read_bytes());assert helper['passed'] and helper['dll_sha256']==sha(dll)
    result['cases']['typed_helpers']=helper['cases'];result['total_cases']+=helper['cases']
    assert result['total_cases']==682304
    (WORK/'semantic_suite.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()

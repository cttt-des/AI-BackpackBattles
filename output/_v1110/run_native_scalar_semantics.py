"""Wait for the exact full20 build and verify the full retained combination."""
import json
import subprocess
import sys
import psutil
from prepare_native_scalar_guards import STAGE,WORK,sha,verify_projection

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
    source=WORK/'prototype_src';dll=WORK/'prototype.dll';verify_projection(source)
    from verify_native_scalar_guards import verify as truth
    from verify_scalar_guard_private import verify as private
    from verify_scalar_guard_display import verify as display
    from verify_scalar_guard_control import verify as control
    rows={}
    for name,func,filename in [('scalar_truth',truth,'scalar_truth_tests.json'),('private',private,'private_tests.json'),
            ('display',display,'retained_display.json'),('control',control,'retained_control.json')]:
        print('Starting '+name,flush=True);rows[name]=func(source,dll,WORK/filename)
        assert rows[name]['passed'];print('Passed '+name,flush=True)
    assert rows['private']['cases']==234880 and rows['display']['cases']==21888 and rows['control']['cases']==44608
    result=dict(passed=True,dll_sha256=sha(dll),cases={k:v['cases'] for k,v in rows.items()},
        total_cases=sum(r['cases'] for r in rows.values()),fixed200_and_original_counters_verified=True,
        scalar_equality_already_deployed_and_not_reimplemented=True,retained_private_display_control_components=True,no_speed_claim=True)
    (WORK/'semantic_suite.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()

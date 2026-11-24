"""Copy the complete evaluation protocol with explicit current round references."""
import ast
import json
from prepare_native_object_routes import STAGE,WORK as PROBE,EXPECTED,ARCHIVE,once

OLD=STAGE/'native_perf50/callback_dispatch_bundle'
WORK=STAGE/'native_perf50/object_routes_bundle'

def update(text):
    text=text.replace('callback_dispatch_bundle','object_routes_bundle').replace('literal_spans_bundle','callback_dispatch_bundle')
    text=text.replace('callback_dispatch_prototype','object_routes_prototype')
    text=text.replace('prepare_native_callback_dispatch','prepare_native_object_routes')
    text=text.replace('prototype_native_callback_dispatch_bundle','prototype_native_object_routes_bundle')
    text=text.replace('c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1',EXPECTED)
    text=text.replace('a27d289f2009c3ad42145d61334d50647b2c060f',ARCHIVE)
    text=text.replace('native-callback-dispatch-','native-object-routes-')
    text=text.replace('verify_callback_dispatch_after_ab.py','verify_object_routes_after_ab.py')
    text=text.replace('before_object_routes_bundle_20261123','before_object_routes_bundle_20261124')
    return text

def main():
    assert not WORK.exists();WORK.mkdir()
    for path in OLD.glob('*.py'):
        if path.name in ('verified_bundle_pending.py','verify_callback_dispatch_after_ab.py','record_deployed_round.py'):continue
        text=update(path.read_text('utf8'))
        if path.name=='build_bundle.py':
            marker="    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py')"
            text=once(text,marker,"    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'freeze_pgo.py')],check=True)\n"+marker)
        if path.name=='validate_then_compare.py':
            text=once(text,"    run('verify_resolved.py','verify.log')","    run('verify_object_routes.py','object_routes_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='resume_build.py':
            text=once(text,"    exports.add('gd_diag_native_integer_grid_stat')","    exports.add('gd_diag_native_integer_grid_stat')\n    exports.add('gd_diag_native_object_route_stat')")
        if path.name=='inspect_variant.py':
            text=once(text,'    audit(1);before=[stat(i) for i in range(6)]',
                "    objects=sim.lib.gd_diag_native_object_route_stat;objects.argtypes=[ctypes.c_uint];objects.restype=ctypes.c_uint64\n    objects_before=[objects(i) for i in range(2)]\n    audit(1);before=[stat(i) for i in range(6)]")
            text=once(text,'    counts=[stat(i)-before[i] for i in range(6)]',
                "    object_counts=[objects(i)-objects_before[i] for i in range(2)]\n    assert object_counts==[901392,88491],object_counts\n    counts=[stat(i)-before[i] for i in range(6)]")
            text=once(text,"    report['variant_coverage']=", "    report['object_route_coverage']=dict(zip(('instance_methods','static_context_f32'),object_counts))\n    report['variant_coverage']=")
        if path.name=='audit_verify.py':
            text=once(text,'resolved_audit(1);resolved_before=',
                "object_stat=lib.gd_diag_native_object_route_stat;object_stat.argtypes=[ctypes.c_uint];object_stat.restype=ctypes.c_uint64\nobject_before=[object_stat(i) for i in range(2)]\nresolved_audit(1);resolved_before=")
            text=once(text,'raise SystemExit(exit_code)',
                "(out/'native_object_route_audit.json').write_text(json.dumps(dict(dll_sha256=report['dll_sha256'],verifier_exit_code=exit_code,counts=[object_stat(i)-object_before[i] for i in range(2)]),indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
        if path.name=='finish_gate.py':
            text=once(text,'    grid_counts=[0]*6','    grid_counts=[0]*6\n    object_counts=[0]*2')
            text=once(text,"        fights+=summary['total'];receipts.append(str(root))", "        obj=json.loads((root/'native_object_route_audit.json').read_bytes())\n        assert obj['dll_sha256']==dll and obj['verifier_exit_code']==0 and len(obj['counts'])==2\n        for i,count in enumerate(obj['counts']):object_counts[i]+=count\n        fights+=summary['total'];receipts.append(str(root))")
            text=once(text,"    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,", "    assert all(n>0 for n in object_counts)\n    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,'object_route_coverage':dict(zip(('instance_methods','static_context_f32'),object_counts)),")
        if path.name=='install_verified.py':
            text=once(text,"    fit = json.loads((WORK / 'bundle_load20.json').read_bytes())", "    assert post_ab['affected_object_route_cases']==320256\n    obj=json.loads((WORK/'object_routes_tests.json').read_bytes())\n    assert obj['passed'] and obj['dll_sha256']==actual and obj['active_route_assertions']==10240\n    fit = json.loads((WORK / 'bundle_load20.json').read_bytes())")
        if path.name=='verify_installed.py':
            text=once(text,"    assert read('callback_dispatch_tests.json')['dll_sha256']==actual", "    assert read('callback_dispatch_tests.json')['dll_sha256']==actual\n    obj=read('object_routes_tests.json')\n    assert obj['passed'] and obj['cases']==320256 and obj['active_route_assertions']==10240 and obj['dll_sha256']==actual\n    object_counts=[0,0]\n    for receipt in audit['receipts']:\n        row=json.loads((Path(receipt)/'native_object_route_audit.json').read_bytes())\n        assert row['dll_sha256']==actual and row['verifier_exit_code']==0\n        for i,count in enumerate(row['counts']):object_counts[i]+=count\n    assert all(n>0 for n in object_counts) and dict(zip(('instance_methods','static_context_f32'),object_counts))==audit['object_route_coverage']")
            text=once(text,"'callback_dispatch_cases':126192,", "'object_route_cases':320256,'object_route_coverage':audit['object_route_coverage'],'callback_dispatch_cases':126192,")
            text=text.replace("('callback_dispatch_tests.json','literal_span_tests.json'","('object_routes_tests.json','callback_dispatch_tests.json','literal_span_tests.json'")
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_object_routes import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'object_routes_tests.json')\n"
    (WORK/'verify_object_routes.py').write_text(wrapper,encoding='utf8')
    text=update((OLD/'verify_callback_dispatch_after_ab.py').read_text('utf8'))
    text=once(text,'from verify_native_callback_dispatch import verify','from verify_native_object_routes import verify as verify_objects\nfrom verify_native_callback_dispatch import verify')
    marker="    verify(WORK/'bundle_src',WORK/'bundle.dll',target/'callback_dispatch.json')"
    text=once(text,marker,"    obj=target/'object_routes';obj.mkdir()\n    verify_objects(WORK/'bundle_src',WORK/'bundle.dll',obj/'object_routes.json')\n"+marker)
    text=once(text,'affected_callback_cases=126192,','affected_object_route_cases=320256,affected_callback_cases=126192,')
    ast.parse(text);(WORK/'verify_object_routes_after_ab.py').write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        prior_trial_remote_archive=ARCHIVE,components=['96 measured object instance routes','original static context float conversion'],
        local_original_dll_cases=320256,local_independent_cases=dict(unknown_cpp_overrides=74496,real_handler_cases=245760),
        full_source_changes=['gd_rt.cpp','native_resolved_dispatch.hpp'],callback_dispatch_and_literal_spans_retained=True,
        instance_route_count_only=901392,static_f32_route_count_only=88491,new_layout_changes=False)
    plan['required'][0]='Retained regressions plus320256 object routes,126192 callback and5184 literal cases;707-source reproduction and freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared full20/new18PGO,320256+retained126192+5184, fixed200 bounded24(+8),strict2604 and first raw/calibration24')

if __name__=='__main__':main()

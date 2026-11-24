"""Carry the frozen evaluation gates forward, adding the affected-path checks."""
import ast
import json
from pathlib import Path
from prepare_native_private_snapshots import STAGE,EXPECTED,ARCHIVE

OLD=STAGE/'native_perf50/object_routes_bundle'
WORK=STAGE/'native_perf50/private_snapshots_bundle'

def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old));return text.replace(old,new,1)

def update(text):
    text=text.replace('object_routes_bundle','private_snapshots_bundle').replace('callback_dispatch_bundle','object_routes_bundle')
    text=text.replace('object_routes_prototype','private_snapshots_prototype')
    text=text.replace('prototype_native_object_routes_bundle','prototype_native_private_snapshots_bundle')
    text=text.replace('prepare_native_object_routes','prepare_native_private_snapshots')
    text=text.replace('80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a',EXPECTED)
    text=text.replace('72dd9c1575087596ad0409b939104a0113033e40',ARCHIVE)
    text=text.replace('native-object-routes-','native-private-snapshots-')
    return text

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        text=update(p.read_text('utf8'))
        if p.name in ('prepare_regeneration.py','test_regeneration_guards.py','verify_installed.py'):
            text=text.replace('707','708')
        if p.name=='build_bundle.py':
            text=once(text,"    objects=Path(tempfile.mkdtemp(prefix='native-private-snapshots-'))", "    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds';cache.mkdir(exist_ok=True)\n    build_root=Path(tempfile.mkdtemp(prefix='private-snapshots-formal-',dir=cache))\n    objects=build_root/'objects';objects.mkdir();scratch=build_root/'scratch';scratch.mkdir()\n    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))\n    tempfile.tempdir=str(scratch)\n    save('persistent_build_directory.json',dict(root=str(build_root),objects=str(objects),scratch=str(scratch)))")
            text=once(text,"link_flags=('-Wl,--exclude-all-symbols',str(definition)))", "link_flags=('-save-temps=obj','-Wl,--exclude-all-symbols',str(definition)))")
            text=once(text,"hot_units=HOT_UNITS)\n    shutil.copyfile(dll", "hot_units=HOT_UNITS,link_flags=('-save-temps=obj',))\n    shutil.copyfile(dll")
        if p.name=='resume_build.py':
            text=once(text,"    exports.add('gd_diag_native_object_route_stat')", "    exports.add('gd_diag_native_object_route_stat')\n    exports.add('gd_diag_native_private_snapshot_stat')")
        if p.name=='validate_then_compare.py':
            text=once(text,"    run('verify_object_routes.py','object_routes_tests.log')", "    run('verify_object_routes.py','object_routes_tests.log')\n    run('verify_private_snapshots.py','private_snapshots_tests.log')")
        if p.name=='inspect_variant.py':
            marker="    report['object_route_coverage']="
            text=once(text,'    audit(1);before=[stat(i) for i in range(6)]', "    private_stat=sim.lib.gd_diag_native_private_snapshot_stat;private_stat.argtypes=[ctypes.c_uint];private_stat.restype=ctypes.c_uint64\n    private_before=[private_stat(i) for i in range(4)]\n    audit(1);before=[stat(i) for i in range(6)]")
            text=once(text,marker,"    private_counts=[private_stat(i)-private_before[i] for i in range(4)]\n    expected_private=json.loads((Path(__file__).resolve().parents[1]/'private_snapshots_prototype/build.json').read_bytes())['new_counts']\n    assert private_counts==list(expected_private.values()),(private_counts,expected_private)\n    report['private_snapshot_coverage']=dict(zip(expected_private,private_counts))\n"+marker)
        if p.name=='verify_object_routes_after_ab.py':
            text=once(text,'from verify_native_object_routes import verify as verify_objects','from verify_native_object_routes import verify as verify_objects\nfrom verify_native_private_snapshots import verify as verify_private')
            text=once(text,"    obj=target/'object_routes';obj.mkdir()", "    priv=target/'private_snapshots';priv.mkdir()\n    verify_private(WORK/'bundle_src',WORK/'bundle.dll',priv/'correctness.json')\n    obj=target/'object_routes';obj.mkdir()")
            text=once(text,'affected_object_route_cases=320256,','affected_private_snapshot_cases=234880,affected_object_route_cases=320256,')
        if p.name=='install_verified.py':
            text=once(text,"    assert post_ab['affected_object_route_cases']==320256", "    assert post_ab['affected_private_snapshot_cases']==234880\n    private=json.loads((WORK/'private_snapshots_tests.json').read_bytes())\n    assert private['passed'] and private['cases']==234880 and private['dll_sha256']==actual\n    assert post_ab['affected_object_route_cases']==320256")
        if p.name=='verify_installed.py':
            text=once(text,"    obj=read('object_routes_tests.json')", "    private=read('private_snapshots_tests.json')\n    assert private['passed'] and private['cases']==234880 and private['dll_sha256']==actual\n    assert read('post_ab_directed_regressions.json')['affected_private_snapshot_cases']==234880\n    obj=read('object_routes_tests.json')")
            text=once(text,"'object_route_cases':320256,", "'private_snapshot_cases':234880,'object_route_cases':320256,")
            text=text.replace("('object_routes_tests.json','callback_dispatch_tests.json'", "('private_snapshots_tests.json','object_routes_tests.json','callback_dispatch_tests.json'")
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_private_snapshots import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'private_snapshots_tests.json')\n"
    (WORK/'verify_private_snapshots.py').write_text(wrapper,encoding='utf8')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        prior_trial_remote_archive=ARCHIVE,components=['bounded private integer views','deferred event identity byte snapshots'],
        local_original_dll_cases=161792,helper_cases=73088,full_source_changes=['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp'],
        added_source_files=['native_private_snapshots.hpp'],candidate_source_files=708,new_layout_changes=False)
    plan['required'][0]='234880 affected cases plus retained320256/126192/5184 and all existing regressions;708-source reproduction;full20/fresh18PGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared private snapshots evaluation; no timing or deployment started')

if __name__=='__main__':main()

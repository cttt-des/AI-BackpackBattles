"""Prepare one complete property/control candidate against verified8e7."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/item_locality_bundle'
WORK=STAGE/'native_perf50/property_control_bundle'
BASE_SHA='8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa'
ARCHIVE='ccecb628a9e36e05e6491b6fd1bfbe3a47d0af1e'

def main():
    WORK.mkdir()
    names=('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
           'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py',
           'run_comparison.py','assess_resolved.py','audit_verify.py','test_full_regeneration.py')
    for name in names:
        text=(OLD/name).read_text('utf8').replace('item_locality_bundle','property_control_bundle')
        text=text.replace('native-item-locality-','native-property-control-')
        text=text.replace('444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc',BASE_SHA)
        if name=='build_bundle.py':
            text=text.replace("ARCHIVE='d4938c4e097d6c2b4ec971e544f9f18df3486e0a'",f"ARCHIVE='{ARCHIVE}'")
            start=text.index('from prototype_native_property_control_bundle import optimize as _locality')
            end=text.index('from resume_build import',start)
            text=text[:start]+'from prototype_native_property_control_bundle import optimize\n\n'+text[end:]
        if name=='resume_build.py':text=text.replace("    exports.add('gd_diag_native_variant_stat')","    exports.add('gd_diag_native_variant_stat')\n    exports.add('gd_diag_native_property_stat')")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'eager_trace_bundle'","OLD=WORK.parent/'item_locality_bundle'")
            text=text.replace("'native_perf50/eager_trace_bundle'","'native_perf50/item_locality_bundle'")
        if name=='validate_then_compare.py':
            text=text.replace("    run('profile_baseline.py','baseline_profile.log')\n",'')
            text=text.replace("    run('verify_resolved.py','verify.log')", "    run('generate_property_tests.py','property_test_generation.log')\n    run('verify_resolved.py','verify.log')")
        if name=='verify_resolved.py':
            text=text.replace('    tests=(("test_native_item_locality.cpp","item_locality_test.json",[]),',
                '    tests=(("test_native_properties.cpp","property_test.json",["-I",str(WORK)]),\n           ("test_native_item_locality.cpp","item_locality_test.json",["-DGD_HOT_CONTROL_CANDIDATE"]),')
        if name=='inspect_variant.py':
            text=text.replace("    variant_before=[variant(i) for i in range(10)]", "    variant_before=[variant(i) for i in range(10)]\n    prop=sim.lib.gd_diag_native_property_stat;prop.argtypes=[ctypes.c_uint];prop.restype=ctypes.c_uint64\n    prop_before=[prop(i) for i in range(2)]")
            text=text.replace("    assert sum(report['variant_coverage'].values())>0", "    report['property_coverage']=dict(zip(('field_hits','selected_fallback'),[prop(i)-prop_before[i] for i in range(2)]))\n    assert report['property_coverage']['field_hits']>0\n    assert sum(report['variant_coverage'].values())>0")
        ast.parse(text,filename=name)
        (WORK/name).write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE_SHA,verified_remote_backup=ARCHIVE,
        components=['compact cooldown/timer/gems control fields','shared exact generated pure field getter rows'],
        new_object_or_context_layout=True,formal_results='pending')
    plan['layout_scope']='CoreItem layout and internal NativeMethodRow layout change; BattleCtx/GdObj/ClassMeta unchanged. Full20/fresh18 mandatory.'
    plan['required_before_comparison'].insert(0,'All674 classes selected-field oracle checks and unknown/copy/resource_path/fallback callbacks')
    plan['recent_baseline_profile']='post_eager_trace_profile/profile_depth64.json;2083 samples/2079 replay roots. No concurrent profiling during timing.'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(WORK)

if __name__=='__main__':main()

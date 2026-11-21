"""Prepare exact metadata/typed-initialization composition against verified1426."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/property_control_bundle'
WORK=STAGE/'native_perf50/type_constructor_bundle'
BASE_SHA='14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548'
ARCHIVE='eb898e2b5c80970a1ef71611c57423c377dab078'

def main():
    WORK.mkdir(exist_ok=True);assert not (WORK/'bundle_src').exists()
    names=('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
           'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py',
           'run_comparison.py','assess_resolved.py','audit_verify.py','generate_property_tests.py')
    for name in names:
        text=(OLD/name).read_text('utf8').replace('property_control_bundle','type_constructor_bundle')
        text=text.replace('native-property-control-','native-type-constructor-')
        text=text.replace('8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa',BASE_SHA)
        if name=='build_bundle.py':text=text.replace("ARCHIVE='ccecb628a9e36e05e6491b6fd1bfbe3a47d0af1e'",f"ARCHIVE='{ARCHIVE}'")
        if name=='resume_build.py':text=text.replace("    exports.add('gd_diag_native_property_stat')","    exports.add('gd_diag_native_property_stat')\n    exports.add('gd_diag_native_type_constructor_stat')")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'item_locality_bundle'","OLD=WORK.parent/'property_control_bundle'")
            text=text.replace("'native_perf50/item_locality_bundle'","'native_perf50/property_control_bundle'")
        if name=='validate_then_compare.py':
            text=text.replace("    run('generate_property_tests.py','property_test_generation.log')", "    run('generate_property_tests.py','property_test_generation.log')\n    run('generate_type_constructor_tests.py','type_constructor_test_generation.log')")
        if name=='verify_resolved.py':
            text=text.replace('    tests=(("test_native_properties.cpp"', '    tests=(("test_native_type_constructor.cpp","type_constructor_test.json",["-I",str(WORK)]),\n           ("test_native_properties.cpp"',1)
        if name=='inspect_variant.py':
            text=text.replace('    prop_before=[prop(i) for i in range(2)]', '    prop_before=[prop(i) for i in range(2)]\n    tc=sim.lib.gd_diag_native_type_constructor_stat;tc.argtypes=[ctypes.c_uint];tc.restype=ctypes.c_uint64\n    tc_before=[tc(i) for i in range(4)]')
            text=text.replace("    assert report['property_coverage']['field_hits']>0", "    report['type_constructor_coverage']=dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),[tc(i)-tc_before[i] for i in range(4)]))\n    assert report['type_constructor_coverage']['type_hits']>0 and report['type_constructor_coverage']['fused_initializations']>0\n    assert report['property_coverage']['field_hits']>0")
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE_SHA,verified_remote_backup=ARCHIVE,
        components=['exact generated metadata and ancestor flags','typed allocation and init_fields fusion'],formal_results='pending')
    plan['layout_scope']='NativeMethodRow internal layout only; GdObj/BattleCtx/ClassMeta and item layouts unchanged. Full20/fresh18 mandatory.'
    plan['required_before_comparison'].insert(0,'All674 metadata predicates and alloc-plus-init graph comparisons; unknown/copied metadata and _init order/RNG')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(WORK)

if __name__=='__main__':main()

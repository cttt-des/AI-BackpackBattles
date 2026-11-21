"""Prepare a128-method/64-field composition against the deployed1426 baseline."""
import ast
import hashlib
import json
from pathlib import Path
import shutil
import tempfile
from prototype_native_hot_coverage_bundle import optimize

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/type_constructor_bundle'
WORK=STAGE/'native_perf50/hot_coverage_bundle'


def main():
    WORK.mkdir(exist_ok=True);assert not (WORK/'bundle_src').exists()
    names=('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
        'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py',
        'run_comparison.py','assess_resolved.py','audit_verify.py','generate_property_tests.py',
        'generate_type_constructor_tests.py')
    for name in names:
        text=(OLD/name).read_text('utf8').replace('type_constructor_bundle','hot_coverage_bundle')
        text=text.replace('native-type-constructor-','native-hot-coverage-')
        if name=='resume_build.py':
            text=text.replace("    exports.add('gd_diag_native_type_constructor_stat')", "    exports.add('gd_diag_native_type_constructor_stat')\n    exports.add('gd_diag_native_hot_slot_stat')")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'property_control_bundle'", "OLD=WORK.parent/'type_constructor_bundle'")
            text=text.replace("'native_perf50/property_control_bundle'", "'native_perf50/type_constructor_bundle'")
        if name=='generate_property_tests.py':
            text=text.replace('PropertyTestRef,32','PropertyTestRef,64').replace('classes,32 columns','classes,64 columns')
        if name=='verify_resolved.py':
            text=text.replace('    tests=(("test_native_type_constructor.cpp"', '    tests=(("test_native_hot_coverage.cpp","hot_coverage_test.json",[]),\n           ("test_native_type_constructor.cpp"',1)
        if name=='inspect_variant.py':
            text=text.replace('    tc_before=[tc(i) for i in range(4)]', '    tc_before=[tc(i) for i in range(4)]\n    hot=sim.lib.gd_diag_native_hot_slot_stat;hot.argtypes=[ctypes.c_uint];hot.restype=ctypes.c_uint64\n    hot_before=[hot(i) for i in range(2)]')
            text=text.replace("    assert report['type_constructor_coverage']['type_hits']", "    report['hot_slot_coverage']=dict(zip(('new_method_hits','new_field_hits'),[hot(i)-hot_before[i] for i in range(2)]))\n    assert all(value>0 for value in report['hot_slot_coverage'].values())\n    assert report['type_constructor_coverage']['type_hits']",1)
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    with tempfile.TemporaryDirectory(prefix='native-hot-coverage-preflight-') as directory:
        scratch=Path(directory).resolve();assert scratch.is_relative_to(Path(tempfile.gettempdir()).resolve())
        native=scratch/'native'
        shutil.copytree(STAGE/'sim_native/native_sim_cpp/native_sim',native,
            ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        design=optimize(native)
        assert design['method_slots']==128 and design['property_slots']==64
        assert design['old112_methods_and32_fields_preserved']
        original=STAGE/'sim_native/native_sim_cpp/native_sim'
        pattern=__import__('re').compile(r'^bool (Gd__\w+)::(?:get_prop|call_method)\([^\n]*\n(.*?)^\}',__import__('re').M|__import__('re').S)
        switches=0
        for path in (native/'gen/shards').glob('*.cpp'):
            before=pattern.findall((original/path.relative_to(native)).read_text('utf8'))
            after=pattern.findall(path.read_text('utf8'))
            assert before==after;switches+=len(before)
        assert switches==1348
    record={'passed':True,'method_slots':128,'property_slots':64,'shared_property_rows':design['shared_property_rows'],
        'unchanged_original_getter_and_method_switches':switches,'old112_methods_and32_fields_preserved':True,
        'new_methods':design['hot_method_additions'],'new_properties':design['selected_properties'][32:],
        'source_and_dll_not_deployed':True}
    (WORK/'transform_preflight.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(components=design['components'],method_slots=128,property_slots=64,formal_results='pending',
        retained_previous_candidate='742ef705e583387510341a9f9055ba80bb6160a1f6290f55ef68ac6970fd081a',
        retained_previous_evidence='No stable gain confirmed; not deployed. New package judged as a whole against1426.',
        layout_scope='NativeMethodRow and NativePropertyRow only; object/context/ClassMeta/item layouts unchanged.')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(record,indent=2))


if __name__=='__main__':main()

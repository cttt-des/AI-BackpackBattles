"""Prepare typed pure reads against the backed-up deployed4013 source."""
import ast
import json
from pathlib import Path
import re
import shutil
import tempfile
from prototype_native_typed_read_bundle import optimize

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/hot_coverage_bundle'
WORK=STAGE/'native_perf50/typed_read_bundle'
BASE='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
ARCHIVE='60963d0804db5dc01a5cace6d3fe56c658bfae13'


def main():
    WORK.mkdir(exist_ok=True);assert not (WORK/'bundle_src').exists()
    for name in ('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
        'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py','run_comparison.py',
        'assess_resolved.py','audit_verify.py','generate_property_tests.py','generate_type_constructor_tests.py'):
        text=(OLD/name).read_text('utf8').replace('hot_coverage_bundle','typed_read_bundle')
        text=text.replace('native-hot-coverage-','native-typed-read-')
        text=text.replace('14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548',BASE)
        text=text.replace('eb898e2b5c80970a1ef71611c57423c377dab078',ARCHIVE)
        if name=='resume_build.py':
            text=text.replace("    exports.add('gd_diag_native_hot_slot_stat')", "    exports.add('gd_diag_native_hot_slot_stat')\n    exports.add('gd_diag_native_typed_read_stat')")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'type_constructor_bundle'", "OLD=WORK.parent/'hot_coverage_bundle'")
            text=text.replace("'native_perf50/type_constructor_bundle'", "'native_perf50/hot_coverage_bundle'")
        if name=='inspect_variant.py':
            text=text.replace('    hot_before=[hot(i) for i in range(2)]', '    hot_before=[hot(i) for i in range(2)]\n    typed=sim.lib.gd_diag_native_typed_read_stat;typed.argtypes=[ctypes.c_uint];typed.restype=ctypes.c_uint64\n    typed_before=[typed(i) for i in range(2)]')
            text=text.replace("    assert all(value>0 for value in report['hot_slot_coverage'].values())", "    report['typed_read_coverage']=dict(zip(('property_reads','pure_method_reads'),[typed(i)-typed_before[i] for i in range(2)]))\n    assert all(value>0 for value in report['typed_read_coverage'].values())\n    assert report['typed_read_coverage']['property_reads']==report['property_coverage']['field_hits']\n    assert all(value>0 for value in report['hot_slot_coverage'].values())")
        # New pure-method fixtures are prepared before the final validation begins.
        if name=='validate_then_compare.py':
            text=text.replace("    run('generate_type_constructor_tests.py','type_constructor_test_generation.log')", "    run('generate_type_constructor_tests.py','type_constructor_test_generation.log')\n    run('generate_typed_read_tests.py','typed_read_test_generation.log')")
        if name=='verify_resolved.py':
            text=text.replace('    tests=(("test_native_hot_coverage.cpp"', '    tests=(("test_native_typed_reads.cpp","typed_read_test.json",["-I",str(WORK)]),\n           ("test_native_hot_coverage.cpp"',1)
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    with tempfile.TemporaryDirectory(prefix='native-typed-read-preflight-') as directory:
        scratch=Path(directory).resolve();assert scratch.is_relative_to(Path(tempfile.gettempdir()).resolve())
        native=scratch/'native';original=STAGE/'sim_native/native_sim_cpp/native_sim'
        shutil.copytree(original,native,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        result=optimize(native)
        for path in (native/'gen/shards').glob('*.cpp'):assert path.read_bytes()==(original/path.relative_to(native)).read_bytes()
        headers=list((native/'gen/hdrs').glob('*.hpp'));assert len(headers)==674
        assert all(path.read_bytes()==(original/path.relative_to(native)).read_bytes() for path in headers)
        assert (native/'gd_rt.hpp').read_bytes()==(original/'gd_rt.hpp').read_bytes()
    preflight={'passed':True,'baseline_dll_sha256':BASE,'read_rows':result['shared_property_rows'],
        'getter_table_rows_preserved':43,'method_slots':128,'property_slots':64,
        'pure_method_symbols':result['typed_read_design']['pure_method_symbols'],
        'all16_shards_and674_headers_and_context_layout_unchanged':True,
        'original_table_bytes':43*64*8,'new_shared_table_plus_tags_bytes':43*64*8+result['shared_property_rows']*128,
        'actual_runtime_gain':'Not measured; evaluate the whole package'}
    (WORK/'transform_preflight.json').write_text(json.dumps(preflight,indent=2)+'\n',encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=result['components'],formal_results='pending',
        layout_scope=result['layout_scope'],required_new_tests='All pure-method field bindings vs original virtual dispatch; all64 original field oracles; tag alignment; inherited and custom override fallbacks')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(preflight,indent=2))


if __name__=='__main__':main()

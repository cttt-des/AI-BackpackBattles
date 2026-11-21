"""Prepare the retained read package plus exact scalar arithmetic fast paths."""
import ast
import json
from pathlib import Path
import re
import shutil
import tempfile
from prototype_native_scalar_math_bundle import optimize
from build_native_hot_lto import HOT_UNITS

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/typed_read_bundle'
WORK=STAGE/'native_perf50/scalar_math_bundle'


def main():
    assert 'sym_ids' not in HOT_UNITS and len(HOT_UNITS)==18
    WORK.mkdir(exist_ok=True);assert not (WORK/'bundle_src').exists()
    names=('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
        'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py','run_comparison.py',
        'assess_resolved.py','audit_verify.py','generate_property_tests.py','generate_type_constructor_tests.py',
        'generate_typed_read_tests.py')
    for name in names:
        text=(OLD/name).read_text('utf8').replace('typed_read_bundle','scalar_math_bundle')
        text=text.replace('native-typed-read-','native-scalar-math-')
        if name=='resume_build.py':
            text=text.replace("    exports.add('gd_diag_native_typed_read_stat')", "    exports.add('gd_diag_native_typed_read_stat')\n    exports.add('gd_diag_native_numeric_stat')")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'hot_coverage_bundle'", "OLD=WORK.parent/'typed_read_bundle'")
            text=text.replace("'native_perf50/hot_coverage_bundle'", "'native_perf50/typed_read_bundle'")
        if name=='inspect_variant.py':
            text=text.replace('    typed_before=[typed(i) for i in range(2)]', '    typed_before=[typed(i) for i in range(2)]\n    numeric=sim.lib.gd_diag_native_numeric_stat;numeric.argtypes=[ctypes.c_uint];numeric.restype=ctypes.c_uint64\n    numeric_before=[numeric(i) for i in range(6)]')
            text=text.replace("    assert all(value>0 for value in report['typed_read_coverage'].values())", "    report['numeric_coverage']=dict(zip(('add_int','add_real','add_fallback','div_int','div_real','div_fallback'),[numeric(i)-numeric_before[i] for i in range(6)]))\n    assert report['numeric_coverage']['add_real']>0 and report['numeric_coverage']['div_real']>0\n    assert all(value>0 for value in report['typed_read_coverage'].values())")
        if name=='validate_then_compare.py':
            text=text.replace("    run('verify_resolved.py','verify.log')", "    run('verify_numeric_barrier.py','numeric_barrier.log')\n    run('verify_numeric_math.py','numeric_math.log')\n    run('verify_resolved.py','verify.log')")
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    with tempfile.TemporaryDirectory(prefix='native-scalar-math-preflight-') as directory:
        scratch=Path(directory).resolve();assert scratch.is_relative_to(Path(tempfile.gettempdir()).resolve())
        native=scratch/'native';original=STAGE/'sim_native/native_sim_cpp/native_sim'
        shutil.copytree(original,native,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        result=optimize(native)
        pattern=re.compile(r'^bool (Gd__\w+)::(?:get_prop|call_method)\([^\n]*\n(.*?)^\}',re.M|re.S)
        switches=0
        for path in (native/'gen/shards').glob('*.cpp'):
            before=pattern.findall((original/path.relative_to(native)).read_text('utf8'))
            after=pattern.findall(path.read_text('utf8'));assert before==after;switches+=len(before)
        assert switches==1348
        assert (native/'gd_rt.cpp').read_bytes()==(original/'gd_rt.cpp').read_bytes()
        assert (native/'gd_rt.hpp').read_bytes()==(original/'gd_rt.hpp').read_bytes()
        assert all(path.read_bytes()==(original/path.relative_to(native)).read_bytes() for path in (native/'gen/hdrs').glob('*.hpp'))
    preflight={'passed':True,'baseline_dll_sha256':result['baseline_dll_sha256'],'numeric_call_sites':result['numeric_call_sites'],
        'unchanged_original_virtual_switches':switches,'original_arithmetic_evaluators_unchanged':True,
        'object_and_context_layout_unchanged':True,'argument_signatures_unchanged':True,
        'non_lto_fallback_unit':'sym_ids','floating_options_unchanged':True,'retained_typed_reads':True}
    (WORK/'transform_preflight.json').write_text(json.dumps(preflight,indent=2)+'\n',encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(components=result['components'],formal_results='pending',
        retained_typed_read_candidate=result['retained_candidate'],
        numerical_contract='Same finite numeric operation/conversion; overflow, nonfinite values, zero real divisors and nonnumeric operands use the untouched original evaluator through non-LTO wrappers.',
        required_new_tests='Baseline/candidate arithmetic bits, kind and container differential; argument callback order, alias mutation and RNG; object-file proof that fallback wrappers are outside LTO.')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(preflight,indent=2))


if __name__=='__main__':main()

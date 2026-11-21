"""Archive the failed arithmetic probe and create a fresh ordered candidate."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/scalar_math_bundle'
WORK=STAGE/'native_perf50/scalar_math_ordered_bundle'


def main():
    assert not WORK.exists()
    baseline=json.loads((OLD/'numeric_baseline_cases.json').read_bytes())
    candidate=json.loads((OLD/'numeric_candidate_cases.json').read_bytes())
    mismatches=[i for i,(a,b) in enumerate(zip(baseline['case_hashes'],candidate['case_hashes'])) if a!=b]
    assert len(mismatches)==12 and all(i<5775 for i in mismatches)
    decision={'status':'rejected_before_timing','dll_sha256':'993cd7ed2a0ac35886a376dbdb4adad8be3a264e9eff9c1a998b31db49cb751a',
        'numeric_cases':candidate['cases'],'mismatch_indices':mismatches,
        'cause':'Both float operands are different NaNs: unchanged public add/multiply recompiled by LTO selected the opposite NaN payload.',
        'deployed':False,'formal_comparisons_started':False,'next':'Pin the deployed operand choice only for two-NaN add/multiply and compare result bits plus floating exception flags against the actual baseline DLL.'}
    (OLD/'final_decision.json').write_text(json.dumps(decision,indent=2)+'\n',encoding='utf8')
    WORK.mkdir()
    for path in OLD.glob('*.py'):
        text=path.read_text('utf8').replace('scalar_math_bundle','scalar_math_ordered_bundle')
        if path.name=='verify_numeric_math.py':
            text=text.replace('test_native_numeric_math.cpp','test_native_numeric_math_ordered.cpp')
            text=text.replace("'argument_order_alias_mutation_and_rng_unchanged':True,", "'argument_order_alias_mutation_and_rng_unchanged':True,'floating_exception_flags_equal_to_actual_baseline':True,")
        if path.name=='save_checkpoint.py':
            insertion="    audit=json.loads"
            text=text.replace(insertion,"    paths.update(STAGE/p for p in ('prototype_native_scalar_math_bundle.py','setup_scalar_math_bundle.py','setup_scalar_math_qualification.py','test_native_numeric_math.cpp','prototype_native_scalar_math_ordered_bundle.py','setup_scalar_math_ordered_bundle.py','test_native_numeric_math_ordered.cpp'))\n    rejected=WORK.parent/'scalar_math_bundle'\n    paths.update(p for p in rejected.iterdir() if p.is_file())\n    paths.update(p for p in (rejected/'bundle_src').rglob('*') if p.is_file())\n"+insertion,1)
            # This qualification setup was never a separate root file for the
            # ordered revision; retain the actual concrete setup instead.
            text=text.replace("'setup_scalar_math_ordered_qualification.py',",'')
        ast.parse(text,filename=path.name)
        (WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    source=(STAGE/'test_native_numeric_math.cpp').read_text('utf8').replace('#include <bit>','#include <bit>\n#include <cfenv>')
    source=source.replace('const auto expected=original(op,reference,a,b);const auto result=candidate(op,fast,a,b);',
        'std::feclearexcept(FE_ALL_EXCEPT);const auto expected=original(op,reference,a,b);const int expected_flags=std::fetestexcept(FE_ALL_EXCEPT);\n        std::feclearexcept(FE_ALL_EXCEPT);const auto result=candidate(op,fast,a,b);const int actual_flags=std::fetestexcept(FE_ALL_EXCEPT);')
    source=source.replace('if(!same(expected,result)){','if(!same(expected,result) || expected_flags!=actual_flags){')
    source=source.replace('<<" got="<<hash(result)<<"\\n"','<<" got="<<hash(result)<<" flags="<<expected_flags<<","<<actual_flags<<"\\n"')
    source=source.replace('mix(mix(mix(hash(result),op),ai),bi)','mix(mix(mix(mix(hash(result),actual_flags),op),ai),bi)')
    assert 'expected_flags!=actual_flags' in source
    (STAGE/'test_native_numeric_math_ordered.cpp').write_text(source,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan['components'].append('Actual-baseline NaN payload and floating-exception operand choice')
    plan['new_object_or_context_layout']=False
    plan['required_before_comparison'].append('5903 actual baseline/candidate arithmetic cases including result bits and all floating exception flags')
    plan['superseded_arithmetic_probe']=decision
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared fresh ordered numeric candidate; rejected probe and raw cases retained')


if __name__=='__main__':main()

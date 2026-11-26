"""Require full old/new actual PGO observations, including every fallback."""
import json
from prepare_native_weapon_chain import STAGE,EXPECTED,sha
WORK=STAGE/'native_perf50/weapon_chain_bundle'

def main():
    checks=WORK/'buff_integer_checks';p=checks/'typed_helper_tests.json';r=json.loads(p.read_bytes())
    assert r['passed'] and r['cases']==204288 and r['operation_checks']==806160
    assert r['dll_sha256']==sha(WORK/'bundle.dll') and r['baseline_dll_sha256']==EXPECTED
    assert r['unchanged_fallback_runtime_cross_compiler_hash_equal']
    raw=checks/'typed_helper_tests_checks'
    for n,h in r['raw_sha256'].items():assert sha(raw/n)==h
    a=json.loads((raw/'baseline_cases.json').read_bytes());b=json.loads((raw/'candidate_cases.json').read_bytes())
    assert a==b and a['passed'] and a['cases']==204288
    result=dict(passed=True,cases=204288,operation_checks=806160,dll_sha256=r['dll_sha256'],baseline_dll_sha256=EXPECTED,
        all_original_and_candidate_pgo_observations_equal_including_float_nan_complex_and_overflow_fallbacks=True,
        four_rounding_and_four_daz_ftz_modes=True,no_additional_execution_or_timing=True,helper_receipt_sha256=sha(p))
    out=WORK/'buff_full_pgo_tests.json';assert not out.exists();out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result),flush=True)

if __name__=='__main__':main()

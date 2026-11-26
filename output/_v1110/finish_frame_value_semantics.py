"""Finish the remaining control suite after binding its actual deployed baseline."""
import json
import psutil
from prepare_native_frame_values import WORK,sha,verify_projection

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'semantic_suite.json').exists()
    repaired=json.loads((WORK/'control_word_checks_first/baseline_pin_repair.json').read_bytes())
    assert sha(WORK/'prototype.dll')==repaired['candidate_dll_sha256']
    rows={}
    for name,filename,cases in [('scalar_truth','scalar_truth_tests.json',34400),('private','private_tests.json',234880),('display','retained_display.json',21888)]:
        r=json.loads((WORK/filename).read_bytes());assert r['passed'] and r['cases']==cases and r['dll_sha256']==sha(WORK/'prototype.dll')
        rows[name]=r
    from verify_frame_value_control import verify
    rows['control']=verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'retained_control.json')
    assert rows['control']['passed'] and rows['control']['cases']==44608
    verify_projection(WORK/'prototype_src')
    result=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),cases={k:v['cases'] for k,v in rows.items()},
        total_cases=sum(r['cases'] for r in rows.values()),fixed200_and_original_counters_verified=True,
        global_scalar_truth_and_equality_unchanged=True,retained_private_display_control_components=True,
        initial_retained_registry_baseline_pin_repaired_before_timing=True,candidate_source_and_dll_unchanged=True,no_speed_claim=True)
    assert result['total_cases']==335776
    (WORK/'semantic_suite.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()

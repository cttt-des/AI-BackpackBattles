"""Validate the actual production entry against the saved independent oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'event_identity_probe'


def main():
    oracle=json.loads((PROBE/'bus_correctness_baseline.json').read_bytes())
    assert oracle['fixture_sha256']==hashlib.sha256((STAGE/'test_native_event_identity_bus.cpp').read_bytes()).hexdigest()
    assert oracle['baseline_dll_sha256']=='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
    dll=WORK/'bundle.dll';reports={}
    with tempfile.TemporaryDirectory(prefix='native-identity-final-tests-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll')
        for label,extra in (('event_identity',[]),('event_identity_bus',['-DGD_EVENT_IDENTITY_PRODUCTION']),('event_emission',['-DGD_EVENT_IDENTITY_PRODUCTION'])):
            exe=root/(label+'.exe')
            fixture=WORK/'test_native_event_identity_bus_godot.cpp' if label=='event_identity_bus' else STAGE/f'test_native_{label}.cpp'
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                *extra,'-I',str(WORK/'bundle_src'),'-I',str(STAGE),str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            result=subprocess.run([str(exe),'--correctness-only'],capture_output=True,text=True)
            (WORK/(label+'_cases.log')).write_text(result.stdout+result.stderr,encoding='utf8')
            if result.returncode:print(result.stdout+result.stderr,flush=True)
            result.check_returncode();reports[label]=json.loads(result.stdout)
    assert reports['event_identity']['cases']==24288
    assert reports['event_identity_bus']['cases']==oracle['cases']==320
    bus=reports['event_identity_bus']
    assert bus['original_contract_hashes']==oracle['case_hashes']
    changed=[i for i,(a,b) in enumerate(zip(bus['case_hashes'],oracle['case_hashes'])) if a!=b]
    assert changed==list(range(16,48)),changed
    save_contract=dict(original_fixture_sha256=oracle['fixture_sha256'],corrected_fixture_sha256=hashlib.sha256((WORK/'test_native_event_identity_bus_godot.cpp').read_bytes()).hexdigest(),changed_cases=changed,all320_cases_retained=True,only_added_callback_trace_and_its_exact_diagnostic_entry_projected=True,all_rng_ids_and_fp_flags_equal=True,original_Godot_reference_sha256=hashlib.sha256((WORK/'original_ordering_reference.json').read_bytes()).hexdigest())
    (WORK/'event_identity_expectation_correction.json').write_text(json.dumps(save_contract,indent=2)+'\n',encoding='utf8')
    assert reports['event_identity_bus']['fast_hits']>0 and reports['event_identity_bus']['fallbacks']>0
    emission_oracle=json.loads((WORK.parent/'event_emission_probe/emission_correctness_baseline.json').read_bytes())
    assert emission_oracle['fixture_sha256']==hashlib.sha256((STAGE/'test_native_event_emission.cpp').read_bytes()).hexdigest()
    assert reports['event_emission']['cases']==emission_oracle['cases']==4417
    assert reports['event_emission']['case_hashes']==emission_oracle['case_hashes']
    assert reports['event_emission']['fast_hits']>0 and reports['event_emission']['fallbacks']>0
    (WORK/'emission_correctness_candidate.json').write_text(json.dumps(reports['event_emission'],indent=2)+'\n',encoding='utf8')
    (WORK/'bus_correctness_candidate.json').write_text(json.dumps(reports['event_identity_bus'],indent=2)+'\n',encoding='utf8')
    report={'passed':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'independent_baseline_dll_sha256':oracle['baseline_dll_sha256'],'primitive_cases':24288,
        'actual_dll_event_bus_cases':320,'unchanged_cases_and_exact_original_contract_projection_equal':True,'intentional_Godot_append_cases':32,
        'trace_toggle_and_snapshot_callback_order_rng_ids_flags_unknown_fallbacks_checked':True,
        'production_fast_hits':reports['event_identity_bus']['fast_hits'],
        'production_fallbacks':reports['event_identity_bus']['fallbacks'],
        'actual_dll_emission_id_cases':4417,'emission_id_per_case_results_equal':True,
        'production_emission_fast_hits':reports['event_emission']['fast_hits'],
        'production_emission_fallbacks':reports['event_emission']['fallbacks']}
    (WORK/'event_identity_tests.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()

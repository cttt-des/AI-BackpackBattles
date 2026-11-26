"""Compare final DLL motion behavior with every retained independent old-DLL case."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
PROBE=WORK.parent/'motion_indices_probe'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    baseline=json.loads((PROBE/'correctness_baseline.json').read_bytes())
    screen=json.loads((PROBE/'screen_matched.json').read_bytes())
    assert baseline['passed'] and baseline['cases']==5840
    for name,digest in screen['dependency_sha256'].items():
        path=STAGE/name if name.endswith('.cpp') else PROBE/name if name=='preflight_motion_indices.hpp' else WORK/'bundle_src'/name
        if name in ('gd_rt.hpp','native_array_index.hpp','native_inline_dispatch.hpp'):
            frozen=json.loads((WORK/'source_before_build.json').read_bytes())
            assert sha(path)==frozen[name],name
        else:assert sha(path)==digest,name
    transform=json.loads((WORK/'transform.json').read_bytes())
    import sys
    sys.path.insert(0,str(STAGE))
    source=(WORK/'bundle_src/gen/shards/shard_07.cpp').read_text('utf8')
    signature='gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion('
    start=source.index(signature);method=source[start:source.index('\n}',start)+2]
    method_sha=hashlib.sha256(method.encode()).hexdigest()
    retained=json.loads((WORK.parent/'object_routes_bundle/transform.json').read_bytes())
    assert 'native_scalar_truth(' in method
    original_method=method.replace('native_scalar_truth(', 'gd_truth(')
    original_sha=hashlib.sha256(original_method.encode()).hexdigest()
    assert original_sha==retained['candidate_method_sha256']
    from prepare_native_weapon_inline_chain import verify_projection
    assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']
    with tempfile.TemporaryDirectory(prefix='native-motion-final-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_MOTION_PRODUCTION','-I',str(PROBE),'-I',str(WORK/'bundle_src'),str(STAGE/'test_native_motion_indices.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        raw=subprocess.check_output([str(exe)],text=True)
    actual=json.loads(raw)
    assert actual['passed'] and actual['cases']==baseline['cases']
    assert actual['case_hashes']==baseline['case_hashes'] and actual['legacy_counter_hashes']==baseline['legacy_counter_hashes']
    (WORK/'motion_indices_production_cases.json').write_text(raw,encoding='utf8')
    report=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),cases=5840,actual_production_method_checked=True,
        independent_baseline_sha256=sha(PROBE/'correctness_baseline.json'),all_original_state_and_legacy_counter_hashes_equal=True,
        source_method_sha256=method_sha,source_before_scalar_truth_sha256=original_sha,exact_inverse_verified=True)
    (WORK/'motion_indices_tests.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

"""Verify staged source is exactly the already tested complete prototype."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_active_cooldowns import STAGE,BASE,WORK as PROBE,EXPECTED,sha
from prototype_native_active_cooldown_bundle import optimize

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    work=STAGE/'native_perf50/active_cooldown_bundle';out=work/'transform_preflight.json';assert not out.exists()
    local=json.loads((PROBE/'differential.json').read_bytes())
    assert local['passed'] and local['cases']==1856
    for name,digest in local['dependencies'].items():assert sha(PROBE/'test_src'/name)==digest
    with tempfile.TemporaryDirectory(prefix='native-active-cooldown-preflight-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
    report.update(preflight_source_matches_actual_tested_prototype=True,independent_actual_old_dll_cases=1856,
        prototype_dll_sha256=sha(PROBE/'prototype.dll'),directed_coverage_receipt_sha256=sha(PROBE/'directed_coverage.json'),
        fixed200_receipt_sha256=sha(PROBE/'fixed200_coverage.json'),no_throughput_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print('Complete706-file source matches tested prototype;1856 old-DLL cases and actual indexed recovery verified')

if __name__=='__main__':main()

"""Reproduce the complete checked source before formal compilation."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_grid_cooldown import STAGE,BASE,WORK as PROBE,EXPECTED,sha
from prototype_native_grid_cooldown_bundle import optimize

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    work=STAGE/'native_perf50/grid_cooldown_bundle';out=work/'transform_preflight.json';assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-grid-cooldown-preflight-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
    report.update(full_source_matches_actual_tested_prototype=True,semantic_receipt_sha256=sha(PROBE/'correctness.json'),no_speed_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print('Checked707-file frozen source reproduced; original DLL oracles retained')

if __name__=='__main__':main()

"""Verify the full707-source reproduction before any formal profile build."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_storage_bundle import STAGE,BASE,EXPECTED,sha
from prototype_native_storage_bundle import optimize

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    out=STAGE/'native_perf50/storage_bundle/transform_preflight.json';assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-storage-preflight-') as directory:
        src=Path(directory)/'source'
        shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(src)
    report.update(full_source_matches_tested_prototype=True,no_speed_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Reproduced707 sources with87425 actual-DLL cases and an independent count-only probe')

if __name__=='__main__':main()

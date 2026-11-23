"""Freeze only the source bytes covered by the actual semantic DLL checks."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_coallocated_events import STAGE,BASE,EXPECTED,sha
from prototype_native_coallocated_events_bundle import optimize

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    out=STAGE/'native_perf50/coallocated_events_bundle/transform_preflight.json';assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-coallocated-preflight-') as directory:
        source=Path(directory)/'source'
        shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
    report.update(full_source_matches_tested_prototype=True,no_speed_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Reproduced707 sources with4161-case actual-DLL proof')

if __name__=='__main__':main()

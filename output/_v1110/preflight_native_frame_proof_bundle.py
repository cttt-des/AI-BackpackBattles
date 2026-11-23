"""Check exact source reproduction before full instrumentation and PGO."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_frame_proof import STAGE,BASE,EXPECTED,sha
from prototype_native_frame_proof_bundle import optimize

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    work=STAGE/'native_perf50/frame_proof_bundle';out=work/'transform_preflight.json';assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-frame-proof-preflight-') as directory:
        source=Path(directory)/'source'
        shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
    report.update(full_source_matches_actual_tested_prototype=True,no_speed_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Reproduced707 sources, unchanged layouts, actual-DLL3073-case proof retained')

if __name__=='__main__':main()

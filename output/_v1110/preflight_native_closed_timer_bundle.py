"""Check exact frozen source equality before paying for a fresh full PGO build."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_closed_timer_bundle import optimize,STAGE
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/closed_timer_bundle'

def main():
    with tempfile.TemporaryDirectory(prefix='native-closed-timer-preflight-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
        for name in ('gd_rt.cpp','gen/shards/shard_03.cpp'):
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(source/name)],check=True)
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Frozen closed-input source matches checked prototype; deployment unchanged')

if __name__=='__main__':main()

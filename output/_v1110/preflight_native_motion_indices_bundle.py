"""Check the frozen production transform before the full PGO build."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_motion_indices_bundle import optimize,STAGE
WORK=STAGE/'native_perf50/motion_indices_bundle'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    WORK.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='native-motion-source-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
        subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(source/'gen/shards/shard_07.cpp')],check=True)
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Frozen bounded-motion transform syntax checked; deployed source unchanged')

if __name__=='__main__':main()

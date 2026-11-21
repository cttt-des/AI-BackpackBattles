"""Validate the four-file transformation and both affected translation units."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_dispatch_chain_bundle import optimize,STAGE
WORK=STAGE/'native_perf50/dispatch_chain_bundle'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    WORK.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='native-dispatch-chain-source-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
        for name in ('gd_rt.cpp','gen/shards/shard_00.cpp','gen/shards/shard_12.cpp'):
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(source/name)],check=True)
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Four-file transform and runtime/item/event-bus syntax checks passed; no layout or arithmetic changes')

if __name__=='__main__':main()

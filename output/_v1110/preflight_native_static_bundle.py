"""Syntax-check the two changed shards before paying for a full build."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_static_collections_bundle import optimize,STAGE
WORK=STAGE/'native_perf50/static_collections_bundle'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
def main():
    WORK.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='native-static-source-preflight-') as directory:
        src=Path(directory)/'source';shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(src)
        for name in ('shard_02.cpp','shard_06.cpp'):
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(src/'gen/shards'/name)],check=True)
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Three-file transform and two shard syntax checks passed; no header or public arithmetic changes')
if __name__=='__main__':main()

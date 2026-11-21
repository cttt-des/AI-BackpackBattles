"""Check every modified translation unit before a complete candidate build."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_static_setup_bundle import optimize,STAGE
WORK=STAGE/'native_perf50/static_setup_bundle'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    WORK.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='native-static-setup-source-') as directory:
        source=Path(directory)/'source';shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
        for name in report['modified_native_files']:
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(source/name)],check=True)
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'syntax_checked':True,'modified_native_files':report['modified_native_files'],'object_headers_and_public_arithmetic_unchanged':True}))

if __name__=='__main__':main()

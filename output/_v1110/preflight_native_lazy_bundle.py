"""Check exact source changes and parse the one changed shard before full PGO."""
import ast
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_lazy_diagnostics_bundle import optimize
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/lazy_diagnostics_bundle'
def main():
    for p in WORK.glob('*.py'):ast.parse(p.read_text('utf8'),filename=str(p))
    with tempfile.TemporaryDirectory(prefix='native-lazy-source-preflight-') as directory:
        src=Path(directory)/'source'
        shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(src)
        subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only','-I',str(src),str(src/'gen/shards/shard_00.cpp')],check=True)
        assert len(list((src/'gen/hdrs').glob('*.hpp')))==674
        assert all(p.read_bytes()==(BASE/p.relative_to(src)).read_bytes() for p in (src/'gen/hdrs').glob('*.hpp'))
    report.update(source_syntax_checked=True,all_674_headers_identical=True)
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Three-file transform, frozen709-file source baseline,674 identical headers, changed shard syntax passed')
if __name__=='__main__':main()

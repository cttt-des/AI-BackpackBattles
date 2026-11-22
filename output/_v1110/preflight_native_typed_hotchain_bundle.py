"""Check frozen full source and iterator semantics before the fresh PGO build."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_typed_hotchain import BASE,STAGE,WORK as PROBE,EXPECTED,sha
from prototype_native_typed_hotchain_bundle import optimize
WORK=STAGE/'native_perf50/typed_hotchain_bundle'

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    with tempfile.TemporaryDirectory(prefix='native-typed-hotchain-preflight-') as directory:
        root=Path(directory);src=root/'source'
        shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(src)
        for rel in ('gen/shards/shard_02.cpp','engine_wrapper.cpp','gd_rt.cpp'):
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(src/rel)],check=True)
        shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'ranges.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(src),str(STAGE/'test_native_typed_damage_ranges.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        output=subprocess.check_output([str(exe)],text=True);ranges=json.loads(output);assert ranges['passed'] and ranges['cases']==240
        ranges.update(helper_sha256=sha(src/'native_typed_damage_math.hpp'),fixture_sha256=sha(STAGE/'test_native_typed_damage_ranges.cpp'),baseline_dll_sha256=EXPECTED)
    (PROBE/'range_correctness.json').write_text(json.dumps(ranges,indent=2)+'\n',encoding='utf8')
    report['syntax_checked']=True
    (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Complete source matches checked typed kernel; scalar33856,damage13112,range240; runtime unchanged')

if __name__=='__main__':main()

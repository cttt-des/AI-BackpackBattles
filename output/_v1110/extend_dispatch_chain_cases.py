"""Add callback surface boundaries without rerunning the first cost screen."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/dispatch_chain_probe'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    old=json.loads((WORK/'correctness_baseline.json').read_bytes())
    screen=json.loads((WORK/'screen.json').read_bytes())
    assert old['cases']==310440 and hashlib.sha256((WORK/'test_screen_snapshot.cpp').read_bytes()).hexdigest()==screen['test_source_sha256']
    with tempfile.TemporaryDirectory(prefix='native-dispatch-chain-extended-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'cases.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_dispatch_chain.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
    result=json.loads(raw)
    assert result['passed'] and result['cases']==310500 and result['case_hashes'][:old['cases']]==old['case_hashes']
    (WORK/'correctness_baseline_extended.json').write_text(raw,encoding='utf8')
    report={'passed':True,'cases':result['cases'],'new_surface_cases':60,'original310440_hashes_unchanged':True,
        'test_source_sha256':hashlib.sha256((STAGE/'test_native_dispatch_chain.cpp').read_bytes()).hexdigest(),
        'revision':'Keep original FuncRef/nonnull/argc guard before evaluating args[0]; no remeasurement of original cost screen',
        'scope':'Preflight adapter and boundary coverage; behavior and callback helper algorithms unchanged'}
    (WORK/'extended_cases.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

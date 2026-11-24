"""Locate a baseline fixture failure; never alter tested simulator bytes."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import sys
from prepare_native_object_routes import WORK,STAGE,ACCEPTED,sha

def main():
    folder=WORK/'fixture_debug_1';resume='--continue-compile' in sys.argv
    if resume:assert folder.exists() and not (folder/'run.log').exists()
    else:assert not folder.exists();folder.mkdir()
    source=STAGE/'test_native_object_routes.cpp';text=source.read_text('utf8')
    if resume:assert (folder/'original_fixture.cpp').read_bytes()==source.read_bytes()
    else:
        (folder/'original_fixture.cpp').write_bytes(source.read_bytes())
        shutil.copyfile(WORK/'baseline_object_routes_first.log',folder/'original_baseline.log')
        shutil.copyfile(STAGE/'object_routes_correctness_first.log',folder/'original_driver.log')
    for marker,trace in [
        ('    gd::BattleCtx owner(4096),caller(4096);','    if(flags==0 && row==0 && mode==0 && shared==0)std::cerr<<"unknown "<<method<<std::endl;\n'),
        ('    gd::BattleCtx owner(8192),other(4096);','    if(value==0 && flags==0 && row==0 && api==0 && round==0 && daz==0)std::cerr<<"known "<<type<<std::endl;\n')]:
        assert text.count(marker)==1;text=text.replace(marker,trace+marker,1)
    debug=folder/'debug.cpp';debug.write_text(text,encoding='utf8',newline='\n')
    (folder/'fixture_identity.json').write_text(json.dumps(dict(original_fixture_sha256=sha(source),baseline_dll_sha256=sha(ACCEPTED/'bundle.dll')))+'\n',encoding='utf8')
    build=Path(tempfile.mkdtemp(prefix='native-object-route-debug-'))
    (folder/'objects.txt').write_text(str(build),encoding='utf8')
    shutil.copyfile(ACCEPTED/'bundle.dll',build/'libgdcore.dll')
    exe=build/'debug.exe'
    with (folder/('compile_second.log' if resume else 'compile.log')).open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-g','-O0','-std=c++20','-ffp-contract=off',
            '-I',str(ACCEPTED/'bundle_src'),'-I',str(WORK),str(debug),str(build/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,check=True)
    with (folder/'run.log').open('wb') as log:
        result=subprocess.run(['D:/mingw64/bin/gdb.exe','-batch','-ex','run','-ex','bt','--args',str(exe)],stdout=log,stderr=subprocess.STDOUT)
    print('Diagnostic exit',result.returncode)

if __name__=='__main__':main()

"""Await the identified semantic build; never restart a lost observation."""
import json
from pathlib import Path
import subprocess
import sys
import shutil
import tempfile
import psutil
from prepare_native_coallocated_events import STAGE,WORK,sha

def main():
    own=psutil.Process();matches=[]
    for p in psutil.process_iter(['pid','cmdline']):
        try:
            args=p.info['cmdline'] or []
            if p.pid!=own.pid and p.exe()==own.exe() and any(Path(x).name=='build_native_coallocated_events.py' for x in args):matches.append(p)
        except (psutil.NoSuchProcess,psutil.AccessDenied):continue
    assert len(matches)<=1,[(p.pid,p.cmdline()) for p in matches]
    if matches:
        process=matches[0];print('Waiting on identified build PID '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    report=json.loads((WORK/'build.json').read_bytes())
    assert report['passed'] and report['dll_sha256']==sha(WORK/'prototype.dll')
    for script in ('verify_coallocated_frame.py','verify_coallocated_params.py'):
        log=WORK/(script.removesuffix('.py')+'_first.log');assert not log.exists()
        with log.open('w',encoding='utf8') as output:
            subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/script)],stdout=output,stderr=subprocess.STDOUT,check=True)
        print('Passed '+script,flush=True)
    with tempfile.TemporaryDirectory(prefix='native-coallocated-storage-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'prototype.dll',root/'libgdcore.dll');exe=root/'storage.exe'
        with (WORK/'storage_compile_first.log').open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-ffp-contract=off',
                '-I',str(WORK/'prototype_src'),str(STAGE/'test_coallocated_event_storage.cpp'),
                str(root/'libgdcore.dll'),'-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
        actual=json.loads(subprocess.check_output([str(exe)],text=True))
        assert actual['passed'] and actual['cases']==64
        actual.update(dll_sha256=sha(WORK/'prototype.dll'),fixture_sha256=sha(STAGE/'test_coallocated_event_storage.cpp'))
        out=WORK/'storage_correctness.json';assert not out.exists();out.write_text(json.dumps(actual,indent=2)+'\n',encoding='utf8')
    print('Actual-DLL frame and event differential checks finished; no performance claim',flush=True)

if __name__=='__main__':main()

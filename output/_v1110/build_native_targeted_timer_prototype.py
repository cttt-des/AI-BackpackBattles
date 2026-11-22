"""Full rebuild for a layout-changing semantic prototype, without PGO/timing claims."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import psutil
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,ARCHIVE,sha
from build_native_hot_lto import build_dll

def main():
    global WORK
    if '--closed' in sys.argv:
        from prepare_native_closed_timer import WORK as closed_work
        WORK=closed_work
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    expected=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert expected=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    repo=STAGE.parents[1]
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified'],cwd=repo).decode().split()[0]==ARCHIVE
    files=sorted(p for p in BASE.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'));assert len(files)==704
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=repo,input=''.join(f'{ARCHIVE}:{p.relative_to(repo).as_posix()}\n' for p in files).encode())
    stream=io.BytesIO(data)
    for p in files:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==p.read_bytes(),p
        assert stream.read(1)==b'\n'
    if '--resume-reviewed-source' in sys.argv:
        assert json.loads((WORK/'reviewed_fix.json').read_bytes())['changed_files']==['gd_rt.cpp']
        objects=Path((WORK/'objects.txt').read_text('utf8'))
        assert objects.resolve().parent==Path(tempfile.gettempdir()).resolve() and objects.name.startswith('native-targeted-timer-prototype-')
        invalid=[]
        for obj in objects.glob('*.o'):
            check=subprocess.run(['D:/mingw64/bin/nm.exe','--defined-only',str(obj)],capture_output=True)
            if check.returncode or not check.stdout:
                invalid.append(obj.name);obj.unlink()
        (WORK/'resume_object_check.json').write_text(json.dumps(dict(invalid_interrupted_objects_removed=invalid),indent=2)+'\n',encoding='utf8')
    else:
        objects=Path(tempfile.mkdtemp(prefix='native-targeted-timer-prototype-'))
        (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',MAKE='D:/mingw64/bin/mingw32-make.exe')
    print('Verified704 remote source blobs; rebuilding all20 units with new layout, max2 below-normal jobs',flush=True)
    build_dll(source,out,2,hot_units=set())
    assert expected=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    report=dict(dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,full20_units=True,
        source_manifest_sha256=sha(WORK/'transform.json'),prototype_only=True,hot_units=[],no_performance_claim=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    inspect='inspect_closed_timer_fixed200.py' if '--closed' in sys.argv else 'inspect_targeted_timer_fixed200.py'
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/inspect)],check=True)
    if '--closed' in sys.argv:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'verify_closed_timer_prototype.py')],check=True)

if __name__=='__main__':main()

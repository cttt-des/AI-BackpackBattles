"""Build every unit for the new BattleCtx layout; this is not a timing build."""
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_active_cooldowns import STAGE,BASE,WORK,EXPECTED,ARCHIVE,sha
from build_native_hot_lto import build_dll

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    repo=STAGE.parents[1]
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified'],cwd=repo).decode().split()[0]==ARCHIVE
    files=sorted(p for p in BASE.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==705
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=repo,input=''.join(f'{ARCHIVE}:{p.relative_to(repo).as_posix()}\n' for p in files).encode())
    stream=io.BytesIO(data)
    for p in files:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==p.read_bytes(),p
        assert stream.read(1)==b'\n'
    objects=Path(tempfile.mkdtemp(prefix='native-active-cooldown-prototype-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',MAKE='D:/mingw64/bin/mingw32-make.exe')
    print('Verified705 remote source blobs; all20 units, max2 below-normal jobs',flush=True)
    build_dll(source,out,2,hot_units=set())
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    shutil.copyfile(__file__,WORK/'build_driver_first.py')
    report=dict(dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        full20_units=True,source_manifest_sha256=sha(WORK/'transform.json'),prototype_only=True,no_performance_claim=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report),flush=True)

if __name__=='__main__':main()

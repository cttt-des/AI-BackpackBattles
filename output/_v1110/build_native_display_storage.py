"""Full-layout semantic build in persistent ASCII storage; no speed experiment."""
import json
import os
from pathlib import Path
import tempfile
import psutil
from prepare_native_display_storage import STAGE,BASE,WORK,EXPECTED,sha,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'prototype.dll').exists()
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    source=WORK/'prototype_src';verify_projection(source)
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    root=Path(tempfile.mkdtemp(prefix='display-storage-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),
        NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',MAKE='D:/mingw64/bin/mingw32-make.exe')
    tempfile.tempdir=str(scratch)
    receipt=dict(pid=p.pid,created=p.create_time(),root=str(root),object_directory=str(objects),source=str(source),full20=True,not_for_timing=True)
    (WORK/'live_semantic_build.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    from build_native_hot_lto import build_dll,HOT_UNITS
    build_dll(source,WORK/'prototype.dll',2,hot_units=HOT_UNITS,link_flags=('-save-temps=obj',))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    assert all((objects/(name+'.o')).is_file() for name in names)
    verify_projection(source)
    result=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        recompiled_units=20,reused_objects=0,full_layout_rebuild=True,not_for_timing=True,
        source_manifest_sha256=sha(WORK/'transform.json'))
    (WORK/'build.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps(result),flush=True)

if __name__=='__main__':main()

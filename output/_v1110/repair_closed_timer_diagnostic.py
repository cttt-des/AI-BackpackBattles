"""Add the missing mode query after the first closed prototype build terminates."""
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import psutil
from prepare_native_closed_timer import BASE,WORK,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';manifest=WORK/'transform.json'
    old=json.loads(manifest.read_bytes())
    assert old['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    file=source/'engine_wrapper.cpp';text=file.read_text('utf8');assert 'gd_diag_native_timer_closed_mode' not in text
    assert (WORK/'build.json').exists() and not (WORK/'correctness.json').exists()
    shutil.copyfile(WORK/'prototype.dll',WORK/'prototype_without_mode_export.dll')
    shutil.copyfile(manifest,WORK/'transform_before_mode_export.json')
    text+='\nextern "C" int gd_diag_native_timer_closed_mode(){return tl_battle_ctx.native_timer_watch.closed_world?1:0;}\n'
    file.write_text(text,encoding='utf8',newline='\n');old['source_sha256']['engine_wrapper.cpp']=sha(file)
    manifest.write_text(json.dumps(old,indent=2)+'\n',encoding='utf8')
    objects=Path((WORK/'objects.txt').read_text('utf8'));assert objects.name.startswith('native-targeted-timer-prototype-')
    before={p.name:sha(p) for p in objects.glob('*.o') if p.name!='engine_wrapper.o'};assert len(before)==19
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    subprocess.run([compiler,*flags,'-c',str(file),'-o',str(objects/'engine_wrapper.o')],check=True)
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert before=={p.name:sha(p) for p in objects.glob('*.o') if p.name!='engine_wrapper.o'}
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    if (WORK/'fixed200_coverage.json').exists():shutil.copyfile(WORK/'fixed200_coverage.json',WORK/'fixed200_before_mode_export.json');(WORK/'fixed200_coverage.json').unlink()
    (WORK/'mode_export_repair.json').write_text(json.dumps(dict(reason='Only add mode diagnostic query omitted by a failed shell quoting command before first build; no runtime algorithm changes',
        reused_objects=19,recompiled_units=1,dll_sha256=sha(WORK/'prototype.dll')),indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED

if __name__=='__main__':main()

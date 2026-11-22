"""Repair the proven foreign-owner counterexample and rebuild only its kernel TU."""
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    failed=json.loads((WORK/'ownership_differential_revision1.json').read_bytes());assert not failed['passed'] and len(failed['mismatches']['state_hashes'])==64
    assert not (WORK/'prototype_revision1.dll').exists()
    shutil.copyfile(WORK/'prototype.dll',WORK/'prototype_revision1.dll')
    shutil.copyfile(WORK/'prototype_src/native_targeted_timers.hpp',WORK/'native_targeted_timers_revision1.hpp')
    shutil.copyfile(WORK/'transform.json',WORK/'transform_revision1.json')
    source=WORK/'prototype_src';design=json.loads((WORK/'transform.json').read_bytes())
    assert design['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    shutil.copyfile(STAGE/'native_targeted_timers.hpp',source/'native_targeted_timers.hpp')
    design['source_sha256']['native_targeted_timers.hpp']=sha(source/'native_targeted_timers.hpp');design['ownership_revision']=2
    (WORK/'transform.json').write_text(json.dumps(design,indent=2)+'\n',encoding='utf8')
    objects=Path((WORK/'objects.txt').read_text('utf8'));assert objects.name.startswith('native-targeted-timer-prototype-')
    before={p.name:sha(p) for p in objects.glob('*.o') if p.name!='shard_03.o'};assert len(before)==19
    shutil.copyfile(objects/'shard_03.o',objects/'shard_03_revision1.o.saved')
    module=runpy.run_path(str(source/'build_windows.py'));compiler='D:/mingw64/bin/g++.exe';flags=module['COMMON']
    subprocess.run([compiler,*flags,'-c',str(source/'gen/shards/shard_03.cpp'),'-o',str(objects/'shard_03.o')],check=True)
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(name+'.o')) for name in names]],check=True)
    assert before=={p.name:sha(p) for p in objects.glob('*.o') if p.name!='shard_03.o'}
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    (WORK/'ownership_repair.json').write_text(json.dumps(dict(revision=2,previous_dll_sha256=failed['candidate_dll_sha256'],dll_sha256=sha(WORK/'prototype.dll'),
        reused_identical_objects=19,recompiled_kernel_units=1,changes=['owned character/grid/item/gem storage and context checks','timer context checks','no float conversion for eligibility']),indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print('Ownership revision2 kernel rebuilt;19 other objects unchanged; deployment untouched',flush=True)

if __name__=='__main__':main()

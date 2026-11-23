"""Check the actual factory's contiguous storage, growth and alias lifetime."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prepare_native_coallocated_events import STAGE,WORK,sha

def verify(source,dll,out):
    assert not out.exists()
    with tempfile.TemporaryDirectory(prefix='native-coallocated-storage-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll');exe=root/'storage.exe'
        with (out.parent/'storage_compile_separate.log').open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-ffp-contract=off',
                '-I',str(source),str(STAGE/'test_coallocated_event_storage.cpp'),str(root/'libgdcore.dll'),
                '-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
        actual=json.loads(subprocess.check_output([str(exe)],text=True))
    assert actual['passed'] and actual['cases']==64
    actual.update(dll_sha256=sha(dll),fixture_sha256=sha(STAGE/'test_coallocated_event_storage.cpp'))
    out.write_text(json.dumps(actual,indent=2)+'\n',encoding='utf8');print(json.dumps(actual))
    return actual

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'storage_correctness.json')

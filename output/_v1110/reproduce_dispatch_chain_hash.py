"""Keep a negative witness for a boundary found before the full build."""
from pathlib import Path
import shutil
import subprocess
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/dispatch_chain_probe'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
with tempfile.TemporaryDirectory(prefix='native-behavior-hash-negative-') as directory:
    root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'negative.exe'
    subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(WORK/'hash_negative.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
    output=subprocess.check_output([str(exe)],text=True)
(WORK/'hash_negative.json').write_text(output,encoding='utf8')
print(output)

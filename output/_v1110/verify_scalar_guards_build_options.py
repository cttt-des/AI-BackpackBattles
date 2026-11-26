"""Freeze actual release objects and verify the unchanged compiler/FP policy."""
import json
from pathlib import Path
import re
import subprocess
from prepare_native_scalar_guards import STAGE,ACCEPTED,EXPECTED,sha
from build_native_hot_lto import HOT_UNITS

WORK=STAGE/'native_perf50/scalar_guards_bundle'

def options(obj):
    raw=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-s','-j','.gnu.lto_.opts',str(obj)],text=True)
    data=bytearray()
    for line in raw.splitlines():
        parts=line.split()
        if not parts or not re.fullmatch('[0-9a-fA-F]+',parts[0]):continue
        for cell in parts[1:5]:
            if not re.fullmatch('[0-9a-fA-F]{2,8}',cell) or len(cell)%2:break
            data.extend(bytes.fromhex(cell))
    text=bytes(data).replace(b'\0',b'').decode('utf8')
    flags=re.findall("'([^']*)'",text)
    assert '-ffp-contract=off' in flags and '-O3' in flags and '-flto=2' in flags
    assert any(x.startswith('-fprofile-use=') for x in flags)
    return text,flags

def main():
    out=WORK/'compiled_option_receipt.json';assert not out.exists()
    root=Path(json.loads((WORK/'persistent_build_directory.json').read_bytes())['objects'])
    baseline=json.loads((ACCEPTED/'release_objects.json').read_bytes())
    old_root=Path(baseline['object_directory'])
    names=baseline['objects_sha256'];assert len(names)==20
    saved=WORK/'compiled_options';assert not saved.exists();saved.mkdir()
    objects={};records={}
    for name in sorted(names):
        # Original recovery receipts use object filenames, not source stems.
        filename=name if name.endswith('.o') else name+'.o'
        objects[filename]=sha(root/filename)
        if Path(filename).stem not in HOT_UNITS:continue
        assert sha(old_root/filename)==names[name]
        text,actual=options(root/filename);_,reference=options(old_root/filename)
        strip=lambda flags:[x for x in flags if not x.startswith('-fprofile-use=')]
        assert strip(actual)==strip(reference),(filename,actual,reference)
        assert '-fipa-pta' not in actual
        (saved/(Path(filename).stem+'.txt')).write_text(text+'\n',encoding='utf8')
        records[filename]=dict(object_sha256=objects[filename],options_sha256=sha(saved/(Path(filename).stem+'.txt')))
    assert len(records)==18
    digest=sha(WORK/'bundle.dll')
    receipt=dict(passed=True,dll_sha256=digest,baseline_dll_sha256=EXPECTED,checked_hot_objects=18,
        actual_object_option_sections=True,fp_contract_off_all=True,compiler_options_identical_except_profile_directory=True,
        compared_with_verified_5DDB_objects=True,no_compiler_pta=True,objects=records)
    out.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    (WORK/'release_objects.json').write_text(json.dumps(dict(object_directory=str(root),dll_sha256=digest,
        objects_sha256=objects),indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(passed=True,checked_hot_objects=18,release_objects=20,dll_sha256=digest)),flush=True)

if __name__=='__main__':main()

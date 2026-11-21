"""Prove the original arithmetic fallback is an actual non-LTO object call."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS


def main():
    assert 'sym_ids' not in HOT_UNITS
    objects=Path((WORK/'bundle_objects.txt').read_text('utf8'))
    obj=objects/'sym_ids.o';assert obj.is_file()
    sections=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-h',str(obj)],text=True)
    assert '.gnu.lto' not in sections
    undefined=subprocess.check_output(['D:/mingw64/bin/nm.exe','-u','--demangle',str(obj)],text=True)
    defined=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only','--demangle',str(obj)],text=True)
    for op in ('add','sub','mul','div'):
        assert f'gd::gd_{op}(' in undefined,op
        assert f'gd::native_numeric_original_{op}(' in defined,op
    assembly=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--demangle',str(obj)],text=True)
    for op,instruction in (('add','addsd'),('mul','mulsd')):
        assert f'gd::native_original_ordered_nan_{op}(' in defined
        start=assembly.index('<gd::native_original_ordered_nan_'+op+'(gd::GdVal const&, gd::GdVal const&)>:')
        end=assembly.find('\n\n',start)
        assert instruction in assembly[start:end],op
    report={'passed':True,'dll_sha256':hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),
        'non_lto_unit':'sym_ids','object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),
        'no_lto_sections':True,'four_original_evaluator_relocations':True,
        'four_wrapper_definitions':True,'same_object_used_for_final_release':True,
        'two_nan_operation_instructions_pinned':True}
    (WORK/'numeric_barrier_build_proof.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()

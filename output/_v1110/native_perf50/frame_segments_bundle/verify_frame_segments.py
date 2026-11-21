"""Check the built candidate against unchanged original methods and baseline math."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from prototype_native_frame_segments_bundle import frame_helper


def main():
    dll=WORK/'bundle.dll';source=WORK/'bundle_src'
    # Recheck any extended fixture payloads against the deployed oracle, after
    # compilation has finished and before starting either candidate executable.
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'run_frame_segments_preflight.py')],check=True)
    preflight=json.loads((WORK/'frame_preflight.json').read_bytes())
    helper,original=frame_helper(source)
    assert preflight['helper_sha256']==hashlib.sha256(helper.encode()).hexdigest()
    assert preflight['original_item_physics_sha256']==hashlib.sha256(original.encode()).hexdigest()
    obj=Path((WORK/'bundle_objects.txt').read_text('utf8'))/'sym_ids.o'
    sections=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-h',str(obj)],text=True)
    assert '.gnu.lto' not in sections
    assembly=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--demangle',str(obj)],text=True)
    for op,instruction in (('add','addsd'),('mul','mulsd')):
        start=assembly.index('<gd::native_original_ordered_nan_'+op+'(gd::GdVal const&, gd::GdVal const&)>:')
        end=assembly.find('\n\n',start)
        assert instruction in assembly[start:end]
    reports={}
    with tempfile.TemporaryDirectory(prefix='native-frame-verification-') as directory:
        root=Path(directory);shutil.copyfile(dll,root/'libgdcore.dll')
        for label in ('frame_segments','timer_chunks'):
            exe=root/(label+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                '-I',str(source),str(STAGE/f'test_native_{label}.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            completed=subprocess.run([str(exe)],capture_output=True,text=True)
            (WORK/(label+'_cases.log')).write_text(completed.stdout+completed.stderr,encoding='utf8')
            print(completed.stdout+completed.stderr,flush=True);completed.check_returncode()
            reports[label]=json.loads(completed.stdout)
    assert reports['frame_segments']['cases']==6912 and reports['timer_chunks']['cases']==9554
    math={}
    for label,headers,library in (('baseline',STAGE/'sim_native/native_sim_cpp/native_sim',STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'),('candidate',source,dll)):
        with tempfile.TemporaryDirectory(prefix='native-frame-math-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'math.exe'
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                '-I',str(headers),str(STAGE/'test_native_numeric_math_ordered.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            math[label]=json.loads(subprocess.check_output([str(exe)],text=True))
            (WORK/f'numeric_original_{label}_cases.json').write_text(json.dumps(math[label],indent=2)+'\n',encoding='utf8')
    assert math['baseline']['case_hashes']==math['candidate']['case_hashes']
    assert math['candidate']['cases']==5903 and math['candidate']['skipped_undefined_divisions']==1
    result={'passed':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'preflight_actual_baseline_dll_sha256':preflight['baseline_dll_sha256'],
        'original_item_physics_and_helper_match_preflight':True,'tests':reports,
        'two_ordered_nan_operations_verified_non_lto':True,
        'numeric_original_cross_dll_cases':5903,'floating_exception_flags_and_result_bits_unchanged':True}
    (WORK/'frame_segment_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))


if __name__=='__main__':main()

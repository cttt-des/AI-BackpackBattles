"""Retained index/frame semantics and the actual DLL's address-only hint entry."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_active_prefetch import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists()
    from verify_native_active_cooldown_final import verify as retained_index
    index=retained_index(source,dll,out.parent/'retained_active_index.json')
    # Its frozen independent oracle and every original case remain intact. The
    # index fixture instantiates the corresponding header against the real DLL;
    # actual production integration is additionally checked by fixed200/full2604.
    assert index['passed'] and index['cases']==1856
    root=Path(tempfile.mkdtemp(prefix='active-prefetch-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    shutil.copyfile(dll,root/'libgdcore.dll');fixture=STAGE/'test_native_active_prefetch_addresses.cpp';exe=root/'addresses.exe'
    with (out.parent/'address_check.log').open('w',encoding='utf8') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,text=True,env=env);log.write(run.stdout+run.stderr);log.flush();run.check_returncode()
    addresses=json.loads(run.stdout);assert addresses['passed'] and addresses['cases']==4096
    disassembly=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--disassemble=gd_test_native_active_prefetch',str(root/'libgdcore.dll')]).decode('utf8',errors='replace')
    (out.parent/'actual_address_entry_disassembly.txt').write_text(disassembly,encoding='utf8')
    assert 'prefetch' in disassembly.lower() and ('prefetcht0' in disassembly.lower() or 'prefetchnta' in disassembly.lower())
    # Existing actual frame helper proof, using the candidate's original frame
    # body and new DLL. A hint never substitutes for one of those reads/ops.
    exe=root/'frame.exe'
    with (out.parent/'retained_frame.log').open('w',encoding='utf8') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-I',str(source),str(STAGE/'test_native_frame_segments.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],
            stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        run=subprocess.run([str(exe)],capture_output=True,text=True,env=env);log.write(run.stdout+run.stderr);log.flush();run.check_returncode()
    frame=json.loads(run.stdout);assert frame['passed'] and frame['cases']==6912
    result=dict(passed=True,cases=1856+4096+6912,retained_header_and_linked_dll_index_cases=1856,
        actual_dll_address_cases=4096,retained_frame_cases=6912,baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
        fixture_sha256=sha(fixture),retained_index_receipt_sha256=sha(out.parent/'retained_active_index.json'),
        prefetch_instructions_present_in_actual_dll=True,address_entry_disassembly_sha256=sha(out.parent/'actual_address_entry_disassembly.txt'),
        index_fixture_scope_explicit=True,actual_production_integration_requires_fixed200_and2604=True,
        no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    return result

def main():
    p=psutil.Process();(WORK/'live_semantic_verification.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),script=str(Path(__file__).resolve())))+'\n',encoding='utf8')
    r=json.loads((WORK/'live_semantic_build.json').read_bytes())
    try:
        other=psutil.Process(r['pid'])
        if other.create_time()==r['created']:other.wait()
    except psutil.NoSuchProcess:pass
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')

if __name__=='__main__':main()

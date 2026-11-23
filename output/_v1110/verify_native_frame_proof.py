"""Compare actual DLL ticks/scopes/phases with the accepted DLL and original loop."""
import hashlib
import argparse
import json
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import psutil
from prepare_native_frame_proof import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists();work=out.parent
    old_dll=ACCEPTED/'bundle.dll';old_source=ACCEPTED/'bundle_src'
    assert sha(old_dll)==EXPECTED
    profile=json.loads((ACCEPTED/'profile_depth64.json').read_bytes())
    assert profile['dll_sha256']==EXPECTED
    name='gd::native_frame_segment_tick(Gd__gd_core__CoreItem*, gd::NativeFrameSegmentSnapshot&, gd::GdVal const&)'
    offsets={r['offset']-r['offset_in_function'] for r in profile['instruction_locations'] if r['function']==name}
    assert len(offsets)==1;offset=offsets.pop()
    # Resolve the old tick inside the SHA-pinned DLL, rather than accidentally
    # compiling the inline baseline body into the test executable.
    header=old_dll.read_bytes()[:512];pe=struct.unpack_from('<I',header,60)[0]
    base=struct.unpack_from('<Q',header,pe+24+24)[0]
    with tempfile.TemporaryDirectory(prefix='native-display-old-symbols-') as directory:
        copied=Path(directory)/'baseline.dll';shutil.copyfile(old_dll,copied)
        listing=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','-C','--defined-only',str(copied)],text=True)
    assert any(int(line.split()[0],16)==base+offset and line.endswith(' '+name) for line in listing.splitlines() if line.split())
    fixture=STAGE/'test_native_frame_proof.cpp'
    original_loop=STAGE/'native_perf50/active_cooldown_prototype/test_src/cooldown_original_phase.hpp'
    records={}
    for label,headers,library in [('baseline',old_source,old_dll),('candidate',source,dll)]:
        with tempfile.TemporaryDirectory(prefix='native-default-display-tests-') as directory:
            root=Path(directory);shutil.copyfile(library,root/'libgdcore.dll');exe=root/'display.exe'
            flags=['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                '-I',str(headers),'-I',str(original_loop.parent),f'-DGD_OLD_FRAME_RVA={offset}']
            if label=='candidate':flags.append('-DGD_DISPLAY_NEW')
            compile_log=work/(label+'_display_compile_first.log');attempt=2
            while compile_log.exists():
                compile_log=work/(label+f'_display_compile_attempt{attempt}.log');attempt+=1
            with compile_log.open('wb') as log:
                subprocess.run([*flags,str(fixture),str(root/'libgdcore.dll'),'-o',str(exe)],check=True,stdout=log,stderr=subprocess.STDOUT)
            for mode,args in [('matrix',[]),('registry',['--registry'])]:
                run=subprocess.run([str(exe),*args],capture_output=True,text=True)
                log=work/(label+'_display_'+mode+'_first.log');assert not log.exists()
                log.write_text(run.stdout+run.stderr,encoding='utf8')
                if run.returncode:print(run.stdout+run.stderr,flush=True)
                run.check_returncode();actual=json.loads(run.stdout)
                path=work/(label+'_display_'+mode+'_cases.json');assert not path.exists()
                path.write_text(run.stdout,encoding='utf8');records[label,mode]=actual
    differences=[]
    for mode,count in [('matrix',3072),('registry',1)]:
        old,new=records['baseline',mode],records['candidate',mode]
        assert old['cases']==new['cases']==count and len(old['hashes'])==len(new['hashes'])==count
        assert old['layout']==new['layout']==dict(GdVal=24,GdArr=32,CoreItem=1792,BattleCtx=328,snapshot=32)
        differences.extend(dict(mode=mode,index=i) for i,(a,b) in enumerate(zip(old['hashes'],new['hashes'])) if a!=b)
    counts=records['candidate','matrix']['counts']
    report=dict(passed=not differences,cases=3073,matrix_cases=3072,registry_cases=1,
        difference_count=len(differences),first_differences=differences[:30],
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),actual_independent_dll_ticks_and_candidate_phase=True,
        baseline_tick_rva=offset,baseline_tick_symbol_checked_against_sha_pinned_profile_and_nm=True,
        original_traversal_fixture_sha256=sha(original_loop),fixture_sha256=sha(fixture),
        rounding_modes=4,daz_ftz_modes=4,original_frame_and_type_counter_deltas_in_hash=True,unused_counts=counts,registry_counts=records['candidate','registry']['counts'],
        canonical_fields_arrays_aliases_callback_order_rng_ids_original_counters_fenv_mxcsr_checked=True,
        gem_getter_context_and_override_mutations_checked=True,cleared_mismatched_rows_and_dispatch_flags_checked=True,
        raw_cases_directory=str(work),raw_cases_sha256={p.name:sha(p) for p in work.glob('*_display_*_cases.json')},
        layouts=records['candidate','matrix']['layout'],no_throughput_claim=True)
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2));assert report['passed'],differences[:30]
    return report

if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('--out',type=Path,default=WORK/'correctness.json');args=parser.parse_args()
    args.out.parent.mkdir(parents=True,exist_ok=True)
    verify(WORK/'prototype_src',WORK/'prototype.dll',args.out)

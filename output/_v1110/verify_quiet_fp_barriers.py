"""Compare the actual dependency barriers with literal SSE reference operations."""
import json,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_quiet_round import WORK,STAGE,sha,save
@isolated_build
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    text=(STAGE/'quiet_core_kernel.cpp').read_text('utf8').split('// BEGIN_QUIET_FP_BARRIERS\n',1)[1].split('// END_QUIET_FP_BARRIERS',1)[0]
    fixture=(STAGE/'test_quiet_fp_barriers.cpp').read_text('utf8').replace('// ACTUAL_BARRIERS',text)
    output=WORK/'fp_dependency_barrier_checks';assert not output.exists();output.mkdir();source=output/'actual_barriers.cpp';source.write_text(fixture,encoding='utf8',newline='\n')
    root=Path(tempfile.mkdtemp(prefix='quiet-fp-barriers-'));exe=root/'check.exe'
    with (output/'compile.log').open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-flto=2','-std=c++20','-ffp-contract=off',str(source),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,check=True)
    run=subprocess.run([str(exe)],capture_output=True);(output/'actual.json').write_bytes(run.stdout);(output/'stderr.log').write_bytes(run.stderr);run.check_returncode();r=json.loads(run.stdout)
    assert r['passed'] and r['cases']==16*13**3
    save('fp_dependency_barrier_tests.json',dict(**r,actual_fragment_sha256=sha(STAGE/'quiet_core_kernel.cpp'),fixture_sha256=sha(source),literal_SSE_reference=True,all16_rounding_DAZ_FTZ_modes=True,positive_negative_zero_subnormal_overflow_and_cancellation=True,compiler_flags=['-O3','-flto=2','-std=c++20','-ffp-contract=off']))
    print(json.dumps(r),flush=True)
if __name__=='__main__':main()

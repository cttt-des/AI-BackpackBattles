"""Expose or verify the live custom-container fractional-size regression."""
import argparse,json,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_timeline_round import STAGE,WORK,ACCEPTED,sha,save
@isolated_build
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--dll',type=Path,required=True);parser.add_argument('--tag',required=True);parser.add_argument('--expect-mismatch',action='store_true');a=parser.parse_args();root=Path(tempfile.mkdtemp(prefix='timeline-container-'));shutil.copyfile(a.dll,root/'libgdcore.dll');psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    text=(ACCEPTED/'bundle_src/gen/shards/shard_07.cpp').read_text('utf8');start=text.index('gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(');method=text[start:text.index('\n}',start)+2].replace('gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(', 'gd::GdVal local_delay(Context* self,').replace('this->','self->');(root/'local_delay.hpp').write_text(method+'\n',encoding='utf8')
    source=STAGE/'test_delay_container_regression.cpp'
    with (WORK/(a.tag+'_container_compile.log')).open('xb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-O3','-std=c++20','-march=native','-ffp-contract=off','-static','-I',str(root),'-I',str(WORK/'bundle_src'),str(source),str(root/'libgdcore.dll'),'-o',str(root/'probe.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
    out=subprocess.check_output([str(root/'probe.exe')]);raw=WORK/(a.tag+'_container_raw.json');raw.write_bytes(out);r=json.loads(out);assert (r['mismatches']>0) if a.expect_mismatch else r['passed']
    save(a.tag+'_container_receipt.json',dict(passed=not a.expect_mismatch,regression_confirmed=a.expect_mismatch,dll_sha256=sha(a.dll),source_sha256=sha(source),raw_sha256=sha(raw),semantic_cases=6,mismatches=r['mismatches']));print(out.decode(),flush=True)
if __name__=='__main__':main()

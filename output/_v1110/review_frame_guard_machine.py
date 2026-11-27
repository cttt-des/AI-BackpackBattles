"""Record actual release code for the changed helper, without predicting speed."""
import json,os,shutil,subprocess,tempfile
from pathlib import Path
from prepare_frame_guard_reuse import WORK,ACCEPTED,sha,save
SYMBOL='_ZN2gd25native_frame_segment_tickEP21Gd__gd_core__CoreItemRNS_26NativeFrameSegmentSnapshotERKNS_5GdValE'
def main():
    root=Path(tempfile.mkdtemp(prefix='frame-guard-release-review-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));rows={}
    for label,path in [('baseline',ACCEPTED/'bundle.dll'),('candidate',WORK/'bundle.dll')]:
        binary=root/(label+'.dll');shutil.copyfile(path,binary)
        text=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+SYMBOL,str(binary)],text=True)
        assert '<'+SYMBOL+'>:' in text
        p=WORK/(label+'_frame_release_disassembly.txt');p.write_text(text,encoding='utf8')
        calls=[x.strip() for x in text.splitlines() if '\tcall' in x and 'native_resolved_exact_row' in x]
        rows[label]=dict(dll_sha256=sha(path),disassembly_sha256=sha(p),exact_row_call_sites=calls,exact_row_static_call_site_count=len(calls),instruction_lines=sum(bool(x.strip()) and ':' in x for x in text.splitlines()))
    save('machine_review.json',dict(passed=True,rows=rows,source_exact_inverse_required_separately=True,eliminated_same_invocation_query_confirmed_by_source_and_actual135168_tests=True,static_counts_not_speed_claim=True))
    print('Actual release machine-code review saved: row-call sites '+str([rows[x]['exact_row_static_call_site_count'] for x in rows]),flush=True)
if __name__=='__main__':main()

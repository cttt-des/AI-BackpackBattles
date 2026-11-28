"""Preserve rejected r1 and repair its demonstrated generic-tail regression."""
import json,shutil
from prepare_timeline_round import WORK,once,TAIL_OLD,TAIL_NEW,inventory,save,verify_projection
def main():
    verify_projection(WORK/'bundle_src');archive=WORK/'rejected_r1';assert not archive.exists();archive.mkdir()
    for name in ['native_typed_timeline.hpp','gen/shards/shard_07.cpp']:
        shutil.copyfile(WORK/'bundle_src'/name,archive/(name.rsplit('/',1)[-1]+'.r1'))
    for path in list(WORK.iterdir()):
        if path.is_file() and (path.name.startswith(('prototype','normal_build','formal_build','formal_interruption')) or path.name in ['live_formal_build.json','persistent_build_directory.json','bundle_objects.txt','instrumented_export_policy.json','source_before_build.json','source_changes.json']):shutil.move(path,archive/path.name)
    header=WORK/'bundle_src/native_typed_timeline.hpp';text=header.read_text('utf8');text=once(text,TAIL_OLD,TAIL_NEW);text=once(text,'#include <bit>','#include <bit>\n#include <xmmintrin.h>');text=once(text,'b.native_resolved_collect || entry.kind','b.native_resolved_collect || (_mm_getcsr()&~63u)!=0x1f80u || entry.kind');header.write_text(text,encoding='utf8',newline='\n')
    changes=json.loads((archive/'source_changes.json').read_bytes());file=WORK/'bundle_src/gen/shards/shard_07.cpp';text=file.read_text('utf8')
    old='!rt_ctx_->native_resolved_collect && f__timed.kind';new='!rt_ctx_->native_resolved_collect && (_mm_getcsr()&~63u)==0x1f80u && f__timed.kind'
    text=once(text,old,new);file.write_text(text,encoding='utf8',newline='\n')
    for pair in changes:
        if old in pair[1]:pair[1]=once(pair[1],old,new)
    save('source_changes.json',changes);save('source_before_build.json',inventory(WORK/'bundle_src'));save('source_projection.json',verify_projection(WORK/'bundle_src'))
    save('revision_r2.json',dict(reason='r1 failed4/6 actual-DLL fractional custom-container tail cases; retain literal GdVal end/read/write tail',r1_regression_receipt='rejected_r1_container_receipt.json',FP_support='New typed paths restricted to default nearest/all-masked/noDAZ/noFTZ; other controls retain original full methods',no_candidate_speed_observations_or_AB_before_revision=True))
    print('Preserved r1 failure and repaired r2 source; full normal rebuild required',flush=True)
if __name__=='__main__':main()

"""Adapt retained actual-DLL checks and build only affected semantic consumers."""
import ast
from prepare_native_frame_proof import STAGE,once

def main():
    t=(STAGE/'build_native_frame_proof_prototype.py').read_text('utf8')
    t=t.replace('prepare_native_frame_proof','prepare_native_coallocated_events').replace(',EXPECTED,ARCHIVE,sha',',EXPECTED,sha')
    t=once(t,"==['engine_wrapper.cpp','native_inline_dispatch.hpp']","==['engine_wrapper.cpp','gen/shards/shard_11.cpp','native_inline_dispatch.hpp']")
    t=once(t,"'shard_03':src/'gen/shards/shard_03.cpp'","'shard_03':src/'gen/shards/shard_03.cpp','shard_11':src/'gen/shards/shard_11.cpp'")
    t=t.replace('reused_objects=17,recompiled_units=3','reused_objects=16,recompiled_units=4')
    t=t.replace('verified_remote_backup=ARCHIVE',"verified_remote_backup=json.loads((WORK/'transform.json').read_bytes())['verified_remote_backup']")
    t=t.replace('native-frame-proof-','native-coallocated-events-')
    ast.parse(t);(STAGE/'build_native_coallocated_events.py').write_text(t,encoding='utf8')
    for old,new in [('verify_native_frame_proof.py','verify_coallocated_frame.py'),('verify_native_event_capacity.py','verify_coallocated_params.py')]:
        t=(STAGE/old).read_text('utf8')
        t=t.replace('prepare_native_frame_proof','prepare_native_coallocated_events').replace('prepare_native_event_capacity','prepare_native_coallocated_events')
        if 'frame' in new:t=t.replace("default=WORK/'correctness.json'","default=WORK/'frame_correctness.json'")
        else:t=t.replace("WORK/'correctness.json'","WORK/'params_correctness.json'")
        ast.parse(t);(STAGE/new).write_text(t,encoding='utf8')
    print('Prepared16 reused/4 recompiled semantic objects and actual-DLL3073+1024 checks')

if __name__=='__main__':main()

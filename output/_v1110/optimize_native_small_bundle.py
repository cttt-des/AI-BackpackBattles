"""Apply the arena/dictionary/label bundle to the verified event-kernel baseline."""
import argparse
import hashlib
from pathlib import Path
import re
import optimize_native_arena_split as arena
import optimize_native_dict_indices as dictionary
import optimize_native_label_ranges as labels
from optimize_native_integer_ranges import blocks
from optimize_native_serial_paths import method_body

HEADER_SHA='01c0ea5c56e25e96a06da6e2b8c65d370cc7ea52b012d0f91878401e7cf22a3c'

def optimize(native):
    path=native/'gd_rt.hpp';source=path.read_text('utf8')
    assert hashlib.sha256(arena.normalize(source).encode()).hexdigest()==HEADER_SHA,'Unexpected baseline arena header'
    output=arena.transform(source)
    if output!=source:path.write_text(output,encoding='utf8',newline='\n')
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    match=re.search(r'^GdVal GdDict::get\([^\n]*\n.*?^}\n',runtime,re.M|re.S)
    assert match
    body=match[0];original=body.replace(dictionary.FAST,'',1)
    assert hashlib.sha256(original.encode()).hexdigest()==dictionary.ORIGINAL_HASH
    if dictionary.FAST not in body:dictionary.optimize(native)
    # Check iterator semantics even when the label transform is already present.
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    begin=runtime.index('GdVal gd_iter_seq(');end=runtime.index('// ─',begin)
    assert hashlib.sha256(runtime[begin:end].encode()).hexdigest()==labels.ITERATOR_HASH
    body=method_body((native/'gen/shards/shard_00.cpp').read_text('utf8'),'CoreItem','getNextFreeLabelPosition')[0]
    old,new=blocks((190,191,192,8),labels.EXPRESSION)
    original=body.replace(new,old,1)
    assert original.count(old)==1 and hashlib.sha256(original.encode()).hexdigest()==labels.METHOD_HASH
    if new not in body:labels.optimize(native)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native',type=Path)
    optimize(parser.parse_args().native)

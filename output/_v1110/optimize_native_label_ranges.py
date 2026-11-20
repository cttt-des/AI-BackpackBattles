"""Avoid temporary integer index arrays for item label placement."""
import argparse
import hashlib
from pathlib import Path
from optimize_native_integer_ranges import ITERATOR_HASH, blocks
from optimize_native_serial_paths import method_body

METHOD_HASH="5daddc848f077230b535e0acd1c5491694c8a4c7fd95c98a909fbfef6374aeb2"
EXPRESSION="gd::call_method(gd_ctx, this->f_buffLabelPositionTimestamps, gd::SYM_size, nullptr, 0)"

def optimize(native):
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    begin=runtime.index('GdVal gd_iter_seq(');end=runtime.index('// ─',begin)
    if hashlib.sha256(runtime[begin:end].encode()).hexdigest()!=ITERATOR_HASH:
        raise ValueError('The integer iterator semantics changed')
    path=native/'gen/shards/shard_00.cpp';source=path.read_text('utf8')
    method=method_body(source,'CoreItem','getNextFreeLabelPosition')
    old,new=blocks((190,191,192,8),EXPRESSION)
    body=method[0]
    original=body.replace(new,old,1) if new in body else body
    if hashlib.sha256(original.encode()).hexdigest()!=METHOD_HASH or original.count(old)!=1:
        raise ValueError('The item label position implementation changed')
    body=original.replace(old,new,1)
    path.write_text(source[:method.start()]+body+source[method.end():],encoding='utf8',newline='\n')
    print('Removed label-placement integer index array; retained captured size and dynamic fallback',flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('native',type=Path)
    optimize(parser.parse_args().native)

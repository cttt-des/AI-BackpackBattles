"""Read an integer-key dictionary entry directly only when its stored key matches."""
import argparse
import hashlib
from pathlib import Path
import re

ORIGINAL_HASH="e19037879e38149c0998c99fe50961b2dd37f1ecfc84a8f07c26b1c3f3128694"
FAST='''    // A matching stored integer key proves the entry without a bucket lookup.
    // The unsigned bound also sends negative and large integers to the original path.
    if (key.kind == GdVal::Kind::Int && static_cast<uint64_t>(key.i) < len) {
        const auto& entry=entries[static_cast<uint32_t>(key.i)];
        if (entry.key.kind == GdVal::Kind::Int && entry.key.i == key.i) return entry.val;
    }
'''

def optimize(native):
    path=native/'gd_rt.cpp'
    source=path.read_text('utf8')
    method=re.search(r'^GdVal GdDict::get\([^\n]*\n.*?^}\n',source,re.M|re.S)
    if not method:raise ValueError('Missing dictionary getter')
    body=method[0]
    original=body.replace(FAST,'',1) if FAST in body else body
    if hashlib.sha256(original.encode()).hexdigest()!=ORIGINAL_HASH:
        raise ValueError('The dictionary getter changed')
    if FAST not in body:
        body=body.replace('    int32_t idx = find_index(key);',FAST+'    int32_t idx = find_index(key);',1)
    source=source[:method.start()]+body+source[method.end():]
    path.write_text(source,encoding='utf8',newline='\n')
    print('Added exact stored-integer entry shortcut to dictionary reads',flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native',type=Path)
    optimize(parser.parse_args().native)

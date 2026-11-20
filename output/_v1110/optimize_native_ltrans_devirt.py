"""Enable one LTO option and make script/config edits invalidate cached objects."""
import argparse
import hashlib
from pathlib import Path

BASE='8d8177098d009a429c41b78278497d8c645dab0e939b58fa1fd4e3ff97bcee80'
ANCHOR='    hdr_deps = [\n'
DEPENDENCY='        ROOT / "build_windows.py",\n'
OLD='COMMON = ["-O3", "-std=c++20"'
NEW='COMMON = ["-O3", "-fdevirtualize-at-ltrans", "-std=c++20"'

def digest(s):return hashlib.sha256(s.encode()).hexdigest()

def with_self_dependency(source):
    assert source.count(ANCHOR)==1 and source.count(DEPENDENCY)<=1
    if DEPENDENCY in source:return source
    return source.replace(ANCHOR,ANCHOR+DEPENDENCY,1)

def optimize(native,*,self_dependency_only=False):
    path=native/'build_windows.py';original=path.read_text('utf8')
    base=original.replace(DEPENDENCY,'',1).replace(NEW,OLD,1)
    if digest(base)!=BASE:raise ValueError('The verified Windows build configuration changed')
    output=with_self_dependency(base)
    if not self_dependency_only:
        assert output.count(OLD)==1;output=output.replace(OLD,NEW,1)
    if path.read_bytes()!=output.encode():path.write_text(output,encoding='utf8',newline='\n')
    print('Build script invalidates cached units; '+('compiler flags unchanged' if self_dependency_only else 'LTO local devirtualization enabled, FP flags retained'),flush=True)

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);p.add_argument('--self-dependency-only',action='store_true')
    a=p.parse_args();optimize(a.native,self_dependency_only=a.self_dependency_only)

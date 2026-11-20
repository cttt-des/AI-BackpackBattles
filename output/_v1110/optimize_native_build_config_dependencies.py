"""Invalidate native objects when the build script's compiler settings change."""
import argparse
import hashlib
from pathlib import Path

BASE='8d8177098d009a429c41b78278497d8c645dab0e939b58fa1fd4e3ff97bcee80'
ANCHOR='    hdr_deps = [\n'
DEPENDENCY='        ROOT / "build_windows.py",\n'

def with_self_dependency(source):
    assert source.count(ANCHOR)==1 and source.count(DEPENDENCY)<=1
    if DEPENDENCY in source:return source
    return source.replace(ANCHOR,ANCHOR+DEPENDENCY,1)

def optimize(native):
    path=native/'build_windows.py';source=path.read_text('utf8')
    restored=source.replace(DEPENDENCY,'',1)
    if hashlib.sha256(restored.encode()).hexdigest()!=BASE:
        raise ValueError('The verified build script changed; review the dependency patch')
    output=with_self_dependency(restored)
    if path.read_bytes()!=output.encode():path.write_text(output,encoding='utf8',newline='\n')
    print('Build-script setting edits invalidate cached objects; compiler flags retained',flush=True)

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)

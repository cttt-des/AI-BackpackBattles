"""Track every native root header when reusing Windows build objects."""
import argparse
import hashlib
from pathlib import Path

OLD='        ROOT / "gd_rt.hpp",\n        ROOT / "builtin_syms.hpp",\n'
NEW='        *sorted(ROOT.glob("*.hpp")),\n'
BASELINE='41a742193cdb357c83316a3e534c68c5d173646b42f853fe1c66b5d13df37e1a'


def optimize(native):
    path=native/'build_windows.py';source=path.read_text('utf8')
    restored=source.replace(NEW,OLD,1)
    if hashlib.sha256(restored.encode('utf8')).hexdigest()!=BASELINE:
        raise ValueError('The verified Windows build script changed')
    assert restored.count(OLD)==1
    output=restored.replace(OLD,NEW,1)
    if source!=output:path.write_text(output,encoding='utf8',newline='\n')
    print('Tracked all root headers, including native scan helpers',flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)

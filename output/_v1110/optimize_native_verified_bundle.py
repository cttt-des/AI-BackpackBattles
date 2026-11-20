"""Replay the reviewed source transform only for its exact supported baseline.

The existing generator rewrites generated classes, while runtime support files
survive regeneration. Prepare restores only the three reviewed runtime inputs;
apply installs the accepted source image after the preceding performance passes.
Both phases reject unknown edits before writing anything.
"""
import argparse
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/bundle_arena_dict_labels'

def digest(data):return hashlib.sha256(data).hexdigest()
def canonical(data):return data.decode('utf8').replace('\r\n','\n').encode('utf8')

def optimize(native,prepare=False):
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    changes=[]
    # Validate every supported region before the first write; a manual edit or
    # upstream change must never be overwritten by an older accepted snapshot.
    for row in manifest['files']:
        path=native/row['path']
        current=path.read_bytes() if path.exists() else None
        actual=digest(canonical(current)) if current is not None else None
        if actual not in (row['before_canonical_sha256'],row['after_canonical_sha256']):
            raise ValueError(f'Unsupported source change: {path}; preserve it and regenerate/revalidate the performance pass')
        if prepare:
            if not row['runtime']:continue
            data=(WORK/'before_runtime'/row['path']).read_bytes()
            assert digest(canonical(data))==row['before_canonical_sha256']
        else:
            data=(WORK/'bundle_src'/row['path']).read_bytes()
            assert digest(canonical(data))==row['after_canonical_sha256']
        if current!=data:changes.append((path,data))
    for path,data in changes:
        path.parent.mkdir(parents=True,exist_ok=True)
        path.write_bytes(data)
    print(f'Verified source bundle {"prepare" if prepare else "apply"}: {len(changes)} files updated',flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native',type=Path)
    parser.add_argument('--prepare',action='store_true')
    args=parser.parse_args()
    optimize(args.native,args.prepare)

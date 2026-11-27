"""Version-locked accepted source transform, with complete source-inventory guards."""
import argparse
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
if not (STAGE/'sim_native').is_dir():STAGE=STAGE.parents[1]
WORK=STAGE/'native_perf50/rng_scaling_bundle'

def digest(data):return hashlib.sha256(data).hexdigest()
def canonical(data):return data.decode('utf8').replace('\r\n','\n').encode('utf8')

def optimize(native,prepare=False):
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    inventory={r['path']:r for r in manifest['inventory']}
    actual={p.relative_to(native).as_posix() for p in native.rglob('*') if p.is_file()
            and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')}
    if actual-set(inventory):raise ValueError(f'Unexpected source files: {sorted(actual-set(inventory))}')
    current={}
    # Validate all generated classes as well as changed files. Otherwise an
    # override added in an untouched shard could invalidate a cached method row.
    for name,row in inventory.items():
        path=native/name
        data=path.read_bytes() if path.exists() else None
        current[name]=data
        value=digest(canonical(data)) if data is not None else None
        allowed=[row['before_canonical_sha256'],row['after_canonical_sha256'],*row.get('intermediate_canonical_sha256',[])]
        if value not in allowed:raise ValueError(f'Unsupported source change: {path}; retain the edit and revalidate the performance transform')
    changes=[]
    for row in manifest['files']:
        name=row['path']
        if prepare:
            if not row['runtime']:continue
            data=(WORK/'before_runtime'/name).read_bytes()
            assert digest(canonical(data))==row['before_canonical_sha256']
        else:
            data=(WORK/'bundle_src'/name).read_bytes()
            assert digest(canonical(data))==row['after_canonical_sha256']
        if current[name]!=data:changes.append((native/name,data))
    for path,data in changes:
        path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    print(f'Verified full-inventory source {"prepare" if prepare else "apply"}: {len(changes)} files updated',flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native',type=Path);parser.add_argument('--prepare',action='store_true')
    args=parser.parse_args();optimize(args.native,args.prepare)

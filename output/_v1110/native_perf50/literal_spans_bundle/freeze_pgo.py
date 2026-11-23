"""Preserve the original18 hot profiles before the formal timing phase."""
import hashlib
import json
from pathlib import Path
import shutil

WORK=Path(__file__).resolve().parent

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    assert not (WORK/'comparison.log').exists(),'Do not do local work during formal timings'
    profile=json.loads((WORK/'fresh_profile_source.json').read_bytes())
    assert profile['dll_sha256']==sha(WORK/'bundle.dll')
    assert profile['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    assert profile['profile_training_and_release_source_identical']
    counts=profile['hot_profiles_sha256'];assert len(counts)==18
    original=Path((WORK/'bundle_objects.txt').read_text('utf8'))/'pgo'
    frozen=WORK/'frozen_pgo_counts';frozen.mkdir(exist_ok=True)
    for name,digest in counts.items():
        source=original/(name+'.gcda');assert sha(source)==digest
        target=frozen/source.name
        if target.exists():assert sha(target)==digest
        else:shutil.copyfile(source,target)
        assert sha(target)==digest
    out=WORK/'frozen_pgo_manifest.json'
    record=dict(dll_sha256=profile['dll_sha256'],source_manifest_sha256=profile['source_manifest_sha256'],counts=counts)
    if out.exists():assert json.loads(out.read_bytes())==record
    else:out.write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
    print('Preserved all18 original PGO profiles; all hashes match the formal build receipt')

if __name__=='__main__':main()

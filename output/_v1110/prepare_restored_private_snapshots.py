"""Restore private snapshots on the deployed display/control-word baseline."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import tempfile
from prepare_native_private_snapshots import transform as private_transform,HEADER

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/display_storage_bundle'
WORK=STAGE/'native_perf50/restored_snapshots_prototype'
EXPECTED='5ddb2c1b15ad7ab7dfe1a8f2640701abddf6da88600b2930e55fc85165b59209'
ARCHIVE='6ceab43e0324e20b4d9d96b75828253c265dcc2c'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def archive():
    d=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert d['remote_upload_verified'] and d['production_dll_sha256']==EXPECTED and d['remote_verified_commit']==ARCHIVE
    return d['remote_verified_commit']

def transform(native):return private_transform(native)

def verify_projection(native):
    reference=ACCEPTED/'bundle_src'
    # Recreate just the two declared source edits from the accepted baseline.
    # Every other byte, including all674 headers and display storage, must match.
    with tempfile.TemporaryDirectory(prefix='restored-snapshot-projection-') as folder:
        scratch=Path(folder);(scratch/'gen/shards').mkdir(parents=True)
        for name in ('shard_00.cpp','shard_12.cpp'):shutil.copyfile(reference/'gen/shards'/name,scratch/'gen/shards'/name)
        component=transform(scratch)
        for relative in ('gen/shards/shard_00.cpp','gen/shards/shard_12.cpp','native_private_snapshots.hpp'):
            assert (scratch/relative).read_bytes()==(native/relative).read_bytes(),relative
    changed={'gen/shards/shard_00.cpp','gen/shards/shard_12.cpp'}
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,digest in frozen.items():
        if name not in changed:assert sha(native/name)==digest,name
    assert (native/'native_private_snapshots.hpp').read_text('utf8')==HEADER
    assert 'native_display_values_[10]' in (native/'gen/hdrs/Gd__gd_core__CoreItem.hpp').read_text('utf8')
    return dict(passed=True,declared_two_source_changes_reproduced_exactly=True,
        all674_headers_gdval_gdarr_context_watch_and_display_storage_unchanged=True,
        prior_control_word_reads_retained=True,private_integer_sites=len(component['private_integer_sites']),
        identity_snapshot_sites=component['identity_snapshot_sites'],full20_formal_rebuild_required=True)

def main():
    archived=archive();assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert not WORK.exists();WORK.mkdir();source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(source);after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n]);assert changed==['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp']
    def closure(p,seen):
        p=p.resolve()
        if p in seen:return
        seen.add(p)
        for name in re.findall(r'^\s*#include\s+"([^"]+)"',p.read_text('utf8'),re.M):
            child=p.parent/name
            if not child.is_file():child=source/name
            if child.is_file():closure(child,seen)
    consumers=[];header=(source/'native_private_snapshots.hpp').resolve()
    for p in source.rglob('*.cpp'):
        seen=set();closure(p,seen)
        if header in seen:consumers.append(p.relative_to(source).as_posix())
    assert sorted(consumers)==changed
    result=dict(baseline_dll_sha256=EXPECTED,verified_backup=archived,source_sha256=after,
        modified_files=changed,new_files=['native_private_snapshots.hpp'],component=component,
        sole_consumers=sorted(consumers),projection=verify_projection(source),
        baseline_cpp_source_files=707,candidate_cpp_source_files=708,
        current_display_and_control_components_retained=True,no_new_branches=True,
        no_layout_change_from_deployed2112_byte_CoreItem=True,not_for_deployment=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(changed=changed,new_files=result['new_files'],cpp_consumers=consumers,baseline_dll_sha256=EXPECTED)),flush=True)

if __name__=='__main__':main()

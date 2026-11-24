"""A distinct compiler configuration using the unchanged verified F950 source."""
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/compiler_pta_bundle'
ACCEPTED=STAGE/'native_perf50/object_routes_bundle'
BACKUP=STAGE/'native_perf50/private_snapshots_bundle'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
ARCHIVE='80c06b2db6f525ae5b0b4acd2f2130f1bd418310'
FLAGS=('-fipa-pta',)

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def optimize(native):
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    receipt=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    assert receipt['production_dll_sha256']==EXPECTED and not receipt['candidate_installed']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.pop('semantic_receipt_sha256',None)
    result.update(baseline_dll_sha256=EXPECTED,components=['interprocedural pointer analysis: -fipa-pta'],
        source_sha256=before,modified_files=[],new_files=[],compiler_optimization_flags=list(FLAGS),
        compiler_configuration_only=True,actual_candidate_validation_pending=True,
        private_snapshots_trial_not_included=True,object_layout_changes=False,
        battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,no_speed_claim=True)
    return result

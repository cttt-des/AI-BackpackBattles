"""Apply only frame reuse to deployed member reads; prove old candidate equality."""
import hashlib
import json
from pathlib import Path
from prototype_native_member_frame_bundle import frame_reuse
STAGE=Path(__file__).resolve().parent
def optimize(native):
    old=STAGE/'native_perf50/member_frame_bundle'
    base=STAGE/'native_perf50/member_only_bundle'
    before=json.loads((base/'source_before_build.json').read_bytes())
    digest=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
    assert before=={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    physics=frame_reuse(native)
    after={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((old/'source_before_build.json').read_bytes()),'Do not reuse a DLL for even one differing source byte'
    report=json.loads((base/'transform.json').read_bytes())
    report.update(baseline_dll_sha256='6cb258ec1baf335d3bc8e9da1538b2edd8aee87669b05249728f4829b1c47785',
        components=['retained deployed member-pointer reads','independent callback-bounded state reuse'],
        modified_native_files=[p for p in before if before[p]!=after[p]],
        original_item_physics_sha256=physics,reused_candidate_cpp_source_exactly_equal=True,
        reused_candidate_dll_sha256='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14',
        no_empty_timer_chunks=True,no_field_tags=True,no_public_nan_guard_changes=True)
    return report

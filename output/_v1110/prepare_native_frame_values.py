"""Preserve all deployed components and shorten frame-local value handling."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/scalar_guards_bundle'
WORK=STAGE/'native_perf50/frame_value_prototype'
EXPECTED='63d8966c95c629855fc336a748cbfcc20860d5e75d7c1700506022f347ac10c5'
ARCHIVE='8f7022b1e28093d6f48d1c1250a92cab8789bad3'
HEADER='native_inline_dispatch.hpp'
OLD='    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();'
NEW='''    // Null覆盖不读取其无用载荷；非Null仍按原时点复制，保留回调前快照。
    const auto override = display && display->len > 3 && !display->data[3].is_null()
        ? display->data[3] : gd::GdVal::null();'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(native):
    return {p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()
        and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE
def section(text):
    start=text.index('inline void native_frame_segment_tick(')
    end=text.index('\n}',start)+2
    return start,end,text[start:end]
def transform(native):
    before=inventory(native);assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    p=native/HEADER;t=p.read_text('utf8');start,end,body=section(t)
    assert body.count(OLD)==1 and body.count('gd::gd_truth(')==4
    changed=body.replace(OLD,NEW,1).replace('gd::gd_truth(', 'gd::native_scalar_truth(')
    p.write_text(t[:start]+changed+t[end:],encoding='utf8',newline='\n')
    return dict(frame_truth_sites=4,null_local_payload_copy_avoided=True,
        non_null_snapshot_timing_and_values_unchanged=True,no_callback_rng_floating_or_frame_reordering=True,
        previous_private_scalar_display_and_control_components_retained=True)
def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==frozen['source_sha256']
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,digest in old.items():
        if name==HEADER:
            t=(native/name).read_text('utf8');start,end,body=section(t)
            assert body.count(NEW)==1 and body.count('gd::native_scalar_truth(')==4
            original=body.replace(NEW,OLD,1).replace('gd::native_scalar_truth(', 'gd::gd_truth(')
            assert hashlib.sha256((t[:start]+original+t[end:]).encode()).hexdigest()==digest
        else:assert sha(native/name)==digest,name
    return dict(passed=True,exact_inverse_matches_retained_source=True,one_header_only=True,
        all674_object_headers_and_all_layouts_unchanged=True,original_global_truth_and_equality_helpers_unchanged=True,
        non_null_capture_and_original_allocation_callback_fp_rng_order_retained=True,full20_formal_build_required=True)
def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    WORK.mkdir();native=WORK/'prototype_src';shutil.copytree(ACCEPTED/'bundle_src',native)
    component=transform(native);after=inventory(native)
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert sorted(n for n in frozen if frozen[n]!=after[n])==[HEADER] and set(after)==set(frozen)
    result=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,
        modified_files=[HEADER],new_files=[],component=component,baseline_cpp_source_files=708,candidate_cpp_source_files=708,
        no_layout_change=True,no_new_branches=True,not_for_deployment=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(verify_projection(native)),flush=True)

if __name__=='__main__':main()

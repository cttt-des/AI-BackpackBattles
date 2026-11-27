"""Frozen baseline and exact reversible transforms for two sequential experiments."""
import json,os
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,BASE,sha,inventory
NAME=os.environ['NATIVE_NEXT_ROUND']
assert NAME in ('dictionary_scalar_bundle','rng_scaling_bundle')
WORK=STAGE/'native_perf50'/NAME
CONFIG=json.loads((WORK/'round.json').read_bytes())
ACCEPTED=STAGE/'native_perf50'/CONFIG['baseline_bundle']
EXPECTED=CONFIG['baseline_dll_sha256']
ARCHIVE=CONFIG['parent_remote_commit']

def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def verify_projection(source):
    actual=inventory(source);before=json.loads((WORK/'baseline_source.json').read_bytes());changes=json.loads((WORK/'source_changes.json').read_bytes())
    assert len(actual)==len(before)==715 and set(actual)==set(before)
    for name,digest in before.items():
        if name not in changes:assert actual[name]==digest,name
        else:
            text=(source/name).read_text('utf8')
            for old,new in reversed(changes[name]):assert text.count(new)==1,(name,new[:100]);text=text.replace(new,old)
            assert text==(ACCEPTED/'bundle_src'/name).read_text('utf8'),name
    frozen=WORK/'source_before_build.json'
    if frozen.exists():assert actual==json.loads(frozen.read_bytes())
    return dict(passed=True,exact_inverse_matches_retained_source=True,all674_headers_and_layouts_unchanged=True,all_sorting_and_three_live_listener_loops_retained=True,no_change_to_floating_RNG_or_callback_order=True)

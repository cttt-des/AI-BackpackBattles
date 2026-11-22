"""Freeze the complete typed path checked against the deployed independent DLL."""
import json
from prepare_native_typed_hotchain import WORK as PROBE,STAGE,EXPECTED,sha,hook_component
from extend_native_typed_hotchain import transform
ACCEPTED=STAGE/'native_perf50/closed_timer_bundle'

def optimize(native):
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    local=json.loads((PROBE/'local_correctness.json').read_bytes());math=json.loads((PROBE/'math_correctness.json').read_bytes())
    assert local['passed'] and local['cases']==13112 and local['baseline_dll_sha256']==EXPECTED
    assert math['passed'] and math['math_cases']==33856 and math['helper_sha256']==sha(STAGE/'native_typed_damage_math.hpp')
    for name,digest in local['dependency_sha256'].items():assert sha(PROBE/name)==digest,name
    p=native/'engine_wrapper.cpp';text,hook=hook_component(p.read_text('utf8'));p.write_text(text,encoding='utf8',newline='\n')
    typed=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform_stage2.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    for key in list(result):
        if 'layout' in key or key=='source_shape':del result[key]
    result.update(baseline_dll_sha256=EXPECTED,components=['native source/result pointer entry','complete sealed takeDamage body','bounded scalar damage blocks','three nonescaping integer iterators','sealed Hook field reads'],
        modified_native_files=[n for n in before if before[n]!=after[n]],new_native_files=[n for n in after if n not in before],
        typed_damage_component=typed,hook_component=hook,local_independent_cases=13112,independent_math_cases=33856,
        nonvirtual_member_declaration_only=True,object_layout_changes_expected=False,
        ordinary_context_original_damage_body_byte_preserved=True,no_whole_fight_gain_claim=True)
    return result

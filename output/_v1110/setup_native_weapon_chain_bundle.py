"""Freeze the producer/consumer slice and retain the complete release protocol."""
import ast
import json
from pathlib import Path
from prepare_native_weapon_chain import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha,verify_projection

WORK=STAGE/'native_perf50/weapon_chain_bundle'
OLD_SHA='5bd31fdc2ab2e4a556c63987de62b9541d5793752d67662cc4034a36bdd69ecc'
OLD_ARCHIVE='5b28ade7ade2de018f121971f4c3bea4648c28d5'

def once(t,a,b):
    assert t.count(a)==1,(a[:160],t.count(a));return t.replace(a,b,1)

def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')

def adapt(t):
    for a,b in [('prepare_native_buff_inline_types','prepare_native_weapon_chain'),
        ('prototype_native_buff_inline_bundle','prototype_native_weapon_chain_bundle'),
        ('verify_native_buff_inline_helpers','verify_weapon_chain_buff_helpers'),
        ('verify_native_buff_inline_methods','verify_weapon_chain_buff_methods'),
        ('verify_native_buff_inline_full_pgo','verify_native_weapon_chain_full_pgo'),
        ('inspect_native_buff_inline_machine','inspect_retained_buff_weapon_chain_machine'),
        ('verify_buff_inline_','verify_weapon_chain_'),
        ('review_buff_inline_release','review_weapon_chain_release'),
        ('buff_inline_types_bundle','weapon_chain_bundle'),('buff_inline_types_prototype','weapon_chain_prototype'),
        ('buff-inline-formal-','weapon-chain-formal-'),(OLD_SHA,EXPECTED),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t

def main():
    pre=json.loads((PROBE/'semantic_preflight.json').read_bytes());assert pre['passed'] and pre['cases']==818432
    assert pre['requires_actual_production_pgo_comparison_before_timing']
    WORK.mkdir(exist_ok=True)
    for p in ACCEPTED.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','wait_calibration_window.py'):continue
        t=adapt(p.read_text('utf8'))
        t=t.replace("WORK.parent/'container_builtins_bundle/","WORK.parent/'buff_inline_types_bundle/")
        t=t.replace("'native_container_builtins_bundle_bundle_'","'native_buff_inline_types_bundle_bundle_'")
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/buff_integer_kernel_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'")
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'container_builtins_bundle'","OLD=WORK.parent/'buff_inline_types_bundle'")
            t=t.replace('native_perf50/container_builtins_bundle','native_perf50/buff_inline_types_bundle')
            t=t.replace('len(rows)==708','len(rows)==709')
        if p.name=='test_regeneration_guards.py':t=t.replace('708','709')
        if p.name=='verify_installed.py':t=t.replace('708','709')
        if p.name=='validate_then_compare.py':
            t=once(t,"    run('inspect_buff_machine.py','machine_code.log')","    run('verify_weapon_chain.py','weapon_chain_tests.log')\n    run('inspect_buff_machine.py','machine_code.log')")
            t=once(t,"    run('inspect_buff_machine.py','machine_code.log')","    run('inspect_weapon_chain_machine.py','weapon_chain_machine.log')\n    run('inspect_buff_machine.py','machine_code.log')")
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(buff_integer_helper_cases="
            t=once(t,anchor,"    from verify_native_weapon_chain import verify as verify_chain\n    chain=verify_chain(WORK/'bundle_src',WORK/'bundle.dll',target/'weapon_chain_tests.json')\n    result=dict(weapon_chain_cases=chain['cases'],buff_integer_helper_cases=")
        if p.name in ('install_verified.py','verify_installed.py'):
            anchor="    assert post_ab['container_builtin_cases']==128128" if p.name=='install_verified.py' else "    builtin=read('container_builtins_tests.json');assert builtin['passed'] and builtin['cases']==128128 and builtin['dll_sha256']==actual"
            t=once(t,anchor,anchor+"\n    chain=json.loads((WORK/'weapon_chain_tests.json').read_bytes());assert chain['passed'] and chain['cases']==136128 and chain['dll_sha256']==actual")
        save(WORK/p.name,t)
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_weapon_chain import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'weapon_chain_tests.json')\n"
    save(WORK/'verify_weapon_chain.py',wrapper)
    save(WORK/'inspect_weapon_chain_machine.py','import runpy\nfrom pathlib import Path\nimport sys\ns=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))\nrunpy.run_path(str(s/"inspect_native_weapon_chain_machine.py"),run_name="__main__")\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        raw=(ACCEPTED/name).read_bytes();p=WORK/name
        if p.exists():assert p.read_bytes()==raw
        else:p.write_bytes(raw)
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        goal='First direction: typed weapon resource and damage producer/consumer boundaries',
        baseline_source_files=708,candidate_source_files=709,
        full_source_changes=[f'gen/shards/shard_{i:02}.cpp' for i in [0,1,2,9]]+['native_weapon_damage_chain.hpp'],
        components=['typed weapon cooldown/attack, item stamina/damage, character stamina/damage/takeDamage boundaries'],
        total_semantic_cases=818432,weapon_chain_cases=136128,
        prototype_preflight_sha256=sha(PROBE/'semantic_preflight.json'),
        prototype_build_mode_differences_retained=True,actual_production_pgo_equality_required_before_timing=True,
        arithmetic_rng_callbacks_and_field_observation_order_unchanged=True)
    for key in ['diagnostic_counts','diagnostic_counts_sha256','semantic_suite_sha256']:plan.pop(key,None)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    for old,new in [('verify_buff_inline_build_options.py','verify_weapon_chain_build_options.py'),
                    ('verify_native_buff_inline_full_pgo.py','verify_native_weapon_chain_full_pgo.py'),
                    ('inspect_native_buff_inline_machine.py','inspect_retained_buff_weapon_chain_machine.py'),
                    ('close_buff_inline_round.py','close_weapon_chain_round.py')]:save(STAGE/new,adapt((STAGE/old).read_text('utf8')))
    formal=adapt((STAGE/'run_buff_inline_formal.py').read_text('utf8'))
    formal=once(formal,"(PROBE/'semantic_suite.json')","(PROBE/'semantic_preflight.json')")
    save(STAGE/'run_weapon_chain_formal.py',formal)
    review=adapt((STAGE/'review_buff_inline_release.py').read_text('utf8')).replace('==708','==709')
    review=once(review,"assert sorted(changed)==['gen/shards/shard_00.cpp']","assert sorted(changed)==['gen/shards/shard_00.cpp','gen/shards/shard_01.cpp','gen/shards/shard_02.cpp','gen/shards/shard_09.cpp','native_weapon_damage_chain.hpp']")
    review=once(review,"'buff_full_pgo_tests.json')","'buff_full_pgo_tests.json','weapon_chain_tests.json')")
    anchor="    assert read('buff_integer_tests.json')['cases']==218400"
    review=once(review,anchor,anchor+"\n    assert read('weapon_chain_tests.json')['cases']==read('post_ab_directed_regressions.json')['weapon_chain_cases']==136128")
    save(STAGE/'review_weapon_chain_release.py',review)
    print(json.dumps(dict(prepared=True,scripts=len(list(WORK.glob('*.py'))),candidate_source_files=709,total_semantic_cases=818432)))

if __name__=='__main__':main()

"""Freeze the new production profile and a distinct next-step review."""
import json
from pathlib import Path
from prepare_native_container_builtins import STAGE,BASE,sha

WORK=STAGE/'native_perf50/container_builtins_followup_profile'
ACCEPTED=STAGE/'native_perf50/container_builtins_bundle'

def save(name,data):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf8')

def main():
    profile=WORK/'profile_depth64.json';p=json.loads(profile.read_bytes())
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    actual=sha(BASE/'libgdcore.dll')
    assert actual==backup['production_dll_sha256']==p['dll_sha256'] and backup['remote_upload_verified']
    assert actual=='5bd31fdc2ab2e4a556c63987de62b9541d5793752d67662cc4034a36bdd69ecc'
    assert p['workload']=='original_replays' and p['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert p['samples']>=2000 and p['native_stack_depth_limit']==64
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert len(frozen)==713 and all(sha(BASE/n)==h for n,h in frozen.items())
    save('profile_receipt.json',dict(passed=True,dll_sha256=actual,profile_sha256=sha(profile),samples=p['samples'],
        batches=p['batches'],depth_limit=64,samples_at_depth_limit=p['samples_at_depth_limit'],
        same_fixed200_corpus=True,source_files_verified=713,verified_remote_backup=backup['remote_verified_commit'],
        no_speed_claim=True,no_sample_fraction_as_gain_or_ceiling=True))
    save('next_candidate_review.json',dict(baseline_dll_sha256=actual,verified_remote_backup=backup['remote_verified_commit'],
        implemented=False,new_branch_required=False,profile_sha256=sha(profile),
        proposed_combination=['Extend existing scalar equality helper with original same-kind identity cases',
            'Use a conservative equality helper in original array search/count and dictionary find_index'],
        existing_scalar_equality_already_deployed=True,existing_container_read_and_mutator_paths_already_deployed=True,
        incremental_scope=['Obj/Dict/ClassRef/Enum/FuncRef/Rng pointer equality',
            'Str/Arr identical pointers only; different pointers retain original comparison',
            'Container Int/Bool/Null and identity comparisons; preserve hash gating and loop order'],
        floating_constraints=['Float lookup parameters retain original gd_eq path',
            'Vec2/Color, mixed numeric and nested arrays retain original comparison semantics',
            'Never shortcut Color equality using pointer identity; same pointer still compares floating components'],
        required_before_formal_build=['Exact inverse reproduces baseline sources',
            'Actual baseline/candidate DLL differential checks including all rounding/DAZ/FTZ, flags, aliases and dictionary modes',
            'Retain all463904 earlier semantic cases and all established regressions',
            'Full20 instrumentation and fresh18PGO; original floating options'],
        unresolved_value_must_be_measured=True,no_individual_speed_claim=True,
        method_name_hint_alternative='Deferred: symbol re-registration/concurrency and object observation require independent proof',
        user_load20_policy='Estimate20 from measured load with existing empirical model; coverage/idle are not release gates'))
    print(json.dumps(dict(passed=True,samples=p['samples'],batches=p['batches'],dll_sha256=actual,next_candidate_implemented=False)),flush=True)

if __name__=='__main__':main()

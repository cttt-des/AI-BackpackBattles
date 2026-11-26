"""Retain concrete Weapon receiver types at two tiny typed producer boundaries."""
import hashlib
import json
import shutil
from prepare_native_weapon_chain import STAGE,BASE,ACCEPTED,EXPECTED,sha,inventory,once,HELPERS
import prepare_native_weapon_chain as previous

WORK=STAGE/'native_perf50/weapon_inline_chain_prototype'
BACKUP=STAGE/'native_perf50/weapon_chain_bundle'
ARCHIVE='379afbdd73ed438ada5b4a008c179ad9bf363e9a'
HEADER_NAME=previous.HEADER_NAME

def archive():
    r=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE

def inline_changes(native):
    p=native/'gen/shards/shard_09.cpp';old=p.read_text('utf8');text=old
    definitions=[]
    for name in ['weapon_attack','weapon_cooldown']:
        start=text.index('GdVal '+name+'(Item& self')
        end=text.index('\n}',start)+2;body=text[start:end]
        definitions.append('template<class W> __attribute__((always_inline)) inline '+body.replace('(Item& self','(W& self',1))
        text=once(text,body,'')
    head,separator,tail=text.rpartition('\nnamespace gd::weapon_chain {\n')
    assert separator and tail.strip()=='}';text=head
    h=native/HEADER_NAME;old_header=h.read_text('utf8');assert old_header==previous.HEADER
    new_header=old_header
    new_header=once(new_header,'#include "native_event_kernel.hpp"\n','#include "native_event_kernel.hpp"\n#include "native_scalar_equal.hpp"\n')
    for name,args in [('weapon_attack','Item&,const GdVal&'),('weapon_cooldown','Item&')]:
        new_header=once(new_header,'GdVal '+name+'('+args+');','template<class W> __attribute__((always_inline)) inline GdVal '+name+'('+args.replace('Item&','W&')+');')
    new_header=once(new_header,'} // namespace weapon_chain','\n'+'\n'.join(definitions)+'\n} // namespace weapon_chain')
    p.write_text(text,encoding='utf8',newline='\n');h.write_text(new_header,encoding='utf8',newline='\n')
    return {p.relative_to(native).as_posix():[dict(old=old,new=text)],HEADER_NAME:[dict(old=old_header,new=new_header)]}

def transform(native):
    base=previous.transform(native)
    first=json.loads((previous.WORK/'transform.json').read_bytes());assert inventory(native)==first['source_sha256']
    edits=inline_changes(native)
    return dict(base_component=base,inline_edits=edits,
        concrete_weapon_types_retained_at_two_producers=True,two_tiny_producers_forced_inline=True,
        no_damage_arithmetic_or_stamina_arithmetic_changes=True,no_further_character_damage_inlining='Already inlined into Item damage in actual first-round PGO',
        all_first_round_fallback_and_snapshot_guards_retained=True,
        evidence='native_perf50/weapon_chain_boundary_assessment/profile_failed_candidate.json',
        previous_pgo_machine_evidence_sha256=sha(BACKUP/'weapon_chain_machine_receipt.json'))

def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==frozen['source_sha256']
    first=json.loads((previous.WORK/'transform.json').read_bytes());original=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=frozen['component'];inline_edits=component['inline_edits'];edits=component['base_component']['edits']
    assert set(inline_edits)=={'gen/shards/shard_09.cpp',HEADER_NAME}
    for name,h in first['source_sha256'].items():
        if name not in inline_edits and name not in edits:
            assert sha(native/name)==h==original[name],name
            continue
        t=(native/name).read_text('utf8')
        for e in reversed(inline_edits.get(name,[])):t=once(t,e['new'],e['old'])
        assert hashlib.sha256(t.encode()).hexdigest()==h,name
        if name==HEADER_NAME:assert t==previous.HEADER;continue
        for e in reversed(edits.get(name,[])):t=once(t,e['new'],e['old'])
        assert hashlib.sha256(t.encode()).hexdigest()==original[name],name
    assert set(inventory(native))-set(original)=={HEADER_NAME}
    return dict(passed=True,exact_inverse_matches_retained_source=True,exact_two_layer_inverse_matches_retained_source=True,all674_object_headers_and_all_layouts_unchanged=True,
        full_original_bodies_retained=True,all_prior_optimizations_retained=True,formal_full20_fresh18_pgo_required=True)

def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    WORK.mkdir(exist_ok=True);native=WORK/'prototype_src';assert not native.exists()
    shutil.copytree(ACCEPTED/'bundle_src',native);component=transform(native)
    after=inventory(native);before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    modified=[n for n,h in before.items() if after[n]!=h]
    assert sorted(modified)==[f'gen/shards/shard_{i:02}.cpp' for i in [0,1,2,9]]
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=modified,new_files=[HEADER_NAME],baseline_cpp_source_files=708,candidate_cpp_source_files=709,
        all_layouts_unchanged=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    for name in ['damage_fixture.hpp','damage_state_fields.hpp','weapon_fixture_base.cpp']:
        shutil.copyfile(previous.WORK/name,WORK/name)
    print(json.dumps(verify_projection(native)),flush=True)

if __name__=='__main__':main()

"""Prepare the existing complete protocol for a local assembly membership slice."""
import ast
from pathlib import Path
from prepare_native_assembly_membership import STAGE

def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')

def main():
    t=(STAGE/'setup_native_weapon_chain_bundle.py').read_text('utf8').replace('weapon_chain','assembly_membership')
    t=t.replace('from verify_native_assembly_membership import verify','from verify_assembly_weapon_chain import verify')
    t=t.replace('assembly_membership_cases','weapon_chain_cases').replace("'assembly_membership_tests.json'","'weapon_chain_tests.json'").replace("'assembly_membership_tests.log'","'weapon_chain_tests.log'").replace("'verify_assembly_membership.py'","'verify_retained_weapon_chain.py'")
    t=t.replace('818432','1047808').replace('native_weapon_damage_chain.hpp','native_assembly_membership.hpp').replace('for i in [0,1,2,9]','for i in [0]')
    t=t.replace("\"STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'\"","\"STAGE/'native_perf50/weapon_inline_chain_bundle/checkpoint_receipt.json'\"")
    old="['gen/shards/shard_00.cpp','gen/shards/shard_01.cpp','gen/shards/shard_02.cpp','gen/shards/shard_09.cpp','native_assembly_membership.hpp']"
    assert t.count(old)==1;t=t.replace(old,"['gen/shards/shard_00.cpp','native_assembly_membership.hpp']")
    t=t.replace('First direction: typed weapon resource and damage producer/consumer boundaries','Second direction: local affected-object set membership')
    t=t.replace("components=['typed weapon cooldown/attack, item stamina/damage, character stamina/damage/takeDamage boundaries']","components=['local primitive membership with an Obj-key unindexed empty dictionary shortcut']")
    anchor='        save(WORK/p.name,t)'
    extra='''        if p.name=='validate_then_compare.py':
            a="    run('verify_retained_weapon_chain.py','weapon_chain_tests.log')"
            t=once(t,a,a+"\\n    run('verify_assembly_membership.py','assembly_membership_tests.log')")
        if p.name=='verify_object_routes_after_ab.py':
            a="    result=dict(weapon_chain_cases=chain['cases'],"
            b="    from verify_native_assembly_membership_helpers import verify as verify_membership\\n    membership=verify_membership(WORK/'bundle_src',WORK/'bundle.dll',target/'assembly_membership_tests.json')\\n    result=dict(assembly_membership_cases=membership['cases'],weapon_chain_cases=chain['cases'],"
            t=once(t,a,b)
        if p.name in ('install_verified.py','verify_installed.py'):
            a="    chain=json.loads((WORK/'weapon_chain_tests.json').read_bytes());assert chain['passed'] and chain['cases']==136128 and chain['dll_sha256']==actual"
            t=once(t,a,a+"\\n    membership=json.loads((WORK/'assembly_membership_tests.json').read_bytes());assert membership['passed'] and membership['cases']==229376 and membership['dll_sha256']==actual")
'''
    assert t.count(anchor)==1;t=t.replace(anchor,extra+anchor)
    anchor="    save(WORK/'verify_retained_weapon_chain.py',wrapper)"
    extra="    save(WORK/'verify_assembly_membership.py',\"import sys\\nfrom pathlib import Path\\nWORK=Path(__file__).resolve().parent\\nsys.path.insert(0,str(WORK.parents[1]))\\nfrom verify_native_assembly_membership_helpers import verify\\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'assembly_membership_tests.json')\\n\")\n"
    assert t.count(anchor)==1;t=t.replace(anchor,anchor+'\n'+extra)
    t=t.replace('total_semantic_cases=1047808,weapon_chain_cases=136128,','total_semantic_cases=1047808,weapon_chain_cases=136128,assembly_membership_cases=229376,')
    anchor="    save(STAGE/'review_assembly_membership_release.py',review)"
    extra='''    review=once(review,"'buff_full_pgo_tests.json','weapon_chain_tests.json')","'buff_full_pgo_tests.json','weapon_chain_tests.json','assembly_membership_tests.json')")
    review=once(review,"    assert read('weapon_chain_tests.json')['cases']==read('post_ab_directed_regressions.json')['weapon_chain_cases']==136128","    assert read('weapon_chain_tests.json')['cases']==read('post_ab_directed_regressions.json')['weapon_chain_cases']==136128\\n    assert read('assembly_membership_tests.json')['cases']==read('post_ab_directed_regressions.json')['assembly_membership_cases']==229376")
'''
    assert t.count(anchor)==1;t=t.replace(anchor,extra+anchor)
    save(STAGE/'setup_native_assembly_membership_bundle.py',t)
    t=(STAGE/'prototype_native_weapon_chain_bundle.py').read_text('utf8').replace('weapon_chain','assembly_membership').replace('818432','1047808')
    t=t.replace('typed weapon/resource/Item/Character damage producer-consumer boundaries','local affected-object-set primitive membership')
    save(STAGE/'prototype_native_assembly_membership_bundle.py',t)
    print('Prepared assembly membership protocol adapters',flush=True)

if __name__=='__main__':main()

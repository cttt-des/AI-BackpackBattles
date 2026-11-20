"""Fold the immutable EventType reverse lookup; preserve unknown-value fallback."""
import argparse
import hashlib
from pathlib import Path
import re
from optimize_native_serial_paths import method_body

SHARD_INPUT='f8696da573e296e8cfaee470d29d36e309f3d84ce77d4cfd0c5942fd611bee8f'
SHARD_OUTPUT='626dec8ddfc5f1e2afb3f5e6cae2efbdf701cad6a3af8e1f852adc22252a0d74'
ENUM_PROOF='7233a27ad3a9c7831abe00258cb6a24ea80baf5d347cb84bcf8c3c664df82609'
ACCESSOR_PROOF='cd0115070956eae5c27de0677019278aa8356245492087c9e5f9643cf821a95c'
ORIGINAL_BLOCK='            {\n                gd::GdVal _t542 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395));\n                gd::GdArr* _t543 = (_t542.kind == gd::GdVal::Kind::Arr) ? _t542.arr : nullptr;\n                uint32_t _len__t544 = _t543 ? _t543->len : 0u;\n                for (uint32_t _t544 = 0; _t544 < _len__t544; ++_t544) {\n                    gd::GdVal lv__k = _t543->data[_t544];\n                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395), lv__k), lv_stackType)))) {\n                        lv__stack_type_name = lv__k;\n                        break;\n                    }\n                }\n            }\n'
HELPER='gd::GdVal gd_native_stack_type_name(gd::BattleCtx& battle,const gd::GdVal& value) {\n    if(value.kind!=gd::GdVal::Kind::Int)return gd::GdVal::null();\n    const char* name=nullptr;\n    switch(value.i) {\n        case 0LL: name="Activation"; break;\n        case 1LL: name="DealDamage"; break;\n        case 2LL: name="CriticalDamage"; break;\n        case 3LL: name="MissedAttack"; break;\n        case 4LL: name="TakeDamage"; break;\n        case 5LL: name="LoseHealth"; break;\n        case 6LL: name="AttackSpeed"; break;\n        case 7LL: name="InvulnerableStart"; break;\n        case 8LL: name="InvulnerableEnd"; break;\n        case 9LL: name="Stun"; break;\n        case 10LL: name="StunResisted"; break;\n        case 11LL: name="CriticalResisted"; break;\n        case 12LL: name="Health"; break;\n        case 13LL: name="Stamina"; break;\n        case 14LL: name="DrainStamina"; break;\n        case 15LL: name="OutofStamina"; break;\n        case 16LL: name="DamageBuff"; break;\n        case 17LL: name="DamReduction"; break;\n        case 18LL: name="DamIncrease"; break;\n        case 19LL: name="TemporaryMaxHealth"; break;\n        case 20LL: name="TemporaryMaxStamina"; break;\n        case 21LL: name="BattleRageStart"; break;\n        case 22LL: name="BattleRageEnd"; break;\n        case 23LL: name="Reincarnate"; break;\n        case 24LL: name="CooldownAdvance"; break;\n        case 98LL: name="Unhealing"; break;\n        case 99LL: name="Fatigue"; break;\n        case 100LL: name="Block"; break;\n        case 101LL: name="Lucky"; break;\n        case 102LL: name="Regeneration"; break;\n        case 103LL: name="Vampirism"; break;\n        case 104LL: name="Spikes"; break;\n        case 105LL: name="Mana"; break;\n        case 106LL: name="Empower"; break;\n        case 107LL: name="Heat"; break;\n        case 108LL: name="Poison"; break;\n        case 109LL: name="Blind"; break;\n        case 110LL: name="Cold"; break;\n        case 111LL: name="Win"; break;\n        case 112LL: name="Loss"; break;\n        default:return gd::GdVal::null();\n    }\n    return gd::GdVal::from_cstr(battle.arena,name);\n}\n\n'
LOWERED_BLOCK='            const auto native_stack_name=gd_native_stack_type_name(gd_ctx,lv_stackType);\n            if(!native_stack_name.is_null()) {\n                lv__stack_type_name=native_stack_name;\n            } else\n            {\n                gd::GdVal _t542 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395));\n                gd::GdArr* _t543 = (_t542.kind == gd::GdVal::Kind::Arr) ? _t542.arr : nullptr;\n                uint32_t _len__t544 = _t543 ? _t543->len : 0u;\n                for (uint32_t _t544 = 0; _t544 < _len__t544; ++_t544) {\n                    gd::GdVal lv__k = _t543->data[_t544];\n                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395), lv__k), lv_stackType)))) {\n                        lv__stack_type_name = lv__k;\n                        break;\n                    }\n                }\n            }\n'

def digest(s):return hashlib.sha256(s.encode()).hexdigest()

RUNTIME_PROOFS = {'^bool GdEnum::get\\([^\\n]*\\n.*?^\\}': '1b17b534ac25c1e96fe4aa6c3a82d8055e9ae11336d32d9ee706c6a704ebd1cb', '^GdArr\\* GdEnum::keys_arr\\([^\\n]*\\n.*?^\\}': '5afa861033bbeb66d63b70bfdf0eef3237609550246ace4b99a53a6ec1319a06', '^bool gd_eq\\([^\\n]*\\n.*?^\\}': '6d09f87a44f48fe8d70e76a46e2c1bdc0dbadaf80d954075d7b27a788ac1049e', '^GdVal get_index\\([^\\n]*\\n.*?^\\}': 'af16316faee8b5d4cfbad1076f3fe6375e105aef903c375b1772ea831f0e774c'}

def optimize(native):
    runtime=(native/"gd_rt.cpp").read_text("utf8")
    for pattern,sha in RUNTIME_PROOFS.items():
        matches=re.findall(pattern,runtime,re.M|re.S)
        if len(matches)!=1 or digest(matches[0])!=sha:
            raise ValueError("An enum lookup/equality runtime invariant changed")
    constants=(native/'gen/shards/shard_06.cpp').read_text('utf8')
    enum=re.search(r'^static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_EventType\[\] = .*$',constants,re.M)[0]
    accessor=re.search(r'^gd::GdVal Gd__gd_core__CoreConst::get_static_const_or_enum\([^\n]*\n.*?^\}',constants,re.M|re.S)[0]
    if digest(enum)!=ENUM_PROOF or digest(accessor)!=ACCESSOR_PROOF:
        raise ValueError('The verified immutable EventType definition/accessor changed')
    path=native/'gen/shards/shard_02.cpp';s=path.read_text('utf8')
    if digest(s)==SHARD_OUTPUT:return
    if digest(s)!=SHARD_INPUT:raise ValueError('The verified character shard changed')
    anchor='gd::GdVal Gd__gd_core__CoreCharacter::fn__init('
    if s.count(anchor)!=1 or s.count(ORIGINAL_BLOCK)!=1:raise ValueError('The verified reverse lookup region changed')
    s=s.replace(anchor,HELPER+anchor,1).replace(ORIGINAL_BLOCK,LOWERED_BLOCK,1)
    if digest(s)!=SHARD_OUTPUT:raise ValueError('Unexpected reverse stack-name output')
    path.write_text(s,encoding='utf8',newline='\n')
    print('Folded immutable EventType reverse names; non-Int/unknown values retain the original scan',flush=True)

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)

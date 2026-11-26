"""Adapt the complete protocol for the distinct concrete receiver trial."""
import ast
import hashlib
import json
from pathlib import Path
import subprocess
from prepare_native_weapon_inline_chain import STAGE,BASE,WORK as PROBE,sha

def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')

def copy(old,new):
    t=(STAGE/old).read_text('utf8').replace('weapon_chain','weapon_inline_chain')
    return t

def main():
    t=copy('setup_native_weapon_chain_bundle.py','setup_native_weapon_inline_chain_bundle.py')
    a="\"STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'\""
    assert t.count(a)==1;t=t.replace(a,"\"STAGE/'native_perf50/weapon_chain_bundle/checkpoint_receipt.json'\"")
    t=t.replace("components=['typed weapon cooldown/attack, item stamina/damage, character stamina/damage/takeDamage boundaries']", "components=['typed weapon damage boundaries with two concrete receiver producer templates forced inline']")
    save(STAGE/'setup_native_weapon_inline_chain_bundle.py',t)
    save(STAGE/'prototype_native_weapon_inline_chain_bundle.py',copy('prototype_native_weapon_chain_bundle.py',''))
    t=copy('inspect_native_weapon_chain_machine.py','')
    t=t.replace("'weapon_inline_chain' in s","'weapon_chain' in s").replace("'weapon_inline_chain' in m.group(1)","'weapon_chain' in m.group(1)")
    anchor="    assert any('take_damage' in r['symbol'] for r in records)"
    assert t.count(anchor)==1
    t=t.replace(anchor,anchor+"\n    assert not any('weapon_attack' in r['symbol'] or 'weapon_cooldown' in r['symbol'] for r in records),'Tiny producers still emitted out of line'\n")
    t=t.replace('producer_consumer_typed_source_pointer_and_typed_result_abi_present=True,','producer_consumer_typed_source_pointer_and_typed_result_abi_present=True,two_tiny_weapon_producers_have_no_emitted_out_of_line_functions=True,')
    save(STAGE/'inspect_native_weapon_inline_chain_machine.py',t)
    t=copy('prepare_weapon_chain_terminal_tools.py','')
    t=t.replace('武器至伤害调用链定型第一轮','武器具体类型内联第二轮')
    t=t.replace('C++模拟器武器伤害调用链优化记录_2026-11-26.md','C++模拟器武器具体类型内联优化记录_2026-11-26.md')
    t=t.replace("STAGE/'native_perf50/remaining_value_review_after_d206'","STAGE/'native_perf50/weapon_chain_boundary_assessment'")
    t=t.replace("\"STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'\"","\"STAGE/'native_perf50/weapon_chain_bundle/checkpoint_receipt.json'\"")
    # The unchanged actual fixture is inherited from the prior verified backup.
    t=t.replace("'test_native_weapon_inline_chain.cpp'","'test_native_weapon_chain.cpp'")
    start=t.index("    description='");end=t.index("\n    t=t[:start]+description+t[end:]",start)
    description='。基于生产D206，第一轮完整ABI链535D已保留32对无正收益证据并归档379afbdd；本轮只在该链基础上将两个很短的Weapon生产入口移至私有头，以具体武器类型模板实例化并强制内联，消除其独立调用及CoreItem接收者类型丢失。取舍来自首轮正式PGO中仍存在的weapon_attack／weapon_cooldown独立函数、其直接调用指令及2032次真实语料栈采样；Character::dealDamage在首轮已被内联到Item伤害，本轮不原样重做该项或旧数学助手实验。所有伤害／体力算式、Source与Result入口、覆写／未知形态／默认argc回退、参数快照、浮点／RNG／回调和物理帧顺序均沿用前轮已验的原逻辑。674对象头及所有布局不变。严格双层逆变换逐字还原生产D206。保留全部818432例；普通构建须与源同生产的普通基准逐例一致，正式全新PGO须与实际生产完整一致才能测速。正式机器码要求两个微型生产入口不再形成独立函数；机制变化不充当收益，收益只由新源码的24对及至多一次8对A/B判定。'
    t=t[:start]+"    description="+repr(description)+t[end:]
    # Compare staged contents: an index stat-cache refresh is not a staged edit.
    anchor="    save(STAGE/'verify_weapon_inline_chain_phase.py',t)"
    replacement="    t=t.replace('import json\\n','import json\\nimport hashlib\\n',1)\n    t=t.replace(\"backup['workspace_state']['head']==boundary['head'] and backup['workspace_state']['index_sha256']==boundary['index_sha256']\",\"backup['workspace_state']['head']==boundary['head']\\n    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==boundary['staged_entries_sha256']\")\n"+anchor
    assert t.count(anchor)==1;t=t.replace(anchor,replacement)
    t=t.replace("scripts=('prepare_native_weapon_inline_chain.py',","scripts=('prepare_weapon_inline_chain_protocol.py','prepare_native_weapon_inline_chain.py',")
    t=t.replace("    t=t.replace('perf: preserve forced inline Buff type propagation with complete evidence','perf: preserve typed weapon damage chain with complete evidence')",'    t=t.replace(\'perf: preserve forced inline Buff type propagation with complete evidence\',\'perf: preserve typed weapon damage chain with complete evidence\')\n    t=t.replace("    paths.add(ACCEPTED/\'checkpoint_receipt.json\')","    paths.add(ACCEPTED/\'checkpoint_receipt.json\')\\n    paths.add(STAGE/\'weapon_chain_boundary_profile_first.log\')")')
    save(STAGE/'prepare_weapon_inline_chain_terminal_tools.py',t)
    p=PROBE/'user_boundary_before.json'
    if not p.exists():
        old=json.loads((STAGE/'native_perf50/weapon_chain_prototype/user_boundary_before.json').read_bytes())
        repo=STAGE.parents[1]
        assert all(sha(repo/n)==h for n,h in old['protected'].items())
        index=Path(subprocess.check_output(['git','rev-parse','--git-path','index'],cwd=repo,text=True).strip())
        if not index.is_absolute():index=repo/index
        staged=subprocess.check_output(['git','ls-files','--stage','-z'],cwd=repo)
        old.update(head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=repo,text=True).strip(),index_sha256=sha(index),staged_entries_sha256=hashlib.sha256(staged).hexdigest())
        p.write_text(json.dumps(old,indent=2)+'\n',encoding='utf8')
    print('Prepared distinct receiver-inline protocol adapters; no formal build or timing started',flush=True)

if __name__=='__main__':main()

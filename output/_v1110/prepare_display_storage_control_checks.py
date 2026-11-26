"""Retain the complete control-word suite with the declared display layout."""
import ast
from prepare_native_display_storage import STAGE,once

def main():
    text=(STAGE/'verify_native_control_word.py').read_text('utf8')
    text=once(text,'from prepare_native_control_word import STAGE,WORK,ACCEPTED,EXPECTED,sha,verify_projection,HELPERS',
        'from prepare_native_display_storage import STAGE,WORK,ACCEPTED,EXPECTED,sha,verify_projection\nfrom prepare_native_control_word import HELPERS')
    text=once(text,'from verify_native_active_cooldown_final import verify as active_verify','from verify_native_display_active import verify as active_verify')
    text=once(text,".replace('prepare_native_active_prefetch','prepare_native_control_word')",
        ".replace('prepare_native_active_prefetch','prepare_native_display_storage')")
    anchor="    wrapper.write_text(text,encoding='utf8',newline='\\n')"
    insertion='''    original_layout_assert="    assert layouts['baseline']['CoreItem']==layouts['candidate']['CoreItem']==1792"
    declared_size=json.loads((WORK/'correctness.json').read_bytes())['candidate_core_item_bytes']
    assert text.count(original_layout_assert)==1
    text=text.replace(original_layout_assert,"    assert layouts['baseline']['CoreItem']==1792 and layouts['candidate']['CoreItem']=="+str(declared_size),1)
    original_equal="    assert layouts['baseline']==layouts['candidate'] and layouts['candidate']['BattleCtx']==328"
    assert text.count(original_equal)==1
    text=text.replace(original_equal,"    assert {k:v for k,v in layouts['baseline'].items() if k!='CoreItem'}=={k:v for k,v in layouts['candidate'].items() if k!='CoreItem'} and layouts['candidate']['BattleCtx']==328",1)
'''
    text=once(text,anchor,insertion+anchor)
    text=text.replace('public control predicates and all retained timer/frame semantics','display-compatible retained control predicates and timer/frame semantics')
    active=(STAGE/'verify_native_active_cooldown_final.py').read_text('utf8')
    active=once(active,"        assert actual['layout']==dict(GdVal=24,GdArr=32,CoreItem=1792,BattleCtx=328)",
        "        assert actual['layout']==dict(GdVal=24,GdArr=32,CoreItem=2112,BattleCtx=328)")
    ast.parse(active);active_out=STAGE/'verify_native_display_active.py';assert not active_out.exists()
    active_out.write_text(active,encoding='utf8',newline='\n')
    ast.parse(text)
    out=STAGE/'verify_native_display_control.py';assert not out.exists();out.write_text(text,encoding='utf8',newline='\n')
    print('Prepared complete44608 retained cases; only declared CoreItem byte assertion adapted, all state/legacy hashes intact')

if __name__=='__main__':main()

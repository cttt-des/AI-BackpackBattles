"""Rank missing cached methods using the current binary's caller stacks."""
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
NATIVE=STAGE/'sim_native/native_sim_cpp/native_sim'
OUT=STAGE/'native_perf50/post_property_control_profile'


def main():
    profile=json.loads((OUT/'profile_depth64.json').read_bytes())
    assert hashlib.sha256((NATIVE/'libgdcore.dll').read_bytes()).hexdigest()==profile['dll_sha256']
    header=(NATIVE/'native_inline_dispatch.hpp').read_text('utf8')
    slots=header[header.index('inline constexpr auto native_resolved_slots='):header.index('inline constexpr auto native_property_slots=')]
    old=[symbol for symbol,index in re.findall(r'value\[([\w:]+)\]=(\d+);',slots)]
    assert len(old)==112 and len(set(old))==112
    plan=analyze(NATIVE,profile,limit=999)
    assert plan['eligible_classes_with_pure_inheritance']==674
    missing=[row for row in plan['selected_methods'] if row['symbol'] not in old]
    heat=Counter()
    for name,count in profile['inclusive']:
        match=re.match(r'(Gd__\w+::fn_\w+)\(',name)
        if match:heat[match[1]]+=count
    self_calls=Counter();evidence={}
    for path in (NATIVE/'gen/shards').glob('*.cpp'):
        text=path.read_text('utf8')
        for match in re.finditer(r'^gd::GdVal (Gd__\w+::fn_\w+)\([^\n]*\n(.*?)^\}',text,re.M|re.S):
            caller,body=match[1],match[2]
            symbols=re.findall(r'gd::native_inline_call\(gd_ctx, gd::GdVal::from_obj\(this\), ([\w:]+),',body)
            for symbol in symbols:
                if symbol in old:continue
                self_calls[symbol]+=heat[caller]
                evidence.setdefault(symbol,[]).append({'caller':caller,'inclusive_samples':heat[caller]})
    ranked=['SYM_GEN_attack_941']
    assert ranked[0] not in old and 'SYM_GEN_useStamina_116' in old
    ranked+=[row['symbol'] for row in missing if row['symbol'] not in ranked]
    ranked+=[symbol for symbol,count in self_calls.most_common() if count>0 and symbol not in ranked]
    chosen=ranked[:16];assert len(chosen)==16 and not set(chosen)&set(old)
    # Force a complete inheritance analysis of every additional symbol too.
    added=analyze(NATIVE,profile,limit=0,extra_symbols=chosen)
    assert added['row_slots']==16 and added['eligible_classes_with_pure_inheritance']==674
    result={'baseline_dll_sha256':profile['dll_sha256'],'profile_samples':profile['samples'],
        'profile_sha256':hashlib.sha256((OUT/'profile_depth64.json').read_bytes()).hexdigest(),
        'old_method_slots':112,'proposed_method_slots':128,'original_slot_order_preserved':old,
        'new_methods':added['selected_methods'],'new_rows':added['resolved_rows'],'new_class_rows':added['class_rows'],
        'missing_sampled_methods':missing,'hot_self_call_evidence':{s:evidence.get(s,[]) for s in chosen},
        'reason':'Weapon.doCooldownEffect calls attack, absent from the existing112 slots; useStamina is already covered. Extend actual missing methods while preserving subtype overrides rather than forcing a base call.',
        'interpretation':'Inclusive samples overlap. Rankings are hypotheses, not measured savings.',
        'next_composition':'Extend missing hot methods and pure field coverage; retain the previous type/constructor components for whole-package testing.'}
    path=OUT/'hot_slot_gaps.json';assert not path.exists()
    path.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({key:result[key] for key in ('profile_samples','old_method_slots','proposed_method_slots','new_methods','reason')},indent=2))


if __name__=='__main__':main()

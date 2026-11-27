"""Require all unchanged legacy cases while verifying corrected matrices in full."""
import json
from prepare_ordering_correctness import WORK,sha,save
def read(p):return json.loads(p.read_bytes())
def difference(a,b,key):
    assert len(a[key])==len(b[key]);return [i for i,(x,y) in enumerate(zip(a[key],b[key])) if x!=y]
def weapon_labels():
    labels=[]
    for closed in (False,True):
        for daz in range(4):
            for family in range(4):
                limit=448 if family<2 else 16 if family==2 else 144
                for scenario in range(limit):
                    for config in range(3):
                        for rounding in range(4):labels.append(dict(family=family,scenario=scenario,append=family==2 and scenario==7))
            for config in (3,4):
                for scenario in range(16):
                    for rounding in range(4):labels.append(dict(family=1,scenario=scenario,append=False))
            for family in (4,5):
                for scenario in range(8 if family==4 else 2):
                    for config in range(3):
                        for rounding in range(4):labels.append(dict(family=family,scenario=scenario,append=False))
            for phase in range(8):
                for scenario in range(32):
                    for config in range(4):
                        for rounding in range(4):labels.append(dict(phase=phase,scenario=scenario,append=phase!=2 and scenario==23))
    assert len(labels)==136128;return labels

def check(kind):
    failed=WORK/(kind+'_old_contract_failure');deltas={};raw={}
    if kind=='private':
        for label,count in [('identity_snapshots',143360),('private_buff_loops',18432)]:
            old=failed/('baseline_'+label+'_cases.json');normal=WORK/old.name;before,after=read(old),read(normal)
            assert before['cases']==after['cases']==count;diff=difference(before,after,'hashes')
            expected=[i for i in range(count) if (i//16)%20 in (1,2)] if label=='identity_snapshots' else []
            assert diff==expected,(label,len(diff),len(expected));deltas[label]=diff;raw[old.name]=dict(old=sha(old),normal=sha(normal))
    elif kind=='literal':
        old=failed/'baseline_literal_cases.json';normal=WORK/old.name;before,after=read(old),read(normal)
        assert before['cases']==after['cases']==5184;diff=difference(before,after,'hashes');assert diff==list(range(6*192,7*192)),diff[:30]
        deltas['appended_listener_mode6']=diff;raw[old.name]=dict(old=sha(old),normal=sha(normal))
    else:
        old=failed/'weapon_chain_tests_checks/baseline_cases.json';normal=WORK/'weapon_chain_tests_checks/baseline_cases.json';before,after=read(old),read(normal);labels=weapon_labels();assert before['cases']==after['cases']==136128
        candidate=read(WORK/'weapon_chain_tests_checks/candidate_cases.json')
        for key in ('case_hashes','legacy_counter_hashes'):
            diff=difference(before,candidate,key);assert diff and all(labels[i]['append'] for i in diff),(key,diff[:20])
            if key=='case_hashes':assert diff==[i for i,row in enumerate(labels) if row['append']] and len(diff)==992
            else:assert len(diff)==224
            assert all(after[key][i]==candidate[key][i] for i,row in enumerate(labels) if row['append'])
            deltas[key]=diff
        normal_extra=difference(after,candidate,'case_hashes')
        expected=[base+17016*group for group in range(8) for base in (16077,16205,16333,16461,16589,16717,16973)]
        assert normal_extra==expected and all(not labels[i]['append'] for i in normal_extra)
        assert not difference(after,candidate,'legacy_counter_hashes')
        save('weapon_normal_build_difference.json',dict(passed=True,normal_vs_both_PGO_difference_indices=normal_extra,normal_vs_both_PGO_difference_count=56,all56_unaffected_by_listener_change=True,normal_compile_source='same corrected source; no LTO/PGO',unchanged_old_PGO_and_new_PGO_match_on_all56=True,selection='Use the independent old PGO result for every unchanged case, corrected normal + original Godot callback semantics for all992 appended-listener cases',raw_sha256=dict(old=sha(old),normal=sha(normal),formal=sha(WORK/'weapon_chain_tests_checks/candidate_cases.json'))))
        raw[old.name]=dict(old=sha(old),normal=sha(normal))
    result=dict(passed=True,kind=kind,all_original_cases_retained=True,all_non_mutating_old_state_and_counter_hashes_retained=True,changed_indices=deltas,changed_counts={k:len(v) for k,v in deltas.items()},raw_sha256=raw,normal_dll_sha256=sha(WORK/'corrected_normal_reference/bundle.dll'),formal_dll_sha256=sha(WORK/'bundle.dll'),source_of_changed_expectations='Original Godot live listener array iteration; normal vs formal compares every case, old baseline differs only in explicitly classified append cases.',original_Godot_reference_sha256=sha(WORK/'original_ordering_reference.json'))
    save(kind+'_expectation_correction.json',result);print('All old unaffected cases retained and changed append cases verified: '+str(result['changed_counts']),flush=True)

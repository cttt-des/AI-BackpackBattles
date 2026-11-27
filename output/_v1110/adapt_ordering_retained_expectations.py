"""After a concrete failure, preserve old outputs and enforce source-proven deltas."""
import argparse,json,sys
from prepare_ordering_correctness import STAGE,WORK,sha,save

def main():
    p=argparse.ArgumentParser();p.add_argument('kind',choices=['private','literal','weapon']);a=p.parse_args()
    spec={
        'private':('private_snapshots_tests.json','verify_private_snapshots.py','verify_assembly_membership_private',('baseline_identity_snapshots_cases.json','candidate_identity_snapshots_cases.json','baseline_private_buff_loops_cases.json','candidate_private_buff_loops_cases.json','baseline_identity_snapshots.log','candidate_identity_snapshots.log','baseline_private_buff_loops.log','candidate_private_buff_loops.log','private_integer_view.log')),
        'literal':('literal_span_tests.json','verify_literal_spans.py','verify_native_literal_spans',('baseline_literal_cases.json','candidate_literal_cases.json','baseline_literal_first.log','candidate_literal_first.log')),
        'weapon':('weapon_chain_tests.json','verify_retained_weapon_chain.py','verify_assembly_weapon_chain',('weapon_chain_tests_checks',)),
    }
    out,script,module,names=spec[a.kind];assert (WORK/out).exists() and not json.loads((WORK/out).read_bytes())['passed'],'Only adapt a recorded concrete mismatch'
    failed=WORK/(a.kind+'_old_contract_failure');assert not failed.exists();failed.mkdir()
    for name in (out,*names):
        source=WORK/name
        if source.exists():
            assert source.resolve().is_relative_to(WORK.resolve());source.rename(failed/name)
    wrapper=f'''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]));sys.path.insert(0,str(WORK))
from prepare_ordering_correctness import sha
import {module} as checks
checks.ACCEPTED=WORK/'corrected_normal_reference'
checks.EXPECTED=sha(checks.ACCEPTED/'bundle.dll')
if __name__=='__main__':
    checks.verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/{out!r})
    from check_ordering_retained_deltas import check
    check({a.kind!r})
'''
    (WORK/script).write_text(wrapper,encoding='utf8',newline='\n');print('Preserved actual old-contract failure; enabled full normal/PGO comparison plus restricted old-result delta check for '+a.kind)
if __name__=='__main__':main()

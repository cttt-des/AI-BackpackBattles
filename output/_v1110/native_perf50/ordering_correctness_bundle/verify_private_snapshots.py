import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]));sys.path.insert(0,str(WORK))
from prepare_ordering_correctness import sha
import verify_assembly_membership_private as checks
checks.ACCEPTED=WORK/'corrected_normal_reference'
checks.EXPECTED=sha(checks.ACCEPTED/'bundle.dll')
if __name__=='__main__':
    checks.verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'private_snapshots_tests.json')
    from check_ordering_retained_deltas import check
    check('private')

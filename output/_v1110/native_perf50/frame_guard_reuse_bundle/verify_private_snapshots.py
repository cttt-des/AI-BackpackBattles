import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]));sys.path.insert(0,str(WORK))
from prepare_frame_guard_reuse import ACCEPTED,EXPECTED
import verify_assembly_membership_private as checks
checks.ACCEPTED=ACCEPTED;checks.EXPECTED=EXPECTED
if __name__=='__main__':checks.verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'private_snapshots_tests.json')

import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
sys.path.insert(0,str(Path(__file__).resolve().parent))
from verify_assembly_membership_private import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'private_snapshots_tests.json')

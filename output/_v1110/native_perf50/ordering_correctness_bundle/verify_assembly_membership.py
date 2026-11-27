import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
sys.path.insert(0,str(Path(__file__).resolve().parent))
from verify_native_assembly_membership_helpers import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'assembly_membership_tests.json')

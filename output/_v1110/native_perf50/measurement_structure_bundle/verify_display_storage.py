import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
sys.path.insert(0,str(Path(__file__).resolve().parent))
from verify_assembly_membership_display import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'display_storage_tests.json')

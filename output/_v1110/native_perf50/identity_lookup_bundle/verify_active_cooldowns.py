import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_display_active import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'active_cooldown_tests.json')

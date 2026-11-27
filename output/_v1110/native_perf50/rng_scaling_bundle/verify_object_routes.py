import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
sys.path.insert(0,str(Path(__file__).resolve().parent))
from verify_native_object_routes import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'object_routes_tests.json')

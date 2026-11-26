import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_identity_lookup import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'identity_lookup_tests.json')
    assert report['cases']==396400 and report['fixture_sha256']=='b103525f5ed99868fa8b3b5bd95f9020ef8b57768fbfe4f850ac205127eef063'

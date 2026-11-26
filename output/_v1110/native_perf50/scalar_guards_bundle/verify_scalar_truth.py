import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_scalar_guards import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'scalar_truth_tests.json')
    assert report['cases']==34400 and report['fixture_sha256']=='a08e1349dd3cae1f0a8698508eee25debc9d78f61745c8fb076631058fcde6db'

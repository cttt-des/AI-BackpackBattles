import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_assembly_membership_builtins import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'container_builtins_tests.json')
    assert report['cases']==128128 and report['fixture_sha256']=='3eb2bd0416d905f7239036a43deb2cc64a5dac5f8e83e7a048a7671bd2044b16'

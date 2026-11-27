"""Validate that a profiling child releases its temporary Windows DLL."""
import json,os,shutil,subprocess,sys
from pathlib import Path
from native_build_storage import workspace,ARCHIVE
from prepare_quiet_round import WORK,STAGE,sha,save


def main():
    dll=STAGE/'build_storage/parallel_headroom_tests_20261128/parallel3.dll'
    with workspace('quiet-profile-child-cleanup-check') as root:
        copied=root/'libgdcore.dll';shutil.copyfile(dll,copied)
        code='''import ctypes,sys
lib=ctypes.CDLL(sys.argv[1]);f=lib.schedule_0_0;f.argtypes=[ctypes.c_double];f.restype=ctypes.c_double
x=2.0
for k in range(30):x=x*1.0000001+(k+1)
assert f(2.0)==x
'''
        subprocess.run([sys.executable,'-c',code,str(copied)],check=True,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS)
        owned=root
    receipt=ARCHIVE/owned.name/'cleanup_receipt.json';row=json.loads(receipt.read_bytes())
    assert row['cleanup_complete'] and not owned.exists()
    save('profiling_child_cleanup_test.json',dict(passed=True,actual_child_load_and_call=True,temporary_DLL_deleted_after_child_exit=True,workspace=str(owned),cleanup_receipt=row,cleanup_receipt_sha256=sha(receipt)))
    print('Child-loaded DLL released and managed workspace removed')


if __name__=='__main__':main()

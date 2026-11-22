"""Verify packed-input sealed mode and the fixed200 original result signature."""
import ctypes
import json
import inspect_targeted_timer_fixed200 as driver
from prepare_native_closed_timer import WORK,sha

def main():
    driver.WORK=WORK
    driver.main()
    lib=ctypes.CDLL(str(WORK/'prototype.dll'))
    for name in ('gd_diag_native_timer_registry_closed','gd_diag_native_timer_closed_mode'):
        fn=getattr(lib,name);fn.argtypes=[];fn.restype=ctypes.c_int
        assert fn()==1,name
    report=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),actual_packed_runtime_mode=True,known_class_registry_remained_sealed=True)
    (WORK/'closed_mode_fixed200.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report))

if __name__=='__main__':main()

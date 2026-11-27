"""Diagnostic sampling of the immutable current baseline; no speed claim."""
import json,runpy,sys
import psutil
from calibrate_structure_measurement import WORK,STAGE,EXPECTED
def main():
    out=WORK/'profile_baseline.json';assert not out.exists()
    psutil.Process().cpu_affinity([2])
    sys.argv=[str(STAGE/'profile_native_windows.py'),'--dll',str(WORK/'baseline.dll'),'--corpus','--min-samples','8000','--max-depth','64','--full-output','--instruction-locations','--out',str(out)]
    runpy.run_path(str(STAGE/'profile_native_windows.py'),run_name='__main__')
    r=json.loads(out.read_bytes());assert r['dll_sha256']==EXPECTED
if __name__=='__main__':main()

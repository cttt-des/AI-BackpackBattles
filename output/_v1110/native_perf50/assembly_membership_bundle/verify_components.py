"""Verify the actual new member rows and frame helper after final PGO."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
def main():
    reports={}
    with tempfile.TemporaryDirectory(prefix='native-frame-ablation-final-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll')
        for name,file,flags in (('member','test_native_member_fields.cpp',['-DGD_MEMBER_PRODUCTION']),('frame','test_native_frame_segments.cpp',[])):
            exe=root/(name+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*flags,'-I',str(WORK/'bundle_src'),'-I',str(WORK),str(STAGE/file),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            output=subprocess.check_output([str(exe)],text=True)
            (WORK/(name+'_production_cases.json')).write_text(output,encoding='utf8')
            report=json.loads(output);assert report['passed'];reports[name]=report
    assert reports['member']['classes']==674 and reports['member']['cases']==125001
    assert reports['frame']['cases']==6912
    result={'passed':True,'dll_sha256':hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest(),'components':reports}
    (WORK/'member_frame_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))
if __name__=='__main__':main()

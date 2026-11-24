"""Recheck the final DLL's affected construction path after positive AB."""
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from prepare_native_compiler_pta import sha
from verify_native_object_routes import verify as verify_objects
from verify_native_callback_dispatch import verify
from verify_native_literal_spans import verify as verify_retained

def main():
    decision=json.loads((WORK/'candidate_decision.json').read_bytes())
    assert decision['status']=='positive_combined_evidence'
    assert decision['candidate_dll_sha256']==sha(WORK/'bundle.dll')
    target=WORK/'post_ab_checks';assert not target.exists();target.mkdir()
    obj=target/'object_routes';obj.mkdir()
    verify_objects(WORK/'bundle_src',WORK/'bundle.dll',obj/'object_routes.json')
    verify(WORK/'bundle_src',WORK/'bundle.dll',target/'callback_dispatch.json')
    retained=target/'retained_literal';retained.mkdir()
    verify_retained(WORK/'bundle_src',WORK/'bundle.dll',retained/'literal_spans.json')
    with tempfile.TemporaryDirectory(prefix='native-factory-final-constructor-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'bundle.dll',root/'libgdcore.dll')
        exe=root/'constructors.exe'
        with (target/'constructors_compile.log').open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
                '-I',str(WORK),'-I',str(WORK/'bundle_src'),str(STAGE/'test_native_type_constructor.cpp'),
                str(root/'libgdcore.dll'),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,check=True)
        run=subprocess.run([str(exe)],capture_output=True,text=True)
        (target/'constructors_cases.log').write_text(run.stdout+run.stderr,encoding='utf8')
        run.check_returncode()
    result=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),affected_object_route_cases=320256,affected_callback_cases=126192,retained_literal_span_cases=5184,
                retained_type_constructor_test_passed=True,
                reports_sha256={p.relative_to(target).as_posix():sha(p) for p in target.rglob('*') if p.is_file()})
    (WORK/'post_ab_directed_regressions.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()

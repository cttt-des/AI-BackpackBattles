"""Use the proven full20/fresh18 builder with this candidate's frozen inputs."""
import hashlib,subprocess
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,WORK,ARCHIVE,verify_projection
def main():
    source=STAGE/'build_ordering_release.py'
    assert source.read_bytes()==subprocess.check_output(['git','show',ARCHIVE+':output/_v1110/build_ordering_release.py'],cwd=REPO)
    text=source.read_text('utf8').replace('from prepare_ordering_correctness import','from prepare_frame_guard_reuse import')
    old="    assert json.loads((WORK/'prototype_ordering_tests.json').read_bytes())['passed']";assert text.count(old)==1
    text=text.replace(old,"    assert json.loads((WORK/'prototype_actual_frame_tests.json').read_bytes())['passed']")
    old="    assert all(json.loads((WORK/n).read_bytes())['passed'] for n in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json'))";assert text.count(old)==1
    text=text.replace(old,'    from prepare_frame_guard_reuse import verify_projection\n    verify_projection(WORK/\'bundle_src\')')
    text=text.replace('ordering-formal-','frame-guard-formal-').replace('Corrected release ready','Frame guard release ready')
    exec(compile(text,str(source),'exec'),dict(__name__='__main__',__file__=str(Path(__file__).resolve())))
if __name__=='__main__':main()

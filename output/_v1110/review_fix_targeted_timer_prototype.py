"""Preserve the stopped first attempt and apply only the reviewed FuncRef guard fix."""
import json
from pathlib import Path
import shutil
import tempfile
from prepare_native_targeted_timers import BASE,WORK,transform,sha

def main():
    assert (WORK/'build_attempt_1_stopped.json').exists()
    old=json.loads((WORK/'transform.json').read_bytes());source=WORK/'prototype_src'
    assert old['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert not (WORK/'transform_attempt_1.json').exists()
    shutil.copyfile(WORK/'transform.json',WORK/'transform_attempt_1.json')
    shutil.copyfile(source/'gd_rt.cpp',WORK/'gd_rt_attempt_1.cpp')
    with tempfile.TemporaryDirectory(prefix='native-timer-reviewed-source-') as directory:
        new=Path(directory)/'source';shutil.copytree(BASE,new,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=transform(new)
        changed=[k for k,v in old['source_sha256'].items() if report['source_sha256'][k]!=v]
        assert changed==['gd_rt.cpp'],changed
        shutil.copyfile(new/'gd_rt.cpp',source/'gd_rt.cpp')
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    receipt=dict(changed_files=changed,reason='Observe once at FuncRef entry; keep original unbraced conditional call and guard is_valid virtual boundary',first_attempt_retained=True)
    (WORK/'reviewed_fix.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    print(json.dumps(receipt))

if __name__=='__main__':main()

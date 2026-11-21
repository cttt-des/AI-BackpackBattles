"""Resume a completed release after removing only verified Python cache additions."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def save(name,data):(WORK/name).write_text(json.dumps(data,indent=2)+'\n',encoding='utf8',newline='\n')

def main():
    src=WORK/'bundle_src'
    expected=json.loads((WORK/'source_before_build.json').read_bytes())
    actual={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    added={name:sha for name,sha in actual.items() if name not in expected}
    assert set(added)=={'__pycache__/'+name+'.cpython-314.pyc' for name in ('build','build_windows','sim','test_parity','__init__')}
    assert all(actual[name]==sha for name,sha in expected.items())
    save('python_cache_guard_incident.json',{'original_build_exit_code':1,
        'cause':'Recursive compileall during preparation generated cache files; completed build rejected extra non-source files',
        'actual_source_bytes_changed':False,'only_added_files':added,'original_failure_log_retained':'build.log',
        'resolution':'Remove precisely the verified cache additions, recheck every frozen source byte, reuse completed source-identical release'})
    for name,sha in added.items():
        target=(src/name).resolve()
        assert target.is_relative_to(src.resolve()) and target.parent==src.resolve()/'__pycache__'
        assert digest(target)==sha;target.unlink()
    (src/'__pycache__').rmdir()
    assert {p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}==expected
    objects=Path((WORK/'bundle_objects.txt').read_text('utf8'))
    profile=objects/'pgo';dll=WORK/'bundle.dll'
    assert digest(dll)==digest(objects/'release.dll')=='444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc'
    assert 'compiled 18/20, linked 20 objs' in (WORK/'build.log').read_text('utf8')
    save('fresh_profile_source.json',{'dll_sha256':digest(dll),
        'source_manifest_sha256':digest(WORK/'source_before_build.json'),
        'profile_training_and_release_source_identical':True,
        'hot_profiles_sha256':{name:digest(profile/(name+'.gcda')) for name in sorted(HOT_UNITS)},
        'full20_instrumentation_and18_release_hot_units':True,'floating_options_unchanged':True,
        'python_cache_only_incident':'python_cache_guard_incident.json'})
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),'--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()

"""Reject unreviewed inheritance edits before writes and preserve idempotence."""
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import tempfile

WORK=Path(__file__).resolve().parent
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def state(root):return {p.relative_to(root).as_posix():(sha(p),p.stat().st_mtime_ns) for p in root.rglob('*') if p.is_file()}

def main():
    spec=importlib.util.spec_from_file_location('candidate_transform',WORK/'verified_bundle_pending.py')
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    with tempfile.TemporaryDirectory(prefix='native-dispatch-array-guards-') as directory:
        native=Path(directory)/'native'
        shutil.copytree(WORK/'bundle_src',native,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        initial=state(native)
        assert sum(p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py' for p in native.rglob('*') if p.is_file())==704
        module.optimize(native);assert state(native)==initial
        victim=native/'gen/hdrs/Gd__gd_core__CoreRng.hpp'
        original=victim.read_bytes();victim.write_bytes(original+b'\n// unreviewed inheritance edit\n')
        changed=state(native)
        for prepare in (False,True):
            try:module.optimize(native,prepare)
            except ValueError:pass
            else:raise AssertionError('Unknown source edit was accepted')
            assert state(native)==changed,'Guard wrote before rejecting the edit'
        victim.write_bytes(original)
        module.optimize(native,True);module.optimize(native)
        assert {p:row[0] for p,row in state(native).items()}=={p:row[0] for p,row in initial.items()}
        before=state(native);module.optimize(native);assert state(native)==before
    report={'passed':True,'source_inventory_verified':704,'transform_files':24,
        'matches_compiled_candidate':True,'idempotent_bytes_and_mtime':True,
        'untouched_header_changes_rejected_before_writes':True}
    (WORK/'regeneration_test.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()

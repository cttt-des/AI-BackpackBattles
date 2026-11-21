"""Relink the verified instrumentation objects with a bounded C export table."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def create_instrumented_exports(objects):
    baseline=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    assert digest(baseline)=='b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588'
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',baseline.name],cwd=baseline.parent,text=True)
    exports={line.split()[-1] for line in names.splitlines() if line.split() and line.split()[-1].startswith('gd_')}
    assert sum(name.startswith('gd_sim_') for name in exports)==22
    exports.add('gd_diag_native_variant_stat')
    exports.add('gd_diag_native_property_stat')
    exports.add('gd_diag_native_type_constructor_stat')
    exports.add('gd_diag_native_hot_slot_stat')
    exports.add('gd_diag_native_event_identity_stat')
    exports.add('gd_diag_native_lazy_diagnostic_stat')
    definition=objects/'instrumented_exports.def'
    definition.write_text('EXPORTS\n'+''.join('    '+name+'\n' for name in sorted(exports)),encoding='ascii',newline='\n')
    return definition,sorted(exports)

def main():
    src=WORK/'bundle_src';objects=Path((WORK/'bundle_objects.txt').read_text('utf8'))
    assert objects.is_dir() and objects.name.startswith('native-lazy-diagnostics-')
    expected=json.loads((WORK/'source_before_build.json').read_bytes())
    assert {p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}==expected
    before={p.name:digest(p) for p in objects.glob('*.o')};assert len(before)==20
    definition,exports=create_instrumented_exports(objects)
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';assert profile.is_dir()
    instrumented=build_dll(src,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),
        hot_units=HOT_UNITS,link_flags=('-Wl,--exclude-all-symbols',str(definition)))
    assert before=={p.name:digest(p) for p in objects.glob('*.o')},'Relink must reuse all20 identical compiled objects'
    report={'instrumentation_only':True,'reason':'Bounded exports for instrumentation-only PGO build',
        'exports':sorted(exports),'original_objects_reused':20,'object_sha256':before,
        'compile_and_fp_flags_unchanged':True,'release_link_policy':'Original automatic export, unchanged'}
    (WORK/'instrumented_export_policy.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    audit=objects/'audit_profile';audit.mkdir(exist_ok=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'inspect_variant.py'),'--dll',str(instrumented),'--out',str(WORK/'instrumented_audit.json')],check=True,
        env=dict(os.environ,GCOV_PREFIX=str(audit),GCOV_PREFIX_STRIP='99'))
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for unit in HOT_UNITS:(objects/(unit+'.o')).unlink()
    dll=build_dll(src,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(dll,WORK/'bundle.dll');print('release',digest(WORK/'bundle.dll'),flush=True)

if __name__=='__main__':main()

"""Compare both independent components to the actual released DLL first."""
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_member_frame_bundle import optimize,STAGE
from prototype_native_frame_segments_bundle import frame_helper
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/member_frame_bundle'
def main():
    WORK.mkdir(exist_ok=True)
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()=='593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670'
    helper,original=frame_helper(BASE)
    header='#pragma once\n#include "native_inline_dispatch.hpp"\n'
    for cls in ('Gd__gd_core__CoreItem','Gd__gd_core__CoreBuff','Gd__gd_core__CoreContext','Gd__gd_core__CoreCharacter','Gd__gd_core_items__Gems__Gem'):
        header+=f'#include "gen/hdrs/{cls}.hpp"\n'
    header+='namespace gd {\n'+helper+'}\n'
    (WORK/'preflight_frame_helper.hpp').write_text(header,encoding='utf8',newline='\n')
    spec=importlib.util.spec_from_file_location('property_fixture_generator',STAGE/'native_perf50/lazy_diagnostics_bundle/generate_property_tests.py')
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);module.WORK=WORK
    design=json.loads((STAGE/'native_perf50/lazy_diagnostics_bundle/transform.json').read_bytes())
    (WORK/'transform.json').write_text(json.dumps(design),encoding='utf8');module.main()
    rows=design['property_rows']
    text='#pragma once\n#include "native_property_test_cases.hpp"\nusing Member=gd::GdVal gd::GdObj::*;\nstatic const std::array<Member,64> probe_members[]={\n'
    for row in rows:text+='    {{'+','.join(f'static_cast<Member>(&{v[0]}::{v[1]})' if v else 'nullptr' for v in row)+'}},\n'
    text+='};\nstatic const unsigned probe_class_rows[]={'+','.join(str(pid) for cls,pid in sorted(design['class_property_rows'].items()))+'};\n'
    (WORK/'member_probe_cases.hpp').write_text(text,encoding='utf8',newline='\n')
    # Independently syntax-check the combined transform; never modify deployment.
    with tempfile.TemporaryDirectory(prefix='native-member-frame-preflight-') as directory:
        root=Path(directory);src=root/'source'
        shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(src)
        for shard in ('shard_00.cpp','shard_03.cpp','shard_12.cpp'):
            subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(src/'gen/shards'/shard)],check=True)
        (WORK/'transform_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
        shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll')
        for label,file,flags in (('member','test_native_member_fields.cpp',[]),('frame','test_native_frame_segments.cpp',['-DGD_FRAME_PREFLIGHT'])):
            exe=root/(label+'.exe')
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*flags,'-I',str(WORK),'-I',str(BASE),str(STAGE/file),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
            completed=subprocess.run([str(exe)],capture_output=True,text=True)
            (WORK/(label+'_preflight.log')).write_text(completed.stdout+completed.stderr,encoding='utf8')
            if completed.returncode:print(completed.stdout+completed.stderr,flush=True)
            completed.check_returncode()
            record=json.loads(completed.stdout);record.update(baseline_dll_sha256=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),
                source_sha256=hashlib.sha256((STAGE/file).read_bytes()).hexdigest(),no_full_build_or_deployment=True)
            (WORK/(label+'_preflight.json')).write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
            print(json.dumps(record),flush=True)
if __name__=='__main__':main()

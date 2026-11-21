"""Compare local loop logic to the actual deployed DLL before a full rebuild."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from prototype_native_frame_segments_bundle import BASE,STAGE,frame_helper,timer_loop

WORK=STAGE/'native_perf50/frame_segments_bundle'


def main():
    WORK.mkdir(exist_ok=True)
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()=='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
    helper,original=frame_helper(BASE)
    header='#pragma once\n#include "native_inline_dispatch.hpp"\n'
    for name in ('CoreBuff','CoreContext','CoreCharacter'):
        header+=f'#include "gen/hdrs/Gd__gd_core__{name}.hpp"\n'
    header+='#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"\nnamespace gd {\n'+helper+'}\n'
    (WORK/'preflight_frame_helper.hpp').write_text(header,encoding='utf8',newline='\n')
    _,timer=timer_loop()
    timer=timer.replace('this->rt_ctx_->native_resolved_collect','battle.native_resolved_collect')
    (WORK/'preflight_timer_loop.hpp').write_text('#pragma once\nstatic void candidate_timer_loop(gd::BattleCtx& battle,const gd::GdArr* items,const gd::GdVal& delta) {\n'+timer+'\n}\n',encoding='utf8',newline='\n')
    with tempfile.TemporaryDirectory(prefix='native-frame-preflight-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-DGD_FRAME_PREFLIGHT','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_frame_segments.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'frame_preflight.log').write_text(result.stdout+result.stderr,encoding='utf8')
        print(result.stdout+result.stderr,flush=True);result.check_returncode()
        report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),
        original_item_physics_sha256=hashlib.sha256(original.encode()).hexdigest(),
        helper_sha256=hashlib.sha256(helper.encode()).hexdigest(),
        independent_actual_original_functions=True,callback_rng_flags_and_float_bits_checked=True,
        fixture_sha256=hashlib.sha256((STAGE/'test_native_frame_segments.cpp').read_bytes()).hexdigest())
    (WORK/'frame_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    with tempfile.TemporaryDirectory(prefix='native-timer-chunk-preflight-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-DGD_FRAME_PREFLIGHT','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_timer_chunks.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'timer_preflight.log').write_text(result.stdout+result.stderr,encoding='utf8')
        print(result.stdout+result.stderr,flush=True);result.check_returncode()
        report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),independent_actual_original_timer_methods=True)
    (WORK/'timer_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')


if __name__=='__main__':main()

"""Real link-only parallelism check using the same LTO objects twice."""
import ast, ctypes, json, os, shutil, subprocess
from pathlib import Path
from unittest.mock import patch
from types import SimpleNamespace
import psutil
from native_build_storage import STAGE, workspace, sha
from native_build_schedule import GIB, select_jobs
from build_native_hot_lto import build_dll

OUT = STAGE / 'build_storage/parallel_headroom_tests_20261128'


def main():
    assert not OUT.exists(); OUT.mkdir(parents=True)
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    for name in ('native_build_schedule.py', 'build_native_hot_lto.py', 'quiet_round.py'):
        ast.parse((STAGE/name).read_text('utf8'))
    with patch.dict(os.environ, {'NATIVE_LTO_JOBS':'auto'}), \
         patch('native_build_schedule.psutil.cpu_count', side_effect=lambda logical=True:8 if logical else 4), \
         patch('native_build_schedule.psutil.virtual_memory', return_value=SimpleNamespace(available=8*GIB)):
        assert select_jobs()['lto_jobs'] == select_jobs()['frontend_jobs'] == 3
        assert select_jobs(2, 8)['lto_jobs'] == 3 and select_jobs(2, 8)['frontend_jobs'] == 2
    with patch('native_build_schedule.psutil.virtual_memory', return_value=SimpleNamespace(available=GIB)), \
         patch.dict(os.environ, {'NATIVE_LTO_JOBS':'auto'}):
        assert select_jobs()['lto_jobs'] == select_jobs()['frontend_jobs'] == 1
    src=OUT/'source'; (src/'gen/shards').mkdir(parents=True)
    shutil.copyfile(STAGE/'sim_native/native_sim_cpp/native_sim/build_windows.py', src/'build_windows.py')
    units=('gd_rt.cpp','engine_wrapper.cpp','gen/sym_ids.cpp','gen/register_all.cpp','gen/shards/shard_00.cpp')
    for i, name in enumerate(units):
        rows=[]
        for j in range(120):
            rows.append(f'extern "C" __declspec(dllexport) __attribute__((noinline)) double schedule_{i}_{j}(double x){{')
            for k in range(30): rows.append(f'x = x * 1.0000001 + {i+j+k+1}.0;')
            rows.append('return x;}')
        (src/name).write_text('\n'.join(rows)+'\n', encoding='utf8')
    receipts={}; outputs={}
    with workspace('parallel-real-lto-check') as root:
        objects=Path(os.environ['NATIVE_SIM_OBJ']);objects.mkdir()
        os.environ.update(NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe', MAKE='D:/mingw64/bin/mingw32-make.exe')
        previous=None
        for jobs in (2,3):
            dll=build_dll(src,OUT/f'parallel{jobs}.dll',2,hot_units={Path(n).stem for n in units},lto_jobs=jobs,
                          link_flags=('-save-temps=obj','--param=lto-min-partition=1','--param=lto-partitions=32'))
            hashes={p.name:sha(p) for p in objects.glob('*.o')};assert len(hashes)==5
            if previous is not None:assert hashes==previous
            previous=hashes
            receipt=json.loads(dll.with_suffix('.build_schedule.json').read_bytes())
            assert receipt['passed'] and receipt['object_lto_option']=='-flto=2'
            assert receipt['link_lto_option']==f'-flto={jobs}'
            assert any(f'-j{jobs}' in c for c in receipt['make_commands']), receipt
            receipts[str(jobs)]=receipt
            text=root/f'text{jobs}.bin'
            copied=root/f'parallel{jobs}.dll';shutil.copyfile(dll,copied)
            subprocess.run(['D:/mingw64/bin/objcopy.exe','-O','binary','--only-section=.text',str(copied),str(text)],check=True)
            outputs[str(jobs)]=sha(text)
            library=ctypes.CDLL(str(dll));fn=library.schedule_3_99;fn.argtypes=[ctypes.c_double];fn.restype=ctypes.c_double
            actual=fn(2.0)
            reference=2.0
            for k in range(30):reference=reference*1.0000001+(3+99+k+1)
            assert actual==reference
            assert not list(objects.glob('*.ltrans*.o')) and not list(objects.glob('*.ltrans*.s'))
        assert outputs['2']==outputs['3'], outputs
        owned=str(root)
    assert not Path(owned).exists()
    result=dict(passed=True,real_link_jobs=[2,3],unchanged_source_objects=True,identical_text_section=True,
                memory_pressure_falls_back_to_one=True,owned_workspace_removed=True,
                no_speed_claim_under_concurrent_build=True,text_sha256=outputs,receipts=receipts)
    (OUT/'receipt.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print('Parallel LTO check passed; no throughput claim under concurrent build',flush=True)


if __name__=='__main__':main()

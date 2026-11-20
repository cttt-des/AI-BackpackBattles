"""Check the empty-snapshot candidate before throughput trials."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from optimize_native_sparse_timers import optimize

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    dll=WORK/'sparse_timers.dll'
    src=WORK/'sparse_timers_src'
    baseline=STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll'
    before={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    optimize(src)
    assert before=={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    with tempfile.TemporaryDirectory(prefix='native-snapshot-abi-') as temp:
        symbols={}
        for label,path in (('baseline',baseline),('candidate',dll)):
            copied=Path(temp)/(label+'.dll')
            shutil.copyfile(path,copied)
            assert digest(copied)==digest(path)
            text=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(copied)],text=True)
            symbols[label]=sorted({line.split()[-1] for line in text.splitlines() if line.split() and line.split()[-1].startswith('gd_sim_')})
        assert symbols['baseline']==symbols['candidate'] and len(symbols['baseline'])==22
    (WORK/'sparse_timers_abi.json').write_text(json.dumps({'baseline_dll_sha256':digest(baseline),'candidate_dll_sha256':digest(dll),'unchanged_c_abi':symbols['candidate'],'generator_idempotent':True},indent=2)+'\n',encoding='utf8')
    directory=Path(tempfile.mkdtemp(prefix="native-inline-timer-candidate-"))
    shutil.copyfile(dll,directory/"libgdcore.dll")
    (WORK/"inline_candidate_test_directory.txt").write_text(str(directory),encoding="utf8")
    tests=(("test_native_sparse_timers.cpp","sparse_differential_test.json",[]),
           ("test_native_timer_scan_tracking.cpp","tracking_test.json",["-DGD_SPARSE_TIMER_CANDIDATE"]),
           ("test_native_inline_timers.cpp","inline_candidate_test.json",["-DGD_INLINE_TIMER_CANDIDATE"]),
           ("test_native_timer_dispatch.cpp","timer_regression_test.json",[]),
           ("test_native_item_prefetch.cpp","traversal_regression_test.json",[]),
           ("test_native_noop_snapshots.cpp","snapshot_regression_test.json",[]))
    for number,(file,receipt,extra) in enumerate(tests):
        executable=directory/f"test_{number}.exe"
        subprocess.run(["D:/mingw64/bin/g++.exe","-static","-O2","-std=c++20","-ffp-contract=off",
                        *extra,"-I",str(src),str(STAGE/file),str(directory/"libgdcore.dll"),"-o",str(executable)],check=True)
        output=subprocess.check_output([str(executable)],text=True)
        (WORK/receipt).write_text(json.dumps({"passed":True,"dll_sha256":digest(dll),"output":output,
                                            "compiled_against_candidate_headers":True},indent=2)+"\n",encoding="utf8")
        print(output,flush=True)
    command=[sys.executable,'-u','-X','utf8',str(STAGE/'sim_native/tools/_cpp_verify_events.py'),
        '--case-ids',str(STAGE/'native_hot_path_target3/cases.json'),
        '--fights-root',str(STAGE/'native_hot_path_target3/fights'),
        '--align-root',str(STAGE/'native_hot_path_target3/align'),
        '--cases-json',str(STAGE/'native_hot_path_target3/fixtures.json'),
        '--strict-gem-origins','--strict-item-origins',
        '--original-dir',str(STAGE/'native_host_observed_base/base'),
        '--ring-placement-observations',str(STAGE/'native_controlled_prismatic_run948_placement'),
        '--native-only','--out',str(WORK/'sparse_timers_target'),'--dll',str(dll)]
    subprocess.run(command,check=True)
    result=json.loads((WORK/'sparse_timers_target/summary.json').read_bytes())
    assert result['passed']==result['total']==3

if __name__=='__main__':
    main()

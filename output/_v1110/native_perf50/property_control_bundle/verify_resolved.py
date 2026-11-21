"""Check the native event chain candidate before throughput trials."""
import psutil
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
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

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    dll=WORK/'bundle.dll'
    src=WORK/'bundle_src'
    baseline=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    before={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    with tempfile.TemporaryDirectory(prefix='native-snapshot-abi-') as temp:
        symbols={}
        for label,path in (('baseline',baseline),('candidate',dll)):
            copied=Path(temp)/(label+'.dll')
            shutil.copyfile(path,copied)
            assert digest(copied)==digest(path)
            text=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(copied)],text=True)
            symbols[label]=sorted({line.split()[-1] for line in text.splitlines() if line.split() and line.split()[-1].startswith('gd_sim_')})
        assert symbols['baseline']==symbols['candidate'] and len(symbols['baseline'])==22
    (WORK/'resolved_abi.json').write_text(json.dumps({'baseline_dll_sha256':digest(baseline),'candidate_dll_sha256':digest(dll),'unchanged_c_abi':symbols['candidate']},indent=2)+'\n',encoding='utf8')
    directory=Path(tempfile.mkdtemp(prefix="native-inline-timer-candidate-"))
    shutil.copyfile(dll,directory/"libgdcore.dll")
    (WORK/"inline_candidate_test_directory.txt").write_text(str(directory),encoding="utf8")
    layout_results={}
    for label,header,dll_path in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim',baseline),('candidate',src,dll)]:
        folder=directory/(label+'_layout');folder.mkdir();shutil.copyfile(dll_path,folder/'libgdcore.dll')
        executable=folder/'layout.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-DGD_ITEM_LOCALITY_LAYOUT_ONLY','-I',str(header),str(STAGE/'test_native_item_locality.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
        layout_results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    (WORK/'item_layout_offsets.json').write_text(json.dumps({'dll_sha256':digest(dll),'results':layout_results},indent=2)+'\n',encoding='utf8')
    print('Measured actual baseline/candidate base and derived layout sizes and offsets',flush=True)
    boundary_results={}
    for label,header,dll_path in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim',baseline),('candidate',src,dll)]:
        folder=directory/label;folder.mkdir();shutil.copyfile(dll_path,folder/'libgdcore.dll')
        executable=folder/'boundary.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-DGD_REVERSE_NAMES_CANDIDATE','-I',str(header),str(STAGE/'test_native_reverse_stack_names.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
        boundary_results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    assert boundary_results['baseline']==boundary_results['candidate'] and boundary_results['candidate']['lookup_cases']==401 and boundary_results['candidate']['constructors']==9
    (WORK/'resolved_boundary_test.json').write_text(json.dumps({'passed':True,'dll_sha256':digest(dll),'differential_results':boundary_results},indent=2)+'\n',encoding='utf8',newline='\n')
    print('401 enum lookup and 9 full constructor cases matched baseline',flush=True)
    buff_results={}
    for label,header,dll_path in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim',baseline),('candidate',src,dll)]:
        folder=directory/label
        executable=folder/'buff_chunks.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(header),str(STAGE/'test_native_buff_chunks.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
        buff_results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    assert buff_results['baseline']==buff_results['candidate'] and buff_results['candidate']['cases']==1624
    assert buff_results['candidate']['cooldown_flag_cases']==40
    (WORK/'buff_chunk_differential.json').write_text(json.dumps({'passed':True,'dll_sha256':digest(dll),'differential_results':buff_results},indent=2)+'\n',encoding='utf8')
    print('1624 Buff scan state/callback and40 cooldown-flag cases matched baseline',flush=True)
    trace_results={}
    for label,header in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim'),('candidate',src)]:
        folder=directory/label
        executable=folder/'addspeed_trace.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(header),str(STAGE/'test_native_addspeed_trace.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
        trace_results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    assert trace_results['baseline']==trace_results['candidate'],trace_results
    (WORK/'addspeed_trace_differential.json').write_text(json.dumps({'passed':True,'dll_sha256':digest(dll),'results':trace_results},indent=2)+'\n',encoding='utf8')
    print('AddSpeed diagnostic and fallback differential cases matched baseline',flush=True)
    tests=(("test_native_properties.cpp","property_test.json",["-I",str(WORK)]),
           ("test_native_item_locality.cpp","item_locality_test.json",["-DGD_HOT_CONTROL_CANDIDATE"]),
           ("test_native_eager_rows.cpp","eager_rows_test.json",[]),
           ("test_native_variant_inline.cpp","variant_inline_test.json",[]),
           ("test_native_inline_dispatch.cpp","inline_dispatch_test.json",[]),
           ("test_native_builtin_dispatch.cpp","builtin_dispatch_test.json",[]),
           ("test_native_scalar_array.cpp","scalar_array_test.json",[]),
           ("test_native_expanded_dispatch.cpp","expanded_dispatch_test.json",[]),
           ("test_native_array_index.cpp","array_index_test.json",[]),
           ("test_native_resolved_dispatch.cpp","resolved_callbacks_test.json",[]),
           ("test_native_arena_split.cpp","arena_stress_test.json",[]),
           ("test_native_dict_indices.cpp","dict_test.json",[]),
           ("test_native_label_ranges.cpp","labels_test.json",[]),
           ("test_native_event_kernel.cpp","native_event_kernel_callbacks.json",[]),
           ("test_native_integer_ranges.cpp","buff_rng_regression_test.json",[]),
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
    command=[sys.executable,'-u','-X','utf8',str(WORK/'audit_verify.py'),
        '--case-ids',str(STAGE/'native_hot_path_target3/cases.json'),
        '--fights-root',str(STAGE/'native_hot_path_target3/fights'),
        '--align-root',str(STAGE/'native_hot_path_target3/align'),
        '--cases-json',str(STAGE/'native_hot_path_target3/fixtures.json'),
        '--strict-gem-origins','--strict-item-origins',
        '--original-dir',str(STAGE/'native_host_observed_base/base'),
        '--ring-placement-observations',str(STAGE/'native_controlled_prismatic_run948_placement'),
        '--native-only','--out',str(WORK/'resolved_target'),'--dll',str(dll)]
    subprocess.run(command,check=True)
    result=json.loads((WORK/'resolved_target/summary.json').read_bytes())
    assert result['passed']==result['total']==3
    assert before=={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'resolved_verified_source.json').write_text(json.dumps({
        'dll_sha256':digest(dll),'source_unchanged_during_verification':True,
        'source_sha256':before},indent=2)+'\n',encoding='utf8',newline='\n')

if __name__=='__main__':
    main()

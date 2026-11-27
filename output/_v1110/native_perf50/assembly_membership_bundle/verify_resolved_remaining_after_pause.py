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
    dll=WORK/'bundle.dll';src=WORK/'bundle_src'
    before={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    directory=Path((WORK/'inline_candidate_test_directory.txt').read_text('utf8'))
    assert directory.is_dir() and digest(directory/'libgdcore.dll')==digest(dll)
    for name in ['resolved_abi.json','item_layout_offsets.json','resolved_boundary_test.json','buff_chunk_differential.json','addspeed_trace_differential.json']:
        r=json.loads((WORK/name).read_bytes());assert r.get('dll_sha256',r.get('candidate_dll_sha256'))==digest(dll)
    tests=(
           ("test_native_hot_coverage.cpp","hot_coverage_test.json",[]),
           ("test_native_type_constructor.cpp","type_constructor_test.json",["-I",str(WORK)]),
           ("test_native_properties.cpp","property_test.json",["-I",str(WORK)]),
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
        saved=WORK/receipt
        if saved.exists():
            r=json.loads(saved.read_bytes());assert r['passed'] and r['dll_sha256']==digest(dll) and r['compiled_against_candidate_headers']
            print('Retained completed '+receipt,flush=True);continue
        executable=directory/f"test_{number}.exe"
        test=STAGE/file
        if file=='test_native_arena_split.cpp':
            original=test.read_text('utf8');old='static_assert(sizeof(gd::GdArr)==24);';new='static_assert(sizeof(gd::GdArr)==32);'
            assert original.count(old)==1
            adapted=original.replace(old,new,1);test=directory/'arena_declared_layout32.cpp'
            test.write_text(adapted,encoding='utf8',newline='\n');assert adapted.replace(new,old,1)==original
            (WORK/'arena_layout_test_adaptation.json').write_text(json.dumps(dict(original_test_sha256=digest(STAGE/file),adapted_test_sha256=digest(test),only_change=[old,new],semantic_checks_removed=False),indent=2)+'\n',encoding='utf8')
        subprocess.run(["D:/mingw64/bin/g++.exe","-static","-O2","-std=c++20","-ffp-contract=off",
                        *extra,"-I",str(src),str(test),str(directory/"libgdcore.dll"),"-o",str(executable)],check=True)
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

if __name__=='__main__':main()

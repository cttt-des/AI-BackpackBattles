"""Resume the unfinished tests; adapt only the intentional array size assertion."""
import ast
import hashlib
import json
from pathlib import Path
import subprocess
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    dll=WORK/'bundle.dll';src=WORK/'bundle_src';actual=sha(dll)
    assert json.loads((WORK/'fresh_profile_source.json').read_bytes())['dll_sha256']==actual
    before=json.loads((WORK/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    abi=json.loads((WORK/'resolved_abi.json').read_bytes());assert abi['candidate_dll_sha256']==actual and len(abi['unchanged_c_abi'])==22
    directory=Path((WORK/'inline_candidate_test_directory.txt').read_text('utf8'))
    assert directory.name.startswith('native-inline-timer-candidate-') and sha(directory/'libgdcore.dll')==actual
    verification=(WORK/'verify_resolved.py').read_text('utf8');tree=ast.parse(verification)
    node=next(node for node in ast.walk(tree) if isinstance(node,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='tests' for t in node.targets))
    expression=ast.get_source_segment(verification,node.value).replace('str(WORK)',repr(str(WORK)))
    tests=ast.literal_eval(expression)
    retained=[];completed=[];started=False
    for number,(file,receipt,extra) in enumerate(tests):
        if file=='test_native_arena_split.cpp':started=True
        if not started:
            row=json.loads((WORK/receipt).read_bytes());assert row['passed'] and row['dll_sha256']==actual
            retained.append(receipt);continue
        assert not (WORK/receipt).exists(),receipt
        test=STAGE/file
        if file=='test_native_arena_split.cpp':
            text=test.read_text('utf8');old='static_assert(sizeof(gd::GdArr)==24);';new='static_assert(sizeof(gd::GdArr)==32);'
            assert text.count(old)==1
            adapted=text.replace(old,new,1);test=directory/'arena_declared_layout32.cpp';test.write_text(adapted,encoding='utf8',newline='\n')
            assert adapted.replace(new,old,1)==text
            (WORK/'arena_layout_test_adaptation.json').write_text(json.dumps(dict(original_test_sha256=sha(STAGE/file),adapted_test_sha256=sha(test),
                reason='GdArr24->32 is the declared layout change; every allocator, alignment, ownership, multithread and recursive construction check retained verbatim',
                only_change=[old,new],semantic_checks_removed=False),indent=2)+'\n',encoding='utf8')
        exe=directory/f'resumed_{number}.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',*extra,'-I',str(src),str(test),str(directory/'libgdcore.dll'),'-o',str(exe)],check=True)
        output=subprocess.check_output([str(exe)],text=True)
        (WORK/receipt).write_text(json.dumps(dict(passed=True,dll_sha256=actual,output=output,compiled_against_candidate_headers=True),indent=2)+'\n',encoding='utf8');print(output,flush=True)
        completed.append(receipt)
    assert started and len(retained)+len(completed)==len(tests)
    assert not (WORK/'resolved_target').exists()
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'audit_verify.py'),
        '--case-ids',str(STAGE/'native_hot_path_target3/cases.json'),'--fights-root',str(STAGE/'native_hot_path_target3/fights'),
        '--align-root',str(STAGE/'native_hot_path_target3/align'),'--cases-json',str(STAGE/'native_hot_path_target3/fixtures.json'),
        '--strict-gem-origins','--strict-item-origins','--original-dir',str(STAGE/'native_host_observed_base/base'),
        '--ring-placement-observations',str(STAGE/'native_controlled_prismatic_run948_placement'),'--native-only',
        '--out',str(WORK/'resolved_target'),'--dll',str(dll)],check=True)
    summary=json.loads((WORK/'resolved_target/summary.json').read_bytes());assert summary['passed']==summary['total']==3
    assert before=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'resolved_verified_source.json').write_text(json.dumps(dict(dll_sha256=actual,source_unchanged_during_verification=True,source_sha256=before),indent=2)+'\n',encoding='utf8')
    (WORK/'resolved_resume.json').write_text(json.dumps(dict(passed=True,dll_sha256=actual,retained_passed_tests=retained,newly_completed_tests=completed,
        adaptation_sha256=sha(WORK/'arena_layout_test_adaptation.json'),candidate_source_and_dll_unchanged=True),indent=2)+'\n',encoding='utf8')

if __name__=='__main__':main()

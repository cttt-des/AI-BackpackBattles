"""Preserve partial timer evidence and correct current-baseline verifier imports."""
import json
import shutil
from prepare_native_callback_dispatch import STAGE, BASE, EXPECTED, sha, once

WORK=STAGE/'native_perf50/callback_dispatch_bundle'

def main():
    assert not (WORK/'comparison.log').exists()
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert sha(WORK/'bundle.dll')=='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'
    saved=WORK/'preflight_harness_failure_2';assert not saved.exists();saved.mkdir()
    names=['verify_targeted_timers.py','verify_closed_registry_current.py','verify_integer_grid.py',
           'targeted_timer_tests_resumed_first.log','live_resumed_validation.json']
    for name in names:shutil.copyfile(WORK/name,saved/name)
    for name in ['resume_callback_dispatch_validation.py','setup_callback_dispatch_bundle.py']:
        shutil.copyfile(STAGE/name,saved/name)
    imports=['verify_closed_registry_current.py','verify_integer_grid.py']
    for name in imports:
        path=WORK/name;text=path.read_text('utf8')
        text=once(text,'from prepare_native_literal_spans import','from prepare_native_callback_dispatch import')
        path.write_text(text,encoding='utf8',newline='\n')
    path=STAGE/'setup_callback_dispatch_bundle.py';text=path.read_text('utf8')
    marker="        if path.name=='build_bundle.py':"
    text=once(text,marker,"        if path.name in ('verify_closed_registry_current.py','verify_integer_grid.py'):\n            text=text.replace('from prepare_native_literal_spans import','from prepare_native_callback_dispatch import')\n"+marker)
    path.write_text(text,encoding='utf8',newline='\n')
    partial=['targeted_timer_production_cases.json','targeted_timer_safety_production_cases.json','targeted_timer_ownership_production_cases.json']
    receipt=dict(dll_sha256=sha(WORK/'bundle.dll'),cases_sha256={n:sha(WORK/n) for n in partial},
        original_failure_files_sha256={p.name:sha(p) for p in saved.iterdir()},
        no_formal_timing_started=True,source707_and_dll_unchanged=True,
        reason='Current-production registry/grid checks imported the previous baseline; retained timer hashes had already matched')
    (WORK/'validation_harness_repair_2.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    path=WORK/'verify_targeted_timers.py';text=path.read_text('utf8')
    text=once(text,"    reports={};layouts=None", "    import sys\n    resume='--resume-checked-cases' in sys.argv\n    if resume:\n        retained=json.loads((WORK/'validation_harness_repair_2.json').read_bytes())\n        assert retained['dll_sha256']==sha(WORK/'bundle.dll')\n        assert all(sha(WORK/n)==h for n,h in retained['cases_sha256'].items())\n    reports={};layouts=None")
    begin=text.index("            subprocess.run(['D:/mingw64/bin/g++.exe'")
    end=text.index("            assert actual['cases']",begin)
    block=text[begin:end]
    replacement="            if resume:\n                raw=(WORK/output).read_text('utf8');actual=json.loads(raw)\n            else:\n"+''.join('    '+line+'\n' for line in block.splitlines())
    text=text[:begin]+replacement+text[end:]
    text=once(text,"            (WORK/output).write_text(raw,encoding='utf8')","            if not resume:(WORK/output).write_text(raw,encoding='utf8')")
    path.write_text(text,encoding='utf8',newline='\n')
    path=STAGE/'resume_callback_dispatch_validation.py';text=path.read_text('utf8')
    text=once(text,'    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)',"    continuation='--continue-harness-repair-2' in sys.argv\n    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)")
    text=once(text,"    assert not (WORK/'resume_validation_first.log').exists(),'Use the live process or existing result; never restart observed timings'", "    marker=WORK/('resume_validation_second.log' if continuation else 'resume_validation_first.log')\n    assert not marker.exists(),'Use the live process or existing result; never restart observed timings'\n    if continuation:\n        assert (WORK/'validation_harness_repair_2.json').exists()\n        previous=json.loads((WORK/'live_resumed_validation.json').read_bytes())\n        if psutil.pid_exists(previous['pid']):assert abs(psutil.Process(previous['pid']).create_time()-previous['created'])>=.001")
    text=once(text,"    (WORK/'resume_validation_first.log').write_text(","    marker.write_text(")
    text=once(text,"    run('verify_targeted_timers.py','targeted_timer_tests_resumed_first.log')", "    if continuation:run('verify_targeted_timers.py','targeted_timer_tests_resumed_second.log','--resume-checked-cases')\n    else:run('verify_targeted_timers.py','targeted_timer_tests_resumed_first.log')")
    path.write_text(text,encoding='utf8',newline='\n')
    additions=['repair_callback_validation_harness.py','repair_callback_validation_harness_2.py','resume_callback_dispatch_validation.py']
    for name in ('archive_callback_dispatch_round.py','setup_callback_dispatch_archive.py'):
        path=STAGE/name;text=path.read_text('utf8')
        text=once(text,"'analyze_native_dispatch.py')", "'analyze_native_dispatch.py',"+','.join(repr(n) for n in additions)+')')
        path.write_text(text,encoding='utf8',newline='\n')
    import ast
    for path in [WORK/n for n in imports]+[WORK/'verify_targeted_timers.py',STAGE/'resume_callback_dispatch_validation.py']:
        ast.parse(path.read_text('utf8'))
    print(json.dumps(receipt,indent=2))

if __name__=='__main__':main()

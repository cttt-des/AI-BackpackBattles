"""Prepare the next direct composition against the newly accepted 444e runtime."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/eager_trace_bundle'
WORK=STAGE/'native_perf50/item_locality_bundle'
BASE_SHA='444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc'
ARCHIVE='d4938c4e097d6c2b4ec971e544f9f18df3486e0a'

def main():
    WORK.mkdir()
    names=('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
           'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py',
           'run_comparison.py','assess_resolved.py','audit_verify.py')
    for name in names:
        text=(OLD/name).read_text('utf8').replace('eager_trace_bundle','item_locality_bundle')
        text=text.replace('native-eager-trace-','native-item-locality-')
        text=text.replace('7af5ff948b949859339f0897a6d857953ae8e3b30ec451cee030672ba9c5129b',BASE_SHA)
        if name=='build_bundle.py':
            text=text.replace("ARCHIVE='7da8b44d591caa4f65a7c1a177d1a81b0950dba0'",f"ARCHIVE='{ARCHIVE}'")
            text=text.replace('from prototype_native_item_locality_bundle import optimize',
                "from prototype_native_item_locality_bundle import optimize as _locality\n\ndef optimize(src):\n    expected=json.loads((STAGE/'native_perf50/eager_trace_bundle/source_before_build.json').read_bytes())\n    return _locality(src,expected)\n")
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'scan_bundle'","OLD=WORK.parent/'eager_trace_bundle'")
            text=text.replace("'native_perf50/scan_bundle'","'native_perf50/eager_trace_bundle'")
        if name=='verify_resolved.py':
            text=text.replace('    tests=(("test_native_eager_rows.cpp"',
                              '    tests=(("test_native_item_locality.cpp","item_locality_test.json",[]),\n           ("test_native_eager_rows.cpp"',1)
        ast.parse(text,filename=name)
        (WORK/name).write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE_SHA,verified_remote_backup=ARCHIVE,
        components=['adjacent timers/gems values and timer length','distinct one-use embedded post-setup gems header'],
        new_object_or_context_layout=True,formal_results='pending')
    plan['layout_scope']='CoreItem and derived layout changes; BattleCtx unchanged. Full20 instrumentation and fresh18 PGO mandatory.'
    plan['required_before_comparison'].insert(0,'43 capacity/alias/lifetime checks, base/derived sizeof/align and exact byte offsets')
    plan['source_note']='Correct preceding frozen guard comment about unspecified nested argument order; original expression and guard behavior unchanged'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    print(WORK)

if __name__=='__main__':main()

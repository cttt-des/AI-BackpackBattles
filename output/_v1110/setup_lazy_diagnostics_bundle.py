"""Declare one diagnostic composition with unchanged timing and truth gates."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/event_emission_bundle'
WORK=STAGE/'native_perf50/lazy_diagnostics_bundle'
BASE='b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588'
ARCHIVE='674fff4fdee8bcf5a408659750e3677a2b6790d6'
PRIOR='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
def main():
    assert not WORK.exists()
    WORK.mkdir()
    for p in OLD.glob('*.py'):
        text=p.read_text('utf8').replace('event_emission_bundle','lazy_diagnostics_bundle').replace('hot_coverage_bundle','event_emission_bundle')
        text=text.replace('native-event-emission-','native-lazy-diagnostics-').replace(PRIOR,BASE).replace('60963d0804db5dc01a5cace6d3fe56c658bfae13',ARCHIVE)
        if p.name=='resume_build.py':text=text.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_lazy_diagnostic_stat')\n    definition=objects/'instrumented_exports.def'")
        if p.name=='validate_then_compare.py':text=text.replace("    run('verify_resolved.py','verify.log')","    run('verify_lazy_diagnostics.py','lazy_diagnostics_tests.log')\n    run('verify_resolved.py','verify.log')")
        if p.name=='verify_installed.py':
            text=text.replace("'event_identity_tests.json','property_test.json'","'event_identity_tests.json','lazy_diagnostics_tests.json','property_test.json'")
        if p.name=='save_checkpoint.py':
            start=text.index('    paths.update(STAGE/p for p in (')
            end=text.index('    audit=json.loads',start)
            text=text[:start]+"    paths.update(STAGE/p for p in ('native_lazy_diagnostics.hpp','prepare_native_lazy_diagnostics.py','prepare_native_buff_diagnostics.py','test_native_lazy_diagnostics.cpp','test_native_buff_diagnostics.cpp','probe_native_lazy_diagnostics.py','probe_native_buff_diagnostics.py','snapshot_label_diagnostic_screen.py','prototype_native_lazy_diagnostics_bundle.py','setup_lazy_diagnostics_bundle.py'))\n    paths.update(p for p in (WORK.parent/'lazy_diagnostics_probe').iterdir() if p.is_file())\n"+text[end:]
            text=text.replace('perf: compose verified event identity and emission ID paths','perf: omit proven unobserved diagnostic formatting')
        ast.parse(text,filename=p.name)
        (WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    # Regeneration must extend the immediately deployed inventory, not itself.
    p=WORK/'prepare_regeneration.py';text=p.read_text('utf8')
    text=text.replace("OLD=WORK.parent/'event_emission_bundle'","OLD=WORK.parent/'event_emission_bundle'")
    p.write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,backup_commit=ARCHIVE,
        components=['skip one label diagnostic only for proven pure fields/primitive formatting','skip six Buff diagnostic arguments only when observationally empty'],
        no_auto_deployment=True)
    plan['required_before_comparison'].append('2048 original label cases and20736 isolated original Buff diagnostics with40036 pure-float flag checks; production path rechecked')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared one seven-site diagnostic composition; fixed200x4,3x8 AB/BA,2604 truth and24 raw batches unchanged')
if __name__=='__main__':main()

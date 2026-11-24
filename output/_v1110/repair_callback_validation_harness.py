"""Repair a stale pre-timing fingerprint; preserve the failed first attempt."""
import hashlib
import json
from pathlib import Path
import shutil
from prepare_native_callback_dispatch import STAGE,WORK as PROBE,EXPECTED,sha

WORK=STAGE/'native_perf50/callback_dispatch_bundle'

def main():
    assert not (WORK/'comparison.log').exists() and not (WORK/'ab_assessment.json').exists()
    dll=sha(WORK/'bundle.dll')
    assert dll=='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'
    manifest=json.loads((WORK/'source_before_build.json').read_bytes())
    assert manifest==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    assert manifest=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    profile=json.loads((WORK/'fresh_profile_source.json').read_bytes())
    assert profile['dll_sha256']==dll and profile['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    target=WORK/'preflight_harness_failure_1';assert not target.exists();target.mkdir()
    for p in [WORK/name for name in ('verify_targeted_timers.py','targeted_timer_tests.log','build_first.log','qualification_first.log','qualify_when_ready.py')]+[STAGE/'setup_callback_dispatch_bundle.py']:
        shutil.copyfile(p,target/p.name)
    wrapper=WORK/'verify_targeted_timers.py';text=wrapper.read_text('utf8')
    old="WORK.parent/'literal_spans_prototype/transform.json'";new="WORK.parent/'callback_dispatch_prototype/transform.json'"
    assert text.count(old)==1;text=text.replace(old,new,1)
    wrapper.write_text(text,encoding='utf8',newline='\n')
    setup=STAGE/'setup_callback_dispatch_bundle.py';text=setup.read_text('utf8')
    marker="        text=text.replace('literal_spans_bundle','callback_dispatch_bundle').replace('event_factory_bundle','literal_spans_bundle')"
    assert text.count(marker)==1;text=text.replace(marker,marker+"\n        text=text.replace('literal_spans_prototype','callback_dispatch_prototype')",1)
    setup.write_text(text,encoding='utf8',newline='\n')
    record=dict(reason='Copied timer verifier referenced the previous prototype fingerprint; assertion ran before any timer test',
        formal_dll_sha256=dll,formal_dll_and707_source_bytes_unchanged=True,
        source_manifest_sha256=sha(WORK/'source_before_build.json'),fresh18_profiles_retained=True,
        no_ab_or_release_measurement_had_started=True,do_not_rebuild_or_repeat_passed_checks=True,
        repaired_files={str(p.relative_to(STAGE)):sha(p) for p in (wrapper,setup)},
        original_failure_files_sha256={p.name:sha(p) for p in target.iterdir() if p.is_file()})
    (WORK/'validation_harness_repair.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
    print(json.dumps(record,indent=2))

if __name__=='__main__':main()

"""Freeze the ordered cooldown source after actual-DLL traversal and coverage checks."""
import json
from prepare_native_active_cooldowns import STAGE,BASE,WORK as PROBE,EXPECTED,sha,transform

def optimize(native):
    for name in ('differential.json','directed_coverage.json','fixed200_coverage.json'):
        record=json.loads((PROBE/name).read_bytes());assert record['passed']
    original=json.loads((PROBE/'transform.json').read_bytes())
    actual=transform(native)
    assert actual['source_sha256']==original['source_sha256']
    result=json.loads((STAGE/'native_perf50/closed_timer_bundle/transform.json').read_bytes())
    result.update(actual)
    result.update(components=['existing targeted structural watcher','separate cooldown eligibility version','ordered active item/gem entries','exact captured-array suffix recovery'],
        independent_actual_dll_cases=1856,open_and_sealed_timer_regressions_still_required=True,
        full_rebuild_required=True,array_header_remains_32=True,expected_BattleCtx_size=328,
        unknown_and_open_entry_original_phase_preserved=True,no_speed_claim=True)
    return result

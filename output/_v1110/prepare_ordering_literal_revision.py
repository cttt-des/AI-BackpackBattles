"""Preserve the incomplete first candidate and repair its cloned literal loop."""
import json,shutil
from prepare_ordering_correctness import REPO,WORK,ACCEPTED,sha,save,inventory,once,verify_projection

def main():
    old=WORK.with_name(WORK.name+'_revision1')
    assert WORK.resolve().is_relative_to(REPO.resolve()) and old.resolve().is_relative_to(REPO.resolve()) and not old.exists()
    WORK.rename(old);WORK.mkdir()
    for name in ('bundle_src','python_pending','maintenance_pending','maintenance_before'):shutil.copytree(old/name,WORK/name)
    inputs=('baseline_verified.json','user_boundary_before.json','maintenance_changes.json','retained_fixture_transform.json','retained_event_test_correction.json','timer_sort_original.json','targeted_timer_godot_reference.json','timer_sort_expectation_correction.json','sort_cases.json','activation_cases.json','python_compiled_ordering_tests.json','python_source_ordering_tests.json','python_fresh_battle_comparison.json','python_baseline_primitives.json','python_candidate_primitives.json','maintained_runtime_syntax.json')
    for p in old.iterdir():
        if p.is_file() and (p.suffix in ('.py','.cpp','.hpp','.gd') or p.name in inputs or p.name.startswith('original_') and p.suffix in ('.json','.log')):shutil.copyfile(p,WORK/p.name)
    shard=WORK/'bundle_src/gen/shards/shard_12.cpp';text=shard.read_text('utf8');start=text.index('gd::GdVal gd_native_emit_literal_body(');end=text.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(',start)
    a='for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {';b='for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {'
    body=once(text[start:end],a,b);shard.write_text(text[:start]+body+text[end:],encoding='utf8',newline='\n')
    transform=json.loads((old/'transform.json').read_bytes());transform['source_sha256']=inventory(WORK/'bundle_src');transform['all_three_dispatch_loops_corrected']=True
    save('transform.json',transform);save('source_before_build.json',transform['source_sha256']);verify_projection(WORK/'bundle_src')
    # Other semantics stay frozen, including the independent sort-side-effect oracle.
    save('revision1_preserved.json',dict(incomplete_candidate_directory=str(old.relative_to(REPO)),not_deployed=True,reason='Copied literal-argument fast path retained its own snapshot loop',previous_dll_sha256=sha(old/'bundle.dll'),previous_source_manifest_sha256=sha(old/'source_before_build.json'),all_previous_failures_and_receipts_preserved=True,extra_changed_source_only='gen/shards/shard_12.cpp'))
    print('Archived incomplete candidate; normal, generic and literal listener loops all corrected')
if __name__=='__main__':main()

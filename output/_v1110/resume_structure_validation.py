"""Audit the unchanged qualified bytes and preserve a pre-ready interruption."""
import json,subprocess
from datetime import datetime,timezone
from pathlib import Path
from prepare_structure_round import WORK,REPO,STAGE,BASE,EXPECTED,ARCHIVE,sha,save,inventory,verify_projection
from install_ordering_correctness import boundary
def main():
    boundary();verify_projection(WORK/'bundle_src')
    candidate=sha(WORK/'bundle.dll');assert candidate=='0e796c7fa00f6aef37b0afd605f313b0c7290b3b915119f334f92afe15c3bfb7'
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==sha(WORK/'baseline.dll')==EXPECTED
    assert inventory(BASE)==json.loads((WORK/'baseline_source.json').read_bytes())
    steps=json.loads((WORK/'qualification_steps.json').read_bytes())
    for name,row in steps.items():
        assert row['passed'] and row['dll_sha256']==candidate,name
        assert sha(WORK/row['log'])==row['log_sha256'],name
    # Directed suite scripts are bound to their retained receipt, except the
    # full-gate/finalization labels whose filenames differ from their label.
    from setup_frame_guard_checks import NAMES
    for name in NAMES[:NAMES.index('inspect_variant.py')]:
        assert sha(WORK/name)==steps[Path(name).stem]['script_sha256'],name
    gate=json.loads((WORK/'complete_correctness_gate.json').read_bytes());assert gate['passed'] and gate['dll_sha256']==candidate and gate['full_original_event_cases']==2604
    audit=json.loads((WORK/'full_type_audit.json').read_bytes());assert audit['fights']==2604 and audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    assert subprocess.check_output(['git','ls-remote','--exit-code','https://github.com/cttt-des/AI-BackpackBattles.git','refs/heads/codex/native-perf50-verified'],cwd=REPO,text=True,timeout=40).split()[0]==ARCHIVE
    assert not list(WORK.glob('ab_fixed_*.json')) and not (WORK/'ab_timing_complete.json').exists()
    old=json.loads((WORK/'formal_timing_inputs.json').read_bytes())
    assert old['candidate_dll_sha256']==candidate and all(sha(STAGE/n)==h for n,h in old['scripts_sha256'].items())
    log=WORK/'ab_fixed_1_A_worker.log';error=log.read_text('utf8')
    assert 'worker' in error and 'ready=True' in error and 'OSError: [Errno 22]' in error
    assert not (WORK/'ab_fixed_1_B_worker.log').exists()
    archive=WORK/'interrupted_before_ready_20261127';assert not archive.exists();archive.mkdir()
    moved={}
    for name in ('formal_timing_inputs.json','ab_fixed_1_A_worker.log','ab_fixed_1.log','comparison_first.log'):
        source=WORK/name;target=archive/name
        assert source.resolve().is_relative_to(WORK.resolve()) and target.resolve().is_relative_to(WORK.resolve())
        moved[name]=sha(source);source.rename(target);assert sha(target)==moved[name]
    result=dict(resumed_on_explicit_user_instruction=True,utc=datetime.now(timezone.utc).isoformat(),candidate_dll_sha256=candidate,baseline_dll_sha256=EXPECTED,completed_qualification_steps=len(steps),all_qualified_logs_and_directed_scripts_verified=True,full2604_original_event_and_counter_proof_reused_for_identical_bytes=True,
      prior_attempt_interrupted_at_first_ready_print=True,prior_warmup_or_formal_observations=0,previous_files_retained=moved,
      same_frozen24_quad_budget_seeds_metrics_and_acceptance=True,no_source_changes_or_rebuild=True,temporary_storage='D:/CodexNativeBuilds/work',cleanup_after_phase=True,no_new_branch=True)
    save('resume_verification.json',result);print(json.dumps(result,indent=2),flush=True)
if __name__=='__main__':main()

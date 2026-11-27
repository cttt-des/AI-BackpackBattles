"""Check the actual deployed result and uploaded backup before goal completion."""
import json
import hashlib
from pathlib import Path
import subprocess
from prepare_native_assembly_membership import STAGE,BASE,sha

WORK=STAGE/'native_perf50/assembly_membership_bundle'
REPO=STAGE.parents[1]

def main():
    def read(n):return json.loads((WORK/n).read_bytes())
    status=read('current_runtime_status.json');post=read('post_install_verification.json');backup=read('checkpoint_receipt.json')
    actual=sha(WORK/'bundle.dll')
    assert status['deployed'] and status['second_direction_deployment_complete']
    assert read('buff_integer_tests.json')['cases']==218400
    assert read('weapon_chain_tests.json')['cases']==136128 and read('assembly_membership_tests.json')['cases']==229376
    assert read('post_ab_directed_regressions.json')['weapon_chain_cases']==136128 and read('post_ab_directed_regressions.json')['assembly_membership_cases']==229376
    assert read('post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read('post_ab_directed_regressions.json')['buff_integer_method_cases']==14112
    assert status['all_protocol_processes_finished'] and status['no_new_branches']
    assert post['passed'] and post['dll_sha256']==actual and post['strict_event_cases']==2604 and post['training_cases']==12
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==actual
    assert backup['remote_upload_verified'] and backup['candidate_installed'] and backup['production_dll_sha256']==actual
    assert backup['no_new_branches'] and backup['workspace_head_and_index_unchanged'] and backup['no_local_refs_updated']
    ref=backup['remote_existing_ref'];commit=backup['remote_verified_commit']
    remote=subprocess.check_output(['git','ls-remote','--exit-code','https://github.com/cttt-des/AI-BackpackBattles.git',ref],cwd=REPO,text=True,timeout=30).split()[0]
    assert remote==commit
    inventory=read('checkpoint_inventory.json')
    for relative,digest in inventory.items():
        if relative.startswith('docs/') and relative in read('archive_document_overlays.json'):continue
        assert sha(REPO/relative)==digest,relative
    for relative,digest in read('source_before_build.json').items():assert sha(BASE/relative)==digest
    assert read('pre_install_review.json')['passed'] and read('measurements_summary.json')['raw24_gate_passed']
    boundary=read('user_boundary_before.json')
    assert all(sha(REPO/n)==h for n,h in boundary['protected'].items())
    assert backup['workspace_state']['head']==boundary['head']
    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==boundary['staged_entries_sha256']
    fit=read('bundle_load20.json');norm=read('normalized20_sample_summary.json')
    assert fit['dll_sha256']==norm['dll_sha256']==actual
    assert fit['reference_load_pct']==20 and fit['fitted_fights_per_second_at_reference_load']==status['candidate_load20_fps']
    report=dict(passed=True,production_dll_sha256=actual,empirical20_fps=status['candidate_load20_fps'],
        normalized_median=norm['median'],normalized_minimum=norm['minimum'],normalized_maximum=norm['maximum'],
        empirical20_is_extrapolation=fit['reference_is_extrapolation'],remote_verified_commit=commit,
        original_2604_events_verified=True,fixed200_24_batches_verified=True,training_cases=12,
        no_valid_optimization_rejected_for20_coverage=True,no_new_branches=True,second_direction_complete=True,three_direction_goal_remains_active=False,three_direction_goal_paused=True,next_work='Original-source same-frame event and potion ordering audit')
    out=WORK/'second_direction_completion_receipt.json';assert not out.exists();out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()

"""Apply the explicit user policy correction to an already-qualified candidate."""
import ast
import json
from pathlib import Path
import shutil
from prepare_native_display_storage import STAGE,WORK as PROBE,sha,once

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/display_storage_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
AUTH='Explicit user clarification2026-11-26: estimate at20% with the empirical formula; coverage is not a deployment gate'
MARKER='2026-11-26 负载换算规则更正'
DOCS=('C++模拟器优化交接_2026-11-23.md','C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md')

def read(p):return json.loads(p.read_bytes())
def write(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf8')

def main():
    audit=read(AUDIT/'audit.json');assert audit['passed']
    entry=next(r for r in audit['omitted_valid_candidates'] if r['candidate']=='display_storage_bundle')
    actual=sha(WORK/'bundle.dll');assert entry['dll_sha256']==actual
    fit=read(AUDIT/'display_storage_bundle_empirical20.json');assert fit['dll_sha256']==actual
    target=WORK/'bundle_load20.json';assert not target.exists();shutil.copyfile(AUDIT/'display_storage_bundle_empirical20.json',target)
    policy=WORK/'user_load20_policy_20261126.json';assert not policy.exists()
    sources={n:sha(WORK/n) for n in ('bundle_serial.json','bundle_load_calibration.json','ab_assessment_32.json','bundle_full_gate.json','bundle_vs_deployed_hashes.json')}
    write(policy,dict(authorization=AUTH,empirical_estimate_allowed_outside_observed_range=True,
        candidate_dll_sha256=actual,original_measurement_files_sha256=sources,
        audit_sha256=sha(AUDIT/'audit.json'),fit_sha256=sha(target),
        no_new_battles=True,no_samples_dropped_or_retimed=True,
        retain_original_AB_correctness_power_and_raw24_thresholds=True,
        remove_idle_window_used_only_to_seek20pct_coverage=True))
    summary=WORK/'measurements_summary.json';old=WORK/'measurements_summary_before_policy_20261126.json'
    assert not old.exists();shutil.copyfile(summary,old);d=read(summary)
    d.update(fitted_fights_per_second_at20=fit['fitted_fights_per_second_at_reference_load'],
        r_squared_log_wall_time=fit['r_squared_log_wall_time'],fit_validation=fit['validation'],
        report_sha256={n:sha(WORK/n) for n in ('bundle_serial.json','bundle_load_calibration.json','bundle_load20.json')},
        single_run_all_samples_retained=True,load20_covered=False,empirical20_is_extrapolation=True,
        user_policy_authorization=AUTH,coverage_is_not_a_deployment_gate=True)
    assert d['raw24_gate_passed'];write(summary,d)
    originals=WORK/'policy_original_verifiers_20261126';assert not originals.exists();originals.mkdir()
    policy_check="    policy=json.loads((WORK/'user_load20_policy_20261126.json').read_bytes())\n    assert policy['empirical_estimate_allowed_outside_observed_range'] and policy['candidate_dll_sha256']==actual\n"
    rows=[]
    for p,needle,replacement in [
        (WORK/'install_verified.py',"    assert fit['minimum_load_pct'] <= 20 <= fit['maximum_load_pct']",
            policy_check+"    assert fit['reference_is_extrapolation']==(not fit['minimum_load_pct']<=20<=fit['maximum_load_pct'])"),
        (WORK/'verify_installed.py',"    assert min(xs)<=20<=max(xs),'Reference load must be covered by actual observations'",
            policy_check+"    assert fit['reference_is_extrapolation']==(not min(xs)<=20<=max(xs))"),
        (STAGE/'review_display_storage_release.py',"    assert min(xs)<=20<=max(xs)",
            policy_check+"    assert fit['reference_is_extrapolation']==(not min(xs)<=20<=max(xs))"),
    ]:
        before=sha(p);saved=originals/p.name;shutil.copyfile(p,saved)
        text=once(p.read_text('utf8'),needle,replacement);ast.parse(text);p.write_text(text,encoding='utf8',newline='\n')
        rows.append(dict(path=p.relative_to(REPO).as_posix(),original_sha256=before,updated_sha256=sha(p),
            original_snapshot=saved.relative_to(REPO).as_posix(),only_coverage_assertion_replaced=True))
    write(WORK/'user_policy_verifier_adaptations.json',dict(authorization=AUTH,adaptations=rows,all_other_acceptance_assertions_retained=True))
    note=f'''\n\n## {MARKER}\n\n用户明确澄清：应按经验公式把已知负载下的速度换算到20%，不因实测区间不覆盖20%而弃用有效优化。此前把覆盖范围作为部署门槛是代理的误读，该限制现已撤销；原始记录保留作历史，新规则以此段和user_load20_policy_20261126.json为准。为执行此澄清，后续也不再等待仅为覆盖20%设置的CPU≤12%窗口。固定200场单线程A/B、2604逐事件、原始24批每批≥50、供电／终局／原hash等条件保留。\n\n沿用原经验模型log(单批墙钟秒数)=a+b×负载百分比，fps20=fps_observed×exp(b×(load−20))。现用原首次cal24直接导出显示数组候选20%估计{entry['empirical20_fps']:.6f}场/秒，属于外推；观测范围、交叉验证误差和全部原样本保留，没有重做战斗或标定。70组历史决策复核另发现private_snapshots_bundle也仅被覆盖规则挡住，下一步合入最新基线组合验证。代码收益看配对A/B，不看不同环境历史估计值的差。\n'''
    banner=f'> **{MARKER}（用户澄清）**：20%速度使用经验公式估算；观测区间覆盖20%及其低负载等待不再是部署门槛。原A/B、逐事件与首raw24门槛保留。详见文末复核记录。\n\n'
    overlays=read(WORK/'archive_document_overlays.json')
    for name in DOCS:
        relative='docs/'+name;current=REPO/relative;snapshot=REPO/overlays[relative]['snapshot']
        for p in (current,snapshot):
            text=p.read_text('utf8');assert MARKER not in text;lines=text.splitlines(keepends=True)
            lines.insert(2,banner);p.write_text(''.join(lines)+note,encoding='utf8',newline='\n')
        overlays[relative]['sha256']=sha(snapshot);overlays[relative]['user_policy_correction_added']=True
    write(WORK/'archive_document_overlays.json',overlays)
    for p in [REPO/'docs/C++模拟器显示数组存储优化记录_2026-11-24.md']:
        text=p.read_text('utf8');assert MARKER not in text;p.write_text(text+note,encoding='utf8')
    assert sources=={n:sha(WORK/n) for n in sources}
    print(json.dumps(dict(prepared=True,dll_sha256=actual,empirical20_fps=entry['empirical20_fps'],
        extrapolation=True,original_measured_files_unchanged=True,all_other_gates_retained=True),ensure_ascii=False,indent=2))

if __name__=='__main__':main()

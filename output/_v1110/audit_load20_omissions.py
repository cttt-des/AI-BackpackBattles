"""Reassess saved trials under the user's empirical-normalization clarification."""
import hashlib
import json
from pathlib import Path
import statistics
import subprocess
import sys

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
ROOT=STAGE/'native_perf50'
WORK=ROOT/'load20_recovery_20261126'
INPUT='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
RESULT='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
EVENT='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(p):return json.loads(p.read_bytes())
def save(name,data):(WORK/name).write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
def summary(d):
    rows=d['samples'];values=[r['fights_per_second'] for r in rows]
    assert len(rows)==d['repeat']==24 and d['workers']==1 and d['fights']==200
    assert d['inputs_sha256']==INPUT and d['results_sha256']==RESULT
    assert all(r['matched_original_terminal']==200 and r['on_ac_before'] is True and r['on_ac_after'] is True for r in rows)
    return dict(median=statistics.median(values),minimum=min(values),maximum=max(values),
        observed_load_range=[min(r['background_load_pct'] for r in rows),max(r['background_load_pct'] for r in rows)])

def eligible(w):
    decision=read(w/'candidate_decision.json');failure=read(w/'release_gate_failure.json')
    assert decision['status']=='positive_combined_evidence' and failure['load20_covered'] is False and failure['raw24_gate_passed']
    actual=sha(w/'bundle.dll');assert actual==decision['candidate_dll_sha256']==failure['candidate_dll_sha256']
    assessment=Path(decision['selected_assessment']);assert sha(assessment)==decision['assessment_sha256']
    ab=read(assessment);assert ab['candidate_dll_sha256']==actual and ab['on_ac_all']
    assert all(v['paired_median_time_reduction_pct']>0 and v['pairs']==32 for v in ab['metrics'].values())
    assert len(ab['reports'])==4
    for report in ab['reports']:
        p=Path(report['path']);assert sha(p)==report['sha256'];raw=read(p)
        assert raw['trial_batch_repetitions']==4 and len(raw['pairs'])==8
        for pair in raw['pairs']:
            for label in ('baseline','candidate'):
                arm=pair[label];assert arm['observed_fights']==800 and len(arm['raw_batches'])==4
                assert all(row['matched_original_terminal']==200 and row['results_sha256']==RESULT for row in arm['raw_batches'])
    gate=read(w/'bundle_full_gate.json');assert gate['complete'] and gate['dll_sha256']==actual
    for name,count in [('base',914),('expand',1690)]:
        row=gate['cohorts'][name]
        assert row['expected']==row['recorded']==row['verified']==row['passed']==count and row['winner_mismatch']==0 and not row['pending']
    events=read(w/'bundle_vs_deployed_hashes.json');assert events['unchanged_cpp_event_streams']==2604 and events['candidate_dll_sha256']==actual
    assert events['ordered_case_and_cpp_event_hashes_sha256']==EVENT
    audit=read(w/'full_type_audit.json');assert audit['fights']==2604 and audit['coverage']==dict(generic_hits=146278076,funcref_hits=2143020,lazy_resolutions=952008,unsupported_types=2601,audit_mismatch=0,selected_fallback=4123200)
    assert audit['old_event_kernel_type_mismatches']==0 and read(w/'post_ab_directed_regressions.json')['passed']
    serial=summary(read(w/'bundle_serial.json'));calibration=summary(read(w/'bundle_load_calibration.json'))
    assert serial['minimum']>=50
    assert not (w/'post_install_verification.json').exists()
    out=WORK/(w.name+'_empirical20.json')
    if not out.exists():subprocess.run([sys.executable,'-X','utf8',str(STAGE/'fit_native_serial_load.py'),str(w/'bundle_load_calibration.json'),'--reference-load','20','--allow-extrapolation','--out',str(out)],stdout=subprocess.DEVNULL,check=True)
    fit=read(out);assert fit['dll_sha256']==actual and fit['reference_is_extrapolation']
    return dict(candidate=w.name,dll_sha256=actual,omission_reason='Only observed-load coverage blocked deployment',
        original_decision_sha256=sha(w/'candidate_decision.json'),original_failure_sha256=sha(w/'release_gate_failure.json'),
        original32_pair_metrics=ab['metrics'],strict_event_cases=2604,raw24=serial,calibration24=calibration,
        empirical20_fps=fit['fitted_fights_per_second_at_reference_load'],reference_is_extrapolation=True,
        fit_validation=fit['validation'],r_squared=fit['r_squared_log_wall_time'],fit_path=out.relative_to(REPO).as_posix(),
        fit_sha256=sha(out),original_measurements_unchanged=True,no_new_battles=True,
        recovery='Deploy exact qualified display candidate; merge private snapshots into latest source and qualify the combination')

def main():
    WORK.mkdir(exist_ok=True)
    records=[];omitted=[];installed=set()
    for w in sorted(p for p in ROOT.iterdir() if p.is_dir() and p!=WORK):
        for p in w.glob('*installation.json'):
            if p.stat().st_size>2000000:continue
            d=read(p)
            if d.get('deployed') is False or 'rejected' in p.name:continue
            if d.get('dll_sha256'):installed.add(d['dll_sha256'])
        p=w/'post_install_verification.json'
        if p.exists():
            d=read(p)
            if d.get('passed') and d.get('dll_sha256'):installed.add(d['dll_sha256'])
    for w in sorted(p for p in ROOT.iterdir() if p.is_dir() and p!=WORK):
        decisions=[]
        for p in sorted(w.glob('*.json')):
            if not any(key in p.name for key in ('decision','installation','rejection_receipt','release_gate_failure')) or p.stat().st_size>2000000:continue
            d=read(p)
            if not isinstance(d,dict):continue
            row={k:d[k] for k in ('status','reason','deployed','dll_sha256','candidate_dll_sha256','raw24_gate_passed','load20_covered') if k in d}
            if row:decisions.append(dict(file=p.relative_to(REPO).as_posix(),sha256=sha(p),data=row))
        if decisions:records.append(dict(directory=w.name,decisions=decisions))
        p=w/'release_gate_failure.json'
        if p.exists() and read(p).get('load20_covered') is False and read(p).get('raw24_gate_passed') and (w/'candidate_decision.json').exists():
            if read(w/'candidate_decision.json').get('status')=='positive_combined_evidence':omitted.append(eligible(w))
    assert {r['candidate'] for r in omitted}=={'display_storage_bundle','private_snapshots_bundle'}
    for row in omitted:assert row['dll_sha256'] not in installed
    # Existing interpolations must remain numerically identical under the new default.
    old=ROOT/'control_word_bundle/bundle_load20.json';out=WORK/'control_word_compatibility20.json'
    if not out.exists():subprocess.run([sys.executable,'-X','utf8',str(STAGE/'fit_native_serial_load.py'),str(ROOT/'control_word_bundle/bundle_load_calibration.json'),'--reference-load','20','--out',str(out)],stdout=subprocess.DEVNULL,check=True)
    a,b=read(old),read(out)
    for name in a:assert a[name]==b[name],name
    strict=WORK/'strict_mode_should_not_exist.json';assert not strict.exists()
    result=subprocess.run([sys.executable,'-X','utf8',str(STAGE/'fit_native_serial_load.py'),str(ROOT/'display_storage_bundle/bundle_load_calibration.json'),'--reference-load','20','--require-observed-range','--out',str(strict)],capture_output=True)
    assert result.returncode==2 and not strict.exists()
    (WORK/'historical_strict_mode.log').write_bytes(result.stdout+result.stderr)
    save('audit.json',dict(passed=True,policy_source='User clarification2026-11-26: empirical load normalization, coverage is not a deployment gate',
        reviewed_decision_directories=len(records),historical_decisions=records,omitted_valid_candidates=omitted,
        existing_interpolation_numerically_unchanged=True,historical_strict_mode_reproducible=True,
        original_measured_files_not_changed=True,code_gain_uses_paired_AB_not_historical_rate_differences=True))
    note='# 负载换算与遗漏优化复核（2026-11-26）\n\n用户澄清：使用经验公式把已知负载下的吞吐换算到20%；实测区间不覆盖20%不再阻止部署。沿用log(单批墙钟秒数)=a+b×后台负载百分比，单批归一化速度=fps×exp(b×(原负载−20))。保留全部原始样本，明确标注外推、负载范围与交叉验证误差；代码收益仍由原固定200场A/B判断。\n\n'
    for row in omitted:
        metrics=row['original32_pair_metrics'];note+=f"- {row['candidate']}：CPU／墙钟耗时中位降幅{metrics['main_thread_cpu_s']['paired_median_time_reduction_pct']:.4f}%／{metrics['wall_s']['paired_median_time_reduction_pct']:.4f}%；2604逐事件通过；首raw24最低{row['raw24']['minimum']:.4f}；20%经验估计{row['empirical20_fps']:.4f}场/秒（外推）。\n"
    note+='\n确认为负载覆盖条件单独挡住的候选只有以上两项。其他记录中的性能退步、收益未确认或首raw24未过50门槛，不因这次负载规则更正而自动恢复；已部署或后续组合采纳的记录也不重复补入。原审计与未部署记录保持原样，新复核作为补充。\n'
    (WORK/'audit.md').write_text(note,encoding='utf8')
    print(json.dumps(dict(passed=True,reviewed_decision_directories=len(records),omissions=[{k:r[k] for k in ('candidate','empirical20_fps','strict_event_cases')} for r in omitted]),ensure_ascii=False,indent=2))

if __name__=='__main__':main()

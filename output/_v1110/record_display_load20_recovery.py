"""Record the qualified deployment without rewriting its original rejection history."""
import json
from pathlib import Path
import statistics
from prepare_native_display_storage import STAGE,BASE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/display_storage_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
MARKER='## 2026-11-26 显示数组遗漏优化已恢复部署'

def read(p):return json.loads(p.read_bytes())
def write(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
def amend(text,note,headline):
    assert MARKER not in text;lines=text.splitlines(keepends=True)
    matches=[i for i,l in enumerate(lines[:10]) if l.startswith('> **当前生产') or ('日期：' in l and '当前已验收部署' in l)]
    if matches:lines[matches[0]]=headline+'\n'
    else:lines.insert(4,headline+'\n\n')
    return ''.join(lines)+note

def main():
    check=read(WORK/'post_install_verification.json');actual=sha(WORK/'bundle.dll')
    assert check['passed'] and check['dll_sha256']==sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==actual
    assert check['strict_event_cases']==2604 and check['training_cases']==12
    assert read(WORK/'bundle_installation.json')['training_matched_baseline']==12
    fit=read(WORK/'bundle_load20.json');assert fit['dll_sha256']==actual and fit['reference_is_extrapolation']
    before=WORK/'current_runtime_status_before_policy_20261126.json';assert not before.exists()
    current=WORK/'current_runtime_status.json';old=read(current);current.rename(before)
    old.update(deployed=True,production_dll_sha256=actual,reason='deployed_after_explicit_user_empirical_load_policy_correction',
        candidate_load20_fps=fit['fitted_fights_per_second_at_reference_load'],empirical20_is_extrapolation=True,
        goal200_reached=check['goal200_reached'],goal_still_active=True,
        policy_receipt='user_load20_policy_20261126.json',post_install_verification_sha256=sha(WORK/'post_install_verification.json'),
        original_gate_failure_preserved=True,backup_status_recorded_separately=True)
    write(current,old)
    values=fit['estimated_fights_per_second_at_reference_load_by_sample']
    normalized=dict(dll_sha256=actual,no_additional_timing=True,interpretation='Empirically normalized estimates from original24 samples; not direct20% observations',
        median=statistics.median(values),minimum=min(values),maximum=max(values),global_fitted_point=fit['fitted_fights_per_second_at_reference_load'],extrapolation=True)
    p=WORK/'normalized20_sample_summary.json';assert not p.exists();write(p,normalized)
    point=old['candidate_load20_fps']
    headline=f'> **当前生产{actual[:8]}，显示数组优化已恢复部署；20%经验估计{point:.4f}场/秒（外推）。规则已按用户澄清更正，继续恢复快照优化并推进200目标。**'
    note=f'''\n\n{MARKER}\n\n按用户明确要求撤销负载区间覆盖门槛后，重新检查原32对A/B、全部定向回归、2604逐事件／当前生产事件哈希、首次raw24、原始独立cal24、707源文件再生成及18PGO证据，均保留原数据。正常训练12样例在旧版、待切换版本和切换后完全一致，部署后完整证据核验通过。生产DLL现为`{actual}`，旧680运行时保存在`dist/native_1_1_10_before_display_storage_bundle_20261124`。仅更改覆盖条件相关断言；首个部署后核验因辅助模块搜索路径失败，首日志与脚本快照保留，补齐路径后通过，未重做任何正式计时。\n\n本轮20%经验估计{point:.6f}场/秒（外推；原cal24负载26.8985%–78.3709%），拟合R²={fit['r_squared_log_wall_time']:.6f}、分组交叉验证中位相对耗时误差={100*fit['validation']['median_absolute_relative_time_error']:.4f}%。按原24样本逐批归一化后的估计中位／最小／最大={normalized['median']:.6f}／{normalized['minimum']:.6f}／{normalized['maximum']:.6f}，这些不是直接20%实测。代码收益仍为原A/B CPU／墙钟耗时中位降低2.5214%／2.6597%，不能用不同环境下的历史20%点差值代替A/B。\n\n70组历史决策复核确认另一个仅因覆盖规则搁置的候选为private_snapshots_bundle；由于它基于F950，下一步合入当前显示数组／control word基线后完整验证，避免覆盖新版优化。200目标仍未完成，远端归档须另读checkpoint_receipt.json。原release_gate_failure.json和旧current_runtime_status均保留，新终态以本节、当前状态文件及post_install_verification.json为准。\n'''
    overlays=read(WORK/'archive_document_overlays.json')
    for name,row in overlays.items():
        current_doc=REPO/name;snapshot=REPO/row['snapshot']
        for p in (current_doc,snapshot):p.write_text(amend(p.read_text('utf8'),note,headline),encoding='utf8',newline='\n')
        row['sha256']=sha(snapshot);row['recovered_deployment_record_added']=True
    write(WORK/'archive_document_overlays.json',overlays)
    trial=REPO/'docs/C++模拟器显示数组存储优化记录_2026-11-24.md';trial.write_text(trial.read_text('utf8')+note,encoding='utf8')
    own=REPO/'docs/C++模拟器负载换算与遗漏优化复核_2026-11-26.md';assert not own.exists();own.write_text((AUDIT/'audit.md').read_text('utf8')+note,encoding='utf8')
    write(AUDIT/'recovery_progress.json',dict(display_storage=dict(deployed=True,dll_sha256=actual,empirical20_fps=point,
        verification_sha256=sha(WORK/'post_install_verification.json')),private_snapshots=dict(status='pending_merge_into_current_deployed_baseline'),goal200_reached=False))
    print(json.dumps(dict(deployed=True,dll_sha256=actual,empirical20_fps=point,normalized_samples=normalized,goal_still_active=True),ensure_ascii=False,indent=2))

if __name__=='__main__':main()

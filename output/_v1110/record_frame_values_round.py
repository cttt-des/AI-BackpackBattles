"""Record the distinct scalar-truth/private-snapshot combination honestly."""
import json
from pathlib import Path
import statistics
import subprocess
import psutil
from prepare_native_frame_values import STAGE,BASE,WORK as PROBE,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/frame_value_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
MARKER='## 逐帧值处理组合终态（2026-11-26）'
DOCS=('C++模拟器优化交接_2026-11-23.md','C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md')

def read(p):return json.loads(p.read_bytes())
def write(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
def terminal():
    rows=list(read(WORK/'live_formal_driver.json').values())
    if (WORK/'live_close_calibration.json').exists():rows.append(read(WORK/'live_close_calibration.json'))
    for row in rows:
        try:
            p=psutil.Process(row['pid']);assert p.create_time()!=row['created'] or not p.is_running(),'Protocol process still running'
        except psutil.NoSuchProcess:pass
def describe(p):
    d=read(p);rows=d['samples'];values=[r['fights_per_second'] for r in rows]
    assert d['workers']==1 and d['fights']==200 and len(rows)==d['repeat']==24
    assert d['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert d['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert all(r['matched_original_terminal']==200 for r in rows)
    return dict(median=statistics.median(values),minimum=min(values),maximum=max(values),
        observed_load_range=[min(r['background_load_pct'] for r in rows),max(r['background_load_pct'] for r in rows)],
        on_ac_all=all(r['on_ac_before'] is True and r['on_ac_after'] is True for r in rows))
def document(text,note,headline):
    assert MARKER not in text
    if headline:
        lines=text.splitlines(keepends=True);matches=[i for i,l in enumerate(lines[:10]) if l.startswith('> **当前生产')]
        if matches:lines[matches[0]]=headline+'\n'
        else:lines.insert(4,headline+'\n\n')
        text=''.join(lines)
    return text+note

def main():
    terminal();decision=read(WORK/'candidate_decision.json');actual=sha(WORK/'bundle.dll')
    assert decision['candidate_dll_sha256']==actual and sha(Path(decision['selected_assessment']))==decision['assessment_sha256']
    ab=read(Path(decision['selected_assessment']));assert ab['baseline_dll_sha256']==EXPECTED and ab['candidate_dll_sha256']==actual
    for name,cases in [('private_snapshots_tests.json',234880),('display_storage_tests.json',21888),('control_word_tests.json',44608),('scalar_truth_tests.json',34400)]:
        r=read(WORK/name);assert r['passed'] and r['cases']==cases and r['dll_sha256']==actual
    deployed=(WORK/'post_install_verification.json').exists();raw=None
    if (WORK/'bundle_load_calibration.json').exists():
        cal=describe(WORK/'bundle_load_calibration.json');raw=describe(WORK/'bundle_serial.json');fit=read(WORK/'bundle_load20.json')
    else:
        r=read(WORK/'rejection_receipt.json');assert r['not_deployed'] and decision['status']!='positive_combined_evidence'
        cal=describe(WORK/'rejected_load_calibration.json');fit=read(WORK/'rejected_load20.json')
    point=fit['fitted_fights_per_second_at_reference_load'];production=actual if deployed else EXPECTED
    assert fit['dll_sha256']==actual and fit['reference_load_pct']==20
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==production
    if deployed:
        check=read(WORK/'post_install_verification.json')
        assert check['passed'] and check['dll_sha256']==actual and check['strict_event_cases']==2604 and check['training_cases']==12
        assert check['production_source_files']==708 and raw['minimum']>=50 and raw['on_ac_all'] and cal['on_ac_all']
        assert read(WORK/'post_ab_directed_regressions.json')['scalar_truth_cases']==34400
        reason='frame_values_deployed_retaining_all_prior_components'
    elif decision['status']=='positive_combined_evidence':
        assert raw and (raw['minimum']<50 or not raw['on_ac_all'] or not cal['on_ac_all']),'Valid candidate still requires deployment review'
        reason='real_release_gate_failed_not_load_coverage'
    else:reason='distinct_combination_AB_not_accepted'
    values=fit['estimated_fights_per_second_at_reference_load_by_sample']
    norm=dict(no_additional_timing=True,dll_sha256=actual,median=statistics.median(values),minimum=min(values),maximum=max(values),
        global_fitted_point=point,extrapolation=fit['reference_is_extrapolation'],interpretation='Fit-derived estimates, not direct20% observations')
    write(WORK/'normalized20_sample_summary.json',norm)
    status=dict(candidate_dll_sha256=actual,production_dll_sha256=production,deployed=deployed,reason=reason,
        candidate_load20_fps=point,empirical20_is_extrapolation=fit['reference_is_extrapolation'],raw24=raw,calibration24=cal,
        goal200_reached=bool(deployed and point>=200),goal_still_active=True,current_display_and_control_components_retained=True,
        restored_private_snapshot_cases=234880,scalar_truth_cases=34400,all_protocol_processes_finished=True,
        no_more_same_configuration_measurements=True,no_new_branches=True,backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    assert not (WORK/'current_runtime_status.json').exists();write(WORK/'current_runtime_status.json',status)
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''\n\n{MARKER}\n\n候选`{actual}`，生产`{production}`，部署={deployed}，原因={reason}。基于已部署63D，仅改native_inline_dispatch.hpp的native_frame_segment_tick：4处真假判断使用原先已验收的通用标量短路径；Null显示覆盖不复制无用载荷，非Null仍在原观察时点保留完整值快照。保留全部私有视图／身份快照、生成方法标量真假判断、显示数组内联存储及control word；原浮点逐次运算、RNG、帧和回调顺序不变。严格逆变换逐字还原一份原头文件，其他712份目录文件、708份C++清单及674对象头／GdVal24／GdArr32／CoreItem2112／BattleCtx328／watch64布局保持；原型完整20普通对象仅作语义验证，正式仍完整20插桩／新18PGO。原型保留的registry检查最初仍绑定旧5DDB基线，在正式测速前改为实际63D基线；旧日志／脚本保留，原DLL和源码未改动，全部状态／计数／registry断言保持。原型及正式版保留34,400标量边界、234880私有、21888显示、44608控制／计时器／帧检查及固定200原结果／终局和原计数。\n\n完整{cpu['pairs']}对CPU／墙钟耗时配对中位降低{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，累计降低{cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。全部原始样本和极值保留。raw24={json.dumps(raw,ensure_ascii=False)}；独立cal24={json.dumps(cal,ensure_ascii=False)}；20%经验点／逐批换算中位／最低／最高={point}／{norm['median']}／{norm['minimum']}／{norm['maximum']}场/秒，外推={fit['reference_is_extrapolation']}。20%覆盖和空闲窗口不是门槛，代码收益仍由配对A/B判定，跨环境点估计不充当代码收益。A/B未接受时校准仅作非发布报告，不能冒充raw24或2604验收。\n\n已部署时完整2604逐事件、正常训练12例、实际运行时与源码以post_install_verification.json确认。目标200达到={status['goal200_reached']}，目标最终完成须另核验实际部署／备份和目标状态；远端备份见checkpoint_receipt.json。\n'''
    headline=f'> **当前生产{production[:8]}，逐帧值处理已部署，保留全部先前优化；20%经验估计{point:.4f}场/秒，外推={fit["reference_is_extrapolation"]}。**' if deployed else None
    own=REPO/'docs/C++模拟器逐帧值处理优化记录_2026-11-26.md';assert not own.exists();own.write_text(note.lstrip(),encoding='utf8')
    snapshots=WORK/'docs_snapshot';snapshots.mkdir();overlays={}
    for name in DOCS:
        relative='docs/'+name;base=subprocess.check_output(['git','show',f'{ARCHIVE}:{relative}'],cwd=REPO).decode('utf8')
        snapshot=snapshots/name;snapshot.write_text(document(base,note,headline),encoding='utf8',newline='\n')
        actual_doc=REPO/relative;actual_doc.write_text(document(actual_doc.read_text('utf8'),note,headline),encoding='utf8',newline='\n')
        overlays[relative]=dict(snapshot=snapshot.relative_to(REPO).as_posix(),sha256=sha(snapshot),base_commit=ARCHIVE,only_this_round_note_and_current_status_added=True)
    write(WORK/'archive_document_overlays.json',overlays)
    print(json.dumps(status,indent=2,ensure_ascii=False),flush=True)

if __name__=='__main__':main()

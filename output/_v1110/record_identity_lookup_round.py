"""Record the distinct scalar-truth/private-snapshot combination honestly."""
import json
from pathlib import Path
import statistics
import subprocess
import psutil
from prepare_native_identity_lookup import STAGE,BASE,WORK as PROBE,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/identity_lookup_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
MARKER='## 对象身份与容器查找组合终态（2026-11-26）'
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
    for name,cases in [('private_snapshots_tests.json',234880),('display_storage_tests.json',21888),('control_word_tests.json',44608),('scalar_truth_tests.json',34400),('container_builtins_tests.json',128128),('identity_lookup_tests.json',396400)]:
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
        assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128
        assert read(WORK/'post_ab_directed_regressions.json')['identity_lookup_cases']==396400
        reason='identity_lookup_deployed_retaining_all_prior_components'
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
        restored_private_snapshot_cases=234880,scalar_truth_cases=34400,container_builtin_cases=128128,identity_lookup_cases=396400,total_semantic_cases=860304,all_protocol_processes_finished=True,
        no_more_same_configuration_measurements=True,no_new_branches=True,backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    assert not (WORK/'current_runtime_status.json').exists();write(WORK/'current_runtime_status.json',status)
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''\n\n{MARKER}\n\n候选`{actual}`，生产`{production}`，部署={deployed}，原因={reason}。基于实际生产5BD3，仅改native_scalar_equal.hpp与gd_rt.cpp：在既有标量相等助手中补充Obj／Dict／ClassRef／Enum／FuncRef／Rng的原纯指针比较，及Str／Arr同一指针返回；不同字符串／数组保留原比较。数组find／count两处和字典find_index三处使用保守查找比较，任何Float查找参数仍调用原gd_eq，Vec2／Color／混合数值／不同嵌套数组仍保留原语义；不按Color同一地址短路，因同一颜色也必须比较含NaN的分量。哈希门槛、桶和顺序、循环起点转换、原gd_eq与call_method体、RNG及全部计数保持。严格逆变换逐字还原两份旧文件，其他711份目录文件、708份C++清单及全部674对象头／GdVal24／GdArr32／GdDict32／CoreItem2112／BattleCtx328／watch64布局不变。此前容器、私有、标量、显示、逐帧和control优化均保留。原型完整20普通对象仅作语义验证；正式完整20插桩／新18PGO，原浮点选项保持。新增396400例（112值形态、200704比较、145152数组查询、2144参数别名、48384字典查询及16单求值检查），逐例比较独立实际基线DLL的结果／异常标志／MXCSR，整数网格额外保留完整观测向量；负数、2^32与极大起点转换、碰撞桶、模式退回、未知种类、嵌套数组、NaN和16浮点模式保持。另保留既有463904语义例，共860304及独立4项registry边界。新增夹具首稿用负坐标初始化0..15整数网格，在任何正式计时前的基线初始化断言处停止；仅将存储坐标修为合法范围，保留全部负查询、计数和旧失败脚本／日志；源码、DLL及构建未改，全部检查随后完成。正式版测速前的运动队列依赖指纹仍固定旧相等助手；保留失败记录，仅以本轮严格逆变换还原旧头文件指纹，再续跑原5840状态／旧计数检查及剩余前置项。DLL／对象／源码／18份PGO不变，已通过项与任何正式计时不重跑。\n\n完整{cpu['pairs']}对CPU／墙钟耗时配对中位降低{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，累计降低{cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。全部原始样本和极值保留。raw24={json.dumps(raw,ensure_ascii=False)}；独立cal24={json.dumps(cal,ensure_ascii=False)}；20%经验点／逐批换算中位／最低／最高={point}／{norm['median']}／{norm['minimum']}／{norm['maximum']}场/秒，外推={fit['reference_is_extrapolation']}。20%覆盖和空闲窗口不是门槛，代码收益仍由配对A/B判定，跨环境点估计不充当代码收益。A/B未接受时校准仅作非发布报告，不能冒充raw24或2604验收。\n\n已部署时完整2604逐事件、正常训练12例、实际运行时与源码以post_install_verification.json确认。目标200达到={status['goal200_reached']}，目标最终完成须另核验实际部署／备份和目标状态；远端备份见checkpoint_receipt.json。\n'''
    headline=f'> **当前生产{production[:8]}，对象身份与容器查找已部署，保留全部先前优化；20%经验估计{point:.4f}场/秒，外推={fit["reference_is_extrapolation"]}。**' if deployed else None
    own=REPO/'docs/C++模拟器对象身份与容器查找优化记录_2026-11-26.md';assert not own.exists();own.write_text(note.lstrip(),encoding='utf8')
    snapshots=WORK/'docs_snapshot';snapshots.mkdir();overlays={}
    for name in DOCS:
        relative='docs/'+name;base=subprocess.check_output(['git','show',f'{ARCHIVE}:{relative}'],cwd=REPO).decode('utf8')
        snapshot=snapshots/name;snapshot.write_text(document(base,note,headline),encoding='utf8',newline='\n')
        actual_doc=REPO/relative;actual_doc.write_text(document(actual_doc.read_text('utf8'),note,headline),encoding='utf8',newline='\n')
        overlays[relative]=dict(snapshot=snapshot.relative_to(REPO).as_posix(),sha256=sha(snapshot),base_commit=ARCHIVE,only_this_round_note_and_current_status_added=True)
    write(WORK/'archive_document_overlays.json',overlays)
    print(json.dumps(status,indent=2,ensure_ascii=False),flush=True)

if __name__=='__main__':main()

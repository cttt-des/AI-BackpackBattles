"""Record the distinct scalar-truth/private-snapshot combination honestly."""
import json
from pathlib import Path
import statistics
import subprocess
import psutil
from prepare_native_assembly_membership import STAGE,BASE,WORK as PROBE,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/assembly_membership_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
MARKER='## 装配成员查询优化第一轮（2026-11-26）'
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
    for name,cases in [('private_snapshots_tests.json',234880),('display_storage_tests.json',21888),('control_word_tests.json',44608),('scalar_truth_tests.json',34400),('container_builtins_tests.json',128128),('buff_integer_tests.json',218400),('weapon_chain_tests.json',136128),('assembly_membership_tests.json',229376)]:
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
        assert check['production_source_files']==709 and raw['minimum']>=50 and raw['on_ac_all'] and cal['on_ac_all']
        assert read(WORK/'post_ab_directed_regressions.json')['scalar_truth_cases']==34400
        assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128
        assert read(WORK/'post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read(WORK/'post_ab_directed_regressions.json')['buff_integer_method_cases']==14112
        reason='assembly_membership_deployed_retaining_all_prior_components'
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
        second_direction_deployment_complete=deployed,goal_requires_verified_remote_backup=True,current_display_and_control_components_retained=True,
        restored_private_snapshot_cases=234880,scalar_truth_cases=34400,container_builtin_cases=128128,buff_integer_helper_cases=204288,buff_integer_method_cases=14112,weapon_chain_cases=136128,assembly_membership_cases=229376,total_semantic_cases=1047808,all_protocol_processes_finished=True,
        no_more_same_configuration_measurements=True,no_new_branches=True,backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    assert not (WORK/'current_runtime_status.json').exists();write(WORK/'current_runtime_status.json',status)
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''\n\n{MARKER}\n\n候选`{actual}`，生产`{production}`，部署={deployed}，原因={reason}。以实际生产D206为基线，仅改变CoreItem::onItemAdded当前受影响对象集合的一处成员判断，增加私有原生bool助手。200场诊断记录1009420次对象集合查询，其中961606次字典为空；坐标数组查询50894次。本切片在对象键且字典未索引、长度为零时返回false，避免无副作用的对象指针哈希和GdVal布尔返回中转；已索引或非空字典继续调用原has，其他容器继续原gd_in与真假转换。未将普通空表推论扩大到可能保留陈旧索引的len=0表，也未跳过非对象键原哈希的FP异常标志。不更改全局相等、哈希或字典表示；坐标查询、完整query阶段／commit阶段及回调、字段观察、RNG和物理帧顺序保持。原型固定200场结果与全部旧计数一致，新增229376组私有助手语义测试，覆盖原112形态、128容器状态和16浮点模式；实际原DLL内部原gd_in与助手逐例完全一致，跨原型／生产结果、fenv／MXCSR及旧计数一致。涵盖未索引空表、保留索引的空表、手工len=0陈旧索引、深复制、整数网格、数值别名、NaN／subnormal及未知形态，并检查输入与容器不变。首个测试夹具因两次新建临时GdVal的填充字节比较而失败，修为对同一持久值前后比较，全部229376例保留，仅新增测试重跑。既有818432例保留，共1047808例；普通构建保留既有56例武器矩阵跨构建差异及源同生产普通基准的零差异证明，正式PGO必须与实际生产完整一致。674对象头、CoreItem2112／Weapon4288／BattleCtx328及所有布局不变。正式完整20插桩／新18PGO，原浮点选项保持。频数及无独立助手函数的机器码证据仅证明机制，不代替成对收益。\n\n完整{cpu['pairs']}对CPU／墙钟耗时配对中位降低{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，累计降低{cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。全部原始样本和极值保留。raw24={json.dumps(raw,ensure_ascii=False)}；独立cal24={json.dumps(cal,ensure_ascii=False)}；20%经验点／逐批换算中位／最低／最高={point}／{norm['median']}／{norm['minimum']}／{norm['maximum']}场/秒，外推={fit['reference_is_extrapolation']}。20%覆盖和空闲窗口不是门槛，代码收益仍由配对A/B判定，跨环境点估计不充当代码收益。A/B未接受时校准仅作非发布报告，不能冒充raw24或2604验收。\n\n已部署时完整2604逐事件、正常训练12例、实际运行时与源码以post_install_verification.json确认。这是三个方向中的第二方向；本轮依据收益与语义验收决定是否部署并备份；按用户最新指示，后续优化保持暂停，收尾后优先对照原版源码核查同帧事件及药水触发顺序；旧200场/秒不是本轮门槛；远端备份见checkpoint_receipt.json。\n'''
    headline=f'> **当前生产{production[:8]}，装配成员查询优化已部署，保留全部先前优化；20%经验估计{point:.4f}场/秒，外推={fit["reference_is_extrapolation"]}。**' if deployed else None
    own=REPO/'docs/C++模拟器装配成员查询优化记录_2026-11-26.md';assert not own.exists();own.write_text(note.lstrip(),encoding='utf8')
    snapshots=WORK/'docs_snapshot';snapshots.mkdir();overlays={}
    for name in DOCS:
        relative='docs/'+name;base=subprocess.check_output(['git','show',f'{ARCHIVE}:{relative}'],cwd=REPO).decode('utf8')
        snapshot=snapshots/name;snapshot.write_text(document(base,note,headline),encoding='utf8',newline='\n')
        actual_doc=REPO/relative;actual_doc.write_text(document(actual_doc.read_text('utf8'),note,headline),encoding='utf8',newline='\n')
        overlays[relative]=dict(snapshot=snapshot.relative_to(REPO).as_posix(),sha256=sha(snapshot),base_commit=ARCHIVE,only_this_round_note_and_current_status_added=True)
    write(WORK/'archive_document_overlays.json',overlays)
    print(json.dumps(status,indent=2,ensure_ascii=False),flush=True)

if __name__=='__main__':main()

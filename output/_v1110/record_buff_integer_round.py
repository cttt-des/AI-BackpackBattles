"""Record the distinct scalar-truth/private-snapshot combination honestly."""
import json
from pathlib import Path
import statistics
import subprocess
import psutil
from prepare_native_buff_integer_kernel import STAGE,BASE,WORK as PROBE,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/buff_integer_kernel_bundle'
AUDIT=STAGE/'native_perf50/load20_recovery_20261126'
MARKER='## Buff整数运算局部定型终态（2026-11-26）'
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
    for name,cases in [('private_snapshots_tests.json',234880),('display_storage_tests.json',21888),('control_word_tests.json',44608),('scalar_truth_tests.json',34400),('container_builtins_tests.json',128128),('buff_integer_tests.json',218400)]:
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
        assert read(WORK/'post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read(WORK/'post_ab_directed_regressions.json')['buff_integer_method_cases']==14112
        reason='buff_integer_deployed_retaining_all_prior_components'
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
        typed_buff_goal_deployment_complete=deployed,goal_requires_verified_remote_backup=True,current_display_and_control_components_retained=True,
        restored_private_snapshot_cases=234880,scalar_truth_cases=34400,container_builtin_cases=128128,buff_integer_helper_cases=204288,buff_integer_method_cases=14112,total_semantic_cases=682304,all_protocol_processes_finished=True,
        no_more_same_configuration_measurements=True,no_new_branches=True,backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    assert not (WORK/'current_runtime_status.json').exists();write(WORK/'current_runtime_status.json',status)
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''\n\n{MARKER}\n\n候选`{actual}`，生产`{production}`，部署={deployed}，原因={reason}。基于实际生产5BD3，仅修改gen/shards/shard_00.cpp中的CoreBuff::gainTemporary原生分支：将整数加减、整数最小值、整数与布尔强转及小整数正数判断局部内联。整数加减溢出、混合类型、未知形态及全部浮点运算仍执行原运行库；比较快路径限制在±2^53以保留整数转double的舍入与异常标志。完整通用分支、全部回调与RNG调用顺序、字段读取位置、循环快照和物理帧时序保持。严格逆变换逐字还原旧分片，其余712份完整清单文件、674对象头与全部布局不变。保留此前所有优化。原型仅重编译变更分片并复用19份已核对源码及字节的普通对象作语义检查；正式完整20插桩／新18PGO，原浮点选项保持。新增204288组助手边界测试（806160次有效操作／库、16浮点模式），在各实际DLL内部逐操作精确比较原函数与助手的完整值向量、输入字节、异常标志与MXCSR；其中9904次新增整数／布尔快路径额外跨DLL一致。112种值形态保留，但原gd_lt无法定义的240次空Str指针排序不执行，原版崩溃、gdb证据与首稿保留。普通编译的未改动gd_sub在极小数减零时与生产PGO存在既有差异，保留两版原始记录，不将未改动fallback的跨编译差异伪报为一致；各库内部所有fallback与原函数必须完全一致。正式PGO版额外要求全部204288组跨DLL完整观测（含浮点、NaN、复杂类型和溢出回退）一致，结果见buff_full_pgo_tests.json。实际Buff方法另有14112例，在16浮点模式下覆盖整数边界、转换、零值、NaN、反射、临时层数及计时器，并与生产DLL逐例核对状态／RNG／异常标志／MXCSR。既有463904例全部保留，共682304及独立4项registry边界。诊断的49858次方法调用及整数热路径频数只用于选题，不代替机器码或测速收益。\n\n完整{cpu['pairs']}对CPU／墙钟耗时配对中位降低{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，累计降低{cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。全部原始样本和极值保留。raw24={json.dumps(raw,ensure_ascii=False)}；独立cal24={json.dumps(cal,ensure_ascii=False)}；20%经验点／逐批换算中位／最低／最高={point}／{norm['median']}／{norm['minimum']}／{norm['maximum']}场/秒，外推={fit['reference_is_extrapolation']}。20%覆盖和空闲窗口不是门槛，代码收益仍由配对A/B判定，跨环境点估计不充当代码收益。A/B未接受时校准仅作非发布报告，不能冒充raw24或2604验收。\n\n已部署时完整2604逐事件、正常训练12例、实际运行时与源码以post_install_verification.json确认。本轮目标是通过验收的伤害／Buff定型正收益部署与远端备份；旧200场/秒目标已由用户清除，不作为本轮完成条件；远端备份见checkpoint_receipt.json。\n'''
    headline=f'> **当前生产{production[:8]}，Buff整数运算局部定型已部署，保留全部先前优化；20%经验估计{point:.4f}场/秒，外推={fit["reference_is_extrapolation"]}。**' if deployed else None
    own=REPO/'docs/C++模拟器Buff整数定型优化记录_2026-11-26.md';assert not own.exists();own.write_text(note.lstrip(),encoding='utf8')
    snapshots=WORK/'docs_snapshot';snapshots.mkdir();overlays={}
    for name in DOCS:
        relative='docs/'+name;base=subprocess.check_output(['git','show',f'{ARCHIVE}:{relative}'],cwd=REPO).decode('utf8')
        snapshot=snapshots/name;snapshot.write_text(document(base,note,headline),encoding='utf8',newline='\n')
        actual_doc=REPO/relative;actual_doc.write_text(document(actual_doc.read_text('utf8'),note,headline),encoding='utf8',newline='\n')
        overlays[relative]=dict(snapshot=snapshot.relative_to(REPO).as_posix(),sha256=sha(snapshot),base_commit=ARCHIVE,only_this_round_note_and_current_status_added=True)
    write(WORK/'archive_document_overlays.json',overlays)
    print(json.dumps(status,indent=2,ensure_ascii=False),flush=True)

if __name__=='__main__':main()

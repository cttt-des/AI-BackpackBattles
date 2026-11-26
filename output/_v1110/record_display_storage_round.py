"""Record complete evidence and append this round without absorbing other edits."""
import json
import os
from pathlib import Path
import statistics
import subprocess
import tempfile
import psutil
from prepare_native_display_storage import STAGE,BASE,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/display_storage_bundle'
DOCS=('C++模拟器优化交接_2026-11-23.md','C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md')
MARKER='## 显示数组存储轮终态（2026-11-24）'

def read(name):return json.loads((WORK/name).read_bytes())
def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def terminal():
    rows=list(read('live_formal_driver.json').values())
    if (WORK/'live_close_calibration.json').exists():rows.append(read('live_close_calibration.json'))
    for row in rows:
        try:
            p=psutil.Process(row['pid']);assert p.create_time()!=row['created'] or not p.is_running(),'Identified protocol process is still running'
        except psutil.NoSuchProcess:pass

def describe(report):
    rows=report['samples'];values=[x['fights_per_second'] for x in rows]
    assert len(rows)==report['repeat']==24 and report['workers']==1 and report['fights']==200
    assert report['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert report['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert all(x['matched_original_terminal']==200 for x in rows)
    return dict(median_fights_per_second=statistics.median(values),minimum_fights_per_second=min(values),maximum_fights_per_second=max(values),
        background_load_range_pct=[min(x['background_load_pct'] for x in rows),max(x['background_load_pct'] for x in rows)],
        on_ac_all=all(x['on_ac_before'] is True and x['on_ac_after'] is True for x in rows))

def document(text,note,status):
    assert MARKER not in text
    if status['deployed']:
        point=status['candidate_load20_fps'];lines=text.splitlines(keepends=True)
        newline='\r\n' if lines and lines[0].endswith('\r\n') else '\n'
        line=f"> **当前生产{status['production_dll_sha256'][:8]}，显示数组存储已验收部署；20%换算{point:.4f}。本轮记录见文末，备份另按收据确认。**"
        candidates=[i for i,l in enumerate(lines[:8]) if l.startswith('> **当前生产') or ('日期：' in l and '当前已验收部署' in l)]
        if candidates:
            previous=lines[candidates[0]]
            ending='\r\n' if previous.endswith('\r\n') else ('\n' if previous.endswith('\n') else '')
            lines[candidates[0]]=line+ending
        else:lines.insert(2,line+newline)
        text=''.join(lines)
    return text+note

def main():
    terminal();actual=sha(WORK/'bundle.dll');decision=read('candidate_decision.json')
    assert decision['candidate_dll_sha256']==actual and decision['assessment_sha256']==sha(Path(decision['selected_assessment']))
    ab=json.loads(Path(decision['selected_assessment']).read_bytes())
    assert ab['baseline_dll_sha256']==EXPECTED and ab['candidate_dll_sha256']==actual
    for name,cases in [('display_storage_tests.json',21888),('control_word_tests.json',44608)]:
        proof=read(name);assert proof['passed'] and proof['cases']==cases and proof['dll_sha256']==actual
    assert read('display_storage_tests.json')['candidate_core_item_bytes']==2112
    assert read('fresh_profile_source.json')['compiler_optimization_flags']==[]
    deployed=(WORK/'post_install_verification.json').exists();point=None;raw=None
    if deployed:
        check=read('post_install_verification.json');summary=read('measurements_summary.json')
        assert check['passed'] and check['dll_sha256']==actual and check['strict_event_cases']==2604
        raw=describe(read('bundle_serial.json'));cal=describe(read('bundle_load_calibration.json'))
        point=summary['fitted_fights_per_second_at20'];assert check['goal200_reached']==(point>=200)
        normalized=read('bundle_load20.json')['estimated_fights_per_second_at_reference_load_by_sample']
        save('normalized20_sample_summary.json',dict(dll_sha256=actual,no_additional_timing=True,
            interpretation='Fit-derived sample estimates, not direct observations at20%',median=statistics.median(normalized),minimum=min(normalized),maximum=max(normalized),global_fitted_point=point))
        reason='deployed_after_all_original_gates'
    elif (WORK/'rejection_receipt.json').exists():
        rejected=read('rejection_receipt.json');assert rejected['candidate_dll_sha256']==actual and rejected['not_deployed'] and decision['status']!='positive_combined_evidence'
        cal=describe(read('rejected_load_calibration.json'));point=rejected['fitted_fights_per_second_at20'];reason='AB_not_accepted_nonrelease_calibration_only'
    else:
        assert decision['status']=='positive_combined_evidence'
        gate=read('bundle_full_gate.json');assert gate['complete'] and gate['dll_sha256']==actual
        raw=describe(read('bundle_serial.json'));cal=describe(read('bundle_load_calibration.json'))
        fit=read('bundle_load20.json') if (WORK/'bundle_load20.json').exists() else None
        lo,hi=cal['background_load_range_pct'];covered=lo<=20<=hi
        if fit:point=fit['fitted_fights_per_second_at_reference_load']
        else:assert not covered
        raw_ok=raw['minimum_fights_per_second']>=50 and raw['on_ac_all']
        assert not covered or not raw_ok or not cal['on_ac_all'],'Valid release evidence still requires review and deployment'
        reason='release_measurement_gate_failed'
        if not (WORK/'measurements_summary.json').exists():save('measurements_summary.json',dict(dll_sha256=actual,serial=raw,load_calibration=cal,raw24_gate_passed=raw_ok,fitted_fights_per_second_at20=point,load20_covered=covered,posthoc_summary_only_no_additional_measurement=True,single_run_all_samples_retained=True))
        save('release_gate_failure.json',dict(status=reason,candidate_dll_sha256=actual,load20_covered=covered,raw24_gate_passed=raw_ok,no_extrapolation=True,no_repeat_measurements=True,not_deployed=True))
    production=actual if deployed else EXPECTED
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==production
    reached=bool(deployed and point is not None and point>=200)
    status=dict(candidate_dll_sha256=actual,production_dll_sha256=production,deployed=deployed,reason=reason,
        candidate_load20_fps=point,raw24=raw,calibration24=cal,goal200_reached=reached,goal_still_active=not reached,
        source_changes=['gen/hdrs/Gd__gd_core__CoreItem.hpp','gen/shards/shard_00.cpp'],intentional_core_item_layout=[1792,2112],
        all_protocol_processes_finished=True,no_more_same_configuration_measurements=True,no_new_branches=True,
        backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    save('current_runtime_status.json',status)
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''

{MARKER}

候选`{actual}`；生产`{production}`；部署={deployed}；原因={reason}。从已部署680版本的707源码开始，仅改CoreItem头与shard00：把首次显示覆盖数组的头及10个值放入同一arena拥有的物品对象。原初始化／size求值／resize／fill顺序、实际逐帧读写、回调、浮点运算、RNG与旧计数器全部保留；数组头及缓冲分别只用一次，别名逸出、重初始化、复制／移动、替换、扩容、监测数组与外部对象保留后备。CoreItem1792→2112，其余GdVal24／GdArr32／BattleCtx328／watch64及C接口不变；全20编译和新18PGO，不混用旧对象文件。

语义原型及正式DLL均完成21888个独立旧／新DLL存储、别名、实际setup和64种浮点状态用例，另保留44608个control／active／targeted／frame用例及4个registry边界。固定200的输入、结果哈希、原终局、旧六与两组十项计数相同。首个语义构建已成功编译链接20单元，末尾宽泛*.o计数误含LTO临时对象而断言失败；按20个正式文件名核验原产物，不重编译。首轮保留用例在原1792字节断言处停止，已通过的日志保留，仅为新布局适配该断言，原状态／旧计数器哈希未删改，源码与DLL未改。正式计时不重复。

完整{cpu['pairs']}对CPU／墙钟配对中位耗时降低{cpu['paired_median_time_reduction_pct']:.4f}%／{wall['paired_median_time_reduction_pct']:.4f}%；累计耗时降低{cpu['sum_time_reduction_pct']:.4f}%／{wall['sum_time_reduction_pct']:.4f}%。保留所有组与极端值，沿用冻结24（必要时仅追加8）规则，不把历史标定点变化当作代码收益。首发布raw24={json.dumps(raw,ensure_ascii=False)}；独立cal24={json.dumps(cal,ensure_ascii=False)}；20%换算={point}。null表示未覆盖20%，不外推、不重测；非发布校准不替代发布raw24。完整2604逐事件验收仅在A/B接受后执行，以实际bundle_vs_deployed_hashes.json等原始证据为准，不把提前拒绝候选写成通过。

目标200及部署验收达到={reached}，远端备份仍须读checkpoint_receipt.json确认。本轮复用既有备份分支；归档使用独立暂存索引及commit-tree，保留工作区当前分支和暂存内容。各原进程均已结束，不重启旧入口。current_runtime_status.json记录终态，candidate_decision.json保留当时未部署决策。
'''
    own=REPO/'docs/C++模拟器显示数组存储优化记录_2026-11-24.md';assert not own.exists();own.write_text(note.lstrip(),encoding='utf8',newline='\n')
    overlays={};folder=WORK/'docs_snapshot';folder.mkdir()
    for name in DOCS:
        relative='docs/'+name
        old=subprocess.check_output(['git','show',f'{ARCHIVE}:{relative}'],cwd=REPO).decode('utf8')
        snapshot=folder/name;snapshot.write_text(document(old,note,status),encoding='utf8',newline='\n')
        overlays[relative]=dict(snapshot=snapshot.relative_to(REPO).as_posix(),sha256=sha(snapshot),base_commit=ARCHIVE,only_this_round_note_and_current_status_added=True)
        current=REPO/relative;before=current.read_bytes();updated=document(before.decode('utf8'),note,status).encode('utf8')
        with tempfile.NamedTemporaryFile(dir=current.parent,prefix='display-round-',delete=False) as temporary:
            swap=Path(temporary.name);temporary.write(updated)
        try:
            assert current.read_bytes()==before,'Documentation changed concurrently; preserve it and inspect before appending'
            os.replace(swap,current)
        finally:swap.unlink(missing_ok=True)
    save('archive_document_overlays.json',overlays)
    print(json.dumps(status,indent=2),flush=True)

if __name__=='__main__':main()

"""Record terminal prefetch-trial evidence without inventing a missing20% point."""
import json
import statistics
from pathlib import Path
import psutil
from prepare_native_control_word import STAGE,BASE,EXPECTED,sha
WORK=STAGE/'native_perf50/control_word_bundle'

REPO=STAGE.parents[1]
def read(name):return json.loads((WORK/name).read_bytes())
def save(name,data):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def terminal():
    identities=read('live_formal_driver.json')
    for key in ('driver','build','qualifier'):
        row=identities[key]
        try:
            p=psutil.Process(row['pid']);assert p.create_time()!=row['created'] or not p.is_running(),key+' is still running'
        except psutil.NoSuchProcess:pass

def describe(report):
    rows=report['samples'];v=[x['fights_per_second'] for x in rows]
    assert len(rows)==report['repeat']==24 and report['workers']==1 and report['fights']==200
    assert report['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert report['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert all(x['matched_original_terminal']==200 for x in rows)
    return dict(median_fights_per_second=statistics.median(v),minimum_fights_per_second=min(v),maximum_fights_per_second=max(v),
        background_load_range_pct=[min(x['background_load_pct'] for x in rows),max(x['background_load_pct'] for x in rows)],
        on_ac_all=all(x['on_ac_before'] is True and x['on_ac_after'] is True for x in rows))

def main():
    terminal();actual=sha(WORK/'bundle.dll');decision=read('candidate_decision.json')
    assert actual==decision['candidate_dll_sha256'] and sha(Path(decision['selected_assessment']))==decision['assessment_sha256']
    ab=json.loads(Path(decision['selected_assessment']).read_bytes())
    assert ab['candidate_dll_sha256']==actual and ab['baseline_dll_sha256']==EXPECTED
    deployed=(WORK/'post_install_verification.json').exists()
    proof=read('control_word_tests.json');assert proof['passed'] and proof['cases']==44608 and proof['dll_sha256']==actual
    assert read('fresh_profile_source.json')['compiler_optimization_flags']==[]
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s'];point=None;raw=None;cal=None
    if deployed:
        checked=read('post_install_verification.json');summary=read('measurements_summary.json')
        assert checked['passed'] and checked['dll_sha256']==actual
        assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==actual
        raw=summary['serial'];cal=summary['load_calibration'];point=summary['fitted_fights_per_second_at20']
        assert checked['goal200_reached']==(point>=200)
        normalized=read('bundle_load20.json')['estimated_fights_per_second_at_reference_load_by_sample']
        save('normalized20_sample_summary.json',dict(dll_sha256=actual,no_additional_timing=True,
            interpretation='Per-sample estimates from the original fit, not direct observations at20%',
            median=statistics.median(normalized),minimum=min(normalized),maximum=max(normalized),global_fitted_point=point))
        reason='deployed_after_all_original_gates'
    elif (WORK/'rejection_receipt.json').exists():
        rejected=read('rejection_receipt.json');assert rejected['candidate_dll_sha256']==actual and rejected['not_deployed']
        assert decision['status']!='positive_combined_evidence'
        cal=describe(read('rejected_load_calibration.json'));point=rejected['fitted_fights_per_second_at20']
        reason='AB_not_accepted_nonrelease_calibration_only'
    else:
        assert decision['status']=='positive_combined_evidence'
        gate=read('bundle_full_gate.json');assert gate['complete'] and gate['dll_sha256']==actual
        raw=describe(read('bundle_serial.json'));cal=describe(read('bundle_load_calibration.json'))
        fit=read('bundle_load20.json') if (WORK/'bundle_load20.json').exists() else None
        lo,hi=cal['background_load_range_pct'];covered=lo<=20<=hi
        if fit is not None:point=fit['fitted_fights_per_second_at_reference_load']
        else:assert not covered
        raw_ok=raw['minimum_fights_per_second']>=50 and raw['on_ac_all']
        assert not covered or not raw_ok or not cal['on_ac_all'],'Valid measurements still require review and deployment; do not close early'
        reason='release_measurement_gate_failed'
        if not (WORK/'measurements_summary.json').exists():
            save('measurements_summary.json',dict(dll_sha256=actual,serial=raw,load_calibration=cal,
                raw24_gate_passed=raw_ok,fitted_fights_per_second_at20=point,load20_covered=covered,
                posthoc_summary_only_no_additional_measurement=True,single_run_all_samples_retained=True,
                missing_reason=None if covered else 'Reference20 lies outside observed range; no extrapolation or rerun',
                report_sha256={n:sha(WORK/n) for n in ('bundle_serial.json','bundle_load_calibration.json')}))
        save('release_gate_failure.json',dict(status=reason,candidate_dll_sha256=actual,load20_covered=covered,
            raw24_gate_passed=raw_ok,no_extrapolation=True,no_repeat_measurements=True,not_deployed=True))
    if not deployed:assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    reached=bool(deployed and point is not None and point>=200)
    status=dict(candidate_dll_sha256=actual,production_dll_sha256=actual if deployed else EXPECTED,
        deployed=deployed,reason=reason,goal200_reached=reached,goal_still_active=not reached,
        candidate_load20_fps=point,raw24=raw,calibration24=cal,compiler_flags=[],source_changes=['gen/shards/shard_03.cpp','native_active_cooldowns.hpp','native_targeted_timers.hpp'],
        all_protocol_processes_finished=True,no_more_same_configuration_measurements=True,
        backup_status_recorded_separately=True,backup_receipt='checkpoint_receipt.json')
    prior=WORK/'current_runtime_status.json'
    if prior.exists():
        assert read('current_runtime_status.json')['stage'] in ('full20_instrumentation_build_running','profile_guided_release_build_running','preflight_validation_running','ab_not_accepted_nonrelease_calibration_pending')
        assert not (WORK/'pre_terminal_runtime_status.json').exists()
        prior.rename(WORK/'pre_terminal_runtime_status.json')
    save('current_runtime_status.json',status)
    note=f'''

## control word轮终态（2026-11-24）

候选`{actual}`，部署={deployed}，原因={reason}。从F950的707源码开始，不叠加失败预取、PTA或private snapshots。只改两份timer辅助头与shard03新增C测试入口，将原四处状态检查改为实时掩码读取。active、timer入口、timer回调后三个谓词各保留原条件范围；collect位忽略，双版本、回调和后缀位置不变，无浮点／RNG／观察／额外写入。全部布局及674对象头保持，完整20插桩与新18PGO。语义原型和正式DLL各完成44608项状态、原Bool后备及旧active／targeted／frame检查，另有4个registry边界；固定200原hash、自然终局、旧六和两组十项计数一致。第一版后备夹具拾取STAGE旧辅助头，失败和已通过actual16k保留；第二版将逐字相同的后备助手隔离命名空间、使用ASCII本地夹具源并不加载DLL，候选源码／DLL未改动。没有重做任何正式计时。

完整{cpu['pairs']}对CPU／墙钟配对中位耗时降低{cpu['paired_median_time_reduction_pct']:.4f}%／{wall['paired_median_time_reduction_pct']:.4f}%，累计耗时降低{cpu['sum_time_reduction_pct']:.4f}%／{wall['sum_time_reduction_pct']:.4f}%。全部原始组／极端值保留，按原冻结24(+唯一8)规则判定，不拿历史20%标定点差值当代码收益。首raw24={json.dumps(raw,ensure_ascii=False)}。独立cal24={json.dumps(cal,ensure_ascii=False)}。候选20%换算={point}，若为null即未覆盖20，不能外推、替代或重跑；非发布校准也明确不当作发布raw24。

状态以current_runtime_status.json和原candidate_decision.json／post_install_verification.json为准。首次cal前OS观测资格记录在calibration_eligibility.json，未运行战斗样本；正式计时仍仅一次24批全部保留。目标200点及部署验收达到={reached}；远端备份必须另读checkpoint_receipt.json再决定目标完成。所有本轮driver已结束，不重启旧入口。生产DLL为{status['production_dll_sha256']}。
'''
    for name in ('C++模拟器优化交接_2026-11-23.md','C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md'):
        p=REPO/'docs'/name;text=p.read_text('utf8');assert '## control word轮终态（2026-11-24）' not in text
        if deployed and name!='C++模拟器性能优化清单.md':
            lines=text.splitlines()
            lines[2]=(f'> **当前生产{actual[:8]}，control word已验收部署；20%换算{point:.4f}。完整记录见文末，备份另按收据确认。**'
                if name=='C++模拟器优化交接_2026-11-23.md' else f'日期：2026-11-24。当前已验收部署{actual[:8]}，最新20%换算{point:.4f}，200点达到={reached}；见文末。')
            text='\n'.join(lines)+'\n'
        p.write_text(text+note,encoding='utf8',newline='\n')
    print(json.dumps(status,indent=2),flush=True)

if __name__=='__main__':main()

"""Close this round without repeating an observed, uncovered calibration."""
import json
import statistics
from pathlib import Path
from prepare_native_private_snapshots import STAGE,EXPECTED,sha

WORK=STAGE/'native_perf50/private_snapshots_bundle'
REPO=STAGE.parents[1]

def read(name):return json.loads((WORK/name).read_bytes())
def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def main():
    actual=sha(WORK/'bundle.dll');decision=read('candidate_decision.json')
    assert actual==decision['candidate_dll_sha256'] and decision['status']=='positive_combined_evidence'
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    assert not (WORK/'bundle_load20.json').exists() and not (WORK/'post_install_verification.json').exists()
    ab=json.loads(Path(decision['selected_assessment']).read_bytes());assert all(r['pairs']==32 for r in ab['metrics'].values())
    gate=read('bundle_full_gate.json');audit=read('full_type_audit.json');hashes=read('bundle_vs_deployed_hashes.json')
    assert gate['complete'] and gate['dll_sha256']==actual
    assert audit['fights']==hashes['unchanged_cpp_event_streams']==2604
    assert hashes['ordered_case_and_cpp_event_hashes_sha256']=='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
    def summarize(name):
        report=read(name);rows=report['samples'];values=[r['fights_per_second'] for r in rows]
        assert report['dll_sha256']==actual and report['repeat']==len(rows)==24 and report['workers']==1 and report['fights']==200
        assert report['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
        assert report['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
        assert all(r['matched_original_terminal']==200 for r in rows)
        return dict(median_fights_per_second=statistics.median(values),minimum_fights_per_second=min(values),maximum_fights_per_second=max(values),
            background_load_range_pct=[min(r['background_load_pct'] for r in rows),max(r['background_load_pct'] for r in rows)],
            on_ac_all=all(r['on_ac_before'] is True and r['on_ac_after'] is True for r in rows))
    serial=summarize('bundle_serial.json');cal=summarize('bundle_load_calibration.json')
    assert serial['minimum_fights_per_second']>=50 and serial['on_ac_all'] and cal['on_ac_all']
    assert not cal['background_load_range_pct'][0]<=20<=cal['background_load_range_pct'][1]
    result=dict(dll_sha256=actual,serial=serial,load_calibration=cal,raw24_gate_passed=True,load20_covered=False,
        fitted_fights_per_second_at20=None,fit_validation=None,r_squared_log_wall_time=None,
        missing_reason='20% lies outside the original independent calibration range; extrapolation and rerun rejected',
        report_sha256={n:sha(WORK/n) for n in ['bundle_serial.json','bundle_load_calibration.json']},
        single_run_all_samples_retained=True,posthoc_summary_only_no_additional_measurement=True)
    save('measurements_summary.json',result)
    save('release_gate_failure.json',dict(status='not_deployed_load20_uncovered',candidate_dll_sha256=actual,
        production_dll_sha256=EXPECTED,strict_event_cases=2604,original_ab_decision_retained=True,
        all32_pairs_retained=True,raw24_gate_passed=True,independent_calibration24_retained=True,
        no_extrapolation=True,no_repeat_calibration=True,no_more_same_source_groups=True,
        load20_covered=False,goal200_reached=False,goal_still_active=True,
        all_formal_protocol_processes_terminal=True,measurements_summary_sha256=sha(WORK/'measurements_summary.json')))
    save('current_runtime_status.json',dict(production_dll_sha256=EXPECTED,candidate_dll_sha256=actual,candidate_installed=False,
        reason='Independent calibration does not cover20%; deployment gate failed',goal200_reached=False,goal_still_active=True,
        latest_production_load20_fps=186.34032339352876,candidate_load20_fps=None,
        no_more_same_source_AB_or_calibration=True,all_formal_protocol_processes_finished=True))
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    note=f'''

## private snapshots轮结束，校准未覆盖20，未部署（2026-11-24）

本轮所有进程／测速已终止；工具95941、PID16780已结束，不等待或重启。正式候选CD4EE746（完整SHA `{actual}`），语义原型B13ECF；生产仍F950，最新已验收20%点仍186.3403，200目标active。不能把生产点当成本轮候选点。

完整20插桩、新18PGO及708源复现完成；14私有整数循环和两处native身份文本快照组合，旧674对象头／布局保持。固定200新增整数视图30901／身份快照34193，旧六计数、自然终局及输入／结果hash一致。实际正式DLL新增234880项差分在A/B前后通过，保留320256／126192／5184及所有原回归通过。wrapper旧原型清单路径漏改的失败、修正与续跑留档；没有重编、重训、重跑已观察正式样本。

完整32对CPU／墙钟配对中位耗时降低{cpu['paired_median_time_reduction_pct']:.4f}%／{wall['paired_median_time_reduction_pct']:.4f}%，但累计耗时增加{-cpu['sum_time_reduction_pct']:.4f}%／{-wall['sum_time_reduction_pct']:.4f}%，胜{cpu['candidate_wins']}／{wall['candidate_wins']}对，CPU有{cpu['ties']}对持平。按冻结最终双中位规则满足A/B门槛，收益证据仍偏弱；不丢弃第二组或极端样本，不再追加。

2604场（914+1690）逐事件严格验收和新旧逐场事件hash全一致，根仍b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54。首raw24中位{serial['median_fights_per_second']:.4f}，最低{serial['minimum_fights_per_second']:.4f}，最高{serial['maximum_fights_per_second']:.4f}场/秒，全部>=50；背景负载{serial['background_load_range_pct'][0]:.4f}%–{serial['background_load_range_pct'][1]:.4f}%。独立cal24中位{cal['median_fights_per_second']:.4f}，最低{cal['minimum_fights_per_second']:.4f}，最高{cal['maximum_fights_per_second']:.4f}，负载{cal['background_load_range_pct'][0]:.4f}%–{cal['background_load_range_pct'][1]:.4f}%，全AC、全200自然终局。

由于独立校准最小负载已超过20%，fit原程序按原规则拒绝，退出2，没有bundle_load20.json。20%换算为缺失（N/A），不外推、不拿raw24代替独立校准、不重复任何同源校准。原qualification和release_measurements日志原样保留；measurements_summary.json仅总结原两份24样本，不是新的测速，release_gate_failure.json记录未部署原因。原candidate_decision.json为A/B时点阳性而not_deployed=true，按原样保留。没有安装、正常训练替换或部署后采样；生产及生成配方保持F950。

归档本轮全部源码／用例／32对／2604逐场收据／原始24+24及失败日志，再评估真正不同的下一候选。小规模分配组合的收益偏弱；下一轮优先评估原规划的编译器跨过程别名分析，先核对工具链默认项／官方语义与资源成本，不自动叠加本轮未部署改动。目标继续active。
'''
    for name in ['C++模拟器优化交接_2026-11-23.md','C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md']:
        p=REPO/'docs'/name;text=p.read_text('utf8');assert '## private snapshots轮结束，校准未覆盖20，未部署' not in text
        p.write_text(text+note,encoding='utf8',newline='\n')
    print(json.dumps(result,indent=2),flush=True)

if __name__=='__main__':main()

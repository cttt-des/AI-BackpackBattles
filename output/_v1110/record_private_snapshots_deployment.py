"""Record only completed deployment evidence, without inferring gains from calibrations."""
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
    check=read('post_install_verification.json');measure=read('measurements_summary.json')
    installation=read('bundle_installation.json');decision=read('candidate_decision.json')
    review=read('pre_install_review.json');fit=read('bundle_load20.json')
    profile=read('profile_receipt.json');summary=read('brainstorm_profile_summary.json')
    ab=json.loads(Path(decision['selected_assessment']).read_bytes());actual=check['dll_sha256']
    assert check['passed'] and check['private_snapshot_cases']==234880
    assert actual==measure['dll_sha256']==profile['dll_sha256']==summary['dll_sha256']
    assert actual==sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')
    assert actual!=EXPECTED and ab['baseline_dll_sha256']==EXPECTED and ab['candidate_dll_sha256']==actual
    assert decision['status']=='positive_combined_evidence' and installation['ab_pairs'] in (24,32)
    assert all(sha(REPO/n)==h for n,h in review['protected_user_files_sha256'].items())
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s']
    serial=measure['serial'];cal=measure['load_calibration'];point=measure['fitted_fights_per_second_at20']
    reached=point>=200;assert check['goal200_reached']==reached
    weak=not (cpu['sum_time_reduction_pct']>0 and wall['sum_time_reduction_pct']>0)
    normalized=fit['estimated_fights_per_second_at_reference_load_by_sample'];assert len(normalized)==24
    save('normalized20_sample_summary.json',dict(dll_sha256=actual,no_additional_timing=True,source_fit_sha256=sha(WORK/'bundle_load20.json'),
        interpretation='Per-sample model estimates; not direct observations at exactly20%',
        median=statistics.median(normalized),minimum=min(normalized),maximum=max(normalized),global_fitted_point=point))
    save('current_runtime_status.json',dict(production_dll_sha256=actual,current_optimization='private integer views and deferred identity byte snapshots',
        deployed=True,post_install_verified=True,goal200_reached=reached,backup_status_recorded_separately=True,
        fitted_fights_per_second_at20=point,raw24=serial,calibration24=cal,ab_pairs=installation['ab_pairs'],
        cpu_paired_median_reduction_pct=cpu['paired_median_time_reduction_pct'],wall_paired_median_reduction_pct=wall['paired_median_time_reduction_pct'],
        cpu_sum_time_reduction_pct=cpu['sum_time_reduction_pct'],wall_sum_time_reduction_pct=wall['sum_time_reduction_pct'],
        weak_cumulative_evidence=weak,source_files=708,object_headers_unchanged=674,verified_training_cases=12,
        all_formal_protocol_processes_finished=True,protected_user_files_unchanged=True,backup_receipt='checkpoint_receipt.json',
        next_candidate_implemented=False))
    save('next_candidates_review.json',dict(current_production_dll_sha256=actual,goal200_point_reached=reached,
        next_candidate_implemented=False,no_more_same_source_AB=True,profile_phase_pct=summary['replay_phase_pct'],
        attribution_not_speedup_or_ceiling=True,next_step='Finish verified archive; if below200, select the next candidate from current profiles',
        profile_receipt_sha256=sha(WORK/'profile_receipt.json')))
    state='20%换算点已达到200，等待远端完整备份收据确认后再结束目标' if reached else '200目标仍active、未完成，归档后继续下一轮'
    note=f'''

## private snapshots已部署（2026-11-24）

生产两处DLL现为`{actual}`，基线为已部署F950。组合仅改shard_00的14处私有循环和shard_12的两处native身份生成，新增native_private_snapshots.hpp；708源码完整复现，674对象头及布局不变。KindInt且<=1024直接生成原整数索引，其他类型及大值保留原迭代器；原数组长度快照及未来槽位实时读取保持。身份文本在原getter位置保存最多128字节原始快照，日志消费时才分配，超长／未知路径保持原后备。回调可修改源文本或中途开日志；RNG、fenv、旧计数、事件顺序均保持。

语义原型B13ECF通过固定200结果、自然终局及旧六计数，新增命中整数30901／文本快照34193。独立F950与候选实际DLL逐项差分143360事件场景和18432三Buff方法场景，另73088整数视图对原gd_iter_seq边界／活数组检查，总234880项全部通过，正式DLL在A/B前后重复通过。首次候选夹具启动因DLL内名称prototype.dll与复制名libgdcore.dll不符，Windows0xc0000135；仅修夹具加载、保留先前通过的基线逐项收据及失败日志，候选C++未更改。其后objdump对中文绝对路径失败，改检查ASCII目录内已复制DLL。所有记录保留，未发生正式计时。

完整20插桩、新18PGO完成，构建使用独立持久目录／私有scratch及最多2个BelowNormal任务，链接保留LTO中间文件。固定200单线程完整{installation['ab_pairs']}对CPU／墙钟配对中位耗时下降{cpu['paired_median_time_reduction_pct']:.4f}%／{wall['paired_median_time_reduction_pct']:.4f}%，累计耗时下降{cpu['sum_time_reduction_pct']:.4f}%／{wall['sum_time_reduction_pct']:.4f}%；累计证据偏弱={weak}。不追加同源组，不以历史标定点差值当代码收益。

2604场逐事件严格验收及新旧逐场事件hash全部一致，旧六计数保持。首raw24中位{serial['median_fights_per_second']:.4f}，极值{serial['minimum_fights_per_second']:.4f}–{serial['maximum_fights_per_second']:.4f}场/秒，全部达到50。独立cal24中位{cal['median_fights_per_second']:.4f}，极值{cal['minimum_fights_per_second']:.4f}–{cal['maximum_fights_per_second']:.4f}；20%负载换算{point:.4f}，负载覆盖{cal['background_load_range_pct'][0]:.4f}%–{cal['background_load_range_pct'][1]:.4f}%，全AC。R²={measure['r_squared_log_wall_time']:.6f}；每样本模型归一化值另存normalized20_sample_summary，不冒充实测20%批次。

正常训练12场匹配，安装后独立核验只执行一次且通过；旧F950运行时在{installation['backup_runtime']}。生产源码、DLL与生成配方已同步，用户六份文件保持。部署后采样{profile['samples']}栈，互斥阶段比例{json.dumps(summary['replay_phase_pct'],ensure_ascii=False)}，归属不是可兑现速度收益。{state}。实际状态见private_snapshots_bundle/current_runtime_status.json，远端备份以checkpoint_receipt.json为准；所有本轮计时和安装均已结束，不重启旧driver。
'''
    for name in ['C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md','C++模拟器优化交接_2026-11-23.md']:
        p=REPO/'docs'/name;text=p.read_text('utf8');assert '## private snapshots已部署（2026-11-24）' not in text
        lines=text.splitlines()
        if name=='C++模拟器优化交接_2026-11-23.md':
            lines[2]=f'> **当前生产为{actual[:8]}，private snapshots轮已验收部署；20%换算{point:.4f}，{state}。完整证据见文末，不重启旧driver。**'
        elif name=='C++模拟器下一阶段优化评估.md':
            lines[2]=f'日期：2026-11-24。当前已验收部署为{actual[:8]}，最新独立20%负载换算{point:.4f}场/秒，{state}。完整{installation["ab_pairs"]}对CPU／墙钟中位降耗{cpu["paired_median_time_reduction_pct"]:.4f}%／{wall["paired_median_time_reduction_pct"]:.4f}%；见文末完整证据。'
        p.write_text('\n'.join(lines)+'\n'+note,encoding='utf8',newline='\n')
    print(f'Recorded deployed{actual[:8]},20%={point:.4f};goal200 point reached={reached};backup still separately verified')

if __name__=='__main__':main()

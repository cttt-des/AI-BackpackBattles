"""Record the accepted weak-median round and preserve the remaining200-FPS goal."""
import hashlib
import json
from pathlib import Path
import statistics

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/object_routes_bundle'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(n):return json.loads((WORK/n).read_bytes())
def save(n,v):
    p=WORK/n;assert not p.exists();p.write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def main():
    check=read('post_install_verification.json');measure=read('measurements_summary.json');installation=read('bundle_installation.json')
    profile=read('profile_receipt.json');summary=read('brainstorm_profile_summary.json');review=read('pre_install_review.json')
    ab=read('ab_assessment_32.json');fit=read('bundle_load20.json')
    actual=check['dll_sha256'];assert actual=='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
    assert check['passed'] and actual==measure['dll_sha256']==profile['dll_sha256']==summary['dll_sha256']
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==actual
    assert not check['goal200_reached'] and installation['ab_pairs']==32
    assert all(sha(REPO/n)==h for n,h in review['protected_user_files_sha256'].items())
    cpu=ab['metrics']['main_thread_cpu_s'];wall=ab['metrics']['wall_s'];serial=measure['serial'];cal=measure['load_calibration']
    normalized=fit['estimated_fights_per_second_at_reference_load_by_sample'];assert len(normalized)==24
    save('normalized20_sample_summary.json',dict(dll_sha256=actual,derived_from_first_calibration_only=True,no_additional_timing=True,
        interpretation='Individual samples normalized with the same log-time fit; estimates, not direct24 observations at exactly20%',
        median=statistics.median(normalized),minimum=min(normalized),maximum=max(normalized),global_fitted_point=measure['fitted_fights_per_second_at20'],
        source_fit_sha256=sha(WORK/'bundle_load20.json')))
    save('current_runtime_status.json',dict(production_dll_sha256=actual,current_optimization='96 object instance routes plus original static context conversion',
        deployed=True,post_install_verified=True,goal200_reached=False,goal_still_active=True,
        fitted_fights_per_second_at20=measure['fitted_fights_per_second_at20'],raw24=serial,calibration24=cal,
        full32_cpu_median_reduction_pct=cpu['paired_median_time_reduction_pct'],full32_wall_median_reduction_pct=wall['paired_median_time_reduction_pct'],
        cumulative_cpu_time_change_pct=-cpu['sum_time_reduction_pct'],cumulative_wall_time_change_pct=-wall['sum_time_reduction_pct'],
        weak_evidence_note='Both paired medians improve under frozen final32 rule; cumulative times increase, not a robust large gain',
        all_formal_protocol_processes_finished=True,source_files=707,object_headers_unchanged=674,verified_training_cases=12,
        backup_receipt='checkpoint_receipt.json',backup_status_recorded_separately=True,next_candidate_implemented=False,
        next_work='Count actual CoreBuff integer iteration calls and lengths before implementing a bounded private iteration view',
        profile_receipt_sha256=sha(WORK/'profile_receipt.json'),protected_user_files_unchanged=True,
        preserved_original18_profiles_and_rebuilt20_release_after_temp_file_loss=True))
    save('next_candidates_review.json',dict(current_production_dll_sha256=actual,current_candidate_deployed=True,
        current_round_weak_dual_median_evidence=True,cumulative_both_improved=False,
        do_not_expand_method_routes_mechanically=True,no_same_source_AB_extension=True,
        next_candidate_implemented=False,next_step='Count only the14 private integer-loop sites in CoreBuff gainTemporary,loseStacks,onTimeout',
        static_review_sha256=sha(WORK/'future_integer_loop_review.json'),runtime_counts_not_yet_available=True,
        requirements=['Copy input once and retain original coercion/callback order','Prove private iteration containers do not escape',
            'Bound fast integer lengths and keep original huge/overflow fallback','Real arrays retain captured length and live future data reads',
            'Keep loop-value kinds,RNG,fenv,old six counters and all event ordering'],
        alternative_compiler_candidate=dict(flag='-fipa-pta',implemented=False,no_speed_claim=True),
        profile_receipt_sha256=sha(WORK/'profile_receipt.json'),profile_phase_pct=summary['replay_phase_pct'],
        attribution_not_speedup_or_ceiling=True))
    note=f'''

## object routes已部署与后续（2026-11-24）

生产两处DLL现为`{actual}`。从已验收80a0681c开始，仅修改gd_rt.cpp和native_resolved_dispatch.hpp：新增普通对象入口的96个实测热实例方法及CoreContext原静态_nativeF32调用。独立97槽侧表始终核对真实C++类型与原缓存行，不改旧128槽、65回调路由、674份对象头及任何原方法体；不进入FuncRef／literal入口，不额外观察对象、不重复旧审计。调用者ctx、原参数指针、RNG／IEEE／日志／回调顺序及旧六计数保持。

全20插桩／新18PGO训练已完成。原链接曾被手动中止，续链后又出现LTO输入不存在，核对发现普通Temp中的原对象及训练JSON等文件丢失，移除原因未确定。D盘保存的18份原计数逐份与丢失前快照一致，因此在独立CodexNativeBuilds目录重编release20单元，复用原18计数并保留链接临时产物；源码和浮点／优化策略不变，不重做训练。两次失败、丢失前快照、恢复依据和原PGO全部留档，没有一次正式计时被重启。

707份源码完整复现，所有前置回归通过。实际正式DLL的320,256项对象入口差分（74,496自定义C++覆写边界及245,760真实方法场景）在A/B前后均通过，10,240项主动确认新路由命中；保留126,192回调及5,184事件参数差分亦在前后通过。固定200新增实例901,392／静态转换88,491次，旧六计数完全相同；次数减少不是速度收益。

固定200单线程原24对后按冻结规则唯一追加8对。完整32对CPU／墙钟配对中位耗时降低{cpu['paired_median_time_reduction_pct']:.4f}%／{wall['paired_median_time_reduction_pct']:.4f}%，胜{cpu['candidate_wins']}／{wall['candidate_wins']}对，CPU有{cpu['ties']}对持平；累计耗时反增{-cpu['sum_time_reduction_pct']:.4f}%／{-wall['sum_time_reduction_pct']:.4f}%。按预先冻结的最终32对双中位规则采纳，但证据偏弱，不称稳定或大幅收益，不再追加同源组，也不以单组2%以上代替完整结果。

2,604场（914+1690）逐事件严格验收全通过，新旧C++逐场事件流全一致，根hash仍b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54。首份raw24中位{serial['median_fights_per_second']:.4f}、最低{serial['minimum_fights_per_second']:.4f}、最高{serial['maximum_fights_per_second']:.4f}场/秒，全部达到50门槛。独立校准24批中位{cal['median_fights_per_second']:.4f}、最低{cal['minimum_fights_per_second']:.4f}、最高{cal['maximum_fights_per_second']:.4f}；20%负载换算{measure['fitted_fights_per_second_at20']:.4f}。校准负载{cal['background_load_range_pct'][0]:.4f}%至{cal['background_load_range_pct'][1]:.4f}%，全AC，R²={measure['r_squared_log_wall_time']:.6f}，耗时相对误差中位{measure['fit_validation']['median_absolute_relative_time_error']*100:.4f}%、P90 {measure['fit_validation']['p90_absolute_relative_time_error']*100:.4f}%。不拿历史180.9931与本轮186.3403的差当作代码收益；每样本模型归一化统计另存normalized20_sample_summary.json，不混作实测20%批次。

正常训练12场与基线一致，安装后独立核验仅执行一次并通过；生产源码、DLL与生成配方已同步。旧80a0681c运行时在{installation['backup_runtime']}。实际状态见native_perf50/object_routes_bundle/post_install_verification.json及current_runtime_status.json；原candidate_decision.json的not_deployed为A/B决策时点，按原样保留。用户原有六份文件哈希不变，远端备份状态以本轮checkpoint_receipt.json为准。

200场/秒目标仍active、未完成。本轮所有正式计时及安装流程已结束，不重启旧driver。下一轮先量化CoreBuff私有整数循环的实际调用和长度，再决定有界整数迭代视图；保留大值／溢出／非整数后备、原数组的长度快照与未来槽位读取，以及所有RNG／fenv／旧计数。当前仅静态审查，尚未实现或测速；不继续机械扩张刚取得弱收益的方法侧表。
'''
    note+='\n部署后采样：'+str(profile['samples'])+'栈／'+str(profile['valid_replay_roots'])+'有效回放根，互斥阶段比例为'+json.dumps(summary['replay_phase_pct'],ensure_ascii=False)+'。归属不是可兑现收益或性能上限。\n'
    for name in ['C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md','C++模拟器优化交接_2026-11-23.md']:
        p=REPO/'docs'/name;text=p.read_text('utf8');assert '## object routes已部署与后续（2026-11-24）' not in text
        lines=text.splitlines()
        if name=='C++模拟器下一阶段优化评估.md':
            assert lines[2].startswith('日期：2026-11-24。当前已验收部署为80a0681c')
            lines[2]='日期：2026-11-24。当前已验收部署为f950b64c，最新独立20%负载换算186.3403场/秒，200目标仍active、未达到。对象路由完整32对CPU／墙钟配对中位降耗0.4339%／0.6507%，但累计耗时增加0.3173%／0.3357%，按冻结双中位规则采纳，证据偏弱；全部语义、吞吐及一次安装核验通过。下一轮先量化私有整数循环，见文末。'
        elif name=='C++模拟器优化交接_2026-11-23.md':
            assert lines[2].startswith('> **当前生产为80a0681c')
            lines[2]='> **当前生产为f950b64c…，object routes轮已按冻结规则验收部署；20%换算186.3403，200目标仍active、未完成。本轮中位小幅改善但累计略退化，见文末完整记录。旧构建／恢复／测速均已结束，不重启旧driver；下一轮仅开始量化整数循环。**'
        p.write_text('\n'.join(lines)+'\n'+note,encoding='utf8',newline='\n')
    print('Recordedf950b64c production,weak paired-median evidence and all original timings; full200-FPS goal remains active')

if __name__=='__main__':main()

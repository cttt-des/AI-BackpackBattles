"""Record the complete accepted round without replacing historical decisions."""
import json
from prepare_native_callback_dispatch import STAGE,sha

WORK=STAGE/'native_perf50/callback_dispatch_bundle'
REPO=STAGE.parents[1]

def read(n):return json.loads((WORK/n).read_bytes())
def save(n,v):
    p=WORK/n;assert not p.exists();p.write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def main():
    check=read('post_install_verification.json');measurement=read('measurements_summary.json')
    profile=read('profile_receipt.json');summary=read('brainstorm_profile_summary.json');review=read('pre_install_review.json')
    actual=check['dll_sha256']
    assert check['passed'] and actual==measurement['dll_sha256']==profile['dll_sha256']==summary['dll_sha256']
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==actual
    assert not check['goal200_reached']
    assert all(sha(REPO/n)==h for n,h in review['protected_user_files_sha256'].items())
    save('current_runtime_status.json',dict(production_dll_sha256=actual,current_optimization='65 exact-type extra callback routes and literal spans',
        deployed=True,post_install_verified=True,goal200_reached=False,goal_still_active=True,
        fitted_fights_per_second_at20=measurement['fitted_fights_per_second_at20'],raw24=measurement['serial'],
        calibration24=measurement['load_calibration'],all_formal_protocol_processes_finished=True,
        source_files=707,object_headers_unchanged=674,verified_training_cases=12,
        backup_receipt='checkpoint_receipt.json',backup_status_recorded_separately=True,
        next_candidate_implemented=False,next_work='Measure real receiver types for residual generic object method calls; prioritize an actually hot closed route',
        profile_receipt_sha256=sha(WORK/'profile_receipt.json'),protected_user_files_unchanged=True))
    save('next_candidates_review.json',dict(current_production_dll_sha256=actual,current_candidate_deployed=True,
        current_round_final32_cpu_median_reduction_pct=.46511627906976605,
        current_round_final32_wall_median_reduction_pct=.8974676785460323,
        no_local_work_during_formal_timing=True,next_candidate_implemented=False,
        highest_priority=dict(name='Residual generic object calls: receiver type and method census',
            prior_count=1456961,prior_dll_sha256='c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1',
            existing65_callback_methods_only268_hits=True,
            require_new_production_probe=True,no_speed_forecast_from_count=True,
            preservation=['actual C++ overrides and copied/invalid rows','read/observe/callback order','RNG and IEEE arithmetic order','old six counters and mutable argument aliases']),
        rejected_hypothesis=dict(name='Bound argument concatenation',observed_bound_concatenations=0,no_implementation_planned=True),
        alternatives=[dict(name='Private integer range iteration view',implemented=False),
            dict(name='Snapshot bounded event identity bytes before callbacks',implemented=False),
            dict(name='Separate -fipa-pta compiler trial preserving floating flags',implemented=False)],
        profile_receipt_sha256=sha(WORK/'profile_receipt.json'),profile_phase_pct=summary['replay_phase_pct'],
        attribution_not_speedup_or_ceiling=True))
    note='''

## callback dispatch已部署与后续（2026-11-24）

生产两处DLL现为`80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a`。从已验收c46cc19c开始，新增65个实际命中的旧表外无绑定回调路由，通过独立侧表及始终执行的实际C++类型检查直达原方法，并允许私有literal参数继续按值传递。原128槽方法表及674份对象头不变；未知、错误／复制行和C++覆写保留原虚方法。仅改gd_rt.cpp、native_event_kernel.hpp及native_resolved_dispatch.hpp，保留原方法、浮点／RNG／日志／观察顺序、旧六计数和活参数别名。

完整20单元插桩、新18热单元PGO、707源码再生成及保留回归均通过。实际正式DLL的126,192项回调独立差分和5,184项事件参数差分在A/B前后均通过，含15,600项C++覆写边界及3,072项主动不物化断言。前置验收复制脚本遗留旧指纹和旧基线导入已修正，原始两次失败记录及通过的部分结果保留，候选DLL和模拟器源码未因此改变或重建；没有重启或重复正式计时。

固定200单线程原24对后按冻结规则唯一追加8对。完整32对CPU／墙钟配对中位耗时降低0.4651%／0.8975%，累计耗时降低2.6721%／3.2730%，胜18／19对，CPU有2对持平。四组中第二组退化；最终逐组留一的两项中位和累计值仍全为正。原24对、唯一追加8对和所有原始批次全部保留，不再追加同源码组。

2,604场（914+1690）逐事件严格验收全部通过，新旧C++逐场事件流全一致，根hash仍b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54。首份raw24中位164.9267、最低80.8447、最高224.8275场/秒，全部达到50门槛。独立校准24批中位181.9167、最低165.4584、最高220.3736，20%负载换算180.9931场/秒；实际负载5.1669%至29.4224%，全AC，R²=0.938659，耗时相对误差中位1.4944%、P90 4.2509%。跨轮校准环境不同，不以历史120.6721与本轮180.9931的差计算代码收益。

正常训练12场与基线一致，安装后独立核验仅执行一次并通过，源码和生成配方已同步。旧c46cc19c运行时保留于dist/native_1_1_10_before_callback_dispatch_bundle_20261123。实际状态见native_perf50/callback_dispatch_bundle/post_install_verification.json和current_runtime_status.json；原candidate_decision.json的not_deployed是A/B决策时点，按原样保留。18份原PGO计数已逐份核对并冻结，用户原有六份修改／文件哈希保持。

20%负载200场/秒目标仍active，未完成。本轮所有正式进程已结束，不重启旧driver。绑定拼接假设已被实际0次命中推翻；下一轮先量化剩余普通对象通用调用的实际接收类型和方法，再选择热路径，不能把旧65个回调直接扩大到全部对象（此前1,456,961次中仅268次命中这65项）。尚未实现下一轮；私有整数迭代、受控身份字节快照及PTA编译仍为备选，不称已有收益。远端备份是否完成以本轮checkpoint_receipt.json为准。
'''
    note+='\n部署后采样：'+str(profile['samples'])+'栈／'+str(profile['valid_replay_roots'])+'有效回放根，互斥阶段比例为'+json.dumps(summary['replay_phase_pct'],ensure_ascii=False)+'。采样归属不是收益或性能上限。\n'
    for name in ['C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md','C++模拟器优化交接_2026-11-23.md']:
        p=REPO/'docs'/name;text=p.read_text('utf8');assert '## callback dispatch已部署与后续（2026-11-24）' not in text
        lines=text.splitlines()
        if name=='C++模拟器下一阶段优化评估.md':
            assert lines[2].startswith('日期：2026-11-23。当前已验收部署为c46cc19c')
            lines[2]='日期：2026-11-24。当前已验收部署为80a0681c，最新独立20%负载换算180.9931场/秒，200目标仍active、未达到。回调分派完整32对CPU／墙钟配对中位降耗0.4651%／0.8975%，累计降耗2.6721%／3.2730%；语义、吞吐及安装核验通过。当前状态及下一轮评估见文末；跨轮标定差不代表代码收益。'
        elif name=='C++模拟器优化交接_2026-11-23.md':
            assert lines[2].startswith('> **当前生产为c46cc19c')
            lines[2]='> **当前生产为80a0681c…，callback dispatch轮已验收部署；20%换算180.9931，200目标仍active、未达到。原交接正文及旧活动轮为历史，请优先读文末“callback dispatch已部署与后续”。所有本轮正式进程已结束，不重启旧driver。**'
        p.write_text('\n'.join(lines)+'\n'+note,encoding='utf8',newline='\n')
    print('Recorded80a0681c production; full200-FPS goal remains active')

if __name__=='__main__':main()

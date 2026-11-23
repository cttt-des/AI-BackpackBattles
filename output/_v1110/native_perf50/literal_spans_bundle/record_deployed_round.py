"""Record the verified deployment and remaining full200-FPS objective."""
import hashlib
import json
from pathlib import Path

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(name):return json.loads((WORK/name).read_bytes())

def main():
    deployed=read('post_install_verification.json');measurement=read('measurements_summary.json')
    profile=read('profile_receipt.json');summary=read('brainstorm_profile_summary.json')
    actual=sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')
    assert deployed['passed'] and actual==deployed['dll_sha256']==profile['dll_sha256']==measurement['dll_sha256']
    assert actual==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==sha(WORK/'bundle.dll')
    assert not deployed['goal200_reached'] and deployed['strict_event_cases']==2604
    assert summary['dll_sha256']==actual
    status=dict(production_dll_sha256=actual,current_optimization='literal event argument spans',
        deployed=True,post_install_verified=True,goal200_reached=False,goal_still_active=True,
        fitted_fights_per_second_at20=measurement['fitted_fights_per_second_at20'],
        raw24=measurement['serial'],calibration24=measurement['load_calibration'],
        all_formal_protocol_processes_finished=True,source_files=707,object_headers_unchanged=674,
        verified_training_cases=12,backup_receipt='checkpoint_receipt.json',
        backup_status_recorded_separately=True,next_candidate_implemented=False,
        next_work='Count real bound-argument lengths; evaluate local temporary concatenation and lazy bound spans',
        profile_receipt_sha256=sha(WORK/'profile_receipt.json'))
    out=WORK/'current_runtime_status.json';assert not out.exists()
    out.write_text(json.dumps(status,indent=2)+'\n',encoding='utf8')
    note='''

## literal spans已部署与后续（2026-11-23）

生产两处DLL现为`c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1`。12处私有事件字面量采用按值span，排队／不透明／绑定回调前才物化原形数组；一旦物化，后续回调始终使用活数组。保留全部公开方法、日志顺序、监听器长度快照与未来槽位、别名、RNG、浮点顺序及旧计数。未继承storage失败组合。

完整20单元插桩、新18热单元PGO、707份源码再生成，以及所有保留回归均通过。正式DLL的5,184项定向差分在A/B前后各通过一次；48项主动确认不物化。固定200单线程首24对未满足直接采纳，按冻结规则唯一追加8对；全部32对CPU／墙钟配对中位降耗1.7469%／1.4170%，累计降耗1.7547%／2.1021%，胜18／19对。四组中一组退化，但最终逐组留一敏感性下两项中位及累计值均保持正向；不以单组5%以上代替完整结果，也不为同源码追加组。

2,604场（914+1690）原版逐事件严格验收全通过，旧新C++逐场事件流全一致，根hash仍`b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54`。首份raw24中位117.1192、最低65.4304、最高137.0703场/秒，全部达到50门槛；独立校准24批中位104.4447、最低59.3472、最高123.7272，20%负载插值为120.6721场/秒。校准实际负载18.8173%至65.0042%，全AC，R²=0.953959，耗时相对误差中位2.3471%、P90 5.9486%。不拿不同轮次的拟合值相减宣布代码收益。

正常训练12场与旧版一致，安装后的独立核验只运行一次并通过，674份对象头布局不变，生成配方已同步。旧d8a736运行时保留在`dist/native_1_1_10_before_literal_spans_bundle_20261123`。目录`native_perf50/literal_spans_bundle`，实际部署状态读`post_install_verification.json`及`current_runtime_status.json`；原`candidate_decision.json`的not_deployed是A/B判定时点，未覆盖旧记录。18份原PGO计数已按构建收据逐份校验并保存。

200场/秒目标仍active，未完成。本轮构建、A/B、strict、raw24与校准进程均已结束，不重启旧driver。下一轮优先量化`GdFuncRef::call_func`绑定参数的临时std::vector拼接及长度分布，再评估短参数栈上合并，并保留观察对象／绑定读取／分派计数顺序；当前尚未实现或测速。PTA编译分析、私有整数迭代视图等仅为备选，不称已取得收益。远端备份状态以本目录`checkpoint_receipt.json`为准。
'''
    note += '\n部署后采样：'+str(profile['samples'])+'栈／'+str(profile['valid_replay_roots'])+'有效回放根，互斥阶段比例为'+json.dumps(summary['replay_phase_pct'],ensure_ascii=False)+'。归属不等于可兑现收益或性能上限。\n'
    for name in ('C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md','C++模拟器优化交接_2026-11-23.md'):
        path=REPO/'docs'/name;text=path.read_text('utf8')
        assert '## literal spans已部署与后续（2026-11-23）' not in text
        if name=='C++模拟器下一阶段优化评估.md':
            lines=text.splitlines();assert lines[2].startswith('日期：2026-11-23。当前已验收部署为d8a736')
            lines[2]='日期：2026-11-23。当前已验收部署为c46cc19c，最新独立20%负载换算120.6721场/秒，200目标仍active、未达到。事件字面量参数span完整32对CPU／墙钟配对中位降耗1.7469%／1.4170%，累计降耗1.7547%／2.1021%；语义、吞吐和部署门槛全通过。当前状态及采样见文末；历史标定之间的差不代表代码收益。'
            text='\n'.join(lines)+'\n'
        elif name=='C++模拟器优化交接_2026-11-23.md':
            lines=text.splitlines();assert lines[2].startswith('> **接手后已更新：当前生产为d8a736')
            lines[2]='> **当前生产为c46cc19c…，literal spans轮已验收部署；20%换算120.6721，200目标仍active、未达到。原交接正文（含“已暂停”及旧DLL）为历史状态，请优先读文末“literal spans已部署与后续”。下一轮状态以最新记录及实际进程为准，不重启旧driver。**'
            text='\n'.join(lines)+'\n'
        path.write_text(text+note,encoding='utf8',newline='\n')
    review=read('next_candidates_review.json')
    review.update(current_production_dll_sha256=actual,current_candidate_deployed=True,
                  profile_receipt_sha256=sha(WORK/'profile_receipt.json'),next_candidate_still_unimplemented=True)
    (WORK/'next_candidates_review.json').write_text(json.dumps(review,indent=2)+'\n',encoding='utf8')
    print('Recorded verified c46cc19c production; full200-FPS goal remains active')

if __name__=='__main__':main()

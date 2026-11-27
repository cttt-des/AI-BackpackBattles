"""Write one honest terminal record from all preserved measurements and gates."""
import json
from prepare_frame_guard_reuse import REPO,WORK,BASE,EXPECTED,sha,save,verify_projection
from install_ordering_correctness import boundary
def main():
    def read(n):return json.loads((WORK/n).read_bytes())
    decision=read('candidate_decision.json');measurement=read('measurements_summary.json');assessment=read(decision['selected_assessment']);deployed=(WORK/'installation.json').exists()
    assert measurement['dll_sha256']==sha(WORK/'bundle.dll') and read('complete_correctness_gate.json')['passed'];boundary()
    if deployed:
        assert decision['accepted'] and read('post_install_verification.json')['passed'] and sha(BASE/'libgdcore.dll')==sha(WORK/'bundle.dll');verify_projection(BASE)
    else:assert sha(BASE/'libgdcore.dll')==EXPECTED
    reason='deployed_after_all_gates' if deployed else 'raw24_gate_failed' if decision['accepted'] else 'paired_AB_not_accepted'
    save('current_runtime_status.json',dict(deployed=deployed,reason=reason,production_dll_sha256=sha(BASE/'libgdcore.dll'),candidate_dll_sha256=sha(WORK/'bundle.dll'),AB_status=decision['status'],all_protocol_processes_finished=True,no_same_source_retiming=True,other_optimization_directions_not_started=True,remaining_backup_required=True))
    cpu=assessment['metrics']['main_thread_cpu_s'];wall=assessment['metrics']['wall_s'];speed=measurement['fitted_fights_per_second_at20']
    note=REPO/'docs/C++模拟器逐帧类型守卫复用优化记录_2026-11-27.md';assert not note.exists()
    deployment_text='正收益后再次完成实际135168、原版排序／事件／药水和全2604场逐事件验收；首raw24与唯一独立cal24完成后部署，安装后的真实DLL135168及训练器12作业再次通过。' if deployed else 'A/B通过但首raw24未达到原有发布门槛，未部署；全部首raw24和独立cal24原样保留，没有挑样重测。' if decision['accepted'] else '没有正收益部署；唯一cal24仅作非发布记录，不冒充发布raw24。正式通过的语义检查和全部退化／不确定计时完整保留。'
    text=f'''# 逐帧类型守卫复用优化记录（2026-11-27）

本轮{'通过验收并已部署' if deployed else '未部署，保留修复后的原生产版本'}。候选 `{sha(WORK/'bundle.dll')}`，原基线 `{EXPECTED}`。A/B 终态 `{decision['status']}`。

## 选择与范围

先对完成排序／事件派发修复的真实生产 DLL 重新采样：2000 个栈，最大单个叶热点为 `native_frame_segment_tick`（177 样本）。实际机器码仍重复读取上下文／方法行，并在审计开启时重复执行精确类型行检查。采样归属不等于可兑现收益或上限。此前两轮武器整链定型均未通过 A/B，没有重跑旧方案。

仅修改 `native_inline_dispatch.hpp` 的冷却热链：入口已验证的方法行，在首次用户回调之前的一段纯字段读取／标量转换／诊断计数代码内复用，通过原类型掩码的 Gem 位判断类型；原成功类型查询计数仍在原位置递增。没有跨回调、跨物品或跨帧缓存。未知行、空行和审计失败仍走原入口后备。原回调后的分派与重新验证不变。

精确逆变换还原原基线的715个目录文件，674对象头及全部布局不变；排序修复与三条实时监听数组派发循环完整保留。两次完整转译和性能流水线均重现710份C++文件，重复字节／mtime不变，未知修改在写入前拒绝。

## 验证

新增135168项，使用 GetProcAddress 调用各真实 DLL 中的生产帧函数，避免把 EXE 内重新实例化的头文件助手冒充 DLL 生产实现。覆盖原18种场景及回调中更改下一物品方法行、失效行、关闭分派、关闭收集等4种场景；四种舍入方式×四种DAZ/FTZ状态。完整状态、RNG、fenv、MXCSR及27个原计数逐例一致。普通原型与同源普通基线比较；正式PGO与独立生产02fd比较。

所有继承的定向检查保留，武器136128项严格与当前生产版本完全一致，不再使用前轮针对修复差异的分例真值合并。原版Godot256组排序、18种事件场景的普通／原生／字面量路径、药水腰带／嵌套及60组未注入终序的开战对照均保持。完整2604场逐事件、来源及类型审计通过。

正式构建为完整20单元插桩、18份新profile和18热单元PGO/LTO，所有原浮点选项保持；20对象和18实际LTO选项已核对。原型复用19个已核对源码与字节的普通对象，仅重编唯一消费分片03，不用于速度或部署结论。

## 全部计时与决策

预声明24对，只有首24不确定或去掉一组后的中位方向不正才允许唯一8对补充；最终保留全部{decision['pairs']}对及所有极值。CPU／墙钟配对中位耗时降低 **{cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%**；累计降低 {cpu['sum_time_reduction_pct']:.6f}%／{wall['sum_time_reduction_pct']:.6f}%。不以单组最好值或不同时段的绝对FPS差作为代码收益。

{deployment_text}

20%负载经验点约 **{speed:.4f} 场/秒**，{'外推' if measurement['reference_is_extrapolation'] else '插值'}，R²={measurement['r_squared_log_wall_time']:.6f}。使用原经验模型 log(墙钟秒数)=a+b×负载；未将20%区间覆盖或低负载等待设为门槛，没有重做同源计时挑选结果。旧200场/秒目标不作为本轮完成条件。

## 保存与边界

证据目录 `output/_v1110/native_perf50/frame_guard_reuse_bundle`；新采样位于 `post_ordering_assessment`。用户原有文件、暂存区与工作区HEAD保留，沿用既有 `codex/native-perf50-verified` 备份引用，不创建新分支。远端上传结果以 `checkpoint_receipt.json` 为准。

本轮只评估这一项优化，没有改用事件流架构，也没有恢复此前失败的预取、PTA或整链内联实验。
'''
    note.write_text(text,encoding='utf8',newline='\n');print(str(note),flush=True)
if __name__=='__main__':main()

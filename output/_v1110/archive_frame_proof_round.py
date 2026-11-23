"""Close unavailable load20 honestly, then preserve the complete fixed32 trial."""
import ast
import json
from prepare_native_frame_proof import STAGE,EXPECTED,sha,once
WORK=STAGE/'native_perf50/frame_proof_bundle'

def main():
    assessment=json.loads((WORK/'ab_assessment_32.json').read_bytes())
    cal=json.loads((WORK/'rejected_load_calibration.json').read_bytes())
    loads=[x['background_load_pct'] for x in cal['samples']]
    assert min(loads)>20 and len(loads)==24
    receipt=dict(candidate_dll_sha256=sha(WORK/'bundle.dll'),status='not_adopted_inconclusive',selected_pairs=32,
        main_thread_cpu_time_reduction_pct=assessment['metrics']['main_thread_cpu_s']['paired_median_time_reduction_pct'],
        wall_time_reduction_pct=assessment['metrics']['wall_s']['paired_median_time_reduction_pct'],
        candidate_fitted_at20_fps=None,load20_unavailable_reason='20% outside observed background load; no extrapolation',
        calibration_load_range_pct=[min(loads),max(loads)],current_runtime_dll_sha256=EXPECTED,
        no_more_same_source_comparisons=True,strict2604_not_started=True,release_raw24_not_started=True,
        reports_sha256={name:sha(WORK/name) for name in ('candidate_decision.json','ab_assessment_32.json','rejected_load_calibration.json','frame_proof_tests.json')})
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==EXPECTED
    out=WORK/'rejection_receipt.json';assert not out.exists();out.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    note='''
## 帧入口证明／Bool组合正式结论：32对未证实提速，未部署

正式DLL`785834d760f4eeb71b8bfec40c07da9f128f21a314bc6a7246ead592216d91af`通过保留回归、最终3,073项实际DLL差分、固定200和原frame／type计数、完整再生成。首24对不明确，按预定规则仅追加8对，全部32对CPU／墙钟配对中位耗时增加1.3238%／2.3654%，累计增加0.6940%／0.7468%，各14胜18负。分组方向不一致，结论为未证实有效；没有挑选有利子集，不再追加同源测速，未启动2,604或发布raw24，生产仍e0bedc。

恢复工作后首次24批独立校准全程接电，后台负载91.8054%–95.8831%，20%不在实测区间，拟合工具已拒绝外推；本轮20%速度记为缺测，保留全部原始数据和失败日志，不用上一轮174.4918替代本轮。下一候选改为实际减少事件小字典分配次数，并评估帧kernel内联；容量从8变4与本轮检查组合均不直接合入。[完整32对](../output/_v1110/native_perf50/frame_proof_bundle/ab_assessment_32.json) · [校准原始数据](../output/_v1110/native_perf50/frame_proof_bundle/rejected_load_calibration.json)
'''
    for name in ('C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md'):
        p=STAGE.parents[1]/'docs'/name;p.write_text(p.read_text('utf8')+note,encoding='utf8')
    t=(STAGE/'save_rejected_display_defaults.py').read_text('utf8')
    t=t.replace("WORK=STAGE/'native_perf50/display_defaults_bundle'","WORK=STAGE/'native_perf50/frame_proof_bundle'")
    t=t.replace("PREVIOUS='e53ca96c4e96c9bc7dabd8aee4122f76fe572f1e'","PREVIOUS='1b18298e39ed36f0fd0dbe5d0e00699d9407c643'")
    t=t.replace("rejection['selected_pairs']==24","rejection['selected_pairs']==32")
    start=t.index('    paths=set()');end=t.index('    relative=sorted',start)
    t=t[:start]+'''    paths=set()
    for folder in ('frame_proof_prototype','frame_proof_bundle'):
        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file() and '__pycache__' not in p.parts and not p.name.startswith('checkpoint'))
    paths.update(STAGE/name for name in ('prepare_native_frame_proof.py','setup_native_frame_proof_checks.py',
        'build_native_frame_proof_prototype.py','test_native_frame_proof.cpp','verify_native_frame_proof.py',
        'prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py',
        'close_frame_proof_round.py','archive_frame_proof_round.py','save_rejected_frame_proof.py'))
    paths.update(STAGE.glob('native_frame_proof*.log'))
    paths.update(REPO/'docs'/name for name in ('C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md'))
'''+t[end:]
    t=t.replace('perf: retain rejected packed display trials and owned-frame guard review','perf: retain complete inconclusive32 tick-proof trials')
    t=t.replace('backup: retain rejected display trials; keep verified e0bedc runtime','backup: retain inconclusive tick-proof trials; keep verified e0bedc runtime')
    ast.parse(t);(STAGE/'save_rejected_frame_proof.py').write_text(t,encoding='utf8')
    print(json.dumps(receipt,indent=2))

if __name__=='__main__':main()

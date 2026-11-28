"""Sequentially finish the already authorized candidate and milestone backup."""
import json,subprocess,sys,time
from pathlib import Path
import psutil
from prepare_timeline_round import STAGE,REPO,WORK,BASE,EXPECTED,sha,save,verify_projection
from install_ordering_correctness import boundary
ROUND=WORK.parent
def read(name):return json.loads((WORK/name).read_bytes())
def wait_process(live):
    while True:
        try:alive=abs(psutil.Process(live['pid']).create_time()-live['created'])<.01
        except psutil.NoSuchProcess:alive=False
        if not alive:return
        time.sleep(5)
def run(script,*args,log):
    path=WORK/log;attempt=1
    while path.exists():attempt+=1;path=WORK/(Path(log).stem+f'_attempt{attempt}'+Path(log).suffix)
    print('Starting '+script+' '+' '.join(args),flush=True)
    with path.open('xb') as stream:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'run_native_managed.py'),str(STAGE/script),*args],stdout=stream,stderr=subprocess.STDOUT,check=True)
def close():
    boundary();decision=read('candidate_decision.json');deployed=(WORK/'installation.json').exists();actual=sha(WORK/'bundle.dll');production=sha(BASE/'libgdcore.dll');assert production==(actual if deployed else EXPECTED)
    assert read('complete_correctness_gate.json')['optimization_enabled_full2604'];verify_projection(WORK/'bundle_src')
    a=read('ab_assessment.json');cpu=a['metrics']['main_thread_cpu_s'];wall=a['metrics']['wall_s'];coverage=read('complete_correctness_gate.json')['coverage']
    result=dict(all_three_directions_have_execution_decisions=True,all_protocol_processes_finished=True,deployed=deployed,baseline_dll_sha256=EXPECTED,candidate_dll_sha256=actual,production_dll_sha256=production,direction1='no_go_live_invariant_margin',direction2='no_go_current_watch_frontier_design',direction3=decision['status'],CPU_time_reduction_pct=cpu['paired_median_time_reduction_pct'],wall_time_reduction_pct=wall['paired_median_time_reduction_pct'],semantic_full2604=True,optimized_coverage=coverage,awaiting_milestone_backup=True)
    (ROUND/'round_completion.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    note=REPO/'docs/C++模拟器三方向接手与类型化时间线候选_2026-11-28.md';text=note.read_text('utf8');assert '## 最终候选结论' not in text
    text=text.replace('本页会随候选验收结果更新，目前候选仍在构建／验证阶段，不代表已获整场收益或已部署。','本轮已完成三个方向的执行结论；正式候选验收、整场A/B与部署结果见文末。')
    text+='\n## 最终候选结论\n\n'
    text+=f"正式候选 DLL `{actual}` 完成全新完整插桩／18热单元PGO，编译选项与CEA除profile目录外一致。正式DLL重新执行受影响的74,448个实际DLL定向对照及6个自定义容器回归场景，并完成一次实际启用优化的2,604场严格逐事件验收。优化覆盖：`{coverage}`。没有为同一DLL在A/B后或复制后重跑完整语料。\n\n"
    text+=f"冻结两会话共24四元组的CPU／墙钟配对中位耗时降低分别为 {cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，判定 `{decision['status']}`。全部首批样本、失败和极值、两会话方向、block2／3置信区间与A/A包络均保留在候选目录。\n\n"
    text+=('收益及绝对运行门槛通过，已经部署，并按DLL／源码SHA与12场训练短运行核对安装。' if deployed else '没有满足全部部署门槛，保持CEA生产DLL。局部原型收益未冒充整场收益。')+'\n\n'
    if (WORK/'measurements_summary.json').exists():
        m=read('measurements_summary.json');text+=f"20%负载经验公式估计 {m['fitted_fights_per_second_at20']:.4f} 场／秒，采用{'外推' if m['reference_is_extrapolation'] else '插值'}，log墙钟拟合R²={m['r_squared_log_wall_time']:.6f}，不以是否实际测到字面20%作为门槛。\n\n"
    text+='三个方向本轮均形成有依据的执行结论。阶段证据按既有备份ref批量归档；不新增分支、不移动HEAD、不改用户暂存条目，根目录受保护DLL与原版脚本未改。\n'
    note.write_text(text,encoding='utf8',newline='\n')
    p=ROUND/'assessment_progress.json';progress=json.loads(p.read_bytes());progress.update(goal_status='execution_finished_archive_pending',final_result=result);p.write_text(json.dumps(progress,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    p=ROUND/'checkpoint_resume.json';checkpoint=json.loads(p.read_bytes());checkpoint.update(goal_status='execution_finished_archive_pending',phase='All three execution decisions; final2604 and frozenAB complete; milestone backup pending',formal_PGO=True,formal_AB=True,deployment=deployed,current_round_not_yet_backed_up=True);p.write_text(json.dumps(checkpoint,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);boundary()
    if (WORK/'live_normal_build.json').exists():wait_process(read('live_normal_build.json'))
    assert (WORK/'prototype_build.json').exists()
    if not (WORK/'prototype_affected_tests.json').exists():run('verify_timeline_affected.py',log='prototype_affected_first.log')
    if not (WORK/'prototype_container_receipt.json').exists():run('verify_timeline_container.py','--dll',str(WORK/'prototype.dll'),'--tag','prototype',log='prototype_container_first.log')
    if not (WORK/'prototype_real200_coverage.json').exists():run('probe_timeline_real200.py',log='prototype_real200_first.log')
    if not (ROUND/'r3_prototype_rows_resume_probe_receipt.json').exists():run('probe_architecture_resume.py','row_guard','--dll',str(WORK/'prototype.dll'),'--tag','r3_prototype_rows',log='prototype_rows_first.log')
    if not (WORK/'compiled_option_receipt.json').exists():
        if (WORK/'live_formal_build.json').exists():wait_process(read('live_formal_build.json'))
        else:run('timeline_round.py','formal',log='formal_build_first.log')
    assert (WORK/'compiled_option_receipt.json').exists(),'Formal build exited without its completion receipt'
    if not (WORK/'formal_affected_tests.json').exists():run('verify_timeline_affected.py','--formal',log='formal_affected_first.log')
    if not (WORK/'formal_container_receipt.json').exists():run('verify_timeline_container.py','--dll',str(WORK/'bundle.dll'),'--tag','formal',log='formal_container_first.log')
    if not (ROUND/'r3_formal_rows_resume_probe_receipt.json').exists():run('probe_architecture_resume.py','row_guard','--dll',str(WORK/'bundle.dll'),'--tag','r3_formal_rows',log='formal_rows_first.log')
    if not (WORK/'complete_correctness_gate.json').exists():run('verify_timeline_full.py',log='formal_full_first.log')
    if not (WORK/'ab_timing_complete.json').exists():run('timeline_round.py','timing',log='formal_AB_first.log')
    if not (WORK/'candidate_decision.json').exists():run('timeline_round.py','analyze',log='formal_AB_analysis.log')
    if read('candidate_decision.json')['accepted']:
        if not (WORK/'measurements_summary.json').exists():run('measure_timeline_round.py',log='raw24_cal24_first.log')
        if read('measurements_summary.json')['raw24_gate_passed'] and not (WORK/'installation.json').exists():run('install_timeline_round.py',log='installation_first.log')
    if not (ROUND/'round_completion.json').exists():close()
    run('archive_architecture_resume.py',log='architecture_archive_first.log')
    receipt=json.loads((ROUND/'checkpoint_receipt.json').read_bytes());assert receipt['remote_upload_verified'];boundary()
    result=json.loads((ROUND/'round_completion.json').read_bytes());result.update(awaiting_milestone_backup=False,remote_verified_commit=receipt['remote_verified_commit'],all_required_work_complete=True)
    (ROUND/'goal_completion_receipt.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf8');print('All required work and verified backup complete',json.dumps(result,ensure_ascii=False),flush=True)
if __name__=='__main__':main()

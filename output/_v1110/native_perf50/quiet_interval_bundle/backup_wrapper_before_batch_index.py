"""Close and back up the architecture experiment on the existing ref only."""
import json,sys
from prepare_quiet_round import REPO,STAGE,WORK,BASE,EXPECTED,sha,save,inventory,ACCEPTED
from install_ordering_correctness import boundary

def close():
    boundary();decision=json.loads((WORK/'candidate_decision.json').read_bytes());speed=json.loads((WORK/'measurements_summary.json').read_bytes());deployed=(WORK/'installation.json').exists()
    assert sha(BASE/'libgdcore.dll')==(sha(WORK/'bundle.dll') if deployed else EXPECTED)
    assert json.loads((WORK/'complete_correctness_gate.json').read_bytes())['optimization_enabled_full2604']
    save('current_runtime_status.json',dict(deployed=deployed,production_dll_sha256=sha(BASE/'libgdcore.dll'),candidate_dll_sha256=sha(WORK/'bundle.dll'),AB_status=decision['status'],all_protocol_processes_finished=True,no_same_source_retiming=True,remaining_backup_required=True))
    a=json.loads((WORK/decision['selected_assessment']).read_bytes());cpu=a['metrics']['main_thread_cpu_s'];wall=a['metrics']['wall_s'];directed=json.loads((WORK/'formal_quiet_core_tests.json').read_bytes());coverage=directed['exercised_core_counts'];full=json.loads((WORK/'formal_quiet_fast_full_tests.json').read_bytes())
    note=REPO/'docs/C++模拟器空帧与局部事件流架构评估_2026-11-27.md';text=note.read_text('utf8');assert '## 本轮验证结果' not in text
    text+='\n## 本轮验证结果\n\n'
    text+=f"正式 DLL `{sha(WORK/'bundle.dll')}` 通过 {directed['cases']:,} 个实际 DLL 定向状态／浮点对照和全部保留检查。固定 200 场实际优化 {coverage['frames']} 个战斗帧；全部 2,604 场优化启用的严格原版逐事件对照通过，共运行 {full['coverage']['frames']} 个优化帧。独立审计路径也完成全部语料、排序／药水／派发及原有计数验证。\n\n"
    text+=f"冻结 24 四元组 A/B 的 CPU／墙钟中位耗时降低分别为 {cpu['paired_median_time_reduction_pct']:.6f}%／{wall['paired_median_time_reduction_pct']:.6f}%，判定 `{decision['status']}`；全部原始样本、两个会话方向、A/A 门槛和区间见 `ab_assessment.json`。"
    text+=('收益及全部部署门槛通过后已部署，并完成部署后实际 DLL 与训练检查。' if deployed else '未确认可信正收益，因此保持生产 DLL 不变。')+'\n\n'
    text+=f"20% 负载经验估计为 {speed['fitted_fights_per_second_at20']:.4f} 场／秒，采用{'外推' if speed['reference_is_extrapolation'] else '插值'}，log 墙钟拟合 R²={speed['r_squared_log_wall_time']:.6f}。模型误差及全部样本单独保留；跨轮归一化 FPS 不用作代码收益判据。\n"
    note.write_text(text,encoding='utf8',newline='\n');save('documentation.json',dict(path=note.relative_to(REPO).as_posix(),sha256=sha(note)))

def archive(upload=False):
    import psutil
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    text=(STAGE/'archive_frame_guard.py').read_text('utf8').replace('from prepare_frame_guard_reuse import','from prepare_quiet_round import')
    text=text.replace("['git',*args]", "['git','-c','pack.threads=2',*args]")
    text=text.replace("['git','-c','http.connectTimeout=10'", "['git','-c','pack.threads=2','-c','http.connectTimeout=10'")
    old="paths=set(STAGE.glob('*frame_guard*.py'));paths.add(STAGE/'profile_post_ordering.py')";assert old in text
    new="paths=set(STAGE.glob('*quiet*.py'));paths.update(STAGE.glob('*quiet*.cpp'));paths.update(STAGE/n for n in ('measurement_platform.py','measure_native_quads.py','measure_native_corpus_blocks.py','analyze_structure_aa.py','compare_structure_round.py','native_build_storage.py','run_native_managed.py','build_native_hot_lto.py','next_two.py','regenerate_frame_guard.py','AGENTS.md','native_storage_hook/sitecustomize.py'));paths.add(REPO/'docs/C++模拟器构建产物管理.md')"
    text=text.replace(old,new)
    text=text.replace("paths.add(REPO/'docs/C++模拟器构建产物管理.md')", "paths.add(REPO/'docs/C++模拟器构建产物管理.md');paths.update(STAGE/n for n in ('native_build_schedule.py','test_native_build_schedule.py'));paths.update((STAGE/'build_storage/parallel_headroom_tests_20261128').rglob('*.json'));paths.update((STAGE/'build_storage/parallel_headroom_tests_20261128/source').rglob('*cpp'));paths.add(STAGE/'build_storage/parallel_headroom_tests_20261128/source/build_windows.py');paths.update((STAGE/'build_storage/parallel_tests_20261128').glob('*.json'))")
    old="paths.update(p for p in STAGE.glob('frame_guard*.log') if not p.name.startswith(('frame_guard_archive_','frame_guard_goal_driver_')));paths.add(STAGE/'post_ordering_profile_first.log')";assert old in text;text=text.replace(old,'# All phase logs are frozen under WORK.')
    text=text.replace("for folder in (WORK,STAGE/'native_perf50/post_ordering_assessment'):","for folder in (WORK,):")
    old="            if p.name.startswith('checkpoint_'):continue";assert old in text;text=text.replace(old,"            if p.name.startswith(('checkpoint_','quiet_goal_driver','quiet_archive_')):continue")
    text=text.replace("note=REPO/'docs/C++模拟器逐帧类型守卫复用优化记录_2026-11-27.md'","note=REPO/json.loads((WORK/'documentation.json').read_bytes())['path']")
    anchor="    relative=sorted(p.relative_to(REPO).as_posix() for p in paths);protected=";assert anchor in text
    text=text.replace(anchor,"    for folder in STAGE.glob('native_quiet_fast_*'):\n        if folder.is_dir():paths.update(folder.rglob('*.json'))\n"+anchor)
    extras="""    paths.add(STAGE/'profile_native_windows.py')
    paths.add(STAGE/'native_perf50/measurement_structure_bundle/profile_baseline.json')
    paths.update(REPO/'docs'/name for name in ('C++模拟器优化交接_2026-11-23.md','C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md'))
    proof_rows=list(json.loads((WORK/'qualification_steps.json').read_bytes()).values())
    if (WORK/'rejected_cost_profile_receipt.json').exists():proof_rows.append(json.loads((WORK/'rejected_cost_profile_receipt.json').read_bytes()))
    for row in proof_rows:
        if 'cleanup_receipt' in row:
            receipt=Path(row['cleanup_receipt']);assert sha(receipt)==row['cleanup_receipt_sha256'];paths.add(receipt)
            for item in json.loads(receipt.read_bytes())['preserved']:
                file=receipt.parent/item['path'];assert sha(file)==item['sha256'];paths.add(file)
    for file in WORK.rglob('persistent_build_directory.json'):
        root=Path(json.loads(file.read_bytes())['root'])
        while root.parent!=Path('D:/CodexNativeBuilds/work') and len(root.parts)>2:root=root.parent
        receipt=STAGE/'build_storage/archive'/root.name/'cleanup_receipt.json'
        if receipt.is_file():
            assert json.loads(receipt.read_bytes())['cleanup_complete'];paths.add(receipt)
"""
    text=text.replace(anchor,extras+anchor)
    text=text.replace('frame type guard reuse','guarded numerical core segments').replace('frame-guard-own-index-','quiet-own-index-')
    sys.argv=[str(STAGE/'finish_quiet_round.py'),*(['--upload'] if upload else [])]
    exec(compile(text,str(STAGE/'archive_frame_guard.py'),'exec'),dict(__name__='__main__',__file__=str(STAGE/'finish_quiet_round.py')))

if __name__=='__main__':{'close':close,'archive':archive,'upload':lambda:archive(True)}[sys.argv[1]]()

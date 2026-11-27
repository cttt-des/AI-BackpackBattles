"""Amortize CPU accounting over repeated executions of the unchanged fixed200."""
import ctypes
import hashlib
import statistics
import time
import psutil


def measure_blocks(sim,jobs,repetitions,load_before,*,precise_timestamps=False):
    assert len(jobs)==200 and repetitions>=1
    before=psutil.sensors_battery()
    def replay(job):
        _,sides,options,_,_=job
        return sim.run_one(*sides,**options)
    psutil.cpu_percent(interval=None)
    raw=[];all_results=[]
    wall_start,cpu_start,thread_start=time.perf_counter(),time.process_time(),time.thread_time()
    for _ in range(repetitions):
        start,thread=time.perf_counter(),time.thread_time()
        all_results.append(list(map(replay,jobs)))
        raw.append({'wall_s':time.perf_counter()-start,'main_thread_cpu_s':time.thread_time()-thread})
    thread_cpu=time.thread_time()-thread_start
    cpu=time.process_time()-cpu_start
    wall_end=time.perf_counter();wall=wall_end-wall_start
    load=psutil.cpu_percent(interval=None);logical=psutil.cpu_count();after=psutil.sensors_battery()
    signatures=[];durations=[]
    for record,results in zip(raw,all_results,strict=True):
        signature=hashlib.sha256()
        for (case_id,_,_,terminal_tick,winner),result in zip(jobs,results,strict=True):
            if(result.formal_ev_capped or result.timed_out or bool(result.player_wins)!=(winner=='player') or round(result.combat_time*60)!=terminal_tick):
                raise ValueError(f'Repeated replay terminal differs: {case_id}')
            durations.append(result.combat_time)
            signature.update(ctypes.string_at(ctypes.addressof(result),ctypes.sizeof(result)))
        signatures.append(signature.hexdigest());record.update(results_sha256=signatures[-1],matched_original_terminal=200)
    assert len(set(signatures))==1,'Every repeated fixed200 must have the same complete result signature'
    timestamps={'measurement_start_qpc':wall_start,'measurement_end_qpc':wall_end} if precise_timestamps else {}
    return {**timestamps,'results_sha256':signatures[0],'matched_original_terminal':200,
        'wall_s':wall/repetitions,'cpu_s':cpu/repetitions,'main_thread_cpu_s':thread_cpu/repetitions,
        'fights_per_second':200*repetitions/wall,
        'combat_seconds':{'minimum':min(durations),'median':statistics.median(durations),'mean':statistics.mean(durations),'maximum':max(durations)},
        'on_ac_before':before.power_plugged if before else None,'on_ac_after':after.power_plugged if after else None,
        'load_pct_before':load_before,'load_pct_after':load,'system_load_pct':load,
        'background_load_pct':max(0.0,load-100*cpu/(wall*logical)) if logical else None,
        'batch_repetitions':repetitions,'observed_fights':200*repetitions,
        'block_wall_s':wall,'block_cpu_s':cpu,'block_main_thread_cpu_s':thread_cpu,
        'normalization':'times per fixed200; outer clocks span all repetitions before validation/hash work',
        'raw_batches':raw,'load_observation_scope':'entire repeated block'}

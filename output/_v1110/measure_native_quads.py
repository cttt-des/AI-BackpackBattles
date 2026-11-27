"""Fixed-core, time-bracketed ABBA/BAAB; preserve every observation."""
import argparse,gc,hashlib,json,math,os,random,subprocess,sys,time
from contextlib import ExitStack
from pathlib import Path
import psutil
from bench_native_corpus import load_simulator,prepare,select_cases
from measure_native_corpus_blocks import measure_blocks
from measurement_platform import Counters

def worker(dll,reference_path,logical_cpu):
    process=psutil.Process();process.cpu_affinity([int(logical_cpu)])
    reference=json.loads(Path(reference_path).read_bytes());sim=load_simulator(Path(dll));signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature));assert signature.hexdigest()==reference['inputs_sha256']
    counters=Counters();print(json.dumps(dict(ready=True,pid=process.pid,affinity=process.cpu_affinity(),dll_sha256=hashlib.sha256(Path(dll).read_bytes()).hexdigest(),inputs_sha256=signature.hexdigest())),flush=True)
    for line in sys.stdin:
        if line.strip()=='quit':return
        count=int(line.strip());assert 1<=count<=16
        gc.collect();previous=gc.isenabled();gc.disable()
        try:
            cpu_before=int(counters.processor());cycles_before=counters.cycles();start=time.perf_counter()
            result=measure_blocks(sim,jobs,count,0,precise_timestamps=True)
            end=time.perf_counter();cycles_after=counters.cycles();cpu_after=int(counters.processor())
        finally:
            if previous:gc.enable()
        assert result['results_sha256']==reference['results_sha256']
        assert cpu_before==cpu_after==int(logical_cpu)
        # Validation/hash work occurs after the measured block inside measure_blocks.
        # Midpoint is computed from the actual measured wall span, before that work.
        result.update(request_start_qpc=start,request_end_qpc=end,logical_cpu_before=cpu_before,logical_cpu_after=cpu_after,
            reported_thread_cycles_including_validation=cycles_after-cycles_before,cycles_not_elapsed_time_or_primary_metric=True,
            gc_disabled_during_block=True)
        print(json.dumps(result),flush=True)

class Arm:
    def __init__(self,dll,reference,cpu,log):
        self.log=log.open('wb');self.process=subprocess.Popen([sys.executable,'-u','-X','utf8',str(Path(__file__).resolve()),'--worker',str(dll.resolve()),str(reference.resolve()),str(cpu)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=self.log,text=True,encoding='utf8',creationflags=subprocess.CREATE_NO_WINDOW|subprocess.NORMAL_PRIORITY_CLASS)
        try:
            self.ready=self.read();assert self.ready['ready'] and self.ready['affinity']==[cpu]
        except BaseException:
            self.close();raise
    def read(self):
        line=self.process.stdout.readline()
        if not line:raise RuntimeError('Benchmark worker exited; inspect retained worker log')
        return json.loads(line)
    def run(self,count):self.process.stdin.write(str(count)+'\n');self.process.stdin.flush();return self.read()
    def close(self):
        try:
            if self.process.poll() is None:
                self.process.stdin.write('quit\n');self.process.stdin.flush()
                try:self.process.wait(timeout=5)
                except subprocess.TimeoutExpired:self.process.kill();self.process.wait(timeout=5)
        finally:
            self.process.stdin.close();self.process.stdout.close();self.log.close()

def contrasts(arms):
    result={};times=[(a['measurement_start_qpc']+a['measurement_end_qpc'])/2 for a in arms]
    assert times[0]<times[1]<times[2]<times[3]
    for metric in ('main_thread_cpu_s','wall_s'):
        outer=[math.log(arms[i][metric]) for i in (0,3)];values=[]
        for i in (1,2):
            weight=(times[i]-times[0])/(times[3]-times[0]);estimate=(1-weight)*outer[0]+weight*outer[1]
            values.append(estimate-math.log(arms[i][metric]) if arms[0]['label']=='A' else math.log(arms[i][metric])-estimate)
        result[metric]=sum(values)/2
    return result

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--baseline',type=Path,required=True);parser.add_argument('--candidate',type=Path,required=True);parser.add_argument('--reference',type=Path,required=True);parser.add_argument('--out',type=Path,required=True);parser.add_argument('--logical-cpu',type=int,required=True);parser.add_argument('--quads',type=int,default=12);parser.add_argument('--repetitions',type=int,default=4);parser.add_argument('--warmup-seconds',type=float,default=120);parser.add_argument('--seed',type=int,required=True);parser.add_argument('--candidate-load-first',action='store_true');a=parser.parse_args()
    assert a.quads>0 and a.quads%2==0 and 1<=a.repetitions<=16 and not a.out.exists()
    orders=['ABBA']*(a.quads//2)+['BAAB']*(a.quads//2);random.Random(a.seed).shuffle(orders)
    report=dict(protocol='fixed-core bracketed log-cost quads v1',baseline_dll_sha256=hashlib.sha256(a.baseline.read_bytes()).hexdigest(),candidate_dll_sha256=hashlib.sha256(a.candidate.read_bytes()).hexdigest(),logical_cpu=a.logical_cpu,seed=a.seed,planned_orders=orders,repetitions=a.repetitions,quads=[],all_observations_retained=True,output_written_only_after_timing=True,primary_estimator='median of quad contrasts; linear interpolation in log cost by measured arm midpoint',requested_warmup_seconds=a.warmup_seconds)
    with ExitStack() as resources:
        arms={};order=('B','A') if a.candidate_load_first else ('A','B')
        for label in order:
            arm=Arm(a.baseline if label=='A' else a.candidate,a.reference,a.logical_cpu,a.out.with_name(a.out.stem+'_'+label+'_worker.log'));arms[label]=arm;resources.callback(arm.close)
        report['workers']={k:v.ready for k,v in arms.items()};report['load_order']=order
        start=time.perf_counter();warmup=[]
        while time.perf_counter()-start<a.warmup_seconds or not warmup:
            for label in order:
                r=arms[label].run(1);warmup.append(dict(label=label,**r))
            order=tuple(reversed(order))
        report['warmup']=dict(elapsed_seconds=time.perf_counter()-start,arms=warmup)
        try:
            for pattern in orders:
                observations=[]
                for label in pattern:observations.append(dict(label=label,**arms[label].run(a.repetitions)))
                report['quads'].append(dict(order=pattern,arms=observations,log_time_reduction=contrasts(observations)))
        finally:
            a.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(out=str(a.out),quads=len(report['quads']),completed=True)),flush=True)
if __name__=='__main__':
    if sys.argv[1:2]==['--worker']:worker(*sys.argv[2:])
    else:main()

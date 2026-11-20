from pathlib import Path
import psutil,subprocess,sys
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
w=Path(__file__).resolve().parent;s=w.parents[1];root=s.parents[1]
for name,option in [('shared_speed_ab','--candidate-first'),('shared_speed_ab_repeat','--candidate-load-first')]:
 subprocess.run([sys.executable,'-u','-X','utf8',str(s/'compare_native_isolated.py'),'--baseline',str(root/'dist/native_1_1_10/libgdcore.dll'),'--candidate',str(w/'shared_speed.dll'),'--reference',str(s/'native_perf50/corpus_baseline_1.json'),'--out',str(w/(name+'.json')),'--warmup-seconds','120','--quiet',option],check=True)

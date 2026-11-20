from pathlib import Path
import psutil,subprocess,sys
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
w=Path(__file__).resolve().parent;s=w.parents[1];root=s.parents[1]
for name,option in [('ltrans_devirt_ab','--candidate-first'),('ltrans_devirt_ab_repeat','--candidate-load-first')]:
 subprocess.run([sys.executable,'-u','-X','utf8',str(s/'compare_native_isolated.py'),'--baseline',str(w.parent/'cycles18/reverse_stack_names.dll'),'--candidate',str(w/'ltrans_devirt.dll'),'--reference',str(s/'native_perf50/corpus_baseline_1.json'),'--out',str(w/(name+'.json')),'--warmup-seconds','120','--quiet',option],check=True)

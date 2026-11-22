"""At most one extra independent eight-pair group, combining every original pair."""
import json
from pathlib import Path
import subprocess
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
assert (WORK/'bounded_followup_policy.json').exists()
plan=WORK/'followup_plan.json';assert not plan.exists()
plan.write_text(json.dumps(dict(maximum_extra_groups=1,all_original24_retained=True,all32_must_be_used=True,no_more_same_source_groups=True,policy='First24 inconclusive or leave-one-group sensitivity not positive: one independent baseline-first group, then stop'),indent=2)+'\n',encoding='utf8')
subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),'--baseline',str(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/'ab_4.json'),'--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet','--candidate-load-first'],check=True)
subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),'--reports',*[str(WORK/f'ab_{i}.json') for i in (1,2,3,4)],'--out',str(WORK/'ab_assessment_32.json')],check=True)

"""One raw24/calibration24 only after the frozen AB has accepted the DLL."""
from pathlib import Path
import json
import psutil
from prepare_timeline_round import STAGE,WORK
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
assert json.loads((WORK/'candidate_decision.json').read_bytes())['accepted']
text=(STAGE/'measure_frame_guard.py').read_text('utf8').replace('from prepare_frame_guard_reuse import','from prepare_timeline_round import')
text=text.replace("WORK/'post_ab_directed_checks.json'","WORK/'formal_affected_tests.json'")
exec(compile(text,str(STAGE/'measure_frame_guard.py'),'exec'),dict(__name__='__main__',__file__=__file__))

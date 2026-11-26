"""Read only the identified protocol processes and their original logs."""
import json
from pathlib import Path
import re
import psutil
WORK=Path(__file__).resolve().parent
rows=json.loads((WORK/'live_formal_driver.json').read_bytes())
active=[]
for role,row in rows.items():
    try:
        p=psutil.Process(row['pid'])
        if abs(p.create_time()-row['created'])>=0.001:continue
        children=[]
        for child in p.children(recursive=True):
            try:children.append(dict(pid=child.pid,name=child.name(),cpu_s=round(sum(child.cpu_times()[:2]),2)))
            except psutil.NoSuchProcess:pass
        active.append(dict(role=role,pid=p.pid,children=children))
    except psutil.NoSuchProcess:pass
print(json.dumps(dict(active=active)))
logs=('build_first.log','qualification_first.log','comparison.log','bounded_followup.log','release_measurements.log')
continuation=WORK.parents[1]/'weapon_inline_chain_continuation_first.log'
if continuation.exists():
    print('continuation.log: '+continuation.read_text('utf8',errors='replace')[-1000:])
    logs=('qualification_continued.log','comparison.log','bounded_followup.log','release_measurements.log')
for name in logs:
    p=WORK/name
    if p.exists():print(name+': '+p.read_text('utf8',errors='replace')[-1000:])
o=Path(json.loads((WORK/'persistent_build_directory.json').read_bytes())['objects'])
p=o/'libgdcore.dll.ltrans.mk'
if p.exists():
    targets=re.findall(r'^(.+\.ltrans\d+\.ltrans\.o):',p.read_text('utf8'),re.M)
    print('LTO completed='+str(len(list(o.glob('*.ltrans.o'))))+' current_targets='+str(len(targets)))
print('decision_exists='+str((WORK/'candidate_decision.json').exists()))

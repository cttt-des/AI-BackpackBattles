"""Combine independent actual-DLL frame, event and storage evidence."""
import json
from pathlib import Path
from prepare_native_coallocated_events import STAGE,WORK,sha
from verify_coallocated_frame import verify as frames
from verify_coallocated_params import verify as params
from verify_coallocated_storage import verify as storage

def combine(dll,out):
    root=out.parent;records={}
    for name,count in [('frame',3073),('params',1024),('storage',64)]:
        path=root/(name+'_correctness.json');row=json.loads(path.read_bytes())
        assert row['passed'] and row['cases']==count and row['dll_sha256']==sha(dll)
        records[name]=dict(cases=count,report_sha256=sha(path))
    raw={p.name:sha(p) for p in root.glob('*_cases.json')}
    report=dict(passed=True,cases=4161,dll_sha256=sha(dll),components=records,raw_cases_sha256=raw,
        fixtures_sha256={name:sha(STAGE/name) for name in ('test_native_frame_proof.cpp','test_native_event_capacity.cpp','test_coallocated_event_storage.cpp')},
        actual_dll_independent_baseline_oracles=True,no_throughput_claim=True)
    assert not out.exists();out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2));return report

def verify(source,dll,out):
    frames(source,dll,out.parent/'frame_correctness.json')
    params(source,dll,out.parent/'params_correctness.json')
    storage(source,dll,out.parent/'storage_correctness.json')
    return combine(dll,out)

if __name__=='__main__':
    # The existing live driver runs frame/params checks; retain those first runs.
    import psutil
    matches=[]
    for p in psutil.process_iter(['pid','cmdline']):
        if p.pid==psutil.Process().pid:continue
        try:
            if p.exe()==psutil.Process().exe() and any(Path(x).name=='validate_coallocated_when_built.py' for x in p.info['cmdline'] or []):matches.append(p)
        except (psutil.NoSuchProcess,psutil.AccessDenied):continue
    assert len(matches)<=1
    if matches:
        print('Awaiting identified live validation PID '+str(matches[0].pid),flush=True)
        while matches[0].is_running():
            try:matches[0].wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    for name in ('frame','params'):
        assert json.loads((WORK/(name+'_correctness.json')).read_bytes())['passed']
    if not (WORK/'storage_correctness.json').exists():storage(WORK/'prototype_src',WORK/'prototype.dll',WORK/'storage_correctness.json')
    combine(WORK/'prototype.dll',WORK/'correctness.json')

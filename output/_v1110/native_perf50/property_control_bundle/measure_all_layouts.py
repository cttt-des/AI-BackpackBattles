"""Measure all exact generated allocation sizes outside the timing window."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    results={}
    with tempfile.TemporaryDirectory(prefix='native-all-layouts-') as temporary:
        for label,header,dll in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim',STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'),('candidate',WORK/'bundle_src',WORK/'bundle.dll')]:
            folder=Path(temporary)/label;folder.mkdir();shutil.copyfile(dll,folder/'libgdcore.dll')
            assert sha(folder/'libgdcore.dll')==sha(dll)
            executable=folder/'layouts.exe'
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(header),str(STAGE/'test_native_all_layouts.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
            results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    assert all(r['count']==674 and r['rng_unchanged'] for r in results.values())
    old={r['id']:r for r in results['baseline']['types']}
    new={r['id']:r for r in results['candidate']['types']}
    assert set(old)==set(new)
    changes=[]
    for id in old:
        a,b=old[id],new[id];assert (a['name'],a['item'])==(b['name'],b['item'])
        if a['bytes']!=b['bytes']:changes.append({'id':id,'name':a['name'],'item':a['item'],'before':a['bytes'],'after':b['bytes']})
    summary={'types_measured':674,'changed_types':len(changes),'item_types_changed':sum(c['item'] for c in changes),
             'unweighted_one_of_each_bytes_before':sum(r['bytes'] for r in old.values()),'unweighted_one_of_each_bytes_after':sum(r['bytes'] for r in new.values())}
    report={'passed':True,'baseline_dll_sha256':sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'),
        'candidate_dll_sha256':sha(WORK/'bundle.dll'),'results':results,'changes':changes,'summary':summary,
        'method':'Two consecutive exact generated allocations in one block; allocators source-verified as one arena.make<T> each',
        'unweighted_totals_are_not_corpus_memory_usage':True}
    (WORK/'all_layouts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(summary,indent=2),flush=True)

if __name__=='__main__':main()

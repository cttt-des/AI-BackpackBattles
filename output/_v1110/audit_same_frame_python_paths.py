"""Identify which ordering discrepancies also affect the active Python fallback."""
import hashlib,json,shutil,subprocess,sys
from pathlib import Path
from types import SimpleNamespace

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
sys.path.insert(0,str(REPO))
WORK=STAGE/'same_frame_potion_audit_20261127'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    import gd_core_py._rt as rt
    from gd_core_py.gd_core.CoreEventBus import CoreEventBus
    from simulator.item import Item
    reference=json.loads((WORK/'godot_reference.json').read_bytes())
    class Compare:
        def compare(self,a,b):return a.priority>b.priority
    rows=[]
    for case in reference['sorts']:
        n,mode=case['length'],case['mode']
        items=[SimpleNamespace(index=i,priority=0 if mode==0 else ((i*7+mode)%(mode+1))*1000) for i in range(n)]
        rt._sort_custom(items,Compare(),'compare')
        rows.append(dict(length=n,mode=mode,order=[x.index for x in items]))
    bus_rows={}
    for scenario in reference['bus']:
        bus=CoreEventBus();ctx=SimpleNamespace(fight_ended=False,rng=SimpleNamespace(oracle_trace=False,_stacktrace=False));bus._ctx=ctx
        emitter=rt.Node();trace=[];nested=False
        def emit():bus.emitSignal(emitter,'test',[])
        def third():trace.append(3)
        def first():
            nonlocal nested
            trace.append(1)
            if scenario=='append':bus.connectEvent(emitter,'test',receiver,'third')
            if scenario=='clear':bus.connections[bus.getEmissionID(emitter,bus.signalIDs['test'])].clear()
            if scenario=='nested' and not nested:nested=True;emit()
            if scenario=='ended':ctx.fight_ended=True
        receiver=SimpleNamespace(first=first,second=lambda:trace.append(2),third=third)
        bus.connectEvent(emitter,'test',receiver,'first');bus.connectEvent(emitter,'test',receiver,'second');emit();bus_rows[scenario]=trace
    class Legacy:
        def __init__(self,empty=False):self.consumed=empty;self.is_full=not empty;self.log=None;self.character=None;self.trace=[]
        def emit_signal(self,signal,*args):self.trace.append(signal)
        def is_empty(self):return self.consumed or not self.is_full
        def visual_activate(self):self.trace.append('visual_activate')
        def has_behavior(self,name):return True
        def call_behavior(self,*args):self.trace.append('effect')
        def get_affected_items(self):return []
    legacy={}
    for empty in (False,True):
        obj=Legacy(empty);Item.consume_potion(obj);legacy['already_empty' if empty else 'full']=obj.trace
    # A previous independently built production DLL shares the frozen layout.
    comparison=json.loads((WORK/'comparison.json').read_bytes());build=Path(comparison['fixture_build_directory']);folder=build/'previous_d206';folder.mkdir()
    shutil.copyfile(build/'test.exe',folder/'test.exe')
    old=STAGE/'native_perf50/buff_inline_types_bundle/bundle.dll'
    assert sha(old)=='d2064b3f17d8168cf87a2e9f46e9fb336ffe4aaf6581c27d93350b2c41477a57'
    shutil.copyfile(old,folder/'libgdcore.dll');shutil.copyfile(old,folder/'release.dll')
    run=subprocess.run([str(folder/'test.exe')],capture_output=True,timeout=60);run.check_returncode()
    (WORK/'previous_d206_actual.json').write_bytes(run.stdout)
    old_result=json.loads(run.stdout);current=json.loads((WORK/'native_actual.json').read_bytes())
    report=dict(python_runtime_module=rt.__file__,python_runtime_module_sha256=sha(Path(rt.__file__)),python_bus_module=sys.modules[CoreEventBus.__module__].__file__,
        python_sort_cases=rows,python_sort_differences=[i for i,(a,b) in enumerate(zip(rows,reference['sorts'])) if a['order']!=b['order']],
        python_bus=bus_rows,python_bus_matches_original=bus_rows==reference['bus'],legacy_potion_trace=legacy,legacy_source_sha256=sha(REPO/'simulator/item.py'),
        previous_production_dll_sha256=sha(old),previous_and_current_native_results_identical=old_result==current,
        findings_predate_latest_assembly_membership_optimization=old_result==current,
        default_trainer_uses_versioned_native_when_available=True,legacy_simulator_not_default=True)
    (WORK/'python_paths.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='python_sort_cases'},indent=2))

if __name__=='__main__':main()

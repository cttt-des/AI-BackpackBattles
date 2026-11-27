"""Run the actual candidate Python modules against the independent oracle."""
import argparse,hashlib,importlib.util,json,sys
from pathlib import Path
from types import SimpleNamespace

def main():
    p=argparse.ArgumentParser();p.add_argument('--package',type=Path,required=True);p.add_argument('--work',type=Path,required=True);p.add_argument('--out',type=Path,required=True);p.add_argument('--pure-rt',action='store_true');a=p.parse_args()
    repo=Path(__file__).resolve().parents[2];sys.path.insert(0,str(repo));sys.path.insert(0,str(a.package.resolve()))
    import gd_core_py._rt as rt
    assert Path(rt.__file__).resolve().is_relative_to(a.package.resolve())
    active=rt
    if a.pure_rt:
        spec=importlib.util.spec_from_file_location('gd_core_py._rt_source_check',a.package/'gd_core_py/_rt.py');active=importlib.util.module_from_spec(spec);spec.loader.exec_module(active)
    keys=json.loads((a.work/'sort_cases.json').read_bytes());reference=json.loads((a.work/'original_ordering_reference.json').read_bytes())
    class Compare:
        def __init__(self):self.trace=[]
        def compare(self,a,b):self.trace.extend((a.index,b.index));return a.priority>b.priority
    results=[]
    for row in keys:
        items=[SimpleNamespace(index=i,priority=x) for i,x in enumerate(row)];compare=Compare();active._sort_custom(items,compare,'compare');results.append(dict(order=[x.index for x in items],comparisons=compare.trace))
    assert results==reference['sort_cases'],[i for i,(x,y) in enumerate(zip(results,reference['sort_cases'])) if x!=y]
    from gd_core_py.gd_core.CoreEventBus import CoreEventBus
    bus_result={}
    for name in [*reference['bus'],*reference['bus_extra']]:
        ctx=SimpleNamespace(fight_ended=False,rng=SimpleNamespace(oracle_trace=False,_stacktrace=False));bus=CoreEventBus();bus._ctx=ctx;emitter=rt.Node();trace=[];nested=False
        def connect(receiver):bus.connectEvent(emitter,'test',receiver,'mark')
        third=SimpleNamespace(mark=lambda:trace.append(3))
        def emit():bus.emitSignal(emitter,'test',[])
        def first():
            nonlocal nested
            trace.append(1);eid=bus.getEmissionID(emitter,bus.signalIDs['test']);listeners=bus.connections[eid]
            if name in ('append','delayed'):connect(third)
            if name=='clear':listeners.clear()
            if name=='shrink':del listeners[1:]
            if name=='erase_current':del listeners[0]
            if name=='erase_future':del listeners[1]
            if name=='replace_future':listeners[1]=listeners[2]
            if name=='clear_then_append':listeners.clear();connect(third)
            if name=='clear_dictionary':bus.disconnectAll()
            if name=='replace_array':bus.connections[eid]=[[rt.FuncRef(third,'mark'),third]]
            if name=='append64':
                for i in range(64):connect(SimpleNamespace(mark=lambda i=i:trace.append(i+3)))
            if name in ('nested','nested_append','nested_clear') and not nested:
                nested=True
                if name=='nested_append':connect(third)
                emit()
            elif name=='nested_clear' and nested:listeners.clear()
            if name in ('ended','append_ended'):
                if name=='append_ended':connect(third)
                ctx.fight_ended=True
        connect(SimpleNamespace(mark=first));connect(SimpleNamespace(mark=lambda:trace.append(2)))
        if name in ('erase_current','erase_future','replace_future'):connect(third)
        if name=='already_ended':ctx.fight_ended=True
        if name=='delayed':bus.setLoggingMode(2)
        emit()
        if name=='delayed':bus.flushLoggingQueue()
        if name=='replace_array':emit()
        bus_result[name]=trace
    assert bus_result=={**reference['bus'],**reference['bus_extra']}
    report=dict(passed=True,pure_rt=a.pure_rt,rt_module=active.__file__,compiled_rt_loaded=rt.__file__,sort_cases=len(results),event_scenarios=len(bus_result),same_comparison_call_sequence_as_original=True,bus_results=bus_result,helper_module=sys.modules['gd_core_py._godot_sort'].__file__,typed_abi_existing_compiled_event_bus_compatible=True)
    a.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps({k:v for k,v in report.items() if k!='bus_results'}))
if __name__=='__main__':main()

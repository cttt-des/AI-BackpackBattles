"""Audit a larger callback-argument representation candidate without timing it."""
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
from prepare_native_storage_bundle import BASE,WORK as PROBE,STAGE,sha

def main():
    counts=Counter();other=[];sites=[];sources={}
    needle='native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitEvent>'
    for p in sorted((BASE/'gen/shards').glob('*.cpp')):
        sources[p.relative_to(BASE).as_posix()]=sha(p)
        method=None
        for line_no,line in enumerate(p.read_text('utf8').splitlines(),1):
            if line.startswith('gd::GdVal '):method=line.split('(',1)[0]
            if re.search(r'\b_args\b',line):
                if re.match(r'^gd::GdVal \w+::(?:fn|sf)_\w+\(.*const gd::GdVal\* _args, int _argc\) \{$',line):counts['function_signatures']+=1
                elif re.match(r'^\s*gd::GdVal lv_\w+ = \(_argc > \d+\) \? _args\[\d+\] : .*;\s*$',line):counts['value_cell_copies']+=1
                else:other.append(dict(path=p.relative_to(BASE).as_posix(),line=line_no,text=line))
            if needle in line:
                sites.append(dict(path=p.relative_to(BASE).as_posix(),line=line_no,method=method,
                                  inline_literal_array='GdArr::from_init' in line,statement=line.strip()))
    assert counts['function_signatures']==4992 and counts['value_cell_copies']==3268
    assert len(other)==7 and len(sites)==12 and all(s['inline_literal_array'] for s in sites)
    plan=dict(baseline_dll_sha256=sha(BASE/'libgdcore.dll'),source_sha256=sources,
        candidate='literal event arguments passed as a non-escaping span through one closed native emission path',
        implemented=False,validated=False,formal_timing_done=False,generated_parameter_accesses=dict(counts),
        remaining_value_reads=other,eligible_literal_call_sites=sites,
        current_coverage_context='deployed profile: trigger43.9664%, event bus366 inclusive samples; attribution is not realizable speedup',
        rationale=['Avoid creating an arena GdArr for a literal argument list when no listener observes it',
                   'Avoid repeated boxing/copying through emitEvent/emitAndLog/function-reference wrappers',
                   'Keep original methods as complete fallbacks and keep original event/log path'],
        proof_still_required=['Audit canonical native method wrappers and C++ bridge boundaries; generated text scan alone is not a complete escape proof',
            'The literal outer array has no prior alias; retain all value and receiver evaluation order',
            'Known native callbacks copy argument cells; unknown and bound callbacks must see materialized original-shape array before invocation',
            'Queue logging materializes and retains the independent mutable array',
            'After the first materialization, future callbacks must see its live data, including mutation by opaque code',
            'Preserve captured listener length, future-slot replacement, nested emission, terminal checks, trace toggles, RNG and FP state',
            'Keep all old event/generic/funcref counters at their original points',
            'Actual-DLL differential, fixed200 and freshPGO/full formal protocol before deployment'],
        no_raw_argument_escape_claim_from_this_scan=True,no_speedup_percentage_forecast=True)
    out=STAGE/'native_perf50/storage_bundle/literal_event_span_review.json'
    assert not out.exists();out.write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(signatures=counts['function_signatures'],copies=counts['value_cell_copies'],other_reads=len(other),literal_sites=len(sites))))

if __name__=='__main__':main()

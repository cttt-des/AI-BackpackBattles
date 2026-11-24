"""Estimate eligible call coverage from actual types and pure dispatch source."""
from collections import Counter
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze
from probe_native_object_routes import STAGE,BASE,ACCEPTED,WORK,EXPECTED,sha

def main():
    out=WORK/'route_scope_analysis.json';assert not out.exists()
    probe=json.loads((WORK/'object_route_probe.json').read_bytes());assert probe['passed'] and probe['baseline_dll_sha256']==EXPECTED
    source='\n'.join(p.read_text('utf8') for p in sorted((BASE/'gen/shards').glob('*.cpp')))
    supported=set(re.findall(r'case (SYM_GEN_\w+): out = fn_\w+\(args, argc\); return true;',source))
    mass=Counter()
    for row in probe['rows']:
        if row['canonical_exact_row_index'] is not None and row['method'] in supported:mass[row['method']]+=row['count']
    symbols=[s for s,_ in mass.most_common()]
    profile=json.loads((ACCEPTED/'profile_depth64.json').read_bytes())
    proof=analyze(BASE,profile,limit=0,extra_symbols=symbols)
    assert proof['eligible_classes_with_pure_inheritance']==674
    slots={r['symbol']:i for i,r in enumerate(proof['selected_methods'])}
    hits=Counter();excluded=Counter()
    for row in probe['rows']:
        match=re.fullmatch(r'\d+(Gd__\w+)',row['receiver_cpp_type'])
        cls=match[1] if match else None
        if row['canonical_exact_row_index'] is None or cls not in proof['class_rows']:
            excluded['not_canonical_exact_generated_row']+=row['count'];continue
        if row['method'] not in slots:
            excluded['no_generated_instance_method']+=row['count'];continue
        implementation=proof['resolved_rows'][proof['class_rows'][cls]][slots[row['method']]]
        if implementation:hits[row['method']]+=row['count']
        else:excluded['missing_method_or_static_shadow']+=row['count']
    assert sum(hits.values())+sum(excluded.values())==probe['total_object_virtual_calls']
    ranked=hits.most_common()
    result=dict(baseline_dll_sha256=EXPECTED,probe_receipt_sha256=sha(WORK/'object_route_probe.json'),
        total_object_virtual_calls=probe['total_object_virtual_calls'],actual_eligible_instance_calls=sum(hits.values()),
        distinct_eligible_instance_methods=len(hits),excluded_call_counts=dict(excluded),
        top_methods=[dict(symbol=s,calls=n) for s,n in ranked],
        coverage_by_method_budget={str(n):sum(v for _,v in ranked[:n]) for n in (16,32,48,64,96,128)},
        exact_type_row_and_pure_inheritance_required=True,not_a_throughput_forecast=True,
        implementation_not_started=True,next_step='Choose hot instance-method budget plus separately prove the88,491 static _nativeF32 calls before bundling')
    (WORK/'instance_route_source_proof.json').write_text(json.dumps(proof,indent=2)+'\n',encoding='utf8')
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in result.items() if k!='top_methods'},indent=2));print(json.dumps(result['top_methods'][:20],indent=2))

if __name__=='__main__':main()

"""Resolve generated inheritance without altering runtime source or executing battles."""
import argparse
from collections import Counter,defaultdict
import hashlib
import json
from pathlib import Path
import re

def analyze(native,profile,limit=32,extra_symbols=()):
    headers={}
    for path in sorted((native/'gen/hdrs').glob('*.hpp')):
        match=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',path.read_text('utf8'),re.M)
        if match:headers[match[1]]=match[2]
    source='\n'.join(p.read_text('utf8') for p in sorted((native/'gen/shards').glob('*.cpp')))
    own={};pure={};symbols=defaultdict(set)
    cases=re.compile(r'case ([\w:]+): out = ((?:fn_\w+\(args, argc\))|(?:sf_\w+\(gd_ctx, args, argc\))); return true;')
    for match in re.finditer(r'^bool (Gd__\w+)::call_method\([^\n]*\n(.*?)^\}',source,re.M|re.S):
        cls,body=match[1],match[2];entries={}
        for item in cases.finditer(body):
            fn=re.fullmatch(r'fn_(\w+)\(args, argc\)',item[2])
            entries[item[1]]=(cls,fn[1]) if fn else None # Static overrides shadow inherited methods too.
            if fn:symbols[fn[1]].add(item[1])
        leftovers=cases.sub('',body)
        leftovers=re.sub(r'return [\w:]+::call_method\(gd_ctx, m, args, argc, out\);','',leftovers)
        leftovers=leftovers.replace('switch (m) {','').replace('default: break;','').replace('return false;','').replace('}','')
        fallbacks=re.findall(r'return ([\w:]+)::call_method\(gd_ctx, m, args, argc, out\);',body)
        base=headers[cls]
        edge_ok=(fallbacks==[base]) if base in headers else (base=='gd::GdObj' and fallbacks in ([],['gd::GdObj']))
        own[cls]=entries;pure[cls]=not leftovers.strip() and edge_ok
    assert set(headers)==set(own),(set(headers)-set(own),set(own)-set(headers))
    eligible={};resolved={}
    def resolve(cls):
        if cls in resolved:return resolved[cls]
        base=headers[cls]
        inherited=resolve(base).copy() if base in headers else {}
        inherited.update(own[cls]);resolved[cls]=inherited
        eligible[cls]=pure[cls] and (eligible[base] if base in headers else base=='gd::GdObj')
        return inherited
    for cls in headers:resolve(cls)
    weighted=Counter()
    for row in profile['resolved_stacks']:
        seen=set();functions=row['functions']
        for i,name in enumerate(functions):
            if '::call_method(' not in name:continue
            j=i-1
            while j>=0 and '::call_method(' in functions[j]:j-=1
            if j>=0:
                match=re.search(r'::fn_(\w+)\(',functions[j])
                if match:seen.add(match[1])
        for name in seen:weighted[name]+=row['samples']
    selected=[]
    for name,samples in weighted.most_common():
        ids=symbols.get(name,set())
        if len(ids)!=1:continue
        symbol=next(iter(ids))
        if symbol.startswith('SYM_GEN_'):
            selected.append({'method':name,'symbol':symbol,'inclusive_dispatch_samples':samples})
        if len(selected)==limit:break
    for symbol in extra_symbols:
        if any(item['symbol']==symbol for item in selected):continue
        names=[name for name,ids in symbols.items() if symbol in ids]
        assert len(names)==1,(symbol,names)
        selected.append({'method':names[0],'symbol':symbol,'selection_origin':'static_call_sites'})
    rows={};classes={}
    for cls in headers:
        if not eligible[cls]:continue
        key=tuple(resolved[cls].get(item['symbol']) for item in selected)
        if key not in rows:rows[key]=len(rows)
        classes[cls]=rows[key]
    overrides=[]
    for item in selected:
        definitions=sorted({resolved[cls][item['symbol']] for cls in headers if eligible[cls] and resolved[cls].get(item['symbol'])})
        overrides.append({'method':item['method'],'implementations':definitions})
    return {'source_dll_sha256':profile['dll_sha256'],'profile_samples':profile['samples'],
        'generated_classes':len(headers),'pure_dispatch_classes':sum(pure.values()),
        'eligible_classes_with_pure_inheritance':len(classes),'excluded_classes':[c for c in headers if not eligible[c]],
        'selected_methods':selected,'resolved_row_count':len(rows),'row_slots':len(selected),
        'estimated_function_pointer_bytes':len(rows)*len(selected)*8,
        'class_rows':classes,'resolved_rows':[[list(value) if value else None for value in key] for key in rows],
        'overrides_preserved':overrides,
        'proof_scope':'All own dispatch cases and parent fallbacks must be pure generated switches; resolve most-derived implementation, including unsupported static-method shadows. This is source analysis, not a runtime equivalence proof.',
        'prototype_constraints':['Native bridge opt-in; generic path and custom C++ overrides retained',
          'Exact generated runtime type validation before caching a per-object row; shared metadata alone is insufficient',
          'Original argument/bind construction, callback order, math helpers and RNG retained',
          'Actual hit/miss/type coverage; full rebuild if object layout changes',
          'Fixed200 combined AB/BA and2604 strict truth/hash andraw24 before deployment'],
        'sampling_notes':'Method counts are inclusive and overlap. They cannot be added as an expected speed gain.'}

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--native',type=Path,required=True)
    parser.add_argument('--profile',type=Path,required=True)
    parser.add_argument('--out',type=Path,required=True)
    args=parser.parse_args()
    profile=json.loads(args.profile.read_bytes())
    assert hashlib.sha256((args.native/'libgdcore.dll').read_bytes()).hexdigest()==profile['dll_sha256']
    result=analyze(args.native,profile)
    args.out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({k:v for k,v in result.items() if k not in ('class_rows','resolved_rows','overrides_preserved')},indent=2))

if __name__=='__main__':main()

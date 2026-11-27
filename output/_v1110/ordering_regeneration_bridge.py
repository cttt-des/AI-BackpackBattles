"""Bootstrap the new guarded manifest after independently checking each raw edit."""
import argparse,hashlib,json,runpy,shutil
from pathlib import Path
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/ordering_correctness_bundle'
OLD=STAGE/'native_perf50/assembly_membership_bundle'

def canonical(data):return data.decode('utf8').replace('\r\n','\n').encode('utf8')
def digest(data):return hashlib.sha256(canonical(data)).hexdigest()
def paths(root):return {p.relative_to(root).as_posix():p for p in root.rglob('*') if p.is_file() and (p.suffix in ('.hpp','.cpp') or p.name=='build_windows.py')}
def sort_body(text):
    start=text.index('void sort_custom_stable(')
    comment='// Preserve this exported symbol for existing callers; its behavior is now\n// Godot 3.6 SortArray, including equal-key order and comparator call sequence.\n'
    if text[:start].endswith(comment):start-=len(comment)
    end=text.index('\n}\n',start)+2
    return start,end,text[start:end]
def corrected_runtime(raw):
    reference=(WORK/'bundle_src/gd_rt.cpp').read_text('utf8');_,_,body=sort_body(reference)
    start,end,_=sort_body(raw);fixed=raw[:start]+body+raw[end:]
    assert fixed.count('#include "gd_rt.hpp"')==1
    return fixed.replace('#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_godot_sort.hpp"',1)

def optimize(native,prepare):
    manifest=WORK/'regeneration_manifest.json'
    if manifest.exists():return runpy.run_path(str(WORK/'verified_bundle_pending.py'))['optimize'](native,prepare)
    legacy=runpy.run_path(str(OLD/'verified_bundle_pending.py'))['optimize']
    if prepare:
        legacy(native,True)
        path=native/'gd_rt.cpp';original=path.read_text('utf8');path.write_text(corrected_runtime(original),encoding='utf8',newline='\n')
        shutil.copyfile(WORK/'bundle_src/native_godot_sort.hpp',native/'native_godot_sort.hpp')
        return
    old=json.loads((OLD/'regeneration_manifest.json').read_bytes());old_rows={r['path']:r for r in old['inventory']}
    after=paths(WORK/'bundle_src');raw=paths(native)
    assert set(raw)==set(after) and len(raw)==710
    rows=[];input_hashes={}
    for name,path in sorted(raw.items()):
        current=path.read_bytes();value=digest(current);input_hashes[name]=value
        if name=='native_godot_sort.hpp':
            assert current==after[name].read_bytes();row=dict(path=name,before_canonical_sha256=value,runtime=False,intermediate_canonical_sha256=[])
        else:
            row=old_rows[name].copy()
            if name=='gd_rt.cpp':
                text=current.decode('utf8');start,end,_=sort_body(text);legacy_text=(OLD/'before_runtime/gd_rt.cpp').read_text('utf8');_,_,body=sort_body(legacy_text)
                inverse=(text[:start]+body+text[end:]).replace('#include "native_godot_sort.hpp"\n','',1)
                assert digest(inverse.encode())==row['before_canonical_sha256'],name
                row['before_canonical_sha256']=value
            elif name=='gen/shards/shard_12.cpp':
                a='for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {'
                b='for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {'
                text=current.decode('utf8');assert text.count(a)==1
                assert digest(text.replace(a,b,1).encode())==row['before_canonical_sha256'],name
                row['before_canonical_sha256']=value
            else:
                assert value in (row['before_canonical_sha256'],row['after_canonical_sha256']),name
            row['intermediate_canonical_sha256']=list(dict.fromkeys([*row.get('intermediate_canonical_sha256',[]),row['after_canonical_sha256']]))
        row['after_canonical_sha256']=digest(after[name].read_bytes());rows.append(row)
    data=dict(candidate_dll_sha256=None,inventory=rows,files=[r for r in rows if r['before_canonical_sha256']!=r['after_canonical_sha256']],raw_inverse_verified_against_accepted_manifest=True)
    manifest.write_text(json.dumps(data,indent=2)+'\n',encoding='utf8')
    shutil.copytree(OLD/'before_runtime',WORK/'before_runtime')
    (WORK/'before_runtime/gd_rt.cpp').write_bytes((native/'gd_rt.cpp').read_bytes())
    assert digest((WORK/'before_runtime/gd_rt.cpp').read_bytes())==next(r['before_canonical_sha256'] for r in rows if r['path']=='gd_rt.cpp')
    (WORK/'raw_generation_inverse_checks.json').write_text(json.dumps(dict(passed=True,source_files=710,only_raw_changed_files=['gd_rt.cpp','gen/shards/shard_12.cpp'],new_header='native_godot_sort.hpp',all_other_raw_sources_match_previously_verified_inventory=True,source_sha256=input_hashes),indent=2)+'\n',encoding='utf8')
    return runpy.run_path(str(WORK/'verified_bundle_pending.py'))['optimize'](native,False)

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('native',type=Path);p.add_argument('--prepare',action='store_true');a=p.parse_args();optimize(a.native,a.prepare)

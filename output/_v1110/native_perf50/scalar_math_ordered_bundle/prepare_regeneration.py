"""Version the accepted-transform candidate without changing the live generator."""
import hashlib
import json
from pathlib import Path
import shutil

WORK=Path(__file__).resolve().parent
OLD=WORK.parent/'typed_read_bundle'

def digest(p):return hashlib.sha256(p.read_bytes().decode('utf8').replace('\r\n','\n').encode('utf8')).hexdigest()

def main():
    original=json.loads((OLD/'regeneration_manifest.json').read_bytes())
    old={r['path']:r for r in original['inventory']}
    rows=[]
    src=WORK/'bundle_src'
    for path in sorted(p for p in src.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')):
        name=path.relative_to(src).as_posix()
        if name in old:
            row=old[name].copy()
            row['intermediate_canonical_sha256']=list(dict.fromkeys([*row.get('intermediate_canonical_sha256',[]),row['after_canonical_sha256']]))
        else:
            row={'path':name,'before_canonical_sha256':None,'runtime':False}
        row['after_canonical_sha256']=digest(path);rows.append(row)
    assert len(rows)==704
    result={'candidate_dll_sha256':None,'inventory':rows,'files':[r for r in rows if r['before_canonical_sha256']!=r['after_canonical_sha256']]}
    dll=WORK/'bundle.dll'
    if dll.exists():result['candidate_dll_sha256']=hashlib.sha256(dll.read_bytes()).hexdigest()
    (WORK/'regeneration_manifest.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    shutil.copytree(OLD/'before_runtime',WORK/'before_runtime',dirs_exist_ok=True)
    helper=(OLD/'verified_bundle_pending.py').read_text('utf8').replace('native_perf50/typed_read_bundle','native_perf50/scalar_math_ordered_bundle').replace("WORK/'resolved_src'","WORK/'bundle_src'")
    (WORK/'verified_bundle_pending.py').write_text(helper,encoding='utf8',newline='\n')
    test=(OLD/'test_full_regeneration.py').read_text('utf8').replace('native_perf50/typed_read_bundle','native_perf50/scalar_math_ordered_bundle').replace('resolved_src','bundle_src')
    (WORK/'test_full_regeneration.py').write_text(test,encoding='utf8',newline='\n')
    print(f'Prepared {len(rows)}-file inventory, {len(result["files"])} transformations; live generator unchanged')

if __name__=='__main__':main()

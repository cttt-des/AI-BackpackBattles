"""Retain sources/evidence and unique DLLs, then retire this project's C: cache."""
import hashlib,json,os,shutil,stat,sys,time
from pathlib import Path
from native_build_storage import LEGACY,ROOT,STAGE,sha
REPORT=STAGE/'build_storage/c_drive_retirement_20261127'
DROP={'.o','.obj','.s','.i','.ii','.exe','.lib','.exp','.res','.gcno','.pch','.gch','.pyc'}
BIN={'.dll','.dylib','.pyd'}
TEMP_NAMES=('frame-guard-regeneration-b8aiyd_d','frame-guard-regeneration-9eo5lp3b','frame-guard-regeneration-fcqm6x3n','next-two-machine-ojxpz__0','next-two-machine-2f5gvbw9','rng-baseline-review-e6u0em1o')
def files(root):
    pending=[root]
    while pending:
        p=pending.pop()
        with os.scandir(p) as entries:
            for e in entries:
                info=e.stat(follow_symlinks=False)
                if info.st_file_attributes&stat.FILE_ATTRIBUTE_REPARSE_POINT:raise ValueError('Refuse reparse point: '+e.path)
                if e.is_dir(follow_symlinks=False):pending.append(Path(e.path))
                elif e.is_file(follow_symlinks=False):yield Path(e.path),info.st_size
def root_check(root):
    allowed=[LEGACY,*[Path(os.environ['TEMP'])/n for n in TEMP_NAMES]]
    root=Path(root)
    assert root.is_absolute() and root.resolve()==root.absolute() and root in allowed
    assert root.drive.upper()=='C:' and not root.is_junction() and not root.is_symlink()
    return root
def main():
    assert not REPORT.exists();REPORT.mkdir(parents=True)
    assert ROOT.resolve().drive.upper()=='D:'
    durable=ROOT/'retained-legacy';durable.mkdir(parents=True,exist_ok=True)
    before=shutil.disk_usage('C:/').free;rows=[];totals={};existing={}
    roots=[root_check(LEGACY),*[root_check(Path(os.environ['TEMP'])/n) for n in TEMP_NAMES]]
    # Inventory before any removal. No user workspace or system cache is scanned.
    for root in roots:
        if not root.exists():continue
        category='builds' if root==LEGACY else 'temp-'+root.name
        totals[str(root)]=0
        for file,size in files(root):
            relative=file.relative_to(root);totals[str(root)]+=size
            row=dict(source=str(file),bytes=size)
            if file.suffix.lower() in DROP or '__pycache__' in file.parts:row['action']='discard_rebuildable'
            else:
                digest=sha(file)
                if file.suffix.lower() in BIN:
                    target=durable/'binary-by-sha256'/(digest+file.suffix.lower())
                else:target=durable/category/relative
                target.parent.mkdir(parents=True,exist_ok=True)
                if not target.exists():shutil.copy2(file,target)
                if str(target) not in existing:existing[str(target)]=sha(target)
                assert existing[str(target)]==digest
                row.update(action='preserve_verified',destination=str(target),sha256=digest)
            rows.append(row)
    manifest=REPORT/'inventory.json';manifest.write_text(json.dumps(dict(roots=totals,files=rows),ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    # A separate verified manifest exists on D: before each explicit C: root is removed.
    for root in roots:
        if root.exists():shutil.rmtree(root_check(root))
    after=shutil.disk_usage('C:/').free
    result=dict(completed=True,roots_bytes=totals,source_bytes=sum(totals.values()),preserved_files=sum(r['action']=='preserve_verified' for r in rows),discarded_rebuildable_files=sum(r['action']=='discard_rebuildable' for r in rows),unique_preserved_bytes=sum(Path(n).stat().st_size for n in existing),C_free_before=before,C_free_after=after,C_free_increase=after-before,inventory_sha256=sha(manifest),all_roots_removed=all(not r.exists() for r in roots),user_workspace_and_staging_untouched=True)
    (REPORT/'receipt.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf8');print(json.dumps(result,ensure_ascii=False,indent=2),flush=True)
if __name__=='__main__':main()

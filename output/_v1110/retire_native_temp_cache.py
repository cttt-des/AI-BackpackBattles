"""Retire only existing temp roots named in saved verifier directory receipts."""
import json,os,shutil,subprocess
from pathlib import Path
from native_build_storage import ROOT,STAGE,sha
from retire_native_c_cache import files,DROP,BIN
def main():
    report=STAGE/'build_storage/c_temp_retirement_20261127';assert not report.exists();report.mkdir()
    temp=Path(os.environ['TEMP']).resolve();assert temp.drive.upper()=='C:'
    recorded={}
    names=subprocess.check_output(['rg','--files',str(STAGE/'native_perf50'),'-g','inline_candidate_test_directory.txt'],text=True).splitlines()
    for name in names:
        source=Path(name);root=Path(source.read_text('utf8').strip())
        if root.is_absolute() and root.parent==temp and root.name.startswith('native-inline-timer-candidate-') and root.exists():recorded.setdefault(root,[]).append(str(source))
    before=shutil.disk_usage('C:/').free;rows=[];sizes={};durable=ROOT/'retained-legacy'
    for root,provenance in recorded.items():
        assert root.resolve()==root.absolute() and not root.is_symlink() and not root.is_junction()
        sizes[str(root)]=0
        for file,size in files(root):
            sizes[str(root)]+=size;row=dict(source=str(file),bytes=size,provenance=provenance)
            if file.suffix.lower() in DROP or '__pycache__' in file.parts:row['action']='discard_rebuildable'
            else:
                digest=sha(file);target=durable/'binary-by-sha256'/(digest+file.suffix.lower()) if file.suffix.lower() in BIN else durable/('temp-'+root.name)/file.relative_to(root)
                target.parent.mkdir(parents=True,exist_ok=True)
                if not target.exists():shutil.copy2(file,target)
                assert sha(target)==digest;row.update(action='preserve_verified',destination=str(target),sha256=digest)
            rows.append(row)
    manifest=report/'inventory.json';manifest.write_text(json.dumps(dict(roots=sizes,files=rows),ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    for root in recorded:
        assert root.resolve().parent==temp and root.name.startswith('native-inline-timer-candidate-')
        shutil.rmtree(root)
    after=shutil.disk_usage('C:/').free
    result=dict(completed=True,source_bytes=sum(sizes.values()),roots=len(recorded),C_free_before=before,C_free_after=after,C_free_increase=after-before,inventory_sha256=sha(manifest),all_removed=all(not r.exists() for r in recorded))
    (report/'receipt.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
if __name__=='__main__':main()

"""Install only the fully accepted DLL; roll back exact CEA bytes on failure."""
import ctypes,json,os,subprocess,sys,tempfile
from pathlib import Path
import psutil
from prepare_timeline_round import STAGE,REPO,BASE,WORK,ACCEPTED,EXPECTED,sha,save,verify_projection
from install_ordering_correctness import boundary,replace

def smoke(dll,tag):
    code='''import ctypes,hashlib,json,sys
sys.path.insert(0,sys.argv[2])
from bench_native_hot_path import load_simulator,OpponentPool
from pathlib import Path
s=load_simulator(Path(sys.argv[1]));pool=OpponentPool().sample((450,650),50,seed=42)[:4];packed=[s.pack_side(x,strict=True) for x in pool]
jobs=[(packed[0],p,s.make_options(round_id=packed[0].round_id,seed=seed,max_time=90.0)) for p in packed for seed in [0,42,(1<<64)-1]]
r=s.run_batch(jobs,n_threads=1,training=True);h=hashlib.sha256()
for x in r:h.update(ctypes.string_at(ctypes.addressof(x),ctypes.sizeof(x)))
print(json.dumps(dict(fights=len(r),results_sha256=h.hexdigest())))
'''
    result=json.loads(subprocess.check_output([sys.executable,'-X','utf8','-c',code,str(dll),str(STAGE)],cwd=REPO,text=True));assert result['fights']==12;save(tag+'_training_smoke.json',result);return result

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);boundary();verify_projection(WORK/'bundle_src')
    actual=sha(WORK/'bundle.dll');assert not (WORK/'installation.json').exists()
    for name in ['complete_correctness_gate.json','formal_affected_tests.json','compiled_option_receipt.json']:
        r=json.loads((WORK/name).read_bytes());assert r['passed'] and r['dll_sha256']==actual,name
    decision=json.loads((WORK/'candidate_decision.json').read_bytes());assert decision['accepted'] and decision['candidate_dll_sha256']==actual
    metrics=json.loads((WORK/'measurements_summary.json').read_bytes());assert metrics['dll_sha256']==actual and metrics['raw24_gate_passed']
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    expected=smoke(BASE/'libgdcore.dll','baseline');dist=REPO/'dist/native_1_1_10';manifest_path=dist/'manifest.json';old_manifest=manifest_path.read_bytes();manifest=json.loads(old_manifest)
    for name,digest in manifest['sha256'].items():assert sha(dist/name)==digest
    shard=BASE/'gen/shards/shard_07.cpp';old_shard=shard.read_bytes();header=BASE/'native_typed_timeline.hpp';assert not header.exists();writes=[]
    try:
        replace(shard,(WORK/'bundle_src/gen/shards/shard_07.cpp').read_bytes());writes.append(shard)
        replace(header,(WORK/'bundle_src/native_typed_timeline.hpp').read_bytes());writes.append(header)
        for dll in [BASE/'libgdcore.dll',dist/'libgdcore.dll']:replace(dll,(WORK/'bundle.dll').read_bytes());writes.append(dll)
        manifest['sha256']['libgdcore.dll']=actual;manifest['gate_sha256']=sha(WORK/'bundle_full_gate.json');replace(manifest_path,(json.dumps(manifest,indent=2)+'\n').encode());writes.append(manifest_path)
        assert sha(BASE/'libgdcore.dll')==sha(dist/'libgdcore.dll')==actual;verify_projection(BASE);boundary()
        installed=smoke(dist/'libgdcore.dll','installed');assert installed==expected
        save('installation.json',dict(passed=True,deployed=True,dll_sha256=actual,production_source_projection=verify_projection(BASE),manifest_sha256=sha(manifest_path),training_smoke_fights=12,training_matches_CEA=True,no_post_install_full_corpus_rerun=True,root_user_DLL_untouched=True))
    except BaseException:
        for path in reversed(writes):
            if path==header:header.unlink(missing_ok=True)
            elif path==shard:replace(path,old_shard)
            elif path==manifest_path:replace(path,old_manifest)
            else:replace(path,(ACCEPTED/'bundle.dll').read_bytes())
        save('installation_rollback.json',dict(restored=True,production_dll_sha256=sha(BASE/'libgdcore.dll')));boundary();raise
    print('Installed accepted typed timeline DLL '+actual,flush=True)
if __name__=='__main__':main()

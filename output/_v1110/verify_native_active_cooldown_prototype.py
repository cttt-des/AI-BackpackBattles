"""Distinct-ABI executables compare new traversal with the frozen actual686f loop."""
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_active_cooldowns import BASE,WORK,STAGE,EXPECTED,sha

def write_json(path,value):path.write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    candidate=WORK/'prototype_src';out=WORK/'differential.json';assert not out.exists()
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    frozen=json.loads((WORK/'transform.json').read_bytes())
    assert frozen['source_sha256']=={p.relative_to(candidate).as_posix():sha(p) for p in candidate.rglob('*') if p.is_file()}
    assert sha(WORK/'prototype.dll')==json.loads((WORK/'build.json').read_bytes())['dll_sha256']
    local=WORK/'test_src';assert not local.exists();local.mkdir()
    block=frozen['original_phase_blocks'][0]
    baseline_text=(BASE/'gen/shards/shard_03.cpp').read_text('utf8');assert baseline_text.count(block)==1
    assert block.count('gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta)')==1
    block=block.replace('gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta)','item_tick(cooldown_item)')
    block,n=re.subn(r'\{native_segment_snapshot\.clear\(\);cooldown_gem->fn_physicsTick\(&lv_delta, 1\);\}',r'{gem_tick(cooldown_gem);}',block);assert n==1
    assert 'native_segment_snapshot' not in block and 'lv_delta' not in block
    oracle='''#pragma once
template<class ItemTick,class GemTick>
void cooldown_original_phase(gd::BattleCtx& gd_ctx,Gd__gd_core__CoreCharacter* character,ItemTick&& item_tick,GemTick&& gem_tick) {
    const auto opponent=[character]{return character;};
'''+block+'\n}\n'
    (local/'cooldown_original_phase.hpp').write_text(oracle,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'test_native_active_cooldowns.cpp',local/'test.cpp')
    results={}
    for name,source,dll in [('baseline',BASE,BASE/'libgdcore.dll'),('candidate',candidate,WORK/'prototype.dll')]:
        with tempfile.TemporaryDirectory(prefix='native-active-cooldown-test-') as directory:
            temp=Path(directory);lib=temp/'libgdcore.dll';shutil.copyfile(dll,lib);exe=temp/'test.exe'
            flags=['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(local),'-I',str(source)]
            if name=='candidate':flags.append('-DGD_ACTIVE_NEW')
            with (WORK/(name+'_test_first.log')).open('w',encoding='utf8') as log:
                subprocess.run([*flags,str(local/'test.cpp'),str(lib),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,check=True)
                result=subprocess.run([str(exe)],capture_output=True,text=True);log.write(result.stdout+result.stderr);log.flush()
                if result.returncode:print(result.stdout+result.stderr,flush=True)
                result.check_returncode()
            write_json(WORK/(name+'_case_hashes.json'),json.loads(result.stdout));results[name]=json.loads(result.stdout)
    old,new=results['baseline'],results['candidate'];assert old['cases']==new['cases']==1856
    differences={key:[i for i,(a,b) in enumerate(zip(old[key],new[key])) if a!=b] for key in ['state_hashes','legacy_hashes']}
    report=dict(passed=not any(differences.values()),cases=old['cases'],differences=differences,
        baseline_dll_sha256=EXPECTED,candidate_dll_sha256=sha(WORK/'prototype.dll'),
        actual_independent_baseline_dll=True,original_phase_extracted_from_baseline=True,only_tick_handlers_substituted=True,
        closed_mode_explicitly_exercised=True,four_rounding_modes=True,mutable_suffixes_and_nested_phases=True,
        old_layout=old['layout'],new_layout=new['layout'],source_manifest_sha256=sha(WORK/'transform.json'),
        dependencies={p.name:sha(p) for p in local.iterdir() if p.is_file()},no_performance_claim=True)
    write_json(out,report);print(json.dumps(report,indent=2));assert report['passed'],differences

if __name__=='__main__':main()

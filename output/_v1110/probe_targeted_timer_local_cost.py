"""Match old/new loop compilation, preserving the independent actual-DLL oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import sys
import tempfile
from prepare_native_targeted_timers import BASE,WORK,STAGE,EXPECTED,sha,body

def prepare():
    original=json.loads((WORK/'transform.json').read_bytes())['original_tick_character_timers']
    candidate=body((WORK/'prototype_src/gen/shards/shard_03.cpp').read_text('utf8'),'gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers(')
    header='#pragma once\n#include "native_targeted_timers.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"\n'
    for name,text in [('reference',original),('candidate',candidate)]:
        text=text.replace('Gd__gd_core__CoreCombat::fn__tickCharacterTimers(',f'{name}_timer_loop(Gd__gd_core__CoreCombat& combat,').replace('this->','combat.')
        assert 'this' not in text
        header+=text+'\n'
    header+='inline bool timer_local_candidate=false;\ninline gd::GdVal invoke_timer_local(Gd__gd_core__CoreCombat& combat,const gd::GdVal* args,int count){return timer_local_candidate?candidate_timer_loop(combat,args,count):reference_timer_loop(combat,args,count);}\n'
    fixture=(STAGE/'test_native_targeted_timers.cpp').read_text('utf8').split('int main(){',1)[0]
    assert fixture.count('combat->fn__tickCharacterTimers(a,2)')==1
    fixture='#include "reference_targeted_timers.hpp"\n'+fixture.replace('combat->fn__tickCharacterTimers(a,2)','invoke_timer_local(*combat,a,2)')
    for name,text in [('reference_targeted_timers.hpp',header),('matched_timer_fixture.hpp',fixture)]:
        p=WORK/name
        if p.exists():assert p.read_text('utf8')==text
        else:p.write_text(text,encoding='utf8',newline='\n')

def main():
    screen='--screen' in sys.argv;prepare()
    name=('local_screen' if screen else 'local_correctness')+('_revision2' if '--revision2' in sys.argv else '')
    output=WORK/(name+'.json');assert not output.exists()
    deps={p.name:sha(p) for p in (STAGE/'test_targeted_timer_local_cost.cpp',WORK/'matched_timer_fixture.hpp',WORK/'reference_targeted_timers.hpp',WORK/'targeted_timer_fields.hpp',WORK/'prototype_src/native_targeted_timers.hpp')}
    if screen:
        check=json.loads((WORK/'local_correctness.json').read_bytes());assert check['passed'] and check['dependency_sha256']==deps
        plan=dict(pairs_per_workload=8,calls_per_arm=30000,owners=[16,48,96],gem_slots_per_item=2,matching_local_compilation=True,
            both_original_and_candidate_local_bodies_match_actual7a57=True,independent_cases=1760,
            excluded_costs='No whole-fight claim: both local arms use the enlarged new ABI/runtime. All-array write guards, layout growth and full PGO interactions require formal whole-DLL A/B.',
            dependency_sha256=deps)
        (WORK/'local_screen_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    log=WORK/f'{name}_attempt_{len(list(WORK.glob(name+"_attempt_*.log")))+1}.log'
    with tempfile.TemporaryDirectory(prefix='native-targeted-timer-local-') as directory:
        root=Path(directory);shutil.copyfile(WORK/'prototype.dll',root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as out:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-DGD_TIMER_NEW','-I',str(WORK),'-I',str(WORK/'prototype_src'),str(STAGE/'test_targeted_timer_local_cost.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=out,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe),*(['--screen'] if screen else [])],text=True,capture_output=True)
            out.write(result.stdout+result.stderr)
        if result.returncode:print(result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    if screen:
        for workload in report['workloads']:
            workload['metrics']={m:dict(paired_median_time_reduction_pct=statistics.median(100*(1-p['candidate'][m]/p['baseline'][m]) for p in workload['pairs']) if all(p['baseline'][m]>0 for p in workload['pairs']) else None,
                sum_time_reduction_pct=100*(1-sum(p['candidate'][m] for p in workload['pairs'])/sum(p['baseline'][m] for p in workload['pairs'])) if sum(p['baseline'][m] for p in workload['pairs']) else None) for m in ('wall_s','cpu_s','cycles')}
    else:
        old=json.loads((WORK/'baseline_expanded_cases.json').read_bytes())
        assert report['cases']==1760 and report['state_hashes']==old['state_hashes'] and report['legacy_hashes']==old['legacy_hashes']
        report['all_actual_old_dll_hashes_equal']=True
    report.update(passed=True,dependency_sha256=deps,baseline_dll_sha256=EXPECTED,no_whole_fight_gain_claim=True)
    output.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([dict(items=w['items'],metrics=w['metrics']) for w in v] if k=='workloads' else v) for k,v in report.items() if k not in ('state_hashes','legacy_hashes','dependency_sha256')},indent=2))

if __name__=='__main__':main()

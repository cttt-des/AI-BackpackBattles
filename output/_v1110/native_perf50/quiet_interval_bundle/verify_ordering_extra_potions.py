import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""Original potion belt, nested chains and whole default activation order."""
import argparse,ctypes,hashlib,importlib.util,json,shutil,subprocess,sys,tempfile
from pathlib import Path
from prepare_quiet_round import REPO,STAGE,WORK,sha,save
from audit_same_frame_potions import method

def reference():
    project=WORK/'potion_chain_reference_project'
    if (WORK/'original_potion_chain_reference.json').exists():return project
    shutil.copytree(WORK/'original_reference_project',project,ignore=shutil.ignore_patterns('.import','*.json'))
    stub=project/'ItemStub.gd';text=stub.read_text('utf8');text+='\nenum Priority { Lowest = -10000, Low = -1000, Normal = 0, High = 1000, Highest = 10000 }\n';stub.write_text(text,encoding='utf8',newline='\n')
    health=project/'Health.gd';health.write_text(health.read_text('utf8')+'\n'+method(STAGE/'decompiled/Items/HealthPotion.gd','getTriggerPriority'),encoding='utf8',newline='\n')
    (project/'StrongHealth.gd').write_text('extends "res://Health.gd"\n'+method(STAGE/'decompiled/Items/StrongHealthPotion.gd','getTriggerPriority'),encoding='utf8',newline='\n')
    belt='''extends "res://ItemStub.gd"
var numConsumed = 0
func isTypeInInventory(_type):
    return false
func giveRandomBuffs(_amount):
    trace.push_back("buff:Belt")
func cleanseRandomDebuffs(_amount):
    trace.push_back("cleanse:Belt")
func activate(_a = null, _b = true, _c = false, _d = null):
    pass
'''+method(STAGE/'decompiled/Items/PotionBelt.gd','onPotionEmptied')
    (project/'Belt.gd').write_text(belt,encoding='utf8',newline='\n')
    (project/'ItemBook.gd').write_text('extends Node\nvar bagtacularDescriptor = null\n',encoding='utf8')
    config=project/'project.godot';config.write_text(config.read_text('utf8')+'\nItemBook="*res://ItemBook.gd"\n',encoding='utf8',newline='\n')
    # Original bag activation does not emit the ordinary item's activated signal.
    for source,name in [('ordering_potion_chains_reference.gd','chains'),('ordering_activation_reference.gd','activation')]:
        shutil.copyfile(STAGE/source,project/(name+'.gd'))
        (project/(name+'.tscn')).write_text(f'[gd_scene load_steps=2 format=2]\n[ext_resource path="res://{name}.gd" type="Script" id=1]\n[node name="Audit" type="Node"]\nscript = ExtResource( 1 )\n',encoding='utf8')
    cases=[]
    for seed in (0,1,42,123456789,4294967295):
        for n in (16,17,32,40):
            for mode in range(3):
                key=lambda i:0 if mode==0 else (0,1000,1001)[(i*7+mode)%3]
                cases.append(dict(seed=str(seed),player=[key(i) for i in range(n)],opponent=[key(i+1) for i in range(n+1)]))
    (project/'activation_cases.json').write_text(json.dumps(cases)+'\n',encoding='utf8');save('activation_cases.json',cases)
    engine=REPO/'output/godot36/Godot_v3.6-stable_win64.exe'
    for name in ('chains','activation'):
        run=subprocess.run([str(engine),'--no-window','--path',str(project),'res://'+name+'.tscn'],capture_output=True,timeout=120)
        (WORK/(name+'_original_stdout.log')).write_bytes(run.stdout);(WORK/(name+'_original_stderr.log')).write_bytes(run.stderr);run.check_returncode();assert b'SCRIPT ERROR' not in run.stderr,run.stderr.decode('utf8',errors='replace')[:1500]
    save('original_potion_chain_reference.json',json.loads((project/'potion_chain_result.json').read_bytes()))
    save('original_activation_reference.json',json.loads((project/'activation_result.json').read_bytes()))
    return project

def native_activation(dll,tag):
    sys.path.insert(0,str(REPO))
    spec=importlib.util.spec_from_file_location('_ordering_native_binding',REPO/'dist/native_1_1_10/sim.py');binding=importlib.util.module_from_spec(spec);spec.loader.exec_module(binding)
    sim=binding.NativeSimulator(lib_path=dll,runtime_path=REPO/'dist/native_1_1_10/gd_core_runtime.json');sim.lib.gd_sim_set_dbg_events.argtypes=[ctypes.c_int];sim.lib.gd_sim_set_dbg_events(1)
    order=sim.lib.gd_sim_dbg_order;order.argtypes=[ctypes.c_int32,ctypes.c_int32,ctypes.POINTER(ctypes.c_int32)];order.restype=ctypes.POINTER(ctypes.c_int32)
    key_for={0:'Heroic Potion',1000:'Health Potion',1001:'Strong Health Potion'}
    def side(keys):
        return dict(**{'class':0},health=100,stamina=10,regen=1,items=[dict(key=key_for[x],occupied=[[3*i,0],[3*i,1]],collision=[[3*i,0],[3*i,1]],affected={},rotation=0,gems=[]) for i,x in enumerate(keys)])
    result=[]
    for case in json.loads((WORK/'activation_cases.json').read_bytes()):
        player=sim.pack_side(side(case['player']),strict=True);opponent=sim.pack_side(side(case['opponent']),strict=True)
        assert player.side.n_activation_order==opponent.side.n_activation_order==0
        sim.run_one(player,opponent,seed=int(case['seed']),max_ticks=1,native_activation_order=True)
        row={}
        for label,s,phase in [('player_shuffle',0,0),('player_sorted',0,1),('opponent_shuffle',1,0),('opponent_sorted',1,1)]:
            n=ctypes.c_int32();values=order(s,phase,ctypes.byref(n));row[label]=[values[i] for i in range(n.value)]
        result.append(row)
    expected=json.loads((WORK/'original_activation_reference.json').read_bytes());save(tag+'_activation_actual.json',result)
    assert result==expected,[i for i,(x,y) in enumerate(zip(result,expected)) if x!=y]
    return len(result)

def main():
    p=argparse.ArgumentParser();p.add_argument('--dll',type=Path);p.add_argument('--source',type=Path);p.add_argument('--tag',default='formal');p.add_argument('--reference-only',action='store_true');a=p.parse_args()
    reference()
    if a.reference_only:print('Original chain and60 default activation references ready');return
    assert a.dll is not None and a.source is not None
    activation=native_activation(a.dll,a.tag)
    build=Path(tempfile.mkdtemp(prefix='ordering-extra-potions-'))
    shutil.copyfile(a.dll,build/'libgdcore.dll')
    for name in ('test_ordering_potion_chains.cpp','test_same_frame_potion_tie.cpp','test_same_frame_potions.cpp'):shutil.copyfile(STAGE/name,build/name)
    results={}
    for label,name in [('potion_chains','test_ordering_potion_chains.cpp'),('potion_tie','test_same_frame_potion_tie.cpp')]:
        with (WORK/(a.tag+'_'+label+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(a.source),str(build/name),str(build/'libgdcore.dll'),'-o',str(build/(label+'.exe'))],stdout=log,stderr=subprocess.STDOUT,check=True)
        run=subprocess.run([str(build/(label+'.exe'))],capture_output=True,timeout=120);(WORK/(a.tag+'_'+label+'_actual.json')).write_bytes(run.stdout);(WORK/(a.tag+'_'+label+'_stderr.log')).write_bytes(run.stderr);run.check_returncode();results[label]=json.loads(run.stdout)
    assert results['potion_chains']==json.loads((WORK/'original_potion_chain_reference.json').read_bytes())
    tie=json.loads((STAGE/'same_frame_potion_audit_20261127/potion_priority_tie_comparison.json').read_bytes())['original_Godot']
    assert all(row==tie for row in results['potion_tie'].values())
    save(a.tag+'_extra_potion_tests.json',dict(passed=True,dll_sha256=sha(a.dll),default_activation_cases_without_injected_order=activation,source_game_shuffle_and_sort_both_checked=True,potion_chain_and_belt_cases=6,original_health_priorities=[1000,1001],tie_actual_potions_both_sort_paths_match_original=True,original_reference_sha256=sha(WORK/'original_potion_chain_reference.json'),actual_sha256={label:sha(WORK/(a.tag+'_'+label+'_actual.json')) for label in results},scope='Original control flow and signal order; visual/random-buff/cleanse services are isolated, full corpus tested separately'))
    print('Original belt/nested chains, tied potions and60 uninjected default activation cases passed',flush=True)
if __name__=='__main__':main()

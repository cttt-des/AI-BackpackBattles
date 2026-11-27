"""Compare focused ordering contracts with original GDScript and the deployed DLL.

This is an audit fixture, not a runtime modification or a performance trial.
"""
from pathlib import Path
import hashlib,json,os,re,shutil,subprocess,sys,tempfile

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'same_frame_potion_audit_20261127'
GAME=STAGE/'decompiled'
SOURCE=STAGE/'sim_native/native_sim_cpp/native_sim'
DLL=REPO/'dist/native_1_1_10/libgdcore.dll'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def write(p,s):p.write_text(s,encoding='utf8',newline='\n')
def method(path,name):
    text=path.read_text('utf8');m=re.search(r'^func '+re.escape(name)+r'\(.*?(?=^func |\Z)',text,re.M|re.S)
    assert m,(path,name)
    return m.group().rstrip()+'\n'

def prepare():
    assert not WORK.exists();WORK.mkdir()
    protected=json.loads((STAGE/'native_perf50/assembly_membership_prototype/user_boundary_before.json').read_bytes())
    assert all(sha(REPO/n)==h for n,h in protected['protected'].items())
    receipt=dict(production_dll_sha256=sha(DLL),head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=REPO,text=True).strip(),staged_entries_sha256=hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest(),protected=protected['protected'])
    write(WORK/'workspace_before.json',json.dumps(receipt,indent=2)+'\n')
    p=WORK/'godot_project';p.mkdir()
    write(p/'project.godot','''config_version=4
[application]
config/name="Same frame ordering audit"
[autoload]
Game="*res://Game.gd"
Util="*res://Util.gd"
EventBus="*res://EventBus.gd"
''')
    write(p/'Game.gd','''extends Node
var fightEnded = false
var combatLog = self
func logEvent(_event):
    pass
''')
    util=method(GAME/'Utility/Util.gd','dictAppend')
    # The source method is static; the extractor begins at func and keeps its body.
    write(p/'Util.gd','extends Node\n'+util)
    original=(GAME/'Utility/EventBus.gd').read_text('utf8')
    assert original.count('event: CombatEvent')==2
    adapted=original.replace('event: CombatEvent','event')
    write(p/'EventBus.gd',adapted)
    write(p/'Actor.gd','''extends Node
var curStamina = 0.0
var maxStamina = 2.0
var temporaryMaxStamina = 0.0
var allowStaminaOverflow = false
var curHealth = 40.0
var maxHealth = 100.0
enum StaminaResult { Sufficient, Insufficient }
func getCurrentStamina():
    return curStamina
func getRelativeHealth():
    return curHealth / maxHealth
'''+''.join(method(GAME/'Core/Character.gd',n) for n in ('getMaxStamina','clampStamina','useStamina')))
    write(p/'ItemStub.gd','''extends Node
var label = ""
var owner
var affected = []
var strength = 4.0
var trace
func character():
    return owner
func getP1():
    return strength
func getP2():
    return 0
func getP3():
    return 0
func getP_m(_key):
    return strength
func connectForCombat(emitter, sig, callback):
    EventBus.connectEvent(emitter, sig, self, callback)
func setState(value, _withNext = false):
    set("isFull", value)
func getAffectedItems():
    return affected
func playActivationAnimation():
    pass
func miniActivate():
    pass
func activate(_damageRes = null, _play = true, _consume = false, _animation = null):
    EventBus.emitSignal(self, "activated", [self])
func giveStamina(amount, _event = null):
    owner.curStamina += amount
    if not owner.allowStaminaOverflow:
        owner.clampStamina()
func giveEmpower(_amount, _event = null):
    pass
func heal(amount, _event = null):
    owner.curHealth = min(owner.maxHealth, owner.curHealth + amount)
func cleansePoison(_amount, _event = null):
    pass
''')
    write(p/'Potion.gd','extends "res://ItemStub.gd"\nvar isFull = true\n'+''.join(method(GAME/'Items/Potion.gd',n) for n in ('isEmpty','drink','consumePotion','onTriggerPotion','triggerPotion','activate')))
    write(p/'Heroic.gd','extends "res://Potion.gd"\n'+''.join(method(GAME/'Items/HeroicPotion.gd',n) for n in ('onTriggerPotion','onPrepare','checkStamina')))
    write(p/'Health.gd','extends "res://Potion.gd"\nvar healthThreshold = 0.5\n'+''.join(method(GAME/'Items/HealthPotion.gd',n) for n in ('onTriggerPotion','onPrepare','onDamaged')))
    provenance={str(x.relative_to(REPO)).replace('\\','/'):sha(x) for x in [GAME/'Items/Potion.gd',GAME/'Items/HeroicPotion.gd',GAME/'Items/HealthPotion.gd',GAME/'Core/Character.gd',GAME/'Utility/EventBus.gd',GAME/'Utility/Util.gd']}
    write(WORK/'reference_provenance.json',json.dumps(dict(source_sha256=provenance,unchanged_extracted_method_bodies=True,event_bus_adaptation='Erase two CombatEvent type annotations only; dispatch body unchanged',fixture_scope='UI/effect services are isolated stubs; original Potion control flow, Heroic/Health conditions, useStamina and EventBus execute in real Godot'),indent=2)+'\n')
    return p

def main():
    p=prepare()
    shutil.copyfile(Path(__file__).with_name('same_frame_potion_reference.gd'),p/'test.gd')
    exe=REPO/'output/godot36/Godot_v3.6-stable_win64.exe'
    run=subprocess.run([str(exe),'--no-window','--path',str(p),'--script','res://test.gd'],capture_output=True,timeout=60)
    (WORK/'godot_stdout.log').write_bytes(run.stdout);(WORK/'godot_stderr.log').write_bytes(run.stderr)
    run.check_returncode()
    lines=run.stdout.decode('utf8',errors='replace').splitlines()
    result=json.loads(next(x[13:] for x in lines if x.startswith('AUDIT_RESULT=')))
    write(WORK/'godot_reference.json',json.dumps(result,indent=2)+'\n')
    build=Path(tempfile.mkdtemp(prefix='potion-order-audit-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    shutil.copyfile(DLL,build/'libgdcore.dll')
    # GCC's PE internal import name is release.dll for this verified build.
    exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(DLL)]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
    internal=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
    assert Path(internal).name==internal
    if internal!='libgdcore.dll':shutil.copyfile(DLL,build/internal)
    test=Path(__file__).with_name('test_same_frame_potions.cpp');shutil.copyfile(test,build/test.name)
    with (WORK/'native_compile.log').open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(SOURCE),str(build/test.name),str(build/'libgdcore.dll'),'-o',str(build/'test.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
    run=subprocess.run([str(build/'test.exe')],capture_output=True,timeout=60)
    (WORK/'native_stdout.log').write_bytes(run.stdout);(WORK/'native_stderr.log').write_bytes(run.stderr);run.check_returncode()
    native=json.loads(run.stdout)
    write(WORK/'native_actual.json',json.dumps(native,indent=2)+'\n')
    report=dict(production_dll_sha256=sha(DLL),actual_separate_Godot_and_native_processes=True,fixture_build_directory=str(build),potion_cases_equal=native['potions']==result['potions'],potion_cases=len(result['potions']),bus_reference=result['bus'],bus_native=native['bus'],sort_reference=result['sorts'],sort_native=native['sorts'])
    report['bus_differences']=[k for k in result['bus'] if result['bus'][k]!=native['bus'][k]]
    report['generic_sort_differences']=[i for i,(a,b) in enumerate(zip(result['sorts'],native['sorts'])) if a['order']!=b['generic']]
    report['specialized_item_sort_differences']=[i for i,(a,b) in enumerate(zip(result['sorts'],native['sorts'])) if a['order']!=b['specialized']]
    before=json.loads((WORK/'workspace_before.json').read_bytes())
    assert sha(DLL)==before['production_dll_sha256'] and all(sha(REPO/n)==h for n,h in before['protected'].items())
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=REPO,text=True).strip()==before['head']
    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==before['staged_entries_sha256']
    report['production_and_protected_files_unchanged']=True
    write(WORK/'comparison.json',json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:v for k,v in report.items() if k not in ('sort_reference','sort_native')},indent=2))

if __name__=='__main__':main()

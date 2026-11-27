"""Reproduce which real potion consumes after a 17-item equal-priority sort."""
from pathlib import Path
import hashlib,json,shutil,subprocess
STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'same_frame_potion_audit_20261127'

def main():
    p=WORK/'godot_project'
    stub=p/'ItemStub.gd';text=stub.read_text('utf8')
    addition='\nfunc getTriggerPriority():\n    return 0\n'
    if 'func getTriggerPriority():' not in text:stub.write_text(text+addition,encoding='utf8',newline='\n')
    else:assert text.endswith(addition)
    (p/'tie.gd').write_text('''extends "res://test.gd"
func run():
    reset()
    var actor = keep(load("res://Actor.gd").new())
    var a = make_potion("res://Heroic.gd", actor, "A", 4)
    var b = make_potion("res://Heroic.gd", actor, "B", 4)
    var items = [a]
    for i in range(15):
        var filler = SortItem.new()
        filler.priority = 0
        filler.index = i
        items.push_back(filler)
    items.push_back(b)
    items.sort_custom(self, "compare")
    for item in items:
        if item.has_method("onPrepare"):
            item.onPrepare()
    actor.useStamina(2)
    print("TIE_RESULT=" + JSON.print({"trace":trace,"full":[a.isFull,b.isFull]}))
    reset()
    get_tree().quit()
''',encoding='utf8',newline='\n')
    (p/'tie.tscn').write_text('[gd_scene load_steps=2 format=2]\n[ext_resource path="res://tie.gd" type="Script" id=1]\n[node name="AuditTie" type="Node"]\nscript = ExtResource( 1 )\n',encoding='utf8',newline='\n')
    build=Path(json.loads((WORK/'comparison.json').read_bytes())['fixture_build_directory'])
    for name in ('test_same_frame_potion_tie.cpp','test_same_frame_potions.cpp'):shutil.copyfile(STAGE/name,build/name)
    assert hashlib.sha256((build/'libgdcore.dll').read_bytes()).hexdigest()==json.loads((WORK/'workspace_before.json').read_bytes())['production_dll_sha256']
    with (WORK/'potion_tie_compile.log').open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(STAGE/'sim_native/native_sim_cpp/native_sim'),str(build/'test_same_frame_potion_tie.cpp'),str(build/'libgdcore.dll'),'-o',str(build/'tie.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
    run=subprocess.run([str(build/'tie.exe')],capture_output=True,check=True,timeout=30);(WORK/'potion_priority_tie.json').write_bytes(run.stdout)
    native=json.loads(run.stdout)
    run=subprocess.run([str(REPO/'output/godot36/Godot_v3.6-stable_win64.exe'),'--no-window','--path',str(p),'res://tie.tscn'],capture_output=True,timeout=30)
    (WORK/'potion_tie_godot_stdout.log').write_bytes(run.stdout);(WORK/'potion_tie_godot_stderr.log').write_bytes(run.stderr);run.check_returncode()
    result=json.loads(next(x[11:] for x in run.stdout.decode().splitlines() if x.startswith('TIE_RESULT=')))
    report=dict(original_Godot=result,native=native,specialized_matches_original=native['specialized']==result,generic_matches_original=native['generic']==result)
    assert report['specialized_matches_original'] and not report['generic_matches_original']
    (WORK/'potion_priority_tie_comparison.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))
if __name__=='__main__':main()

import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
"""A mandatory source-backed Godot oracle for the correctness release."""
import argparse,hashlib,json,os,re,shutil,subprocess,sys,tempfile
from pathlib import Path
from prepare_structure_round import REPO,STAGE,WORK,BASE,sha,save

def cases():
    rows=[]
    for n in (0,1,2,3,15,16,17,18,31,32,33,64,127,128,257,512):
        rows.extend([
            [0]*n,list(range(n)),list(reversed(range(n))),
            [(i%2)*1000 for i in range(n)],[(0,1000,1001)[i%3] for i in range(n)],
            [((i*1103515245+12345)&0x7fffffff)%11-5 for i in range(n)],
            [min(i,n-1-i) for i in range(n)],[(i*7+3)%17 for i in range(n)],
        ])
    state=0x13579bdf
    for n in range(17,145):
        keys=[]
        for i in range(n):state=(state*1664525+1013904223)&0xffffffff;keys.append((state>>16)%19-9)
        rows.append(keys)
    return rows

def reference():
    result=WORK/'original_ordering_reference.json'
    keys=cases()
    if result.exists():
        assert json.loads((WORK/'sort_cases.json').read_bytes())==keys
        receipt=json.loads((WORK/'original_reference_provenance.json').read_bytes())
        assert receipt['result_sha256']==sha(result)
        return json.loads(result.read_bytes())
    project=WORK/'original_reference_project'
    if not project.exists():shutil.copytree(STAGE/'same_frame_potion_audit_20261127/godot_project',project,ignore=shutil.ignore_patterns('.import','*.log'))
    else:
        assert not (WORK/'original_reference_provenance.json').exists()
        for name in ('original_reference_stdout.log','original_reference_stderr.log'):
            shutil.copyfile(WORK/name,WORK/(name.replace('.log','_attempt1.log')))
    shutil.copyfile(STAGE/'ordering_original_reference.gd',project/'ordering.gd')
    (project/'ordering.tscn').write_text('[gd_scene load_steps=2 format=2]\n[ext_resource path="res://ordering.gd" type="Script" id=1]\n[node name="Ordering" type="Node"]\nscript = ExtResource( 1 )\n',encoding='utf8')
    raw=json.dumps(keys)+'\n';(WORK/'sort_cases.json').write_text(raw,encoding='utf8');(project/'sort_cases.json').write_text(raw,encoding='utf8')
    engine=REPO/'output/godot36/Godot_v3.6-stable_win64.exe'
    run=subprocess.run([str(engine),'--no-window','--path',str(project),'res://ordering.tscn'],capture_output=True,timeout=120)
    (WORK/'original_reference_stdout.log').write_bytes(run.stdout);(WORK/'original_reference_stderr.log').write_bytes(run.stderr)
    run.check_returncode();assert b'SCRIPT ERROR' not in run.stderr,run.stderr.decode('utf8',errors='replace')[:1200]
    data=json.loads((project/'original_result.json').read_bytes())
    result.write_text(json.dumps(data,indent=2)+'\n',encoding='utf8')
    source=STAGE/'decompiled/Utility/EventBus.gd';adapted=(project/'EventBus.gd').read_text('utf8')
    assert adapted==source.read_text('utf8').replace('event: CombatEvent','event')
    save('original_reference_provenance.json',dict(engine_sha256=sha(engine),source_event_bus_sha256=sha(source),source_game_version='1.1.10',event_bus_body_unchanged=True,source_potion_provenance=json.loads((STAGE/'same_frame_potion_audit_20261127/reference_provenance.json').read_bytes()),result_sha256=sha(result),sort_cases=len(keys),comparison_call_sequences_recorded=True,fixture_sha256={p.relative_to(project).as_posix():sha(p) for p in project.rglob('*') if p.is_file() and '.import' not in p.parts}))
    return data

def native(dll,source,tag,oracle):
    root=Path(tempfile.mkdtemp(prefix='ordering-contracts-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    shutil.copyfile(dll,root/'libgdcore.dll')
    exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(root/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
    internal=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1);assert Path(internal).name==internal
    if internal!='libgdcore.dll':shutil.copyfile(dll,root/internal)
    for name in ('test_ordering_contracts.cpp','test_same_frame_potions.cpp'):shutil.copyfile(STAGE/name,root/name)
    fixture=(STAGE/'test_same_frame_potions.cpp').read_text('utf8')
    anchor='bus->fn_emitAndLog(args,4);'
    assert fixture.count(anchor)==1
    fixture=fixture.replace(anchor,'if(ordering_literal_path)gd_native_emit_literal_event(c,V::from_obj(bus),args,arguments.arr?arguments.arr->data:nullptr,arguments.arr?arguments.arr->len:0);else bus->fn_emitAndLog(args,4);',1)
    (root/'test_same_frame_potions_all_dispatch.cpp').write_text(fixture,encoding='utf8',newline='\n')
    with (WORK/(tag+'_ordering_compile.log')).open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(source),str(root/'test_ordering_contracts.cpp'),str(root/'libgdcore.dll'),'-o',str(root/'check.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
    keys=cases();stdin=''.join(str(len(row))+' '+' '.join(map(str,row))+'\n' for row in keys).encode()
    run=subprocess.run([str(root/'check.exe')],input=stdin,capture_output=True,timeout=120)
    (WORK/(tag+'_ordering_stdout.json')).write_bytes(run.stdout);(WORK/(tag+'_ordering_stderr.log')).write_bytes(run.stderr);run.check_returncode()
    actual=json.loads(run.stdout);differences={}
    for key in ('potions','bus','bus_extra'):
        if actual[key]!=oracle[key]:differences[key]=dict(actual=actual[key],original=oracle[key])
    for key,reference_key in [('bus_literal','bus'),('bus_extra_literal','bus_extra')]:
        if actual[key]!=oracle[reference_key]:differences[key]=dict(actual=actual[key],original=oracle[reference_key])
    for i,(a,b) in enumerate(zip(actual['sort_cases'],oracle['sort_cases'])):
        if a!=b:differences['sort_'+str(i)]=dict(length=len(keys[i]),keys=keys[i],actual=a,original=b)
    assert len(actual['sort_cases'])==len(oracle['sort_cases'])==len(keys)
    report=dict(passed=not differences,dll_sha256=sha(dll),source_manifest_sha256=hashlib.sha256(json.dumps({p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file() and p.suffix in ('.hpp','.cpp')},sort_keys=True).encode()).hexdigest(),sort_cases=len(keys),potion_cases=12,event_scenarios=len(oracle['bus'])+len(oracle['bus_extra']),event_native_and_generic_both_checked=True,exact_original_comparator_call_order=True,full_original_results_compared=True,original_reference_sha256=sha(WORK/'original_ordering_reference.json'),result_sha256=sha(WORK/(tag+'_ordering_stdout.json')),differences=differences,build_directory=str(root))
    report['literal_fast_path_and_public_native_and_generic_paths_checked']=True
    report['literal_event_scenarios']=18
    report['literal_fixture_sha256']=sha(root/'test_same_frame_potions_all_dispatch.cpp')
    save(tag+'_ordering_tests.json',report);print(json.dumps({k:v for k,v in report.items() if k!='differences'}),flush=True)
    assert report['passed'],list(differences)
    return report

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--dll',type=Path,required=True);parser.add_argument('--source',type=Path,required=True);parser.add_argument('--tag',required=True);args=parser.parse_args()
    oracle=reference();native(args.dll,args.source,args.tag,oracle)
if __name__=='__main__':main()

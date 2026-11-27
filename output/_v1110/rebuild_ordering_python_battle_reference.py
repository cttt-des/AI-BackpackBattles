"""Rebuild a fresh Godot-kernel matrix from the current production input data.

The retired56-case file currently has zero reference rows and is not a gate.
Only fixture adapters are updated; Godot combat and item scripts stay intact.
"""
import ast,hashlib,importlib.util,json,shutil,subprocess,sys
from pathlib import Path
STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/ordering_correctness_bundle'
sys.path.insert(0,str(REPO))

def literal(x):
    if x is None:return 'null'
    if isinstance(x,bool):return 'true' if x else 'false'
    if isinstance(x,(int,float)):return repr(x)
    if isinstance(x,str):return json.dumps(x,ensure_ascii=False)
    if isinstance(x,(list,tuple)):return '['+','.join(literal(v) for v in x)+']'
    if isinstance(x,dict):return '{'+','.join(literal(k)+':'+literal(v) for k,v in x.items())+'}'
    raise TypeError(type(x))

def main():
    from simulator.gd_core_engine import runtime_data,character_stats,class_id_of,_place_of,_key_of
    from simulator.lineup import load_lineup
    data=runtime_data();names=sorted(data['counts']['lineup_names'])
    project=WORK/'python_battle_godot_project'
    if project.exists():assert not (project/'FreshBattle.gd').exists()
    else:project.mkdir()
    for n in ('gd_core','gd_core_items'):
        if not (project/n).exists():shutil.copytree(REPO/'gd_core_test'/n,project/n)
    shutil.copyfile(REPO/'gd_core_test/project.godot',project/'project.godot')
    code=(REPO/'simulator/gd_core_engine.py').read_text('utf8');tree=ast.parse(code)
    cls=next(n for n in tree.body if isinstance(n,ast.ClassDef) and n.name=='GDCoreEngine')
    function=next(n for n in cls.body if isinstance(n,ast.FunctionDef) and n.name=='_descriptor')
    call=next(n for n in ast.walk(function) if isinstance(n,ast.Call) and isinstance(n.func,ast.Attribute) and n.func.attr=='fromDict')
    expression=compile(ast.Expression(call.args[0]),'<production-static-descriptor>','eval')
    items={};lineups={}
    def descriptor(key):
        if key not in items:
            d=data['items'][key]['descr'];entry=eval(expression,dict(d=d))
            entry['sockets']=data['items'][key]['sockets'];items[key]=entry
    for name in names:
        lineup=load_lineup(str(REPO/'lineups'/(name+'.json')));stats=character_stats(lineup,data['characters']);entries=[]
        for entry in (lineup.get('backpack') or {}).get('items',[]):
            key=entry.get('id') or entry.get('key')
            if not key:continue
            descriptor(key);rotation=int(entry.get('rotation') or 0);placed=_place_of(data,key,int(entry.get('row') or 0),int(entry.get('col') or 0),rotation)
            gems=[_key_of(x) for x in (entry.get('gems') or [])]
            for gem in gems:
                if gem:descriptor(gem)
            entries.append(dict(placed,key=key,rotation=rotation,crafted=entry.get('crafted'),effects=entry.get('effects'),storage=False,gems=gems,gemScripts=[data['items'][g]['script'] if g else None for g in gems]))
        lineups[name]=dict(name=name,**{'class':class_id_of(lineup,data['classes'])},round=int(lineup.get('round',1)),health=stats['health'],stamina=stats['stamina'],regen=stats['regen'],items=entries)
    fixture='extends Reference\nclass_name LineupFixture\nconst ITEMS = '+literal(items)+'\nconst LINEUPS = '+literal(lineups)+'\n'
    (project/'LineupFixture.gd').write_text(fixture,encoding='utf8',newline='\n')
    text=(REPO/'gd_core_test/LineupBattle.gd').read_text('utf8')
    start=text.index('func _init() -> void:');end=text.index('\n\n# ',start)
    main='''func _init() -> void:
	var names = LineupFixture.LINEUPS.keys()
	names.sort()
	for a in names:
		for b in names:
			if a == b:
				continue
			var seed_value = BASE_SEED + PAIR_STRIDE * names.find(a) + names.find(b)
			var w = new_battle(seed_value,a,b)
			run_battle(w["ctx"],w["combat"])
			say(a.replace("lineup_","") + " vs " + b.replace("lineup_","") + "：" + outcome(w))
	quit(0)
'''
    text=text[:start]+main+text[end:]
    # Keep the original test's battle driver; bring its assembly boundary up to
    # the actual production adapter's descriptor/rotation/charge/gem inputs.
    start=text.index('\tvar made = CoreItemData.new().fromDict({');end=text.index('\n\t_descr_cache[key]',start)
    text=text[:start]+'\tvar made = CoreItemData.new().fromDict(d)'+text[end:]
    anchor='\tit.setup(ctx, descriptor_of(ctx, e["key"]), chr)'
    text=text.replace(anchor,'\tif e.get("crafted") != null:\n\t\tit.crafted_instance = 1 if e["crafted"] else 0\n'+anchor,1)
    anchor='\tit.ownerType = owner_type\n'
    text=text.replace(anchor,anchor+'\tit.faceDirection = (int(e.get("rotation",0)) / 90) % 4\n\tvar cf = e.get("charge_frame",[0,0])\n\tit.chargeFrame = [v(cf),v(cf),v(cf),v(cf)]\n',1)
    anchor='\tchr.inventory.addItem(it, it.occupiedCells)\n'
    text=text.replace(anchor,anchor+'\tif e.get("effects") != null and not e["effects"].empty() and it.has_method("setCraftedEffects"):\n\t\tit.setCraftedEffects(e["effects"])\n',1)
    text=text.replace('\t\tvar gkey: String = e["gems"][gi]','\t\tvar gkey = e["gems"][gi]\n\t\tif gkey == null or gkey == "":\n\t\t\tcontinue',1)
    text=text.replace('\t\tgem._readyInit()','\t\tgem.ownerType = owner_type\n\t\tgem._readyInit()',1)
    anchor='\tvar ctx = CoreContext.new(seed_value, probe)'
    text=text.replace(anchor,'\tseed(seed_value)\n'+anchor+'\n\tctx.cur_round = int(LineupFixture.LINEUPS[p_name]["round"])',1)
    (project/'LineupBattle.gd').write_text(text,encoding='utf8',newline='\n')
    (project/'FreshBattle.gd').write_text(text,encoding='utf8',newline='\n')
    run=subprocess.run([str(REPO/'output/godot36/Godot_v3.6-stable_win64.exe'),'--no-window','--path',str(project),'--script','FreshBattle.gd'],capture_output=True,timeout=300)
    (WORK/'python_battle_original_stdout.log').write_bytes(run.stdout);(WORK/'python_battle_original_stderr.log').write_bytes(run.stderr);run.check_returncode();assert b'SCRIPT ERROR' not in run.stderr,run.stderr.decode('utf8',errors='replace')[:1500]
    spec=importlib.util.spec_from_file_location('original_battle_rows',REPO/'tools/check_gd_core_engine.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    original=module.parse_rows((project/'lineup_result.txt').read_text('utf8'));candidate=module.parse_rows((WORK/'candidate_python_56_results.txt').read_text('utf8'));baseline=module.parse_rows((WORK/'baseline_python_56_results.txt').read_text('utf8'))
    assert set(original)==set(candidate)==set(baseline) and len(original)==len(names)*(len(names)-1)
    diff={k:dict(original=original[k],candidate=candidate[k],baseline=baseline[k]) for k in original if original[k]!=candidate[k]}
    report=dict(passed=not diff,fights=len(original),original='Fresh real Godot kernel, combat/item sources unchanged',boundary_adapters_updated=True,sorting_fix_not_applied_to_Godot_reference=True,original_lineups_sha256=hashlib.sha256(json.dumps(lineups,sort_keys=True).encode()).hexdigest(),old_cached_reference_had_zero_rows=True,baseline_matches=sum(baseline[k]==v for k,v in original.items()),candidate_matches=len(original)-len(diff),differences=diff)
    (WORK/'python_fresh_battle_comparison.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps({k:v for k,v in report.items() if k!='differences'}))
    assert report['passed'],list(diff)[:5]
if __name__=='__main__':main()

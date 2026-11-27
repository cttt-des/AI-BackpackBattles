"""Guarded numerical segment builds and inherited complete proof gates."""
import json,os,runpy,shutil,subprocess,sys,tempfile
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import psutil
from native_build_storage import isolated_build,adapt_formal_builder
import prepare_quiet_round as p
import next_two as inherited

def rewrite(text):
    return text.replace('prepare_frame_guard_retained','prepare_quiet_retained').replace('prepare_next_two_retained','prepare_quiet_retained').replace('prepare_frame_guard_reuse','prepare_quiet_round').replace('prepare_next_two_round','prepare_quiet_round')
inherited.prepared=lambda:p
inherited.rewrite=rewrite

def run_managed(script,*args,log=None):
    command=[sys.executable,'-u','-X','utf8',str(p.STAGE/'run_native_managed.py'),str(script),*map(str,args)]
    if log:
        initial=log;attempt=2
        while log.exists():log=initial.with_name(initial.stem+f'_attempt{attempt}'+initial.suffix);attempt+=1
        with log.open('wb') as stream:subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,check=True)
    else:subprocess.run(command,check=True)
inherited.run=run_managed

def setup():inherited.setup()

@isolated_build
def preflight():
    p.verify_projection(p.WORK/'bundle_src')
    subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(p.WORK/'bundle_src/engine_wrapper.cpp')],check=True)
    p.save('candidate_syntax_preflight.json',dict(passed=True,source_sha256=p.sha(p.WORK/'bundle_src/engine_wrapper.cpp')))

@isolated_build
def prototype():
    assert not (p.WORK/'prototype.dll').exists();p.verify_projection(p.WORK/'bundle_src');psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='quiet-normal-'));objects=root/'objects'
    os.environ.update(NATIVE_SIM_OBJ=str(objects),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    module=runpy.run_path(str(p.WORK/'bundle_src/build_windows.py'));module['build'].__globals__['ThreadPoolExecutor']=lambda max_workers:ThreadPoolExecutor(max_workers=min(2,max_workers))
    library=module['build']();shutil.move(library,p.WORK/'prototype.dll');paths={s.name:s for s in objects.glob('*.o')};assert len(paths)==20
    p.verify_projection(p.WORK/'bundle_src');p.save('normal_object_paths.json',{n:str(s) for n,s in paths.items()})
    p.save('prototype_build.json',dict(passed=True,dll_sha256=p.sha(p.WORK/'prototype.dll'),objects_sha256={n:p.sha(s) for n,s in paths.items()},full20_normal_units=True,maximum_workers=2,below_normal=True,only_semantic_not_for_speed_or_deployment=True))

def affected(formal=False,tag=None,dll=None):
    tag=tag or ('formal' if formal else 'prototype');library=dll or p.WORK/('bundle.dll' if formal else 'prototype.dll')
    inherited.run(p.STAGE/'verify_quiet_core.py','--tag',tag,'--dll',library,log=p.WORK/(tag+'_quiet_core.log'))
    r=json.loads((p.WORK/(tag+'_quiet_core_tests.json')).read_bytes());assert r['passed'] and r['dll_sha256']==p.sha(library)
    p.save(tag+'_affected_tests.json',r)

def regenerate():inherited.regenerate()

@isolated_build
def build():
    script=p.STAGE/'build_ordering_release.py'
    assert script.read_bytes()==subprocess.check_output(['git','show',p.ARCHIVE+':output/_v1110/build_ordering_release.py'],cwd=p.REPO)
    text=script.read_text('utf8').replace('from prepare_ordering_correctness import','from prepare_quiet_round import')
    text=text.replace("WORK/'prototype_ordering_tests.json'","WORK/'prototype_affected_tests.json'")
    old="    assert all(json.loads((WORK/n).read_bytes())['passed'] for n in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json'))"
    assert text.count(old)==1;text=text.replace(old,"    assert json.loads((WORK/'full_regeneration_test.json').read_bytes())['passed']")
    text=adapt_formal_builder(text).replace('ordering-formal-','quiet-formal-')
    # Historical builder stays immutable. Future invocations select scheduling
    # independently; object options and every correctness/performance gate stay frozen.
    assert text.count("build_dll(src,objects/'instrumented.dll',2,")==1
    assert text.count("build_dll(src,objects/'release.dll',2,")==1
    text=text.replace("build_dll(src,objects/'instrumented.dll',2,", "build_dll(src,objects/'instrumented.dll',0,")
    text=text.replace("build_dll(src,objects/'release.dll',2,", "build_dll(src,objects/'release.dll',0,")
    text=text.replace('original FP flags; max2 jobs', 'original FP flags; memory-aware independent compile/LTO jobs')
    exec(compile(text,str(script),'exec'),dict(__name__='__main__',__file__=str(p.STAGE/'quiet_round.py')))

def fast_full(tag,dll=None):
    dll=dll or p.WORK/('prototype.dll' if tag=='prototype' else 'bundle.dll')
    inherited.run(p.STAGE/'verify_quiet_full.py','--tag',tag,'--dll',dll,log=p.WORK/(tag+'_quiet_fast_full.log'))
    r=json.loads((p.WORK/(tag+'_quiet_fast_full_tests.json')).read_bytes());assert r['passed'] and r['dll_sha256']==p.sha(dll)

def qualify():
    # Each managed verifier now disposes its own workspace. The extra-potion
    # verifier must not borrow the preceding ordering verifier's deleted folder.
    script=p.WORK/'verify_ordering_extra_potions.py';text=script.read_text('utf8')
    old="    build=Path(json.loads((WORK/(a.tag+'_ordering_tests.json')).read_bytes())['build_directory'])"
    if old in text:
        backup=p.WORK/'qualification_fixture_revisions';backup.mkdir(exist_ok=True)
        shutil.copyfile(script,backup/'verify_ordering_extra_potions_before_storage_fix.py')
        text=text.replace('import argparse,ctypes,hashlib,importlib.util,json,shutil,subprocess,sys', 'import argparse,ctypes,hashlib,importlib.util,json,shutil,subprocess,sys,tempfile')
        text=text.replace(old,"    build=Path(tempfile.mkdtemp(prefix='ordering-extra-potions-'))\n    shutil.copyfile(a.dll,build/'libgdcore.dll')")
        script.write_text(text,encoding='utf8',newline='\n')
        p.save('potion_fixture_storage_fix.json',dict(previous_sha256=p.sha(backup/'verify_ordering_extra_potions_before_storage_fix.py'),current_sha256=p.sha(script),fresh_self_contained_managed_D_workspace=True,game_cases_and_expectations_unchanged=True))
    inherited.qualify()
    if not (p.WORK/'formal_quiet_fast_full_tests.json').exists():fast_full('formal')
    gate=json.loads((p.WORK/'complete_correctness_gate.json').read_bytes());r=json.loads((p.WORK/'formal_quiet_fast_full_tests.json').read_bytes())
    assert r['passed'] and r['dll_sha256']==gate['dll_sha256']
    gate.update(optimization_enabled_full2604=True,optimized_full_corpus_frames=r['coverage']['frames'],optimized_full_corpus_receipt_sha256=p.sha(p.WORK/'formal_quiet_fast_full_tests.json'))
    p.save('complete_correctness_gate.json',gate)

def post():
    inherited.affected=affected;inherited.post();fast_full('post_ab')
    r=json.loads((p.WORK/'post_ab_directed_checks.json').read_bytes());r['optimized_full2604_receipt_sha256']=p.sha(p.WORK/'post_ab_quiet_fast_full_tests.json');p.save('post_ab_directed_checks.json',r)

def measure():inherited.measure()

def install():
    assert json.loads((p.WORK/'formal_quiet_fast_full_tests.json').read_bytes())['passed']
    assert json.loads((p.WORK/'post_ab_quiet_fast_full_tests.json').read_bytes())['passed']
    inherited.affected=affected;inherited.install()

def drive():
    w=p.WORK
    if not (w/'prototype_affected_tests.json').exists():affected()
    if not (w/'prototype_quiet_fast_full_tests.json').exists():fast_full('prototype')
    if not (w/'full_regeneration_test.json').exists():regenerate()
    if not (w/'bundle.dll').exists():inherited.run(p.STAGE/'quiet_round.py','build',log=w/'formal_build_first.log')
    if not (w/'formal_affected_tests.json').exists():affected(True)
    if not (w/'formal_quiet_fast_full_tests.json').exists():qualify()
    assert json.loads((w/'complete_correctness_gate.json').read_bytes())['optimization_enabled_full2604']
    print('All semantic gates passed; ready for frozen timing without concurrent work',flush=True)

if __name__=='__main__':
    actions={'setup':setup,'preflight':preflight,'prototype':prototype,'affected':affected,'formal_affected':lambda:affected(True),'regenerate':regenerate,'build':build,'qualify':qualify,'drive':drive,'post':post,'measure':measure,'install':install,'prototype_fast_full':lambda:fast_full('prototype')}
    actions[sys.argv[1]]()

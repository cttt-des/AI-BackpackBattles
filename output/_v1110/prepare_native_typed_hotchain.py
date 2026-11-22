"""Stage a Hook component for a complete typed hot-chain experiment, not a standalone gain."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/typed_hotchain_prototype'
EXPECTED='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def hook_component(text):
    start=text.index('    void on_log_event(');end=text.index('    bool call_method(',start)
    old=text[start:end]
    assert old.count('ev->get_prop(')==7 and old.count('        dbg_record_event(gd_ctx, ev);')==1
    method=old.replace('ev->get_prop(','native_read_event(')
    marker='        dbg_record_event(gd_ctx, ev);'
    addition='''
        // Only the packed bridge's sealed graph has stable generated dynamic
        // types across callbacks. Ordinary C++ contexts retain every getter.
        const auto* exact_event=(gd_ctx.native_timer_watch.closed_world && ev &&
            typeid(*ev)==typeid(Gd__gd_core__CoreEvent))
            ? static_cast<const Gd__gd_core__CoreEvent*>(ev):nullptr;
        const auto native_read_event=[&](gd::SymId property,gd::GdVal& value) {
            if(exact_event) {
                if(property==g_syms.type){value=exact_event->f_type;return true;}
                if(property==g_syms.target){value=exact_event->f_target;return true;}
                if(property==g_syms.origin){value=exact_event->f_origin;return true;}
                if(property==g_syms.params){value=exact_event->f_params;return true;}
            }
            return ev->get_prop(property,value);
        };
'''
    method=method.replace(marker,marker+addition,1)
    assert method.replace(addition,'',1).replace('native_read_event(','ev->get_prop(')==old
    text=text[:start]+method+text[end:]
    assert text.count('#include <typeinfo>')==1
    text=text.replace('#include <typeinfo>','#include <typeinfo>\n#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"',1)
    return text,dict(original_method_sha256=hashlib.sha256(old.encode()).hexdigest(),candidate_method_sha256=hashlib.sha256(method.encode()).hexdigest(),
        original_getter_calls=7,arithmetic_and_branch_body_unchanged=True,dbg_record_event_still_first=True,
        ordinary_context_original_getters_retained=True,exact_rtti_guard_has_no_user_virtual_calls=True,
        fields_always_read_live=True,closed_generated_graph_dynamic_types_stable_across_callbacks=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    frozen=json.loads((STAGE/'native_perf50/closed_timer_bundle/source_before_build.json').read_bytes())
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()};assert before==frozen
    p=src/'engine_wrapper.cpp';text,proof=hook_component(p.read_text('utf8'));p.write_text(text,encoding='utf8',newline='\n')
    subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(p)],check=True)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert [n for n in before if before[n]!=after[n]]==['engine_wrapper.cpp']
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_before_sha256=before,source_sha256=after,
        hook_component=proof,syntax_checked=True,components_staged=['sealed Hook field reads'],
        complete_typed_damage_chain_not_implemented_yet=True,semantic_differential_not_run_yet=True,
        not_ready_for_formal_ab=True,no_performance_or_deployment_claim=True)
    (WORK/'transform_stage1.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Staged Hook component,syntax checked; complete typed damage chain and differential still required')

if __name__=='__main__':main()

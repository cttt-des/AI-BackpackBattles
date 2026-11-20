"""Hoist native context validation within one Buff method; preserve live field reads."""
import argparse
import hashlib
from pathlib import Path
import re
from optimize_native_serial_paths import method_body

ORIGINAL_METHOD = '06caa727976b8903fa12ccd0c5f9bb5e1b2e5ca935aa3d36b1d7abb758d6962c'
LOWERED_METHOD = '7da6f83dbde9a85ff38873d096f8ffb19ee433bbef841619714dac89a2b3a6ad'
CONTEXT_GETTER = '62ebbe57bac10f238528412637a749d8443a40bea074b46c757f5ad239760b46'
RUNTIME_GETTER = '2784416e21bfa9b1671b9fda9b18956702e029970b464fdfc3324d06f21f4dee'
WRAPPER_INPUT = '1dd69d3aa317890b1be03e1e65acb837322ce8ca0c4cbdcbacf85a8aabd45a88'
SHARD_INPUT = 'e39d297289c832f5237609815630ba3cc4bd435345572c04114bfb42e2d1bced'
SCOPE = '// The bridge owns all battle objects until the whole arena resets.\nthread_local gd::BattleCtx* native_buff_active_battle = nullptr;\nstruct NativeBuffContextScope {\n    gd::BattleCtx* previous;\n    explicit NativeBuffContextScope(gd::BattleCtx& battle):previous(native_buff_active_battle) {\n        native_buff_active_battle=&battle;\n    }\n    ~NativeBuffContextScope(){native_buff_active_battle=previous;}\n    NativeBuffContextScope(const NativeBuffContextScope&)=delete;\n    NativeBuffContextScope& operator=(const NativeBuffContextScope&)=delete;\n};\n\n'
SCOPE_LINE = '    NativeBuffContextScope native_buff_scope(battle);\n'
HELPER = '\nGd__gd_core__CoreContext* gd_native_buff_context(gd::BattleCtx& battle,const gd::GdVal& context) {\n    if(native_buff_active_battle!=&battle)return nullptr;\n    if(context.kind!=gd::GdVal::Kind::Obj || !context.obj ||\n       &typeid(*context.obj)!=&typeid(Gd__gd_core__CoreContext))return nullptr;\n    return static_cast<Gd__gd_core__CoreContext*>(context.obj);\n}\n'
DECL = 'extern Gd__gd_core__CoreContext* gd_native_buff_context(gd::BattleCtx&,const gd::GdVal&);\n'
LAMBDA = '    Gd__gd_core__CoreContext* native_context=nullptr;\n    bool native_context_checked=false;\n    const auto buff_context_property=[this,&gd_ctx,&native_context,&native_context_checked](gd::SymId property)->gd::GdVal {\n        // Check lazily at the original first getter; unused context paths stay untouched.\n        if(!native_context_checked) {\n            native_context_checked=true;\n            native_context=gd_native_buff_context(gd_ctx,this->f_ctx);\n        }\n        if(native_context && this->f_ctx.kind==gd::GdVal::Kind::Obj && this->f_ctx.obj==native_context) {\n            switch(property) {\n                case SYM_GEN_bus_1408: return native_context->f_bus;\n                case SYM_GEN_combat_log_1410: return native_context->f_combat_log;\n                case SYM_GEN_hooks_1409: return native_context->f_hooks;\n                case SYM_GEN_player_1302: return native_context->f_player;\n                case SYM_GEN_rng_1406: return native_context->f_rng;\n                case SYM_GEN_time_1411: return native_context->f_time;\n            }\n        }\n        return gd::get_prop(gd_ctx,this->f_ctx,property);\n    };\n'
SITES = 15
FIELDS = [('SYM_GEN_bus_1408', 'bus'), ('SYM_GEN_combat_log_1410', 'combat_log'), ('SYM_GEN_hooks_1409', 'hooks'), ('SYM_GEN_player_1302', 'player'), ('SYM_GEN_rng_1406', 'rng'), ('SYM_GEN_time_1411', 'time')]


def digest(body):return hashlib.sha256(body.encode()).hexdigest()


def normalize_wrapper(source):
    present=[part in source for part in (SCOPE,SCOPE_LINE,HELPER)]
    if not any(present):return source
    if not all(present) or any(source.count(part)!=1 for part in (SCOPE,SCOPE_LINE,HELPER)):
        raise ValueError('The native Buff scope region changed')
    for part in (SCOPE,SCOPE_LINE,HELPER):source=source.replace(part,'',1)
    return source


def normalize_shard(source):
    match=method_body(source,'CoreBuff','gainTemporary');body=match[0]
    if digest(body)==LOWERED_METHOD:
        assert body.count(LAMBDA)==1;body=body.replace(LAMBDA,'',1)
        body,count=re.subn(r'buff_context_property\((SYM_GEN_\w+_\d+)\)',lambda m:f'gd::get_prop(gd_ctx, this->f_ctx, {m[1]})',body)
        assert count==SITES and digest(body)==ORIGINAL_METHOD
        source=source[:match.start()]+body+source[match.end():]
    elif digest(body)!=ORIGINAL_METHOD:raise ValueError('The verified Buff method changed')
    if DECL in source:
        assert source.count(DECL)==1;source=source.replace(DECL,'',1)
    return source


def transform_wrapper(source):
    source=normalize_wrapper(source)
    if digest(source)!=WRAPPER_INPUT:raise ValueError('The verified native bridge changed')
    anchor='static void run_one_internal(\n';assert source.count(anchor)==1
    source=source.replace(anchor,SCOPE+anchor,1)
    anchor='    battle.reset_for_battle(opts.seed);\n';assert source.count(anchor)==1
    return source.replace(anchor,SCOPE_LINE+anchor,1)+HELPER


def transform_shard(source):
    source=normalize_shard(source)
    if digest(source)!=SHARD_INPUT:raise ValueError('The verified Buff shard changed')
    match=method_body(source,'CoreBuff','gainTemporary');body=match[0]
    body,count=re.subn(r'gd::get_prop\(gd_ctx, this->f_ctx, (SYM_GEN_\w+_\d+)\)',lambda m:f'buff_context_property({m[1]})',body)
    assert count==SITES
    anchor='    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n';assert body.count(anchor)==1
    body=body.replace(anchor,anchor+LAMBDA,1);assert digest(body)==LOWERED_METHOD
    source=source[:match.start()]+body+source[match.end():]
    anchor='#include "../hdrs/Gd__gd_core__CoreContext.hpp"\n';assert source.count(anchor)==1
    return source.replace(anchor,anchor+DECL,1)


def optimize(native):
    ctx=(native/'gen/shards/shard_07.cpp').read_text('utf8');rt=(native/'gd_rt.cpp').read_text('utf8')
    a=re.search(r'^bool Gd__gd_core__CoreContext::get_prop\([^\n]*\n.*?^\}\n',ctx,re.M|re.S)[0]
    b=re.search(r'^GdVal get_prop\([^\n]*\n.*?^\}\n',rt,re.M|re.S)[0]
    if digest(a)!=CONTEXT_GETTER or digest(b)!=RUNTIME_GETTER:raise ValueError('A property getter changed')
    for name,transform in [('engine_wrapper.cpp',transform_wrapper),('gen/shards/shard_00.cpp',transform_shard)]:
        path=native/name;source=path.read_text('utf8');output=transform(source)
        if path.read_bytes()!=output.encode():path.write_text(output,encoding='utf8',newline='\n')
    print(f'Buff context: lazy bridge-only exact validation, {SITES} live property reads, receiver replacement fallback',flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)

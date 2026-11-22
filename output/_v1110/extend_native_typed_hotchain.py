"""Lower a complete sealed takeDamage path, native pointer entry and scalar blocks."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
from prepare_native_typed_hotchain import BASE,WORK,STAGE,EXPECTED,ARCHIVE,sha
from prepare_native_damage_records import prepare,body

def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old));return text.replace(old,new,1)

def transform(native):
    design=prepare(native)
    candidate=design['candidate'];original=design['original']
    marker='\n    }\n    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();'
    kernel=candidate[:candidate.index(marker)]
    prefix='''gd::GdVal Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
'''
    assert kernel.startswith(prefix);kernel=kernel[len(prefix):]
    kernel=once(kernel,'    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();','    gd::GdVal lv_damageSource = gd::GdVal::from_obj(input_source);')
    kernel=once(kernel,'    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());','    gd::GdVal lv_triggerEvent = trigger_event;')
    r='native_damage_result'
    a=next(line for line in kernel.splitlines() if 'gd::GdVal lv_activeDmgResi =' in line)
    lines=kernel.splitlines();idx=lines.index(a);b=lines[idx+1]
    assert 'gd::gd_round(gd::gd_mul' in b
    kernel=once(kernel,a+'\n'+b,'        gd::native_typed_damage_resistance(gd_ctx,*native_damage_result,this->f_damageResistance);')
    old=f'({r}->f_damage = gd::gd_coerce_int(gd::gd_sub(({r}->f_damage), this->f_damageReduction)))'
    kernel=once(kernel,old,f'({r}->f_damage = gd::native_typed_damage_subtract(gd_ctx,{r}->f_damage,this->f_damageReduction))')
    old=f'''        ({r}->f_damage = gd::gd_coerce_int(gd::gd_sub(({r}->f_damage), ({r}->f_damageReduction))));
        ({r}->f_damage = gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), ({r}->f_damage))));'''
    kernel=once(kernel,old,'        gd::native_typed_damage_after_signal(gd_ctx,*native_damage_result);')
    old=f'({r}->f_healthDamage = gd::gd_coerce_int(gd::gd_sub(({r}->f_healthDamage), lv_curBlock)))'
    kernel=once(kernel,old,f'({r}->f_healthDamage = gd::native_typed_damage_subtract(gd_ctx,{r}->f_healthDamage,lv_curBlock))')
    kernel=once(kernel,f'        this->f_curHealth = gd::gd_coerce_float(gd::gd_sub(this->f_curHealth, ({r}->f_healthDamage)));',
                '        gd::native_typed_damage_health(gd_ctx,this->f_curHealth,native_damage_result->f_healthDamage);')
    # All three integer iterators have an unused index. Their temporary arrays
    # never escape; only the sealed generated graph may skip the allocation.
    pattern=re.compile(r'(?P<indent> +)\{\n +gd::GdVal (_t\d+) = gd::gd_iter_seq\(gd_ctx.arena, lv_attackEffectCount\);\n +gd::GdArr\* (_t\d+) = .*?\n +uint32_t (_len__t\d+) = .*?\n +for \(uint32_t (_t\d+) = 0; .*?\n +gd::GdVal lv_i = .*?\n(?P<action> +\(void\).*?;)\n +\}\n +\}',re.S)
    loops=[]
    def lower_loop(m):
        assert len(re.findall(r'\blv_i\b',m[0]))==1 and m['action'].count('\n')==0
        assert '_behavior_call_' in m['action'] and 'lv_damageRes' in m['action']
        loops.append(m[0]);return m['indent']+'gd::native_typed_damage_each(gd_ctx,lv_attackEffectCount,[&] {\n'+m['action']+'\n'+m['indent']+'});'
    kernel=pattern.sub(lower_loop,kernel);assert len(loops)==3,len(loops)
    assert kernel.count('return lv_damageRes;')==2
    kernel=kernel.replace('return lv_damageRes;','return native_damage_result;')
    assert kernel.endswith('    return gd::GdVal::null();');kernel=kernel[:-len('    return gd::GdVal::null();')]+'    return nullptr;'
    function='''Gd__gd_core__CoreDamageResult* Gd__gd_core__CoreCharacter::fn_takeDamage_native(Gd__gd_core__CoreDamageSource* input_source,const gd::GdVal& trigger_event) {
    gd::BattleCtx& gd_ctx=*this->rt_ctx_;
    gd::native_typed_damage_count(gd_ctx,0);
'''+kernel+'\n}'
    entry='''    if(gd_ctx.native_event_kernel && gd_ctx.native_timer_watch.closed_world && _argc>0 &&
       _args[0].kind==gd::GdVal::Kind::Obj && _args[0].obj &&
       typeid(*_args[0].obj)==typeid(Gd__gd_core__CoreDamageSource)) {
        const gd::GdVal trigger=_argc>1?_args[1]:gd::GdVal::null();
        return gd::GdVal::from_obj(fn_takeDamage_native(static_cast<Gd__gd_core__CoreDamageSource*>(_args[0].obj),trigger));
    }
'''
    wrapper=once(original,'    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n','    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n'+entry)
    assert wrapper.replace(entry,'',1)==original
    p=native/'gen/shards/shard_02.cpp';text=p.read_text('utf8');text=once(text,original,function+'\n'+wrapper)
    deal=body(text,'gd::GdVal Gd__gd_core__CoreCharacter::fn_dealDamage(')
    old='''    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_damageSource, lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_takeDamage>(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1148, _ca, 2); })();'''
    new='''    gd::GdVal lv_res;
    if(gd_ctx.native_timer_watch.closed_world && this->f_opponent.kind==gd::GdVal::Kind::Obj && this->f_opponent.obj &&
       typeid(*this->f_opponent.obj)==typeid(Gd__gd_core__CoreCharacter) && lv_damageSource.kind==gd::GdVal::Kind::Obj && lv_damageSource.obj &&
       typeid(*lv_damageSource.obj)==typeid(Gd__gd_core__CoreDamageSource)) {
        gd::native_typed_damage_count(gd_ctx,1);
        lv_res=gd::GdVal::from_obj(static_cast<Gd__gd_core__CoreCharacter*>(this->f_opponent.obj)->fn_takeDamage_native(static_cast<Gd__gd_core__CoreDamageSource*>(lv_damageSource.obj),lv_triggerEvent));
    } else {
'''+old+'''
    }'''
    new_deal=once(deal,old,new);text=once(text,deal,new_deal)
    text='#include "../../native_typed_damage_math.hpp"\n'+text;p.write_text(text,encoding='utf8',newline='\n')
    hdr=native/'gen/hdrs/Gd__gd_core__CoreCharacter.hpp';text=hdr.read_text('utf8')
    text=once(text,'struct Gd__gd_core__CoreCharacter :','struct Gd__gd_core__CoreDamageSource;\nstruct Gd__gd_core__CoreDamageResult;\n\nstruct Gd__gd_core__CoreCharacter :')
    declaration='    gd::GdVal fn_takeDamage(const gd::GdVal* _args, int _argc);'
    text=once(text,declaration,declaration+'\n    Gd__gd_core__CoreDamageResult* fn_takeDamage_native(Gd__gd_core__CoreDamageSource*,const gd::GdVal&);')
    hdr.write_text(text,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_typed_damage_math.hpp',native/'native_typed_damage_math.hpp')
    p=native/'gd_rt.cpp';text=p.read_text('utf8')+'''
namespace gd {
static thread_local uint64_t native_typed_damage_counts[12]{};
void native_typed_damage_hit(unsigned field){if(field<12)++native_typed_damage_counts[field];}
}
extern "C" uint64_t gd_diag_native_typed_damage_stat(unsigned field){return field<12?gd::native_typed_damage_counts[field]:0;}
''';p.write_text(text,encoding='utf8',newline='\n')
    return dict(direct_record_operations=design['counts'],integer_temporary_loops_lowered=len(loops),
        original_take_damage_sha256=hashlib.sha256(original.encode()).hexdigest(),native_body_sha256=hashlib.sha256(function.encode()).hexdigest(),
        original_paths_byte_preserved=True,native_pointer_parameter_and_return=True,
        scoped_scalar_blocks=['resistance','damage reduction','post-signal clamp','block damage','health'],
        callbacks_always_see_committed_fields=True,all_rng_calls_retained=True,
        no_arithmetic_reassociation=True,source_result_fields_are_live_not_snapshots=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    src=WORK/'prototype_src';old=json.loads((WORK/'transform_stage1.json').read_bytes())
    assert old['source_sha256']=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    proof=transform(src)
    for rel in ('gen/shards/shard_02.cpp','gd_rt.cpp'):
        subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(src/rel)],check=True)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,source_before_sha256=old['source_before_sha256'],
        hook_component=old['hook_component'],typed_damage_component=proof,syntax_checked=True,semantic_differential_not_run_yet=True,
        no_performance_or_deployment_claim=True)
    (WORK/'transform_stage2.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(proof,indent=2))

if __name__=='__main__':main()

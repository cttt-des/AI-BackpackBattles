"""Pass private event literals by value span; materialize before opaque use."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/event_factory_bundle'
WORK=STAGE/'native_perf50/literal_spans_prototype'
EXPECTED='d8a7365191ad57a48ac378a7db77e8587169814f6f74298734f7d0b4786e3a76'
ARCHIVE='8c40f0b1b2cbb1ce5227f69757f89eca3bbc644a'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a))
    return t.replace(a,b,1)

HEADER=r'''

namespace gd { bool native_literal_canonical_row(const NativeMethodRow*); }

// This view is used only for fresh, unaliased literals at frozen call sites.
// A callback that may retain or mutate the array receives a real arena array.
struct NativeLiteralEventArguments {
    gd::BattleArena& arena;
    const gd::GdVal* data;
    int count;
    gd::GdVal array;
    gd::GdVal materialize() {
        if(array.is_null()) {
            auto* a=gd::GdArr::create(arena,static_cast<uint32_t>(count));
            for(int i=0;i<count;++i)a->data[a->len++]=data[i];
            array=gd::GdVal::from_arr(a);
        }
        return array;
    }
    gd::GdVal invoke(gd::BattleCtx& ctx,const gd::GdVal& receiver) {
        if(array.is_null() && ctx.native_resolved_dispatch &&
           receiver.kind==gd::GdVal::Kind::FuncRef && receiver.fr &&
           receiver.fr->instance && receiver.fr->method!=gd::SYM_NONE &&
           (!receiver.fr->binds || !receiver.fr->binds->len) &&
           gd::native_literal_canonical_row(receiver.fr->instance->native_call_row_)) {
            // The canonical method wrappers copy every argument cell before any
            // callback. The header is never passed to a method or opaque code.
            gd::GdArr borrowed;
            borrowed.data=const_cast<gd::GdVal*>(data);
            borrowed.len=borrowed.cap=static_cast<uint32_t>(count);
            gd::GdVal out;
            if(gd::native_try_flat_funcref(ctx,receiver,gd::GdVal::from_arr(&borrowed),out))return out;
            // A failed audit may have observable effects. Do not audit twice.
            return receiver.fr->call_funcv(ctx,materialize());
        }
        const gd::GdVal args[]={materialize()};
        return native_event_funcv(ctx,receiver,args,1);
    }
};

gd::GdVal gd_native_emit_literal_body(Gd__gd_core__CoreEventBus*,const gd::GdVal*,NativeLiteralEventArguments&);

inline gd::GdVal gd_native_emit_literal_event(gd::BattleCtx& caller,const gd::GdVal& receiver,
        const gd::GdVal* prefix,const gd::GdVal* payload,int count) {
    NativeLiteralEventArguments arguments{caller.arena,payload,count,gd::GdVal::null()};
    if(receiver.kind==gd::GdVal::Kind::Obj && receiver.obj &&
       native_event_type_ok<Gd__gd_core__CoreEventBus>(caller,receiver)) {
        auto* bus=static_cast<Gd__gd_core__CoreEventBus*>(receiver.obj);
        if(bus->rt_ctx_->native_event_kernel)return gd_native_emit_literal_body(bus,prefix,arguments);
        const gd::GdVal args[]={prefix[0],prefix[1],prefix[2],arguments.materialize()};
        return bus->fn_emitEvent(args,4);
    }
    const gd::GdVal args[]={prefix[0],prefix[1],prefix[2],arguments.materialize()};
    return gd::call_method(caller,receiver,SYM_GEN_emitEvent_1593,args,4);
}
'''

CANONICAL=r'''
bool native_literal_canonical_row(const NativeMethodRow* row) {
    const auto first=reinterpret_cast<uintptr_t>(native_resolved_rows);
    const auto selected=reinterpret_cast<uintptr_t>(row);
    return selected>=first && selected-first<sizeof(native_resolved_rows) &&
           (selected-first)%sizeof(NativeMethodRow)==0;
}

'''

def transform(native):
    review=json.loads((STAGE/'native_perf50/storage_bundle/literal_event_span_review.json').read_bytes())
    for name,digest in review['source_sha256'].items():assert sha(native/name)==digest
    # Complete method-body argument audit, not a speed estimate.
    other=[];signatures=0;copies=0
    for p in sorted((native/'gen/shards').glob('*.cpp')):
        for line in p.read_text('utf8').splitlines():
            if not re.search(r'\b_args\b',line):continue
            if re.match(r'^gd::GdVal \w+::(?:fn|sf)_\w+\(.*const gd::GdVal\* _args, int _argc\) \{$',line):signatures+=1
            elif re.match(r'^\s*gd::GdVal lv_\w+ = \(_argc > \d+\) \? _args\[\d+\] : .*;\s*$',line):copies+=1
            else:other.append(line)
    assert signatures==4992 and copies==3268
    assert other==[s['text'] for s in review['remaining_value_reads']]
    # The seven bridge reads consume scalar cells; none retain the pointer.
    assert len(other)==7 and all('gd_coerce_float' in x or '.as_int()' in x for x in other)
    resolved=native/'native_resolved_dispatch.hpp';text=resolved.read_text('utf8')
    rows=text.split('static const NativeMethodRow native_resolved_rows[] = {',1)[1].split('\n};',1)[0]
    functions=re.findall(r'&([A-Za-z_][A-Za-z_0-9]*)<',rows)
    assert functions and set(functions)=={'native_resolved_invoke'}
    text=once(text,'static const NativeMethodRow native_resolved_empty{};',CANONICAL+'static const NativeMethodRow native_resolved_empty{};')
    resolved.write_text(text,encoding='utf8',newline='\n')
    header=native/'native_event_kernel.hpp'
    with header.open('a',encoding='utf8',newline='\n') as stream:stream.write(HEADER)
    # Duplicate exactly the existing native emission body, with one local
    # representation substitution; the generic and public methods remain intact.
    p=native/'gen/shards/shard_12.cpp';text=p.read_text('utf8')
    marker='gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(const gd::GdVal* _args, int _argc) {'
    start=text.index('    if (gd_ctx.native_event_kernel) {',text.index(marker))
    opening=text.index('{',start);depth=1;end=opening+1
    while depth:
        depth += (text[end]=='{')-(text[end]=='}');end+=1
    body=text[opening+1:end-1]
    for i,name in enumerate(('emitter','signalName','event')):
        body=once(body,f'(_argc > {i}) ? _args[{i}] : gd::GdVal::null()',f'prefix[{i}]')
    body=once(body,'    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();\n','')
    old='(void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return native_event_funcv(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), _ca, 1); })();'
    body=once(body,old,'(void)arguments.invoke(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)));')
    assert '_args' not in body and 'lv_arguments' not in body
    helper='''gd::GdVal gd_native_emit_literal_body(Gd__gd_core__CoreEventBus* bus,const gd::GdVal* prefix,NativeLiteralEventArguments& arguments) {
    gd::BattleCtx& gd_ctx=*bus->rt_ctx_;
    if(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(bus->f_loggingMode,gd::GdVal::from_int(2))))) {
        const gd::GdVal args[]={prefix[0],prefix[1],prefix[2],arguments.materialize()};
        (void)bus->fn_queueSignal(args,4);
        return gd::GdVal::null();
    }
'''+body.replace('this->','bus->')+'\n}\n\n'
    text=once(text,marker,helper+marker);p.write_text(text,encoding='utf8',newline='\n')
    needle='native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitEvent>'
    pattern=r'gd::GdVal _ca\[\] = \{(.*), gd::GdVal::from_arr\(gd::GdArr::from_init\(gd_ctx.arena, \{(.*)\}\)\)\}; return '+re.escape(needle)+r'\(gd_ctx, (.*), SYM_GEN_emitEvent_1593, _ca, 4\);'
    sites=review['eligible_literal_call_sites']
    for path in sorted({s['path'] for s in sites}):
        p=native/path;text=p.read_text('utf8')
        for site in (s for s in sites if s['path']==path):
            old=site['statement'];match=re.search(pattern,old);assert match,old
            prefix,payload,receiver=match.groups()
            new='gd::GdVal _ca[] = {'+prefix+'}; const gd::GdVal _payload[] = {'+payload+'}; return gd_native_emit_literal_event(gd_ctx, '+receiver+', _ca, _payload, static_cast<int>(std::size(_payload)));'
            # Two Buff sites have identical text; replace exactly one at a time.
            assert old in text;text=text.replace(old,old[:match.start()]+new+old[match.end():],1)
        assert needle not in text
        p.write_text(text,encoding='utf8',newline='\n')
    return dict(component='12 private event literals with lazy argument-array materialization',
        eligible_call_sites=len(sites),canonical_argument_signature_count=signatures,
        canonical_value_copy_count=copies,additional_scalar_reads=other,
        original_methods_retained=True,materialization_uses_original_caller_arena=True,
        original_emission_body_cloned_with_single_callback_substitution=True,
        materialized_array_remains_live_for_all_future_listeners=True,
        canonical_row_guard_has_no_virtual_callbacks=True,failed_audits_not_repeated=True,
        old_counters_layouts_rng_float_order_unchanged=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert not WORK.exists();WORK.mkdir()
    src=WORK/'prototype_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n])
    assert changed==['gen/shards/shard_00.cpp','gen/shards/shard_02.cpp','gen/shards/shard_12.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp']
    (WORK/'transform.json').write_text(json.dumps(dict(baseline_dll_sha256=EXPECTED,
        verified_backup=ARCHIVE,source_sha256=after,modified_files=changed,component=component,
        not_for_deployment=True),indent=2)+'\n',encoding='utf8')
    print('Prepared 12 frozen literal event sites; no speed claim')

if __name__=='__main__':main()

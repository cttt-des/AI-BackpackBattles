"""Single frozen candidate in each independent optimization direction."""
DICT_EQUAL='''// Specialize only the exact pure branches of gd_eq; retain the original
// evaluator for every floating, mixed numeric, recursive or unknown key.
static inline bool native_dict_scalar_key_equal(const GdVal& a,const GdVal& b) {
    if(a.kind==b.kind) {
        switch(a.kind) {
            case GdVal::Kind::Int:return a.i==b.i;
            case GdVal::Kind::Obj:return a.obj==b.obj;
            case GdVal::Kind::Str:
                if(a.str==b.str)return true;
                if(!a.str || !b.str)return false;
                return a.str->len==b.str->len && a.str->hash==b.str->hash &&
                    std::memcmp(a.str->data,b.str->data,a.str->len)==0;
            default:break;
        }
    }
    return gd_eq(a,b);
}

'''

def dictionary(source):
    name='gd_rt.cpp';text=(source/name).read_text('utf8')
    start=text.index('int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {');end=text.index('\nGdVal GdDict::get(',start)
    old=text[start:end];assert old.count('gd_eq(entries[')==3
    new=DICT_EQUAL+old.replace('gd_eq(entries[','native_dict_scalar_key_equal(entries[')
    return {name:[[old,new]]}

def rng_scaling(source):
    name='gd_rt.hpp';text=(source/name).read_text('utf8')
    old='''        return static_cast<double>(std::ldexp(mantissa, -32 - clz));'''
    new='''        // The original unsigned-to-float conversion above is retained,
        // including its rounding and exception flags. Its result is in
        // [2^31,2^32], and clz is in [0,31]: scaling is exact and normal.
        // Adjust only the exponent field; never change draws or mantissa bits.
        if constexpr (sizeof(float)==sizeof(uint32_t) &&
                std::numeric_limits<float>::is_iec559 &&
                std::numeric_limits<float>::digits==24 &&
                std::numeric_limits<float>::max_exponent==128) {
            uint32_t bits;
            std::memcpy(&bits,&mantissa,sizeof(bits));
            bits-=static_cast<uint32_t>(32+clz)<<23;
            float scaled;
            std::memcpy(&scaled,&bits,sizeof(scaled));
            return static_cast<double>(scaled);
        } else {
            return static_cast<double>(std::ldexp(mantissa, -32 - clz));
        }'''
    assert text.count(old)==1
    return {name:[[old,new]]}

def event_loop(source):
    # Exact bounded integral loop control; dynamic live listener length stays
    # at every iteration, including after append, replacement or nested emit.
    name='gen/shards/shard_12.cpp';text=(source/name).read_text('utf8')
    start=text.index('gd::GdVal gd_native_emit_literal_body(');end=text.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_connectEvent',start)
    old=text[start:end]
    assert old.count('gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);')==3
    assert old.count('lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));')==3
    new=old.replace('gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);','uint64_t native_bus_i = 0;')
    new=new.replace('lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));','++native_bus_i;')
    new=new.replace('lv__bus_i','gd::GdVal::from_int(static_cast<int64_t>(native_bus_i))')
    # uint32_t iterator can never increment more than UINT32_MAX times before
    # termination (max len UINT32_MAX). Thus every original Int add is exact.
    assert new.count('_t1646 < _t1645->len')==3
    assert new.count(' && _t')==old.count(' && _t')
    helper='''// Fresh pure-field proof at each original diagnostic observation point.
// No result survives a callback. A failed proof evaluates the full old path,
// including every audit mismatch and generic/property diagnostic counter.
static inline bool native_bus_trace_proven_off(gd::BattleCtx& ctx,const gd::GdVal& value) {
    if(value.kind!=gd::GdVal::Kind::Obj || !value.obj ||
       &typeid(*value.obj)!=&typeid(Gd__gd_core__CoreContext))return false;
    const auto& rng=static_cast<Gd__gd_core__CoreContext*>(value.obj)->f_rng;
    if(rng.kind!=gd::GdVal::Kind::Obj || !rng.obj ||
       &typeid(*rng.obj)!=&typeid(Gd__gd_core__CoreRng))return false;
    const auto& trace=static_cast<Gd__gd_core__CoreRng*>(rng.obj)->f_oracle_trace;
    return trace.kind==gd::GdVal::Kind::Bool && !trace.b;
}

'''
    lines=[];gates=0
    for line in new.splitlines(keepends=True):
        stripped=line.lstrip()
        if stripped.startswith('if (') and 'native_event_get<' in line and 'SYM_GEN_oracle_trace_1729' in line and 'SYM_GEN__stacktrace_1731' in line:
            assert stripped.endswith(') {\n')
            owner='bus' if 'bus->f__ctx' in line else 'this'
            indent=line[:len(line)-len(stripped)]
            line=indent+'if (!native_bus_trace_proven_off(gd_ctx, '+owner+'->f__ctx) && ('+stripped[4:-4]+')) {\n';gates+=1
        lines.append(line)
    assert gates==6,gates
    new=helper+''.join(lines)
    return {name:[[old,new]]}

def event_trace_fixture(stage):
    text=(stage/'test_native_event_identity_bus.cpp').read_text('utf8')
    text=text.replace('#include <vector>','#include <vector>\n#include <xmmintrin.h>')
    at=text.index('static Result run(')
    extra='''static bool next_literal=false;
struct ForeignContext:Context {
    using Context::Context;
    bool get_prop(gd::SymId property,V& out)const override {
        (void)rt_ctx_->math_rng.randi();return Context::get_prop(property,out);
    }
};
struct ForeignRng:Rng {
    using Rng::Rng;
    bool get_prop(gd::SymId property,V& out)const override {
        (void)rt_ctx_->math_rng.randi();return Rng::get_prop(property,out);
    }
};
'''
    text=text[:at]+extra+text[at:]
    old='Context ctx(&battle);ctx.init_fields(battle);'
    new='auto* plain_context=static_cast<Context*>(META_Gd__gd_core__CoreContext.alloc_fn(battle));ForeignContext foreign_context(&battle);Context& ctx=mode==20?static_cast<Context&>(foreign_context):*plain_context;ctx.init_fields(battle);'
    assert text.count(old)==1;text=text.replace(old,new)
    old='auto* rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);'
    new='auto* normal_rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);ForeignRng foreign_rng(&battle);foreign_rng.init_fields(battle);Rng* rng=mode==21?static_cast<Rng*>(&foreign_rng):normal_rng;'
    assert text.count(old)==1;text=text.replace(old,new)
    anchor='    ctx.f_rng=V::from_obj(rng);'
    add='''
    const V trace_values[]={V::null(),V::from_int(0),V::from_int(1),V::from_float(0.0),V::from_float(-0.0),
        V::from_float(std::bit_cast<double>(UINT64_C(1))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),
        V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234))),V::from_str(nullptr),V::from_str(gd::make_str(battle.arena,"0")),
        V::from_vec2(0.0,1.0),V::from_bool(false)};
    if(trace_mode>=4){rng->f_oracle_trace=trace_values[trace_mode-4];rng->f__stacktrace=V::from_bool(true);}
    auto* alternate_rng=make<Rng>(battle,META_Gd__gd_core__CoreRng);alternate_rng->f_rng=V::from_rng(&battle.math_rng);
    alternate_rng->f_oracle_trace=V::from_bool(true);alternate_rng->f__stacktrace=V::from_bool(true);
    auto& alternate_context=*make<Context>(battle,META_Gd__gd_core__CoreContext);alternate_context.f_rng=V::from_obj(alternate_rng);alternate_context.f_fight_ended=V::from_bool(false);
'''
    assert text.count(anchor)==1;text=text.replace(anchor,anchor+add)
    old='(void)candidate;bus.fn_emitAndLog(args,4);'
    new='(void)candidate;if(next_literal)gd_native_emit_literal_event(battle,V::from_obj(&bus),args,arguments.arr->data,arguments.arr->len);else bus.fn_emitAndLog(args,4);'
    assert text.count(old)==1;text=text.replace(old,new)
    anchor='            case 4:ctx.f_fight_ended=V::from_bool(true);break;'
    assert text.count(anchor)==1;text=text.replace(anchor,anchor+'\n            case 22:ctx.f_rng=V::from_obj(alternate_rng);break;\n            case 23:bus.f__ctx=V::from_obj(&alternate_context);break;')
    text=text.replace('std::vector<uint64_t> trace;std::string diagnostics;', 'std::vector<uint64_t> metrics;std::vector<uint64_t> trace;std::string diagnostics;')
    anchor='    return result;\n}'
    extra='''    for(auto n:battle.native_resolved_counts)result.metrics.push_back(n);
    for(auto n:battle.native_event_counts)result.metrics.push_back(n);
    result.metrics.push_back(battle.native_timer_watch.version);
    result.metrics.push_back(battle.native_timer_watch.depth);
'''
    assert text.count(anchor)==1;text=text.replace(anchor,extra+anchor)
    anchor='    mix(r.trace.size());for(auto v:r.trace)mix(v);'
    assert text.count(anchor)==1;text=text.replace(anchor,anchor+'\n    for(auto v:r.metrics)mix(v);')
    text=text[:text.index('int main(int argc,char**) {')]+'''
int main() {
    register_gen_syms();const int rounds[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
    std::vector<uint64_t> hashes;
    for(int rounding:rounds)for(unsigned daz=0;daz<4;++daz)
    for(unsigned mode=0;mode<24;++mode)for(unsigned trace=0;trace<16;++trace)
    for(bool native:{false,true})for(bool audit:{false,true})for(bool literal:{false,true}) {
        std::fesetround(rounding);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        next_literal=literal;const auto result=run(true,mode,trace,native,audit);
        uint64_t h=result_hash(result);h=(h^_mm_getcsr())*1099511628211ULL;hashes.push_back(h);
    }
    assert(hashes.size()==49152);
    std::cout<<"{\\"passed\\":true,\\"cases\\":"<<hashes.size()<<",\\"hashes\\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"]}\\n";
}
'''
    return text

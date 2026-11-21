#include "native_inline_dispatch.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;
#ifdef GD_NUMERIC_CANDIDATE
extern "C" uint64_t gd_diag_native_numeric_stat(unsigned);
#endif

uint64_t mix(uint64_t h,uint64_t value){return (h^value)*UINT64_C(1099511628211);}
bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    switch(a.kind){
        case V::Kind::Null:return true;
        case V::Kind::Bool:return a.b==b.b;
        case V::Kind::Int:return a.i==b.i;
        case V::Kind::Float:return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
        case V::Kind::Vec2:return std::bit_cast<uint64_t>(a.v2.x)==std::bit_cast<uint64_t>(b.v2.x) && std::bit_cast<uint64_t>(a.v2.y)==std::bit_cast<uint64_t>(b.v2.y);
        case V::Kind::Str:return bool(a.str)==bool(b.str) && (!a.str || (a.str->len==b.str->len && a.str->hash==b.str->hash && std::memcmp(a.str->data,b.str->data,a.str->len)==0));
        case V::Kind::Arr:
            if(bool(a.arr)!=bool(b.arr))return false;
            if(!a.arr)return true;
            if(a.arr->len!=b.arr->len || a.arr->is_pool_real!=b.arr->is_pool_real)return false;
            for(uint32_t i=0;i<a.arr->len;++i)if(!same(a.arr->data[i],b.arr->data[i]))return false;
            return true;
        case V::Kind::Dict:
            if(bool(a.dict)!=bool(b.dict))return false;
            if(!a.dict)return true;
            if(a.dict->len!=b.dict->len)return false;
            for(uint32_t i=0;i<a.dict->len;++i)if(!same(a.dict->entries[i].key,b.dict->entries[i].key) || !same(a.dict->entries[i].val,b.dict->entries[i].val))return false;
            return true;
        case V::Kind::Obj:return a.obj==b.obj;
        case V::Kind::Color:return a.col==b.col;
        case V::Kind::Rng:return a.rng==b.rng;
        case V::Kind::FuncRef:return a.fr==b.fr;
        case V::Kind::ClassRef:return a.cls==b.cls;
        case V::Kind::Enum:return a.en==b.en;
    }
    return false;
}
uint64_t hash(const V& value,uint64_t h=UINT64_C(1469598103934665603)){
    h=mix(h,unsigned(value.kind));
    switch(value.kind){
        case V::Kind::Null:return h;
        case V::Kind::Bool:return mix(h,value.b);
        case V::Kind::Int:return mix(h,uint64_t(value.i));
        case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(value.f));
        case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(value.v2.x)),std::bit_cast<uint64_t>(value.v2.y));
        case V::Kind::Str:
            h=mix(h,bool(value.str));if(value.str){h=mix(h,value.str->len);for(uint32_t i=0;i<value.str->len;++i)h=mix(h,uint8_t(value.str->data[i]));}return h;
        case V::Kind::Obj:return mix(h,bool(value.obj));
        case V::Kind::Arr:
            h=mix(h,bool(value.arr));if(value.arr){h=mix(h,value.arr->len);for(uint32_t i=0;i<value.arr->len;++i)h=hash(value.arr->data[i],h);}return h;
        case V::Kind::Dict:
            h=mix(h,bool(value.dict));if(value.dict){h=mix(h,value.dict->len);for(uint32_t i=0;i<value.dict->len;++i){h=hash(value.dict->entries[i].key,h);h=hash(value.dict->entries[i].val,h);}}return h;
        case V::Kind::Color:
            h=mix(h,bool(value.col));if(value.col){for(double x:{value.col->r,value.col->g,value.col->b,value.col->a})h=mix(h,std::bit_cast<uint64_t>(x));}return h;
        case V::Kind::Rng:
            h=mix(h,bool(value.rng));return value.rng?mix(mix(h,value.rng->pcg.state),value.rng->pcg.inc):h;
        case V::Kind::FuncRef:
            h=mix(h,bool(value.fr));if(value.fr){h=mix(h,value.fr->method);h=mix(h,bool(value.fr->instance));}return h;
        case V::Kind::ClassRef:return mix(h,bool(value.cls));
        case V::Kind::Enum:return mix(h,bool(value.en));
    }
    assert(false);return 0;
}

struct Payload:gd::GdObj {
    mutable unsigned metadata_reads=0;
    explicit Payload(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta() const override{++metadata_reads;return nullptr;}
};

V original(unsigned op,gd::BattleCtx& ctx,const V& a,const V& b){
    switch(op){case 0:return gd::gd_add(ctx,a,b);case 1:return gd::gd_sub(a,b);case 2:return gd::gd_mul(a,b);default:return gd::gd_div(ctx,a,b);}
}
V candidate(unsigned op,gd::BattleCtx& ctx,const V& a,const V& b){
#ifdef GD_NUMERIC_CANDIDATE
    switch(op){case 0:return gd::native_numeric_add(ctx,a,b);case 1:return gd::native_numeric_sub(a,b);case 2:return gd::native_numeric_mul(a,b);default:return gd::native_numeric_div(ctx,a,b);}
#else
    return original(op,ctx,a,b);
#endif
}

struct Side {
    gd::BattleCtx& ctx;
    V a=V::from_float(3.25),b=V::from_float(-2.0);
    std::vector<unsigned> trace;
    bool alias=false,integers=false;
};
const V& side(Side& state,unsigned which){
    state.trace.push_back(which);
    const double draw=state.ctx.math_rng.randf();
    if(which==0){
        state.a=state.integers?V::from_int(int64_t(draw*73)+1):V::from_float(draw+state.b.as_float());
        return state.a;
    }
    state.a=state.integers?V::from_int(int64_t(draw*31)+2):V::from_float(draw*7.0);
    state.b=state.integers?V::from_int(int64_t(draw*19)+1):V::from_float(draw-2.0);
    return state.alias?state.a:state.b;
}

// Preserve direct call-site shapes: both-operand callbacks and references to
// fields changed by the other operand must retain the original evaluation order.
V original_sides(unsigned op,Side& s,bool nested){
    const auto two=V::from_float(2.0);
    if(nested)return gd::gd_add(s.ctx,gd::gd_mul(side(s,0),two),side(s,1));
    switch(op){
        case 0:return gd::gd_add(s.ctx,side(s,0),side(s,1));
        case 1:return gd::gd_sub(side(s,0),side(s,1));
        case 2:return gd::gd_mul(side(s,0),side(s,1));
        default:return gd::gd_div(s.ctx,side(s,0),side(s,1));
    }
}
V candidate_sides(unsigned op,Side& s,bool nested){
#ifdef GD_NUMERIC_CANDIDATE
    const auto two=V::from_float(2.0);
    if(nested)return gd::native_numeric_add(s.ctx,gd::native_numeric_mul(side(s,0),two),side(s,1));
    switch(op){
        case 0:return gd::native_numeric_add(s.ctx,side(s,0),side(s,1));
        case 1:return gd::native_numeric_sub(side(s,0),side(s,1));
        case 2:return gd::native_numeric_mul(side(s,0),side(s,1));
        default:return gd::native_numeric_div(s.ctx,side(s,0),side(s,1));
    }
#else
    return original_sides(op,s,nested);
#endif
}

int main(){
    register_gen_syms();gd::BattleCtx reference,fast;
    reference.bind_battle(41);fast.bind_battle(41);fast.native_resolved_collect=true;fast.native_resolved_dispatch=true;
    Payload payload(&reference);gd::GdRng value_rng(73);gd::GdFuncRef function{&payload,gd::SYM_size,nullptr};
    const gd::GdClassMeta meta{};const gd::GdEnum::KV keys[]={{"entry",1}};const gd::GdEnum enumeration{"test",keys,1};
    gd::GdColor color{0.5,-0.0,1.0,0.25};
    auto* dictionary=gd::GdDict::create(reference.arena);dictionary->set(reference.arena,V::from_int(7),V::from_str(gd::make_static_str("dict")));
    auto* array=gd::GdArr::from_init(reference.arena,{V::from_int(7),V::from_obj(&payload),V::from_vec2(1.0,-0.0)});
    auto* other=gd::GdArr::from_init(reference.arena,{V::from_color(&color),V::from_rng(&value_rng),V::from_funcref(&function),V::from_cls(&meta),V::from_enum(&enumeration),V::from_dict(dictionary)});
    const auto qnan_a=std::bit_cast<double>(UINT64_C(0x7ff80000000000a5));
    const auto qnan_b=std::bit_cast<double>(UINT64_C(0xfff8000000001234));
    const auto snan=std::bit_cast<double>(UINT64_C(0x7ff00000000000b6));
    const std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),
        V::from_int(0),V::from_int(1),V::from_int(-1),V::from_int(3),V::from_int((INT64_C(1)<<53)+1),
        V::from_int(std::numeric_limits<int64_t>::min()),V::from_int(std::numeric_limits<int64_t>::max()),
        V::from_float(0.0),V::from_float(-0.0),V::from_float(1.25),V::from_float(-2.5),
        V::from_float(1e308),V::from_float(-1e308),V::from_float(std::numeric_limits<double>::denorm_min()),
        V::from_float(-std::numeric_limits<double>::denorm_min()),
        V::from_float(std::numeric_limits<double>::infinity()),V::from_float(-std::numeric_limits<double>::infinity()),
        V::from_float(qnan_a),V::from_float(qnan_b),V::from_float(snan),
        V::from_vec2(1.25,-0.0),V::from_vec2(qnan_a,0.0),V::from_vec2(-2.0,3.0),
        V::from_str(gd::make_static_str("value")),V::from_str(nullptr),V::from_arr(array),V::from_arr(other),V::from_arr(nullptr),
        V::from_dict(dictionary),V::from_obj(&payload),V::from_cls(&meta),V::from_enum(&enumeration),V::from_funcref(&function),V::from_rng(&value_rng),V::from_color(&color)};
    std::vector<uint64_t> hashes;unsigned skipped=0,directed=0;
    for(unsigned op=0;op<4;++op)for(unsigned ai=0;ai<values.size();++ai)for(unsigned bi=0;bi<values.size();++bi){
        const auto& a=values[ai];const auto& b=values[bi];
        if(op==3 && a.kind==V::Kind::Int && b.kind==V::Kind::Int && a.i==std::numeric_limits<int64_t>::min() && b.i==-1){++skipped;continue;}
        const auto expected=original(op,reference,a,b);const auto result=candidate(op,fast,a,b);
        if(!same(expected,result)){
            std::cerr<<"Mismatch op="<<op<<" a="<<ai<<" b="<<bi<<" expected="<<std::hex<<hash(expected)<<" got="<<hash(result)<<"\n";return 2;
        }
        hashes.push_back(mix(mix(mix(hash(result),op),ai),bi));
    }
    assert(payload.metadata_reads==0);
    for(unsigned seed=0;seed<4;++seed)for(unsigned op=0;op<4;++op)for(bool alias:{false,true})for(bool integers:{false,true})for(bool nested:{false,true}){
        gd::BattleCtx a,b;a.bind_battle(seed+91);b.bind_battle(seed+91);b.native_resolved_collect=true;b.native_resolved_dispatch=true;
        Side old_side{a},new_side{b};old_side.alias=new_side.alias=alias;old_side.integers=new_side.integers=integers;
        const auto before=original_sides(op,old_side,nested);const auto after=candidate_sides(op,new_side,nested);
        assert(same(before,after) && old_side.trace==new_side.trace);
        assert(same(old_side.a,new_side.a) && same(old_side.b,new_side.b));
        assert(a.math_rng.pcg.state==b.math_rng.pcg.state && a.math_rng.pcg.inc==b.math_rng.pcg.inc);
        auto h=mix(mix(hash(after),b.math_rng.pcg.state),b.math_rng.pcg.inc);
        for(auto step:new_side.trace)h=mix(h,step);
        hashes.push_back(h);++directed;
    }
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"directed_cases\":"<<directed<<",\"skipped_undefined_divisions\":"<<skipped<<",\"case_hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"]";
#ifdef GD_NUMERIC_CANDIDATE
    std::cout<<",\"numeric_counts\":[";for(unsigned i=0;i<6;++i){if(i)std::cout<<',';std::cout<<gd_diag_native_numeric_stat(i);}std::cout<<']';
#endif
    std::cout<<"}\n";
}

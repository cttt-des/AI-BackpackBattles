#include "native_inline_dispatch.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
static unsigned static_calls=0;
static bool handled=true;
static bool static_callback(gd::BattleCtx&,gd::SymId,const V*,int,V& out){++static_calls;out=V::from_int(733);return handled;}
struct Foreign:gd::GdObj {
    mutable unsigned metadata_calls=0;
    unsigned calls=0;
    explicit Foreign(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{++metadata_calls;return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId,const V*,int,V& out)override{++calls;out=V::from_int(911);return handled;}
};
struct Result {std::vector<uint64_t> words;bool operator==(const Result&)const=default;};

__attribute__((noinline,noclone)) static Result one(bool candidate,unsigned receiver,gd::SymId method,unsigned shape,bool enabled,int rounding,unsigned denorm){
    gd::BattleCtx ctx(4096);Foreign foreign(&ctx);static_calls=0;handled=(shape&1)!=0;
    auto* other=gd::GdArr::from_init(ctx.arena,{V::from_int(22),V::from_float(3.5)});
    auto* a=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_float(-0.0),V::from_arr(other),V::from_cstr(ctx.arena,"b"),V::from_bool(false)});
    auto* empty=gd::GdArr::create(ctx.arena);
    auto* d=gd::GdDict::create(ctx.arena);auto* empty_d=gd::GdDict::create(ctx.arena);
    d->set(ctx.arena,V::from_int(1),V::from_int(9));
    d->set(ctx.arena,shape%3?V::from_cstr(ctx.arena,"b"):V::from_int(2),V::from_float(-0.0));
    d->set(ctx.arena,V::from_int(3),V::from_arr(other));
    if(shape%3==0)d->enable_integer_grid(ctx.arena);
    const gd::GdEnum::KV entries[]={{"first",1},{"b",-7},{"\xc3\xa9",INT64_MAX}};
    const gd::GdEnum enumeration={"Probe",entries,3},empty_enum={"Empty",nullptr,0};
    gd::GdClassMeta cls={gd::CLS_NONE,"ForeignStatic","",nullptr,false,nullptr,nullptr,static_callback};
    V null_enum;null_enum.kind=V::Kind::Enum;null_enum.en=nullptr;
    const V receivers[]={V::from_arr(a),V::from_arr(empty),V::from_arr(nullptr),V::from_dict(d),V::from_dict(empty_d),
        V::from_dict(nullptr),V::from_enum(&enumeration),V::from_enum(&empty_enum),null_enum,V::from_obj(&foreign),
        V::from_cls(&cls),V::from_cstr(ctx.arena,"receiver"),V::null(),V::from_float(-0.0)};
    const double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000001));
    gd::GdColor color={snan,0,0,0};
    V args[]={V::null(),V::from_float(-0.0)};const V* input=args;int argc=1;
    switch(shape){
        case 0:argc=0;input=nullptr;break;
        case 1:argc=-1;input=nullptr;break;
        case 2:break;
        case 3:args[0]=V::from_int(0);break;
        case 4:args[0]=V::from_int(-1);break;
        case 5:args[0]=V::from_int(2);break;
        case 6:args[0]=V::from_int(12);break;
        case 7:args[0]=V::from_float(2.75);break;
        case 8:args[0]=V::from_float(snan);break;
        case 9:args[0]=V::from_bool(false);break;
        case 10:args[0]=V::from_bool(true);break;
        case 11:args[0]=V::from_cstr(ctx.arena,"b");argc=2;break;
        case 12:args[0]=V::from_arr(other);break;
        case 13:args[0]=V::from_arr(nullptr);break;
        case 14:args[0]=V::from_arr(a);break;
        case 15:input=a->data;break;
        case 16:args[0]=V::from_dict(d);break;
        case 17:args[0]=V::from_color(&color);break;
        case 18:args[0]=V::from_float(-0.0);break;
        case 19:args[0]=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000000012)));break;
        case 20:args[0]=V::from_str(nullptr);break;
        case 21:args[0]=V::from_obj(&foreign);break;
    }
    a->is_pool_real=(shape&1)!=0;
    auto& watch=ctx.native_timer_watch;watch.version=shape==14?UINT64_MAX:7;
    watch.depth=shape==15?UINT32_MAX:0;watch.usable=true;watch.enabled=(shape&1)!=0;watch.collect=true;watch.closed_world=(shape&2)!=0;
    a->timer_watch=shape%5?&watch:nullptr;empty->timer_watch=shape%5?&watch:nullptr;
    auto* old_data=a->data;auto* old_empty_data=empty->data;
    ctx.native_resolved_dispatch=enabled;ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
    uint64_t before[6];for(unsigned i=0;i<6;++i)before[i]=ctx.native_resolved_counts[i];
    std::fesetround(rounding);std::feclearexcept(FE_ALL_EXCEPT);
    const unsigned mode=(_mm_getcsr()&~(0x8040u|0x3fu))|denorm|4u;_mm_setcsr(mode);
    const V out=candidate?gd::native_inline_call(ctx,receivers[receiver],method,input,argc):gd::call_method(ctx,receivers[receiver],method,input,argc);
    const int flags=std::fetestexcept(FE_ALL_EXCEPT);const unsigned csr=_mm_getcsr();
    Result result;auto& w=result.words;w.reserve(192);auto add=[&](uint64_t v){w.push_back(v);};
    add(unsigned(flags));add(csr);add(watch.version);add(watch.depth);add(watch.enabled);add(watch.usable);add(watch.closed_world);add(watch.cooldown_version);
    add(foreign.calls);add(foreign.metadata_calls);add(static_calls);add(ctx.native_resolved_dispatch);
    for(unsigned i=0;i<6;++i)add(ctx.native_resolved_counts[i]-before[i]);
    auto value=[&](auto&& self,const V& v,unsigned depth)->void{
        add(unsigned(v.kind));
        switch(v.kind){
            case V::Kind::Null:break;
            case V::Kind::Bool:add(v.b);break;
            case V::Kind::Int:add(uint64_t(v.i));break;
            case V::Kind::Float:add(std::bit_cast<uint64_t>(v.f));break;
            case V::Kind::Vec2:add(std::bit_cast<uint64_t>(v.v2.x));add(std::bit_cast<uint64_t>(v.v2.y));break;
            case V::Kind::Color:add(v.col!=nullptr);if(v.col){add(std::bit_cast<uint64_t>(v.col->r));add(std::bit_cast<uint64_t>(v.col->g));add(std::bit_cast<uint64_t>(v.col->b));add(std::bit_cast<uint64_t>(v.col->a));}break;
            case V::Kind::Str:add(v.str!=nullptr);if(v.str){add(v.str->len);add(v.str->hash);for(unsigned i=0;i<v.str->len;++i)add(uint8_t(v.str->data[i]));}break;
            case V::Kind::Obj:add(v.obj==&foreign);add(v.obj!=nullptr);break;
            case V::Kind::ClassRef:add(v.cls==&cls);add(v.cls!=nullptr);break;
            case V::Kind::Enum:add(v.en==&enumeration?1:v.en==&empty_enum?2:0);break;
            case V::Kind::Arr:
                if(!v.arr){add(0);break;}
                if(v.arr==a){add(1);break;}if(v.arr==other){add(2);break;}if(v.arr==empty){add(3);break;}
                add(4);add(v.arr->len);add(v.arr->cap);add(v.arr->is_pool_real);add(v.arr->timer_watch==&watch);
                add(v.arr->data==a->data);add(v.arr->data==other->data);
                if(depth<4)for(unsigned i=0;i<v.arr->len;++i)self(self,v.arr->data[i],depth+1);break;
            case V::Kind::Dict:
                if(!v.dict){add(0);break;}if(v.dict==d){add(1);break;}if(v.dict==empty_d){add(2);break;}
                add(3);add(v.dict->len);add(v.dict->cap);add(v.dict->bucket_cap);
                if(depth<4)for(unsigned i=0;i<v.dict->len;++i){self(self,v.dict->entries[i].key,depth+1);self(self,v.dict->entries[i].val,depth+1);}break;
            default:add(0);break;
        }
    };
    for(auto* arr:{a,other,empty}){add(arr->len);add(arr->cap);add(arr->is_pool_real);add(arr->timer_watch==&watch);for(unsigned i=0;i<arr->len;++i)value(value,arr->data[i],0);}
    add(a->data==old_data);add(empty->data==old_empty_data);
    for(auto* dict:{d,empty_d}){add(dict->len);add(dict->cap);add(dict->bucket_cap);for(unsigned i=0;i<dict->len;++i){value(value,dict->entries[i].key,0);value(value,dict->entries[i].val,0);add(dict->entries[i].hash);}}
    value(value,out,0);return result;
}
int main(){
    static_assert(sizeof(V)==24 && sizeof(gd::GdArr)==32 && sizeof(gd::GdDict)==32 && sizeof(gd::BattleCtx)==328);
    register_gen_syms();fenv_t saved;std::fegetenv(&saved);const unsigned old_csr=_mm_getcsr();
    const gd::SymId methods[]={gd::SYM_push_back,gd::SYM_append,gd::SYM_append_array,gd::SYM_clear,gd::SYM_resize,gd::SYM_fill,gd::SYM_duplicate,
        gd::SYM_keys,gd::SYM_values,gd::SYM_size,gd::SYM_empty,gd::SYM_has,gd::SYM_pop_back};
    std::vector<uint64_t> hashes;hashes.reserve(128128);
    for(unsigned receiver=0;receiver<14;++receiver)for(auto method:methods)for(unsigned shape=0;shape<22;++shape)for(bool enabled:{false,true})
        for(int rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned denorm:{0u,0x40u,0x8000u,0x8040u}){
            const auto a=one(false,receiver,method,shape,enabled,rounding,denorm),b=one(true,receiver,method,shape,enabled,rounding,denorm);
            if(!(a==b)){std::cerr<<"builtin mismatch receiver="<<receiver<<" method="<<method<<" shape="<<shape<<" enabled="<<enabled<<" rounding="<<rounding<<" denorm="<<denorm<<" sizes="<<a.words.size()<<','<<b.words.size()<<'\n';return 2;}
            uint64_t h=1469598103934665603ULL;for(auto v:a.words)h=(h^v)*1099511628211ULL;hashes.push_back(h);
        }
    std::fesetenv(&saved);_mm_setcsr(old_csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"exact_state_vectors_compared\":true,\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"all16_fp_modes\":true}";
}

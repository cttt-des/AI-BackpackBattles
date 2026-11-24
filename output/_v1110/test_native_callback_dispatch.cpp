#include "native_event_kernel.hpp"
#include "callback_test_symbols.hpp"
#include "gen/hdrs/Gd__gd_core_items__Darksaber.hpp"
#include "gen/hdrs/Gd__gd_core_items__DjinnLamp.hpp"
#include "gen/hdrs/Gd__gd_core_items__AcornCollar.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t hash(const V& v,unsigned depth=0){
    auto h=mix(1469598103934665603ULL,unsigned(v.kind));
    switch(v.kind){
    case V::Kind::Bool:return mix(h,v.b);
    case V::Kind::Int:return mix(h,uint64_t(v.i));
    case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
    case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
    case V::Kind::Str:if(v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,uint8_t(v.str->data[i]));}return h;
    case V::Kind::Arr:if(v.arr && depth<3){h=mix(h,v.arr->len);h=mix(h,v.arr->cap);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i],depth+1));}return h;
    default:return h;
    }
}
static std::array<V,16> inputs(gd::BattleCtx& c){return {V::null(),V::from_bool(false),V::from_bool(true),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(7),
    V::from_float(0.0),V::from_float(-0.0),V::from_float(0.3),V::from_float(std::bit_cast<double>(UINT64_C(1))),
    V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),
    V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000000000))),V::from_str(gd::make_str(c.arena,"2.5")),
    V::from_vec2(-0.0,1.25),V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(9)}))};}
static const gd::GdClassMeta custom_meta{65101,"ExtraCallbackOverride"};
struct Unknown:Item {
    mutable uint64_t metadata_reads=0;
    uint64_t calls=0,trace=1469598103934665603ULL;
    std::function<void(const V*,int)> action;
    const V* saved=nullptr;int saved_count=0;
    explicit Unknown(gd::BattleCtx* c):Item(c){}
    const gd::GdClassMeta* meta()const override{++metadata_reads;return &custom_meta;}
    bool call_method(gd::BattleCtx& c,gd::SymId method,const V* args,int count,V& out)override{
        ++calls;trace=mix(mix(trace,method),uint64_t(count));
        for(int i=0;i<count;++i)trace=mix(trace,hash(args[i]));
        saved=args;saved_count=count;
        (void)c.math_rng.randi();if(action)action(args,count);
        out=V::from_int(int64_t(trace));return true;
    }
};
struct Sink:gd::GdObj {
    uint64_t calls=0;std::function<void()> action;
    explicit Sink(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &custom_meta;}
    bool call_method(gd::BattleCtx& c,gd::SymId,const V*,int,V& out)override{
        ++calls;(void)c.math_rng.randi();if(action)action();out=V::null();return true;
    }
};
static uint64_t state(gd::BattleCtx& c,uint64_t h){
    h=mix(h,c.math_rng.pcg.state);h=mix(h,c.math_rng.pcg.inc);h=mix(h,c.next_gid);
    for(auto n:c.native_resolved_counts)h=mix(h,n);
    for(auto n:c.native_event_counts)h=mix(h,n);
    const auto& w=c.native_timer_watch;
    h=mix(h,w.version);h=mix(h,w.cooldown_version);h=mix(h,w.depth);h=mix(h,w.usable);h=mix(h,w.closed_world);
    h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));return mix(h,_mm_getcsr());
}
static void floating(unsigned rounding,unsigned daz){
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(rounds[rounding]);
    _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
}
static const gd::NativeMethodRow* empty_row(gd::BattleCtx& c){
    Unknown p(&c);V out;(void)gd::try_native_resolved_dispatch(c,&p,SYM_GEN_getP_188,nullptr,0,out,1);
    return p.native_call_row_;
}
static const gd::NativeMethodRow* choose_row(unsigned mode,const gd::NativeMethodRow* valid,
        const gd::NativeMethodRow* wrong,const gd::NativeMethodRow* empty,gd::NativeMethodRow& copy){
    switch(mode){case 0:return valid;case 1:return nullptr;case 2:copy=*valid;return &copy;case 3:return wrong;case 4:copy={};return &copy;default:return empty;}
}
static uint64_t unknown_case(unsigned method_index,unsigned flags,unsigned row_mode,unsigned mode){
    gd::BattleCtx c(8192);c.bind_battle(39);c.native_resolved_dispatch=true;
    auto* donor=META_Gd__gd_core_items__DjinnLamp.alloc_fn(c);
    auto* other=META_Gd__gd_core_items__Darksaber.alloc_fn(c);
    const auto* empty=empty_row(c);Unknown object(&c);object.init_fields(c);
    gd::NativeMethodRow copied{};object.native_call_row_=choose_row(row_mode,donor->native_call_row_,other->native_call_row_,empty,copied);
    c.native_resolved_dispatch=(flags&1)!=0;c.native_resolved_audit=(flags&2)!=0;c.native_resolved_collect=true;
    c.native_timer_watch.enabled=true;c.native_timer_watch.collect=true;c.native_timer_watch.closed_world=(flags&4)!=0;
    gd::GdFuncRef reference;reference.instance=&object;reference.method=callback_test_symbols[method_index];
    const auto values=inputs(c);const V data[]={values[(method_index+mode)%values.size()],V::from_int(42),V::from_bool(true),V::from_float(-0.0)};
    const int argc=int((method_index+mode)%5);
    auto* a=gd::GdArr::create(c.arena,unsigned(argc));for(int i=0;i<argc;++i)a->data[a->len++]=data[i];
    if(mode==2)reference.binds=gd::GdArr::from_init(c.arena,{V::from_int(91)});
    if(mode==3)reference.binds=gd::GdArr::create(c.arena);
#ifdef CALLBACK_DISPATCH_CANDIDATE
    NativeLiteralEventArguments view{c.arena,data,argc,V::null()};
#endif
    bool inside=false;
    object.action=[&](const V* args,int count){
        if(count)const_cast<V*>(args)[0]=V::from_int(17);
        if(mode==1 && !inside){inside=true;(void)reference.call_func(c,args,count);inside=false;}
        if(mode==3)c.native_timer_watch.change();
    };
    floating((method_index+mode)%4,(method_index/4+mode)%4);
    uint64_t h=1469598103934665603ULL;
    const auto api=[&]{
        if(mode==0)return reference.call_func(c,a->data,int(a->len));
#ifdef CALLBACK_DISPATCH_CANDIDATE
        if(mode==3){const auto result=view.invoke(c,V::from_funcref(&reference));assert(!view.array.is_null());a=view.array.arr;return result;}
#endif
        const auto value=V::from_arr(a);
        if(mode==3 || mode==4){const V args[]={value};return native_event_funcv(c,V::from_funcref(&reference),args,1);}
        return reference.call_funcv(c,value);
    };
    h=mix(h,hash(api()));
    if(!reference.binds || !reference.binds->len){if(object.saved_count)h=mix(h,hash(object.saved[0]));}
    for(unsigned i=0;i<13;++i)a->push_back(c.arena,V::from_int(i));
    h=mix(h,hash(api()));h=mix(h,hash(V::from_arr(a)));
    h=mix(h,object.calls);h=mix(h,object.trace);h=mix(h,object.metadata_reads);
    return state(c,h);
}
static uint64_t fast_assertions=0;
#ifdef CALLBACK_DISPATCH_CANDIDATE
extern "C" uint64_t gd_diag_native_extra_callback_stat(unsigned);
#endif
static uint64_t known_case(unsigned type,unsigned value_index,unsigned flags,unsigned row_mode,unsigned bound,unsigned round,unsigned daz){
    gd::BattleCtx c(8192);c.bind_battle(40);c.native_resolved_dispatch=true;
    const gd::GdClassMeta* metas[]={&META_Gd__gd_core_items__Darksaber,&META_Gd__gd_core_items__DjinnLamp,&META_Gd__gd_core_items__AcornCollar};
    const gd::SymId methods[]={callback_darksaber_symbol,callback_djinn_symbol,callback_acorn_symbol};
    auto* raw=metas[type]->alloc_fn(c);raw->init_fields(c);auto* item=static_cast<Item*>(raw);
    auto* donor=META_Gd__gd_core__CoreRng.alloc_fn(c);
    const auto* empty=empty_row(c);const auto* good=raw->native_call_row_;gd::NativeMethodRow copied{};
    raw->native_call_row_=choose_row(row_mode,good,donor->native_call_row_,empty,copied);
    Gd__gd_core__CoreContext context(&c);context.init_fields(c);Sink sink(&c);
    context.f_combat_log=V::from_obj(&sink);item->f_ctx=V::from_obj(&context);
    if(type==0)static_cast<Gd__gd_core_items__Darksaber*>(raw)->f_damPerDebuff=V::from_float(0.3);
    if(type==1)static_cast<Gd__gd_core_items__DjinnLamp*>(raw)->f_activated=V::from_bool(true);
    c.native_resolved_dispatch=(flags&1)!=0;c.native_resolved_audit=(flags&2)!=0;
    c.native_event_kernel=(flags&4)!=0;c.native_event_audit=true;c.native_resolved_collect=true;
    c.native_timer_watch.enabled=true;c.native_timer_watch.collect=true;c.native_timer_watch.closed_world=(round&1)!=0;
    if(value_index&1)c.native_timer_watch.trusted_hooks=&sink;
    const auto values=inputs(c);const V payload[]={values[value_index],V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(5)}))};
    gd::GdFuncRef reference;reference.instance=raw;reference.method=methods[type];
    if(bound==1)reference.binds=gd::GdArr::create(c.arena);
    if(bound==2)reference.binds=gd::GdArr::from_init(c.arena,{V::from_int(91)});
    bool inside=false;
    sink.action=[&]{if(value_index%4==0 && !inside){inside=true;const V nested[]={V::from_float(0.125),V::null()};(void)reference.call_func(c,nested,2);inside=false;}};
    floating(round,daz);uint64_t h=1469598103934665603ULL;
    if(value_index&1){
        const auto array=V::from_arr(gd::GdArr::from_init(c.arena,{payload[0],payload[1]}));
        h=mix(h,hash(reference.call_funcv(c,array)));
    }else{
#ifdef CALLBACK_DISPATCH_CANDIDATE
        NativeLiteralEventArguments view{c.arena,payload,2,V::null()};
        const auto before=gd_diag_native_extra_callback_stat(1);
        h=mix(h,hash(view.invoke(c,V::from_funcref(&reference))));
        if((flags&1) && row_mode==0 && bound!=2){assert(view.array.is_null());assert(gd_diag_native_extra_callback_stat(1)>before);++fast_assertions;}
#else
        const V args[]={V::from_arr(gd::GdArr::from_init(c.arena,{payload[0],payload[1]}))};
        h=mix(h,hash(native_event_funcv(c,V::from_funcref(&reference),args,1)));
#endif
    }
    h=mix(h,hash(item->f_bonusMinDam));h=mix(h,hash(item->f_bonusMaxDam));h=mix(h,hash(item->f_removableDam));
    if(type==1)h=mix(h,hash(static_cast<Gd__gd_core_items__DjinnLamp*>(raw)->f_activated));
    h=mix(h,sink.calls);h=mix(h,hash(payload[1]));return state(c,h);
}
int main(){
    register_gen_syms();const auto csr=_mm_getcsr();const auto old_round=std::fegetround();std::vector<uint64_t> hashes;
    for(unsigned method=0;method<callback_test_symbols.size();++method)for(unsigned flags=0;flags<8;++flags)
    for(unsigned row=0;row<6;++row)for(unsigned mode=0;mode<5;++mode)hashes.push_back(unknown_case(method,flags,row,mode));
    const auto unknown_cases=hashes.size();
    for(unsigned type=0;type<3;++type)for(unsigned value=0;value<16;++value)for(unsigned flags=0;flags<8;++flags)
    for(unsigned row=0;row<6;++row)for(unsigned bound=0;bound<3;++bound)for(unsigned round=0;round<4;++round)
    for(unsigned daz=0;daz<4;++daz)hashes.push_back(known_case(type,value,flags,row,bound,round,daz));
    std::fesetround(old_round);_mm_setcsr(csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"unknown_cases\":"<<unknown_cases<<",\"fast_assertions\":"<<fast_assertions<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";
}

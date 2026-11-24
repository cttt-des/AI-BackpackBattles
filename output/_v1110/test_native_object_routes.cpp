#include "native_inline_dispatch.hpp"
#include "object_route_test_symbols.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core_items__ManaPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__DemonicFlask.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <functional>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Context=Gd__gd_core__CoreContext;
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
static void floating(unsigned rounding,unsigned daz){
    const int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(rounds[rounding]);
    _mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
}
static uint64_t state(gd::BattleCtx& c,uint64_t h){
    h=mix(h,c.math_rng.pcg.state);h=mix(h,c.math_rng.pcg.inc);h=mix(h,c.next_gid);
    for(auto n:c.native_resolved_counts)h=mix(h,n);
    for(auto n:c.native_event_counts)h=mix(h,n);
    const auto& w=c.native_timer_watch;
    h=mix(h,w.version);h=mix(h,w.cooldown_version);h=mix(h,w.depth);h=mix(h,w.usable);h=mix(h,w.closed_world);
    h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));return mix(h,_mm_getcsr());
}
static const gd::GdClassMeta custom_meta{65102,"ObjectRouteOverride"};
template<class Base> struct Override:Base {
    mutable uint64_t metadata_reads=0;
    uint64_t calls=0,trace=1469598103934665603ULL;bool shared=false,inside=false;
    const V* saved=nullptr;int saved_count=0;unsigned mode=0;
    explicit Override(gd::BattleCtx* c):Base(c){}
    const gd::GdClassMeta* meta()const override{++metadata_reads;return shared?Base::meta():&custom_meta;}
    bool call_method(gd::BattleCtx& c,gd::SymId m,const V* a,int n,V& out)override{
        ++calls;trace=mix(mix(trace,m),uint64_t(n));trace=mix(trace,&c!=this->rt_ctx_);
        for(int i=0;i<n;++i)trace=mix(trace,hash(a[i]));
        saved=a;saved_count=n;(void)c.math_rng.randi();
        if(n>0)const_cast<V*>(a)[0]=V::from_int(int64_t(calls));
        if(mode==1 && !inside){inside=true;(void)gd::call_method(c,V::from_obj(this),m,a,n);inside=false;}
        if(mode==2)c.native_timer_watch.change();
        if(mode==3 && !inside){inside=true;gd::GdFuncRef ref;ref.instance=this;ref.method=m;(void)ref.call_func(c,a,n);inside=false;}
        out=V::from_int(int64_t(trace));return true;
    }
};
struct Sink:gd::GdObj {
    mutable uint64_t reads=0;uint64_t calls=0;V value;std::function<void()> action;
    explicit Sink(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &custom_meta;}
    bool get_prop(gd::SymId,V& out)const override{++reads;if(action)action();out=value;return true;}
    bool call_method(gd::BattleCtx& c,gd::SymId,const V*,int,V& out)override{
        ++calls;(void)c.math_rng.randi();if(action)action();out=value;return true;
    }
};
static const gd::NativeMethodRow* empty_row(gd::BattleCtx& c){
    Sink s(&c);V out;(void)gd::try_native_resolved_dispatch(c,&s,SYM_GEN_getP_188,nullptr,0,out,1);return s.native_call_row_;
}
static const gd::NativeMethodRow* choose_row(unsigned mode,const gd::NativeMethodRow* good,
        const gd::NativeMethodRow* wrong,const gd::NativeMethodRow* empty,gd::NativeMethodRow& copy){
    switch(mode){case 0:return good;case 1:return nullptr;case 2:copy=*good;return &copy;
    case 3:return wrong;case 4:copy={};return &copy;default:return empty;}
}
static void configure(gd::BattleCtx& c,unsigned flags){
    c.native_resolved_dispatch=(flags&1)!=0;c.native_resolved_audit=(flags&2)!=0;c.native_resolved_collect=true;
    c.native_timer_watch.enabled=true;c.native_timer_watch.collect=true;c.native_timer_watch.closed_world=(flags&4)!=0;
}
#ifdef OBJECT_ROUTES_CANDIDATE
extern "C" uint64_t gd_diag_native_object_route_stat(unsigned);
#endif
static uint64_t fast_assertions=0;
template<class Base> static uint64_t unknown_case(unsigned method,unsigned flags,unsigned row,unsigned mode,unsigned shared){
    gd::BattleCtx owner(4096),caller(4096);owner.bind_battle(91);caller.bind_battle(92);owner.native_resolved_dispatch=true;
    auto* donor=META_Gd__gd_core__CoreContext.alloc_fn(owner);donor->init_fields(owner);
    auto* wrong=META_Gd__gd_core__CoreBuff.alloc_fn(owner);wrong->init_fields(owner);
    const auto* empty=empty_row(owner);Override<Base> obj(&owner);obj.init_fields(owner);obj.shared=shared;obj.mode=mode;
    gd::NativeMethodRow copy{};obj.native_call_row_=choose_row(row,donor->native_call_row_,wrong->native_call_row_,empty,copy);
    configure(owner,flags);configure(caller,flags);const auto values=inputs(owner);
    auto* args=gd::GdArr::from_init(owner.arena,{values[method%16],V::from_int(42),V::from_bool(true),V::from_float(-0.0)});
    const int n=int((method+mode)%6)-1;const auto symbol=object_route_test_symbols[method];
    floating((method+mode)%4,(method/4+mode)%4);
#ifdef OBJECT_ROUTES_CANDIDATE
    const auto old=gd_diag_native_object_route_stat(0)+gd_diag_native_object_route_stat(1);
#endif
    auto h=hash(gd::call_method(caller,V::from_obj(&obj),symbol,args->data,n));
    h=mix(h,obj.saved==args->data);h=mix(h,uint64_t(obj.saved_count));
    if(obj.saved_count>0)h=mix(h,hash(obj.saved[0]));
    const V* retained=obj.saved;for(unsigned i=0;i<17;++i)args->push_back(owner.arena,V::from_int(i));
    if(obj.saved_count>0)h=mix(h,hash(retained[0]));
    h=mix(h,hash(gd::native_inline_call(caller,V::from_obj(&obj),symbol,args->data,n)));
    h=mix(h,obj.calls);h=mix(h,obj.trace);h=mix(h,obj.metadata_reads);h=mix(h,hash(V::from_arr(args)));
#ifdef OBJECT_ROUTES_CANDIDATE
    assert(old==gd_diag_native_object_route_stat(0)+gd_diag_native_object_route_stat(1));
#endif
    return state(caller,state(owner,h));
}
static uint64_t known_case(unsigned type,unsigned value,unsigned flags,unsigned row,unsigned api,unsigned round,unsigned daz){
    gd::BattleCtx owner(8192),other(4096);owner.bind_battle(123);other.bind_battle(124);owner.native_resolved_dispatch=true;
    const gd::GdClassMeta* metas[]={&META_Gd__gd_core__CoreContext,&META_Gd__gd_core__CoreItem,
        &META_Gd__gd_core__CoreDamageSource,&META_Gd__gd_core__CoreItem,&META_Gd__gd_core__CoreCharacter,
        &META_Gd__gd_core__CoreCharacter,&META_Gd__gd_core__CoreRng,&META_Gd__gd_core__CoreGrid,
        &META_Gd__gd_core_items__DemonicFlask,&META_Gd__gd_core_items__ManaPotion};
    const gd::SymId methods[]={SYM_GEN__nativeF32_1502,SYM_GEN_setCooldownActive_97,SYM_GEN_setDamage_1551,
        SYM_GEN_canDamage_89,SYM_GEN_getRelativeHealth_302,SYM_GEN_getBuffDamageMod_1258,
        SYM_GEN_pickRandomElement_1746,SYM_GEN_getItemInCell_1607,SYM_GEN_canDamage_89,SYM_GEN_isEmpty_923};
    auto* raw=metas[type]->alloc_fn(owner);raw->init_fields(owner);
    auto* donor=META_Gd__gd_core__CoreBuff.alloc_fn(owner);donor->init_fields(owner);
    const auto* empty=empty_row(owner);gd::NativeMethodRow copy{};
    raw->native_call_row_=choose_row(row,raw->native_call_row_,donor->native_call_row_,empty,copy);
    const auto values=inputs(owner);Sink sink(&owner);sink.value=values[value];
    Context context(&owner);context.init_fields(owner);context.f_in_item_physics_pass=V::from_bool(true);
    context.f_timer_pass_epoch=V::from_int(5);gd::GdRng rng(238);
    const V payload[]={values[value],values[(value+5)%16]};const V* args=payload;
    auto* array=gd::GdArr::from_init(owner.arena,{values[(value+3)%16],V::from_int(7),V::from_float(-0.0)});
    const V array_payload[]={V::from_arr(array)};
    if(type==1 || type==3){auto* item=static_cast<Item*>(raw);item->f_ctx=V::from_obj(&context);item->f_descriptor=V::from_obj(&sink);
        item->f__cooldown_active=values[(value+3)%16];item->f__cooldown_changed_epoch=V::from_int(2);item->f__cooldown_blocked_epoch=V::from_int(3);}
    if(type==3){sink.action=[&]{auto* item=static_cast<Item*>(raw);item->f_bonusMinDam=V::from_int(int64_t(sink.reads));owner.native_timer_watch.change();};}
    if(type==4 || type==5){auto* character=static_cast<Gd__gd_core__CoreCharacter*>(raw);
        character->f_curHealth=values[value];character->f_maxHealth=values[(value+1)%16];
        character->f_temporaryMaxHealth=V::from_int(3);character->f_temporaryMaxHealthGain=V::from_int(2);character->f_empowerDamage=V::from_float(0.3);
        auto* buffs=gd::GdArr::create(owner.arena,128);for(unsigned i=0;i<128;++i)buffs->push_back(owner.arena,V::from_obj(&sink));character->f_buffs=V::from_arr(buffs);
        sink.action=[&,character]{character->f_empowerDamage=values[(value+2)%16];owner.native_timer_watch.change();};}
    if(type==6){auto* object=static_cast<Gd__gd_core__CoreRng*>(raw);object->f_rng=V::from_rng(&rng);object->f_oracle_trace=V::from_bool(false);args=array_payload;}
    if(type==7){auto* dict=gd::GdDict::create(owner.arena,8);dict->set(owner.arena,V::from_vec2(-0.0,1.25),V::from_int(812));
        dict->set(owner.arena,V::from_int(7),V::from_int(192));static_cast<Gd__gd_core__CoreGrid*>(raw)->f_filledCells=V::from_dict(dict);}
    if(type==9)static_cast<Gd__gd_core_items__ManaPotion*>(raw)->f_isFull=values[value];
    configure(owner,flags);configure(other,flags);owner.native_event_kernel=other.native_event_kernel=(value&2)!=0;
    auto& caller=(value&1)?other:owner;const int argc=type==6?1:int(value%4)-1;
    floating(round,daz);
#ifdef OBJECT_ROUTES_CANDIDATE
    const auto before=gd_diag_native_object_route_stat(0)+gd_diag_native_object_route_stat(1);
#endif
    V out;
    if(api==0)out=gd::call_method(caller,V::from_obj(raw),methods[type],args,argc);
    else{gd::GdFuncRef ref;ref.instance=raw;ref.method=methods[type];out=ref.call_func(caller,args,argc);}
#ifdef OBJECT_ROUTES_CANDIDATE
    const auto after=gd_diag_native_object_route_stat(0)+gd_diag_native_object_route_stat(1);
    if((flags&1) && row==0 && api==0){assert(after>before);++fast_assertions;}
    if(type==0 && api==1)assert(after==before);
#endif
    auto h=hash(out);h=mix(h,sink.calls);h=mix(h,sink.reads);h=mix(h,rng.pcg.state);h=mix(h,hash(V::from_arr(array)));
    h=mix(h,hash(payload[0]));h=mix(h,hash(payload[1]));
    if(type==1 || type==3){auto* item=static_cast<Item*>(raw);h=mix(h,hash(item->f__cooldown_active));h=mix(h,hash(item->f__cooldown_changed_epoch));
        h=mix(h,hash(item->f__cooldown_blocked_epoch));h=mix(h,hash(item->f_bonusMinDam));}
    if(type==2){auto* damage=static_cast<Gd__gd_core__CoreDamageSource*>(raw);h=mix(h,hash(damage->f_minDamage));h=mix(h,hash(damage->f_maxDamage));}
    if(type==4 || type==5)h=mix(h,hash(static_cast<Gd__gd_core__CoreCharacter*>(raw)->f_empowerDamage));
    return state(other,state(owner,h));
}
int main(){
    register_gen_syms();const auto csr=_mm_getcsr();const auto rounding=std::fegetround();std::vector<uint64_t> hashes;
    for(unsigned method=0;method<object_route_test_symbols.size();++method)for(unsigned flags=0;flags<8;++flags)
    for(unsigned row=0;row<6;++row)for(unsigned mode=0;mode<4;++mode)for(unsigned shared=0;shared<2;++shared){
        hashes.push_back(unknown_case<Item>(method,flags,row,mode,shared));
        hashes.push_back(unknown_case<Context>(method,flags,row,mode,shared));}
    const auto unknown=hashes.size();
    for(unsigned type=0;type<10;++type)for(unsigned value=0;value<16;++value)for(unsigned flags=0;flags<8;++flags)
    for(unsigned row=0;row<6;++row)for(unsigned api=0;api<2;++api)for(unsigned round=0;round<4;++round)
    for(unsigned daz=0;daz<4;++daz)hashes.push_back(known_case(type,value,flags,row,api,round,daz));
    std::fesetround(rounding);_mm_setcsr(csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"unknown_cases\":"<<unknown<<",\"fast_assertions\":"<<fast_assertions<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}std::cout<<"]}\n";
}

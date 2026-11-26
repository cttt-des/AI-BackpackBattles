#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <utility>
#include <vector>
#include <xmmintrin.h>

using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
extern "C" void gd_init_all_classes();
static uint64_t mix(uint64_t a,uint64_t b){return (a^b)*UINT64_C(1099511628211);}
static uint64_t hash_value(const V& v){
    uint64_t h=mix(17,unsigned(v.kind));
    switch(v.kind){
    case V::Kind::Null:return h;
    case V::Kind::Bool:return mix(h,v.b);
    case V::Kind::Int:return mix(h,v.i);
    case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
    case V::Kind::Arr:
        if(!v.arr)return mix(h,0);
        h=mix(mix(mix(h,v.arr->len),v.arr->cap),v.arr->is_pool_real);
        for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash_value(v.arr->data[i]));
        return h;
    default:assert(false);return 0;
    }
}
static void prepare(Item& item,gd::BattleCtx& c,const V& n){
#ifdef GD_DISPLAY_CANDIDATE
    item.native_prepare_display_resize(c,n);
#endif
}
static V resize(Item& item,gd::BattleCtx& c,const V& n){
    prepare(item,c,n);
    return gd::native_inline_call(c,item.f_statDisplayOverrides,gd::SYM_resize,&n,1);
}
static void environment(unsigned mode){
    const int rounding[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
    assert(std::fesetround(rounding[mode%4])==0);std::feclearexcept(FE_ALL_EXCEPT);
    unsigned csr=_mm_getcsr();csr&=~((1u<<6)|(1u<<15));
    if(mode&4)csr|=1u<<6;if(mode&8)csr|=1u<<15;
    _mm_setcsr(csr);
    if(mode&16)std::feraiseexcept(FE_INEXACT);
    if(mode&32)std::feraiseexcept(FE_INVALID);
}
static V request(unsigned i){
    const int sizes[]={-9,0,1,3,4,9,10,11,21};
    if(i<9)return V::from_int(sizes[i]);
    if(i==9)return V::from_bool(true);
    if(i==10)return V::null();
    if(i==11)return V::from_float(3.5);
    if(i==12)return V::from_float(-0.0);
    return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));
}
static uint64_t storage_case(unsigned scenario,unsigned size,unsigned fp){
    gd::BattleCtx c(16384),foreign(16384);c.bind_battle(77);foreign.bind_battle(78);
    c.native_inline_timer_headers=scenario!=1;
    c.native_resolved_dispatch=(scenario%2)==0;c.native_resolved_audit=true;
    Item stack(&c);Item* item=scenario==2?&stack:
        static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(scenario==3?foreign:c));
    item->init_fields(c);
    V original=item->f_statDisplayOverrides;
    V* old_data=nullptr;uint64_t old_hash=0;
    Item copy(*item),moved(std::move(copy));
    if(scenario==4)original.arr->resize(c.arena,4);
    if(scenario==5)original.arr->is_pool_real=true;
    if(scenario==6 || scenario==19 || scenario==20){
        original.arr->timer_watch=&c.native_timer_watch;
        c.native_timer_watch.enabled=true;
        if(scenario==19)c.native_timer_watch.depth=UINT32_MAX;
        if(scenario==20)c.native_timer_watch.version=UINT64_MAX;
    }
    if(scenario==7)item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(c.arena));
    if(scenario==8)item->f_statDisplayOverrides=V::null();
    if(scenario==9)item->f_statDisplayOverrides=V::from_int(4);
    if(scenario==10)item->init_fields(c);
    if(scenario==11)item=&copy;
    if(scenario==12)item=&moved;
    if(scenario==13){original.arr->resize(c.arena,1);original.arr->data[0]=V::from_int(45);}
    if(scenario==14){item->init_fields(c);original.arr->resize(c.arena,2);original.arr->fill(V::from_int(61));}
    if(scenario==15)original.arr->resize(c.arena,0);
    if(scenario==16){original.arr->resize(c.arena,1);original.arr->resize(c.arena,0);}
    if(scenario==17){
        resize(*item,c,V::from_int(3));original.arr->data[0]=V::from_int(913);
        old_data=original.arr->data;old_hash=hash_value(old_data[0]);
        original.arr->data=nullptr;original.arr->len=original.arr->cap=0;
    }
    if(scenario==18){resize(*item,c,V::from_int(2));item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(c.arena));}
    if(scenario==21)item->f_statDisplayOverrides=V::from_arr(nullptr);
    if(scenario==22)item->init_fields(foreign);
    if(scenario==23){resize(*item,c,V::from_int(1));original.arr->data[0]=V::from_int(719);}
    V n=request(size);environment(fp);
    const auto result=resize(*item,c,n);
    const int flags=std::fetestexcept(FE_ALL_EXCEPT);const unsigned csr=_mm_getcsr();
    const bool same=item->f_statDisplayOverrides.kind==V::Kind::Arr && item->f_statDisplayOverrides.arr==original.arr;
    uint64_t h=mix(mix(hash_value(result),hash_value(item->f_statDisplayOverrides)),hash_value(original));
    h=mix(mix(mix(mix(h,flags),csr),same),c.native_timer_watch.version);
    h=mix(mix(h,c.native_timer_watch.depth),c.native_timer_watch.usable);
    if(old_data){assert(hash_value(old_data[0])==old_hash);h=mix(h,old_hash);}
#ifdef GD_DISPLAY_CANDIDATE
    if(scenario==0 && size>=2 && size<=6){
        assert(item->f_statDisplayOverrides.arr==&item->native_display_header_);
        assert(item->f_statDisplayOverrides.arr->data==item->native_display_values_);
    }
#endif
    auto* a=item->f_statDisplayOverrides.kind==V::Kind::Arr?item->f_statDisplayOverrides.arr:nullptr;
    if(a){
        a->fill(V::from_float(std::bit_cast<double>(UINT64_C(0x8000000000000000))));
        a->set_idx(-1,V::from_int(704));a->push_back(c.arena,V::from_float(2.25));
        auto* deep=a->duplicate(c.arena,true);deep->set_idx(0,V::from_int(883));
        h=mix(mix(h,hash_value(V::from_arr(deep))),hash_value(item->f_statDisplayOverrides));
        a->resize(c.arena,32);a->fill(V::null());h=mix(h,hash_value(item->f_statDisplayOverrides));
    }
    return h;
}
struct DescriptorProxy:gd::GdObj{
    Gd__gd_core__CoreItemData* real;Item* item;unsigned scenario;mutable unsigned calls=0;
    DescriptorProxy(gd::BattleCtx& c,Gd__gd_core__CoreItemData& d,Item& i,unsigned s):GdObj(&c),real(&d),item(&i),scenario(s){}
    const gd::GdClassMeta* meta()const override{return &META_Gd__gd_core__CoreItemData;}
    bool get_prop(gd::SymId prop,V& out)const override{
        ++calls;
        if(prop==SYM_GEN_cd_1679){
            if(scenario==2)item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(rt_ctx_->arena));
            if(scenario==3)item->f_statDisplayOverrides=V::null();
            if(scenario==4)item->f_statDisplayOverrides.arr->resize(rt_ctx_->arena,4);
        }
        return real->get_prop(prop,out);
    }
};
static uint64_t setup_case(unsigned scenario,unsigned fp){
    gd::BattleCtx c(65536);c.bind_battle(191);c.native_inline_timer_headers=scenario!=1;
    c.native_resolved_dispatch=(scenario%2)==0;c.native_resolved_audit=true;
    Gd__gd_core__CoreContext context(&c);context.init_fields(c);
    Gd__gd_core__CoreRng rng(&c);rng.init_fields(c);rng.f_rng=V::from_rng(&c.math_rng);context.f_rng=V::from_obj(&rng);
    Gd__gd_core__CoreItemData descriptor(&c);descriptor.init_fields(c);descriptor.f_sceneDepth=V::from_int(2);descriptor.f_cd=V::from_float(1.25);
    auto* item=static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(c));item->init_fields(c);
    if(scenario==5)item->init_fields(c);
    V old=item->f_statDisplayOverrides;
    DescriptorProxy proxy(c,descriptor,*item,scenario);
    const V args[]={V::from_obj(&context),scenario>=2&&scenario<=4?V::from_obj(&proxy):V::from_obj(&descriptor),V::null()};
    environment(fp);V result=item->fn_setup(args,3);
    const int flags=std::fetestexcept(FE_ALL_EXCEPT);const unsigned csr=_mm_getcsr();
    assert(result.kind==V::Kind::Obj && result.obj==item);
#ifdef GD_DISPLAY_CANDIDATE
    if(scenario==0){assert(item->f_statDisplayOverrides.arr==&item->native_display_header_);assert(item->f_statDisplayOverrides.arr->data==item->native_display_values_);}
#endif
    uint64_t h=mix(mix(mix(hash_value(item->f_statDisplayOverrides),hash_value(old)),flags),csr);
    h=mix(mix(mix(h,c.math_rng.pcg.state),c.math_rng.pcg.inc),proxy.calls);
    h=mix(mix(h,hash_value(item->f_itemMetrics)),c.next_gid);
    item->init_fields(c);assert(item->f_statDisplayOverrides.arr!=old.arr);
    h=mix(mix(h,hash_value(item->f_statDisplayOverrides)),hash_value(old));return h;
}
int main(){
    gd_init_all_classes();std::vector<uint64_t> hashes;
    for(unsigned fp=0;fp<64;++fp){
        for(unsigned scenario=0;scenario<24;++scenario)for(unsigned size=0;size<14;++size)hashes.push_back(storage_case(scenario,size,fp));
        for(unsigned scenario=0;scenario<6;++scenario)hashes.push_back(setup_case(scenario,fp));
    }
    std::fesetround(FE_TONEAREST);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"core_item_bytes\":"<<sizeof(Item)<<",\"gdval_bytes\":"<<sizeof(V)<<",\"gdarr_bytes\":"<<sizeof(gd::GdArr)<<",\"context_bytes\":"<<sizeof(gd::BattleCtx)<<",\"watch_bytes\":"<<sizeof(gd::NativeTimerWatch)<<",\"case_hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"]}\n";
}

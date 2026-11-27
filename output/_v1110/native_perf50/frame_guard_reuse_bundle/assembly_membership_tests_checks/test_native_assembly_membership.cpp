#include "gd_rt.hpp"
#include "native_assembly_membership.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
struct Foreign:gd::GdObj {
    mutable unsigned metadata_calls=0;unsigned callbacks=0;
    explicit Foreign(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{++metadata_calls;return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId,const V*,int,V&)override{++callbacks;return false;}
};
extern "C" uint64_t gd_diag_native_integer_grid_stat(unsigned);
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);
extern "C" uint64_t gd_diag_native_property_stat(unsigned);
extern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned);
extern "C" uint64_t gd_diag_native_dispatch_chain_stat(unsigned);
extern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);
static const std::pair<uint64_t(*)(unsigned),unsigned> counters[]={{gd_diag_native_integer_grid_stat,6},{gd_diag_native_variant_stat,10},{gd_diag_native_property_stat,2},{gd_diag_native_hot_slot_stat,2},{gd_diag_native_dispatch_chain_stat,4},{gd_diag_native_type_constructor_stat,4}};
static std::array<uint64_t,28> counter_values(){std::array<uint64_t,28> out{};unsigned at=0;for(auto [f,n]:counters)for(unsigned i=0;i<n;++i)out[at++]=f(i);assert(at==28);return out;}
struct Observation {bool value;int flags;unsigned csr;std::array<uint64_t,28> counts;bool operator==(const Observation&)const=default;};
__attribute__((noinline,noclone)) static Observation observed(bool candidate,const V& key,const V& set,unsigned mode){
    auto before=counter_values();std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(mode);
    bool value=candidate?gd::assembly_membership::object_set_contains(key,set):gd::native_scalar_truth(gd::gd_in(key,set));
    int flags=std::fetestexcept(FE_ALL_EXCEPT);unsigned csr=_mm_getcsr();auto after=counter_values();
    for(unsigned i=0;i<after.size();++i)after[i]-=before[i];
    return {value,flags,csr,after};
}
static uint64_t mix(uint64_t a,uint64_t b){return(a^b)*1099511628211ULL;}
static std::vector<unsigned char> representation(const V& value){
    std::vector<unsigned char> bytes;auto add=[&](const void* p,size_t n){auto* a=static_cast<const unsigned char*>(p);bytes.insert(bytes.end(),a,a+n);};
    add(&value,sizeof(value));
    if(value.kind==V::Kind::Dict && value.dict){add(value.dict,sizeof(*value.dict));if(value.dict->len)add(value.dict->entries,sizeof(gd::GdDictEntry)*value.dict->len);}
    if(value.kind==V::Kind::Arr && value.arr){add(value.arr,sizeof(*value.arr));if(value.arr->len)add(value.arr->data,sizeof(V)*value.arr->len);}
    return bytes;
}
int main(){
    static_assert(sizeof(V)==24 && sizeof(gd::GdDict)==32 && sizeof(gd::GdArr)==32 && sizeof(gd::BattleCtx)==328);
    fenv_t saved;std::fegetenv(&saved);unsigned saved_csr=_mm_getcsr();
    assert(std::fesetround(FE_TONEAREST)==0);_mm_setcsr(_mm_getcsr()&~(0x8040u|0x3fu));
    #include "assembly_membership_values.hpp"
    assert(values.size()==112);std::vector<V> sets=values;
    std::vector<gd::GdDict*> extras;
    auto make=[&](unsigned reserve=0){auto* d=gd::GdDict::create(ctx.arena,reserve);extras.push_back(d);sets.push_back(V::from_dict(d));return d;};
    make();make(64);
    auto* one=make();one->set(ctx.arena,V::from_obj(&first),V::from_bool(true));
    auto* two=make();two->set(ctx.arena,V::from_obj(&first),V::from_bool(false));two->set(ctx.arena,V::from_obj(&second),V::from_bool(true));
    auto* mixed=make();mixed->set(ctx.arena,V::from_obj(&first),V::from_int(17));mixed->set(ctx.arena,V::from_int(1),V::null());mixed->set(ctx.arena,V::from_float(1.5),V::from_bool(false));
    auto* dense=make();for(int i=0;i<64;++i)dense->set(ctx.arena,V::from_int(i),V::from_int(i));
    auto* cleared=make();for(int i=0;i<64;++i)cleared->set(ctx.arena,V::from_int(i),V::from_int(i));cleared->clear();
    auto* stale=make();stale->set(ctx.arena,V::from_obj(&first),V::from_bool(true));for(int i=0;i<32;++i)stale->set(ctx.arena,V::from_int(i),V::null());assert(stale->buckets && stale->bucket_cap);stale->len=0;
    auto* empty_grid=make();assert(empty_grid->enable_integer_grid(ctx.arena));
    auto* grid=make();assert(grid->enable_integer_grid(ctx.arena));grid->set(ctx.arena,V::from_vec2(0,0),V::null());grid->set(ctx.arena,V::from_vec2(1,-1),V::null());
    auto* nan_keys=make();nan_keys->set(ctx.arena,V::from_float(qnan),V::from_int(1));nan_keys->set(ctx.arena,V::from_float(snan),V::from_int(2));
    auto* strings=make();strings->set(ctx.arena,V::from_str(&collision_a),V::from_int(1));strings->set(ctx.arena,V::from_str(&collision_b),V::from_int(2));
    auto* arrays=make();arrays->set(ctx.arena,V::from_arr(array_a),V::from_int(1));arrays->set(ctx.arena,V::from_arr(nested_a),V::from_int(2));
    auto* stale_linear=make();stale_linear->set(ctx.arena,V::from_obj(&first),V::null());stale_linear->len=0;stale_linear->buckets=nullptr;stale_linear->bucket_cap=0;
    auto* reinsert=make();reinsert->set(ctx.arena,V::from_obj(&first),V::null());reinsert->set(ctx.arena,V::from_obj(&second),V::null());reinsert->erase(V::from_obj(&first));reinsert->set(ctx.arena,V::from_obj(&first),V::from_bool(false));
    auto* copy=mixed->duplicate(ctx.arena,true);extras.push_back(copy);sets.push_back(V::from_dict(copy));
    assert(extras.size()==16 && sets.size()==128);
    std::vector<std::vector<unsigned char>> dict_before;for(size_t i=0;i<extras.size();++i)dict_before.push_back(representation(sets[112+i]));
    auto rng_before=ctx.math_rng.pcg;
    uint64_t hash=1469598103934665603ULL,fast_hash=hash,cases=0,fast_cases=0;std::vector<uint64_t> hashes;
    for(int rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}){
        assert(std::fesetround(rounding)==0);
        for(unsigned denorm:{0u,0x40u,0x8000u,0x8040u}){
            unsigned mode=(_mm_getcsr()&~(0x8040u|0x3fu))|denorm|4u;
            for(size_t i=0;i<values.size();++i)for(size_t j=0;j<sets.size();++j){
                const auto& key=values[i];const auto& set=sets[j];auto oldkey=representation(key),oldset=representation(set);
                auto reference=observed(false,key,set,mode),actual=observed(true,key,set,mode);
                if(!(reference==actual)){std::cerr<<"Mismatch key="<<i<<" set="<<j<<" round="<<rounding<<" denorm="<<denorm<<" values="<<reference.value<<','<<actual.value<<" flags="<<reference.flags<<','<<actual.flags<<" csr="<<reference.csr<<','<<actual.csr<<'\n';std::abort();}
                assert(oldkey==representation(key) && oldset==representation(set));
                uint64_t h=mix(mix(mix(1469598103934665603ULL,actual.value),unsigned(actual.flags)),actual.csr);
                for(auto n:actual.counts)h=mix(h,n);hash=mix(hash,h);hashes.push_back(h);++cases;
                bool fast=key.kind==V::Kind::Obj && set.kind==V::Kind::Dict && set.dict && set.dict->len==0 && (!set.dict->buckets || set.dict->bucket_cap==0);
                if(fast){++fast_cases;fast_hash=mix(fast_hash,h);assert(!actual.value);}
            }
            // A zero length alone cannot bypass an indexed stale table.
            assert(observed(false,V::from_obj(&first),V::from_dict(stale),mode).value);
            assert(observed(true,V::from_obj(&first),V::from_dict(stale),mode).value);
            assert(first.metadata_calls==0 && second.metadata_calls==0 && first.callbacks==0 && second.callbacks==0);
        }
    }
    for(size_t i=0;i<extras.size();++i)assert(dict_before[i]==representation(sets[112+i]));
    assert(ctx.math_rng.pcg.state==rng_before.state && ctx.math_rng.pcg.inc==rng_before.inc);
    std::fesetenv(&saved);_mm_setcsr(saved_csr);assert(cases==229376 && hashes.size()==cases);
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"value_shapes\":112,\"container_states\":128,\"fp_modes\":16,\"fast_empty_object_cases\":"<<fast_cases<<",\"hash\":"<<hash<<",\"fast_hash\":"<<fast_hash<<",\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"input_and_container_representations_unchanged\":true,\"stale_index_and_nonobject_hash_fp_effects_preserved\":true}";
}

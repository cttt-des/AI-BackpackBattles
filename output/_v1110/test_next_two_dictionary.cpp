#include "gd_rt.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
struct Object:gd::GdObj {using GdObj::GdObj;const gd::GdClassMeta* meta()const override{return nullptr;}};
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
int main(){
    gd::BattleCtx ctx(8192);Object object(&ctx);gd::GdFuncRef reference;
    gd::GdStr collision_a{"alpha",5,123},collision_b{"bravo",5,123},same_a{"alpha",5,123};
    std::vector<V> keys={V::null(),V::from_bool(false),V::from_bool(true),
        V::from_int(0),V::from_int(1),V::from_int(-1),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_int(INT64_C(9007199254740993)),
        V::from_float(0.0),V::from_float(-0.0),V::from_float(1.0),V::from_float(0.3),
        V::from_float(std::bit_cast<double>(UINT64_C(1))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),
        V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000000000))),
        V::from_str(nullptr),V::from_str(&collision_a),V::from_str(&collision_b),V::from_str(&same_a),
        V::from_obj(nullptr),V::from_obj(&object),V::from_funcref(&reference),
        V::from_vec2(0.0,-0.0),V::from_vec2(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)),0),
        V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_float(0.3)})),
        V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_float(0.3)})),
        V::from_dict(gd::GdDict::create(ctx.arena))};
    const int rounds[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
    std::vector<uint64_t> hashes;
    for(int rounding:rounds)for(unsigned daz=0;daz<4;++daz)
    for(unsigned mode=0;mode<4;++mode)for(unsigned size:{0u,1u,8u,9u,17u,31u})
    for(unsigned rotation=0;rotation<keys.size();++rotation)for(const auto& query:keys){
        std::vector<gd::GdDictEntry> entries(size);std::vector<int32_t> buckets(128,-1);
        for(unsigned i=0;i<size;++i)entries[i]={keys[(i+rotation)%keys.size()],V::from_int(i),uint64_t(mode==3 && (i&1)?8:7)};
        gd::GdDict dict;dict.entries=entries.data();dict.len=dict.cap=size;
        if(mode&1){dict.buckets=buckets.data();dict.bucket_cap=128;
            for(unsigned i=0;i<size;++i){unsigned p=unsigned(entries[i].hash)&127;while(buckets[p]>=0)p=(p+1)&127;buckets[p]=i;}}
        std::fesetround(rounding);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~0x3fu);
        const auto index=dict.find_index(query,mode==2?8:7);
        uint64_t h=mix(1469598103934665603ULL,uint64_t(int64_t(index)));
        h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));h=mix(h,_mm_getcsr());hashes.push_back(h);
    }
    assert(hashes.size()==322944);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"]}\n";
}

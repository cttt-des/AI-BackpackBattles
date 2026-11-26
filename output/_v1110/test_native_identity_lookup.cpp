#include "native_scalar_equal.hpp"
#include "native_integer_grid.hpp"
#include <bit>
#include <algorithm>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
struct Observation {int64_t value;int flags;unsigned csr;bool operator==(const Observation&)const=default;};
struct Foreign:gd::GdObj {
    mutable unsigned metadata_calls=0;unsigned callbacks=0;
    explicit Foreign(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{++metadata_calls;return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId,const V*,int,V&)override{++callbacks;return false;}
};
static uint64_t hash=1469598103934665603ULL;
static std::vector<uint64_t> hashes;
static std::vector<std::vector<uint64_t>> grid_words;
static uint64_t mix(uint64_t a,uint64_t b){return(a^b)*1099511628211ULL;}
static void record(const std::vector<uint64_t>& words){for(auto x:words)hash=mix(hash,x);hashes.push_back(hash);}
static void append(std::vector<uint64_t>& words,Observation o){words.push_back(uint64_t(o.value));words.push_back(unsigned(o.flags));words.push_back(o.csr);}
template<class F> static Observation observed(unsigned mode,F f){
    std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(mode);
    int64_t v=f();return {v,std::fetestexcept(FE_ALL_EXCEPT),_mm_getcsr()};
}
__attribute__((noinline,noclone)) static Observation compare(unsigned op,const V& a,const V& b,unsigned mode){
    return observed(mode,[&]()->int64_t{
        switch(op){case 0:return gd::gd_eq(a,b);case 1:return gd::native_scalar_eq(a,b);
            case 2:return !gd::native_scalar_ne(a,b);default:return gd::native_lookup_eq(a,b);}
    });
}
__attribute__((noinline,noclone)) static int64_t original_find(const gd::GdArr& a,const V& v,int64_t from){
    if(from<0)from=std::max<int64_t>(0,int64_t(a.len)+from);
    for(uint32_t i=uint32_t(from);i<a.len;++i)if(gd::gd_eq(a.data[i],v))return i;
    return -1;
}
__attribute__((noinline,noclone)) static int64_t original_count(const gd::GdArr& a,const V& v){
    int64_t c=0;for(uint32_t i=0;i<a.len;++i)if(gd::gd_eq(a.data[i],v))++c;return c;
}
__attribute__((noinline,noclone)) static int64_t original_dict_find(const gd::GdDict& d,const V& key,uint64_t h){
    for(uint32_t i=0;i<d.len;++i)if(d.entries[i].hash==h && gd::gd_eq(d.entries[i].key,key))return i;return -1;
}
int main(){
    static_assert(sizeof(V)==24 && sizeof(gd::GdArr)==32 && sizeof(gd::GdDict)==32 && sizeof(gd::BattleCtx)==328);
    fenv_t saved;std::fegetenv(&saved);unsigned saved_csr=_mm_getcsr();
    gd::BattleCtx ctx;Foreign first(&ctx),second(&ctx);
    gd::GdRng rng_a{},rng_b{};gd::GdFuncRef ref_a{},ref_b{};
    gd::GdClassMeta cls_a{},cls_b{};gd::GdEnum enum_a{},enum_b{};
    std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true)};
    for(int64_t i:{INT64_MIN,INT64_MIN+1,-9007199254740993LL,-4294967296LL,-2LL,-1LL,0LL,1LL,2LL,
            4294967296LL,9007199254740991LL,9007199254740992LL,9007199254740993LL,INT64_MAX})values.push_back(V::from_int(i));
    const uint64_t bits[]={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0xfffffffffffffULL,0x10000000000000ULL,
        0x3ff0000000000000ULL,0xbff0000000000000ULL,0x3fe0000000000000ULL,0x4340000000000000ULL,
        0x7fefffffffffffffULL,0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000001ULL,
        0xfff8000000000042ULL,0x7ff0000000000001ULL,0xfff0000000000042ULL};
    for(auto b:bits)values.push_back(V::from_float(std::bit_cast<double>(b)));
    for(auto b:bits){double f=std::bit_cast<double>(b);values.push_back(V::from_vec2(f,0));values.push_back(V::from_vec2(0,f));}
    double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000001)),qnan=std::bit_cast<double>(UINT64_C(0x7ff8000000000012));
    gd::GdColor colors[]={{0,0,0,1},{-0.0,0,0,1},{1,2,3,4},{snan,0,0,1},{0,snan,0,1},{0,0,snan,1},{0,0,0,snan},{qnan,0,0,1}};
    values.push_back(V::from_color(nullptr));for(auto& c:colors)values.push_back(V::from_color(&c));
    gd::GdStr collision_a={"ab",2,123},collision_b={"cd",2,123};
    for(auto v:{V::from_str(nullptr),V::from_cstr(ctx.arena,""),V::from_cstr(ctx.arena,"abc"),V::from_cstr(ctx.arena,"abc"),
            V::from_str(gd::make_str(ctx.arena,"a\0b",3)),V::from_cstr(ctx.arena,"a\xc3\xa9"),V::from_str(&collision_a),V::from_str(&collision_b)})values.push_back(v);
    auto* empty_a=gd::GdArr::create(ctx.arena);auto* empty_b=gd::GdArr::create(ctx.arena);
    auto* array_a=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_float(snan)});
    auto* array_b=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_float(snan)});
    auto* nested_a=gd::GdArr::from_init(ctx.arena,{V::from_arr(array_a),V::from_int(2)});
    auto* nested_b=gd::GdArr::from_init(ctx.arena,{V::from_arr(array_b),V::from_int(2)});
    for(auto* a:{static_cast<gd::GdArr*>(nullptr),empty_a,empty_b,array_a,array_b,nested_a,nested_b})values.push_back(V::from_arr(a));
    gd::GdDict dict_a{},dict_b{};
    for(auto* d:{static_cast<gd::GdDict*>(nullptr),&dict_a,&dict_b})values.push_back(V::from_dict(d));
    for(unsigned kind:{9u,10u,11u}){V v;v.kind=V::Kind(kind);v.i=0;values.push_back(v);}
    for(auto v:{V::from_obj(&first),V::from_obj(&second),V::from_cls(&cls_a),V::from_cls(&cls_b),V::from_enum(&enum_a),V::from_enum(&enum_b),
            V::from_funcref(nullptr),V::from_funcref(&ref_a),V::from_funcref(&ref_b),V::from_rng(nullptr),V::from_rng(&rng_a),V::from_rng(&rng_b)})values.push_back(v);
    for(unsigned kind:{14u,255u}){V v;v.kind=V::Kind(kind);v.i=0x12345678;values.push_back(v);}
    std::vector<gd::GdArr*> arrays={empty_a,array_a,nested_a};
    auto make_array=[&](std::initializer_list<V> list){auto* a=gd::GdArr::from_init(ctx.arena,list);arrays.push_back(a);};
    make_array({V::from_obj(&first),V::from_obj(&second),V::from_obj(&first),V::null()});
    make_array({V::from_int(1),V::from_bool(true),V::from_float(1),V::from_float(snan),V::from_float(qnan)});
    make_array({V::from_color(&colors[3]),V::from_color(&colors[3]),V::from_color(nullptr)});
    make_array({V::from_str(&collision_a),V::from_str(&collision_b),V::from_cstr(ctx.arena,"abc")});
    make_array({V::from_arr(array_a),V::from_arr(array_b),V::from_arr(nullptr)});
    auto* all=gd::GdArr::create(ctx.arena,uint32_t(values.size()));for(auto v:values)all->push_back(ctx.arena,v);arrays.push_back(all);
    std::vector<gd::GdDict*> dicts;
    for(unsigned shape=0;shape<9;++shape){
        auto* d=gd::GdDict::create(ctx.arena,shape%3==1?32:0);
        if(shape>=6){for(int i=0;i<6;++i)d->set(ctx.arena,V::from_vec2(i,i%2),V::from_int(100+i));assert(d->enable_integer_grid(ctx.arena));}
        else if(shape>=3){for(size_t i=0;i<values.size();++i)d->set(ctx.arena,values[i],V::from_int(1000+i));}
        else for(int i=0;i<int(shape);++i)d->set(ctx.arena,V::from_int(100+i),V::from_int(i));
        if(shape==5)d->erase(V::from_int(1));
        if(shape==8)d->set(ctx.arena,V::from_cstr(ctx.arena,"grid-to-ordinary"),V::from_int(-8));
        dicts.push_back(d);
    }
    uint64_t pairs=0,array_cases=0,dict_cases=0,alias_cases=0,once_cases=0;
    const int64_t starts[]={INT64_MIN,-100,-3,-1,0,1,3,INT64_C(0x100000000),INT64_MAX};
    for(int rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}){
        assert(std::fesetround(rounding)==0);
        for(unsigned denorm:{0u,0x40u,0x8000u,0x8040u}){
            unsigned mode=(_mm_getcsr()&~(0x8040u|0x3fu))|denorm|4u;
            for(const auto& a:values)for(const auto& b:values){
                unsigned char saved_a[sizeof(V)],saved_b[sizeof(V)];std::memcpy(saved_a,&a,sizeof(V));std::memcpy(saved_b,&b,sizeof(V));
                auto reference=compare(0,a,b,mode);std::vector<uint64_t> words;
                append(words,reference);
                for(unsigned op:{1u,2u,3u}){auto r=compare(op,a,b,mode);assert(r==reference);append(words,r);}
                assert(std::memcmp(&a,saved_a,sizeof(V))==0 && std::memcmp(&b,saved_b,sizeof(V))==0);
                record(words);++pairs;
            }
            for(auto* a:arrays)for(const auto& v:values)for(auto from:starts){
                std::vector<unsigned char> before(a->len*sizeof(V));if(a->len)std::memcpy(before.data(),a->data,before.size());auto* data=a->data;auto len=a->len,cap=a->cap;
                auto expected=observed(mode,[&]{return original_find(*a,v,from);});
                auto actual=observed(mode,[&]{return a->find_val(v,from);});assert(actual==expected);
                auto ec=observed(mode,[&]{return original_count(*a,v);});auto ac=observed(mode,[&]{return a->count_val(v);});assert(ec==ac);
                assert(a->len==len && a->cap==cap && a->data==data && (!len || std::memcmp(before.data(),a->data,len*sizeof(V))==0));
                std::vector<uint64_t> words={len,cap};append(words,actual);append(words,ac);record(words);++array_cases;
            }
            for(auto* a:arrays)for(uint32_t i=0;i<a->len;++i){
                const V& v=a->data[i];auto e=observed(mode,[&]{return original_find(*a,v,0);});auto r=observed(mode,[&]{return a->find_val(v,0);});assert(e==r);
                std::vector<uint64_t> words={i};append(words,r);record(words);++alias_cases;
            }
            for(auto* d:dicts)for(const auto& key:values)for(unsigned hash_mode=0;hash_mode<3;++hash_mode){
                std::vector<unsigned char> before(d->len*sizeof(gd::GdDictEntry));if(d->len)std::memcpy(before.data(),d->entries,before.size());auto* entries=d->entries;auto* buckets=d->buckets;
                auto len=d->len,cap=d->cap,bcap=d->bucket_cap;
                auto actual=observed(mode,[&]{uint64_t h=gd::gd_val_hash(key);if(hash_mode==1)h^=1;if(hash_mode==2 && d->len)h=d->entries[0].hash;return d->find_index(key,h);});
                if(!gd::integer_grid_detail::enabled(*d)){
                    auto expected=observed(mode,[&]{uint64_t h=gd::gd_val_hash(key);if(hash_mode==1)h^=1;if(hash_mode==2 && d->len)h=d->entries[0].hash;return original_dict_find(*d,key,h);});assert(actual==expected);
                }
                assert(d->len==len && d->cap==cap && d->bucket_cap==bcap && d->entries==entries && d->buckets==buckets);
                assert(!len || std::memcmp(before.data(),entries,len*sizeof(gd::GdDictEntry))==0);
                std::vector<uint64_t> words={len,cap,bcap};append(words,actual);record(words);
                if(gd::integer_grid_detail::enabled(*d))grid_words.push_back(words);++dict_cases;
            }
            unsigned calls=0;auto once=[&](){++calls;return V::from_obj(&first);};
            assert(gd::native_scalar_eq(once(),V::from_obj(&first)) && calls==1);record({calls});++once_cases;
            assert(first.metadata_calls==0 && second.metadata_calls==0 && first.callbacks==0 && second.callbacks==0);
        }
    }
    std::fesetenv(&saved);_mm_setcsr(saved_csr);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"value_shapes\":"<<values.size()<<",\"pair_cases\":"<<pairs
        <<",\"array_cases\":"<<array_cases<<",\"alias_cases\":"<<alias_cases<<",\"dictionary_cases\":"<<dict_cases<<",\"once_cases\":"<<once_cases
        <<",\"all16_fp_modes\":true,\"full_observations_compared\":true,\"hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"grid_observations\":[";
    for(size_t i=0;i<grid_words.size();++i){if(i)std::cout<<',';std::cout<<'[';for(size_t j=0;j<grid_words[i].size();++j){if(j)std::cout<<',';std::cout<<grid_words[i][j];}std::cout<<']';}
    std::cout<<"],\"hash\":"<<hash<<"}";
}

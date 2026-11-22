#include "gd_rt.hpp"
#include "native_integer_grid.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
using V=gd::GdVal;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t fast_queries=0;
static const gd::GdClassMeta dummy_meta{65011,"GridDictionaryIdentity"};
struct Dummy:gd::GdObj{using GdObj::GdObj;const gd::GdClassMeta* meta()const override{return &dummy_meta;}};
struct Fixture {
    gd::BattleCtx c{65536};gd::GdDict* dict;std::array<Dummy*,4> objects;
    gd::GdArr* array;gd::GdDict* nested;uint64_t trace=1469598103934665603ULL;
    Fixture(unsigned config) {
        for(auto& o:objects)o=c.arena.make<Dummy>(&c);
        array=gd::GdArr::from_init(c.arena,{V::from_int(42),V::from_float(-0.0)});
        nested=gd::GdDict::create(c.arena);nested->set(c.arena,V::from_int(1),V::from_int(9));
        dict=gd::GdDict::create(c.arena);
        const unsigned n=std::array<unsigned,4>{0,8,64,256}[config];
        for(unsigned i=0;i<n;++i)dict->set(c.arena,cell(i),value(i));
    }
    static V cell(unsigned i){return V::from_vec2((i%16)?double(i%16):-0.0,(i/16)?double(i/16):-0.0);}
    V value(unsigned i)const {switch(i%5){case 0:return V::from_int(i);case 1:return V::from_float(i?double(i):-.0);case 2:return V::from_obj(objects[i%4]);case 3:return V::from_arr(array);default:return V::null();}}
    uint64_t hash(const V& v,unsigned depth=0)const {
        uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
        switch(v.kind){case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
        case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
        case V::Kind::Obj:for(unsigned i=0;i<objects.size();++i)if(v.obj==objects[i])return mix(h,i+1);return mix(h,0);
        case V::Kind::Str:if(v.str)for(unsigned i=0;i<v.str->len;++i)h=mix(h,uint8_t(v.str->data[i]));return h;
        case V::Kind::Arr:if(v.arr && depth<3){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i],depth+1));}return h;
        case V::Kind::Dict:if(v.dict && depth<3){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key,depth+1));h=mix(h,hash(v.dict->entries[i].val,depth+1));}}return h;
        default:return h;}
    }
    void state() {
        trace=mix(trace,dict->len);trace=mix(trace,dict->cap);
        for(unsigned i=0;i<dict->len;++i){const auto& e=dict->entries[i];trace=mix(trace,hash(e.key));trace=mix(trace,hash(e.val));
            if(e.key.kind==V::Kind::Vec2 || e.key.kind==V::Kind::Int || e.key.kind==V::Kind::Float || e.key.kind==V::Kind::Str)trace=mix(trace,e.hash);}
        trace=mix(trace,c.next_gid);trace=mix(trace,c.math_rng.pcg.state);trace=mix(trace,c.math_rng.pcg.inc);
    }
    void flags(){trace=mix(trace,std::fetestexcept(FE_ALL_EXCEPT));trace=mix(trace,_mm_getcsr()&0x3f);}
    static void clear_flags(){std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(_mm_getcsr()&~unsigned(0x3f));}
    void query(const V& key) {
        clear_flags();int32_t index;
#ifdef GD_GRID_NEW
        if(dict->try_integer_grid_index(key,index))++fast_queries;else
#endif
            index=dict->find_index(key);
        trace=mix(trace,uint32_t(index));if(index>=0)trace=mix(trace,hash(dict->entries[index].val));flags();
        clear_flags();trace=mix(trace,hash(dict->get(key,V::from_int(-901))));flags();
        clear_flags();trace=mix(trace,dict->has(key));flags();
        clear_flags();const auto h=gd::gd_val_hash(key);trace=mix(trace,uint32_t(dict->find_index(key,h^UINT64_C(0x123456789))));flags();
    }
    void queries() {
        for(unsigned i=0;i<256;++i)query(cell(i));
        for(uint64_t raw:std::array<uint64_t,14>{0,UINT64_C(0x8000000000000000),1,UINT64_C(0x8000000000000001),UINT64_C(0x0010000000000000),UINT64_C(0x3fe0000000000000),UINT64_C(0xbff0000000000000),UINT64_C(0x4030000000000000),UINT64_C(0x7fefffffffffffff),UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0x7ff0000000001234),UINT64_C(0xfff0000000001234)}) {
            const double d=std::bit_cast<double>(raw);query(V::from_vec2(d,0));query(V::from_vec2(-1,d));
        }
        for(const V key:{V::null(),V::from_int(1),V::from_float(1),V::from_obj(objects[0]),V::from_str(gd::make_static_str("cell")),V::from_arr(array),V::from_dict(nested)})query(key);
    }
    void enable(unsigned config) {
#ifdef GD_GRID_NEW
        if(config!=3)(void)dict->enable_integer_grid(c.arena);
#endif
    }
    void mutate(unsigned scenario) {
        switch(scenario) {
        case 0:break;
        case 1:for(unsigned i=0;i<256;++i)dict->set(c.arena,cell(i),value(i+1));break;
        case 2:for(unsigned i=0;i<256;i+=3)dict->erase(cell(i));break;
        case 3:dict->set(c.arena,V::from_vec2(0,0),V::from_int(881));break;
        case 4:dict->set(c.arena,V::from_vec2(16,0),V::from_int(884));break;
        case 5:dict->set(c.arena,V::from_vec2(-1,0),V::from_int(885));break;
        case 6:dict->set(c.arena,V::from_vec2(.5,0),V::from_int(886));break;
        case 7:dict->set(c.arena,V::from_vec2(std::bit_cast<double>(UINT64_C(1)),0),V::from_int(887));break;
        case 8:dict->set(c.arena,V::from_vec2(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)),0),V::from_int(888));break;
        case 9:dict->set(c.arena,V::from_vec2(-1,std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),V::from_int(889));break;
        case 10:dict->set(c.arena,V::from_vec2(std::bit_cast<double>(UINT64_C(0x7ff0000000000000)),0),V::from_int(890));break;
        case 11:dict->set(c.arena,V::from_int(1),V::from_int(891));break;
        case 12:dict->set(c.arena,V::from_obj(objects[0]),V::from_int(892));break;
        case 13:dict->set(c.arena,V::from_str(gd::make_static_str("cell")),V::from_int(893));break;
        case 14:for(unsigned i=0;i<64;++i)dict->set(c.arena,cell(i),V::from_obj(objects[(i+1)%4]));break;
        case 15:for(unsigned i=0;i<256;++i)dict->erase(cell(i));break;
        case 16:dict->clear();for(unsigned i=0;i<16;++i)dict->set(c.arena,cell(i*17),value(i));break;
        case 17:dict->invert(c.arena);break;
        case 18:dict=dict->duplicate(c.arena,false);break;
        case 19:dict=dict->duplicate(c.arena,true);break;
        case 20:{auto* keys=dict->keys(c.arena);if(keys->len)keys->set_idx(0,V::from_vec2(9,9));break;}
        case 21:dict->set(c.arena,V::from_arr(array),V::from_int(901));array->set_idx(0,V::from_int(902));break;
        case 22:dict->set(c.arena,V::from_dict(nested),V::from_int(903));break;
        case 23:dict->clear();break;
        case 24:{V alias=V::from_dict(dict);alias.dict->set(c.arena,cell(255),V::from_int(904));alias.dict->erase(cell(0));break;}
        case 25:for(unsigned i=0;i<64;++i){dict->erase(cell(i));dict->set(c.arena,cell(i),value(i));}break;
        case 26:dict->set(c.arena,V::from_vec2(32,32),V::null());dict->erase(V::from_vec2(32,32));break;
        case 27:dict->set(c.arena,cell(0),V::from_dict(nested));nested->set(c.arena,V::from_int(1),V::from_int(999));break;
        }
    }
};
static uint64_t run(unsigned scenario,unsigned config,int rounding,unsigned denorm) {
    std::fesetround(rounding);unsigned csr=_mm_getcsr();_mm_setcsr((csr&~unsigned(0x8040))|((denorm&1)?0x40:0)|((denorm&2)?0x8000:0));
    Fixture::clear_flags();Fixture f(config);f.flags();
    if(scenario==22){f.dict->set(f.c.arena,V::from_int(17),V::null());f.flags();}
    if(scenario==23 && f.dict->len)f.dict->entries[0].hash^=UINT64_C(0x45678);
    Fixture::clear_flags();f.enable(config);f.flags();f.state();f.queries();
    Fixture::clear_flags();f.mutate(scenario);f.flags();f.state();f.queries();
    _mm_setcsr(_mm_getcsr()^unsigned(0x8040));f.queries();f.state();
    return f.trace;
}
int main() {
    const unsigned csr=_mm_getcsr();const int rounding=std::fegetround();std::vector<uint64_t> hashes;
    for(unsigned s=0;s<28;++s)for(unsigned c=0;c<4;++c)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned d=0;d<4;++d)hashes.push_back(run(s,c,r,d));
    _mm_setcsr(csr);std::fesetround(rounding);
#ifdef GD_GRID_NEW
    assert(fast_queries>0);
#endif
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"hashes\":[";
    for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}
    std::cout<<"],\"fast_queries\":"<<fast_queries<<",\"GdDict\":"<<sizeof(gd::GdDict)<<",\"GdVal\":"<<sizeof(V)<<",\"GdArr\":"<<sizeof(gd::GdArr)<<",\"BattleCtx\":"<<sizeof(gd::BattleCtx)<<"}\n";
}

#include "preflight_spatial.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bit>
#include <cassert>
#include <cfenv>
#include <chrono>
#include <iostream>
#include <memory>
using V=gd::GdVal;
using Grid=Gd__gd_core__CoreGrid;
using Item=Gd__gd_core__CoreItem;
extern "C" uint64_t gd_diag_native_variant_stat(unsigned);
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t hash(const V& v){uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));switch(v.kind){
case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));
case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
case V::Kind::Str:if(v.str){h=mix(h,v.str->len);h=mix(h,v.str->hash);for(unsigned i=0;i<v.str->len;++i)h=mix(h,(unsigned char)v.str->data[i]);}return h;
case V::Kind::Obj:return mix(h,v.obj?v.obj->gid_:0);case V::Kind::Arr:if(v.arr){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));}return h;
case V::Kind::Dict:if(v.dict){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key));h=mix(h,hash(v.dict->entries[i].val));}}return h;
case V::Kind::ClassRef:return mix(h,v.cls?v.cls->id:0);case V::Kind::Enum:return mix(h,v.en?v.en->len:0);default:return h;}}
static V invoke(bool candidate,unsigned mode,Grid& grid,const V* args,int argc){
#ifdef GD_SPATIAL_PRODUCTION
    candidate=false;
#endif
    if(mode==0)return candidate?candidate_getItemsInCells(grid,args,argc):grid.fn_getItemsInCells(args,argc);
    if(mode==1)return candidate?candidate_countItemsInCells(grid,args,argc):grid.fn_countItemsInCells(args,argc);
    return candidate?candidate_getBagsInCells(grid,args,argc):grid.fn_getBagsInCells(args,argc);
}
struct Mutator:gd::GdObj {
    Grid* grid=nullptr;gd::GdDict* map=nullptr;gd::GdArr* cells=nullptr;V replacement;V nested_cells;unsigned mode=0;bool candidate=false;mutable unsigned reads=0;unsigned calls=0;mutable bool busy=false;mutable uint64_t nested=0;
    explicit Mutator(gd::BattleCtx* c):GdObj(c){gid_=900;}
    const gd::GdClassMeta* meta()const override{return &META_Gd__gd_core__CoreItem;}
    bool get_prop(gd::SymId prop,V& out)const override{
        if(prop!=SYM_GEN_placed_6){out=replacement;return true;}
        ++reads;
        if(!busy){busy=true;
            if(mode==1)map->set(rt_ctx_->arena,V::from_vec2(1,0),replacement);
            if(mode==2)map->erase(V::from_vec2(1,0));
            if(mode==3)map->clear();
            if(mode==4)grid->f_filledCells=replacement;
            if(mode==5 && cells && cells->len>1)cells->data[1]=V::from_vec2(2,0);
            if(mode==6 && cells)cells->push_back(rt_ctx_->arena,V::from_vec2(2,0));
            if(mode==7){nested=mix(nested,hash(invoke(candidate,0,*grid,&nested_cells,1)));}
            busy=false;
        }
        out=mode==8?V::from_bool(reads%2==0):V::from_bool(true);return true;
    }
    bool call_method(gd::BattleCtx&,gd::SymId method,const V*,int,V& out)override{
        ++calls;if(method==gd::SYM_has){if(mode==9)grid->f_filledCells=replacement;out=V::from_bool(true);return true;}return false;
    }
};
struct Fixture {
    gd::BattleCtx persistent{65536},c{65536};Grid grid{&c};std::vector<std::unique_ptr<Item>> items;Mutator custom{&c};V cells;gd::GdDict* map;
    Fixture(unsigned count=24){
        c.native_resolved_dispatch=true;c.native_resolved_audit=true;grid.gid_=800;
        for(unsigned i=0;i<12;++i){auto p=std::make_unique<Item>(&c);p->gid_=i+1;p->f_placed=V::from_bool(i%4!=0);items.push_back(std::move(p));}
        map=gd::GdDict::create(persistent.arena,count);auto* a=gd::GdArr::create(persistent.arena,count);
        for(unsigned i=0;i<count;++i){const V key=V::from_vec2(i%8,i/8);map->set(persistent.arena,key,V::from_obj(items[i%items.size()].get()));a->push_back(persistent.arena,key);}
        cells=V::from_arr(a);grid.f_filledCells=grid.f_bagCells=V::from_dict(map);custom.grid=&grid;custom.map=map;custom.cells=a;custom.replacement=V::from_obj(items[3].get());
        custom.nested_cells=V::from_arr(gd::GdArr::from_init(persistent.arena,{V::from_vec2(2,0)}));
    }
};
static V key_for(Fixture& f,unsigned mode){
    switch(mode%18){case 0:return V::from_vec2(0,0);case 1:return V::from_vec2(-0.0,0);case 2:return V::from_vec2(1.25,-3.5);
    case 3:return V::from_vec2(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)),1);
    case 4:return V::from_vec2(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)),1);
    case 5:return V::from_vec2(1,std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
    case 6:return V::from_int(0);case 7:return V::from_int(INT64_MIN);case 8:return V::from_bool(false);
    case 9:return V::from_float(-0.0);case 10:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
    case 11:return V::from_str(gd::make_static_str("cell"));case 12:return V::from_obj(f.items[0].get());case 13:return V::null();
    case 14:return V::from_arr(gd::GdArr::from_init(f.persistent.arena,{V::from_int(1)}));case 15:return V::from_dict(gd::GdDict::create(f.persistent.arena));
    case 16:return V::from_cls(&META_Gd__gd_core__CoreItem);default:return V::from_vec2(1e100,1e-200);}}
static V value_for(Fixture& f,unsigned mode){switch(mode%12){case 0:return V::from_obj(f.items[0].get());case 1:return V::from_obj(f.items[3].get());case 2:return V::from_obj(nullptr);
    case 3:return V::null();case 4:return V::from_int(1);case 5:return V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
    case 6:return V::from_arr(gd::GdArr::from_init(f.persistent.arena,{V::from_int(3)}));case 7:{auto* d=gd::GdDict::create(f.persistent.arena);d->set(f.persistent.arena,V::from_str(gd::make_static_str("placed")),V::from_bool(true));return V::from_dict(d);}
    case 8:return V::from_str(gd::make_static_str("x"));case 9:return V::from_bool(true);case 10:return V::from_vec2(-0.0,1);default:return V::from_arr(nullptr);}}
static uint64_t run_case(bool candidate,unsigned mode,unsigned scenario,bool native,bool collect,int rounding){
    Fixture f((scenario%4==0)?0:(scenario%4==1)?4:(scenario%4==2)?24:65);f.custom.candidate=candidate;
    if(scenario<216){V key=key_for(f,scenario/12),value=value_for(f,scenario%12);f.map->set(f.persistent.arena,key,value);auto* a=gd::GdArr::create(f.persistent.arena,4);for(unsigned i=0;i<3;++i)a->push_back(f.persistent.arena,key);a->push_back(f.persistent.arena,V::from_vec2(999,999));f.cells=V::from_arr(a);}
    else if(scenario<226){f.map->clear();for(unsigned i=0;i<3;++i)f.map->set(f.persistent.arena,V::from_vec2(i,0),i?V::from_obj(f.items[3].get()):V::from_obj(&f.custom));f.cells=V::from_arr(gd::GdArr::from_init(f.persistent.arena,{V::from_vec2(0,0),V::from_vec2(1,0),V::from_vec2(2,0),V::from_vec2(0,0)}));f.custom.cells=f.cells.arr;f.custom.mode=scenario-216;if(f.custom.mode==4)f.custom.replacement=V::from_dict(gd::GdDict::create(f.persistent.arena));}
    else if(scenario<238){const unsigned kind=scenario-226;V x=kind<8?value_for(f,kind):kind==8?V::from_dict(nullptr):kind==9?V::from_arr(nullptr):kind==10?V::from_obj(&f.custom):V::from_str(gd::make_static_str("cell"));f.grid.f_filledCells=f.grid.f_bagCells=x;f.cells=V::from_arr(gd::GdArr::from_init(f.persistent.arena,{V::from_str(gd::make_static_str("cell")),V::from_int(0)}));if(kind==10){f.custom.mode=9;auto* d=gd::GdDict::create(f.persistent.arena);d->set(f.persistent.arena,V::from_str(gd::make_static_str("cell")),f.custom.replacement);f.custom.replacement=V::from_dict(d);}}
    else {const unsigned kind=scenario-238;f.cells=kind==0?V::null():kind==1?V::from_arr(nullptr):kind==2?V::from_dict(f.map):kind==3?V::from_int(4):kind==4?V::from_bool(true):V::from_float(2.5);}
    f.c.native_resolved_dispatch=native;f.c.native_resolved_collect=collect;std::array<uint64_t,10> before{};for(unsigned i=0;i<10;++i)before[i]=gd_diag_native_variant_stat(i);
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    const V result=invoke(candidate,mode,f.grid,&f.cells,scenario==244?0:1);const int flags=std::fetestexcept(FE_ALL_EXCEPT);
    uint64_t h=mix(hash(result),flags);h=mix(h,hash(f.grid.f_filledCells));h=mix(h,hash(f.cells));h=mix(h,hash(V::from_dict(f.map)));h=mix(h,f.c.next_gid);h=mix(h,f.c.math_rng.pcg.state);h=mix(h,f.c.math_rng.pcg.inc);
    h=mix(mix(mix(h,f.custom.reads),f.custom.calls),f.custom.nested);for(auto count:f.c.native_resolved_counts)h=mix(h,count);for(unsigned i=0;i<10;++i)h=mix(h,gd_diag_native_variant_stat(i)-before[i]);return h;
}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 n;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
struct Timing{double cpu_s,wall_s;uint64_t cycle_count,digest;};static volatile uint64_t sink;
static Timing bench(bool candidate,unsigned mode,unsigned count){Fixture f(mode==3?64:24);f.c.native_resolved_audit=false;const unsigned method=mode%3;uint64_t h=0;
    for(unsigned i=0;i<64;++i)(void)invoke(candidate,method,f.grid,&f.cells,1);f.c.arena.reset();const auto before=cpu(),cy=cycles();const auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<count;++i){if(i%32==0)f.c.arena.reset();const auto result=invoke(candidate,method,f.grid,&f.cells,1);h=mix(h,result.kind==V::Kind::Arr?result.arr->len:result.dict->len);}
    const double wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();sink=h;return{(cpu()-before)*1e-9,wall,cycles()-cy,h};}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycle_count<<",\"digest\":"<<t.digest<<'}';}
int main(int argc,char**){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));std::vector<uint64_t> hashes;
    for(unsigned method=0;method<3;++method)for(unsigned scenario=0;scenario<245;++scenario)for(bool native:{false,true})for(bool collect:{false,true})for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        const auto a=run_case(false,method,scenario,native,collect,rounding),b=run_case(true,method,scenario,native,collect,rounding);if(a!=b){std::cerr<<"mismatch method="<<method<<" scenario="<<scenario<<" native="<<native<<" collect="<<collect<<" rounding="<<rounding<<" a="<<std::hex<<a<<" b="<<b<<'\n';return 2;}hashes.push_back(a);}
    assert(std::fesetround(FE_TONEAREST)==0);std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size();
    if(argc>1){std::cout<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;}
    std::cout<<",\"workloads\":[";for(unsigned mode=0;mode<4;++mode){if(mode)std::cout<<',';std::cout<<"{\"mode\":"<<mode<<",\"calls_per_arm\":100000,\"pairs\":[";for(unsigned pair=0;pair<8;++pair){Timing a,b;if(pair%2){b=bench(true,mode,100000);a=bench(false,mode,100000);}else{a=bench(false,mode,100000);b=bench(true,mode,100000);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";
}

#include "preflight_frame_helper.hpp"
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
#include <vector>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
using Character=Gd__gd_core__CoreCharacter;
using Buff=Gd__gd_core__CoreBuff;
using Context=Gd__gd_core__CoreContext;
namespace gd {void native_frame_segment_hit(unsigned){assert(false && "counter collection must stay disabled during timing");}}
template<class T> static T* make(gd::BattleCtx& c,const gd::GdClassMeta& m){auto* p=static_cast<T*>(m.alloc_fn(c));p->init_fields(c);return p;}
struct Fixture {
    gd::BattleCtx battle{65536};Context* context;Character* characters[2];Buff* heats[2];Buff* colds[2];std::vector<Item*> items;
    Fixture(){
        battle.native_resolved_dispatch=true;battle.native_resolved_audit=false;battle.native_resolved_collect=false;
        context=make<Context>(battle,META_Gd__gd_core__CoreContext);
        context->f_timer_pass_epoch=V::from_int(0);context->f_show_cooldown_progress=V::from_bool(false);
        for(unsigned side=0;side<2;++side){
            auto* character=make<Character>(battle,META_Gd__gd_core__CoreCharacter);characters[side]=character;
            character->f_stunnedDuration=V::from_float(0.0);
            auto* buffs=gd::GdDict::create(battle.arena,15);character->f_buffs=V::from_dict(buffs);
            for(unsigned slot=0;slot<15;++slot){auto* buff=make<Buff>(battle,META_Gd__gd_core__CoreBuff);buff->f_current=V::from_int(slot%4);buffs->set(battle.arena,V::from_int(100+slot),V::from_obj(buff));if(slot==7)heats[side]=buff;if(slot==10)colds[side]=buff;}
            for(unsigned n=0;n<10;++n){
                auto* item=make<Item>(battle,META_Gd__gd_core__CoreItem);item->f_ctx=V::from_obj(context);item->f_character_=V::from_obj(character);
                item->f__cooldown_active=V::from_bool(true);item->f__cooldown_blocked_epoch=V::from_int(-1);
                item->f_placed=V::from_bool(true);item->f_speedScale=V::from_float(n*0.05);
                item->f_triggerTime=V::from_float(1000000.0+n);item->f_iterationCooldown=V::from_float(1000000.0);
                item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(battle.arena,0));items.push_back(item);
            }
        }
    }
    void tick(bool candidate,unsigned frame,unsigned mode){
        const V delta=V::from_float(1.0/60.0);gd::NativeFrameSegmentSnapshot snapshot;
        for(unsigned side=0;side<2;++side){
            snapshot.clear();heats[side]->f_current=V::from_int((frame/64+side)%7);
            characters[side]->f_stunnedDuration=V::from_float(mode && frame%4==0?0.25:0.0);
            for(unsigned n=0;n<10;++n){auto* item=items[side*10+n];if(candidate)gd::native_frame_segment_tick(item,snapshot,delta);else(void)item->fn_physicsTick(&delta,1);}
        }
    }
    uint64_t hash()const{uint64_t h=1469598103934665603ULL;for(auto* item:items)h=(h^std::bit_cast<uint64_t>(item->f_triggerTime.f))*1099511628211ULL;return h;}
};
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 x=0;assert(QueryThreadCycleTime(GetCurrentThread(),&x));return x;}
struct Timing{double cpu_s,wall_s;uint64_t cycles,digest;int flags;};
static Timing bench(bool candidate,unsigned mode){
    Fixture fixture;for(unsigned i=0;i<1000;++i)fixture.tick(candidate,i,mode);
    std::feclearexcept(FE_ALL_EXCEPT);const auto c=cpu(),cy=cycles();const auto start=std::chrono::steady_clock::now();
    for(unsigned i=0;i<100000;++i)fixture.tick(candidate,i,mode);
    const auto wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();
    return{(cpu()-c)*1e-9,wall,cycles()-cy,fixture.hash(),std::fetestexcept(FE_ALL_EXCEPT)};
}
static void write(const Timing& t){std::cout<<"{\"cpu_s\":"<<t.cpu_s<<",\"wall_s\":"<<t.wall_s<<",\"cycles\":"<<t.cycles<<",\"digest\":"<<t.digest<<",\"flags\":"<<t.flags<<'}';}
int main(){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    std::cout<<"{\"scope\":\"persistent common-path item tick fixture; no whole-fight claim; original DLL call and local inline helper have different cross-module visibility\",\"calls_per_arm\":2000000,\"workloads\":[";
    for(unsigned mode=0;mode<2;++mode){if(mode)std::cout<<',';std::cout<<"{\"mode\":"<<mode<<",\"pairs\":[";
        for(unsigned p=0;p<8;++p){Timing a,b;if(p%2){b=bench(true,mode);a=bench(false,mode);}else{a=bench(false,mode);b=bench(true,mode);}assert(a.digest==b.digest && a.flags==b.flags);if(p)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}
        std::cout<<"]}";
    }
    std::cout<<"]}\n";
}

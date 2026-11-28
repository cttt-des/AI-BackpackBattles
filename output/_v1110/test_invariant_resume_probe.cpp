// Restricted no-callback mechanism: raw-input memoization plus sticky replay.
// This deliberately retains live field qualification; it is not a DLL patch.
#define main inherited_frame_fixture_main
#include "test_native_frame_segments.cpp"
#undef main
#include <windows.h>
#include <xmmintrin.h>
#include <chrono>
#include <iomanip>
using ActualTick=void (*)(Item*,gd::NativeFrameSegmentSnapshot&,const V&);
static ActualTick actual_tick;
struct Memo {bool valid=false;uint64_t scale=0,increment=0,delta=0;double decrement=0;unsigned flags=0;};
struct Scene {
    gd::BattleCtx battle{1u<<20};Context* ctx;Character* character;Buff *heat,*cold;
    std::vector<Item*> items;std::vector<Memo> memos;
    Scene() {
        battle.bind_battle(123);battle.native_resolved_dispatch=true;
        ctx=make<Context>(battle,META_Gd__gd_core__CoreContext);
        ctx->f_timer_pass_epoch=V::from_int(17);ctx->f_show_cooldown_progress=V::from_bool(false);
        character=make<Character>(battle,META_Gd__gd_core__CoreCharacter);
        character->f_stunnedDuration=V::from_float(0);
        character->f_buffs=V::from_dict(gd::GdDict::create(battle.arena));
        for(int64_t k=100;k<=110;++k){auto* b=make<Buff>(battle,META_Gd__gd_core__CoreBuff);b->f_current=V::from_int(0);character->f_buffs.dict->set(battle.arena,V::from_int(k),V::from_obj(b));if(k==107)heat=b;if(k==110)cold=b;}
        for(unsigned i=0;i<40;++i){auto* item=make<Item>(battle,META_Gd__gd_core__CoreItem);
            item->f_ctx=V::from_obj(ctx);item->f_character_=V::from_obj(character);item->f_placed=V::from_bool(true);
            item->f__cooldown_active=V::from_bool(true);item->f__cooldown_blocked_epoch=V::from_int(-1);
            item->f_triggerTime=V::from_float(1000000+i*.125);item->f_speedScale=V::from_float((int(i)%9-4)*.13);
            item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(battle.arena,5));item->f_statDisplayOverrides.arr->resize(battle.arena,5);
            items.push_back(item);memos.emplace_back();}
    }
    void reset(){for(unsigned i=0;i<items.size();++i){items[i]->f_triggerTime=V::from_float(1000000+i*.125);items[i]->f_speedScale=V::from_float((int(i)%9-4)*.13);}heat->f_current=V::from_int(0);cold->f_current=V::from_int(0);for(auto& m:memos)m.valid=false;}
};
__attribute__((noinline)) static double compute(double scale,double inc,double delta) {
    volatile double bonus=scale+inc;
    volatile double value=bonus>=0?1.0+bonus:1.0/(1.0-bonus);
    volatile double speed=value<.1?.1:value>10?10:value;
    return delta*speed;
}
__attribute__((noinline)) static void phase(Scene& s,bool memoized,const V& delta) {
    gd::NativeFrameSegmentSnapshot snapshot;
    const unsigned control=_mm_getcsr();
    if(!memoized || (control&~63u)!=0x1f80u){for(auto* p:s.items)actual_tick(p,snapshot,delta);return;}
    unsigned replay=0;
    // Fixture's exact owned graph has been proved once. No user callbacks occur
    // within this bounded phase; non-Null overrides and due items are excluded.
    for(unsigned i=0;i<s.items.size();++i){auto* p=s.items[i];auto& m=s.memos[i];
        const auto* display=p->f_statDisplayOverrides.arr;
        if(p->f__cooldown_active.kind!=V::Kind::Bool || !p->f__cooldown_active.b ||
           p->f_character_.obj!=s.character || p->f_ctx.obj!=s.ctx ||
           p->f_placed.kind!=V::Kind::Bool || !p->f_placed.b ||
           p->f_speedScale.kind!=V::Kind::Float || !display || display->len<=3 || !display->data[3].is_null() ||
           gd::native_scalar_truth(s.ctx->f_show_cooldown_progress)) {
            _mm_setcsr(_mm_getcsr()|replay);replay=0;m.valid=false;actual_tick(p,snapshot,delta);continue;
        }
        if(p->f__cooldown_blocked_epoch.as_int()==s.ctx->f_timer_pass_epoch.as_int() || snapshot.stunned(s.character,false))continue;
        const double inc=snapshot.speed_increment(s.character,false,[&]{return double(s.heat->f_current.as_int()-s.cold->f_current.as_int())*.02;});
        const uint64_t scale=bits(p->f_speedScale.f),increment=bits(inc),dt=bits(delta.f);
        if(!m.valid || m.scale!=scale || m.increment!=increment || m.delta!=dt){
            const auto old=_mm_getcsr();_mm_setcsr(old&~63u);
            const auto d=compute(p->f_speedScale.f,inc,delta.f);const auto f=_mm_getcsr()&63u;
            _mm_setcsr(old|f);m={true,scale,increment,dt,d,f};
        }
        replay|=m.flags;p->f_triggerTime=V::from_float(p->f_triggerTime.as_float()-m.decrement);
        if(p->f_triggerTime.f<=0)std::abort();
    }
    _mm_setcsr(_mm_getcsr()|replay);
}
static uint64_t signature(const Scene& s){uint64_t h=1469598103934665603ull;for(auto* p:s.items)h=(h^bits(p->f_triggerTime.f))*1099511628211ull;return h;}
static void mutate(Scene& s,unsigned frame,unsigned period){if(period && frame%period==0){s.heat->f_current=V::from_int((frame/period)%13);s.cold->f_current=V::from_int((frame/period)%5);s.items[(frame/period)%40]->f_speedScale=V::from_float(((int(frame/period)%13)-6)*.137);}}
__attribute__((noinline)) static void run(Scene& s,bool memo,unsigned frames,unsigned period){const auto d=V::from_float(.01666666753590107);for(unsigned n=0;n<frames;++n){mutate(s,n,period);phase(s,memo,d);}}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
int main(){register_gen_syms();auto mod=GetModuleHandleA("libgdcore.dll");assert(mod);actual_tick=reinterpret_cast<ActualTick>(GetProcAddress(mod,"_ZN2gd25native_frame_segment_tickEP21Gd__gd_core__CoreItemRNS_26NativeFrameSegmentSnapshotERKNS_5GdValE"));assert(actual_tick);
    const auto saved=_mm_getcsr();unsigned cases=0;
    for(unsigned mode=0;mode<16;++mode)for(unsigned period:{0u,1u,8u,128u}){Scene a,b;
        unsigned control=0x1f80u|((mode&3)<<13)|((mode&4)?0x40:0)|((mode&8)?0x8000:0);
        for(unsigned frame=0;frame<153;++frame){mutate(a,frame,period);mutate(b,frame,period);
            _mm_setcsr(control|(frame%2?0x10u:0));phase(a,false,V::from_float(.01666666753590107));const auto ca=_mm_getcsr();
            _mm_setcsr(control|(frame%2?0x10u:0));phase(b,true,V::from_float(.01666666753590107));const auto cb=_mm_getcsr();
            if(signature(a)!=signature(b)||ca!=cb){std::cerr<<"mismatch "<<mode<<' '<<period<<' '<<frame<<' '<<ca<<' '<<cb<<'\n';return 2;}++cases;}
    }
    _mm_setcsr(saved);std::cout<<std::setprecision(17)<<"{\"passed\":true,\"semantic_cases\":"<<cases<<",\"samples\":[";bool comma=false;
    for(unsigned period:{0u,1u,8u,128u}){Scene s;run(s,false,10000,period);s.reset();run(s,true,10000,period);
        for(unsigned q=0;q<4;++q){const char* pattern=q%2?"BAAB":"ABBA";for(unsigned arm=0;arm<4;++arm){s.reset();const auto c=cycles();const auto start=std::chrono::steady_clock::now();run(s,pattern[arm]=='B',100000,period);const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();const auto cy=cycles()-c;
            if(comma)std::cout<<',';comma=true;std::cout<<"{\"period\":"<<period<<",\"quad\":"<<q<<",\"arm\":"<<arm<<",\"label\":\""<<pattern[arm]<<"\",\"wall_s\":"<<elapsed<<",\"cycles\":"<<cy<<",\"signature\":"<<signature(s)<<'}';}}
    }std::cout<<"]}\n";
}

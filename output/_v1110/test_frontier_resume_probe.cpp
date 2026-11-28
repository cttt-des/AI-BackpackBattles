// Bounded observer model, not a game scheduler or a release performance test.
#include "native_inline_dispatch.hpp"
#include "native_array_index.hpp"
#include "exact_countdown_jump.hpp"
#include <xmmintrin.h>
#include <bit>
#include <cassert>
#include <iostream>
#include <vector>
#include <array>
using V=gd::GdVal;using Item=Gd__gd_core__CoreItem;
static uint64_t bits(double x){return std::bit_cast<uint64_t>(x);}
static double value(uint64_t x){return std::bit_cast<double>(x);}
static double sub(double x,double d){asm volatile("subsd %1,%0":"+x"(x):"x"(d));return x;}
struct Lane {uint64_t x,d;unsigned pending=0;};
struct Model {
    std::array<std::array<Lane,4>,2> lanes;
    bool lazy,in_original[2]{};uint64_t scans=0,jumps=0,scalar_steps=0,flags_writes=0;
    std::vector<uint64_t> trace;
    Model(bool mode):lazy(mode){for(unsigned s=0;s<2;++s)for(unsigned i=0;i<4;++i)lanes[s][i]={bits(96.0+i*.125+s),bits(.01666666753590107),0};}
    void materialize(unsigned side){if(in_original[side])return;for(auto& l:lanes[side])if(l.pending){exact_countdown::Result r;assert(exact_countdown::jump(l.x,l.d,l.pending,0x1f80,r));l.x=r.bits;l.pending=0;++jumps;}}
    void observe(unsigned id){materialize(0);materialize(1);trace.push_back(id);trace.push_back(_mm_getcsr());for(auto& side:lanes)for(auto l:side){assert(!l.pending);trace.push_back(l.x);}}
    void callback(unsigned side,unsigned frame,unsigned pattern){observe(1000+side*100+frame);
        // Mutations happen after old operands have been materialized. The
        // opposite side may already have completed the current frame.
        if(pattern&1)lanes[1-side][frame%4].d=bits((frame%3+1)*.01);
        if(pattern&2)_mm_setcsr(_mm_getcsr()&~63u);
        if(pattern&4){unsigned c=_mm_getcsr();_mm_setcsr((c&~0x6000u)|((frame%4)<<13));}
    }
    void phase(unsigned side,unsigned frame,unsigned pattern){
        const bool has_callback=frame%7==0;bool safe=lazy && !has_callback && (_mm_getcsr()&~63u)==0x1f80u;
        unsigned flags=0;
        if(safe)for(auto& l:lanes[side]){++scans;exact_countdown::Result r;if(!exact_countdown::jump(l.x,l.d,l.pending+1,0x1f80,r)){safe=false;break;}flags|=r.flags;}
        if(safe){for(auto& l:lanes[side])++l.pending;_mm_setcsr(_mm_getcsr()|flags);++flags_writes;return;}
        materialize(side);in_original[side]=true;
        for(unsigned i=0;i<4;++i){auto& l=lanes[side][i];l.x=bits(sub(value(l.x),value(l.d)));++scalar_steps;if(has_callback && i==frame%4)callback(side,frame,pattern);}
        in_original[side]=false;
    }
    void run(unsigned csr,unsigned pattern){_mm_setcsr(csr);for(unsigned frame=0;frame<96;++frame){
        if(frame%5==0){observe(frame*10);if(pattern&2)_mm_setcsr(_mm_getcsr()&~63u);}
        phase(0,frame,pattern);
        if(frame%3==0)callback(0,frame,pattern);
        phase(1,frame,pattern);
        if(frame%4==0)callback(1,frame,pattern);
    }observe(99999);}
};
int main(){register_gen_syms();const auto saved=_mm_getcsr();unsigned semantic_cases=0;uint64_t total_scans=0,total_jumps=0,total_scalar=0,total_flags=0;
    for(unsigned mode=0;mode<16;++mode)for(unsigned pattern=0;pattern<8;++pattern){const unsigned csr=0x1f80u|((mode&3)<<13)|((mode&4)?0x40:0)|((mode&8)?0x8000:0);Model a(false),b(true);a.run(csr,pattern);b.run(csr,pattern);assert(a.trace==b.trace);semantic_cases+=a.trace.size()/10;total_scans+=b.scans;total_jumps+=b.jumps;total_scalar+=b.scalar_steps;total_flags+=b.flags_writes;}
    _mm_setcsr(0x1f80);
    // Concrete current-DLL counterexamples to using structure/eligibility
    // versions as a complete numeric dependency certificate.
    gd::BattleCtx b(1u<<20);b.bind_battle(123);b.native_resolved_dispatch=true;
    auto* p=static_cast<Item*>(META_Gd__gd_core__CoreItem.alloc_fn(b));p->init_fields(b);
    auto& watch=b.native_timer_watch;watch.enabled=true;watch.closed_world=true;
    unsigned untracked=0;const auto verify=[&](auto operation){const auto a=watch.version,c=watch.cooldown_version;operation();assert(a==watch.version && c==watch.cooldown_version);++untracked;};
    verify([&]{assert(p->set_prop(b,SYM_GEN_speedScale_9,V::from_float(.5)));});
    verify([&]{assert(p->set_prop(b,SYM_GEN_placed_6,V::from_bool(false)));});
    verify([&]{assert(p->set_prop(b,SYM_GEN_triggerTime_38,V::from_float(80)));});
    p->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(b.arena,5));
    auto* arr=p->f_statDisplayOverrides.arr;arr->resize(b.arena,5);arr->timer_watch=&watch;
    verify([&]{arr->data[3]=V::from_float(1.75);});
    verify([&]{p->f_speedScale=V::from_float(.25);});
    // Held direct/resolved getters both see stale storage without a barrier.
    p->f_triggerTime=V::from_float(96);exact_countdown::Result r;assert(exact_countdown::jump(bits(96),bits(.01666666753590107),4,0x1f80,r));
    const auto direct=bits(p->f_triggerTime.f);const auto resolved=bits(gd::native_inline_get_prop(b,V::from_obj(p),SYM_GEN_triggerTime_38).as_float());assert(direct!=r.bits && resolved!=r.bits);
    // Replaying flags on read would re-raise an already cleared exception.
    _mm_setcsr(0x1f80);volatile double consumed=sub(96,.1);(void)consumed;assert(_mm_getcsr()&32);_mm_setcsr(0x1f80);const auto clear=_mm_getcsr();assert(exact_countdown::jump(bits(96),bits(.1),4,0x1f80,r));assert(_mm_getcsr()==clear && r.flags&32);
    _mm_setcsr(saved);
    std::cout<<"{\"passed\":true,\"semantic_cases\":"<<semantic_cases<<",\"model_scenarios\":128,\"untracked_numeric_writers\":"<<untracked<<",\"stale_direct_and_resolved_getters_exposed\":true,\"read_must_not_replay_old_cleared_flags\":true,\"lazy_model_counts\":{\"per_lane_frontier_scans\":"<<total_scans<<",\"materialization_jumps\":"<<total_jumps<<",\"scalar_steps\":"<<total_scalar<<",\"phase_flags_writes\":"<<total_flags<<"},\"model_is_not_a_full_game_observer_proof\":true}\n";
}

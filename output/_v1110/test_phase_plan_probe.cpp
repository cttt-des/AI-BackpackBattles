// Ideal no-callback phase cost probe, not a deployable replacement.
#define main inherited_frame_fixture_main
#include "test_native_frame_segments.cpp"
#undef main
#include <windows.h>
#include <xmmintrin.h>
#include <chrono>
#include <iomanip>

using ActualTick=void (*)(Item*,gd::NativeFrameSegmentSnapshot&,const V&);
static ActualTick actual_tick=nullptr;
struct Entry {Item* item;double* left;double* scale;bool override_used;double override_value;};
struct Scene {
    gd::BattleCtx battle{1u<<20};Context* ctx;Character* character;
    std::vector<Item*> items;std::vector<Entry> entries;
    explicit Scene(unsigned mode) {
        battle.bind_battle(123);battle.native_resolved_dispatch=true;
        ctx=make<Context>(battle,META_Gd__gd_core__CoreContext);
        ctx->f_timer_pass_epoch=V::from_int(17);ctx->f_show_cooldown_progress=V::from_bool(false);
        character=make<Character>(battle,META_Gd__gd_core__CoreCharacter);
        character->f_stunnedDuration=V::from_float(0.0);
        character->f_buffs=V::from_dict(gd::GdDict::create(battle.arena));
        for(int64_t key=100;key<=110;++key) {
            auto* b=make<Buff>(battle,META_Gd__gd_core__CoreBuff);b->f_current=V::from_int(key==107?int(mode):0);
            character->f_buffs.dict->set(battle.arena,V::from_int(key),V::from_obj(b));
        }
        for(unsigned i=0;i<40;++i) {
            auto* item=make<Item>(battle,META_Gd__gd_core__CoreItem);
            item->f_ctx=V::from_obj(ctx);item->f_character_=V::from_obj(character);
            item->f_placed=V::from_bool(true);item->f__cooldown_active=V::from_bool(true);
            item->f__cooldown_blocked_epoch=V::from_int(-1);
            item->f_triggerTime=V::from_float(1000000.0+i*0.125);
            item->f_speedScale=V::from_float(mode==0?0.0:(int(i)%9-4)*0.13);
            item->f_statDisplayOverrides=V::from_arr(gd::GdArr::create(battle.arena,5));
            item->f_statDisplayOverrides.arr->resize(battle.arena,5);
            if(mode==2 && i%5==0)item->f_statDisplayOverrides.arr->data[3]=V::from_float(1.75);
            items.push_back(item);
        }
        build();
    }
    __attribute__((noinline)) void build() {
        entries.clear();entries.reserve(items.size());
        for(auto* item:items) {
            assert(item->native_call_row_ && item->native_call_row_->metadata);
            assert(item->f_ctx.obj==ctx && item->f_character_.obj==character);
            assert(item->f_placed.kind==V::Kind::Bool && item->f_placed.b);
            assert(item->f_triggerTime.kind==V::Kind::Float && item->f_speedScale.kind==V::Kind::Float);
            const auto v=item->f_statDisplayOverrides.arr->data[3];
            assert(v.is_null() || v.kind==V::Kind::Float);
            const bool used=!v.is_null() && v.f!=0.0;
            entries.push_back({item,&item->f_triggerTime.f,&item->f_speedScale.f,used,used?v.f:0.0});
        }
    }
    void reset(){for(unsigned i=0;i<items.size();++i)items[i]->f_triggerTime=V::from_float(1000000.0+i*0.125);}
};

__attribute__((noinline)) static void baseline(Scene& s,unsigned frames) {
    const auto delta=V::from_float(0.01666666753590107);
    for(unsigned n=0;n<frames;++n){gd::NativeFrameSegmentSnapshot snapshot;for(auto* item:s.items)actual_tick(item,snapshot,delta);}
}
__attribute__((noinline)) static void fused(Scene& s,unsigned frames) {
    for(unsigned n=0;n<frames;++n) {
        // Graph and numeric-shape proof is intentionally idealized outside this
        // interval. A real phase needs invalidation and a live suffix fallback.
        const auto* b=s.character->f_buffs.dict;
        const auto heat=static_cast<const Buff*>(b->entries[7].val.obj)->f_current.i;
        const auto cold=static_cast<const Buff*>(b->entries[10].val.obj)->f_current.i;
        const double bonus=static_cast<double>(heat-cold)*0.02;
        for(const auto& entry:s.entries) {
            double speed=entry.override_value;
            if(!entry.override_used) {
                const auto v=*entry.scale+bonus;const auto m=v>=0.0?1.0+v:1.0/(1.0-v);
                speed=m<0.1?0.1:m>10.0?10.0:m;
            }
            *entry.left=*entry.left-0.01666666753590107*speed;
        }
    }
}
static uint64_t signature(const Scene& s) {
    uint64_t h=1469598103934665603ull;
    for(auto* item:s.items)h=(h^bits(item->f_triggerTime.f))*1099511628211ull;
    return h;
}
static uint64_t cycles(){ULONG64 n=0;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
int main() {
    register_gen_syms();auto module=GetModuleHandleA("libgdcore.dll");assert(module);
    actual_tick=reinterpret_cast<ActualTick>(GetProcAddress(module,"_ZN2gd25native_frame_segment_tickEP21Gd__gd_core__CoreItemRNS_26NativeFrameSegmentSnapshotERKNS_5GdValE"));assert(actual_tick);
    fenv_t saved;std::fegetenv(&saved);const auto csr=_mm_getcsr();unsigned cases=0;
    const int rounds[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};
    for(unsigned mode=0;mode<3;++mode) {
        Scene a(mode),b(mode);
        for(auto rounding:rounds)for(unsigned ftz=0;ftz<4;++ftz) {
            a.reset();b.reset();assert(std::fesetround(rounding)==0);
            const auto control=(_mm_getcsr()&~(0x8040u|0x3fu))|((ftz&1)?0x40u:0)|((ftz&2)?0x8000u:0);
            _mm_setcsr(control);std::feclearexcept(FE_ALL_EXCEPT);baseline(a,19);
            const auto af=std::fetestexcept(FE_ALL_EXCEPT);const auto ac=_mm_getcsr();
            _mm_setcsr(control);std::feclearexcept(FE_ALL_EXCEPT);fused(b,19);
            const auto bf=std::fetestexcept(FE_ALL_EXCEPT);const auto bc=_mm_getcsr();
            if(signature(a)!=signature(b)||af!=bf||ac!=bc){std::cerr<<"mismatch "<<mode<<' '<<rounding<<' '<<ftz<<' '<<af<<' '<<bf<<'\n';return 2;}
            ++cases;
        }
    }
    std::fesetenv(&saved);_mm_setcsr(csr);
    std::cout<<std::setprecision(17)<<"{\"semantic_cases\":"<<cases<<",\"no_callback_ideal_probe_only\":true,\"samples\":[";
    bool comma=false;
    for(unsigned mode=0;mode<3;++mode) {
        Scene scene(mode);baseline(scene,10000);scene.reset();fused(scene,10000);
        for(unsigned quad=0;quad<4;++quad) {
            const char* pattern=quad%2?"BAAB":"ABBA";
            for(unsigned arm=0;arm<4;++arm) {
                scene.reset();const auto c=cycles();const auto start=std::chrono::steady_clock::now();
                if(pattern[arm]=='A')baseline(scene,100000);else fused(scene,100000);
                const auto end=std::chrono::steady_clock::now();const auto spent=cycles()-c;
                if(comma)std::cout<<',';comma=true;
                std::cout<<"{\"mode\":"<<mode<<",\"quad\":"<<quad<<",\"arm\":"<<arm<<",\"label\":\""<<pattern[arm]<<"\",\"wall_s\":"<<std::chrono::duration<double>(end-start).count()<<",\"thread_cycles\":"<<spent<<",\"signature\":"<<signature(scene)<<"}";
            }
        }
    }
    std::cout<<"],\"build_samples\":[";
    Scene scene(1);
    for(unsigned i=0;i<5;++i) {
        const auto start=std::chrono::steady_clock::now();for(unsigned n=0;n<100000;++n)scene.build();
        if(i)std::cout<<',';std::cout<<std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count()/100000.0;
    }
    std::cout<<"]}\n";
}

#include "native_inline_dispatch.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <iostream>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;
extern "C" void gd_init_all_classes();
extern "C" uint64_t gd_diag_native_hot_slot_stat(unsigned);

constexpr std::array<gd::SymId,16> methods={
    SYM_GEN_attack_941,SYM_GEN_useMana_332,SYM_GEN_cleanseRandomDebuffs_356,
    SYM_GEN_giveMaxHealth_317,SYM_GEN_giveLucky_215,SYM_GEN_giveMostBuffs_367,
    SYM_GEN_onPreDealDamage_early_945,SYM_GEN_onPrepare_123,SYM_GEN_changeChargedItemStat_326,
    SYM_GEN_onChargeEnteredCell_2059,SYM_GEN_emitCharge_2058,SYM_GEN_giveSpikes_209,
    SYM_GEN_chargeReceived_324,SYM_GEN_onChargeReceived_2129,SYM_GEN_giveRandomBuffs_369,
    SYM_GEN_combatEndDeferred_1335};

bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    if(a.kind==V::Kind::Float)return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
    if(a.kind==V::Kind::Vec2)return std::bit_cast<uint64_t>(a.v2.x)==std::bit_cast<uint64_t>(b.v2.x) && std::bit_cast<uint64_t>(a.v2.y)==std::bit_cast<uint64_t>(b.v2.y);
    return gd::gd_eq(a,b);
}

struct Unknown:Item {
    mutable unsigned metadata_reads=0;
    unsigned calls=0,argc_seen=0;
    bool handled=true,saw_cached=false;
    V seen;
    explicit Unknown(gd::BattleCtx* ctx):Item(ctx){}
    const gd::GdClassMeta* meta() const override{++metadata_reads;return Item::meta();}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out) override{
        bool selected=false;for(auto symbol:methods)selected|=method==symbol;
        if(!selected)return Item::call_method(ctx,method,args,argc,out);
        ++calls;argc_seen=argc;saw_cached=native_call_row_!=nullptr;
        assert(argc==1 || argc==3);seen=args[0];
        if(argc==3)assert(args[1].kind==V::Kind::Int && args[1].i==73 && args[2].kind==V::Kind::Bool && args[2].b);
        ctx.math_rng.randf();
        // Expose an extra cache write as an actual RNG divergence.
        if(saw_cached)ctx.math_rng.randf();
        out=args[0];return handled;
    }
};

int main(){
    gd_init_all_classes();
    for(unsigned i=0;i<methods.size();++i)assert(gd::native_resolved_slots[methods[i]]==112+int(i));
    gd::BattleCtx slow,fast;slow.bind_battle(17);fast.bind_battle(17);
    fast.native_resolved_dispatch=true;fast.native_resolved_collect=true;fast.native_resolved_audit=true;
    const V payloads[]={V::null(),V::from_int((INT64_C(1)<<53)+3),V::from_bool(true),
        V::from_float(-0.0),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234))),
        V::from_str(gd::make_static_str("new_slot_payload")),V::from_vec2(1.25,-0.0)};
    unsigned checks=0;
    for(auto method:methods)for(const auto& payload:payloads)for(bool handled:{false,true})for(bool cached:{false,true}){
        Unknown a(&slow),b(&fast);a.handled=b.handled=handled;
        if(cached){
            // An older selected slot already cached an unsupported exact type.
            (void)gd::native_inline_call(fast,V::from_obj(&b),SYM_GEN_character_74,nullptr,0);
            assert(b.native_call_row_);a.native_call_row_=b.native_call_row_;
        }
        const auto* before_a=a.native_call_row_;const auto* before_b=b.native_call_row_;
        for(unsigned route=0;route<3;++route){
            const auto first_a=a.calls,first_b=b.calls,meta_a=a.metadata_reads,meta_b=b.metadata_reads;
            V x,y;
            if(route==0){
                x=gd::call_method(slow,V::from_obj(&a),method,&payload,1);
                y=gd::native_inline_call(fast,V::from_obj(&b),method,&payload,1);
            }else{
                auto* binds_a=gd::GdArr::create(slow.arena);auto* binds_b=gd::GdArr::create(fast.arena);
                for(const auto& value:{V::from_int(73),V::from_bool(true)}){binds_a->push_back(slow.arena,value);binds_b->push_back(fast.arena,value);}
                gd::GdFuncRef old_ref{&a,method,binds_a},new_ref{&b,method,binds_b};
                if(route==1){x=old_ref.call_func(slow,&payload,1);y=new_ref.call_func(fast,&payload,1);}
                else{
                    auto* aa=gd::GdArr::create(slow.arena);auto* ab=gd::GdArr::create(fast.arena);
                    aa->push_back(slow.arena,payload);ab->push_back(fast.arena,payload);
                    x=old_ref.call_funcv(slow,V::from_arr(aa));y=new_ref.call_funcv(fast,V::from_arr(ab));
                }
            }
            assert(same(x,y) && same(a.seen,payload) && same(b.seen,payload));
            assert(a.calls==first_a+1 && b.calls==first_b+1 && a.argc_seen==b.argc_seen);
            assert(a.saw_cached==cached && b.saw_cached==cached);
            assert(a.native_call_row_==before_a && b.native_call_row_==before_b);
            assert(a.metadata_reads-meta_a==b.metadata_reads-meta_b);
            assert(slow.math_rng.pcg.state==fast.math_rng.pcg.state && slow.math_rng.pcg.inc==fast.math_rng.pcg.inc);
            ++checks;
        }
    }
    const auto hits=gd_diag_native_hot_slot_stat(0);
    auto* known=META_Gd__gd_core__CoreItem.alloc_fn(fast);known->init_fields(fast);
    V expected;assert(known->call_method(fast,SYM_GEN_onPrepare_123,nullptr,0,expected));
    assert(same(expected,gd::native_inline_call(fast,V::from_obj(known),SYM_GEN_onPrepare_123,nullptr,0)));
    assert(gd_diag_native_hot_slot_stat(0)==hits+1);
    known->native_call_row_=reinterpret_cast<const gd::NativeMethodRow*>(uintptr_t(1));
    assert(gd::native_inline_call(fast,V::from_obj(known),SYM_GEN_onPrepare_123,nullptr,0).is_null());
    assert(fast.native_resolved_counts[4]==1);
    std::cout<<"{\"new_method_symbols\":16,\"unknown_receiver_payload_rng_bind_cases\":"<<checks
        <<",\"null_and_existing_cache_preserved\":true,\"generated_fast_path_and_bad_row_audit\":true}\n";
}

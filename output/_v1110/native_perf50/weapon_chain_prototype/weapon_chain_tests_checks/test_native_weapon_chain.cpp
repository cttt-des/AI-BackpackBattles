#include "weapon_fixture_base.cpp"

static uint64_t override_calls=0,override_trace=0;
static V next_source;
static V override_status(gd::GdObj*,const V* args,int argc){
    ++override_calls;override_trace=mix(override_trace,uint64_t(argc));
    for(int i=0;i<argc;++i)override_trace=mix(override_trace,hash(args[i]));
    return V::from_int(7);
}
static V override_character(gd::GdObj* raw,const V*,int argc){
    ++override_calls;override_trace=mix(override_trace,uint64_t(argc));
    auto* item=static_cast<Item*>(raw);item->f_damageSource=next_source;
    return item->f_character_;
}

static uint64_t whole_case(unsigned phase,unsigned scenario,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);_mm_setcsr(_mm_getcsr()&~(0x8040u|0x3fu));
    ExtendedFixture f(scenario,true);override_calls=0;override_trace=1469598103934665603ULL;next_source=V::from_obj(f.alternate);
    Item* active=f.weapon;
    if(phase>=6){
        auto* other=static_cast<Gd__gd_core_items__Weapon*>(gd::construct_class(f.c,&META_Gd__gd_core_items__Weapon,nullptr,0).obj);
        std::vector<V> fields;visit_damage_fields(static_cast<Item&>(*f.weapon),[&](const V& v){fields.push_back(v);});
        size_t at=0;visit_damage_fields(static_cast<Item&>(*other),[&](V& v){v=fields.at(at++);});assert(at==fields.size());active=other;
    }
    auto* data=static_cast<Gd__gd_core__CoreItemData*>(active->f_descriptor.obj);
    data->f_identifier=V::from_cstr(f.c.arena,"ChainFixture");data->f_name=data->f_identifier;
    data->f_minDam=V::from_int(4);data->f_maxDam=V::from_int(8);data->f_staminaCost=V::from_float(1.5);
    data->f_accuracy=V::from_float(87.5);data->f_canActivate=V::from_bool(true);data->f_cd=V::from_float(1.0);
    data->f_types=V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(0)}));
    active->f_damageSource=V::from_obj(f.source);f.source->f_origin=V::from_obj(active);
    f.attacker->f_curStamina=V::from_float(scenario%3==0?0.0:scenario%3==1?1.5:8.0);
    f.attacker->f_baseMaxStamina=V::from_float(10.0);
    auto dummy=gd::construct_class(f.c,&META_Gd__gd_core__CoreDamageResult,nullptr,0);
    Callback capture(&f.c);V captured=dummy;
    capture.action=[&](const V* args,int argc){if(argc>0 && args[0].kind==V::Kind::Obj && dynamic_cast<Result*>(args[0].obj))captured=args[0];};
    const V connection[]={V::from_obj(f.defender),V::from_cstr(f.c.arena,"character_damaged"),V::from_obj(&capture),V::from_cstr(f.c.arena,"damage_record_callback")};
    static_cast<Bus*>(f.ctx->f_bus.obj)->fn_connectEvent(connection,4);
    if(scenario>=16 && phase!=2)f.callbacks(scenario%16);
    gd::NativeMethodRow copied{};
    const unsigned row_mode=scenario%8;
    if(row_mode==1)active->native_call_row_=nullptr;
    else if(row_mode>=2){
        copied=*active->native_call_row_;active->native_call_row_=&copied;
        if(row_mode==3)copied.methods[gd::native_resolved_slots[SYM_GEN_useStamina_116]]=&override_status;
        if(row_mode==4)copied.methods[gd::native_resolved_slots[SYM_GEN_attack_941]]=&override_status;
        if(row_mode==5)copied.methods[gd::native_resolved_slots[SYM_GEN_dealDamage_220]]=&override_status;
        if(row_mode==7)copied.methods[gd::native_resolved_slots[SYM_GEN_character_74]]=&override_character;
    }
    if(row_mode==6)f.attacker->native_call_row_=f.defender->native_call_row_=nullptr;
    f.c.native_event_kernel=config<3;f.c.native_event_audit=config!=1;
    f.c.native_resolved_dispatch=config!=2;f.c.native_resolved_audit=config!=1;f.c.native_resolved_collect=true;
    f.c.native_timer_watch.closed_world=chain_closed;
    const V source=f.initial,event=f.parent,amount=boundary_value(f,scenario%18);
    std::vector<uint64_t> before;for(auto [stat,count]:legacy_counters)for(unsigned i=0;i<count;++i)before.push_back(stat(i));
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|chain_daz|4u);
    V result;
    switch(phase){
        case 0:{const V args[]={source,event};result=f.defender->fn_takeDamage(args,2);break;}
        case 1:{const V args[]={source,event};result=gd::native_inline_call(f.c,V::from_obj(f.attacker),SYM_GEN_dealDamage_220,args,2);break;}
        case 2:result=gd::native_inline_call(f.c,V::from_obj(f.attacker),SYM_GEN_useStamina_116,&amount,1);break;
        case 3:result=gd::native_inline_call(f.c,V::from_obj(active),SYM_GEN_dealDamage_220,&event,1);break;
        case 4:case 6:result=gd::native_inline_call(f.c,V::from_obj(active),SYM_GEN_attack_941,&event,1);break;
        default:result=gd::native_inline_call(f.c,V::from_obj(active),SYM_GEN_doCooldownEffect_144,nullptr,0);break;
    }
    const int flags=std::fetestexcept(FE_ALL_EXCEPT);const unsigned csr=_mm_getcsr();
    if(result.kind==V::Kind::Obj && dynamic_cast<Result*>(result.obj))captured=result;
    uint64_t h=mix(mix(f.state(captured,flags),csr),hash(result));
    visit_damage_fields(*active,[&](const V& v){h=mix(h,hash(v));});
    h=mix(mix(mix(h,override_calls),override_trace),capture.calls);
    const auto& watch=f.c.native_timer_watch;h=mix(mix(mix(mix(mix(h,watch.version),watch.cooldown_version),watch.depth),watch.usable),watch.closed_world);
    latest_legacy_hash=1469598103934665603ULL;unsigned index=0;
    for(auto [stat,count]:legacy_counters)for(unsigned i=0;i<count;++i){latest_legacy_hash=mix(latest_legacy_hash,stat(i)-before[index]);++index;}
    return h;
}

int main(){
    register_gen_syms();fenv_t saved;std::fegetenv(&saved);unsigned saved_csr=_mm_getcsr();
    std::vector<uint64_t> hashes,legacy_hashes;uint64_t retained=0,whole=0;
    auto check=[&](unsigned family,unsigned scenario,unsigned config,int rounding){hashes.push_back(extended_case(false,family,scenario,config,rounding));legacy_hashes.push_back(latest_legacy_hash);++retained;};
    for(bool closed:{false,true})for(unsigned denorm:{0u,0x40u,0x8000u,0x8040u}){
        chain_closed=closed;chain_daz=denorm;
        for(unsigned family=0;family<4;++family){const unsigned limit=family<2?448:family==2?16:144;
            for(unsigned scenario=0;scenario<limit;++scenario)for(unsigned config=0;config<3;++config)
            for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})check(family,scenario,config,rounding);
        }
        for(unsigned config:{3u,4u})for(unsigned scenario=0;scenario<16;++scenario)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})check(1,scenario,config,rounding);
        for(unsigned family:{4u,5u})for(unsigned scenario=0;scenario<(family==4?8u:2u);++scenario)for(unsigned config=0;config<3;++config)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})check(family,scenario,config,rounding);
        for(unsigned phase=0;phase<8;++phase)for(unsigned scenario=0;scenario<32;++scenario)for(unsigned config=0;config<4;++config)
        for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){hashes.push_back(whole_case(phase,scenario,config,rounding));legacy_hashes.push_back(latest_legacy_hash);++whole;}
    }
    std::fesetenv(&saved);_mm_setcsr(saved_csr);assert(retained==103360 && whole==32768);
    std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"retained_damage_cases\":"<<retained<<",\"whole_chain_cases\":"<<whole<<",\"case_hashes\":[";
    for(size_t i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}
    std::cout<<"],\"legacy_counter_hashes\":[";for(size_t i=0;i<legacy_hashes.size();++i){if(i)std::cout<<',';std::cout<<legacy_hashes[i];}
    std::cout<<"],\"all16_fp_modes_open_and_closed_contexts\":true}";
}

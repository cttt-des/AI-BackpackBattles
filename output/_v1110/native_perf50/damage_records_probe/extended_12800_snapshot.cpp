// Preserve the preliminary reference and reuse its independently built fixture.
#include "damage_fixture.hpp"
#include "gen/hdrs/Gd__gd_core__Weapon.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "damage_state_fields.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <vector>
using Weapon=Gd__gd_core__Weapon;
using Bus=Gd__gd_core__CoreEventBus;
static V invoke_damage(bool candidate,Character& target,const V* args,int argc){
#ifdef GD_DAMAGE_PRODUCTION
    candidate=false;
#endif
    return candidate?candidate_takeDamage(target,args,argc):target.fn_takeDamage(args,argc);
}
static uint64_t object_fields(gd::GdObj* object){
    uint64_t h=hash(V::from_obj(object));auto add=[&](const V& v){h=mix(h,hash(v));};
    if(auto* x=dynamic_cast<Result*>(object))visit_damage_fields(*x,add);
    else if(auto* x=dynamic_cast<Source*>(object))visit_damage_fields(*x,add);
    else if(auto* x=dynamic_cast<Gd__gd_core__CoreEvent*>(object))visit_damage_fields(*x,add);
    return h;
}
static const gd::GdClassMeta callback_meta{65000,"DamageRecordCallback"};
struct Callback:gd::GdObj {
    std::function<void(const V*,int)> action;unsigned calls=0;
    explicit Callback(gd::BattleCtx* c):GdObj(c){}
    const gd::GdClassMeta* meta()const override{return &callback_meta;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override{
        if(method!=gd::intern_sym("damage_record_callback"))return false;
        ++calls;action(args,argc);out=V::null();return true;
    }
};
static uint64_t input_seed=42;
struct ExtendedFixture:Fixture {
    Weapon* weapon;Source* alternate;Callback first{&c},second{&c},third{&c};
    std::vector<uint64_t> trace;bool candidate=false,busy=false,modified=false;unsigned action=0;V initial,parent;
    ExtendedFixture(unsigned scenario,bool item):Fixture(scenario){
        auto* descriptor=gd::construct_class(c,&META_Gd__gd_core__CoreItemData,nullptr,0).obj;
        weapon=static_cast<Weapon*>(gd::construct_class(c,&META_Gd__gd_core__Weapon,nullptr,0).obj);
        weapon->f_ctx=V::from_obj(ctx);weapon->f_character_=V::from_obj(attacker);weapon->f_descriptor=V::from_obj(descriptor);weapon->f_ownerType=V::from_int(2);
        weapon->f_critSeverity=V::from_float(2.0);weapon->f_doubleAttackEffectChance=V::from_float(scenario%3==0?100:0);
        weapon->f_hasPreDealDamageEarlyEffect=weapon->f_hasPreDealDamageLateEffect=weapon->f_hasDealtDamageEffect=V::from_bool(false);
        source->f_origin=item?V::from_obj(weapon):V::null();
        alternate=static_cast<Source*>(gd::construct_class(c,&META_Gd__gd_core__CoreDamageSource,nullptr,0).obj);
        alternate->f_types=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(2)}));alternate->f_flags=V::from_int(0);
        V event_args[]={V::from_int(700),V::from_float(1.25),V::null(),V::from_obj(attacker),V::from_int(0)};
        parent=gd::construct_class(c,&META_Gd__gd_core__CoreEvent,event_args,5);initial=V::from_obj(source);
    }
    void connect(Callback& callback,unsigned signal_index){
        V args[]={V::from_obj(defender),V::from_str(&battle_string_literals[signal_index]),V::from_obj(&callback),V::from_cstr(c.arena,"damage_record_callback")};
        static_cast<Bus*>(ctx->f_bus.obj)->fn_connectEvent(args,4);
    }
    void callbacks(unsigned variant){
        action=variant;defender->f_isDead=defender->f_invulnerable=V::from_bool(false);
        source->f_accuracy=V::from_float(100);source->f_flags=V::from_int(63);source->f_types=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(0)}));
        first.action=[&](const V* args,int argc){
            trace.push_back(mix(1,argc));for(int i=0;i<argc;++i)trace.push_back(args[i].kind==V::Kind::Obj?object_fields(args[i].obj):hash(args[i]));
            auto* result=argc>0 && args[0].kind==V::Kind::Obj?dynamic_cast<Result*>(args[0].obj):nullptr;
            if(!result || busy || modified)return;modified=true;
            if(action==1)result->f_damage=V::from_int(31);
            if(action==2)result->f_damageReduction=V::from_int(7);
            if(action==3)result->f_damage=V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234)));
            if(action==4)result->f_damageSource=V::from_obj(alternate);
            if(action==5)result->f_hit=V::from_bool(false);
            if(action==6){auto* s=static_cast<Source*>(result->f_damageSource.obj);s->f_types.arr->push_back(c.arena,V::from_int(5));s->f_flags=V::from_int(0);}
            if(action==7)connect(third,19);
            if(action==8){V idargs[]={V::from_obj(defender),gd::get_index(c,static_cast<Bus*>(ctx->f_bus.obj)->f_signalIDs,V::from_str(&battle_string_literals[19]))};auto id=static_cast<Bus*>(ctx->f_bus.obj)->fn_getEmissionID(idargs,2);auto list=gd::get_index(c,static_cast<Bus*>(ctx->f_bus.obj)->f_connections,id);auto pair=list.arr->data[1];pair.arr->data[0].fr->binds=gd::GdArr::from_init(c.arena,{V::from_int(991)});}
            if(action==9){busy=true;V nested[]={V::from_obj(alternate),parent};trace.push_back(object_fields(invoke_damage(candidate,*defender,nested,2).obj));busy=false;}
            if(action==10)ctx->f_fight_ended=V::from_bool(true);
            if(action==11)result->f_damageSource=V::null();
            if(action==12)result->f_healthDamage=V::from_int(79);
            if(action==13){result->f_damageReduction=V::from_float(-1.25);defender->f_damageResistance=V::from_float(25.0);}
            if(action==14)result->f_event=parent;
            if(action==15){defender->f_invulnerable=V::from_bool(true);result->f_damage=V::from_float(-0.0);}
        };
        second.action=[&](const V* args,int argc){trace.push_back(mix(2,argc));for(int i=0;i<argc;++i)trace.push_back(args[i].kind==V::Kind::Obj?object_fields(args[i].obj):hash(args[i]));};
        third.action=[&](const V*,int argc){trace.push_back(mix(3,argc));};
        for(unsigned signal:{19u,21u,27u,28u}){connect(first,signal);connect(second,signal);}
    }
    uint64_t state(const V& value,int flags){
        uint64_t h=mix(object_fields(value.obj),flags);auto add=[&](const V& v){h=mix(h,hash(v));};
        auto* r=static_cast<Result*>(value.obj);
        if(r->f_damageSource.kind==V::Kind::Obj)h=mix(h,object_fields(r->f_damageSource.obj));
        if(r->f_event.kind==V::Kind::Obj)h=mix(h,object_fields(r->f_event.obj));
        visit_damage_fields(*ctx,add);visit_damage_fields(*attacker,add);visit_damage_fields(*defender,add);visit_damage_fields(*source,add);visit_damage_fields(*weapon,add);
        visit_damage_fields(*static_cast<Bus*>(ctx->f_bus.obj),add);visit_damage_fields(*static_cast<Gd__gd_core__CoreCombatLog*>(ctx->f_combat_log.obj),add);
        for(auto* character:{attacker,defender}){
            for(unsigned i=0;i<character->f_buffs.dict->len;++i){auto* buff=static_cast<Gd__gd_core__CoreBuff*>(character->f_buffs.dict->entries[i].val.obj);visit_damage_fields(*buff,add);}
            for(auto rng_value:{character->f_accuracyRng,character->f_critRng,character->f_critResistanceRng,character->f_stunResistanceRng})visit_damage_fields(*static_cast<Gd__gd_core__CoreRng__INNER__BalancedRng*>(rng_value.obj),add);
        }
        auto* rng=static_cast<Gd__gd_core__CoreRng*>(ctx->f_rng.obj)->f_rng.rng;h=mix(mix(h,rng->pcg.state),rng->pcg.inc);h=mix(mix(h,c.math_rng.pcg.state),c.math_rng.pcg.inc);
        for(auto n:c.native_event_counts)h=mix(h,n);for(auto n:c.native_resolved_counts)h=mix(h,n);
        for(auto x:trace)h=mix(h,x);h=mix(h,first.calls);h=mix(h,second.calls);h=mix(h,third.calls);h=mix(h,c.next_gid);
        if(auto* copy=dynamic_cast<Source*>(r->f_damageSource.kind==V::Kind::Obj?r->f_damageSource.obj:nullptr)){h=mix(h,copy!=source);if(copy->f_types.kind==V::Kind::Arr && source->f_types.kind==V::Kind::Arr)h=mix(h,copy->f_types.arr!=source->f_types.arr);}
        return h;
    }
};
static V boundary_value(ExtendedFixture& f,unsigned kind){
    const uint64_t bits[]={0,UINT64_C(0x8000000000000000),UINT64_C(1),UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0xfff8000000004321),UINT64_C(0x7ff0000000001234)};
    if(kind<8)return V::from_float(std::bit_cast<double>(bits[kind]));
    switch(kind){case 8:return V::null();case 9:return V::from_int(INT64_MIN);case 10:return V::from_int(INT64_MAX);case 11:return V::from_bool(false);case 12:return V::from_bool(true);case 13:return V::from_str(gd::make_static_str("12.5"));case 14:return V::from_arr(gd::GdArr::from_init(f.c.arena,{V::from_int(2)}));case 15:return V::from_dict(gd::GdDict::create(f.c.arena));case 16:return V::from_vec2(-0.0,1.25);default:return V::from_obj(f.weapon);}
}
static uint64_t extended_case(bool candidate,unsigned family,unsigned scenario,unsigned config,int rounding){
    // Both arms construct their fixtures under the same environment. A prior
    // arm's requested rounding must not leak into the next arm's setup.
    assert(std::fesetround(FE_TONEAREST)==0);
    ExtendedFixture f(scenario,family==1 || family==2);f.candidate=candidate;
    if(family==2)f.callbacks(scenario);
    if(family==3){f.defender->f_isDead=V::from_bool(true);const V value=boundary_value(f,scenario%18);switch(scenario/18){case 0:f.source->f_minDamage=value;break;case 1:f.source->f_maxDamage=value;break;case 2:f.source->f_accuracy=value;break;case 3:f.source->f_critChancePercent=value;break;case 4:f.source->f_flags=value;break;case 5:f.source->f_types=value;break;case 6:f.source->f_origin=value;break;default:f.initial=value;}}
    f.c.native_event_kernel=config<3;f.c.native_event_audit=config!=1;f.c.native_resolved_audit=config!=1;f.c.native_resolved_dispatch=config!=2 && config!=4;f.c.native_resolved_collect=true;
    V args[]={f.initial,f.parent};assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    const V result=invoke_damage(candidate,*f.defender,args,2);const int flags=std::fetestexcept(FE_ALL_EXCEPT);return f.state(result,flags);
}
static uint64_t stamp(FILETIME x){return(uint64_t{x.dwHighDateTime}<<32)|x.dwLowDateTime;}
static uint64_t cpu(){FILETIME a,b,c,d;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&c,&d));return(stamp(c)+stamp(d))*100;}
static uint64_t cycles(){ULONG64 n;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
struct DamageTiming{double cpu_s,wall_s;uint64_t cycle_count,digest;};static volatile uint64_t damage_sink;
static DamageTiming bench(bool candidate,bool item,unsigned count){
    ExtendedFixture f(63,item);f.candidate=candidate;f.c.native_event_audit=false;f.c.native_resolved_audit=false;f.c.native_resolved_collect=false;
    f.defender->f_isDead=f.defender->f_invulnerable=V::from_bool(false);f.defender->f_dodgeStacks=V::from_int(0);f.defender->f_curHealth=V::from_float(1e12);
    V args[]={f.initial,f.parent};for(unsigned i=0;i<32;++i)(void)invoke_damage(candidate,*f.defender,args,2);
    const auto before=cpu(),cy=cycles();const auto start=std::chrono::steady_clock::now();uint64_t h=0;V last_result;
    for(unsigned i=0;i<count;++i){last_result=invoke_damage(candidate,*f.defender,args,2);h=mix(h,hash(static_cast<Result*>(last_result.obj)->f_damage));}
    const double wall=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();const auto used=cpu()-before,used_cycles=cycles()-cy;damage_sink=h;
    h=mix(h,f.state(last_result,0));
    return{used*1e-9,wall,used_cycles,h};
}
static void write(const DamageTiming& x){std::cout<<"{\"cpu_s\":"<<x.cpu_s<<",\"wall_s\":"<<x.wall_s<<",\"cycles\":"<<x.cycle_count<<",\"digest\":"<<x.digest<<'}';}
int main(int argc,char** argv){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));std::vector<uint64_t> hashes;
    const bool screen=argc>1 && std::string(argv[1])=="--screen";
    if(!screen){for(unsigned family=0;family<4;++family){const unsigned limit=family<2?448:family==2?16:144;for(unsigned scenario=0;scenario<limit;++scenario)for(unsigned config=0;config<3;++config)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        const auto a=extended_case(false,family,scenario,config,rounding),b=extended_case(true,family,scenario,config,rounding);if(a!=b){std::cerr<<"mismatch family="<<family<<" scenario="<<scenario<<" config="<<config<<" round="<<rounding<<" a="<<std::hex<<a<<" b="<<b<<'\n';return 2;}hashes.push_back(a);}}
        for(unsigned config:{3u,4u})for(unsigned scenario=0;scenario<16;++scenario)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){const auto a=extended_case(false,1,scenario,config,rounding),b=extended_case(true,1,scenario,config,rounding);assert(a==b);hashes.push_back(a);}
        std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";return 0;
    }
    assert(std::fesetround(FE_TONEAREST)==0);std::cout<<"{\"workloads\":[";for(unsigned item=0;item<2;++item){if(item)std::cout<<',';std::cout<<"{\"item\":"<<item<<",\"calls_per_arm\":10000,\"pairs\":[";for(unsigned pair=0;pair<8;++pair){DamageTiming a,b;if(pair%2){b=bench(true,item,10000);a=bench(false,item,10000);}else{a=bench(false,item,10000);b=bench(true,item,10000);}assert(a.digest==b.digest);if(pair)std::cout<<',';std::cout<<"{\"baseline\":";write(a);std::cout<<",\"candidate\":";write(b);std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";
}

#include "damage_extended_fixture.hpp"
#include "damage_source_fixture.hpp"
static uint64_t active_case(bool candidate,unsigned type,unsigned flags,unsigned config,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);ExtendedFixture f(type*18+flags,(type+flags)%2==0);f.candidate=candidate;
    f.defender->f_isDead=f.defender->f_invulnerable=V::from_bool(false);f.defender->f_dodgeStacks=V::from_int(0);
    f.source->f_types=types_value(f.c,*f.source,type);f.source->f_flags=input_value(f.c,*f.source,flags);f.source->f_accuracy=V::from_float(100.0);
    f.c.native_event_kernel=true;f.c.native_resolved_dispatch=config!=2;f.c.native_event_audit=f.c.native_resolved_audit=config!=1;f.c.native_resolved_collect=true;
    std::vector<uint64_t> before;for(auto [stat,count]:legacy_counters)for(unsigned i=0;i<count;++i)before.push_back(stat(i));
    V args[]={f.initial,f.parent};assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);
    const V result=invoke_damage(candidate,*f.defender,args,2);const auto exceptions=std::fetestexcept(FE_ALL_EXCEPT);uint64_t h=f.state(result,exceptions);
    unsigned index=0;for(auto [stat,count]:legacy_counters)for(unsigned i=0;i<count;++i){h=mix(h,stat(i)-before[index]);++index;}
    return h;
}
int main(){register_gen_syms();std::vector<uint64_t> hashes;
    for(unsigned type=0;type<30;++type)for(unsigned flags=0;flags<18;++flags)for(unsigned config=0;config<3;++config)for(int rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        const auto a=active_case(false,type,flags,config,rounding),b=active_case(true,type,flags,config,rounding);if(a!=b){std::cerr<<"active mismatch type="<<type<<" flags="<<flags<<" config="<<config<<" round="<<rounding<<'\n';return 2;}hashes.push_back(a);
    }
    std::fesetround(FE_TONEAREST);std::cout<<"{\"passed\":true,\"cases\":"<<hashes.size()<<",\"case_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'\"'<<std::hex<<hashes[i]<<std::dec<<'\"';}std::cout<<"]}\n";
}

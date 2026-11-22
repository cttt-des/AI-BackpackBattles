#include "matched_timer_fixture.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <chrono>
static uint64_t cycles(){ULONG64 n;assert(QueryThreadCycleTime(GetCurrentThread(),&n));return n;}
static double cpu(){FILETIME a,b,k,u;assert(GetThreadTimes(GetCurrentThread(),&a,&b,&k,&u));ULARGE_INTEGER x,y;x.LowPart=k.dwLowDateTime;x.HighPart=k.dwHighDateTime;y.LowPart=u.dwLowDateTime;y.HighPart=u.dwHighDateTime;return(x.QuadPart+y.QuadPart)*1e-7;}
static volatile unsigned timer_sink=0;
static void measure_arm(bool candidate,unsigned items){
    Fixture f(items);for(unsigned i=0;i<f.items.size();i+=23)f.add(f.items[i]);for(unsigned i=0;i<f.gems.size();i+=37)f.add(f.gems[i]);
    f.c.native_resolved_audit=false;f.c.native_event_audit=false;f.enable();timer_local_candidate=candidate;
    V a[]={V::from_obj(f.chr),V::from_float(1.0/60)};
    for(unsigned i=0;i<10;++i)invoke_timer_local(*f.combat,a,2);
    const auto t=std::chrono::steady_clock::now();const auto ct=cpu();const auto cy=cycles();
    for(unsigned i=0;i<30000;++i)timer_sink=unsigned(invoke_timer_local(*f.combat,a,2).kind);
    const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count();const auto ce=cpu()-ct;const auto cyc=cycles()-cy;
    std::cout<<'"'<<(candidate?"candidate":"baseline")<<"\":{\"wall_s\":"<<elapsed<<",\"cpu_s\":"<<ce<<",\"cycles\":"<<cyc<<'}';
}
int main(int argc,char**argv){register_gen_syms();assert(SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS));assert(SetProcessAffinityMask(GetCurrentProcess(),255));
    if(argc>1&&std::string(argv[1])=="--screen"){std::cout<<"{\"workloads\":[";unsigned w=0;for(unsigned n:{16,48,96}){if(w++)std::cout<<',';std::cout<<"{\"items\":"<<n<<",\"pairs\":[";for(unsigned p=0;p<8;++p){if(p)std::cout<<',';std::cout<<'{';measure_arm(p%2==0,n);std::cout<<',';measure_arm(p%2!=0,n);std::cout<<'}';}std::cout<<"]}";}std::cout<<"]}\n";return 0;}
    std::vector<uint64_t> hashes,legacy;for(unsigned family=0;family<7;++family){unsigned n=family==4?4:family==5?6:20;for(unsigned s=0;s<n;++s)for(unsigned c=0;c<4;++c)for(int r:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}){
        timer_local_candidate=false;auto a=run(family,s,c,r);timer_local_candidate=true;auto b=run(family,s,c,r);
        if(a!=b){std::cerr<<"mismatch family="<<family<<" scenario="<<s<<" config="<<c<<" rounding="<<r<<'\n';return 2;}hashes.push_back(a.first);legacy.push_back(a.second);
    }}
    std::cout<<"{\"cases\":"<<hashes.size()<<",\"state_hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<hashes[i]<<std::dec<<'"';}std::cout<<"],\"legacy_hashes\":[";for(unsigned i=0;i<legacy.size();++i){if(i)std::cout<<',';std::cout<<'"'<<std::hex<<legacy[i]<<std::dec<<'"';}std::cout<<"]}\n";
}

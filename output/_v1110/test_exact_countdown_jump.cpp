#include "exact_countdown_jump.hpp"
#include <bit>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

static uint64_t rng=0xc16c7422973576e9ull;
static uint64_t random_bits(){rng^=rng<<13;rng^=rng>>7;rng^=rng<<17;return rng;}
static unsigned status(double witness=0){unsigned csr;asm volatile("stmxcsr %0":"=m"(csr):"x"(witness):"memory");return csr;}
static void control(unsigned csr){asm volatile("ldmxcsr %0"::"m"(csr):"memory");}
__attribute__((noinline)) static double original(double x,double d,uint64_t n) {
    for(uint64_t i=0;i<n;++i)asm volatile("subsd %1,%0":"+x"(x):"x"(d):"memory");
    return x;
}
struct Case {uint64_t x,d,n;};
int main() {
    const auto saved=status();std::vector<Case> cases;
    const unsigned exponents[]={1,2,500,1000,1017,1022,1023,1024,1027,1043,1500,2046};
    const unsigned gaps[]={0,1,2,6,7,12,24,51,52,53,54,63,64,100,1074};
    const uint64_t counts[]={0,1,2,3,4,8,16,63,256};
    const uint64_t mask=(1ull<<52)-1;
    for(auto e:exponents)for(auto gap:gaps)for(auto n:counts)for(unsigned k=0;k<20;++k) {
        const uint64_t x=uint64_t(e)<<52|(random_bits()&mask);
        const unsigned de=e>gap?e-gap:0;
        uint64_t d=uint64_t(de)<<52|(random_bits()&mask);
        if(k==0)d=0;if(k==1)d=1;if(k==2)d=0x7ff0000000000000ull;
        cases.push_back({x,d,n});
        if(gap>0 && gap<=53 && de) {
            uint64_t dm=(1ull<<52)|(random_bits()&mask);
            dm=(dm&~((1ull<<gap)-1))|(1ull<<(gap-1));
            cases.push_back({x,uint64_t(de)<<52|(dm&mask),n});
            cases.push_back({x^1,uint64_t(de)<<52|(dm&mask),n});
        }
    }
    // Dense random finite operands, plus exact binade boundary and signed cases.
    for(unsigned i=0;i<100000;++i) {
        const unsigned e=1+random_bits()%2046,gap=random_bits()%70,de=e>gap?e-gap:0;
        cases.push_back({uint64_t(e)<<52|(random_bits()&mask),uint64_t(de)<<52|(random_bits()&mask),counts[random_bits()%9]});
    }
    for(auto x:{0ull,0x8000000000000000ull,0x7ff0000000000000ull,0x7ff0000000000123ull,0xbff0000000000000ull,1ull,0x3ff0000000000000ull,0x3ff0000000000001ull})
        for(auto d:{0ull,0x3f91111120000000ull,0x3ca0000000000000ull,0x8000000000000000ull})for(auto n:counts)cases.push_back({x,d,n});
    uint64_t accepted=0,rejected=0,digest=1469598103934665603ull;
    for(unsigned mode=0;mode<16;++mode) {
        const auto csr=0x1f80u|((mode&3)<<13)|((mode&4)?0x40u:0)|((mode&8)?0x8000u:0);
        for(const auto& c:cases) {
            const unsigned initial=(c.x&1)?32u:0u;control(csr|initial);
            exact_countdown::Result actual{0xabcdef1234567890ull,0x76543210u};const auto before=actual;
            const bool ok=exact_countdown::jump(c.x,c.d,c.n,csr,actual);
            assert(status()==(csr|initial));
            if(!ok){assert(actual.bits==before.bits&&actual.flags==before.flags);++rejected;continue;}
            const double reference=original(std::bit_cast<double>(c.x),std::bit_cast<double>(c.d),c.n);const auto flags=status(reference);
            if(std::bit_cast<uint64_t>(reference)!=actual.bits || flags!=(csr|initial|actual.flags)) {
                std::cerr<<"mismatch mode="<<mode<<" x="<<std::hex<<c.x<<" d="<<c.d<<std::dec<<" n="<<c.n<<" flags="<<flags<<","<<(csr|initial|actual.flags)<<"\n";return 2;
            }
            digest=(digest^actual.bits^actual.flags)*1099511628211ull;++accepted;
        }
    }
    control(saved);
    // Cost screen only. Input classes stay within a binade, hardware-rounded
    // subtraction is the reference; timings do not include scheduler costs.
    std::cout<<std::setprecision(17)<<"{\"passed\":true,\"input_cases\":"<<cases.size()<<",\"accepted\":"<<accepted<<",\"rejected_without_changes\":"<<rejected<<",\"digest\":"<<digest<<",\"samples\":[";
    bool comma=false;volatile uint64_t sink=0;
    for(unsigned n:{4u,8u,32u,128u})for(unsigned q=0;q<4;++q) {
        const char* pattern=q%2?"BAAB":"ABBA";
        for(unsigned arm=0;arm<4;++arm) {
            uint64_t h=0;const auto start=std::chrono::steady_clock::now();
            for(unsigned i=0;i<200000;++i) {
                const uint64_t x=0x4038000000000000ull+(uint64_t(i&1023)<<30); // about24, decrement1/60
                if(pattern[arm]=='A')h^=std::bit_cast<uint64_t>(original(std::bit_cast<double>(x),0.01666666753590107,n));
                else {exact_countdown::Result out;assert(exact_countdown::jump(x,std::bit_cast<uint64_t>(0.01666666753590107),n,0x1f80,out));h^=out.bits;}
            }
            sink=h;const auto end=std::chrono::steady_clock::now();if(comma)std::cout<<',';comma=true;
            std::cout<<"{\"steps\":"<<n<<",\"quad\":"<<q<<",\"arm\":"<<arm<<",\"label\":\""<<pattern[arm]<<"\",\"wall_s\":"<<std::chrono::duration<double>(end-start).count()<<",\"signature\":"<<h<<"}";
        }
    }
    std::cout<<"],\"not_a_scheduler_or_release_gain\":true}\n";
}

#include "exact_countdown_jump.hpp"
#include <bit>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <xmmintrin.h>
static uint64_t state=0x914eae72359817b1ull;
static uint64_t next(){state^=state<<13;state^=state>>7;state^=state<<17;return state;}
struct Input {uint64_t x,d;};
__attribute__((noinline)) static uint64_t original(uint64_t xb,uint64_t db,uint64_t n) {
    double x=std::bit_cast<double>(xb),d=std::bit_cast<double>(db);
    for(uint64_t i=0;i<n;++i)asm volatile("subsd %1,%0":"+x"(x):"x"(d):"memory");
    return std::bit_cast<uint64_t>(x);
}
__attribute__((noinline)) static exact_countdown::Result jumped(uint64_t x,uint64_t d,uint64_t n) {
    asm volatile("":"+r"(n)::"memory"); // Prevent specializing the benchmark's chosen counts.
    exact_countdown::Result result;assert(exact_countdown::jump(x,d,n,0x1f80,result));return result;
}
int main() {
    std::vector<Input> inputs;
    for(unsigned i=0;i<4096;++i) {
        // x in[24,32), d in[1/64,1/32): all128-step windows remain in[16,32).
        inputs.push_back({0x4038000000000000ull|(next()&0x0007ffffffffffffull),0x3f90000000000000ull|(next()&0x000fffffffffffffull)});
    }
    std::cout<<std::setprecision(17)<<"{\"runtime_varied_inputs\":4096,\"opaque_step_count\":true,\"samples\":[";
    volatile uint64_t sink=0;bool comma=false;
    for(unsigned n:{4u,8u,32u,128u})for(unsigned q=0;q<4;++q) {
        const char* pattern=q%2?"BAAB":"ABBA";const uint64_t requests=80000000ull/n;
        for(unsigned arm=0;arm<4;++arm) {
            uint64_t hash=1469598103934665603ull;unsigned flags=0;
            const auto start=std::chrono::steady_clock::now();
            for(uint64_t i=0;i<requests;++i) {
                const auto& in=inputs[(i*13)&4095];uint64_t value;
                if(pattern[arm]=='A')value=original(in.x,in.d,n);
                else {const auto result=jumped(in.x,in.d,n);value=result.bits;flags|=result.flags;}
                hash=(hash^value)*1099511628211ull;
            }
            const auto end=std::chrono::steady_clock::now();sink=hash^flags;
            if(comma)std::cout<<',';comma=true;
            std::cout<<"{\"steps\":"<<n<<",\"requests\":"<<requests<<",\"quad\":"<<q<<",\"arm\":"<<arm<<",\"label\":\""<<pattern[arm]<<"\",\"wall_s\":"<<std::chrono::duration<double>(end-start).count()<<",\"signature\":"<<hash<<",\"required_flags\":"<<flags<<"}";
        }
    }
    std::cout<<"],\"scheduler_and_flag_materialization_not_measured\":true,\"not_release_gain\":true}\n";
}

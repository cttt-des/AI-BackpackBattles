#include "gd_rt.hpp"
#include <bit>
#include <cfenv>
#include <cassert>
#include <iostream>

__attribute__((noinline)) double ordered(double left,double right,bool multiply) {
    if(multiply) __asm__ volatile ("mulsd %1, %0" : "+x"(left) : "x"(right) : "memory");
    else __asm__ volatile ("addsd %1, %0" : "+x"(left) : "x"(right) : "memory");
    return left;
}

int main() {
    gd::BattleCtx ctx;unsigned cases=0;
    const uint64_t patterns[]={UINT64_C(0x7ff80000000000a5),UINT64_C(0xfff8000000001234),
        UINT64_C(0x7ff00000000000b6),UINT64_C(0xfff0000000001234),
        UINT64_C(0x7fffffffffffffff),UINT64_C(0xffffffffffffffff)};
    for(auto a:patterns)for(auto b:patterns)for(bool multiply:{false,true}) {
        const auto left=gd::GdVal::from_float(std::bit_cast<double>(a));
        const auto right=gd::GdVal::from_float(std::bit_cast<double>(b));
        std::feclearexcept(FE_ALL_EXCEPT);
        const auto expected=multiply?gd::gd_mul(left,right):gd::gd_add(ctx,left,right);
        const auto expected_flags=std::fetestexcept(FE_ALL_EXCEPT);
        std::feclearexcept(FE_ALL_EXCEPT);
        const double actual=ordered(left.f,right.f,multiply);
        const auto actual_flags=std::fetestexcept(FE_ALL_EXCEPT);
        assert(expected.kind==gd::GdVal::Kind::Float);
        assert(std::bit_cast<uint64_t>(expected.f)==std::bit_cast<uint64_t>(actual));
        assert(expected_flags==actual_flags);++cases;
    }
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<"}\n";
}

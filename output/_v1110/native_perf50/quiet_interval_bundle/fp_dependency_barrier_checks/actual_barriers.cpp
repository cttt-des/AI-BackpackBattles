#include <xmmintrin.h>
#include <bit>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
template<class T> static T* quiet_fp_begin(T* pointer) {
    unsigned csr;
    asm volatile("stmxcsr %0" : "=m"(csr) : : "memory");
    csr&=~0x3fu;
    asm volatile("ldmxcsr %1" : "+r"(pointer) : "m"(csr) : "memory");
    return pointer;
}
static unsigned quiet_fp_capture(double first=0.0,double second=0.0) {
    unsigned csr;
    asm volatile("stmxcsr %0" : "=m"(csr) : "x"(first),"x"(second) : "memory");
    return csr&0x3fu;
}

struct Input {double a,b,c,d;};
struct Result {double product,sum;unsigned flags;};
__attribute__((noinline)) static Result candidate(Input input,unsigned csr){
    _mm_setcsr(csr);const auto* p=quiet_fp_begin(&input);
    const auto product=p->a*p->b;const auto sum=p->c+p->d;
    return {product,sum,quiet_fp_capture(product,sum)};
}
__attribute__((noinline)) static Result reference(Input input,unsigned csr){
    double product=input.a,sum=input.c;unsigned flags;
    asm volatile("ldmxcsr %[control]\n\tmulsd %[b],%[product]\n\taddsd %[d],%[sum]\n\tstmxcsr %[flags]"
        :[product]"+x"(product),[sum]"+x"(sum),[flags]"=m"(flags)
        :[control]"m"(csr),[b]"x"(input.b),[d]"x"(input.d):"memory");
    return {product,sum,flags&0x3fu};
}
__attribute__((noinline)) static unsigned memory_candidate(Input* inputs,double* out,unsigned csr){
    _mm_setcsr(csr);auto* p=quiet_fp_begin(inputs);
    for(unsigned i=0;i<4;++i)out[i]=(p[i].a*p[i].b)+p[i].c;
    return quiet_fp_capture();
}
int main(){
    const uint64_t values[]={0,0x8000000000000000ull,1,0x100,0x8000000000000100ull,0x0010000000000000ull,0x8010000000000000ull,0x3ff0000000000000ull,0xbff0000000000000ull,0x3fe999999999999aull,0x3f91111120000000ull,0x7fefffffffffffffull,0xffefffffffffffffull};
    unsigned saved=_mm_getcsr(),cases=0;uint64_t digest=1469598103934665603ull;
    const auto bits=[](double x){return std::bit_cast<uint64_t>(x);};
    for(unsigned rounding=0;rounding<4;++rounding)for(unsigned ftz=0;ftz<4;++ftz)
    for(unsigned i=0;i<13;++i)for(unsigned j=0;j<13;++j)for(unsigned k=0;k<13;++k){
        unsigned csr=0x1f80u|(rounding<<13)|((ftz&1)?0x40u:0)|((ftz&2)?0x8000u:0);
        Input input{std::bit_cast<double>(values[i]),std::bit_cast<double>(values[j]),std::bit_cast<double>(values[k]),std::bit_cast<double>(values[(i+j+k)%13])};
        auto a=candidate(input,csr),b=reference(input,csr);
        assert(bits(a.product)==bits(b.product)&&bits(a.sum)==bits(b.sum)&&a.flags==b.flags);
        Input batch[4]={input,input,input,input};double actual[4];auto flags=memory_candidate(batch,actual,csr);
        double expected;unsigned expected_flags;double x=input.a;
        asm volatile("ldmxcsr %[control]\n\tmulsd %[b],%[x]\n\taddsd %[c],%[x]\n\tstmxcsr %[flags]"
            :[x]"+x"(x),[flags]"=m"(expected_flags):[control]"m"(csr),[b]"x"(input.b),[c]"x"(input.c):"memory");expected=x;
        assert(flags==(expected_flags&0x3fu));for(auto value:actual)assert(bits(value)==bits(expected));
        digest=(digest^bits(a.product)^bits(a.sum)^a.flags)*1099511628211ull;++cases;
    }
    _mm_setcsr(saved);std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fingerprint\":"<<digest<<"}\n";
}

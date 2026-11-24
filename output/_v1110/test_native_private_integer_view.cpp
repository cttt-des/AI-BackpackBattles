#include "native_private_snapshots.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

using V=gd::GdVal;
static uint64_t mix(uint64_t h,uint64_t v){return(h^v)*1099511628211ULL;}
static uint64_t hash(const V& v){
    uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));
    if(v.kind==V::Kind::Int)return mix(h,uint64_t(v.i));
    if(v.kind==V::Kind::Float)return mix(h,std::bit_cast<uint64_t>(v.f));
    if(v.kind==V::Kind::Str && v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,uint8_t(v.str->data[i]));}
    return h;
}
static V input(gd::BattleCtx& ctx,unsigned shape){
    if(shape<1130)return V::from_int(int64_t(shape)-100);
    switch(shape){
    case 1130:return V::from_int(INT64_MIN);
    case 1131:return V::from_bool(false);
    case 1132:return V::from_bool(true);
    case 1133:return V::from_float(2.75);
    case 1134:return V::from_float(-2.75);
    case 1135:return V::from_float(-0.0);
    case 1136:return V::from_str(nullptr);
    case 1137:return V::from_cstr(ctx.arena,"a\xc3\xa9Z");
    case 1138:return V::from_arr(nullptr);
    case 1139:return V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_int(2),V::from_float(3.25),V::from_int(4)}));
    case 1140:{auto* d=gd::GdDict::create(ctx.arena);d->set(ctx.arena,V::from_int(8),V::from_int(7));return V::from_dict(d);}
    default:return V::null();
    }
}
static uint64_t one(bool candidate,unsigned shape,unsigned mutation){
    gd::BattleCtx ctx(8192);ctx.bind_battle(137);V source=input(ctx,shape);
    gd::NativePrivateIntegerView view(ctx,candidate?source:V::null());
    const auto original=candidate?V::null():gd::gd_iter_seq(ctx.arena,source);
    auto* array=original.kind==V::Kind::Arr?original.arr:nullptr;
    const uint32_t length=candidate?view.length:array?array->len:0;
    uint64_t h=mix(1469598103934665603ULL,length);
    std::feclearexcept(FE_ALL_EXCEPT);
    for(uint32_t i=0;i<length;++i){
        const auto value=candidate?view.at(i):array->data[i];h=mix(h,hash(value));
        h=mix(h,ctx.math_rng.randi());
        if(i==0 && source.kind==V::Kind::Arr && source.arr && source.arr->len==3){
            auto* live=source.arr;
            if(mutation==1)live->data[1]=V::from_int(999);
            if(mutation==2){auto* data=ctx.arena.alloc_array<V>(8);for(unsigned j=0;j<3;++j)data[j]=live->data[j];data[2]=V::from_int(777);live->data=data;live->cap=8;live->len=1;}
            if(mutation==3)source=V::from_arr(gd::GdArr::from_init(ctx.arena,{V::from_int(0)}));
        }
    }
    h=mix(h,std::fetestexcept(FE_ALL_EXCEPT));h=mix(h,ctx.math_rng.pcg.state);h=mix(h,ctx.next_gid);return h;
}
int main(){
    register_gen_syms();uint64_t cases=0;
    for(auto rounding:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO})for(unsigned daz=0;daz<4;++daz){
        assert(std::fesetround(rounding)==0);_mm_setcsr((_mm_getcsr()&~0x8040u)|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        for(unsigned shape=0;shape<1142;++shape)for(unsigned mutation=0;mutation<4;++mutation){
            assert(one(false,shape,mutation)==one(true,shape,mutation));++cases;
        }
    }
    std::cout<<"{\"passed\":true,\"cases\":"<<cases<<",\"fallback_live_array_and_integer_boundary_checked\":true}\n";
}

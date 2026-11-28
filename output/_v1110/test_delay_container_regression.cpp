#include "native_inline_dispatch.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using V=gd::GdVal;using Context=Gd__gd_core__CoreContext;
#include "local_delay.hpp"
struct Container:gd::GdObj {
    double size=4.5;std::vector<double> resize;
    explicit Container(gd::BattleCtx* b):GdObj(b){}
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId method,const V* args,int argc,V& out)override{
        if(method==gd::SYM_size){out=V::from_float(size);return true;}
        if(method==gd::SYM_resize){assert(argc==1);resize.push_back(args[0].as_float());out=V::null();return true;}
        out=V::null();return false;
    }
};
struct Receiver:gd::GdObj {
    Context* ctx;Container* container;
    Receiver(gd::BattleCtx* b,Context* c,Container* p):GdObj(b),ctx(c),container(p){}
    const gd::GdClassMeta* meta()const override{return nullptr;}
    bool call_method(gd::BattleCtx&,gd::SymId,const V*,int,V& out)override{ctx->f__timed=V::from_obj(container);out=V::null();return true;}
};
static double run(bool literal,double size){gd::BattleCtx b(65536);b.bind_battle(123);b.native_resolved_dispatch=true;
    auto* ctx=static_cast<Context*>(META_Gd__gd_core__CoreContext.alloc_fn(b));ctx->init_fields(b);ctx->f_fight_ended=V::from_bool(false);
    Container container(&b);container.size=size;Receiver recv(&b,ctx,&container);
    for(unsigned i=0;i<4;++i){auto entry=V::from_arr(gd::GdArr::from_init(b.arena,{V::from_obj(&recv),V::from_str(gd::make_static_str("done")),V::from_float(i==0?.001:.2),V::from_arr(gd::GdArr::create(b.arena))}));ctx->f__timed.arr->push_back(b.arena,entry);}
    const V delta=V::from_float(.01666666753590107);if(literal)local_delay(ctx,&delta,1);else ctx->fn__step_native_delays(&delta,1);
    assert(container.resize.size()==1);return container.resize[0];
}
int main(){register_gen_syms();unsigned mismatch=0;std::cout<<"{\"rows\":[";bool comma=false;for(double size:{4.0,4.25,4.5,4.75,5.0,5.25}){const auto original=run(true,size),actual=run(false,size);if(original!=actual)++mismatch;if(comma)std::cout<<',';comma=true;std::cout<<"{\"size\":"<<size<<",\"original_resize\":"<<original<<",\"actual_resize\":"<<actual<<'}';}std::cout<<"],\"semantic_cases\":6,\"mismatches\":"<<mismatch<<",\"passed\":"<<(mismatch?"false":"true")<<"}\n";}

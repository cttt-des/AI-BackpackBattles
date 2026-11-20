#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <cassert>
#include <iostream>
#include <limits>
using V=gd::GdVal;
using Item=Gd__gd_core__CoreItem;

struct Custom:Item {
    bool intercept=false;
    mutable int metadata_reads=0,queries=0;
    int intercepted=0;
    explicit Custom(gd::BattleCtx* ctx):Item(ctx){}
    const gd::GdClassMeta* meta() const override {++metadata_reads;return Item::meta();}
    bool has_own_method(gd::SymId method) const override {++queries;return Item::has_own_method(method);}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out) override {
        if(intercept && method==gd::SYM_has_method){++intercepted;out=V::from_bool(false);return true;}
        if(intercept && method==gd::SYM_get_instance_id){++intercepted;out=V::from_int(777);return true;}
        return Item::call_method(ctx,method,args,argc,out);
    }
};

int main(){
    register_gen_syms();
    gd::BattleCtx fast,slow;
    fast.native_resolved_dispatch=true;fast.native_resolved_collect=true;fast.native_resolved_audit=true;
    auto call=[](gd::BattleCtx& ctx,gd::GdObj* object,gd::SymId method,const V* args=nullptr,int argc=0){
        return gd::call_method(ctx,V::from_obj(object),method,args,argc);
    };
    Item a(&fast),b(&slow),a2(&fast),b2(&slow);
    a.init_fields(fast);b.init_fields(slow);a2.init_fields(fast);b2.init_fields(slow);
    unsigned checks=0;
    const V names[]={V::from_cstr(fast.arena,"character"),V::from_cstr(fast.arena,"physicsTick"),
        V::from_cstr(fast.arena,"has_method"),V::from_cstr(fast.arena,"not_a_generated_method"),
        V::from_cstr(fast.arena,""),V::from_int(0),V::null(),V::from_str(nullptr)};
    for(const auto& name:names){
        const auto x=call(fast,&a,gd::SYM_has_method,&name,1),y=call(slow,&b,gd::SYM_has_method,&name,1);
        assert(x.kind==V::Kind::Bool && x.b==y.b);++checks;
    }
    for(int argc: {0,-1}){
        const auto x=call(fast,&a,gd::SYM_has_method,nullptr,argc),y=call(slow,&b,gd::SYM_has_method,nullptr,argc);
        assert(x.kind==V::Kind::Bool && !x.b && gd::gd_eq(x,y));++checks;
    }
    for(int epoch=0;epoch<3;++epoch){
        if(epoch){++fast.gid_epoch;++slow.gid_epoch;}
        if(epoch==2)fast.next_gid=slow.next_gid=std::numeric_limits<uint64_t>::max();
        for(int i=0;i<5;++i){
            Item* lhs=i%2?&a2:&a;Item* rhs=i%2?&b2:&b;
            const auto x=call(fast,lhs,gd::SYM_get_instance_id),y=call(slow,rhs,gd::SYM_get_instance_id);
            assert(x.kind==V::Kind::Int && x.i==y.i && fast.next_gid==slow.next_gid);
            assert(lhs->gid_==rhs->gid_ && lhs->gid_epoch_==rhs->gid_epoch_);++checks;
        }
    }
    const auto name=V::from_cstr(fast.arena,"character");
    Custom ca(&fast),cb(&slow);ca.init_fields(fast);cb.init_fields(slow);
    for(bool intercept: {false,true}){
        ca.intercept=cb.intercept=intercept;
        assert(gd::gd_eq(call(fast,&ca,gd::SYM_has_method,&name,1),call(slow,&cb,gd::SYM_has_method,&name,1)));
        assert(gd::gd_eq(call(fast,&ca,gd::SYM_get_instance_id),call(slow,&cb,gd::SYM_get_instance_id)));
        assert(ca.intercepted==cb.intercepted && ca.queries==cb.queries);
        assert(ca.metadata_reads==cb.metadata_reads && ca.metadata_reads==0);checks+=2;
    }
    gd::GdFuncRef fa,fb;fa.instance=&a;fb.instance=&b;
    for(const auto method: {gd::SYM_has_method,gd::SYM_get_instance_id}){
        fa.method=fb.method=method;
        assert(fa.call_func(fast,&name,1).is_null() && fb.call_func(slow,&name,1).is_null());
        fa.binds=fb.binds=gd::GdArr::from_init(fast.arena,{name});
        assert(fa.call_func(fast,nullptr,0).is_null() && fb.call_func(slow,nullptr,0).is_null());
        fa.binds=fb.binds=nullptr;checks+=2;
    }
    fa.instance=&ca;fb.instance=&cb;fa.method=fb.method=gd::SYM_get_instance_id;
    assert(fa.call_func(fast,nullptr,0).i==777 && fb.call_func(slow,nullptr,0).i==777);++checks;
    const auto previous=fast.native_resolved_counts[0];fast.native_resolved_dispatch=false;
    assert(gd::gd_eq(call(fast,&a,gd::SYM_has_method,&name,1),call(slow,&b,gd::SYM_has_method,&name,1)));
    assert(fast.native_resolved_counts[0]==previous && fast.native_resolved_counts[4]==0);
    assert(fast.native_resolved_counts[3]>0);
    std::cout<<checks<<" builtin differential checks; missing/nonstring argument, C++ override/shared metadata, FuncRef original Null, rebound custom FuncRef, ID order/epoch/wrap and disabled path passed\n";
}

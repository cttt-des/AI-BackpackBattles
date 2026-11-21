#include "native_property_test_cases.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
extern "C" void gd_init_all_classes();
extern "C" uint64_t gd_diag_native_property_stat(unsigned);

bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    switch(a.kind){
        case V::Kind::Null:return true;
        case V::Kind::Bool:return a.b==b.b;
        case V::Kind::Int:return a.i==b.i;
        case V::Kind::Float:return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
        case V::Kind::Vec2:return std::bit_cast<uint64_t>(a.v2.x)==std::bit_cast<uint64_t>(b.v2.x) && std::bit_cast<uint64_t>(a.v2.y)==std::bit_cast<uint64_t>(b.v2.y);
        case V::Kind::Color:return a.col==b.col;
        case V::Kind::Str:return a.str==b.str;
        case V::Kind::Arr:return a.arr==b.arr;
        case V::Kind::Dict:return a.dict==b.dict;
        case V::Kind::Obj:return a.obj==b.obj;
        case V::Kind::ClassRef:return a.cls==b.cls;
        case V::Kind::Enum:return a.en==b.en;
        case V::Kind::FuncRef:return a.fr==b.fr;
        case V::Kind::Rng:return a.rng==b.rng;
    }
    return false;
}

struct Payload:gd::GdObj {
    mutable unsigned metadata_reads=0;
    explicit Payload(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta() const override{++metadata_reads;return &META_Gd__gd_core__CoreItemData;}
};
struct CustomContext:Context {
    mutable unsigned reads=0,metadata_reads=0;
    mutable bool saw_null=true;
    explicit CustomContext(gd::BattleCtx* ctx):Context(ctx){}
    const gd::GdClassMeta* meta() const override{++metadata_reads;return Context::meta();}
    bool get_prop(gd::SymId s,V& out) const override{
        ++reads;saw_null=saw_null && !native_call_row_;
        rt_ctx_->math_rng.randf();
        if(s==SYM_GEN_rng_1406){out=V::from_int(77);return true;}
        return Context::get_prop(s,out);
    }
};
static unsigned static_calls=0;
bool custom_static(gd::SymId,V& out){++static_calls;out=V::from_int(333);return false;}

int main(){
    gd_init_all_classes();uint64_t cases=0,fields=0,classes=0,alias_checks=0;
    const auto initial_hits=gd_diag_native_property_stat(0);
    for(const auto& type:property_test_classes){
        ++classes;
        for(bool seeded:{false,true}){
            gd::BattleCtx ctx;ctx.native_resolved_dispatch=seeded;
            ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
            auto* object=type.meta->alloc_fn(ctx);assert(object && object->meta()==type.meta);
            assert(bool(object->native_call_row_)==seeded);
            const auto recv=V::from_obj(object);const auto rng=ctx.math_rng.pcg.state;
            Payload payload(&ctx);gd::GdRng value_rng(42);gd::GdFuncRef reference;
            reference.instance=&payload;reference.method=SYM_GEN_rng_1406;
            const gd::GdEnum::KV keys[]={{"entry",1}};const gd::GdEnum enumeration{"test",keys,1};
            gd::GdColor color{0.5,-0.0,1.0,0.25};
            auto* array=gd::GdArr::from_init(ctx.arena,{V::from_int(3)});
            auto* dict=gd::GdDict::create(ctx.arena);
            const auto nan=std::bit_cast<double>(uint64_t{0x7ff80000000000a5ULL});
            const std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),
                V::from_int(0),V::from_int(std::numeric_limits<int64_t>::min()),V::from_int(std::numeric_limits<int64_t>::max()),
                V::from_float(0.0),V::from_float(-0.0),V::from_float(1.25),V::from_float(nan),
                V::from_float(std::numeric_limits<double>::infinity()),V::from_vec2(nan,-0.0),
                V::from_str(gd::make_static_str("property-test")),V::from_str(nullptr),
                V::from_arr(array),V::from_dict(dict),V::from_obj(&payload),V::from_cls(type.meta),
                V::from_enum(&enumeration),V::from_funcref(&reference),V::from_rng(&value_rng),V::from_color(&color)};
            bool any=false;
            for(unsigned slot=0;slot<std::size(property_test_symbols);++slot){
                const auto ref=type.row->refs[slot];if(!ref)continue;
                any=true;++fields;auto* field=ref(object);const auto symbol=property_test_symbols[slot];
                assert(symbol!=gd::SYM_resource_path);
                assert(gd::native_property_slots[symbol]==static_cast<int>(slot));
                for(const auto& input:values){
                    *field=input;
                    // Independently execute the original virtual switch first.
                    // This also catches an incorrect fixture field/shadow owner.
                    const auto oracle=gd::get_prop(ctx,recv,symbol);assert(same(oracle,input));
                    ctx.native_resolved_dispatch=false;
                    const auto* before=object->native_call_row_;
                    assert(same(gd::native_inline_get_prop(ctx,recv,symbol),oracle));
                    assert(object->native_call_row_==before);
                    ctx.native_resolved_dispatch=true;
                    assert(same(gd::native_inline_get_prop(ctx,recv,symbol),oracle));
                    assert(same(*field,input));++cases;
                }
                *field=V::from_arr(array);array->push_back(ctx.arena,V::from_int(9));
                const auto alias=gd::native_inline_get_prop(ctx,recv,symbol);
                assert(alias.arr==array && alias.arr->data[alias.arr->len-1].i==9);++alias_checks;
            }
            if(any)assert(object->native_call_row_);
            const auto missing=gd::intern_sym("missing_native_property_test");
            assert(gd::get_prop(ctx,recv,missing).is_null());
            assert(gd::native_inline_get_prop(ctx,recv,missing).is_null());
            assert(ctx.math_rng.pcg.state==rng && ctx.next_gid==1 && payload.metadata_reads==0);
            assert(ctx.native_resolved_counts[4]==0);
        }
    }
    assert(classes==674 && cases>10000 && gd_diag_native_property_stat(0)>initial_hits);
    unsigned boundary=0;
    gd::BattleCtx slow,fast;slow.bind_battle(17);fast.bind_battle(17);
    fast.native_resolved_dispatch=true;fast.native_resolved_audit=true;fast.native_resolved_collect=true;
    CustomContext a(&slow),b(&fast);
    for(unsigned i=0;i<3;++i){
        const auto x=gd::get_prop(slow,V::from_obj(&a),SYM_GEN_rng_1406);
        const auto y=gd::native_inline_get_prop(fast,V::from_obj(&b),SYM_GEN_rng_1406);
        assert(same(x,y) && a.reads==b.reads && a.saw_null && b.saw_null);
        assert(!a.native_call_row_ && !b.native_call_row_ && a.metadata_reads==0 && b.metadata_reads==0);
        assert(slow.math_rng.pcg.state==fast.math_rng.pcg.state);++boundary;
    }
    const auto x=gd::get_prop(slow,V::from_obj(&a),gd::SYM_resource_path);
    const auto y=gd::native_inline_get_prop(fast,V::from_obj(&b),gd::SYM_resource_path);
    assert(gd::gd_eq(x,y) && a.metadata_reads==1 && b.metadata_reads==1 && a.reads==3 && b.reads==3);++boundary;
    Context plain(&fast);plain.f_rng=V::from_int(9);
    assert(gd::native_inline_get_prop(fast,V::from_obj(&plain),SYM_GEN_rng_1406).i==9 && plain.native_call_row_);++boundary;
    Context copy(plain);assert(!copy.native_call_row_);
    assert(gd::native_inline_get_prop(fast,V::from_obj(&copy),SYM_GEN_rng_1406).i==9);++boundary;
    b.f_rng=V::from_int(19);plain=b;assert(!plain.native_call_row_);
    assert(gd::native_inline_get_prop(fast,V::from_obj(&plain),SYM_GEN_rng_1406).i==19 && b.reads==3);++boundary;
    Context slice(b);assert(!slice.native_call_row_);
    assert(gd::native_inline_get_prop(fast,V::from_obj(&slice),SYM_GEN_rng_1406).i==19);++boundary;
    plain.native_call_row_=reinterpret_cast<const gd::NativeMethodRow*>(uintptr_t(1));
    assert(gd::native_inline_get_prop(fast,V::from_obj(&plain),SYM_GEN_rng_1406).i==19);
    assert(fast.native_resolved_counts[4]==1);plain.native_call_row_=nullptr;++boundary;
    assert(gd::native_inline_get_prop(fast,V::from_obj(&plain),SYM_GEN_identifier_1673).is_null());++boundary;
    gd::GdClassMeta meta=META_Gd__gd_core__CoreContext;meta.get_static_prop=custom_static;
    assert(gd::native_inline_get_prop(fast,V::from_cls(&meta),SYM_GEN_rng_1406).is_null() && static_calls==1);++boundary;
    const auto path=gd::native_inline_get_prop(fast,V::from_cls(&meta),gd::SYM_resource_path);
    assert(path.kind==V::Kind::Str && static_calls==1);++boundary;
    auto* dictionary=gd::GdDict::create(fast.arena);dictionary->set(fast.arena,V::from_cstr(fast.arena,"rng"),V::from_int(88));
    assert(gd::native_inline_get_prop(fast,V::from_dict(dictionary),SYM_GEN_rng_1406).i==88);++boundary;
    const std::vector<V> others={V::null(),V::from_int(3),V::from_bool(true),V::from_str(gd::make_static_str("text")),
        V::from_vec2(1.25,-0.0),V::from_arr(nullptr),V::from_dict(nullptr),V::from_rng(nullptr),V::from_funcref(nullptr),V::from_color(nullptr)};
    for(const auto& value:others){
        assert(same(gd::get_prop(fast,value,SYM_GEN_rng_1406),gd::native_inline_get_prop(fast,value,SYM_GEN_rng_1406)));++boundary;
    }
    V null_object;null_object.kind=V::Kind::Obj;null_object.obj=nullptr;
    assert(gd::native_inline_get_prop(fast,null_object,SYM_GEN_rng_1406).is_null());++boundary;
    std::cout<<"{\"classes\":"<<classes<<",\"field_cases\":"<<cases<<",\"field_bindings\":"<<fields
        <<",\"aliases\":"<<alias_checks<<",\"boundary_cases\":"<<boundary
        <<",\"rng_ids_payload_metadata_unchanged\":true,\"explicit_bad_row_audit_caught\":true}\n";
}

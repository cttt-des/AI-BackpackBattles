#include "native_typed_read_test_cases.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include <bit>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using V=gd::GdVal;
extern "C" void gd_init_all_classes();
extern "C" uint64_t gd_diag_native_typed_read_stat(unsigned);

bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    switch(a.kind){
        case V::Kind::Null:return true;
        case V::Kind::Bool:return a.b==b.b;
        case V::Kind::Int:return a.i==b.i;
        case V::Kind::Float:return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
        case V::Kind::Vec2:return std::bit_cast<uint64_t>(a.v2.x)==std::bit_cast<uint64_t>(b.v2.x) && std::bit_cast<uint64_t>(a.v2.y)==std::bit_cast<uint64_t>(b.v2.y);
        case V::Kind::Str:return a.str==b.str;
        case V::Kind::Obj:return a.obj==b.obj;
        case V::Kind::Arr:return a.arr==b.arr;
        case V::Kind::Dict:return a.dict==b.dict;
        case V::Kind::Color:return a.col==b.col;
        case V::Kind::Rng:return a.rng==b.rng;
        case V::Kind::FuncRef:return a.fr==b.fr;
        case V::Kind::ClassRef:return a.cls==b.cls;
        case V::Kind::Enum:return a.en==b.en;
    }
    return false;
}

struct Payload:gd::GdObj {
    mutable unsigned reads=0;
    explicit Payload(gd::BattleCtx* ctx):GdObj(ctx){}
    const gd::GdClassMeta* meta() const override{++reads;return &META_Gd__gd_core__CoreItemData;}
};

int main(){
    gd_init_all_classes();uint64_t cases=0,bindings=0,aliases=0,alignments=0;
    const auto initial=gd_diag_native_typed_read_stat(1);
    for(const auto& type:typed_read_classes)for(bool seeded:{false,true}){
        gd::BattleCtx ctx;ctx.native_resolved_dispatch=seeded;ctx.native_resolved_collect=true;ctx.native_resolved_audit=true;
        auto* object=type.meta->alloc_fn(ctx);assert(object && object->meta()==type.meta);
        assert(bool(object->native_call_row_)==seeded);
        if(seeded){
            const auto* row=object->native_call_row_->properties;
            assert(row && uintptr_t(row)%64==0 && row->getters && sizeof(*row)==128);
            ++alignments;
        }
        Payload payload(&ctx);gd::GdRng rng(42);gd::GdFuncRef reference{&payload,SYM_GEN_character_74,nullptr};
        const gd::GdEnum::KV keys[]={{"entry",1}};const gd::GdEnum enumeration{"test",keys,1};
        gd::GdColor color{0.5,-0.0,1.0,0.25};
        auto* array=gd::GdArr::from_init(ctx.arena,{V::from_int(3)});
        auto* dictionary=gd::GdDict::create(ctx.arena);
        const auto nan=std::bit_cast<double>(UINT64_C(0x7ff80000000000a5));
        const std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),
            V::from_int(std::numeric_limits<int64_t>::min()),V::from_int(std::numeric_limits<int64_t>::max()),
            V::from_float(0.0),V::from_float(-0.0),V::from_float(1.25),V::from_float(nan),
            V::from_float(std::bit_cast<double>(UINT64_C(0x7ff00000000000a5))),
            V::from_float(std::numeric_limits<double>::denorm_min()),
            V::from_float(std::numeric_limits<double>::infinity()),V::from_vec2(nan,-0.0),
            V::from_str(gd::make_static_str("typed-read")),V::from_str(nullptr),V::from_arr(array),V::from_dict(dictionary),
            V::from_obj(&payload),V::from_cls(type.meta),V::from_enum(&enumeration),V::from_funcref(&reference),V::from_rng(&rng),V::from_color(&color)};
        const auto state=ctx.math_rng.pcg.state;
        for(unsigned column=0;column<std::size(typed_read_methods);++column){
            const auto ref=type.refs->values[column];if(!ref)continue;
            ++bindings;auto* field=ref(object);const auto method=typed_read_methods[column];
            for(const auto& input:values){
                *field=input;const V args[]={V::from_obj(&payload),V::from_float(-0.0)};
                V oracle;assert(object->call_method(ctx,method,args,2,oracle));
                // This independently checks the fixture's field against the
                // untouched virtual method before exercising typed dispatch.
                assert(same(oracle,input));
                ctx.native_resolved_dispatch=false;
                assert(same(gd::native_inline_call(ctx,V::from_obj(object),method,args,2),oracle));
                ctx.native_resolved_dispatch=true;
                assert(same(gd::native_inline_call(ctx,V::from_obj(object),method,args,2),oracle));
                assert(same(gd::call_method(ctx,V::from_obj(object),method,args,2),oracle));
                auto* binds=gd::GdArr::from_init(ctx.arena,{V::from_int(77)});
                gd::GdFuncRef function{object,method,binds};
                assert(same(function.call_func(ctx,args,2),oracle));
                assert(same(*field,input));++cases;
            }
            *field=V::from_arr(array);array->push_back(ctx.arena,V::from_int(19));
            const auto alias=gd::native_inline_call(ctx,V::from_obj(object),method,nullptr,0);
            assert(alias.arr==array && alias.arr->data[alias.arr->len-1].i==19);++aliases;
        }
        assert(ctx.math_rng.pcg.state==state && ctx.next_gid==1 && payload.reads==0);
        assert(ctx.native_resolved_counts[4]==0);
    }
    assert(alignments==674 && bindings>500 && cases>10000 && aliases==bindings);
    assert(gd_diag_native_typed_read_stat(1)>initial);
    std::cout<<"{\"classes\":674,\"method_columns\":4,\"pure_method_payload_cases\":"<<cases
        <<",\"field_bindings_and_aliases\":"<<bindings<<",\"aligned_read_rows\":"<<alignments
        <<",\"original_virtual_oracle_args_binds_rng_ids_unchanged\":true}\n";
}

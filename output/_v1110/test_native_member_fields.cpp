#include "member_probe_cases.hpp"
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
#include <vector>
using V=gd::GdVal;
extern "C" void gd_init_all_classes();
static bool same(const V& a,const V& b){
    if(a.kind!=b.kind)return false;
    if(a.kind==V::Kind::Null)return true;
    if(a.kind==V::Kind::Vec2)return std::bit_cast<uint64_t>(a.v2.x)==std::bit_cast<uint64_t>(b.v2.x) && std::bit_cast<uint64_t>(a.v2.y)==std::bit_cast<uint64_t>(b.v2.y);
    if(a.kind==V::Kind::Float)return std::bit_cast<uint64_t>(a.f)==std::bit_cast<uint64_t>(b.f);
    return a.i==b.i;
}
int main(){
    gd_init_all_classes();uint64_t cases=0,aliases=0,fields=0;
    for(unsigned n=0;n<std::size(property_test_classes);++n){
        gd::BattleCtx c(65536);c.native_resolved_dispatch=true;c.native_resolved_audit=true;
        const auto& type=property_test_classes[n];auto* obj=type.meta->alloc_fn(c);obj->init_fields(c);
        assert(obj->native_call_row_ && gd::native_resolved_row_matches(obj,obj->native_call_row_));
        const auto& members=probe_members[probe_class_rows[n]];
        auto* array=gd::GdArr::create(c.arena,1);array->push_back(c.arena,V::from_int(99));
        auto* dict=gd::GdDict::create(c.arena,0);
        const std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),V::from_int(0),V::from_int(INT64_MIN),V::from_int(INT64_MAX),V::from_float(0.0),V::from_float(-0.0),V::from_float(1.25),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff8000000001234))),V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))),V::from_vec2(-0.0,1.25),V::from_str(gd::make_str(c.arena,"member")),V::from_str(nullptr),V::from_arr(array),V::from_dict(dict),V::from_obj(obj),V::from_cls(type.meta),V::from_rng(&c.math_rng)};
        for(unsigned slot=0;slot<64;++slot){
            if(!members[slot]){assert(!type.row->refs[slot]);continue;}
            ++fields;auto* ref=type.row->refs[slot](obj);assert(&(obj->*members[slot])==ref);
            for(const auto& value:values){
                *ref=value;V original;assert(obj->get_prop(property_test_symbols[slot],original));
                assert(same(original,value));
                std::feclearexcept(FE_ALL_EXCEPT);const V member_value=obj->*members[slot];assert(std::fetestexcept(FE_ALL_EXCEPT)==0);
                assert(same(original,member_value));
                const auto fn=obj->native_call_row_->properties->getters[slot];assert(fn);
#ifdef GD_MEMBER_PRODUCTION
                assert(same(obj->*fn,member_value));
#else
                assert(same(fn(obj),member_value));
#endif
                ++cases;
            }
            *ref=V::from_arr(array);auto copied=obj->*members[slot];copied.arr->data[0]=V::from_int(55);assert(ref->arr->data[0].i==55);++aliases;
        }
    }
    std::cout<<"{\"passed\":true,\"classes\":"<<std::size(property_test_classes)<<",\"field_bindings\":"<<fields<<",\"cases\":"<<cases<<",\"alias_checks\":"<<aliases<<",\"member_pointer_bytes\":"<<sizeof(Member)<<",\"variant_bytes\":"<<sizeof(V)<<"}\n";
}

#include "gd_rt.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using V=gd::GdVal;
using D=gd::GdDict;

void value(D* dict,const V& key,int64_t expected) {
    const auto found=dict->get(key,V::from_int(-999999));
    assert(found.kind==V::Kind::Int && found.i==expected);
}

int main() {
    gd::BattleCtx context;
    auto& arena=context.arena;
    auto* dense=D::create(arena);
    value(dense,V::from_int(0),-999999);
    for(int i=0;i<1024;++i) dense->set(arena,V::from_int(i),V::from_int(i*7+3));
    for(int i=0;i<1024;++i) {
        value(dense,V::from_int(i),i*7+3);
        value(dense,V::from_float(i),i*7+3);
        assert(dense->find_index(V::from_int(i),gd::gd_val_hash(V::from_int(i)))==i);
        assert(dense->find_index(V::from_int(i),gd::gd_val_hash(V::from_int(i))^1ULL)==-1);
    }
    std::vector<int> order;
    for(int i=0;i<1024;++i) if(i%3==0) dense->erase(V::from_int(i)); else order.push_back(i);
    for(int i=0;i<1024;++i) value(dense,V::from_int(i),i%3==0?-999999:i*7+3);
    for(int i=0;i<1024;i+=3) {dense->set(arena,V::from_int(i),V::from_int(-i-1));order.push_back(i);}
    auto* keys=dense->keys(arena);
    assert(keys->len==order.size());
    for(unsigned i=0;i<keys->len;++i) assert(keys->data[i].kind==V::Kind::Int && keys->data[i].i==order[i]);
    for(int i=0;i<1024;++i) value(dense,V::from_int(i),i%3==0?-i-1:i*7+3);
    value(dense,V::from_int(-1),-999999);
    value(dense,V::from_int(std::numeric_limits<int64_t>::max()),-999999);
    auto* copy=dense->duplicate(arena);
    dense->clear();
    value(dense,V::from_int(5),-999999);value(copy,V::from_int(5),38);

    auto* mixed=D::create(arena);
    mixed->set(arena,V::from_cstr(arena,"first"),V::from_int(77));
    for(int i=0;i<20;++i) mixed->set(arena,V::from_int(i),V::from_int(i+100));
    for(int i=0;i<20;++i) value(mixed,V::from_int(i),i+100);
    mixed->erase(V::from_cstr(arena,"first"));
    for(int i=0;i<20;++i) value(mixed,V::from_int(i),i+100);
    mixed->set(arena,V::from_float(-0.0),V::from_int(91));
    value(mixed,V::from_int(0),91);value(mixed,V::from_bool(false),91);
    mixed->set(arena,V::from_bool(true),V::from_int(92));
    value(mixed,V::from_int(1),92);value(mixed,V::from_float(1.0),92);
    mixed->set(arena,V::from_float(0.25),V::from_int(93));
    value(mixed,V::from_float(0.25),93);
    mixed->set(arena,V::from_vec2(2,3),V::from_int(94));
    value(mixed,V::from_vec2(2,3),94);
    mixed->set(arena,V::null(),V::from_int(95));value(mixed,V::null(),95);
    auto* float_first=D::create(arena);
    float_first->set(arena,V::from_float(0.0),V::from_int(20));
    float_first->set(arena,V::from_float(1.0),V::from_int(21));
    value(float_first,V::from_int(0),20);value(float_first,V::from_int(1),21);
    float_first->set(arena,V::from_int(1),V::from_int(23));
    value(float_first,V::from_float(1.0),23);
    const int64_t huge=(1LL<<53);
    float_first->set(arena,V::from_int(huge),V::from_int(50));
    float_first->set(arena,V::from_int(huge+1),V::from_int(51));
    value(float_first,V::from_int(huge),50);value(float_first,V::from_int(huge+1),51);
    value(float_first,V::from_float(static_cast<double>(huge)),50);
    const auto nan=V::from_float(std::numeric_limits<double>::quiet_NaN());
    float_first->set(arena,nan,V::from_int(99));value(float_first,nan,-999999);
    std::cout<<"Dense lookup, growth, erase/reinsert order, default, duplication, clear, mixed keys, numeric aliases, huge integers and NaN passed\n";
}

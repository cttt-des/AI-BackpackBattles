#pragma once
#include "gd_rt.hpp"
namespace gd {
inline GdVal native_array_index(BattleCtx& ctx,const GdVal& recv,const GdVal& key) {
    if(recv.kind==GdVal::Kind::Arr && recv.arr && key.kind==GdVal::Kind::Int) {
        int64_t index=key.i;
        if(index<0)index+=static_cast<int64_t>(recv.arr->len);
        if(index<0 || static_cast<uint64_t>(index)>=recv.arr->len)return GdVal::null();
        return recv.arr->data[index];
    }
    return gd::get_index(ctx,recv,key);
}
} // namespace gd

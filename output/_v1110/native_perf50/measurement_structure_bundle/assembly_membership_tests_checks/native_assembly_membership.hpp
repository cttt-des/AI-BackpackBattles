#pragma once
#include "gd_rt.hpp"
namespace gd::assembly_membership {
__attribute__((always_inline)) inline bool object_set_contains(const GdVal& item,const GdVal& set) {
    if(set.kind==GdVal::Kind::Dict && set.dict) {
        const auto* dict=set.dict;
        // Obj hashing reads only the pointer and cannot raise FP exceptions.
        // The unindexed empty path in the original find_index cannot match.
        // Indexed empty/stale tables retain their original lookup behavior.
        if(item.kind==GdVal::Kind::Obj && dict->len==0 && (!dict->buckets || dict->bucket_cap==0))return false;
        return dict->has(item);
    }
    return native_scalar_truth(gd_in(item,set));
}
}

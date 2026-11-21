#pragma once
#include "gd_rt.hpp"
namespace gd {
inline bool native_static_sound_count(const GdVal& character_class,unsigned column,GdVal& out) {
    if(character_class.kind!=GdVal::Kind::Int || character_class.i<0 || character_class.i>=7 || column>=3)return false;
    static constexpr int64_t counts[7][3]={
        {3,6,6},
        {3,2,4},
        {3,4,6},
        {5,4,4},
        {3,6,5},
        {4,7,6},
        {6,5,8},
    };
    out=GdVal::from_int(counts[character_class.i][column]);return true;
}
}

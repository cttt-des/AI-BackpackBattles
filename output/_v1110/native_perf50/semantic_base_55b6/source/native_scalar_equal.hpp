#pragma once
#include "gd_rt.hpp"
namespace gd {
inline bool native_scalar_eq(const GdVal& a,const GdVal& b) {
    if(a.kind==b.kind) {
        switch(a.kind) {
            case GdVal::Kind::Null:return true;
            case GdVal::Kind::Bool:return a.b==b.b;
            case GdVal::Kind::Int:return a.i==b.i;
            case GdVal::Kind::Float:return a.f==b.f;
            default:break;
        }
    }
    if(a.kind==GdVal::Kind::Null || b.kind==GdVal::Kind::Null)return false;
    return gd::gd_eq(a,b);
}
inline bool native_scalar_ne(const GdVal& a,const GdVal& b) {
    return !native_scalar_eq(a,b);
}
} // namespace gd

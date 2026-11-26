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
            // 与原gd_eq相同的纯身份分支，不读取对象内容或触发回调。
            case GdVal::Kind::Obj:return a.obj==b.obj;
            case GdVal::Kind::Dict:return a.dict==b.dict;
            case GdVal::Kind::ClassRef:return a.cls==b.cls;
            case GdVal::Kind::Enum:return a.en==b.en;
            case GdVal::Kind::FuncRef:return a.fr==b.fr;
            case GdVal::Kind::Rng:return a.rng==b.rng;
            case GdVal::Kind::Str:if(a.str==b.str)return true;break;
            case GdVal::Kind::Arr:if(a.arr==b.arr)return true;break;
            default:break;
        }
    }
    if(a.kind==GdVal::Kind::Null || b.kind==GdVal::Kind::Null)return false;
    return gd::gd_eq(a,b);
}
inline bool native_scalar_ne(const GdVal& a,const GdVal& b) {
    return !native_scalar_eq(a,b);
}
// 容器Float查找仍调用原比较体；保持其浮点异常和混合数值语义。
inline bool native_lookup_eq(const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Float || b.kind==GdVal::Kind::Float)return gd::gd_eq(a,b);
    return native_scalar_eq(a,b);
}
} // namespace gd

#pragma once
#include "native_event_kernel.hpp"

namespace gd {
void native_private_snapshot_hit(unsigned);
// Only generated private sequences use this view. Fallback arrays retain their
// original pointer and length snapshot; each element reads the current data.
struct NativePrivateIntegerView {
    GdArr* array;
    uint32_t length;
    explicit NativePrivateIntegerView(BattleCtx& ctx,const GdVal& input) {
        if(input.kind==GdVal::Kind::Int && input.i<=1024) {
            array=nullptr;length=input.i>0?static_cast<uint32_t>(input.i):0;
            if(ctx.native_resolved_collect)native_private_snapshot_hit(0);
        } else {
            if(ctx.native_resolved_collect)native_private_snapshot_hit(1);
            const auto sequence=gd_iter_seq(ctx.arena,input);
            array=sequence.kind==GdVal::Kind::Arr?sequence.arr:nullptr;
            length=array?array->len:0;
        }
    }
    GdVal at(uint32_t index)const {
        return array?array->data[index]:GdVal::from_int(index);
    }
};

// Capture text at the original observation point, before any callback. Large
// text retains eager allocation; no live source string survives in this view.
struct NativeEventIdentitySnapshot {
    char bytes[128];
    uint32_t length=0;
    bool pending=false;
    bool capture(const GdVal& identifier,const GdStr* delimiter,const GdVal& owner) {
        if(identifier.kind!=GdVal::Kind::Str || owner.kind!=GdVal::Kind::Int)return false;
        char digits[32];
        const auto converted=std::to_chars(digits,digits+sizeof(digits),owner.i);
        if(converted.ec!=std::errc{})return false;
        const uint32_t a=identifier.str?identifier.str->len:0;
        const uint32_t b=delimiter?delimiter->len:0;
        const uint32_t c=static_cast<uint32_t>(converted.ptr-digits);
        const uint64_t total=uint64_t{a}+b+c;
        if(total>sizeof(bytes))return false;
        if(a)std::memcpy(bytes,identifier.str->data,a);
        if(b)std::memcpy(bytes+a,delimiter->data,b);
        std::memcpy(bytes+a+b,digits,c);
        length=static_cast<uint32_t>(total);pending=true;return true;
    }
    GdVal value(BattleCtx& ctx,const GdVal& eager)const {
        return pending?GdVal::from_str(make_str(ctx.arena,bytes,length)):eager;
    }
};

inline bool native_try_event_identity_snapshot(BattleCtx& ctx,const GdVal& emitter,
        const GdStr* delimiter,GdVal& out,NativeEventIdentitySnapshot& snapshot) {
    const auto miss=[&]{if(ctx.native_resolved_collect)native_event_identity_hit(1);return false;};
    if(!ctx.native_resolved_dispatch)return miss();
    const auto descriptor_getter=native_event_identity_getter(ctx,emitter,8);
    const auto owner_getter=native_event_identity_getter(ctx,emitter,18);
    if(!descriptor_getter || !owner_getter)return miss();
    const auto descriptor=(emitter.obj->*descriptor_getter);
    const auto identifier_getter=native_event_identity_getter(ctx,descriptor,9);
    if(!identifier_getter)return miss();
    const auto owner=(emitter.obj->*owner_getter);
    const auto identifier=(descriptor.obj->*identifier_getter);
    const bool captured=snapshot.capture(identifier,delimiter,owner);
    if(!captured && !native_event_identity_string(ctx.arena,identifier,delimiter,owner,out))return miss();
    if(ctx.native_resolved_collect) {
        native_private_snapshot_hit(captured?2:3);
        native_event_identity_hit(0);
        native_inline_property_hit(0);native_inline_property_hit(0);native_inline_property_hit(0);
    }
    return true;
}
}

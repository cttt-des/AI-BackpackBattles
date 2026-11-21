#pragma once
#include "gd_rt.hpp"
#include <charconv>
#include <cstring>
#include <limits>

namespace gd {
// The input values have already been read. This primitive performs no object
// lookup, callback, identifier assignment, random draw or floating operation.
inline bool native_event_identity_string(BattleArena& arena,const GdVal& identifier,
        const GdStr* delimiter,const GdVal& owner,GdVal& out) {
    if(identifier.kind!=GdVal::Kind::Str || owner.kind!=GdVal::Kind::Int)return false;
    char digits[32];
    const auto converted=std::to_chars(digits,digits+sizeof(digits),owner.i);
    if(converted.ec!=std::errc{})return false;
    const uint32_t id_length=identifier.str?identifier.str->len:0;
    const uint32_t delimiter_length=delimiter?delimiter->len:0;
    const uint32_t digit_length=static_cast<uint32_t>(converted.ptr-digits);
    const uint64_t total=uint64_t{id_length}+delimiter_length+digit_length;
    if(total>=std::numeric_limits<uint32_t>::max())return false;
    auto* value=arena.make<GdStr>();
    const auto length=static_cast<uint32_t>(total);
    char* data=arena.alloc_array<char>(size_t{length}+1);
    if(id_length)std::memcpy(data,identifier.str->data,id_length);
    if(delimiter_length)std::memcpy(data+id_length,delimiter->data,delimiter_length);
    std::memcpy(data+id_length+delimiter_length,digits,digit_length);data[length]='\0';
    value->data=data;value->len=length;value->hash=fnv1a_32(data,length);
    out=GdVal::from_str(value);return true;
}
}

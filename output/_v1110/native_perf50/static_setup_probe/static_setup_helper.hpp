#pragma once
#include "gd_rt.hpp"
namespace gd {
void native_static_setup_hit(unsigned);
inline bool native_setup_empty_stack_tables(BattleCtx& ctx, const GdVal& powers, const GdVal& chances) {
    if (powers.kind != GdVal::Kind::Dict || chances.kind != GdVal::Kind::Dict || !powers.dict || !chances.dict || powers.dict == chances.dict) return false;
    auto* a = powers.dict; auto* b = chances.dict;
    if (a->len || a->cap || a->entries || a->buckets || a->bucket_cap || b->len || b->cap || b->entries || b->buckets || b->bucket_cap) return false;
    a->entries = ctx.arena.alloc_array<GdDictEntry>(16); a->cap = 16;
    b->entries = ctx.arena.alloc_array<GdDictEntry>(16); b->cap = 16;
    a->buckets = ctx.arena.alloc_array<int32_t>(32); a->bucket_cap = 32;
    b->buckets = ctx.arena.alloc_array<int32_t>(32); b->bucket_cap = 32;
    std::memset(a->buckets, -1, 32 * sizeof(int32_t));
    std::memset(b->buckets, -1, 32 * sizeof(int32_t));
    for (uint32_t i = 0; i < 11; ++i) {
        const auto key = GdVal::from_int(100 + i); const auto hash = gd_val_hash(key);
        a->entries[i] = {key, GdVal::from_float(1.0), hash}; ++a->len;
        b->entries[i] = {key, GdVal::from_float(0.0), hash}; ++b->len;
        uint32_t position = uint32_t(hash) & 31;
        while (a->buckets[position] >= 0) position = (position + 1) & 31;
        a->buckets[position] = b->buckets[position] = int32_t(i);
    }
    if (ctx.native_resolved_collect) native_static_setup_hit(0);
    return true;
}
}

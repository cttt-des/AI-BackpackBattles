"""Keep first native item timer headers next to the item, preserving reinit aliases."""
import argparse
import hashlib
from pathlib import Path

HASHES = {'gd_rt.hpp': 'cb81e3386a6b1b4dc6eeb37a5ecfddab2015eb4669cb6fba9b8800d8fec8dc4d', 'gen/hdrs/Gd__gd_core__CoreItem.hpp': '261d229ba4ddd85eb9a14fbfbce30242516d828b14aa55ae786315e2b8f168d8', 'gen/shards/shard_00.cpp': '91ea4375f5f20c5d755f2ed9f935505fe8149cf734782bf6e8463e80932c686c', 'engine_wrapper.cpp': '73a14c61c0d97cdf68d42b0a818fb5853b51d21739d97dd214c6c2328bff456b'}
OLD_ARENA = (
    'class BattleArena {\n'
    'public:\n'
    '    explicit BattleArena(size_t default_block_bytes = (1u << 20), bool thread_safe = false)\n'
    '        : block_bytes_(default_block_bytes),\n'
    '          mtx_(thread_safe ? new std::mutex() : nullptr) {}\n'
    '\n'
    '    ~BattleArena() {\n'
    '        for (auto& b : blocks_) {\n'
    '            delete[] b.ptr;\n'
    '        }\n'
    '        delete mtx_;\n'
    '    }\n'
    '\n'
    '    BattleArena(const BattleArena&) = delete;\n'
    '    BattleArena& operator=(const BattleArena&) = delete;\n'
    '\n'
    '    void reset() {\n'
    '        std::unique_lock<std::mutex> lk;\n'
    '        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n'
    '        for (auto& b : blocks_) b.used = 0;\n'
    '        cur_ = 0;\n'
    '    }\n'
    '\n'
    '    void* alloc_raw(size_t bytes, size_t align = 8) {\n'
    '        std::unique_lock<std::mutex> lk;\n'
    '        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n'
    '        if (bytes == 0) bytes = 1;\n'
    '        while (cur_ < blocks_.size()) {\n'
    '            ArenaBlock& b = blocks_[cur_];\n'
    '            size_t off = (b.used + (align - 1)) & ~(align - 1);\n'
    '            if (off + bytes <= b.cap) {\n'
    '                b.used = off + bytes;\n'
    '                return b.ptr + off;\n'
    '            }\n'
    '            cur_++;\n'
    '        }\n'
    '        size_t sz = bytes > block_bytes_ ? (bytes + align) : block_bytes_;\n'
    '        ArenaBlock nb;\n'
    '        nb.ptr = new uint8_t[sz];\n'
    '        nb.cap = sz;\n'
    '        nb.used = bytes;\n'
    '        blocks_.push_back(nb);\n'
    '        cur_ = blocks_.size() - 1;\n'
    '        return nb.ptr;\n'
    '    }\n'
    '\n'
    '    template <typename T, typename... Args>\n'
    '    T* make(Args&&... args) {\n'
    '        void* mem = alloc_raw(sizeof(T), alignof(T));\n'
    '        return new (mem) T(static_cast<Args&&>(args)...);\n'
    '    }\n'
    '\n'
    '    template <typename T>\n'
    '    T* alloc_array(size_t count) {\n'
    '        if (count == 0) return nullptr;\n'
    '        return static_cast<T*>(alloc_raw(sizeof(T) * count, alignof(T)));\n'
    '    }\n'
    '\n'
    'private:\n'
    '    size_t block_bytes_;\n'
    '    std::vector<ArenaBlock> blocks_;\n'
    '    size_t cur_ = 0;\n'
    '    std::mutex* mtx_ = nullptr;\n'
    '};\n'
)
NEW_ARENA = (
    'class BattleArena {\n'
    'public:\n'
    '    explicit BattleArena(size_t default_block_bytes = (1u << 20), bool thread_safe = false)\n'
    '        : block_bytes_(default_block_bytes),\n'
    '          mtx_(thread_safe ? new std::mutex() : nullptr) {}\n'
    '\n'
    '    ~BattleArena() {\n'
    '        for (auto& b : blocks_) {\n'
    '            delete[] b.ptr;\n'
    '        }\n'
    '        delete mtx_;\n'
    '    }\n'
    '\n'
    '    BattleArena(const BattleArena&) = delete;\n'
    '    BattleArena& operator=(const BattleArena&) = delete;\n'
    '\n'
    '    void reset() {\n'
    '        std::unique_lock<std::mutex> lk;\n'
    '        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n'
    '        for (auto& b : blocks_) b.used = 0;\n'
    '        cur_ = 0;\n'
    '    }\n'
    '\n'
    '    void* alloc_raw(size_t bytes, size_t align = 8) {\n'
    '        std::unique_lock<std::mutex> lk;\n'
    '        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n'
    '        if (bytes == 0) bytes = 1;\n'
    '        while (cur_ < blocks_.size()) {\n'
    '            ArenaBlock& b = blocks_[cur_];\n'
    '            size_t off = (b.used + (align - 1)) & ~(align - 1);\n'
    '            if (align > alignof(std::max_align_t)) {\n'
    '                const auto base = reinterpret_cast<uintptr_t>(b.ptr);\n'
    '                off = ((base + b.used + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n'
    '            }\n'
    '            if (off + bytes <= b.cap) {\n'
    '                b.used = off + bytes;\n'
    '                return b.ptr + off;\n'
    '            }\n'
    '            cur_++;\n'
    '        }\n'
    '        size_t sz = bytes > block_bytes_ ? (bytes + align) : block_bytes_;\n'
    '        if (align > alignof(std::max_align_t) && bytes + align - 1 > sz) sz = bytes + align - 1;\n'
    '        ArenaBlock nb;\n'
    '        nb.ptr = new uint8_t[sz];\n'
    '        nb.cap = sz;\n'
    '        size_t initial_offset = 0;\n'
    '        if (align > alignof(std::max_align_t)) {\n'
    '            const auto base = reinterpret_cast<uintptr_t>(nb.ptr);\n'
    '            initial_offset = ((base + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n'
    '        }\n'
    '        nb.used = initial_offset + bytes;\n'
    '        blocks_.push_back(nb);\n'
    '        cur_ = blocks_.size() - 1;\n'
    '        return nb.ptr + initial_offset;\n'
    '    }\n'
    '\n'
    '    template <typename T, typename... Args>\n'
    '    T* make(Args&&... args) {\n'
    '        void* mem = alloc_raw(sizeof(T), alignof(T));\n'
    '        return new (mem) T(static_cast<Args&&>(args)...);\n'
    '    }\n'
    '\n'
    '    template <typename T>\n'
    '    T* alloc_array(size_t count) {\n'
    '        if (count == 0) return nullptr;\n'
    '        return static_cast<T*>(alloc_raw(sizeof(T) * count, alignof(T)));\n'
    '    }\n'
    '\n'
    '    bool owns_storage(const void* pointer, size_t bytes) const {\n'
    '        std::unique_lock<std::mutex> lk;\n'
    '        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n'
    '        const auto address = reinterpret_cast<uintptr_t>(pointer);\n'
    '        for (const auto& block : blocks_) {\n'
    '            const auto base = reinterpret_cast<uintptr_t>(block.ptr);\n'
    '            if (address >= base && address - base <= block.used &&\n'
    '                    bytes <= block.used - (address - base)) return true;\n'
    '        }\n'
    '        return false;\n'
    '    }\n'
    '\n'
    'private:\n'
    '    size_t block_bytes_;\n'
    '    std::vector<ArenaBlock> blocks_;\n'
    '    size_t cur_ = 0;\n'
    '    std::mutex* mtx_ = nullptr;\n'
    '};\n'
)
OLD_DECL = '    gd::GdVal f_timers;\n'
NEW_DECL = (
    '    alignas(64) gd::GdVal f_timers;\n'
    '    gd::GdArr native_timer_header_;\n'
    '    bool native_timer_header_used_ = false;\n'
)
OLD_ASSIGN = '    this->f_timers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n'
NEW_ASSIGN = (
    '    // Native bridge items live until the battle arena resets. Other contexts keep arena headers.\n'
    '    if (gd_ctx.native_inline_timer_headers && !this->native_timer_header_used_ &&\n'
    '            gd_ctx.arena.owns_storage(this, sizeof(*this))) {\n'
    '        this->native_timer_header_used_ = true;\n'
    '        this->f_timers = gd::GdVal::from_arr(&this->native_timer_header_);\n'
    '    } else {\n'
    '        this->f_timers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n'
    '    }\n'
)
FLAG = (
    '    // Internal bridge opt-in: item objects and their first timer arrays share arena lifetime.\n'
    '    // Outside the bridge, independent arena headers preserve escaped array references.\n'
    '    bool native_inline_timer_headers = false;\n'
    '\n'
)
CTOR = '    explicit BattleCtx(size_t arena_bytes = (1u << 20)) : arena(arena_bytes) {}\n'
RESET = '    void reset_for_battle(uint64_t seed) {\n'
RESET_FLAG = '        native_inline_timer_headers = false;\n'
WRAPPER = '    battle.reset_for_battle(opts.seed);\n'
WRAPPER_FLAG = '    battle.native_inline_timer_headers = true;\n'


def optimize(native):
    sources={name:(native/name).read_text("utf8") for name in HASHES}
    restored=dict(sources)
    restored["gd_rt.hpp"]=restored["gd_rt.hpp"].removeprefix("#include <cstddef>\n")
    restored["gd_rt.hpp"]=restored["gd_rt.hpp"].replace(NEW_ARENA,OLD_ARENA,1).replace(FLAG, "", 1).replace(RESET_FLAG, "", 1)
    restored["gen/hdrs/Gd__gd_core__CoreItem.hpp"]=restored["gen/hdrs/Gd__gd_core__CoreItem.hpp"].replace(NEW_DECL,OLD_DECL,1)
    restored["gen/shards/shard_00.cpp"]=restored["gen/shards/shard_00.cpp"].replace(NEW_ASSIGN,OLD_ASSIGN,1)
    restored["engine_wrapper.cpp"]=restored["engine_wrapper.cpp"].replace(WRAPPER_FLAG,"",1)
    for name,body in restored.items():
        if hashlib.sha256(body.encode()).hexdigest()!=HASHES[name]:
            raise ValueError(f"The verified source changed: {name}")
    sources["gd_rt.hpp"]="#include <cstddef>\n"+restored["gd_rt.hpp"].replace(OLD_ARENA,NEW_ARENA,1).replace(CTOR,FLAG+CTOR,1).replace(RESET,RESET+RESET_FLAG,1)
    sources["gen/hdrs/Gd__gd_core__CoreItem.hpp"]=restored["gen/hdrs/Gd__gd_core__CoreItem.hpp"].replace(OLD_DECL,NEW_DECL,1)
    sources["gen/shards/shard_00.cpp"]=restored["gen/shards/shard_00.cpp"].replace(OLD_ASSIGN,NEW_ASSIGN,1)
    sources["engine_wrapper.cpp"]=restored["engine_wrapper.cpp"].replace(WRAPPER,WRAPPER+WRAPPER_FLAG,1)
    for name,body in sources.items():
        path=native/name
        if path.read_bytes()!=body.encode("utf8"):
            path.write_text(body,encoding="utf8",newline="\n")
    print("Placed first native timer headers beside item fields; reinit and external contexts retain independent headers",flush=True)

if __name__=="__main__":
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("native",type=Path)
    optimize(parser.parse_args().native)

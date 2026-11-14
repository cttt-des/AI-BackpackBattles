#pragma once
// C++20 GDScript 3.6 Headless Runtime for Backpack Battles (Apple M4 / arm64)
// Matches gd_core_py/_rt.py bit-for-bit (IEEE-754 rounding, PCG32, Godot 3.6 containers & math).

#pragma STDC FP_CONTRACT OFF

#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

#include "builtin_syms.hpp"

namespace gd {

// ─────────────────────────── Symbol & Class IDs ───────────────────────────
using SymId = uint32_t;
using ClsId = uint32_t;

static constexpr SymId SYM_NONE = 0;
static constexpr ClsId CLS_NONE = 0;

enum BuiltinSym : SymId {
    SYM_BUILTIN_ZERO = 0,
#define GD_X_ENUM(name, str) name,
    GD_BUILTIN_SYMS(GD_X_ENUM)
#undef GD_X_ENUM
    SYM_BUILTIN_END
};

void register_sym(SymId id, std::string_view sv);

struct GdVal;
struct GdStr;
struct GdArr;
struct GdDict;
struct GdObj;
struct GdFuncRef;
struct GdRng;
struct GdEnum;
struct GdClassMeta;
struct BattleCtx;

// ─────────────────────────── Per-Battle Bump Arena ───────────────────────────
struct ArenaBlock {
    uint8_t* ptr = nullptr;
    size_t cap = 0;
    size_t used = 0;
};

class BattleArena {
public:
    explicit BattleArena(size_t default_block_bytes = (1u << 20), bool thread_safe = false)
        : block_bytes_(default_block_bytes),
          mtx_(thread_safe ? new std::mutex() : nullptr) {}

    ~BattleArena() {
        for (auto& b : blocks_) {
            delete[] b.ptr;
        }
        delete mtx_;
    }

    BattleArena(const BattleArena&) = delete;
    BattleArena& operator=(const BattleArena&) = delete;

    void reset() {
        std::unique_lock<std::mutex> lk;
        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);
        for (auto& b : blocks_) b.used = 0;
        cur_ = 0;
    }

    void* alloc_raw(size_t bytes, size_t align = 8) {
        std::unique_lock<std::mutex> lk;
        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);
        if (bytes == 0) bytes = 1;
        while (cur_ < blocks_.size()) {
            ArenaBlock& b = blocks_[cur_];
            size_t off = (b.used + (align - 1)) & ~(align - 1);
            if (off + bytes <= b.cap) {
                b.used = off + bytes;
                return b.ptr + off;
            }
            cur_++;
        }
        size_t sz = bytes > block_bytes_ ? (bytes + align) : block_bytes_;
        ArenaBlock nb;
        nb.ptr = new uint8_t[sz];
        nb.cap = sz;
        nb.used = bytes;
        blocks_.push_back(nb);
        cur_ = blocks_.size() - 1;
        return nb.ptr;
    }

    template <typename T, typename... Args>
    T* make(Args&&... args) {
        void* mem = alloc_raw(sizeof(T), alignof(T));
        return new (mem) T(static_cast<Args&&>(args)...);
    }

    template <typename T>
    T* alloc_array(size_t count) {
        if (count == 0) return nullptr;
        return static_cast<T*>(alloc_raw(sizeof(T) * count, alignof(T)));
    }

private:
    size_t block_bytes_;
    std::vector<ArenaBlock> blocks_;
    size_t cur_ = 0;
    std::mutex* mtx_ = nullptr;
};

BattleArena& static_arena();

// ─────────────────────────── Strings ───────────────────────────
struct GdStr {
    const char* data;
    uint32_t len;
    uint32_t hash;
};

inline uint32_t fnv1a_32(const char* s, uint32_t len) {
    uint32_t h = 2166136261u;
    for (uint32_t i = 0; i < len; ++i) {
        h ^= static_cast<uint8_t>(s[i]);
        h *= 16777619u;
    }
    return h;
}

const GdStr* make_str(BattleArena& arena, const char* s, uint32_t len);
const GdStr* make_str(BattleArena& arena, std::string_view sv);
const GdStr* make_static_str(std::string_view sv);
const GdStr* str_concat(BattleArena& arena, const GdStr* a, const GdStr* b);
SymId intern_sym(std::string_view sv);
const char* sym_name(SymId id);

// ─────────────────────────── Vec2 & Color ───────────────────────────
struct GdVec2 {
    double x = 0.0;
    double y = 0.0;

    bool operator==(const GdVec2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const GdVec2& o) const { return !(*this == o); }
    GdVec2 operator+(const GdVec2& o) const { return {x + o.x, y + o.y}; }
    GdVec2 operator-(const GdVec2& o) const { return {x - o.x, y - o.y}; }
    GdVec2 operator-() const { return {-x, -y}; }
    GdVec2 operator*(const GdVec2& o) const { return {x * o.x, y * o.y}; }
    GdVec2 operator*(double s) const { return {x * s, y * s}; }
    GdVec2 operator/(const GdVec2& o) const { return {x / o.x, y / o.y}; }
    GdVec2 operator/(double s) const { return {x / s, y / s}; }
};

struct GdColor {
    double r = 0.0, g = 0.0, b = 0.0, a = 1.0;
    bool operator==(const GdColor& o) const {
        return r == o.r && g == o.g && b == o.b && a == o.a;
    }
};

// ─────────────────────────── Tagged Variant (GdVal) ───────────────────────────
struct alignas(8) GdVal {
    enum class Kind : uint8_t {
        Null = 0,
        Bool = 1,
        Int = 2,
        Float = 3,
        Vec2 = 4,
        Color = 5,
        Str = 6,
        Arr = 7,
        Dict = 8,
        Obj = 9,
        ClassRef = 10,
        Enum = 11,
        FuncRef = 12,
        Rng = 13,
    };

    Kind kind = Kind::Null;
    union {
        bool b;
        int64_t i;
        double f;
        GdVec2 v2;
        GdColor* col;
        const GdStr* str;
        GdArr* arr;
        GdDict* dict;
        GdObj* obj;
        const GdClassMeta* cls;
        const GdEnum* en;
        GdFuncRef* fr;
        GdRng* rng;
    };

    GdVal() : kind(Kind::Null), i(0) {}
    static GdVal null() { return GdVal(); }
    static GdVal from_bool(bool v) { GdVal r; r.kind = Kind::Bool; r.b = v; return r; }
    static GdVal from_int(int64_t v) { GdVal r; r.kind = Kind::Int; r.i = v; return r; }
    static GdVal from_float(double v) { GdVal r; r.kind = Kind::Float; r.f = v; return r; }
    static GdVal from_vec2(double x, double y) {
        GdVal r; r.kind = Kind::Vec2; r.v2 = {x, y}; return r;
    }
    static GdVal from_vec2(GdVec2 v) { GdVal r; r.kind = Kind::Vec2; r.v2 = v; return r; }
    static GdVal from_str(const GdStr* s) { GdVal r; r.kind = Kind::Str; r.str = s; return r; }
    static GdVal from_cstr(BattleArena& arena, const char* s) {
        return from_str(make_str(arena, std::string_view(s)));
    }
    static GdVal from_arr(GdArr* a) { GdVal r; r.kind = Kind::Arr; r.arr = a; return r; }
    static GdVal from_dict(GdDict* d) { GdVal r; r.kind = Kind::Dict; r.dict = d; return r; }
    static GdVal from_obj(GdObj* o) {
        if (!o) return null();
        GdVal r; r.kind = Kind::Obj; r.obj = o; return r;
    }
    static GdVal from_cls(const GdClassMeta* c) {
        if (!c) return null();
        GdVal r; r.kind = Kind::ClassRef; r.cls = c; return r;
    }
    static GdVal from_enum(const GdEnum* e) {
        if (!e) return null();
        GdVal r; r.kind = Kind::Enum; r.en = e; return r;
    }
    static GdVal from_color(GdColor* c) { GdVal r; r.kind = Kind::Color; r.col = c; return r; }
    static GdVal from_funcref(GdFuncRef* fr) { GdVal r; r.kind = Kind::FuncRef; r.fr = fr; return r; }
    static GdVal from_rng(GdRng* rng) { GdVal r; r.kind = Kind::Rng; r.rng = rng; return r; }

    bool is_null() const { return kind == Kind::Null; }
    bool is_num() const { return kind == Kind::Int || kind == Kind::Float || kind == Kind::Bool; }

    int64_t as_int() const {
        switch (kind) {
            case Kind::Int: return i;
            case Kind::Float: return static_cast<int64_t>(f);
            case Kind::Bool: return b ? 1 : 0;
            default: return 0;
        }
    }
    double as_float() const {
        switch (kind) {
            case Kind::Float: return f;
            case Kind::Int: return static_cast<double>(i);
            case Kind::Bool: return b ? 1.0 : 0.0;
            default: return 0.0;
        }
    }
};

// ─────────────────────────── Equality, Hash, Truth, String ───────────────────────────
bool gd_truth(const GdVal& v);
bool gd_eq(const GdVal& a, const GdVal& b);
inline bool gd_ne(const GdVal& a, const GdVal& b) { return !gd_eq(a, b); }
bool gd_lt(const GdVal& a, const GdVal& b);
bool gd_le(const GdVal& a, const GdVal& b);
inline bool gd_gt(const GdVal& a, const GdVal& b) { return gd_lt(b, a); }
inline bool gd_ge(const GdVal& a, const GdVal& b) { return gd_le(b, a); }
uint64_t gd_val_hash(const GdVal& v);
const GdStr* gd_to_str(BattleArena& arena, const GdVal& v);
GdVal gd_coerce_int(const GdVal& v);
GdVal gd_coerce_float(const GdVal& v);
GdVal gd_coerce_bool(const GdVal& v);

// ─────────────────────────── Math & Builtins ───────────────────────────
inline double f32_d(double x) {
    return static_cast<double>(static_cast<float>(x));
}
GdVal gd_add(BattleCtx& ctx, const GdVal& a, const GdVal& b);
GdVal gd_sub(const GdVal& a, const GdVal& b);
GdVal gd_mul(const GdVal& a, const GdVal& b);
GdVal gd_div(BattleCtx& ctx, const GdVal& a, const GdVal& b);
GdVal gd_mod(BattleCtx& ctx, const GdVal& a, const GdVal& b);
GdVal gd_neg(const GdVal& a);
GdVal gd_pos(const GdVal& a);
GdVal gd_bitand(const GdVal& a, const GdVal& b);
GdVal gd_bitor(const GdVal& a, const GdVal& b);
GdVal gd_bitxor(const GdVal& a, const GdVal& b);
GdVal gd_bitnot(const GdVal& a);
GdVal gd_shl(const GdVal& a, const GdVal& b);
GdVal gd_shr(const GdVal& a, const GdVal& b);

GdVal gd_abs(const GdVal& x);
GdVal gd_min(const GdVal& a, const GdVal& b);
GdVal gd_max(const GdVal& a, const GdVal& b);
GdVal gd_clamp(const GdVal& v, const GdVal& lo, const GdVal& hi);
GdVal gd_floor(const GdVal& x);
GdVal gd_ceil(const GdVal& x);
GdVal gd_round(const GdVal& x);
GdVal gd_stepify(const GdVal& v, const GdVal& step);
GdVal gd_snapped(const GdVal& v, const GdVal& step);
GdVal gd_fmod(const GdVal& x, const GdVal& y);
GdVal gd_posmod(const GdVal& x, const GdVal& y);
GdVal gd_sqrt(const GdVal& x);
GdVal gd_pow(const GdVal& x, const GdVal& y);
GdVal gd_sign(const GdVal& x);
GdVal gd_lerp(const GdVal& a, const GdVal& b, const GdVal& t);
GdVal gd_inverse_lerp(const GdVal& a, const GdVal& b, const GdVal& v);
GdVal gd_smoothstep(const GdVal& a, const GdVal& b, const GdVal& v);
GdVal gd_move_toward(const GdVal& f, const GdVal& t, const GdVal& d);
GdVal gd_wrapf(const GdVal& v, const GdVal& mn, const GdVal& mx);
GdVal gd_wrapi(const GdVal& v, const GdVal& mn, const GdVal& mx);
GdVal gd_deg2rad(const GdVal& d);
GdVal gd_rad2deg(const GdVal& r);
bool gd_is_equal_approx(const GdVal& a, const GdVal& b);
int64_t gd_typeof(const GdVal& v);
GdVal gd_range(BattleArena& arena, const GdVal* args, int argc);
GdVal gd_str_fn(BattleArena& arena, const GdVal* args, int argc);
GdVal gd_fmt(BattleArena& arena, const GdVal& fmt, const GdVal& args);
GdVal gd_in(const GdVal& needle, const GdVal& haystack);
GdVal gd_iter_seq(BattleArena& arena, const GdVal& x);

// ─────────────────────────── Containers ───────────────────────────
struct GdArr {
    GdVal* data = nullptr;
    uint32_t len = 0;
    uint32_t cap = 0;
    bool is_pool_real = false;

    static GdArr* create(BattleArena& arena, uint32_t reserve_cap = 0);
    static GdArr* create_pool_real(BattleArena& arena, const GdVal* src = nullptr) {
        GdArr* a = create(arena, (src && src->kind == GdVal::Kind::Arr && src->arr) ? src->arr->len : 0);
        a->is_pool_real = true;
        if (src && src->kind == GdVal::Kind::Arr && src->arr) {
            for (uint32_t i = 0; i < src->arr->len; ++i) a->push_back(arena, src->arr->data[i]);
        }
        return a;
    }
    static GdArr* from_init(BattleArena& arena, std::initializer_list<GdVal> vals);
    void push_back(BattleArena& arena, const GdVal& v);
    void insert_at(BattleArena& arena, int64_t pos, const GdVal& v);
    void append_array(BattleArena& arena, const GdArr* o);
    GdVal pop_front();
    GdVal pop_back();
    GdVal pop_at(int64_t idx);
    void remove_at(int64_t idx);
    void erase_val(const GdVal& v);
    int64_t find_val(const GdVal& v, int64_t from = 0) const;
    bool has_val(const GdVal& v) const { return find_val(v) >= 0; }
    void resize(BattleArena& arena, int64_t n);
    void fill(const GdVal& v);
    void invert();
    int64_t count_val(const GdVal& v) const;
    GdArr* duplicate(BattleArena& arena, bool deep = false) const;
    GdVal get_idx(int64_t idx) const;
    void set_idx(int64_t idx, const GdVal& v);
};

struct GdDictEntry {
    GdVal key;
    GdVal val;
    uint64_t hash;
};

struct GdDict {
    GdDictEntry* entries = nullptr;
    uint32_t len = 0;
    uint32_t cap = 0;
    int32_t* buckets = nullptr;
    uint32_t bucket_cap = 0;

    static GdDict* create(BattleArena& arena, uint32_t reserve_cap = 0);
    int32_t find_index(const GdVal& key, uint64_t h) const;
    int32_t find_index(const GdVal& key) const { return find_index(key, gd_val_hash(key)); }
    bool has(const GdVal& key) const { return find_index(key) >= 0; }
    GdVal get(const GdVal& key, const GdVal& def = GdVal::null()) const;
    void set(BattleArena& arena, const GdVal& key, const GdVal& val);
    void erase(const GdVal& key);
    void clear();
    GdArr* keys(BattleArena& arena) const;
    GdArr* values(BattleArena& arena) const;
    GdDict* duplicate(BattleArena& arena, bool deep = false) const;
    void invert(BattleArena& arena);

private:
    void rebuild_index(BattleArena& arena);
};

struct GdEnum {
    const char* name;
    struct KV { const char* key; int64_t val; };
    const KV* items;
    uint32_t len;

    bool get(std::string_view k, int64_t& out) const;
    bool has(std::string_view k) const { int64_t tmp; return get(k, tmp); }
    GdArr* keys_arr(BattleArena& arena) const;
    GdArr* values_arr(BattleArena& arena) const;
};

// ─────────────────────────── PCG32 & RandomNumberGenerator ───────────────────────────
struct GdPCG32 {
    static constexpr uint64_t MULT = 6364136223846793005ULL;
    static constexpr uint64_t DEFAULT_INC = 1442695040888963407ULL;
    uint64_t state = 0;
    uint64_t inc = (DEFAULT_INC << 1ULL) | 1ULL;

    void srandom(uint64_t init_state, uint64_t init_seq) {
        state = 0;
        inc = (init_seq << 1ULL) | 1ULL;
        next_u32();
        state += init_state;
        next_u32();
    }

    uint32_t next_u32() {
        uint64_t old = state;
        state = old * MULT + inc;
        uint32_t xorshifted = static_cast<uint32_t>(((old >> 18u) ^ old) >> 27u);
        uint32_t rot = static_cast<uint32_t>(old >> 59u);
        return (xorshifted >> rot) | (xorshifted << ((0u - rot) & 31u));
    }
};

struct GdRng {
    static constexpr uint64_t DEFAULT_SEED = 12047754176567800795ULL;
    GdPCG32 pcg;
    uint64_t current_seed = DEFAULT_SEED;
    uint64_t inc = GdPCG32::DEFAULT_INC;
    bool randomized_flag = false;

    explicit GdRng(uint64_t p_seed = DEFAULT_SEED, uint64_t p_inc = GdPCG32::DEFAULT_INC)
        : inc(p_inc) {
        set_seed(p_seed);
    }

    void set_seed(uint64_t s) {
        current_seed = s;
        pcg.srandom(current_seed, inc);
    }
    uint64_t get_seed() const { return current_seed; }
    void set_state(uint64_t st) { pcg.state = st; }
    uint64_t get_state() const { return pcg.state; }

    uint32_t randi() { return pcg.next_u32(); }

    int64_t randi_range(int64_t from, int64_t to) {
        uint32_t ret = pcg.next_u32();
        if (to < from) {
            uint64_t span = static_cast<uint64_t>(from - to) + 1ULL;
            return static_cast<int64_t>(ret % span) + to;
        }
        uint64_t span = static_cast<uint64_t>(to - from) + 1ULL;
        return static_cast<int64_t>(ret % span) + from;
    }

    double randf() {
        uint32_t proto = pcg.next_u32();
        if (proto == 0u) return 0.0;
        int clz = __builtin_clz(proto);
        float mantissa = static_cast<float>(pcg.next_u32() | 0x80000001u);
        return static_cast<double>(std::ldexp(mantissa, -32 - clz));
    }

    double randd() {
        uint32_t proto = pcg.next_u32();
        if (proto == 0u) return 0.0;
        int clz = __builtin_clz(proto);
        uint64_t hi = pcg.next_u32();
        uint64_t lo = pcg.next_u32();
        uint64_t sig = ((hi << 32u) | lo) | 0x8000000000000001ULL;
        return std::ldexp(static_cast<double>(sig), -64 - clz);
    }

    double randf_range(double from, double to) {
        float rf = static_cast<float>(randf());
        float f = static_cast<float>(from);
        float t = static_cast<float>(to);
        float d = t - f;
        float prod = rf * d;
        float res = prod + f;
        return static_cast<double>(res);
    }

    void randomize() {
        randomized_flag = true;
        set_seed(0x9e3779b97f4a7c15ULL ^ (pcg.state + 1));
    }
};

// ─────────────────────────── FuncRef & Object Model ───────────────────────────
struct GdFuncRef {
    GdObj* instance = nullptr;
    SymId method = SYM_NONE;
    GdArr* binds = nullptr;

    bool is_valid() const;
    GdVal call_func(BattleCtx& ctx, const GdVal* args, int argc) const;
    GdVal call_funcv(BattleCtx& ctx, const GdVal& args_arr) const;
};

struct GdConn {
    SymId signal = SYM_NONE;
    GdObj* target = nullptr;
    SymId method = SYM_NONE;
    GdArr* binds = nullptr;
    GdConn* next = nullptr;
};

struct GdClassMeta {
    ClsId id = CLS_NONE;
    const char* class_name = "";
    const char* res_path = "";
    const GdClassMeta* base = nullptr;
    bool is_behavior_tree = false;
    GdObj* (*alloc_fn)(BattleCtx& ctx) = nullptr;
    bool (*get_static_prop)(SymId prop, GdVal& out) = nullptr;
    bool (*call_static_fn)(BattleCtx& ctx, SymId fn, const GdVal* args, int argc, GdVal& out) = nullptr;

    bool is_subclass_of(const GdClassMeta* target) const {
        for (const GdClassMeta* c = this; c; c = c->base) {
            if (c == target) return true;
        }
        return false;
    }
};

class GdObj {
public:
    explicit GdObj(BattleCtx* ctx) : rt_ctx_(ctx) {}
    virtual ~GdObj() = default;

    BattleCtx* rt_ctx_ = nullptr;
    uint64_t gid_ = 0;
    uint64_t gid_epoch_ = 0;
    GdConn* conns_head_ = nullptr;

    virtual const GdClassMeta* meta() const = 0;
    virtual void init_fields(BattleCtx& ctx) {}
    virtual bool get_prop(SymId prop, GdVal& out) const { return false; }
    virtual bool set_prop(BattleCtx& ctx, SymId prop, const GdVal& val) { return false; }
    virtual bool has_own_method(SymId m) const { return false; }
    virtual bool call_method(BattleCtx& ctx, SymId m, const GdVal* args, int argc, GdVal& out) {
        return false;
    }

    uint64_t get_instance_id();
    void connect_signal(BattleArena& arena, SymId sig, GdObj* target, SymId method, GdArr* binds = nullptr);
    void disconnect_signal(SymId sig, GdObj* target, SymId method);
    bool is_connected_signal(SymId sig, GdObj* target, SymId method) const;
    void emit_signal(BattleCtx& ctx, SymId sig, const GdVal* args, int argc);
};

// ─────────────────────────── Battle Context ───────────────────────────
struct BattleCtx {
    BattleArena arena;
    GdRng math_rng;
    uint64_t next_gid = 1;
    uint64_t gid_epoch = 1;

    // Fast counters populated by C++ hooks subclass without Python overhead
    uint32_t event_count = 0;
    double player_damage_dealt = 0.0;
    double opponent_damage_dealt = 0.0;
    double player_healing_done = 0.0;
    double opponent_healing_done = 0.0;
    int32_t player_crits = 0;
    int32_t opponent_crits = 0;
    int32_t player_misses = 0;
    int32_t opponent_misses = 0;

    explicit BattleCtx(size_t arena_bytes = (1u << 20)) : arena(arena_bytes) {}

    void reset_for_battle(uint64_t seed) {
        arena.reset();
        bind_battle(seed);
        event_count = 0;
        player_damage_dealt = 0.0;
        opponent_damage_dealt = 0.0;
        player_healing_done = 0.0;
        opponent_healing_done = 0.0;
        player_crits = 0;
        opponent_crits = 0;
        player_misses = 0;
        opponent_misses = 0;
    }

    void bind_battle(uint64_t seed) {
        math_rng = GdRng(seed);
        next_gid = 1;
        gid_epoch += 1;
    }
};

// ─────────────────────────── Class Registry & Dispatch Helpers ───────────────────────────
void register_class(const GdClassMeta* meta);
const GdClassMeta* find_class(std::string_view name_or_path);
const GdClassMeta* find_class_by_id(ClsId id);
GdVal construct_class(BattleCtx& ctx, const GdClassMeta* cls, const GdVal* args, int argc);
GdVal load_resource(std::string_view path);
GdVal get_named_color(std::string_view name);
GdVal make_color_from_args(const GdVal* args, int argc);

// Uniform Variant property / subscript / call helpers
GdVal get_prop(BattleCtx& ctx, const GdVal& recv, SymId prop);
void set_prop(BattleCtx& ctx, GdVal& recv, SymId prop, const GdVal& val);
GdVal get_index(BattleCtx& ctx, const GdVal& recv, const GdVal& key);
void set_index(BattleCtx& ctx, GdVal& recv, const GdVal& key, const GdVal& val);
GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId method, const GdVal* args, int argc);
GdVal call_method_dyn(BattleCtx& ctx, const GdVal& recv, const GdVal& method_name, const GdVal* args, int argc);
bool gd_is_type(const GdVal& v, const GdClassMeta* cls);
bool gd_is_builtin(const GdVal& v, int type_tag);
void godot_sort_custom_items(BattleCtx& ctx, GdArr* arr);
void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method);
void shuffle_array(BattleCtx& ctx, GdArr* arr);
GdVal pick_random_array(BattleCtx& ctx, const GdArr* arr);

}  // namespace gd

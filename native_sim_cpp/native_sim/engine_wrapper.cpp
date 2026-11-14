#pragma STDC FP_CONTRACT OFF

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

#include "gd_rt.hpp"
#include "gen/class_metas.hpp"
#include "gen/sym_ids.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemBook.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"

extern "C" void gd_init_all_classes();

namespace {

// ─────────────────────────── Cached Symbol IDs ───────────────────────────
struct WrapperSyms {
    gd::SymId logEvent = 0;
    gd::SymId type = 0;
    gd::SymId origin = 0;
    gd::SymId target = 0;
    gd::SymId params = 0;
    gd::SymId damage = 0;
    gd::SymId amount = 0;
    gd::SymId _readyInit = 0;
    gd::SymId setup = 0;
    gd::SymId addItem = 0;
    gd::SymId setCraftedEffects = 0;
    gd::SymId setGem = 0;
    gd::SymId setFaceDirectionInstant = 0;
    gd::SymId crafted_instance = 0;
    gd::SymId triggerType = 0;
    gd::SymId stackType = 0;
    gd::SymId health = 0;
    gd::SymId stamina = 0;
    gd::SymId regen = 0;
    gd::SymId gold = 0;
    gd::SymId b_key = 0;
    gd::SymId i_key = 0;
    gd::SymId c_key = 0;
    gd::SymId getPlayer = 0;
    gd::SymId character = 0;
    gd::SymId timestamp = 0;
    gd::SymId id = 0;
    gd::SymId parentEvent = 0;
    gd::SymId ownerType = 0;
    gd::SymId descriptor = 0;
    gd::SymId identifier = 0;
    const gd::GdStr* s_damage = nullptr;
    const gd::GdStr* s_amount = nullptr;
    const gd::GdStr* s_health = nullptr;
    const gd::GdStr* s_stamina = nullptr;
    const gd::GdStr* s_regen = nullptr;
    const gd::GdStr* s_gold = nullptr;
};

static WrapperSyms g_syms;
static std::once_flag g_init_once;

// ─────────────────────────── Static Item & Character Registry ───────────────────────────
struct OrigRecipeProto {
    const gd::GdStr* base = nullptr;
    std::vector<const gd::GdStr*> ingredients;
    std::vector<bool> consumed;
};

struct ItemProto {
    int32_t id = -1;
    std::string key;
    const gd::GdClassMeta* cls = nullptr;
    int32_t sockets = 0;

    // Descriptor fields
    const gd::GdStr* name = nullptr;
    const gd::GdStr* identifier = nullptr;
    int32_t minDam = 0;
    int32_t maxDam = 0;
    double staminaCost = 0.0;
    int32_t block = 0;
    double cd = 0.0;
    double accuracy = 100.0;
    bool canActivate = true;
    double chance = 0.0;
    double chance2 = 0.0;
    double shopChance = 0.0;
    int64_t tags = 0;
    int64_t physics = 0;
    int32_t rarity = 0;
    int32_t price = 0;
    int64_t classes = 0;
    bool randomUniquePool = false;
    bool hasBattleRageEffect = false;
    const gd::GdStr* startsSubclass = nullptr;
    const gd::GdStr* gateItem = nullptr;
    bool animationScene = false;
    bool flickerAni = false;
    double flickerMinDist = 0.1;
    double flickerMaxDist = 3.0;
    double flickerMinSpeed = 0.3;
    double flickerMaxSpeed = 1.0;
    bool connectorReadyRoll = false;
    bool gemRoll = false;
    int32_t sceneDepth = 2;
    int32_t releaseState = 1;
    int64_t gainedStacks = 0;
    int64_t removedStacks = 0;
    int64_t usedStacks = 0;

    std::vector<double> params;
    std::vector<double> extraCds;
    std::vector<int64_t> types;
    std::vector<std::pair<const gd::GdStr*, double>> namedParams;
    std::vector<OrigRecipeProto> originatingRecipes;
};

struct CharProto {
    int32_t class_id = 0;
    std::string key;
    double health = 25.0;
    double stamina = 5.0;
    double regen = 1.0;
    int32_t gold = 13;
    bool valid = false;
};

static std::vector<ItemProto> g_items;
static std::unordered_map<std::string, int32_t> g_item_by_key;
static CharProto g_chars[8];

// ─────────────────────────── Debug: per-battle event stream dump ───────────────────────────
// 仅单线程调试用途（run_batch 多线程会竞写）。镜像 sim 主仓 py 钩子的行提取口径：
// 每条 logEvent 记一行 canonical 字符串，用于与 py/gd 留档事件流逐行对拍找首个分叉。
// 格式: ts=<f:hexbits>|type=<i>|id=<i>|tgt=<i|-999null>|parent=<i>|origin=<...>|params=<...>
//   值编码: n=null b:0/1 i:<int64> f:<16位hex的双精度位型> s:<文本> v:[f,f]
//           a:[...] d:{k=v,...}键名字典序 o:item:<identifier>#<ownerType> / o:cls:<类名>
struct DbgEv { double ts; int32_t type; std::string line; };
static std::vector<DbgEv> g_dbg_events;
// ★ 记录开关（默认关）：缓冲非线程安全，run_batch 多线程绝不写；
//   仅单线程对拍路径先调 gd_sim_set_dbg_events(1) 再 run_one。
static std::atomic<int32_t> g_dbg_enabled{0};

static void dbg_serialize_val(gd::BattleCtx& battle, const gd::GdVal& v, std::string& out);

static void dbg_serialize_dict(gd::BattleCtx& battle, gd::GdDict* d, std::string& out) {
    std::vector<std::pair<std::string, std::string>> kvs;
    if (d) {
        for (uint32_t i = 0; i < d->len; ++i) {
            const auto& e = d->entries[i];
            std::string k, val;
            if (e.key.kind == gd::GdVal::Kind::Str && e.key.str)
                k.assign(e.key.str->data, e.key.str->len);
            else
                dbg_serialize_val(battle, e.key, k);
            dbg_serialize_val(battle, e.val, val);
            kvs.emplace_back(std::move(k), std::move(val));
        }
    }
    std::sort(kvs.begin(), kvs.end());
    out += "d:{";
    for (size_t i = 0; i < kvs.size(); ++i) {
        if (i) out += ",";
        out += kvs[i].first + "=" + kvs[i].second;
    }
    out += "}";
}

static void dbg_serialize_val(gd::BattleCtx& battle, const gd::GdVal& v, std::string& out) {
    char buf[64];
    switch (v.kind) {
        case gd::GdVal::Kind::Null: out += "n"; break;
        case gd::GdVal::Kind::Bool:
            out += v.b ? "b:1" : "b:0"; break;
        case gd::GdVal::Kind::Int:
            snprintf(buf, sizeof(buf), "i:%lld", static_cast<long long>(v.i));
            out += buf; break;
        case gd::GdVal::Kind::Float: {
            uint64_t bits;
            std::memcpy(&bits, &v.f, sizeof(bits));
            snprintf(buf, sizeof(buf), "f:%016llx", static_cast<unsigned long long>(bits));
            out += buf; break;
        }
        case gd::GdVal::Kind::Str:
            if (v.str) out += "s:" + std::string(v.str->data, v.str->len);
            else out += "n";
            break;
        case gd::GdVal::Kind::Vec2: {
            uint64_t bx, by;
            std::memcpy(&bx, &v.v2.x, sizeof(bx));
            std::memcpy(&by, &v.v2.y, sizeof(by));
            snprintf(buf, sizeof(buf), "v:[f:%016llx,f:%016llx]",
                     static_cast<unsigned long long>(bx), static_cast<unsigned long long>(by));
            out += buf; break;
        }
        case gd::GdVal::Kind::Arr: {
            out += "a:[";
            if (v.arr) {
                for (uint32_t i = 0; i < v.arr->len; ++i) {
                    if (i) out += ",";
                    dbg_serialize_val(battle, v.arr->data[i], out);
                }
            }
            out += "]";
            break;
        }
        case gd::GdVal::Kind::Dict:
            dbg_serialize_dict(battle, v.dict, out);
            break;
        case gd::GdVal::Kind::Obj: {
            if (!v.obj) { out += "n"; break; }
            gd::GdVal descr, ident, owner;
            if (v.obj->get_prop(g_syms.descriptor, descr) &&
                descr.kind == gd::GdVal::Kind::Obj && descr.obj &&
                descr.obj->get_prop(g_syms.identifier, ident) &&
                ident.kind == gd::GdVal::Kind::Str && ident.str) {
                out += "o:item:" + std::string(ident.str->data, ident.str->len);
                if (v.obj->get_prop(g_syms.ownerType, owner) && owner.is_num()) {
                    snprintf(buf, sizeof(buf), "#%lld", static_cast<long long>(owner.as_int()));
                    out += buf;
                }
                break;
            }
            out += std::string("o:cls:") + (v.obj->meta() ? v.obj->meta()->class_name : "?");
            break;
        }
        default: out += "x:<unhandled-kind>"; break;
    }
}

static void dbg_record_event(gd::BattleCtx& battle, gd::GdObj* ev) {
    if (!g_dbg_enabled.load(std::memory_order_relaxed)) return;
    double ts = 0.0;
    int32_t type = -1;
    int64_t eid = -1;
    int64_t parent = -1;
    int64_t target = -999;
    gd::GdVal tv, idv, tsv, pvv, prev;

    if (ev->get_prop(g_syms.type, tv)) {
        if (tv.kind == gd::GdVal::Kind::Int) type = static_cast<int32_t>(tv.i);
        else if (tv.kind == gd::GdVal::Kind::Float) type = static_cast<int32_t>(tv.f);
    }
    if (ev->get_prop(g_syms.timestamp, tsv)) {
        if (tsv.kind == gd::GdVal::Kind::Float) ts = tsv.f;
        else if (tsv.kind == gd::GdVal::Kind::Int) ts = static_cast<double>(tsv.i);
    }
    if (ev->get_prop(g_syms.id, idv) && idv.is_num()) eid = idv.as_int();
    if (ev->get_prop(g_syms.target, tv) && !tv.is_null()) {
        if (tv.is_num()) target = static_cast<int32_t>(tv.as_int());
        else target = -998;
    }
    if (ev->get_prop(g_syms.parentEvent, prev) &&
        prev.kind == gd::GdVal::Kind::Obj && prev.obj) {
        gd::GdVal pid;
        if (prev.obj->get_prop(g_syms.id, pid) && pid.is_num()) parent = pid.as_int();
    }

    std::string line;
    line.reserve(96);
    char buf[80];
    uint64_t bits;
    std::memcpy(&bits, &ts, sizeof(bits));
    snprintf(buf, sizeof(buf), "ts=f:%016llx|type=%d|id=%lld|tgt=%lld|parent=%lld|origin=",
             static_cast<unsigned long long>(bits), type, static_cast<long long>(eid),
             static_cast<long long>(target), static_cast<long long>(parent));
    line += buf;
    gd::GdVal ov;
    if (ev->get_prop(g_syms.origin, ov)) dbg_serialize_val(battle, ov, line);
    else line += "n";
    line += "|params=";
    if (ev->get_prop(g_syms.params, pvv) && pvv.kind == gd::GdVal::Kind::Dict)
        dbg_serialize_dict(battle, pvv.dict, line);
    else
        line += "d:{}";
    g_dbg_events.push_back(DbgEv{ts, type, std::move(line)});
}

// ─────────────────────────── Hooks Subclass ───────────────────────────
struct NativeBattleHooks final : public Gd__gd_core__CoreHooks {
    explicit NativeBattleHooks(gd::BattleCtx* ctx) : Gd__gd_core__CoreHooks(ctx) {}

    void on_log_event(gd::BattleCtx& gd_ctx, gd::GdObj* ev) {
        gd_ctx.event_count += 1;
        dbg_record_event(gd_ctx, ev);
        gd::GdVal tv;
        if (!ev->get_prop(g_syms.type, tv)) return;
        int64_t etype = tv.as_int();

        // CoreConst.EventType: DealDamage=1, CriticalDamage=2, MissedAttack=3, Health=12
        if (etype == 1 || etype == 2) {
            int pid = -1;
            gd::GdVal targ;
            if (ev->get_prop(g_syms.target, targ) && !targ.is_null()) {
                pid = static_cast<int>(targ.as_int());
            } else {
                gd::GdVal orig;
                if (ev->get_prop(g_syms.origin, orig) && orig.kind == gd::GdVal::Kind::Obj && orig.obj) {
                    gd::GdVal ch = gd::call_method(gd_ctx, orig, g_syms.character, nullptr, 0);
                    if (ch.kind == gd::GdVal::Kind::Obj && ch.obj) {
                        auto* chr = static_cast<Gd__gd_core__CoreCharacter*>(ch.obj);
                        pid = static_cast<int>(chr->f_playerId.as_int());
                    }
                }
            }
            double dmg = 0.0;
            gd::GdVal pv;
            if (ev->get_prop(g_syms.params, pv) && pv.kind == gd::GdVal::Kind::Dict && pv.dict) {
                dmg = pv.dict->get(gd::GdVal::from_str(g_syms.s_damage)).as_float();
            }
            if (pid == 0) {
                gd_ctx.player_damage_dealt += dmg;
                if (etype == 2) gd_ctx.player_crits += 1;
            } else if (pid == 1) {
                gd_ctx.opponent_damage_dealt += dmg;
                if (etype == 2) gd_ctx.opponent_crits += 1;
            }
        } else if (etype == 3) {
            gd::GdVal orig;
            if (ev->get_prop(g_syms.origin, orig) && orig.kind == gd::GdVal::Kind::Obj && orig.obj) {
                gd::GdVal ch = gd::call_method(gd_ctx, orig, g_syms.character, nullptr, 0);
                if (ch.kind == gd::GdVal::Kind::Obj && ch.obj) {
                    int pid = static_cast<int>(static_cast<Gd__gd_core__CoreCharacter*>(ch.obj)->f_playerId.as_int());
                    if (pid == 0) gd_ctx.player_misses += 1;
                    else if (pid == 1) gd_ctx.opponent_misses += 1;
                }
            }
        } else if (etype == 12) {
            gd::GdVal targ;
            if (ev->get_prop(g_syms.target, targ) && !targ.is_null()) {
                int pid = static_cast<int>(targ.as_int());
                gd::GdVal pv;
                double amt = 0.0;
                if (ev->get_prop(g_syms.params, pv) && pv.kind == gd::GdVal::Kind::Dict && pv.dict) {
                    amt = pv.dict->get(gd::GdVal::from_str(g_syms.s_amount)).as_float();
                }
                if (pid == 0) gd_ctx.player_healing_done += amt;
                else if (pid == 1) gd_ctx.opponent_healing_done += amt;
            }
        }
    }

    bool call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) override {
        if (m == g_syms.logEvent) {
            if (argc >= 1 && args[0].kind == gd::GdVal::Kind::Obj && args[0].obj) {
                on_log_event(gd_ctx, args[0].obj);
            }
            out = gd::GdVal::null();
            return true;
        }
        return Gd__gd_core__CoreHooks::call_method(gd_ctx, m, args, argc, out);
    }
};

// ─────────────────────────── Helper: Build CoreItemData inside Battle Arena ───────────────────────────
Gd__gd_core__CoreItemData* build_descriptor_in_battle(gd::BattleCtx& battle, const ItemProto& p) {
    gd::GdVal dv = gd::construct_class(battle, &META_Gd__gd_core__CoreItemData, nullptr, 0);
    auto* d = static_cast<Gd__gd_core__CoreItemData*>(dv.obj);

    d->f_name = gd::GdVal::from_str(p.name);
    d->f_identifier = gd::GdVal::from_str(p.identifier);
    d->f_minDam = gd::GdVal::from_int(p.minDam);
    d->f_maxDam = gd::GdVal::from_int(p.maxDam);
    d->f_staminaCost = gd::GdVal::from_float(p.staminaCost);
    d->f_block = gd::GdVal::from_int(p.block);
    d->f_cd = gd::GdVal::from_float(p.cd);
    d->f_accuracy = gd::GdVal::from_float(p.accuracy);
    d->f_canActivate = gd::GdVal::from_bool(p.canActivate);
    d->f_chance = gd::GdVal::from_float(p.chance);
    d->f_chance2 = gd::GdVal::from_float(p.chance2);
    d->f_shopChance = gd::GdVal::from_float(p.shopChance);
    d->f_tags = gd::GdVal::from_int(p.tags);
    d->f_physics = gd::GdVal::from_int(p.physics);
    d->f_rarity = gd::GdVal::from_int(p.rarity);
    d->f_price = gd::GdVal::from_int(p.price);
    d->f_classes = gd::GdVal::from_int(p.classes);
    d->f_randomUniquePool = gd::GdVal::from_bool(p.randomUniquePool);
    d->f_hasBattleRageEffect = gd::GdVal::from_bool(p.hasBattleRageEffect);
    d->f_startsSubclass = gd::GdVal::from_str(p.startsSubclass);
    d->f_gateItem = p.gateItem ? gd::GdVal::from_str(p.gateItem) : gd::GdVal::null();
    d->f_animationScene = gd::GdVal::from_bool(p.animationScene);
    d->f_flickerAni = gd::GdVal::from_bool(p.flickerAni);
    d->f_flickerMinDist = gd::GdVal::from_float(p.flickerMinDist);
    d->f_flickerMaxDist = gd::GdVal::from_float(p.flickerMaxDist);
    d->f_flickerMinSpeed = gd::GdVal::from_float(p.flickerMinSpeed);
    d->f_flickerMaxSpeed = gd::GdVal::from_float(p.flickerMaxSpeed);
    d->f_connectorReadyRoll = gd::GdVal::from_bool(p.connectorReadyRoll);
    d->f_gemRoll = gd::GdVal::from_bool(p.gemRoll);
    d->f_sceneDepth = gd::GdVal::from_int(p.sceneDepth);
    d->f_releaseState = gd::GdVal::from_int(p.releaseState);
    d->f_gainedStacks = gd::GdVal::from_int(p.gainedStacks);
    d->f_removedStacks = gd::GdVal::from_int(p.removedStacks);
    d->f_usedStacks = gd::GdVal::from_int(p.usedStacks);

    gd::GdArr* params_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(p.params.size()));
    for (double v : p.params) params_arr->push_back(battle.arena, gd::GdVal::from_float(v));
    d->f_params = gd::GdVal::from_arr(params_arr);

    gd::GdArr* ecd_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(p.extraCds.size()));
    for (double v : p.extraCds) ecd_arr->push_back(battle.arena, gd::GdVal::from_float(v));
    d->f_extraCds = gd::GdVal::from_arr(ecd_arr);

    gd::GdArr* types_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(p.types.size()));
    for (int64_t v : p.types) types_arr->push_back(battle.arena, gd::GdVal::from_int(v));
    d->f_types = gd::GdVal::from_arr(types_arr);

    gd::GdArr* rec_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(p.originatingRecipes.size()));
    for (const auto& rec : p.originatingRecipes) {
        gd::GdDict* rd = gd::GdDict::create(battle.arena, 4);
        rd->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("b")), gd::GdVal::from_str(rec.base));
        gd::GdArr* ia = gd::GdArr::create(battle.arena, static_cast<uint32_t>(rec.ingredients.size()));
        for (const auto* s : rec.ingredients) ia->push_back(battle.arena, gd::GdVal::from_str(s));
        rd->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("i")), gd::GdVal::from_arr(ia));
        gd::GdArr* ca = gd::GdArr::create(battle.arena, static_cast<uint32_t>(rec.consumed.size()));
        for (bool b : rec.consumed) ca->push_back(battle.arena, gd::GdVal::from_bool(b));
        rd->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("c")), gd::GdVal::from_arr(ca));
        rec_arr->push_back(battle.arena, gd::GdVal::from_dict(rd));
    }
    d->f_originatingRecipes = gd::GdVal::from_arr(rec_arr);

    for (const auto& np : p.namedParams) {
        gd::GdVal args[2] = {gd::GdVal::from_str(np.first), gd::GdVal::from_float(np.second)};
        d->fn_addNamedParam(args, 2);
    }
    return d;
}

}  // namespace

// ─────────────────────────── C ABI Input / Output Structs ───────────────────────────
extern "C" {

struct PackedEffect {
    int16_t trigger_type;
    int16_t stack_type;
};

struct PackedAffectedGroup {
    int32_t color;
    uint16_t count;
    uint16_t offset;  // offset into side.cells_xy
};

struct PackedItem {
    int32_t item_id;
    int32_t rotation;
    int8_t crafted;  // -1 unset, 0 false, 1 true
    int8_t storage;  // 0 placed, 1 storage (skip)
    int16_t charge_frame_x;
    int16_t charge_frame_y;
    uint16_t n_occupied;
    uint16_t occupied_off;   // index into cells_xy (pairs)
    uint16_t n_collision;
    uint16_t collision_off;  // index into cells_xy (pairs)
    uint16_t n_affected_groups;
    uint16_t affected_group_off;  // index into affected_groups
    uint8_t n_gems;
    uint8_t n_effects;
    int16_t n_sockets;   // -1 = 未指定(回落 proto.sockets)；>=0 = 实例真值(夹具 gem_lens)
    int16_t _pad0;
    int32_t gems[8];
    PackedEffect effects[8];
};

struct PackedSide {
    int32_t char_class;
    double health;            // < 0 -> from g_chars[char_class]
    double stamina;           // < 0 -> from g_chars[char_class]
    double base_max_stamina;  // < 0 -> use stamina
    double regen;             // < 0 -> from g_chars[char_class]
    double snapshot_stamina;  // < 0 -> unset
    int32_t n_items;
    const PackedItem* items;
    const int16_t* cells_xy;  // pairs (x, y) -> 2 * count int16_t
    const PackedAffectedGroup* affected_groups;
    // 夹具 activation_order 直通（真 Godot 全局链洗牌终序，下标相对输入装配序）。
    // n_activation_order == 0 -> 未指定，走 native_activation_order 自己洗牌。
    int32_t n_activation_order;
    const int32_t* activation_order;
};

struct BattleOptions {
    uint64_t seed;
    int32_t round_id;
    int32_t below_master;
    double custom_health_multiplier;
    int32_t label_rng_enabled;
    int32_t native_activation_order;
    int32_t reseed_after_player_character;
    int32_t formal_ev_gate;
    int32_t max_ticks;
    double max_time;  // <= 0 -> keep default (600.0)
    int32_t record_per_item;
    // rng_state 注入（oracle rng_state.txt 直灌）。-1 = 未指定。
    uint64_t rng_state;     // state= 原值（uint64 全值域）
    int32_t has_rng_state;  // 1 = 注入（-1 会与合法负值冲突，故用独立标志）
};

struct BattleResult {
    int32_t player_wins;
    int32_t timed_out;
    int32_t formal_ev_capped;
    double combat_time;
    int32_t ticks;
    int32_t fatigue_counter;
    double player_hp;
    double player_max_hp;
    double player_block;
    double opponent_hp;
    double opponent_max_hp;
    double opponent_block;
    int32_t out_of_stamina_count;
    int32_t event_count;
    double player_damage_dealt;
    double opponent_damage_dealt;
    double player_healing_done;
    double opponent_healing_done;
    int32_t player_crits;
    int32_t opponent_crits;
    int32_t player_misses;
    int32_t opponent_misses;
    int32_t n_placed_items;
    int32_t item_activations[64];
};

void gd_sim_init() {
    std::call_once(g_init_once, []() {
        gd_init_all_classes();
        g_syms.logEvent = gd::intern_sym("logEvent");
        g_syms.type = gd::intern_sym("type");
        g_syms.origin = gd::intern_sym("origin");
        g_syms.target = gd::intern_sym("target");
        g_syms.params = gd::intern_sym("params");
        g_syms.damage = gd::intern_sym("damage");
        g_syms.amount = gd::intern_sym("amount");
        g_syms._readyInit = gd::intern_sym("_readyInit");
        g_syms.setup = gd::intern_sym("setup");
        g_syms.addItem = gd::intern_sym("addItem");
        g_syms.setCraftedEffects = gd::intern_sym("setCraftedEffects");
        g_syms.setGem = gd::intern_sym("setGem");
        g_syms.setFaceDirectionInstant = gd::intern_sym("setFaceDirectionInstant");
        g_syms.crafted_instance = gd::intern_sym("crafted_instance");
        g_syms.triggerType = gd::intern_sym("triggerType");
        g_syms.stackType = gd::intern_sym("stackType");
        g_syms.health = gd::intern_sym("health");
        g_syms.stamina = gd::intern_sym("stamina");
        g_syms.regen = gd::intern_sym("regen");
        g_syms.gold = gd::intern_sym("gold");
        g_syms.character = gd::intern_sym("character");
        g_syms.timestamp = gd::intern_sym("timestamp");
        g_syms.id = gd::intern_sym("id");
        g_syms.parentEvent = gd::intern_sym("parentEvent");
        g_syms.ownerType = gd::intern_sym("ownerType");
        g_syms.descriptor = gd::intern_sym("descriptor");
        g_syms.identifier = gd::intern_sym("identifier");
        g_syms.s_damage = gd::make_static_str("damage");
        g_syms.s_amount = gd::make_static_str("amount");
        g_syms.s_health = gd::make_static_str("health");
        g_syms.s_stamina = gd::make_static_str("stamina");
        g_syms.s_regen = gd::make_static_str("regen");
        g_syms.s_gold = gd::make_static_str("gold");
    });
}

void gd_sim_reset_registry() {
    g_items.clear();
    g_item_by_key.clear();
    for (int i = 0; i < 8; ++i) g_chars[i] = CharProto{};
}

void gd_sim_register_character(
    int32_t class_id, const char* key, double health, double stamina, double regen, int32_t gold
) {
    if (class_id < 0 || class_id >= 8) return;
    g_chars[class_id] = CharProto{class_id, key ? key : "", health, stamina, regen, gold, true};
}

int32_t gd_sim_find_item_id(const char* key) {
    if (!key) return -1;
    auto it = g_item_by_key.find(key);
    return it == g_item_by_key.end() ? -1 : it->second;
}

int32_t gd_sim_register_item(
    const char* key,
    const char* script_path,
    int32_t sockets,
    const char* name,
    const char* identifier,
    int32_t minDam,
    int32_t maxDam,
    double staminaCost,
    int32_t block,
    double cd,
    double accuracy,
    int32_t canActivate,
    double chance,
    double chance2,
    double shopChance,
    int64_t tags,
    int64_t physics,
    int32_t rarity,
    int32_t price,
    int64_t classes,
    int32_t randomUniquePool,
    int32_t hasBattleRageEffect,
    const char* startsSubclass,
    const char* gateItem,
    int32_t animationScene,
    int32_t flickerAni,
    double flickerMinDist,
    double flickerMaxDist,
    double flickerMinSpeed,
    double flickerMaxSpeed,
    int32_t connectorReadyRoll,
    int32_t gemRoll,
    int32_t sceneDepth,
    int32_t releaseState,
    int64_t gainedStacks,
    int64_t removedStacks,
    int64_t usedStacks,
    const double* params, int32_t n_params,
    const double* extraCds, int32_t n_extraCds,
    const int64_t* types, int32_t n_types,
    const char* const* np_keys, const double* np_vals, int32_t n_np,
    const char* recipes_encoded
) {
    gd_sim_init();
    int32_t existing = gd_sim_find_item_id(key);
    if (existing >= 0) return existing;

    ItemProto proto;
    proto.id = static_cast<int32_t>(g_items.size());
    proto.key = key ? key : "";
    proto.cls = gd::find_class(script_path ? script_path : "res://gd_core_items/Item.gd");
    if (!proto.cls) proto.cls = &META_Gd__gd_core_items__Item;
    proto.sockets = sockets;

    proto.name = gd::make_static_str(name ? name : proto.key);
    proto.identifier = gd::make_static_str(identifier ? identifier : proto.key);
    proto.minDam = minDam;
    proto.maxDam = maxDam;
    proto.staminaCost = staminaCost;
    proto.block = block;
    proto.cd = cd;
    proto.accuracy = accuracy;
    proto.canActivate = canActivate != 0;
    proto.chance = chance;
    proto.chance2 = chance2;
    proto.shopChance = shopChance;
    proto.tags = tags;
    proto.physics = physics;
    proto.rarity = rarity;
    proto.price = price;
    proto.classes = classes;
    proto.randomUniquePool = randomUniquePool != 0;
    proto.hasBattleRageEffect = hasBattleRageEffect != 0;
    proto.startsSubclass = gd::make_static_str(startsSubclass ? startsSubclass : "");
    proto.gateItem = (gateItem && gateItem[0]) ? gd::make_static_str(gateItem) : nullptr;
    proto.animationScene = animationScene != 0;
    proto.flickerAni = flickerAni != 0;
    proto.flickerMinDist = flickerMinDist;
    proto.flickerMaxDist = flickerMaxDist;
    proto.flickerMinSpeed = flickerMinSpeed;
    proto.flickerMaxSpeed = flickerMaxSpeed;
    proto.connectorReadyRoll = connectorReadyRoll != 0;
    proto.gemRoll = gemRoll != 0;
    proto.sceneDepth = sceneDepth;
    proto.releaseState = releaseState;
    proto.gainedStacks = gainedStacks;
    proto.removedStacks = removedStacks;
    proto.usedStacks = usedStacks;

    if (params && n_params > 0) proto.params.assign(params, params + n_params);
    if (extraCds && n_extraCds > 0) proto.extraCds.assign(extraCds, extraCds + n_extraCds);
    if (types && n_types > 0) proto.types.assign(types, types + n_types);
    for (int32_t i = 0; i < n_np; ++i) {
        if (np_keys && np_keys[i]) {
            proto.namedParams.emplace_back(gd::make_static_str(np_keys[i]), np_vals[i]);
        }
    }

    // Parse compact recipes string: records separated by '\n', fields by '\t': base \t ing1,ing2 \t 1,0
    if (recipes_encoded && recipes_encoded[0]) {
        std::string_view sv(recipes_encoded);
        size_t pos = 0;
        while (pos < sv.size()) {
            size_t nl = sv.find('\n', pos);
            if (nl == std::string_view::npos) nl = sv.size();
            std::string_view line = sv.substr(pos, nl - pos);
            pos = nl + 1;
            if (line.empty()) continue;
            size_t t1 = line.find('\t');
            size_t t2 = (t1 == std::string_view::npos) ? std::string_view::npos : line.find('\t', t1 + 1);
            if (t1 == std::string_view::npos || t2 == std::string_view::npos) continue;
            OrigRecipeProto rec;
            rec.base = gd::make_static_str(line.substr(0, t1));
            std::string_view ings = line.substr(t1 + 1, t2 - (t1 + 1));
            std::string_view cons = line.substr(t2 + 1);
            size_t p = 0;
            while (p < ings.size()) {
                size_t c = ings.find('|', p);
                if (c == std::string_view::npos) c = ings.size();
                rec.ingredients.push_back(gd::make_static_str(ings.substr(p, c - p)));
                p = c + 1;
            }
            p = 0;
            while (p < cons.size()) {
                size_t c = cons.find('|', p);
                if (c == std::string_view::npos) c = cons.size();
                rec.consumed.push_back(cons.substr(p, c - p) == "1");
                p = c + 1;
            }
            proto.originatingRecipes.push_back(std::move(rec));
        }
    }

    g_item_by_key[proto.key] = proto.id;
    g_items.push_back(std::move(proto));
    return static_cast<int32_t>(g_items.size() - 1);
}

}  // extern "C"

// ─────────────────────────── Single Battle Execution on Persistent BattleCtx ───────────────────────────
namespace {

static void setup_character_stats(Gd__gd_core__CoreCharacter* chr, const PackedSide& side) {
    int cid = side.char_class;
    const CharProto& cp = (cid >= 0 && cid < 8 && g_chars[cid].valid) ? g_chars[cid] : CharProto{};
    double h = (side.health >= 0.0) ? side.health : cp.health;
    double stam = (side.stamina >= 0.0) ? side.stamina : cp.stamina;
    double bstam = (side.base_max_stamina >= 0.0) ? side.base_max_stamina : stam;
    double reg = (side.regen >= 0.0) ? side.regen : cp.regen;

    chr->f_characterClass = gd::GdVal::from_int(cid);
    gd::GdVal hv = gd::GdVal::from_float(h);
    chr->fn_setMaxHealth(&hv, 1);
    chr->fn_setCurrentHealth(&hv, 1);
    chr->f_baseMaxStamina = gd::GdVal::from_float(bstam);
    gd::GdVal sv = gd::GdVal::from_float(stam);
    chr->fn_setMaxStamina(&sv, 1);
    chr->f_baseStaminaRegen = gd::GdVal::from_float(reg);
    chr->f_staminaRegen = gd::GdVal::from_float(reg);
}

static gd::GdArr* make_vec2_arr(gd::BattleCtx& battle, const int16_t* xy, uint16_t off, uint16_t count) {
    gd::GdArr* a = gd::GdArr::create(battle.arena, count);
    const int16_t* ptr = xy + static_cast<size_t>(off) * 2;
    for (uint16_t i = 0; i < count; ++i) {
        a->push_back(battle.arena, gd::GdVal::from_vec2(static_cast<double>(ptr[i * 2]), static_cast<double>(ptr[i * 2 + 1])));
    }
    return a;
}

static gd::GdVal build_single_item_obj(
    gd::BattleCtx& battle,
    gd::GdObj* ctx_obj,
    Gd__gd_core__CoreCharacter* chr,
    int32_t owner_type,
    const ItemProto& proto,
    Gd__gd_core__CoreItemData* descr,
    int32_t rotation,
    int8_t crafted,
    int16_t cf_x,
    int16_t cf_y,
    int32_t proto_index_sockets,
    gd::GdArr* occ_arr,
    gd::GdArr* col_arr,
    gd::GdDict* aff_dict
) {
    gd::GdVal iv = gd::construct_class(battle, proto.cls, nullptr, 0);
    gd::GdObj* item = iv.obj;
    if (!item) return gd::GdVal::null();

    if (crafted >= 0) {
        item->set_prop(battle, g_syms.crafted_instance, gd::GdVal::from_int(crafted));
    }

    gd::GdVal setup_args[3] = {gd::GdVal::from_obj(ctx_obj), gd::GdVal::from_obj(descr), gd::GdVal::from_obj(chr)};
    gd::call_method(battle, iv, g_syms.setup, setup_args, 3);

    auto* ci = static_cast<Gd__gd_core__CoreItem*>(item);
    int32_t _n_sockets = (proto_index_sockets >= 0) ? proto_index_sockets : proto.sockets;
    gd::GdArr* gems_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(std::max<int32_t>(0, _n_sockets)));
    gems_arr->resize(battle.arena, static_cast<int64_t>(std::max<int32_t>(0, _n_sockets)));
    ci->f_gems = gd::GdVal::from_arr(gems_arr);

    ci->f_collisionCells = gd::GdVal::from_arr(col_arr);
    ci->f_affectedTileCells = gd::GdVal::from_dict(aff_dict);
    ci->f_occupiedCells = gd::GdVal::from_arr(occ_arr);
    ci->f_ownerType = gd::GdVal::from_int(owner_type);

    int64_t fd = (((rotation / 90) % 4) + 4) % 4;
    ci->f_faceDirection = gd::GdVal::from_int(fd);
    ci->f_rotation = gd::GdVal::from_float(static_cast<double>(fd) * 3.14159265358979323846 * 0.5);

    gd::GdArr* cf = gd::GdArr::create(battle.arena, 4);
    for (int k = 0; k < 4; ++k) {
        cf->push_back(battle.arena, gd::GdVal::from_vec2(static_cast<double>(cf_x), static_cast<double>(cf_y)));
    }
    ci->f_chargeFrame = gd::GdVal::from_arr(cf);

    gd::call_method(battle, iv, g_syms._readyInit, nullptr, 0);
    return iv;
}

static void build_side_items(
    gd::BattleCtx& battle,
    gd::GdObj* ctx_obj,
    Gd__gd_core__CoreCharacter* chr,
    int32_t owner_type,
    const PackedSide& side,
    std::vector<Gd__gd_core__CoreItemData*>& descr_cache,
    gd::GdArr* out_items,
    std::vector<Gd__gd_core__CoreItem*>* record_items
) {
    for (int32_t i = 0; i < side.n_items; ++i) {
        const PackedItem& pi = side.items[i];
        if (pi.storage) continue;
        if (pi.item_id < 0 || static_cast<size_t>(pi.item_id) >= g_items.size()) continue;
        const ItemProto& proto = g_items[pi.item_id];
        Gd__gd_core__CoreItemData* descr = descr_cache[pi.item_id];

        gd::GdArr* occ = make_vec2_arr(battle, side.cells_xy, pi.occupied_off, pi.n_occupied);
        gd::GdArr* col = make_vec2_arr(battle, side.cells_xy, pi.collision_off, pi.n_collision);

        gd::GdDict* aff = gd::GdDict::create(battle.arena, pi.n_affected_groups);
        for (uint16_t ag = 0; ag < pi.n_affected_groups; ++ag) {
            const PackedAffectedGroup& grp = side.affected_groups[pi.affected_group_off + ag];
            gd::GdArr* ga = make_vec2_arr(battle, side.cells_xy, grp.offset, grp.count);
            aff->set(battle.arena, gd::GdVal::from_int(grp.color), gd::GdVal::from_arr(ga));
        }

        gd::GdVal iv = build_single_item_obj(
            battle, ctx_obj, chr, owner_type, proto, descr, pi.rotation, pi.crafted,
            pi.charge_frame_x, pi.charge_frame_y,
            (pi.n_sockets >= 0) ? static_cast<int32_t>(pi.n_sockets) : -1,
            occ, col, aff);
        if (iv.is_null()) continue;

        gd::GdVal add_args[2] = {iv, gd::GdVal::from_arr(occ)};
        gd::call_method(battle, chr->f_inventory, g_syms.addItem, add_args, 2);

        if (pi.n_effects > 0) {
            gd::GdArr* eff_arr = gd::GdArr::create(battle.arena, pi.n_effects);
            for (uint8_t e = 0; e < pi.n_effects; ++e) {
                gd::GdDict* ed = gd::GdDict::create(battle.arena, 2);
                ed->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("triggerType")),
                        gd::GdVal::from_int(pi.effects[e].trigger_type));
                ed->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("stackType")),
                        gd::GdVal::from_int(pi.effects[e].stack_type));
                eff_arr->push_back(battle.arena, gd::GdVal::from_dict(ed));
            }
            gd::GdVal eff_arg = gd::GdVal::from_arr(eff_arr);
            gd::call_method(battle, iv, g_syms.setCraftedEffects, &eff_arg, 1);
        }

        for (uint8_t gi = 0; gi < pi.n_gems; ++gi) {
            int32_t gid = pi.gems[gi];
            if (gid < 0 || static_cast<size_t>(gid) >= g_items.size()) continue;
            const ItemProto& gproto = g_items[gid];
            Gd__gd_core__CoreItemData* gdescr = descr_cache[gid];
            gd::GdArr* gocc = gd::GdArr::create(battle.arena, 1);
            gocc->push_back(battle.arena, gd::GdVal::from_vec2(0.0, 0.0));
            gd::GdArr* gcol = gd::GdArr::create(battle.arena, 1);
            gcol->push_back(battle.arena, gd::GdVal::from_vec2(0.0, 0.0));
            gd::GdDict* gaff = gd::GdDict::create(battle.arena, 0);

            gd::GdVal gv = build_single_item_obj(
                battle, ctx_obj, chr, 7 /* CoreConst.Owner.Socket */, gproto, gdescr, 0, -1, 0, 0, -1, gocc, gcol, gaff);
            gd::GdVal sg_args[2] = {gd::GdVal::from_int(gi), gv};
            gd::call_method(battle, iv, g_syms.setGem, sg_args, 2);
        }

        out_items->push_back(battle.arena, iv);
        if (record_items) {
            record_items->push_back(static_cast<Gd__gd_core__CoreItem*>(iv.obj));
        }
    }
}

static void register_side_descriptors(
    gd::BattleCtx& battle,
    Gd__gd_core__CoreItemBook* book,
    const PackedSide& side,
    std::vector<Gd__gd_core__CoreItemData*>& descr_cache
) {
    for (int32_t i = 0; i < side.n_items; ++i) {
        const PackedItem& pi = side.items[i];
        if (pi.storage) continue;
        if (pi.item_id >= 0 && static_cast<size_t>(pi.item_id) < g_items.size() && !descr_cache[pi.item_id]) {
            auto* d = build_descriptor_in_battle(battle, g_items[pi.item_id]);
            descr_cache[pi.item_id] = d;
            gd::GdVal dv = gd::GdVal::from_obj(d);
            book->fn_register(&dv, 1);
        }
        for (uint8_t gi = 0; gi < pi.n_gems; ++gi) {
            int32_t gid = pi.gems[gi];
            if (gid >= 0 && static_cast<size_t>(gid) < g_items.size() && !descr_cache[gid]) {
                auto* gd = build_descriptor_in_battle(battle, g_items[gid]);
                descr_cache[gid] = gd;
                gd::GdVal gdv = gd::GdVal::from_obj(gd);
                book->fn_register(&gdv, 1);
            }
        }
    }
}

// ─────────────────────────── Debug: last computed activation orders ───────────────────────────
// 仅单线程调试用途（run_batch 多线程会竞写）。记录 native_activation_order 路径上
// shuffle 后 / sort 后的物品下标（相对输入装配序），用于与真 Godot 复刻终序对拍。
static std::vector<int32_t> g_dbg_p_shuffle, g_dbg_o_shuffle;
static std::vector<int32_t> g_dbg_p_sorted, g_dbg_o_sorted;

static void record_order(const gd::GdArr* arr,
                         const std::unordered_map<const gd::GdObj*, int32_t>& idx,
                         std::vector<int32_t>& out) {
    out.clear();
    if (!arr) return;
    out.reserve(arr->len);
    for (uint32_t i = 0; i < arr->len; ++i) {
        auto it = (arr->data[i].kind == gd::GdVal::Kind::Obj && arr->data[i].obj)
                      ? idx.find(arr->data[i].obj) : idx.end();
        out.push_back(it != idx.end() ? it->second : -1);
    }
}

static void run_one_internal(
    gd::BattleCtx& battle,
    const PackedSide& player_side,
    const PackedSide& opponent_side,
    const BattleOptions& opts,
    BattleResult& out
) {
    std::memset(&out, 0, sizeof(BattleResult));
    battle.reset_for_battle(opts.seed);
    if (g_dbg_enabled.load(std::memory_order_relaxed)) g_dbg_events.clear();  // 逐场清空（仅单线程语义）

    auto* hooks = battle.arena.make<NativeBattleHooks>(&battle);
    hooks->init_fields(battle);

    gd::GdVal ctx_args[2] = {gd::GdVal::from_int(static_cast<int64_t>(opts.seed)), gd::GdVal::from_obj(hooks)};
    gd::GdVal ctx_val = gd::construct_class(battle, &META_Gd__gd_core__CoreContext, ctx_args, 2);
    auto* ctx_obj = static_cast<Gd__gd_core__CoreContext*>(ctx_val.obj);

    ctx_obj->f_below_master = gd::GdVal::from_bool(opts.below_master != 0);
    ctx_obj->f_custom_health_multiplier = gd::GdVal::from_float(opts.custom_health_multiplier);
    ctx_obj->f_label_rng_enabled = gd::GdVal::from_bool(opts.label_rng_enabled != 0);
    ctx_obj->f_deferred_flush_enabled = gd::GdVal::from_bool(false);
    ctx_obj->f_eb_relay_mirrored = gd::GdVal::from_bool(false);
    ctx_obj->f_cur_round = gd::GdVal::from_int(opts.round_id);


    // Populate class_resources dictionary
    gd::GdDict* cr_dict = gd::GdDict::create(battle.arena, 8);
    for (int cid = 0; cid < 8; ++cid) {
        if (!g_chars[cid].valid) continue;
        gd::GdDict* cinfo = gd::GdDict::create(battle.arena, 4);
        cinfo->set(battle.arena, gd::GdVal::from_str(g_syms.s_health), gd::GdVal::from_float(g_chars[cid].health));
        cinfo->set(battle.arena, gd::GdVal::from_str(g_syms.s_stamina), gd::GdVal::from_float(g_chars[cid].stamina));
        cinfo->set(battle.arena, gd::GdVal::from_str(g_syms.s_regen), gd::GdVal::from_float(g_chars[cid].regen));
        cinfo->set(battle.arena, gd::GdVal::from_str(g_syms.s_gold), gd::GdVal::from_int(g_chars[cid].gold));
        cr_dict->set(battle.arena, gd::GdVal::from_int(cid), gd::GdVal::from_dict(cinfo));
    }
    ctx_obj->f_class_resources = gd::GdVal::from_dict(cr_dict);

    // Construct player character (ID.PLAYER = 0)
    gd::GdVal p_args[2] = {ctx_val, gd::GdVal::from_int(0)};
    gd::GdVal p_val = gd::construct_class(battle, &META_Gd__gd_core__CoreCharacter, p_args, 2);
    auto* p_chr = static_cast<Gd__gd_core__CoreCharacter*>(p_val.obj);
    setup_character_stats(p_chr, player_side);

    gd::GdVal o_val;
    Gd__gd_core__CoreCharacter* o_chr = nullptr;
    gd::GdVal combat_val;
    Gd__gd_core__CoreCombat* combat_obj = nullptr;

    if (opts.reseed_after_player_character) {
        auto* core_rng = static_cast<Gd__gd_core__CoreRng*>(ctx_obj->f_rng.obj);
        if (core_rng && core_rng->f_rng.kind == gd::GdVal::Kind::Rng && core_rng->f_rng.rng) {
            core_rng->f_rng.rng->set_seed(opts.seed);
        }
        ctx_obj->f_player = p_val;
        combat_val = gd::construct_class(battle, &META_Gd__gd_core__CoreCombat, &ctx_val, 1);
        combat_obj = static_cast<Gd__gd_core__CoreCombat*>(combat_val.obj);
        ctx_obj->f_combat = combat_val;
    } else {
        gd::GdVal o_args[2] = {ctx_val, gd::GdVal::from_int(1)};
        o_val = gd::construct_class(battle, &META_Gd__gd_core__CoreCharacter, o_args, 2);
        o_chr = static_cast<Gd__gd_core__CoreCharacter*>(o_val.obj);
        setup_character_stats(o_chr, opponent_side);
        combat_val = gd::construct_class(battle, &META_Gd__gd_core__CoreCombat, &ctx_val, 1);
        combat_obj = static_cast<Gd__gd_core__CoreCombat*>(combat_val.obj);
        gd::GdVal su_args[2] = {p_val, o_val};
        combat_obj->fn_setup(su_args, 2);
    }

    if (opts.max_time > 0.0) {
        combat_obj->f_max_time = gd::GdVal::from_float(opts.max_time);
    }

    // Pre-register all descriptors in both lineups into ctx.item_book before placing any item
    auto* book = static_cast<Gd__gd_core__CoreItemBook*>(ctx_obj->f_item_book.obj);
    std::vector<Gd__gd_core__CoreItemData*> descr_cache(g_items.size(), nullptr);
    register_side_descriptors(battle, book, player_side, descr_cache);
    register_side_descriptors(battle, book, opponent_side, descr_cache);

    gd::GdArr* p_items = gd::GdArr::create(battle.arena, static_cast<uint32_t>(std::max<int32_t>(0, player_side.n_items)));
    std::vector<Gd__gd_core__CoreItem*> p_item_ptrs;
    if (opts.record_per_item) p_item_ptrs.reserve(64);
    build_side_items(
        battle, ctx_val.obj, p_chr, 1 /* PlayerInventory */, player_side, descr_cache, p_items,
        opts.record_per_item ? &p_item_ptrs : nullptr);

    if (opts.reseed_after_player_character) {
        gd::GdVal o_args[2] = {ctx_val, gd::GdVal::from_int(1)};
        o_val = gd::construct_class(battle, &META_Gd__gd_core__CoreCharacter, o_args, 2);
        o_chr = static_cast<Gd__gd_core__CoreCharacter*>(o_val.obj);
        setup_character_stats(o_chr, opponent_side);
        gd::GdVal su_args[2] = {p_val, o_val};
        combat_obj->fn_setup(su_args, 2);
    }

    gd::GdArr* o_items = gd::GdArr::create(battle.arena, static_cast<uint32_t>(std::max<int32_t>(0, opponent_side.n_items)));
    build_side_items(battle, ctx_val.obj, o_chr, 3 /* Opponent */, opponent_side, descr_cache, o_items, nullptr);

    if (player_side.snapshot_stamina >= 0.0) {
        double bm = player_side.base_max_stamina >= 0.0 ? player_side.base_max_stamina : 5.0;
        p_chr->f_baseMaxStamina = gd::GdVal::from_float(bm);
        gd::GdVal sv = gd::GdVal::from_float(player_side.snapshot_stamina);
        p_chr->fn_setMaxStamina(&sv, 1);
        p_chr->fn_fillUpStamina(nullptr, 0);
    }
    if (opponent_side.snapshot_stamina >= 0.0) {
        double bm = opponent_side.base_max_stamina >= 0.0 ? opponent_side.base_max_stamina : 5.0;
        o_chr->f_baseMaxStamina = gd::GdVal::from_float(bm);
        gd::GdVal sv = gd::GdVal::from_float(opponent_side.snapshot_stamina);
        o_chr->fn_setMaxStamina(&sv, 1);
        o_chr->fn_fillUpStamina(nullptr, 0);
    }

    // ★ 神谕 rng_state 直灌：真源 py 腿 ctx.set_state（gd_core_engine.py:1209-1210）——
    //   注入点 = 双方角色 + 全部物品实例装配完成、startBattle 的 prepareItems/activateItems
    //   与逐 tick 判定链之前。放早了会被装配期消耗覆盖，放晚了会漏掉首拍掷点。
    if (opts.has_rng_state) {
        gd::GdVal _st = gd::GdVal::from_int(static_cast<int64_t>(opts.rng_state));  // 位模式直通
        ctx_obj->fn_set_state(&_st, 1);
    }

    // ★ 夹具 activation_order 直通（最高优先级）：真 Godot 全局链洗牌的终序。
    //   给了就按它重排（不洗牌、不排序，零 RNG 消耗），与 py 腿
    //   combat.startBattle([items[i] for i in order], ...) 同位同义。
    if (player_side.n_activation_order > 0 || opponent_side.n_activation_order > 0) {
        // ★ 只重排「传给 startBattle 的副本」——p_items/o_items 是 inventory 内容，
        //   就地改它会把 inventory 顺序也改掉。py 腿 prepareItems 里 `if item.placed:
        //   continue` ⇒ 物品装配期已 addItem，inventory 恒为装配序；activation_order
        //   只影响 ordered_items（activateItems 的遍历序）。
        auto reorder_copy = [&](gd::GdArr* arr, const PackedSide& side) -> gd::GdArr* {
            if (side.n_activation_order <= 0) return arr;
            gd::GdArr* tmp = gd::GdArr::create(battle.arena, arr->len);
            for (int32_t k = 0; k < side.n_activation_order; ++k) {
                int32_t src = side.activation_order[k];
                if (src >= 0 && static_cast<uint32_t>(src) < arr->len) {
                    tmp->push_back(battle.arena, arr->data[src]);
                }
            }
            return tmp;
        };
        gd::GdArr* p_ordered = reorder_copy(p_items, player_side);
        gd::GdArr* o_ordered = reorder_copy(o_items, opponent_side);
        // ★ 全局 Math 流对齐（真源 py gd_core_engine.py:1273-1278）：
        //   ① py 在装配完成之后调 _bind_battle(seed) 重置 Godot 全局链，
        //      抹掉装配期（物品脚本 shuffleEngine 等）对全局链的消耗；
        //      本函数入口的 reset_for_battle() 在装配之前，两者不等价。
        //   ② 原版装配段每个 side 的 items 下标数组各消耗一条 Array.shuffle()
        //      （Fisher-Yates 自后向前 n-1 抽）；结果弃置，仅对齐链状态。
        //      战斗期物品脚本的裸 arr.shuffle()（Eggscalibur.onDealtDamage 的
        //      affected.shuffle()）消费的就是这条链。
        //   ★ 用 battle.math_rng（Math::default_pcg 全局链），
        //     不是 ctx.rng（CoreRng）—— 两者是独立随机流。
        battle.bind_battle(opts.seed);
        for (uint32_t _n : {p_ordered->len, o_ordered->len}) {
            for (int64_t _i = static_cast<int64_t>(_n) - 1; _i > 0; --_i) {
                (void)(battle.math_rng.randi() % static_cast<uint32_t>(_i + 1));
            }
        }
        gd::GdVal sb_args[3] = {gd::GdVal::from_arr(p_ordered), gd::GdVal::from_arr(o_ordered), gd::GdVal::from_bool(true)};
        combat_obj->fn_startBattle(sb_args, 3);
    } else if (opts.native_activation_order) {
        battle.bind_battle(opts.seed);
        // 调试台账：输入装配序 → 下标表（对象指针 → 原下标）
        std::unordered_map<const gd::GdObj*, int32_t> dbg_idx_p, dbg_idx_o;
        for (uint32_t i = 0; i < p_items->len; ++i)
            if (p_items->data[i].kind == gd::GdVal::Kind::Obj && p_items->data[i].obj)
                dbg_idx_p.emplace(p_items->data[i].obj, static_cast<int32_t>(i));
        for (uint32_t i = 0; i < o_items->len; ++i)
            if (o_items->data[i].kind == gd::GdVal::Kind::Obj && o_items->data[i].obj)
                dbg_idx_o.emplace(o_items->data[i].obj, static_cast<int32_t>(i));

        const bool dbg = g_dbg_enabled.load(std::memory_order_relaxed) != 0;
        gd::shuffle_array(battle, p_items);
        if (dbg) record_order(p_items, dbg_idx_p, g_dbg_p_shuffle);
        gd::godot_sort_custom_items(battle, p_items);
        if (dbg) record_order(p_items, dbg_idx_p, g_dbg_p_sorted);
        gd::shuffle_array(battle, o_items);
        if (dbg) record_order(o_items, dbg_idx_o, g_dbg_o_shuffle);
        gd::godot_sort_custom_items(battle, o_items);
        if (dbg) record_order(o_items, dbg_idx_o, g_dbg_o_sorted);
        gd::GdVal sb_args[3] = {gd::GdVal::from_arr(p_items), gd::GdVal::from_arr(o_items), gd::GdVal::from_bool(true)};
        combat_obj->fn_startBattle(sb_args, 3);
    } else {
        gd::GdVal sb_args[3] = {gd::GdVal::from_arr(p_items), gd::GdVal::from_arr(o_items), gd::GdVal::from_bool(false)};
        combat_obj->fn_startBattle(sb_args, 3);
    }

    const int32_t max_ticks = opts.max_ticks > 0 ? opts.max_ticks : 20000;
    const int32_t ev_gate = opts.formal_ev_gate > 0 ? opts.formal_ev_gate : 25000;
    const gd::GdVal dt = gd::GdVal::from_float(1.0 / 60.0);

    int32_t ticks = 0;
    bool ev_capped = false;
    while (!gd::gd_truth(combat_obj->f_fight_ended) && ticks < max_ticks) {
        combat_obj->fn_physicsTick(&dt, 1);
        ticks += 1;
        if (static_cast<int32_t>(battle.event_count) > ev_gate) {
            ev_capped = true;
            break;
        }
    }

    out.player_wins = gd::gd_truth(combat_obj->fn_playerWins(nullptr, 0)) ? 1 : 0;
    out.timed_out = gd::gd_truth(combat_obj->f_timed_out) ? 1 : 0;
    out.formal_ev_capped = ev_capped ? 1 : 0;
    out.combat_time = combat_obj->f_combat_time.as_float();
    out.ticks = ticks;
    out.fatigue_counter = static_cast<int32_t>(combat_obj->f_fatigue_counter.as_int());

    out.player_hp = p_chr->fn_getCurrentHealth(nullptr, 0).as_float();
    out.player_max_hp = p_chr->fn_getMaxHealth(nullptr, 0).as_float();
    out.player_block = p_chr->fn_getBlock(nullptr, 0).as_float();
    out.opponent_hp = o_chr->fn_getCurrentHealth(nullptr, 0).as_float();
    out.opponent_max_hp = o_chr->fn_getMaxHealth(nullptr, 0).as_float();
    out.opponent_block = o_chr->fn_getBlock(nullptr, 0).as_float();

    out.out_of_stamina_count = static_cast<int32_t>(ctx_obj->f_out_of_stamina_count.as_int());
    out.event_count = static_cast<int32_t>(battle.event_count);
    out.player_damage_dealt = battle.player_damage_dealt;
    out.opponent_damage_dealt = battle.opponent_damage_dealt;
    out.player_healing_done = battle.player_healing_done;
    out.opponent_healing_done = battle.opponent_healing_done;
    out.player_crits = battle.player_crits;
    out.opponent_crits = battle.opponent_crits;
    out.player_misses = battle.player_misses;
    out.opponent_misses = battle.opponent_misses;

    if (opts.record_per_item) {
        int32_t n_rec = static_cast<int32_t>(std::min<size_t>(p_item_ptrs.size(), 64));
        out.n_placed_items = n_rec;
        for (int32_t k = 0; k < n_rec; ++k) {
            gd::GdVal im = p_item_ptrs[k]->f_itemMetrics;
            if (im.kind == gd::GdVal::Kind::Arr && im.arr && im.arr->len > 4) {
                out.item_activations[k] = static_cast<int32_t>(im.arr->data[4].as_int());  // ItemMetrics.Activations = 4
            }
        }
    }
}

static thread_local gd::BattleCtx tl_battle_ctx(1u << 20);

}  // namespace

extern "C" {

void gd_sim_run_one(
    const PackedSide* player,
    const PackedSide* opponent,
    const BattleOptions* opts,
    BattleResult* out
) {
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out);
}

// 调试导出：最近一场的 canonical 事件行（见 DbgEv 注释）。行数与逐行取用：
// gd_sim_dbg_event_count() / gd_sim_dbg_event_line(idx)。仅单线程有定义。
void gd_sim_set_dbg_events(int32_t on) {
    g_dbg_enabled.store(on ? 1 : 0, std::memory_order_relaxed);
    if (!on) {
        g_dbg_events.clear();
        g_dbg_p_shuffle.clear(); g_dbg_o_shuffle.clear();
        g_dbg_p_sorted.clear(); g_dbg_o_sorted.clear();
    }
}

int32_t gd_sim_dbg_event_count() {
    return static_cast<int32_t>(g_dbg_events.size());
}

const char* gd_sim_dbg_event_line(int32_t idx) {
    if (idx < 0 || static_cast<size_t>(idx) >= g_dbg_events.size()) return nullptr;
    return g_dbg_events[static_cast<size_t>(idx)].line.c_str();
}

// 调试导出：最近一次 native_activation_order 战斗的 shuffle 后/排序后终序
//（下标相对输入装配序）。side: 0=player 1=opponent；phase: 0=shuffle 1=sorted。
// 仅单线程（run_one）调用有定义；run_batch 多线程下内容不可信。
const int32_t* gd_sim_dbg_order(int32_t side, int32_t phase, int32_t* n) {
    const std::vector<int32_t>* v =
        (side == 0) ? (phase == 0 ? &g_dbg_p_shuffle : &g_dbg_p_sorted)
                    : (phase == 0 ? &g_dbg_o_shuffle : &g_dbg_o_sorted);
    *n = static_cast<int32_t>(v->size());
    return v->empty() ? nullptr : v->data();
}

void gd_sim_run_batch(
    int32_t n_fights,
    const PackedSide* players,
    const PackedSide* opponents,
    const BattleOptions* opts,
    BattleResult* outs,
    int32_t n_threads
) {
    gd_sim_init();
    if (n_fights <= 0) return;
    if (n_threads <= 1 || n_fights == 1) {
        for (int32_t i = 0; i < n_fights; ++i) {
            run_one_internal(tl_battle_ctx, players[i], opponents[i], opts[i], outs[i]);
        }
        return;
    }

    int32_t nw = std::min<int32_t>(n_threads, n_fights);
    std::atomic<int32_t> next_idx{0};
    std::vector<std::thread> workers;
    workers.reserve(nw);
    for (int32_t w = 0; w < nw; ++w) {
        workers.emplace_back([&]() {
            gd::BattleCtx local_ctx(1u << 20);
            while (true) {
                int32_t i = next_idx.fetch_add(1, std::memory_order_relaxed);
                if (i >= n_fights) break;
                run_one_internal(local_ctx, players[i], opponents[i], opts[i], outs[i]);
            }
        });
    }
    for (auto& t : workers) t.join();
}

}  // extern "C"

#include <typeinfo>
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
    gd::SymId socket = 0;
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
struct DbgGemOrigin {
    bool is_gem = false;
    std::string gem;
    std::string host;
    int32_t host_owner = -1;
    int32_t x = 0;
    int32_t y = 0;
    int32_t slot = -1;
};
struct DbgItemOrigin {
    Gd__gd_core__CoreItem* pending = nullptr;
    std::string identifier;
    int32_t cell[3] = {};
    int32_t status = 0;
};
struct DbgEv {
    double ts;
    int32_t type;
    std::string line;
    DbgGemOrigin gem_origin;
    DbgItemOrigin item_origin;
};
static bool g_dbg_item_origins = false;
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

static std::string dbg_item_identifier(gd::GdObj* item) {
    gd::GdVal descriptor, identifier;
    if (item->get_prop(g_syms.descriptor, descriptor) &&
        descriptor.kind == gd::GdVal::Kind::Obj && descriptor.obj &&
        descriptor.obj->get_prop(g_syms.identifier, identifier) &&
        identifier.kind == gd::GdVal::Kind::Str && identifier.str) {
        return {identifier.str->data, identifier.str->len};
    }
    return {};
}

static DbgGemOrigin dbg_gem_origin(const gd::GdVal& origin) {
    DbgGemOrigin result;
    if (origin.kind != gd::GdVal::Kind::Obj || !origin.obj) return result;
    auto* gem = dynamic_cast<Gd__gd_core__CoreItem*>(origin.obj);
    if (!gem || gem->f_ownerType.as_int() != 7) return result;
    result.is_gem = true;
    gd::GdVal socket;
    if (!gem->get_prop(g_syms.socket, socket) || socket.kind != gd::GdVal::Kind::Obj || !socket.obj)
        return result;
    auto* host = dynamic_cast<Gd__gd_core__CoreItem*>(socket.obj);
    if (!host || host->f_gems.kind != gd::GdVal::Kind::Arr || !host->f_gems.arr) return result;
    for (uint32_t i = 0; i < host->f_gems.arr->len; ++i) {
        const auto& equipped = host->f_gems.arr->data[i];
        if (equipped.kind == gd::GdVal::Kind::Obj && equipped.obj == gem) {
            result.slot = static_cast<int32_t>(i);
            break;
        }
    }
    result.gem = dbg_item_identifier(gem);
    result.host = dbg_item_identifier(host);
    auto pos = host->fn_getTopLeftCell(nullptr, 0);
    if (pos.kind == gd::GdVal::Kind::Vec2) {
        result.host_owner = static_cast<int32_t>(host->f_ownerType.as_int());
        result.x = static_cast<int32_t>(pos.v2.x);
        result.y = static_cast<int32_t>(pos.v2.y);
    }
    return result;
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
    DbgItemOrigin item_origin;
    if (g_dbg_item_origins && ov.kind == gd::GdVal::Kind::Obj && ov.obj) {
        auto* item = dynamic_cast<Gd__gd_core__CoreItem*>(ov.obj);
        if (item && item->f_ownerType.as_int() != 7) item_origin.pending = item;
    }
    g_dbg_events.push_back(DbgEv{ts, type, std::move(line), dbg_gem_origin(ov), std::move(item_origin)});
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
    uint16_t n_placement_effects;
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

struct PackedFlicker {
    double position, speed, length, min_dist, max_dist, min_speed, max_speed;
    int32_t playing;
    int32_t attachment;  // 0 off tree, 1 attached, 2 attached under Opponent
    int32_t loop, n_pending;
    const double* pending;
};

struct ReplayInitial {
    int32_t has_activation_state;
    uint64_t activation_state;
    double player_idle_left;
    double opponent_idle_left;
    int32_t n_flickers;
    const PackedFlicker* flickers;
};

struct PackedReplayBuff {
    int32_t side, type, current, permanent;
};

struct ReplayBuffState {
    int32_t count;
    const PackedReplayBuff* rows;
};

struct ReplayEngineRng {
    int64_t prepare_seed, activate_seed;
    int32_t prepare_offset, activate_offset, label_mode;
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
        g_syms.socket = gd::intern_sym("socket");
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
    gd::GdArr* gems_arr = ci->native_make_bridge_gems(battle, static_cast<uint32_t>(std::max<int32_t>(0, _n_sockets)));
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

static void apply_ring_effects(gd::BattleCtx& battle, gd::GdVal item,
                               const PackedEffect* effects, uint16_t count) {
    auto* entries = gd::GdArr::create(battle.arena, count);
    for (uint16_t i = 0; i < count; ++i) {
        auto* effect = gd::GdDict::create(battle.arena, 2);
        effect->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("triggerType")),
                    gd::GdVal::from_int(effects[i].trigger_type));
        effect->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("stackType")),
                    gd::GdVal::from_int(effects[i].stack_type));
        entries->push_back(battle.arena, gd::GdVal::from_dict(effect));
    }
    auto argument = gd::GdVal::from_arr(entries);
    gd::call_method(battle, item, g_syms.setCraftedEffects, &argument, 1);
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

        // Match the ring's _ready -> addItem -> setData sequence. Placement
        // can grant a dynamic type that survives when the saved rolls load.
        if (pi.n_placement_effects && pi.n_effects + pi.n_placement_effects <= 8)
            apply_ring_effects(battle, iv, pi.effects + pi.n_effects, pi.n_placement_effects);

        gd::GdVal add_args[2] = {iv, gd::GdVal::from_arr(occ)};
        gd::call_method(battle, chr->f_inventory, g_syms.addItem, add_args, 2);

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

        if (pi.n_effects > 0 && pi.n_effects <= 8)
            apply_ring_effects(battle, iv, pi.effects, pi.n_effects);

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

struct ReplayHostDraw {
    int32_t tick;
    int32_t phase;
    uint64_t before;
    uint64_t after;
};
static_assert(sizeof(ReplayHostDraw) == 24);

struct ReplayHostRng {
    const ReplayHostDraw* draws;
    int32_t count;
    int32_t next = 0;
    bool invalid = false;
};

static void apply_host_draws(ReplayHostRng& host, Gd__gd_core__CoreContext& context,
                             double combat_time, int32_t phase) {
    if (host.invalid || host.next >= host.count || gd::gd_truth(context.f_fight_ended)) return;
    const auto tick = std::llround(combat_time * 60.0);
    while (host.next < host.count) {
        const auto& draw = host.draws[host.next];
        if (draw.tick > tick || (draw.tick == tick && draw.phase > phase)) return;
        auto* util = static_cast<Gd__gd_core__CoreRng*>(context.f_rng.obj)->f_rng.rng;
        if (draw.tick != tick || draw.phase != phase || util->get_state() != draw.before) {
            host.invalid = true;
            return;
        }
        util->randf_range(10.0, 30.0);
        if (util->get_state() != draw.after) {
            host.invalid = true;
            return;
        }
        ++host.next;
    }
}

static void run_one_internal(
    gd::BattleCtx& battle,
    const PackedSide& player_side,
    const PackedSide& opponent_side,
    const BattleOptions& opts,
    BattleResult& out,
    const ReplayInitial* replay = nullptr,
    const ReplayBuffState* buffs = nullptr,
    const ReplayEngineRng* engine_rng = nullptr,
    bool scene_delays = false,
    double util_time = 0.0,
    ReplayHostRng* host = nullptr,
    bool training_start = false
) {
    std::memset(&out, 0, sizeof(BattleResult));
    battle.reset_for_battle(opts.seed);
    battle.native_inline_timer_headers = true;
    battle.native_event_kernel = true;
    battle.native_resolved_dispatch = true;
    if (g_dbg_enabled.load(std::memory_order_relaxed)) g_dbg_events.clear();  // 逐场清空（仅单线程语义）

    auto* hooks = battle.arena.make<NativeBattleHooks>(&battle);
    hooks->init_fields(battle);

    gd::GdVal ctx_args[2] = {gd::GdVal::from_int(static_cast<int64_t>(opts.seed)), gd::GdVal::from_obj(hooks)};
    gd::GdVal ctx_val = gd::construct_class(battle, &META_Gd__gd_core__CoreContext, ctx_args, 2);
    auto* ctx_obj = static_cast<Gd__gd_core__CoreContext*>(ctx_val.obj);
    ctx_obj->f_show_cooldown_progress = gd::GdVal::from_bool(false);
    if (training_start) {
        ctx_obj->f_training_start = gd::GdVal::from_bool(true);
        ctx_obj->f_native_frame_rng = gd::GdVal::from_bool(true);
        ctx_obj->f_replay_native_scene_delays = gd::GdVal::from_bool(true);
        ctx_obj->f_native_label_mode = gd::GdVal::from_int(opts.label_rng_enabled ? 0 : 3);
    }

    ctx_obj->f_below_master = gd::GdVal::from_bool(opts.below_master != 0);
    ctx_obj->f_custom_health_multiplier = gd::GdVal::from_float(opts.custom_health_multiplier);
    ctx_obj->f_label_rng_enabled = gd::GdVal::from_bool(opts.label_rng_enabled != 0);
    // ★ A3（2026-11-15）：deferred 冲刷开启——与 harness [M15] 帧末冲刷同点同批
    //  （activateItems 后 + 每 tick 末），卡链真实化；冲刷面 rng 中性。
    ctx_obj->f_deferred_flush_enabled = gd::GdVal::from_bool(true);
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

    if (training_start) {
        if (player_side.snapshot_stamina < 0.0) p_chr->fn_recalculateMaxStamina(nullptr, 0);
        if (opponent_side.snapshot_stamina < 0.0) o_chr->fn_recalculateMaxStamina(nullptr, 0);
    }

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

    if (replay) {
        auto* idle = gd::GdArr::create(battle.arena, 2);
        idle->push_back(battle.arena, gd::GdVal::from_float(replay->player_idle_left));
        idle->push_back(battle.arena, gd::GdVal::from_float(replay->opponent_idle_left));
        gd::GdVal flicker_initial;
        if (replay->n_flickers >= 0) {
            auto* states = gd::GdArr::create(battle.arena, replay->n_flickers);
            for (int32_t i = 0; i < replay->n_flickers; ++i) {
                const auto& f = replay->flickers[i];
                auto* state = gd::GdDict::create(battle.arena, 8);
                auto put = [&](const char* key, gd::GdVal value) {
                    state->set(battle.arena, gd::GdVal::from_cstr(battle.arena, key), value);
                };
                put("position", gd::GdVal::from_float(f.position));
                put("speed", gd::GdVal::from_float(f.speed));
                put("length", gd::GdVal::from_float(f.length));
                put("playing", gd::GdVal::from_bool(f.playing != 0));
                put("inside_tree", gd::GdVal::from_bool(f.attachment != 0));
                if (f.attachment == 2) put("native_opponent", gd::GdVal::from_bool(true));
                put("loop", gd::GdVal::from_bool(f.loop != 0));
                auto* limits = gd::GdArr::create(battle.arena, 4);
                for (double value : {f.min_dist, f.max_dist, f.min_speed, f.max_speed})
                    limits->push_back(battle.arena, gd::GdVal::from_float(value));
                put("limits", gd::GdVal::from_arr(limits));
                auto* pending = gd::GdArr::create(battle.arena, f.n_pending);
                for (int32_t j = 0; j < f.n_pending; ++j) {
                    auto* call = gd::GdDict::create(battle.arena, scene_delays ? 4 : 2);
                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "method"), gd::GdVal::from_cstr(battle.arena, "playAni"));
                    const auto offset = scene_delays ? 3 * j : j;
                    call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left"), gd::GdVal::from_float(f.pending[offset]));
                    if (scene_delays) {
                        call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "order"), gd::GdVal::from_int(static_cast<int64_t>(f.pending[offset + 1])));
                        call->set(battle.arena, gd::GdVal::from_cstr(battle.arena, "left_at_first_physics"), gd::GdVal::from_float(f.pending[offset + 2]));
                    }
                    pending->push_back(battle.arena, gd::GdVal::from_dict(call));
                }
                put("pending", gd::GdVal::from_arr(pending));
                states->push_back(battle.arena, gd::GdVal::from_dict(state));
            }
            flicker_initial = gd::GdVal::from_arr(states);
        }
        gd::GdVal buff_initial;
        if (buffs) {
            gd::GdArr* sides[2] = {gd::GdArr::create(battle.arena, 0), gd::GdArr::create(battle.arena, 0)};
            for (int32_t i = 0; i < buffs->count; ++i) {
                const auto& buff = buffs->rows[i];
                auto* row = gd::GdArr::create(battle.arena, 4);
                for (int32_t field : {buff.type, buff.current, buff.permanent, 0})
                    row->push_back(battle.arena, gd::GdVal::from_int(field));
                sides[buff.side]->push_back(battle.arena, gd::GdVal::from_arr(row));
            }
            auto* state = gd::GdArr::create(battle.arena, 2);
            for (auto* side : sides) state->push_back(battle.arena, gd::GdVal::from_arr(side));
            buff_initial = gd::GdVal::from_arr(state);
        }
        gd::GdVal engine_initial;
        if (engine_rng) {
            auto* engine = gd::GdArr::create(battle.arena, 5);
            for (int64_t value : {engine_rng->prepare_seed, int64_t{engine_rng->prepare_offset},
                                  engine_rng->activate_seed, int64_t{engine_rng->activate_offset},
                                  int64_t{engine_rng->label_mode}}) {
                engine->push_back(battle.arena, gd::GdVal::from_int(value));
            }
            engine_initial = gd::GdVal::from_arr(engine);
        }
        gd::GdVal initial[7] = {
            replay->has_activation_state
                ? gd::GdVal::from_int(static_cast<int64_t>(replay->activation_state))
                : gd::GdVal(),
            gd::GdVal::from_arr(idle), flicker_initial, buff_initial, engine_initial, gd::GdVal::from_bool(scene_delays),
            gd::GdVal::from_float(util_time)
        };
        ctx_obj->fn_setReplayInitial(initial, 7);
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
    } else if (opts.native_activation_order || training_start) {
        if (!training_start) battle.bind_battle(opts.seed);
        std::unordered_map<const gd::GdObj*, int32_t> dbg_idx_p, dbg_idx_o;
        const bool dbg = g_dbg_enabled.load(std::memory_order_relaxed) != 0;
        if (dbg) {
            for (uint32_t i = 0; i < p_items->len; ++i)
                if (p_items->data[i].kind == gd::GdVal::Kind::Obj && p_items->data[i].obj)
                    dbg_idx_p.emplace(p_items->data[i].obj, static_cast<int32_t>(i));
            for (uint32_t i = 0; i < o_items->len; ++i)
                if (o_items->data[i].kind == gd::GdVal::Kind::Obj && o_items->data[i].obj)
                    dbg_idx_o.emplace(o_items->data[i].obj, static_cast<int32_t>(i));
        }
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
    const gd::GdVal dt = gd::GdVal::from_float(0.01666666753590107);

    const gd::GdVal tick_args[] = {
        dt, gd::GdVal::from_int(reinterpret_cast<intptr_t>(host))
    };
    int32_t ticks = 0;
    bool ev_capped = false;
    while (!gd::gd_truth(combat_obj->f_fight_ended) && ticks < max_ticks) {
        combat_obj->fn_physicsTick(tick_args, host ? 2 : 1);
        if (host && gd::gd_truth(combat_obj->f_activated)) {
            apply_host_draws(*host, *ctx_obj, combat_obj->f_combat_time.as_float(), 1);
        }
        ticks += 1;
        if (static_cast<int32_t>(battle.event_count) > ev_gate) {
            ev_capped = true;
            break;
        }
    }

    if (g_dbg_item_origins && g_dbg_enabled.load(std::memory_order_relaxed)) {
        // The original recorder reads outstanding item references after the natural terminal.
        for (auto& event : g_dbg_events) {
            auto& origin = event.item_origin;
            auto* item = origin.pending;
            if (!item) continue;
            origin.pending = nullptr;
            origin.identifier = dbg_item_identifier(item);
            const auto cell = item->fn_getTopLeftCell(nullptr, 0);
            if (origin.identifier.empty() || cell.kind != gd::GdVal::Kind::Vec2 ||
                !std::isfinite(cell.v2.x) || !std::isfinite(cell.v2.y)) {
                origin.status = -2;
                continue;
            }
            origin.cell[0] = static_cast<int32_t>(item->f_ownerType.as_int());
            origin.cell[1] = static_cast<int32_t>(cell.v2.x);
            origin.cell[2] = static_cast<int32_t>(cell.v2.y);
            origin.status = 1;
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

void replay_host_before_idle(int64_t control, gd::GdObj* context, double combat_time) {
    auto& host = *reinterpret_cast<ReplayHostRng*>(static_cast<intptr_t>(control));
    auto& ctx = *static_cast<Gd__gd_core__CoreContext*>(context);
    apply_host_draws(host, ctx, combat_time, 0);
}

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

void gd_sim_run_one_training(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out
) {
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, nullptr, nullptr, nullptr,
                     false, 0.0, nullptr, true);
}

void gd_sim_run_one_replay_v2(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial
) {
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial);
}

static bool valid_replay_buffs(const ReplayBuffState& buffs) {
    if (buffs.count < 0 || buffs.count > 22 || (buffs.count && !buffs.rows)) return false;
    for (int32_t i = 0; i < buffs.count; ++i) {
        const auto& row = buffs.rows[i];
        if (row.side < 0 || row.side > 1 || row.type < 100 || row.type > 110) return false;
    }
    return true;
}

void gd_sim_run_one_replay_buff_state(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs
) {
    if (!initial || !buffs || !valid_replay_buffs(*buffs)) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs);
}

static bool valid_engine_rng(const ReplayEngineRng& engine) {
    return engine.prepare_offset >= 0 && engine.prepare_offset < 8192 &&
           engine.activate_offset >= 0 && engine.activate_offset < 8192 &&
           engine.label_mode >= 0 && engine.label_mode <= 3;
}

void gd_sim_run_one_replay_engine_rng(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine
) {
    if (!initial || !engine || (buffs && !valid_replay_buffs(*buffs)) || !valid_engine_rng(*engine)) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine);
}

// With this entry point each PackedFlicker timer is three doubles:
// activation remaining time, creation order and first-physics remaining time.
void gd_sim_run_one_replay_scene_delays(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine))) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine, true);
}

// 调试导出：最近一场的 canonical 事件行（见 DbgEv 注释）。行数与逐行取用：
// gd_sim_dbg_event_count() / gd_sim_dbg_event_line(idx)。仅单线程有定义。
void gd_sim_run_one_replay_native_clock(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine,
    int32_t scene_delays, double util_time
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine)) ||
        !std::isfinite(util_time) || util_time < 0.0) {
        *out = {};
        out->timed_out = 1;
        return;
    }
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine,
                     scene_delays != 0, util_time);
}

int32_t gd_sim_run_one_replay_host_phases(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out, const ReplayInitial* initial,
    const ReplayBuffState* buffs, const ReplayEngineRng* engine,
    int32_t scene_delays, double util_time, const ReplayHostDraw* draws, int32_t count
) {
    if (!initial || (buffs && !valid_replay_buffs(*buffs)) || (engine && !valid_engine_rng(*engine)) ||
        !std::isfinite(util_time) || util_time < 0.0 || !draws || count <= 0) {
        return -1;
    }
    int32_t previous_tick = -1;
    for (int32_t index = 0; index < count; ++index) {
        if (draws[index].tick < 0 || draws[index].tick < previous_tick ||
            draws[index].phase < 0 || draws[index].phase > 1) return -1;
        previous_tick = draws[index].tick;
    }
    gd_sim_init();
    ReplayHostRng host{draws, count};
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, initial, buffs, engine,
                     scene_delays != 0, util_time, &host);
    return host.invalid || host.next != count ? -host.next - 2 : 0;
}

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

// Strings remain valid until the next replay or debug buffer reset.
// Returns 0 for a non-gem event, 1 for complete metadata and -1 otherwise.
void gd_sim_set_dbg_item_origins(int32_t on) {
    g_dbg_item_origins = on != 0;
}

int32_t gd_sim_dbg_event_item_origin(int32_t idx, const char** identifier, int32_t* cell) {
    if (idx < 0 || static_cast<size_t>(idx) >= g_dbg_events.size()) return -1;
    const auto& origin = g_dbg_events[static_cast<size_t>(idx)].item_origin;
    if (origin.status == 1) {
        *identifier = origin.identifier.c_str();
        std::copy_n(origin.cell, 3, cell);
    }
    return origin.status;
}

int32_t gd_sim_dbg_event_gem_origin(int32_t idx, const char** gem, const char** host,
                                    int32_t* coordinates) {
    if (idx < 0 || static_cast<size_t>(idx) >= g_dbg_events.size()) return -1;
    const auto& origin = g_dbg_events[static_cast<size_t>(idx)].gem_origin;
    if (!origin.is_gem) return 0;
    if (origin.host_owner < 0 || origin.slot < 0 || origin.gem.empty() || origin.host.empty())
        return -1;
    *gem = origin.gem.c_str();
    *host = origin.host.c_str();
    coordinates[0] = origin.host_owner;
    coordinates[1] = origin.x;
    coordinates[2] = origin.y;
    coordinates[3] = origin.slot;
    return 1;
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

static void run_batch_internal(
    int32_t n_fights,
    const PackedSide* players,
    const PackedSide* opponents,
    const BattleOptions* opts,
    BattleResult* outs,
    int32_t n_threads,
    bool training_start
) {
    gd_sim_init();
    if (n_fights <= 0) return;
    if (n_threads <= 1 || n_fights == 1 || g_dbg_enabled.load(std::memory_order_relaxed)) {
        for (int32_t i = 0; i < n_fights; ++i) {
            run_one_internal(tl_battle_ctx, players[i], opponents[i], opts[i], outs[i], nullptr, nullptr, nullptr, false, 0.0, nullptr, training_start);
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
                run_one_internal(local_ctx, players[i], opponents[i], opts[i], outs[i], nullptr, nullptr, nullptr, false, 0.0, nullptr, training_start);
            }
        });
    }
    for (auto& t : workers) t.join();
}

void gd_sim_run_batch(
    int32_t n_fights, const PackedSide* players, const PackedSide* opponents,
    const BattleOptions* opts, BattleResult* outs, int32_t n_threads
) {
    run_batch_internal(n_fights, players, opponents, opts, outs, n_threads, false);
}

void gd_sim_run_batch_training(
    int32_t n_fights, const PackedSide* players, const PackedSide* opponents,
    const BattleOptions* opts, BattleResult* outs, int32_t n_threads
) {
    run_batch_internal(n_fights, players, opponents, opts, outs, n_threads, true);
}

}  // extern "C"

bool gd_native_character_snapshots_are_noop(const gd::GdVal& context) {
    if (g_syms.logEvent == SYM_GEN_snapshotCharacterStat_1387) return false;
    if (context.kind != gd::GdVal::Kind::Obj || !context.obj ||
            &typeid(*context.obj) != &typeid(Gd__gd_core__CoreContext)) return false;
    const auto& hooks = static_cast<Gd__gd_core__CoreContext*>(context.obj)->f_hooks;
    return hooks.kind == gd::GdVal::Kind::Obj && hooks.obj &&
        &typeid(*hooks.obj) == &typeid(NativeBattleHooks);
}

gd::GdVal gd_native_event_hooks_call(gd::BattleCtx& ctx,const gd::GdVal& hooks,gd::SymId method,const gd::GdVal* args,int argc) {
    if(hooks.kind!=gd::GdVal::Kind::Obj || !hooks.obj)return gd::call_method(ctx,hooks,method,args,argc);
    if(ctx.native_event_audit && &typeid(*hooks.obj)!=&typeid(NativeBattleHooks)) {
        ++ctx.native_event_counts[4];return gd::call_method(ctx,hooks,method,args,argc);
    }
    gd::GdVal out=gd::GdVal::null();
    static_cast<NativeBattleHooks*>(hooks.obj)->NativeBattleHooks::call_method(ctx,method,args,argc,out);
    return out;
}
extern "C" uint64_t gd_diag_native_event_stat(unsigned field) {return field<5?tl_battle_ctx.native_event_counts[field]:0;}
extern "C" void gd_diag_native_event_audit(int enabled) {tl_battle_ctx.native_event_audit=enabled!=0;}

extern "C" uint64_t gd_diag_native_resolved_stat(unsigned field) {return field<6?tl_battle_ctx.native_resolved_counts[field]:0;}
extern "C" void gd_diag_native_resolved_audit(int enabled) {
    tl_battle_ctx.native_resolved_audit=enabled!=0;
    tl_battle_ctx.native_resolved_collect=enabled!=0;
}

namespace gd {
static thread_local uint64_t native_event_identity_counts[4]{};
void native_event_identity_hit(unsigned index) {if(index<4)++native_event_identity_counts[index];}
}
extern "C" uint64_t gd_diag_native_event_identity_stat(unsigned index) {
    return index<4 ? gd::native_event_identity_counts[index] : 0;
}

namespace gd {
static thread_local uint64_t native_lazy_diagnostic_counts[14]{};
void native_lazy_diagnostic_hit(unsigned site,bool skipped) {if(site<7)++native_lazy_diagnostic_counts[site*2+(skipped?0:1)];}
}
extern "C" uint64_t gd_diag_native_lazy_diagnostic_stat(unsigned index) {return index<14?gd::native_lazy_diagnostic_counts[index]:0;}

namespace gd {
static thread_local uint64_t native_frame_segment_counts[17]{};
void native_frame_segment_hit(unsigned index) {if(index<17)++native_frame_segment_counts[index];}
}
extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned index) {
    return index<17?gd::native_frame_segment_counts[index]:0;
}

namespace gd {
static thread_local uint64_t native_static_collection_counts[3]{};
void native_static_collection_hit(unsigned index){if(index<3)++native_static_collection_counts[index];}
}
extern "C" uint64_t gd_diag_native_static_collection_stat(unsigned index){return index<3?gd::native_static_collection_counts[index]:0;}

namespace gd {
static thread_local uint64_t native_static_setup_counts[4]{};
void native_static_setup_hit(unsigned index){if(index<4)++native_static_setup_counts[index];}
}
extern "C" uint64_t gd_diag_native_static_setup_stat(unsigned index){return index<4?gd::native_static_setup_counts[index]:0;}

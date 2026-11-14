#pragma STDC FP_CONTRACT OFF

#include "gd_rt.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <unordered_map>

namespace gd {

// ─────────────────────────── Static Arena & Symbols ───────────────────────────
BattleArena& static_arena() {
    static BattleArena s_arena(1u << 20, true);
    return s_arena;
}

static std::mutex& sym_mtx() {
    static std::mutex* m = new std::mutex();
    return *m;
}

static std::unordered_map<std::string_view, SymId>& sym_map() {
    static std::unordered_map<std::string_view, SymId>* m = new std::unordered_map<std::string_view, SymId>();
    return *m;
}

static std::vector<const char*>& sym_names_vec() {
    static std::vector<const char*>* v = new std::vector<const char*>({""});
    return *v;
}

static void register_sym_unlocked(SymId id, std::string_view sv) {
    auto& v = sym_names_vec();
    if (id >= v.size()) v.resize(id + 1, "");
    char* copy = static_arena().alloc_array<char>(sv.size() + 1);
    std::memcpy(copy, sv.data(), sv.size());
    copy[sv.size()] = '\0';
    v[id] = copy;
    sym_map()[std::string_view(copy, sv.size())] = id;
}

static void ensure_builtin_syms_unlocked() {
    static bool inited = false;
    if (inited) return;
    inited = true;
#define GD_X_REG(name, str) register_sym_unlocked(name, str);
    GD_BUILTIN_SYMS(GD_X_REG)
#undef GD_X_REG
}

void register_sym(SymId id, std::string_view sv) {
    std::lock_guard<std::mutex> lk(sym_mtx());
    register_sym_unlocked(id, sv);
}

SymId intern_sym(std::string_view sv) {
    std::lock_guard<std::mutex> lk(sym_mtx());
    ensure_builtin_syms_unlocked();
    auto& m = sym_map();
    auto it = m.find(sv);
    if (it != m.end()) return it->second;
    auto& v = sym_names_vec();
    SymId id = static_cast<SymId>(v.size());
    if (id < SYM_BUILTIN_END) id = SYM_BUILTIN_END;
    register_sym_unlocked(id, sv);
    return id;
}

const char* sym_name(SymId id) {
    std::lock_guard<std::mutex> lk(sym_mtx());
    ensure_builtin_syms_unlocked();
    const auto& v = sym_names_vec();
    if (id < v.size() && v[id]) return v[id];
    return "";
}

// ─────────────────────────── Strings ───────────────────────────
const GdStr* make_str(BattleArena& arena, const char* s, uint32_t len) {
    auto* gs = arena.make<GdStr>();
    char* buf = arena.alloc_array<char>(len + 1);
    if (len > 0) std::memcpy(buf, s, len);
    buf[len] = '\0';
    gs->data = buf;
    gs->len = len;
    gs->hash = fnv1a_32(buf, len);
    return gs;
}

const GdStr* make_str(BattleArena& arena, std::string_view sv) {
    return make_str(arena, sv.data(), static_cast<uint32_t>(sv.size()));
}

const GdStr* make_static_str(std::string_view sv) {
    return make_str(static_arena(), sv);
}

const GdStr* str_concat(BattleArena& arena, const GdStr* a, const GdStr* b) {
    uint32_t al = a ? a->len : 0;
    uint32_t bl = b ? b->len : 0;
    auto* gs = arena.make<GdStr>();
    char* buf = arena.alloc_array<char>(al + bl + 1);
    if (al > 0) std::memcpy(buf, a->data, al);
    if (bl > 0) std::memcpy(buf + al, b->data, bl);
    buf[al + bl] = '\0';
    gs->data = buf;
    gs->len = al + bl;
    gs->hash = fnv1a_32(buf, al + bl);
    return gs;
}

// ─────────────────────────── Named Colors (Godot 3.6) ───────────────────────────
struct NamedColor { const char* name; double r, g, b, a; };
static const NamedColor NAMED_COLORS[] = {
    {"aliceblue", 0.9411764740943909, 0.9725490212440491, 1.0, 1.0},
    {"antiquewhite", 0.9803921580314636, 0.9215686321258545, 0.843137264251709, 1.0},
    {"aqua", 0.0, 1.0, 1.0, 1.0},
    {"aquamarine", 0.49803921580314636, 1.0, 0.8313725590705872, 1.0},
    {"azure", 0.9411764740943909, 1.0, 1.0, 1.0},
    {"beige", 0.9607843160629272, 0.9607843160629272, 0.8627451062202454, 1.0},
    {"bisque", 1.0, 0.8941176533699036, 0.7686274647712708, 1.0},
    {"black", 0.0, 0.0, 0.0, 1.0},
    {"blanchedalmond", 1.0, 0.9215686321258545, 0.8039215803146362, 1.0},
    {"blue", 0.0, 0.0, 1.0, 1.0},
    {"blueviolet", 0.5411764979362488, 0.16862745583057404, 0.886274516582489, 1.0},
    {"brown", 0.6470588445663452, 0.16470588743686676, 0.16470588743686676, 1.0},
    {"burlywood", 0.8705882430076599, 0.7215686440467834, 0.529411792755127, 1.0},
    {"cadetblue", 0.37254902720451355, 0.6196078658103943, 0.6274510025978088, 1.0},
    {"chartreuse", 0.49803921580314636, 1.0, 0.0, 1.0},
    {"chocolate", 0.8235294222831726, 0.4117647111415863, 0.11764705926179886, 1.0},
    {"coral", 1.0, 0.49803921580314636, 0.3137255012989044, 1.0},
    {"cornflower", 0.3921568691730499, 0.5843137502670288, 0.929411768913269, 1.0},
    {"cornsilk", 1.0, 0.9725490212440491, 0.8627451062202454, 1.0},
    {"crimson", 0.8627451062202454, 0.0784313753247261, 0.23529411852359772, 1.0},
    {"cyan", 0.0, 1.0, 1.0, 1.0},
    {"darkblue", 0.0, 0.0, 0.545098066329956, 1.0},
    {"darkcyan", 0.0, 0.545098066329956, 0.545098066329956, 1.0},
    {"darkgoldenrod", 0.7215686440467834, 0.5254902243614197, 0.04313725605607033, 1.0},
    {"darkgray", 0.6627451181411743, 0.6627451181411743, 0.6627451181411743, 1.0},
    {"darkgreen", 0.0, 0.3921568691730499, 0.0, 1.0},
    {"darkkhaki", 0.7411764860153198, 0.7176470756530762, 0.41960784792900085, 1.0},
    {"darkmagenta", 0.545098066329956, 0.0, 0.545098066329956, 1.0},
    {"darkolivegreen", 0.3333333432674408, 0.41960784792900085, 0.18431372940540314, 1.0},
    {"darkorange", 1.0, 0.5490196347236633, 0.0, 1.0},
    {"darkorchid", 0.6000000238418579, 0.19607843458652496, 0.800000011920929, 1.0},
    {"darkred", 0.545098066329956, 0.0, 0.0, 1.0},
    {"darksalmon", 0.9137254953384399, 0.5882353186607361, 0.47843137383461, 1.0},
    {"darkseagreen", 0.5607843399047852, 0.7372549176216125, 0.5607843399047852, 1.0},
    {"darkslateblue", 0.2823529541492462, 0.239215686917305, 0.545098066329956, 1.0},
    {"darkslategray", 0.18431372940540314, 0.30980393290519714, 0.30980393290519714, 1.0},
    {"darkturquoise", 0.0, 0.8078431487083435, 0.8196078538894653, 1.0},
    {"darkviolet", 0.5803921818733215, 0.0, 0.8274509906768799, 1.0},
    {"deeppink", 1.0, 0.0784313753247261, 0.5764706134796143, 1.0},
    {"deepskyblue", 0.0, 0.7490196228027344, 1.0, 1.0},
    {"dimgray", 0.4117647111415863, 0.4117647111415863, 0.4117647111415863, 1.0},
    {"dodgerblue", 0.11764705926179886, 0.5647059082984924, 1.0, 1.0},
    {"firebrick", 0.6980392336845398, 0.13333334028720856, 0.13333334028720856, 1.0},
    {"floralwhite", 1.0, 0.9803921580314636, 0.9411764740943909, 1.0},
    {"forestgreen", 0.13333334028720856, 0.545098066329956, 0.13333334028720856, 1.0},
    {"fuchsia", 1.0, 0.0, 1.0, 1.0},
    {"gainsboro", 0.8627451062202454, 0.8627451062202454, 0.8627451062202454, 1.0},
    {"ghostwhite", 0.9725490212440491, 0.9725490212440491, 1.0, 1.0},
    {"gold", 1.0, 0.843137264251709, 0.0, 1.0},
    {"goldenrod", 0.8549019694328308, 0.6470588445663452, 0.125490203499794, 1.0},
    {"gray", 0.7450980544090271, 0.7450980544090271, 0.7450980544090271, 1.0},
    {"green", 0.0, 1.0, 0.0, 1.0},
    {"greenyellow", 0.6784313917160034, 1.0, 0.18431372940540314, 1.0},
    {"honeydew", 0.9411764740943909, 1.0, 0.9411764740943909, 1.0},
    {"hotpink", 1.0, 0.4117647111415863, 0.7058823704719543, 1.0},
    {"indianred", 0.8039215803146362, 0.3607843220233917, 0.3607843220233917, 1.0},
    {"indigo", 0.29411765933036804, 0.0, 0.5098039507865906, 1.0},
    {"ivory", 1.0, 1.0, 0.9411764740943909, 1.0},
    {"khaki", 0.9411764740943909, 0.9019607901573181, 0.5490196347236633, 1.0},
    {"lavender", 0.9019607901573181, 0.9019607901573181, 0.9803921580314636, 1.0},
    {"lavenderblush", 1.0, 0.9411764740943909, 0.9607843160629272, 1.0},
    {"lawngreen", 0.48627451062202454, 0.9882352948188782, 0.0, 1.0},
    {"lemonchiffon", 1.0, 0.9803921580314636, 0.8039215803146362, 1.0},
    {"lightblue", 0.6784313917160034, 0.8470588326454163, 0.9019607901573181, 1.0},
    {"lightcoral", 0.9411764740943909, 0.501960813999176, 0.501960813999176, 1.0},
    {"lightcyan", 0.8784313797950745, 1.0, 1.0, 1.0},
    {"lightgoldenrod", 0.9803921580314636, 0.9803921580314636, 0.8235294222831726, 1.0},
    {"lightgray", 0.8274509906768799, 0.8274509906768799, 0.8274509906768799, 1.0},
    {"lightgreen", 0.5647059082984924, 0.9333333373069763, 0.5647059082984924, 1.0},
    {"lightpink", 1.0, 0.7137255072593689, 0.7568627595901489, 1.0},
    {"lightsalmon", 1.0, 0.6274510025978088, 0.47843137383461, 1.0},
    {"lightseagreen", 0.125490203499794, 0.6980392336845398, 0.6666666865348816, 1.0},
    {"lightskyblue", 0.529411792755127, 0.8078431487083435, 0.9803921580314636, 1.0},
    {"lightslategray", 0.46666666865348816, 0.5333333611488342, 0.6000000238418579, 1.0},
    {"lightsteelblue", 0.6901960968971252, 0.7686274647712708, 0.8705882430076599, 1.0},
    {"lightyellow", 1.0, 1.0, 0.8784313797950745, 1.0},
    {"lime", 0.0, 1.0, 0.0, 1.0},
    {"limegreen", 0.19607843458652496, 0.8039215803146362, 0.19607843458652496, 1.0},
    {"linen", 0.9803921580314636, 0.9411764740943909, 0.9019607901573181, 1.0},
    {"magenta", 1.0, 0.0, 1.0, 1.0},
    {"maroon", 0.6901960968971252, 0.1882352977991104, 0.3764705955982208, 1.0},
    {"mediumaquamarine", 0.4000000059604645, 0.8039215803146362, 0.6666666865348816, 1.0},
    {"mediumblue", 0.0, 0.0, 0.8039215803146362, 1.0},
    {"mediumorchid", 0.729411780834198, 0.3333333432674408, 0.8274509906768799, 1.0},
    {"mediumpurple", 0.5764706134796143, 0.43921568989753723, 0.8588235378265381, 1.0},
    {"mediumseagreen", 0.23529411852359772, 0.7019608020782471, 0.4431372582912445, 1.0},
    {"mediumslateblue", 0.48235294222831726, 0.40784314274787903, 0.9333333373069763, 1.0},
    {"mediumspringgreen", 0.0, 0.9803921580314636, 0.6039215922355652, 1.0},
    {"mediumturquoise", 0.2823529541492462, 0.8196078538894653, 0.800000011920929, 1.0},
    {"mediumvioletred", 0.7803921699523926, 0.08235294371843338, 0.5215686559677124, 1.0},
    {"midnightblue", 0.09803921729326248, 0.09803921729326248, 0.43921568989753723, 1.0},
    {"mintcream", 0.9607843160629272, 1.0, 0.9803921580314636, 1.0},
    {"mistyrose", 1.0, 0.8941176533699036, 0.8823529481887817, 1.0},
    {"moccasin", 1.0, 0.8941176533699036, 0.7098039388656616, 1.0},
    {"navajowhite", 1.0, 0.8705882430076599, 0.6784313917160034, 1.0},
    {"navyblue", 0.0, 0.0, 0.501960813999176, 1.0},
    {"oldlace", 0.9921568632125854, 0.9607843160629272, 0.9019607901573181, 1.0},
    {"olive", 0.501960813999176, 0.501960813999176, 0.0, 1.0},
    {"olivedrab", 0.41960784792900085, 0.5568627715110779, 0.13725490868091583, 1.0},
    {"orange", 1.0, 0.6470588445663452, 0.0, 1.0},
    {"orangered", 1.0, 0.2705882489681244, 0.0, 1.0},
    {"orchid", 0.8549019694328308, 0.43921568989753723, 0.8392156958580017, 1.0},
    {"palegoldenrod", 0.9333333373069763, 0.9098039269447327, 0.6666666865348816, 1.0},
    {"palegreen", 0.5960784554481506, 0.9843137264251709, 0.5960784554481506, 1.0},
    {"paleturquoise", 0.686274528503418, 0.9333333373069763, 0.9333333373069763, 1.0},
    {"palevioletred", 0.8588235378265381, 0.43921568989753723, 0.5764706134796143, 1.0},
    {"papayawhip", 1.0, 0.9372549057006836, 0.8352941274642944, 1.0},
    {"peachpuff", 1.0, 0.8549019694328308, 0.7254902124404907, 1.0},
    {"peru", 0.8039215803146362, 0.5215686559677124, 0.24705882370471954, 1.0},
    {"pink", 1.0, 0.7529411911964417, 0.7960784435272217, 1.0},
    {"plum", 0.8666666746139526, 0.6274510025978088, 0.8666666746139526, 1.0},
    {"powderblue", 0.6901960968971252, 0.8784313797950745, 0.9019607901573181, 1.0},
    {"purple", 0.6274510025978088, 0.125490203499794, 0.9411764740943909, 1.0},
    {"rebeccapurple", 0.4000000059604645, 0.20000000298023224, 0.6000000238418579, 1.0},
    {"red", 1.0, 0.0, 0.0, 1.0},
    {"rosybrown", 0.7372549176216125, 0.5607843399047852, 0.5607843399047852, 1.0},
    {"royalblue", 0.2549019753932953, 0.4117647111415863, 0.8823529481887817, 1.0},
    {"saddlebrown", 0.545098066329956, 0.2705882489681244, 0.07450980693101883, 1.0},
    {"salmon", 0.9803921580314636, 0.501960813999176, 0.4470588266849518, 1.0},
    {"sandybrown", 0.95686274766922, 0.6431372761726379, 0.3764705955982208, 1.0},
    {"seagreen", 0.18039216101169586, 0.545098066329956, 0.34117648005485535, 1.0},
    {"seashell", 1.0, 0.9607843160629272, 0.9333333373069763, 1.0},
    {"sienna", 0.6274510025978088, 0.32156863808631897, 0.1764705926179886, 1.0},
    {"silver", 0.7529411911964417, 0.7529411911964417, 0.7529411911964417, 1.0},
    {"skyblue", 0.529411792755127, 0.8078431487083435, 0.9215686321258545, 1.0},
    {"slateblue", 0.4156862795352936, 0.3529411852359772, 0.8039215803146362, 1.0},
    {"slategray", 0.43921568989753723, 0.501960813999176, 0.5647059082984924, 1.0},
    {"snow", 1.0, 0.9803921580314636, 0.9803921580314636, 1.0},
    {"springgreen", 0.0, 1.0, 0.49803921580314636, 1.0},
    {"steelblue", 0.27450981736183167, 0.5098039507865906, 0.7058823704719543, 1.0},
    {"tan", 0.8235294222831726, 0.7058823704719543, 0.5490196347236633, 1.0},
    {"teal", 0.0, 0.501960813999176, 0.501960813999176, 1.0},
    {"thistle", 0.8470588326454163, 0.7490196228027344, 0.8470588326454163, 1.0},
    {"tomato", 1.0, 0.38823530077934265, 0.27843138575553894, 1.0},
    {"transparent", 1.0, 1.0, 1.0, 0.0},
    {"turquoise", 0.250980406999588, 0.8784313797950745, 0.8156862854957581, 1.0},
    {"violet", 0.9333333373069763, 0.5098039507865906, 0.9333333373069763, 1.0},
    {"webgray", 0.501960813999176, 0.501960813999176, 0.501960813999176, 1.0},
    {"webgreen", 0.0, 0.501960813999176, 0.0, 1.0},
    {"webmaroon", 0.501960813999176, 0.0, 0.0, 1.0},
    {"webpurple", 0.501960813999176, 0.0, 0.501960813999176, 1.0},
    {"wheat", 0.9607843160629272, 0.8705882430076599, 0.7019608020782471, 1.0},
    {"white", 1.0, 1.0, 1.0, 1.0},
    {"whitesmoke", 0.9607843160629272, 0.9607843160629272, 0.9607843160629272, 1.0},
    {"yellow", 1.0, 1.0, 0.0, 1.0},
    {"yellowgreen", 0.6039215922355652, 0.8039215803146362, 0.19607843458652496, 1.0},
};

GdVal get_named_color(std::string_view name) {
    for (const auto& c : NAMED_COLORS) {
        if (name == c.name) {
            auto* gc = static_arena().make<GdColor>(GdColor{c.r, c.g, c.b, c.a});
            return GdVal::from_color(gc);
        }
    }
    return GdVal::null();
}

GdVal make_color_from_args(const GdVal* args, int argc) {
    GdColor col;
    if (argc == 1 && args[0].kind == GdVal::Kind::Str) {
        std::string low;
        for (uint32_t i = 0; i < args[0].str->len; ++i)
            low.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(args[0].str->data[i]))));
        GdVal nc = get_named_color(low);
        if (!nc.is_null()) return nc;
    } else if (argc >= 3) {
        col.r = args[0].as_float();
        col.g = args[1].as_float();
        col.b = args[2].as_float();
        col.a = (argc >= 4) ? args[3].as_float() : 1.0;
    } else if (argc == 1 && args[0].kind == GdVal::Kind::Color && args[0].col) {
        col = *args[0].col;
    }
    auto* gc = static_arena().make<GdColor>(col);
    return GdVal::from_color(gc);
}

// ─────────────────────────── Equality, Ordering, Hash, Truth, String ───────────────────────────
bool gd_truth(const GdVal& v) {
    switch (v.kind) {
        case GdVal::Kind::Null: return false;
        case GdVal::Kind::Bool: return v.b;
        case GdVal::Kind::Int: return v.i != 0;
        case GdVal::Kind::Float: return v.f != 0.0;
        case GdVal::Kind::Vec2: return v.v2.x != 0.0 || v.v2.y != 0.0;
        case GdVal::Kind::Color: return v.col && (v.col->r != 0.0 || v.col->g != 0.0 || v.col->b != 0.0 || v.col->a != 0.0);
        case GdVal::Kind::Str: return v.str && v.str->len > 0;
        case GdVal::Kind::Arr: return v.arr && v.arr->len > 0;
        case GdVal::Kind::Dict: return v.dict && v.dict->len > 0;
        default: return true;
    }
}

bool gd_eq(const GdVal& a, const GdVal& b) {
    if (a.kind == b.kind) {
        switch (a.kind) {
            case GdVal::Kind::Null: return true;
            case GdVal::Kind::Bool: return a.b == b.b;
            case GdVal::Kind::Int: return a.i == b.i;
            case GdVal::Kind::Float: return a.f == b.f;
            case GdVal::Kind::Vec2: return a.v2 == b.v2;
            case GdVal::Kind::Color: return a.col && b.col ? (*a.col == *b.col) : (a.col == b.col);
            case GdVal::Kind::Str:
                if (a.str == b.str) return true;
                if (!a.str || !b.str) return false;
                return a.str->len == b.str->len && a.str->hash == b.str->hash &&
                       std::memcmp(a.str->data, b.str->data, a.str->len) == 0;
            case GdVal::Kind::Arr:
                if (a.arr == b.arr) return true;
                if (!a.arr || !b.arr || a.arr->len != b.arr->len) return false;
                for (uint32_t i = 0; i < a.arr->len; ++i)
                    if (!gd_eq(a.arr->data[i], b.arr->data[i])) return false;
                return true;
            case GdVal::Kind::Dict: return a.dict == b.dict;
            case GdVal::Kind::Obj: return a.obj == b.obj;
            case GdVal::Kind::ClassRef: return a.cls == b.cls;
            case GdVal::Kind::Enum: return a.en == b.en;
            case GdVal::Kind::FuncRef: return a.fr == b.fr;
            case GdVal::Kind::Rng: return a.rng == b.rng;
        }
    }
    if (a.is_num() && b.is_num()) {
        if ((a.kind == GdVal::Kind::Int || a.kind == GdVal::Kind::Bool) &&
            (b.kind == GdVal::Kind::Int || b.kind == GdVal::Kind::Bool)) {
            return a.as_int() == b.as_int();
        }
        return a.as_float() == b.as_float();
    }
    return false;
}

bool gd_lt(const GdVal& a, const GdVal& b) {
    if (a.is_num() && b.is_num()) return a.as_float() < b.as_float();
    if (a.kind == GdVal::Kind::Str && b.kind == GdVal::Kind::Str) {
        return std::string_view(a.str->data, a.str->len) < std::string_view(b.str->data, b.str->len);
    }
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) {
        if (a.v2.x == b.v2.x) return a.v2.y < b.v2.y;
        return a.v2.x < b.v2.x;
    }
    return false;
}

bool gd_le(const GdVal& a, const GdVal& b) {
    if (a.is_num() && b.is_num()) return a.as_float() <= b.as_float();
    if (a.kind == GdVal::Kind::Str && b.kind == GdVal::Kind::Str) {
        return std::string_view(a.str->data, a.str->len) <= std::string_view(b.str->data, b.str->len);
    }
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) {
        return a.v2.x < b.v2.x || (a.v2.x == b.v2.x && a.v2.y <= b.v2.y);
    }
    return false;
}

static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

uint64_t gd_val_hash(const GdVal& v) {
    switch (v.kind) {
        case GdVal::Kind::Null: return 0x1234567ULL;
        case GdVal::Kind::Bool: return splitmix64(v.b ? 1ULL : 0ULL);
        case GdVal::Kind::Int: return splitmix64(static_cast<uint64_t>(v.i));
        case GdVal::Kind::Float: {
            if (std::isfinite(v.f) && v.f >= -9e18 && v.f <= 9e18) {
                int64_t iv = static_cast<int64_t>(v.f);
                if (static_cast<double>(iv) == v.f) return splitmix64(static_cast<uint64_t>(iv));
            }
            uint64_t bits = 0;
            double d = (v.f == 0.0) ? 0.0 : v.f;
            std::memcpy(&bits, &d, 8);
            return splitmix64(bits);
        }
        case GdVal::Kind::Vec2: {
            uint64_t bx = 0, by = 0;
            double x = (v.v2.x == 0.0) ? 0.0 : v.v2.x;
            double y = (v.v2.y == 0.0) ? 0.0 : v.v2.y;
            std::memcpy(&bx, &x, 8);
            std::memcpy(&by, &y, 8);
            return splitmix64(bx) ^ (splitmix64(by) * 0x9e3779b97f4a7c15ULL);
        }
        case GdVal::Kind::Str: return v.str ? splitmix64(v.str->hash) : 0ULL;
        case GdVal::Kind::Obj: return splitmix64(reinterpret_cast<uintptr_t>(v.obj));
        case GdVal::Kind::ClassRef: return splitmix64(reinterpret_cast<uintptr_t>(v.cls));
        case GdVal::Kind::Enum: return splitmix64(reinterpret_cast<uintptr_t>(v.en));
        default: return splitmix64(reinterpret_cast<uintptr_t>(v.obj));
    }
}

static void append_gd_str(std::string& out, const GdVal& v) {
    char buf[128];
    switch (v.kind) {
        case GdVal::Kind::Null: out += "Null"; break;
        case GdVal::Kind::Bool: out += (v.b ? "True" : "False"); break;
        case GdVal::Kind::Int:
            std::snprintf(buf, sizeof(buf), "%lld", static_cast<long long>(v.i));
            out += buf;
            break;
        case GdVal::Kind::Float:
            if (std::isfinite(v.f) && std::abs(v.f) < 1e16 && v.f == static_cast<double>(static_cast<int64_t>(v.f))) {
                std::snprintf(buf, sizeof(buf), "%lld", static_cast<long long>(static_cast<int64_t>(v.f)));
            } else {
                std::snprintf(buf, sizeof(buf), "%.17g", v.f);
            }
            out += buf;
            break;
        case GdVal::Kind::Vec2:
            out.push_back('(');
            append_gd_str(out, GdVal::from_float(v.v2.x));
            out += ", ";
            append_gd_str(out, GdVal::from_float(v.v2.y));
            out.push_back(')');
            break;
        case GdVal::Kind::Str:
            if (v.str) out.append(v.str->data, v.str->len);
            break;
        case GdVal::Kind::Arr:
            out.push_back('[');
            if (v.arr) {
                for (uint32_t i = 0; i < v.arr->len; ++i) {
                    if (i) out += ", ";
                    append_gd_str(out, v.arr->data[i]);
                }
            }
            out.push_back(']');
            break;
        case GdVal::Kind::Dict:
            out.push_back('{');
            if (v.dict) {
                for (uint32_t i = 0; i < v.dict->len; ++i) {
                    if (i) out += ", ";
                    append_gd_str(out, v.dict->entries[i].key);
                    out += ": ";
                    append_gd_str(out, v.dict->entries[i].val);
                }
            }
            out.push_back('}');
            break;
        case GdVal::Kind::ClassRef:
            out += v.cls ? v.cls->class_name : "<Class>";
            break;
        case GdVal::Kind::Enum:
            out += v.en ? v.en->name : "<Enum>";
            break;
        case GdVal::Kind::Obj:
            out += v.obj ? v.obj->meta()->class_name : "Null";
            break;
        default:
            out += "<Obj>";
            break;
    }
}

const GdStr* gd_to_str(BattleArena& arena, const GdVal& v) {
    if (v.kind == GdVal::Kind::Str && v.str) return v.str;
    std::string s;
    append_gd_str(s, v);
    return make_str(arena, s);
}

GdVal gd_coerce_int(const GdVal& v) { return GdVal::from_int(v.as_int()); }
GdVal gd_coerce_float(const GdVal& v) { return GdVal::from_float(v.as_float()); }
GdVal gd_coerce_bool(const GdVal& v) { return GdVal::from_bool(gd_truth(v)); }

// ─────────────────────────── Arithmetic & Builtins ───────────────────────────
GdVal gd_add(BattleCtx& ctx, const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) return GdVal::from_int(a.i + b.i);
    if (a.is_num() && b.is_num()) return GdVal::from_float(a.as_float() + b.as_float());
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(a.v2 + b.v2);
    if (a.kind == GdVal::Kind::Str && b.kind == GdVal::Kind::Str) {
        return GdVal::from_str(str_concat(ctx.arena, a.str, b.str));
    }
    if (a.kind == GdVal::Kind::Arr && b.kind == GdVal::Kind::Arr) {
        auto* out = GdArr::create(ctx.arena, (a.arr ? a.arr->len : 0) + (b.arr ? b.arr->len : 0));
        if (a.arr) out->append_array(ctx.arena, a.arr);
        if (b.arr) out->append_array(ctx.arena, b.arr);
        return GdVal::from_arr(out);
    }
    return GdVal::null();
}

GdVal gd_sub(const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) return GdVal::from_int(a.i - b.i);
    if (a.is_num() && b.is_num()) return GdVal::from_float(a.as_float() - b.as_float());
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(a.v2 - b.v2);
    return GdVal::null();
}

GdVal gd_mul(const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) return GdVal::from_int(a.i * b.i);
    if (a.is_num() && b.is_num()) return GdVal::from_float(a.as_float() * b.as_float());
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(a.v2 * b.v2);
    if (a.kind == GdVal::Kind::Vec2 && b.is_num()) return GdVal::from_vec2(a.v2 * b.as_float());
    if (a.is_num() && b.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(b.v2 * a.as_float());
    return GdVal::null();
}

GdVal gd_div(BattleCtx& ctx, const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) {
        if (b.i == 0) return GdVal::from_int(0);
        return GdVal::from_int(a.i / b.i);
    }
    if (a.is_num() && b.is_num()) return GdVal::from_float(a.as_float() / b.as_float());
    if (a.kind == GdVal::Kind::Vec2 && b.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(a.v2 / b.v2);
    if (a.kind == GdVal::Kind::Vec2 && b.is_num()) return GdVal::from_vec2(a.v2 / b.as_float());
    return GdVal::null();
}

GdVal gd_mod(BattleCtx& ctx, const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Str) return gd_fmt(ctx.arena, a, b);
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) {
        if (b.i == 0) return GdVal::from_int(0);
        return GdVal::from_int(a.i % b.i);
    }
    if (a.is_num() && b.is_num()) return GdVal::from_float(std::fmod(a.as_float(), b.as_float()));
    return GdVal::null();
}

GdVal gd_neg(const GdVal& a) {
    if (a.kind == GdVal::Kind::Int) return GdVal::from_int(-a.i);
    if (a.kind == GdVal::Kind::Bool) return GdVal::from_int(-(a.b ? 1 : 0));
    if (a.kind == GdVal::Kind::Float) return GdVal::from_float(-a.f);
    if (a.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(-a.v2);
    return GdVal::null();
}

GdVal gd_pos(const GdVal& a) { return a; }

GdVal gd_bitand(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() & b.as_int()); }
GdVal gd_bitor(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() | b.as_int()); }
GdVal gd_bitxor(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() ^ b.as_int()); }
GdVal gd_bitnot(const GdVal& a) { return GdVal::from_int(~a.as_int()); }
GdVal gd_shl(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() << b.as_int()); }
GdVal gd_shr(const GdVal& a, const GdVal& b) { return GdVal::from_int(a.as_int() >> b.as_int()); }

GdVal gd_abs(const GdVal& x) {
    if (x.kind == GdVal::Kind::Int) return GdVal::from_int(x.i < 0 ? -x.i : x.i);
    if (x.kind == GdVal::Kind::Vec2) return GdVal::from_vec2(std::abs(x.v2.x), std::abs(x.v2.y));
    return GdVal::from_float(std::abs(x.as_float()));
}

GdVal gd_min(const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) return GdVal::from_int(a.i < b.i ? a.i : b.i);
    double af = a.as_float(), bf = b.as_float();
    return GdVal::from_float(af < bf ? af : bf);
}

GdVal gd_max(const GdVal& a, const GdVal& b) {
    if (a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int) return GdVal::from_int(a.i > b.i ? a.i : b.i);
    double af = a.as_float(), bf = b.as_float();
    return GdVal::from_float(af > bf ? af : bf);
}

GdVal gd_clamp(const GdVal& v, const GdVal& lo, const GdVal& hi) {
    if (v.kind == GdVal::Kind::Int && lo.kind == GdVal::Kind::Int && hi.kind == GdVal::Kind::Int) {
        int64_t r = v.i < lo.i ? lo.i : (v.i > hi.i ? hi.i : v.i);
        return GdVal::from_int(r);
    }
    double vf = v.as_float(), lof = lo.as_float(), hif = hi.as_float();
    return GdVal::from_float(vf < lof ? lof : (vf > hif ? hif : vf));
}

GdVal gd_floor(const GdVal& x) { return GdVal::from_float(std::floor(x.as_float())); }
GdVal gd_ceil(const GdVal& x) { return GdVal::from_float(std::ceil(x.as_float())); }
GdVal gd_round(const GdVal& x) {
    double v = x.as_float();
    return GdVal::from_float(v >= 0.0 ? std::floor(v + 0.5) : -std::floor(-v + 0.5));
}

GdVal gd_stepify(const GdVal& v, const GdVal& step) {
    if (step.as_float() == 0.0) return v;
    if (v.kind == GdVal::Kind::Int && step.kind == GdVal::Kind::Int) {
        return GdVal::from_float(std::floor(static_cast<double>(v.i / step.i) + 0.5) * static_cast<double>(step.i));
    }
    double sf = step.as_float();
    return GdVal::from_float(std::floor(v.as_float() / sf + 0.5) * sf);
}

GdVal gd_snapped(const GdVal& v, const GdVal& step) {
    double sf = step.as_float();
    if (sf == 0.0) return v;
    return GdVal::from_float(std::floor(v.as_float() / sf + 0.5) * sf);
}

GdVal gd_fmod(const GdVal& x, const GdVal& y) { return GdVal::from_float(std::fmod(x.as_float(), y.as_float())); }
GdVal gd_posmod(const GdVal& x, const GdVal& y) {
    double a = x.as_float(), b = y.as_float();
    double r = std::fmod(a, b);
    if ((r < 0 && b > 0) || (r > 0 && b < 0)) r += b;
    return GdVal::from_float(r);
}
GdVal gd_sqrt(const GdVal& x) {
    double v = x.as_float();
    if (v < 0.0) return GdVal::from_float(std::numeric_limits<double>::quiet_NaN());
    return GdVal::from_float(std::sqrt(v));
}
GdVal gd_pow(const GdVal& x, const GdVal& y) { return GdVal::from_float(std::pow(x.as_float(), y.as_float())); }
GdVal gd_sign(const GdVal& x) {
    if (x.kind == GdVal::Kind::Int) return GdVal::from_int((x.i > 0) - (x.i < 0));
    double f = x.as_float();
    return GdVal::from_float(static_cast<double>((f > 0.0) - (f < 0.0)));
}
GdVal gd_lerp(const GdVal& a, const GdVal& b, const GdVal& t) {
    double af = a.as_float(), bf = b.as_float(), tf = t.as_float();
    return GdVal::from_float(af + (bf - af) * tf);
}
GdVal gd_inverse_lerp(const GdVal& a, const GdVal& b, const GdVal& v) {
    double af = a.as_float(), bf = b.as_float();
    if (af == bf) return GdVal::from_float(0.0);
    return GdVal::from_float((v.as_float() - af) / (bf - af));
}
GdVal gd_smoothstep(const GdVal& a, const GdVal& b, const GdVal& v) {
    double t = gd_clamp(gd_inverse_lerp(a, b, v), GdVal::from_float(0.0), GdVal::from_float(1.0)).as_float();
    return GdVal::from_float(t * t * (3.0 - 2.0 * t));
}
GdVal gd_move_toward(const GdVal& f, const GdVal& t, const GdVal& d) {
    double ff = f.as_float(), tf = t.as_float(), df = d.as_float();
    double diff = tf - ff;
    double c = diff < -df ? -df : (diff > df ? df : diff);
    return GdVal::from_float(ff + c);
}
GdVal gd_wrapf(const GdVal& v, const GdVal& mn, const GdVal& mx) {
    double vf = v.as_float(), mnf = mn.as_float(), mxf = mx.as_float();
    double r = mxf - mnf;
    if (r == 0.0) return GdVal::from_float(mnf);
    return GdVal::from_float(vf - r * std::floor((vf - mnf) / r));
}
GdVal gd_wrapi(const GdVal& v, const GdVal& mn, const GdVal& mx) {
    return GdVal::from_int(static_cast<int64_t>(gd_wrapf(v, mn, mx).as_float()));
}
GdVal gd_deg2rad(const GdVal& d) { return GdVal::from_float(d.as_float() * (3.14159265358979323846 / 180.0)); }
GdVal gd_rad2deg(const GdVal& r) { return GdVal::from_float(r.as_float() * (180.0 / 3.14159265358979323846)); }
bool gd_is_equal_approx(const GdVal& a, const GdVal& b) {
    double af = a.as_float(), bf = b.as_float();
    if (af == bf) return true;
    double tol = 0.00001 * std::max(std::abs(af), std::abs(bf));
    return std::abs(af - bf) <= tol;
}

int64_t gd_typeof(const GdVal& v) {
    switch (v.kind) {
        case GdVal::Kind::Null: return 0;
        case GdVal::Kind::Bool: return 1;
        case GdVal::Kind::Int: return 2;
        case GdVal::Kind::Float: return 3;
        case GdVal::Kind::Str: return 4;
        case GdVal::Kind::Vec2: return 5;
        case GdVal::Kind::Color: return 14;
        case GdVal::Kind::Dict: return 18;
        case GdVal::Kind::Arr: return 19;
        default: return 17;
    }
}

GdVal gd_range(BattleArena& arena, const GdVal* args, int argc) {
    int64_t start = 0, stop = 0, step = 1;
    if (argc == 1) {
        stop = args[0].as_int();
    } else if (argc == 2) {
        start = args[0].as_int();
        stop = args[1].as_int();
    } else if (argc >= 3) {
        start = args[0].as_int();
        stop = args[1].as_int();
        step = args[2].as_int();
    }
    auto* arr = GdArr::create(arena);
    if (step == 0) return GdVal::from_arr(arr);
    if (step > 0) {
        for (int64_t i = start; i < stop; i += step) arr->push_back(arena, GdVal::from_int(i));
    } else {
        for (int64_t i = start; i > stop; i += step) arr->push_back(arena, GdVal::from_int(i));
    }
    return GdVal::from_arr(arr);
}

GdVal gd_str_fn(BattleArena& arena, const GdVal* args, int argc) {
    std::string out;
    for (int i = 0; i < argc; ++i) append_gd_str(out, args[i]);
    return GdVal::from_str(make_str(arena, out));
}

GdVal gd_fmt(BattleArena& arena, const GdVal& fmt, const GdVal& args) {
    std::string_view f = (fmt.kind == GdVal::Kind::Str && fmt.str) ? std::string_view(fmt.str->data, fmt.str->len) : "";
    std::vector<GdVal> list;
    if (args.kind == GdVal::Kind::Arr && args.arr) {
        list.assign(args.arr->data, args.arr->data + args.arr->len);
    } else {
        list.push_back(args);
    }
    std::string out;
    size_t idx = 0;
    for (size_t i = 0; i < f.size(); ++i) {
        if (f[i] == '%' && i + 1 < f.size()) {
            if (f[i + 1] == '%') { out.push_back('%'); ++i; continue; }
            size_t j = i + 1;
            while (j < f.size() && (std::isdigit(static_cast<unsigned char>(f[j])) || f[j] == '.' || f[j] == '-' || f[j] == '+')) ++j;
            char spec = (j < f.size()) ? f[j] : 's';
            GdVal v = (idx < list.size()) ? list[idx++] : GdVal::null();
            if (spec == 'd' || spec == 'i') {
                char buf[64];
                std::snprintf(buf, sizeof(buf), "%lld", static_cast<long long>(v.as_int()));
                out += buf;
            } else if (spec == 'f') {
                std::string ffmt(f.substr(i, j - i + 1));
                char buf[64];
                std::snprintf(buf, sizeof(buf), ffmt.c_str(), v.as_float());
                out += buf;
            } else {
                append_gd_str(out, v);
            }
            i = j;
            continue;
        }
        out.push_back(f[i]);
    }
    return GdVal::from_str(make_str(arena, out));
}

GdVal gd_in(const GdVal& needle, const GdVal& haystack) {
    if (haystack.kind == GdVal::Kind::Arr && haystack.arr) {
        return GdVal::from_bool(haystack.arr->has_val(needle));
    }
    if (haystack.kind == GdVal::Kind::Dict && haystack.dict) {
        return GdVal::from_bool(haystack.dict->has(needle));
    }
    if (haystack.kind == GdVal::Kind::Str && needle.kind == GdVal::Kind::Str && haystack.str && needle.str) {
        std::string_view h(haystack.str->data, haystack.str->len);
        std::string_view n(needle.str->data, needle.str->len);
        return GdVal::from_bool(h.find(n) != std::string_view::npos);
    }
    if (haystack.kind == GdVal::Kind::Enum && haystack.en && needle.kind == GdVal::Kind::Str && needle.str) {
        return GdVal::from_bool(haystack.en->has(std::string_view(needle.str->data, needle.str->len)));
    }
    return GdVal::from_bool(false);
}

GdVal gd_iter_seq(BattleArena& arena, const GdVal& x) {
    if (x.kind == GdVal::Kind::Arr) return x;
    if (x.kind == GdVal::Kind::Dict) return GdVal::from_arr(x.dict ? x.dict->keys(arena) : GdArr::create(arena));
    if (x.kind == GdVal::Kind::Enum) return GdVal::from_arr(x.en ? x.en->keys_arr(arena) : GdArr::create(arena));
    if (x.kind == GdVal::Kind::Float) {
        int64_t n = x.f > 0.0 ? static_cast<int64_t>(std::ceil(x.f)) : 0;
        auto* arr = GdArr::create(arena, n > 0 ? static_cast<uint32_t>(n) : 0);
        for (int64_t i = 0; i < n; ++i) arr->push_back(arena, GdVal::from_int(i));
        return GdVal::from_arr(arr);
    }
    if (x.kind == GdVal::Kind::Int || x.kind == GdVal::Kind::Bool) {
        int64_t n = x.as_int();
        auto* arr = GdArr::create(arena, n > 0 ? static_cast<uint32_t>(n) : 0);
        for (int64_t i = 0; i < n; ++i) arr->push_back(arena, GdVal::from_int(i));
        return GdVal::from_arr(arr);
    }
    if (x.kind == GdVal::Kind::Str && x.str) {
        auto* arr = GdArr::create(arena, x.str->len);
        for (uint32_t i = 0; i < x.str->len; ++i)
            arr->push_back(arena, GdVal::from_str(make_str(arena, &x.str->data[i], 1)));
        return GdVal::from_arr(arr);
    }
    return GdVal::from_arr(GdArr::create(arena));
}

// ─────────────────────────── GdArr ───────────────────────────
GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {
    auto* a = arena.make<GdArr>();
    if (reserve_cap > 0) {
        a->data = arena.alloc_array<GdVal>(reserve_cap);
        a->cap = reserve_cap;
    }
    return a;
}

GdArr* GdArr::from_init(BattleArena& arena, std::initializer_list<GdVal> vals) {
    auto* a = create(arena, static_cast<uint32_t>(vals.size()));
    for (const auto& v : vals) a->data[a->len++] = v;
    return a;
}

void GdArr::push_back(BattleArena& arena, const GdVal& v) {
    GdVal elem = is_pool_real ? GdVal::from_float(f32_d(v.as_float())) : v;
    if (len == cap) {
        uint32_t ncap = cap == 0 ? 8 : cap * 2;
        GdVal* nd = arena.alloc_array<GdVal>(ncap);
        if (len > 0) std::memcpy(nd, data, sizeof(GdVal) * len);
        data = nd;
        cap = ncap;
    }
    data[len++] = elem;
}

void GdArr::insert_at(BattleArena& arena, int64_t pos, const GdVal& v) {
    if (pos < 0) pos = static_cast<int64_t>(len) + pos;
    if (pos < 0) pos = 0;
    if (pos > static_cast<int64_t>(len)) pos = static_cast<int64_t>(len);
    if (len == cap) {
        uint32_t ncap = cap == 0 ? 8 : cap * 2;
        GdVal* nd = arena.alloc_array<GdVal>(ncap);
        if (len > 0) std::memcpy(nd, data, sizeof(GdVal) * len);
        data = nd;
        cap = ncap;
    }
    if (pos < static_cast<int64_t>(len)) {
        std::memmove(data + pos + 1, data + pos, sizeof(GdVal) * (len - static_cast<uint32_t>(pos)));
    }
    data[pos] = v;
    ++len;
}

GdVal GdArr::pop_at(int64_t idx) {
    if (idx < 0) idx = static_cast<int64_t>(len) + idx;
    if (idx < 0 || idx >= static_cast<int64_t>(len)) return GdVal::null();
    GdVal out = data[idx];
    if (idx + 1 < static_cast<int64_t>(len)) {
        std::memmove(data + idx, data + idx + 1, sizeof(GdVal) * (len - static_cast<uint32_t>(idx) - 1));
    }
    --len;
    return out;
}

void GdArr::append_array(BattleArena& arena, const GdArr* o) {
    if (!o || o->len == 0) return;
    if (len + o->len > cap) {
        uint32_t ncap = std::max(cap == 0 ? 8u : cap * 2, len + o->len);
        GdVal* nd = arena.alloc_array<GdVal>(ncap);
        if (len > 0) std::memcpy(nd, data, sizeof(GdVal) * len);
        data = nd;
        cap = ncap;
    }
    std::memcpy(data + len, o->data, sizeof(GdVal) * o->len);
    len += o->len;
}

GdVal GdArr::pop_front() {
    if (len == 0) return GdVal::null();
    GdVal out = data[0];
    if (len > 1) std::memmove(data, data + 1, sizeof(GdVal) * (len - 1));
    --len;
    return out;
}

GdVal GdArr::pop_back() {
    if (len == 0) return GdVal::null();
    return data[--len];
}

void GdArr::remove_at(int64_t idx) {
    if (idx < 0 || static_cast<uint64_t>(idx) >= len) return;
    uint32_t i = static_cast<uint32_t>(idx);
    if (i + 1 < len) std::memmove(data + i, data + i + 1, sizeof(GdVal) * (len - i - 1));
    --len;
}

void GdArr::erase_val(const GdVal& v) {
    int64_t i = find_val(v, 0);
    if (i >= 0) remove_at(i);
}

int64_t GdArr::find_val(const GdVal& v, int64_t from) const {
    if (from < 0) from = std::max<int64_t>(0, static_cast<int64_t>(len) + from);
    for (uint32_t i = static_cast<uint32_t>(from); i < len; ++i) {
        if (gd_eq(data[i], v)) return static_cast<int64_t>(i);
    }
    return -1;
}

void GdArr::resize(BattleArena& arena, int64_t n) {
    if (n <= 0) { len = 0; return; }
    uint32_t un = static_cast<uint32_t>(n);
    if (un > cap) {
        uint32_t ncap = std::max(un, cap * 2);
        GdVal* nd = arena.alloc_array<GdVal>(ncap);
        if (len > 0) std::memcpy(nd, data, sizeof(GdVal) * len);
        data = nd;
        cap = ncap;
    }
    for (uint32_t i = len; i < un; ++i) data[i] = GdVal::null();
    len = un;
}

void GdArr::fill(const GdVal& v) {
    for (uint32_t i = 0; i < len; ++i) data[i] = v;
}

void GdArr::invert() {
    for (uint32_t i = 0; i < len / 2; ++i) std::swap(data[i], data[len - 1 - i]);
}

int64_t GdArr::count_val(const GdVal& v) const {
    int64_t c = 0;
    for (uint32_t i = 0; i < len; ++i) if (gd_eq(data[i], v)) ++c;
    return c;
}

GdArr* GdArr::duplicate(BattleArena& arena, bool deep) const {
    auto* out = create(arena, len);
    for (uint32_t i = 0; i < len; ++i) {
        GdVal v = data[i];
        if (deep) {
            if (v.kind == GdVal::Kind::Arr && v.arr) v = GdVal::from_arr(v.arr->duplicate(arena, true));
            else if (v.kind == GdVal::Kind::Dict && v.dict) v = GdVal::from_dict(v.dict->duplicate(arena, true));
        }
        out->data[i] = v;
    }
    out->len = len;
    return out;
}

GdVal GdArr::get_idx(int64_t idx) const {
    if (idx < 0) idx += static_cast<int64_t>(len);
    if (idx < 0 || static_cast<uint64_t>(idx) >= len) return GdVal::null();
    return data[idx];
}

void GdArr::set_idx(int64_t idx, const GdVal& v) {
    if (idx < 0) idx += static_cast<int64_t>(len);
    if (idx < 0 || static_cast<uint64_t>(idx) >= len) return;
    data[idx] = v;
}

// ─────────────────────────── GdDict ───────────────────────────
GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {
    auto* d = arena.make<GdDict>();
    if (reserve_cap > 0) {
        d->entries = arena.alloc_array<GdDictEntry>(reserve_cap);
        d->cap = reserve_cap;
    }
    return d;
}

void GdDict::rebuild_index(BattleArena& arena) {
    if (cap <= 8) { buckets = nullptr; bucket_cap = 0; return; }
    uint32_t bcap = 32;
    while (bcap < cap * 2) bcap *= 2;
    buckets = arena.alloc_array<int32_t>(bcap);
    bucket_cap = bcap;
    std::memset(buckets, -1, sizeof(int32_t) * bcap);
    uint32_t mask = bcap - 1;
    for (uint32_t i = 0; i < len; ++i) {
        uint32_t pos = static_cast<uint32_t>(entries[i].hash) & mask;
        while (buckets[pos] >= 0) pos = (pos + 1) & mask;
        buckets[pos] = static_cast<int32_t>(i);
    }
}

int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {
    if (!buckets || bucket_cap == 0) {
        for (uint32_t i = 0; i < len; ++i) {
            if (entries[i].hash == h && gd_eq(entries[i].key, key)) return static_cast<int32_t>(i);
        }
        return -1;
    }
    uint32_t mask = bucket_cap - 1;
    uint32_t pos = static_cast<uint32_t>(h) & mask;
    while (true) {
        int32_t ei = buckets[pos];
        if (ei < 0) return -1;
        if (entries[ei].hash == h && gd_eq(entries[ei].key, key)) return ei;
        pos = (pos + 1) & mask;
    }
}

GdVal GdDict::get(const GdVal& key, const GdVal& def) const {
    int32_t idx = find_index(key);
    return idx >= 0 ? entries[idx].val : def;
}

void GdDict::set(BattleArena& arena, const GdVal& key, const GdVal& val) {
    uint64_t h = gd_val_hash(key);
    int32_t idx = find_index(key, h);
    if (idx >= 0) {
        entries[idx].val = val;
        return;
    }
    if (len == cap) {
        uint32_t ncap = cap == 0 ? 8 : cap * 2;
        auto* ne = arena.alloc_array<GdDictEntry>(ncap);
        if (len > 0) std::memcpy(ne, entries, sizeof(GdDictEntry) * len);
        entries = ne;
        cap = ncap;
        entries[len++] = {key, val, h};
        rebuild_index(arena);
        return;
    }
    uint32_t ei = len++;
    entries[ei] = {key, val, h};
    if (buckets && bucket_cap > 0) {
        uint32_t mask = bucket_cap - 1;
        uint32_t pos = static_cast<uint32_t>(h) & mask;
        while (buckets[pos] >= 0) pos = (pos + 1) & mask;
        buckets[pos] = static_cast<int32_t>(ei);
    }
}

void GdDict::erase(const GdVal& key) {
    uint64_t h = gd_val_hash(key);
    int32_t idx = find_index(key, h);
    if (idx < 0) return;
    uint32_t ui = static_cast<uint32_t>(idx);
    if (ui + 1 < len) std::memmove(entries + ui, entries + ui + 1, sizeof(GdDictEntry) * (len - ui - 1));
    --len;
    if (buckets && bucket_cap > 0) {
        std::memset(buckets, -1, sizeof(int32_t) * bucket_cap);
        uint32_t mask = bucket_cap - 1;
        for (uint32_t i = 0; i < len; ++i) {
            uint32_t pos = static_cast<uint32_t>(entries[i].hash) & mask;
            while (buckets[pos] >= 0) pos = (pos + 1) & mask;
            buckets[pos] = static_cast<int32_t>(i);
        }
    }
}

void GdDict::clear() {
    len = 0;
    if (buckets && bucket_cap > 0) std::memset(buckets, -1, sizeof(int32_t) * bucket_cap);
}

GdArr* GdDict::keys(BattleArena& arena) const {
    auto* a = GdArr::create(arena, len);
    for (uint32_t i = 0; i < len; ++i) a->data[a->len++] = entries[i].key;
    return a;
}

GdArr* GdDict::values(BattleArena& arena) const {
    auto* a = GdArr::create(arena, len);
    for (uint32_t i = 0; i < len; ++i) a->data[a->len++] = entries[i].val;
    return a;
}

GdDict* GdDict::duplicate(BattleArena& arena, bool deep) const {
    auto* d = GdDict::create(arena, len);
    for (uint32_t i = 0; i < len; ++i) {
        GdVal k = entries[i].key, v = entries[i].val;
        if (deep) {
            if (v.kind == GdVal::Kind::Arr && v.arr) v = GdVal::from_arr(v.arr->duplicate(arena, true));
            else if (v.kind == GdVal::Kind::Dict && v.dict) v = GdVal::from_dict(v.dict->duplicate(arena, true));
        }
        d->set(arena, k, v);
    }
    return d;
}

void GdDict::invert(BattleArena& arena) {
    uint32_t n = len;
    if (n == 0) return;
    auto* tmp = arena.alloc_array<GdDictEntry>(n);
    std::memcpy(tmp, entries, sizeof(GdDictEntry) * n);
    clear();
    for (uint32_t i = 0; i < n; ++i) set(arena, tmp[i].val, tmp[i].key);
}

// ─────────────────────────── GdEnum ───────────────────────────
bool GdEnum::get(std::string_view k, int64_t& out) const {
    for (uint32_t i = 0; i < len; ++i) {
        if (k == items[i].key) { out = items[i].val; return true; }
    }
    return false;
}

GdArr* GdEnum::keys_arr(BattleArena& arena) const {
    auto* a = GdArr::create(arena, len);
    for (uint32_t i = 0; i < len; ++i) a->push_back(arena, GdVal::from_cstr(arena, items[i].key));
    return a;
}

GdArr* GdEnum::values_arr(BattleArena& arena) const {
    auto* a = GdArr::create(arena, len);
    for (uint32_t i = 0; i < len; ++i) a->push_back(arena, GdVal::from_int(items[i].val));
    return a;
}

// ─────────────────────────── GdObj / GdFuncRef ───────────────────────────
uint64_t GdObj::get_instance_id() {
    if (!rt_ctx_) return reinterpret_cast<uintptr_t>(this);
    if (gid_epoch_ != rt_ctx_->gid_epoch) {
        gid_epoch_ = rt_ctx_->gid_epoch;
        gid_ = rt_ctx_->next_gid++;
    }
    return gid_;
}

void GdObj::connect_signal(BattleArena& arena, SymId sig, GdObj* target, SymId method, GdArr* binds) {
    auto* c = arena.make<GdConn>();
    c->signal = sig;
    c->target = target;
    c->method = method;
    c->binds = binds;
    c->next = nullptr;
    if (!conns_head_) {
        conns_head_ = c;
    } else {
        GdConn* tail = conns_head_;
        while (tail->next) tail = tail->next;
        tail->next = c;
    }
}

void GdObj::disconnect_signal(SymId sig, GdObj* target, SymId method) {
    GdConn** p = &conns_head_;
    while (*p) {
        if ((*p)->signal == sig && (*p)->target == target && (*p)->method == method) {
            *p = (*p)->next;
        } else {
            p = &((*p)->next);
        }
    }
}

bool GdObj::is_connected_signal(SymId sig, GdObj* target, SymId method) const {
    for (const GdConn* c = conns_head_; c; c = c->next) {
        if (c->signal == sig && c->target == target && c->method == method) return true;
    }
    return false;
}

void GdObj::emit_signal(BattleCtx& ctx, SymId sig, const GdVal* args, int argc) {
    if (!conns_head_) return;
    std::vector<GdConn> snap;
    for (const GdConn* c = conns_head_; c; c = c->next) {
        if (c->signal == sig) snap.push_back(*c);
    }
    for (const auto& c : snap) {
        if (!c.target) continue;
        GdVal dummy;
        if (c.binds && c.binds->len > 0) {
            std::vector<GdVal> all(args, args + argc);
            for (uint32_t i = 0; i < c.binds->len; ++i) all.push_back(c.binds->data[i]);
            c.target->call_method(ctx, c.method, all.data(), static_cast<int>(all.size()), dummy);
        } else {
            c.target->call_method(ctx, c.method, args, argc, dummy);
        }
    }
}

bool GdFuncRef::is_valid() const {
    return instance != nullptr && method != SYM_NONE && instance->has_own_method(method);
}

GdVal GdFuncRef::call_func(BattleCtx& ctx, const GdVal* args, int argc) const {
    if (!instance || method == SYM_NONE) return GdVal::null();
    GdVal out = GdVal::null();
    if (binds && binds->len > 0) {
        std::vector<GdVal> all(args, args + argc);
        for (uint32_t i = 0; i < binds->len; ++i) all.push_back(binds->data[i]);
        instance->call_method(ctx, method, all.data(), static_cast<int>(all.size()), out);
    } else {
        instance->call_method(ctx, method, args, argc, out);
    }
    return out;
}

GdVal GdFuncRef::call_funcv(BattleCtx& ctx, const GdVal& args_arr) const {
    if (args_arr.kind == GdVal::Kind::Arr && args_arr.arr) {
        return call_func(ctx, args_arr.arr->data, static_cast<int>(args_arr.arr->len));
    }
    return call_func(ctx, nullptr, 0);
}

// ─────────────────────────── Class Registry ───────────────────────────
static std::unordered_map<std::string_view, const GdClassMeta*>& class_reg() {
    static auto* m = new std::unordered_map<std::string_view, const GdClassMeta*>();
    return *m;
}

static std::vector<const GdClassMeta*>& class_id_reg() {
    static auto* v = new std::vector<const GdClassMeta*>({nullptr});
    return *v;
}

static void reg_one_key(std::string_view key, const GdClassMeta* meta) {
    if (key.empty()) return;
    auto& m = class_reg();
    auto it = m.find(key);
    if (it != m.end() && it->second->is_behavior_tree && !meta->is_behavior_tree) return;
    m[key] = meta;
}

void register_class(const GdClassMeta* meta) {
    if (!meta) return;
    auto& idv = class_id_reg();
    if (meta->id >= idv.size()) idv.resize(meta->id + 1, nullptr);
    idv[meta->id] = meta;
    if (meta->res_path && meta->res_path[0]) {
        // res_path is always unique per file
        class_reg()[meta->res_path] = meta;
        // stem fallback
        std::string_view rp(meta->res_path);
        auto slash = rp.rfind('/');
        std::string_view stem = (slash == std::string_view::npos) ? rp : rp.substr(slash + 1);
        if (stem.ends_with(".gd")) stem.remove_suffix(3);
        reg_one_key(stem, meta);
    }
    if (meta->class_name && meta->class_name[0]) reg_one_key(meta->class_name, meta);
}

const GdClassMeta* find_class(std::string_view name_or_path) {
    auto& m = class_reg();
    auto it = m.find(name_or_path);
    return it != m.end() ? it->second : nullptr;
}

const GdClassMeta* find_class_by_id(ClsId id) {
    const auto& v = class_id_reg();
    return id < v.size() ? v[id] : nullptr;
}

GdVal construct_class(BattleCtx& ctx, const GdClassMeta* cls, const GdVal* args, int argc) {
    if (!cls || !cls->alloc_fn) return GdVal::null();
    GdObj* obj = cls->alloc_fn(ctx);
    obj->init_fields(ctx);
    GdVal dummy;
    obj->call_method(ctx, SYM__init, args, argc, dummy);
    return GdVal::from_obj(obj);
}

GdVal load_resource(std::string_view path) {
    return GdVal::from_cls(find_class(path));
}

bool gd_is_type(const GdVal& v, const GdClassMeta* cls) {
    if (!cls || v.kind != GdVal::Kind::Obj || !v.obj) return false;
    return v.obj->meta()->is_subclass_of(cls);
}

bool gd_is_builtin(const GdVal& v, int type_tag) {
    switch (type_tag) {
        case 1: return v.kind == GdVal::Kind::Bool;
        case 2: return v.kind == GdVal::Kind::Int;
        case 3: return v.kind == GdVal::Kind::Float || v.kind == GdVal::Kind::Int;
        case 4: return v.kind == GdVal::Kind::Str;
        case 5: return v.kind == GdVal::Kind::Vec2;
        case 14: return v.kind == GdVal::Kind::Color;
        case 18: return v.kind == GdVal::Kind::Dict;
        case 19: return v.kind == GdVal::Kind::Arr;
        case 17: return v.kind == GdVal::Kind::Obj || v.kind == GdVal::Kind::FuncRef || v.kind == GdVal::Kind::Rng;
        default: return false;
    }
}

// ─────────────────────────── Sort & Shuffle ───────────────────────────
void shuffle_array(BattleCtx& ctx, GdArr* arr) {
    if (!arr || arr->len < 2) return;
    for (int64_t i = static_cast<int64_t>(arr->len) - 1; i > 0; --i) {
        uint32_t j = ctx.math_rng.randi() % static_cast<uint32_t>(i + 1);
        std::swap(arr->data[i], arr->data[j]);
    }
}

GdVal pick_random_array(BattleCtx& ctx, const GdArr* arr) {
    if (!arr || arr->len == 0) return GdVal::null();
    uint32_t j = ctx.math_rng.randi() % arr->len;
    return arr->data[j];
}

void godot_sort_custom_items(BattleCtx& ctx, GdArr* arr) {
    if (!arr || arr->len < 2) return;
    const uint32_t n = arr->len;
    struct Pair { int64_t key; GdVal val; };
    std::vector<Pair> pairs(n);
    for (uint32_t i = 0; i < n; ++i) {
        GdVal res = call_method(ctx, arr->data[i], SYM_getTriggerPriority, nullptr, 0);
        pairs[i] = {-res.as_int(), arr->data[i]};
    }
    if (n <= 16) {
        std::stable_sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) { return a.key < b.key; });
        for (uint32_t i = 0; i < n; ++i) arr->data[i] = pairs[i].val;
        return;
    }

    auto adjust_heap = [&](int first, int hole, int length, Pair value) {
        int start = hole;
        int right = 2 * hole + 2;
        while (right < length) {
            int child = right - (pairs[first + right].key < pairs[first + right - 1].key ? 1 : 0);
            pairs[first + hole] = pairs[first + child];
            hole = child;
            right = 2 * hole + 2;
        }
        if (right == length) {
            pairs[first + hole] = pairs[first + right - 1];
            hole = right - 1;
        }
        while (hole > start) {
            int parent = (hole - 1) / 2;
            if (pairs[first + parent].key >= value.key) break;
            pairs[first + hole] = pairs[first + parent];
            hole = parent;
        }
        pairs[first + hole] = value;
    };

    auto heap_sort = [&](int first, int last) {
        int length = last - first;
        for (int hole = (length - 2) / 2; hole >= 0; --hole) {
            adjust_heap(first, hole, length, pairs[first + hole]);
        }
        for (int end = last - 1; end > first; --end) {
            Pair value = pairs[end];
            pairs[end] = pairs[first];
            adjust_heap(first, 0, end - first, value);
        }
    };

    auto partition_fn = [&](auto& self_fn, int first, int last, int depth) -> void {
        while (last - first > 16) {
            if (depth == 0) {
                heap_sort(first, last);
                return;
            }
            depth--;
            int64_t a = pairs[first].key;
            int64_t b = pairs[(first + last) / 2].key;
            int64_t c = pairs[last - 1].key;
            int64_t pivot = a < b ? (b < c ? b : (a < c ? c : a)) : (a < c ? a : (b < c ? c : b));
            int lo = first, hi = last;
            while (true) {
                while (pairs[lo].key < pivot) ++lo;
                --hi;
                while (pivot < pairs[hi].key) --hi;
                if (lo >= hi) break;
                std::swap(pairs[lo], pairs[hi]);
                ++lo;
            }
            self_fn(self_fn, lo, last, depth);
            last = lo;
        }
    };

    int bit_len = 32 - __builtin_clz(n);
    partition_fn(partition_fn, 0, static_cast<int>(n), (bit_len - 1) * 2);
    std::stable_sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) { return a.key < b.key; });
    for (uint32_t i = 0; i < n; ++i) arr->data[i] = pairs[i].val;
}

void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method) {
    if (!arr || arr->len < 2 || !obj) return;
    std::stable_sort(arr->data, arr->data + arr->len, [&](const GdVal& a, const GdVal& b) {
        GdVal args[2] = {a, b};
        GdVal out = GdVal::null();
        obj->call_method(ctx, method, args, 2, out);
        return gd_truth(out);
    });
}

// ─────────────────────────── Property, Index & Method Dispatch ───────────────────────────
GdVal get_prop(BattleCtx& ctx, const GdVal& recv, SymId prop) {
    switch (recv.kind) {
        case GdVal::Kind::Obj: {
            if (!recv.obj) return GdVal::null();
            if (prop == SYM_resource_path) return GdVal::from_cstr(ctx.arena, recv.obj->meta()->res_path);
            GdVal out;
            if (recv.obj->get_prop(prop, out)) return out;
            return GdVal::null();
        }
        case GdVal::Kind::Vec2:
            if (prop == SYM_x) return GdVal::from_float(recv.v2.x);
            if (prop == SYM_y) return GdVal::from_float(recv.v2.y);
            return GdVal::null();
        case GdVal::Kind::Color:
            if (!recv.col) return GdVal::null();
            if (prop == SYM_r) return GdVal::from_float(recv.col->r);
            if (prop == SYM_g) return GdVal::from_float(recv.col->g);
            if (prop == SYM_b) return GdVal::from_float(recv.col->b);
            if (prop == SYM_a) return GdVal::from_float(recv.col->a);
            return GdVal::null();
        case GdVal::Kind::Enum:
            if (recv.en) {
                int64_t val = 0;
                if (recv.en->get(sym_name(prop), val)) return GdVal::from_int(val);
            }
            return GdVal::null();
        case GdVal::Kind::ClassRef: {
            if (recv.cls) {
                if (prop == SYM_resource_path) return GdVal::from_cstr(ctx.arena, recv.cls->res_path);
                if (recv.cls->get_static_prop) {
                    GdVal out;
                    if (recv.cls->get_static_prop(prop, out)) return out;
                }
            }
            return GdVal::null();
        }
        case GdVal::Kind::Rng:
            if (!recv.rng) return GdVal::null();
            if (prop == SYM_seed) return GdVal::from_int(static_cast<int64_t>(recv.rng->get_seed()));
            if (prop == SYM_state) return GdVal::from_int(static_cast<int64_t>(recv.rng->get_state()));
            return GdVal::null();
        case GdVal::Kind::Dict:
            if (recv.dict) return recv.dict->get(GdVal::from_cstr(ctx.arena, sym_name(prop)));
            return GdVal::null();
        default:
            return GdVal::null();
    }
}

void set_prop(BattleCtx& ctx, GdVal& recv, SymId prop, const GdVal& val) {
    switch (recv.kind) {
        case GdVal::Kind::Obj:
            if (recv.obj) recv.obj->set_prop(ctx, prop, val);
            break;
        case GdVal::Kind::Vec2:
            if (prop == SYM_x) recv.v2.x = val.as_float();
            else if (prop == SYM_y) recv.v2.y = val.as_float();
            break;
        case GdVal::Kind::Color:
            if (recv.col) {
                if (prop == SYM_r) recv.col->r = val.as_float();
                else if (prop == SYM_g) recv.col->g = val.as_float();
                else if (prop == SYM_b) recv.col->b = val.as_float();
                else if (prop == SYM_a) recv.col->a = val.as_float();
            }
            break;
        case GdVal::Kind::Rng:
            if (recv.rng) {
                if (prop == SYM_seed) recv.rng->set_seed(static_cast<uint64_t>(val.as_int()));
                else if (prop == SYM_state) recv.rng->set_state(static_cast<uint64_t>(val.as_int()));
            }
            break;
        case GdVal::Kind::Dict:
            if (recv.dict) recv.dict->set(ctx.arena, GdVal::from_cstr(ctx.arena, sym_name(prop)), val);
            break;
        default:
            break;
    }
}

GdVal get_index(BattleCtx& ctx, const GdVal& recv, const GdVal& key) {
    if (recv.kind == GdVal::Kind::Arr && recv.arr) return recv.arr->get_idx(key.as_int());
    if (recv.kind == GdVal::Kind::Dict && recv.dict) return recv.dict->get(key);
    if (recv.kind == GdVal::Kind::Enum && recv.en && key.kind == GdVal::Kind::Str && key.str) {
        int64_t val = 0;
        if (recv.en->get(std::string_view(key.str->data, key.str->len), val)) return GdVal::from_int(val);
        return GdVal::null();
    }
    if (recv.kind == GdVal::Kind::Str && recv.str) {
        int64_t idx = key.as_int();
        if (idx < 0) idx += static_cast<int64_t>(recv.str->len);
        if (idx >= 0 && static_cast<uint32_t>(idx) < recv.str->len) {
            return GdVal::from_str(make_str(ctx.arena, &recv.str->data[idx], 1));
        }
        return GdVal::from_cstr(ctx.arena, "");
    }
    if (recv.kind == GdVal::Kind::Obj && recv.obj && key.kind == GdVal::Kind::Str && key.str) {
        return get_prop(ctx, recv, intern_sym(std::string_view(key.str->data, key.str->len)));
    }
    return GdVal::null();
}

void set_index(BattleCtx& ctx, GdVal& recv, const GdVal& key, const GdVal& val) {
    if (recv.kind == GdVal::Kind::Arr && recv.arr) {
        recv.arr->set_idx(key.as_int(), val);
    } else if (recv.kind == GdVal::Kind::Dict && recv.dict) {
        recv.dict->set(ctx.arena, key, val);
    } else if (recv.kind == GdVal::Kind::Obj && recv.obj && key.kind == GdVal::Kind::Str && key.str) {
        SymId s = intern_sym(std::string_view(key.str->data, key.str->len));
        recv.obj->set_prop(ctx, s, val);
    }
}

static SymId val_to_sym(const GdVal& name) {
    if (name.kind == GdVal::Kind::Str && name.str) {
        return intern_sym(std::string_view(name.str->data, name.str->len));
    }
    return SYM_NONE;
}

GdVal call_method_dyn(BattleCtx& ctx, const GdVal& recv, const GdVal& method_name, const GdVal* args, int argc) {
    return call_method(ctx, recv, val_to_sym(method_name), args, argc);
}

GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId m, const GdVal* args, int argc) {
    switch (recv.kind) {
        case GdVal::Kind::Obj: {
            if (!recv.obj) return GdVal::null();
            // Dispatch user/generated methods first so subclass overrides win if any
            GdVal out = GdVal::null();
            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;
            // Godot Object builtins
            switch (m) {
                case SYM_has_method:
                    return GdVal::from_bool(argc >= 1 && recv.obj->has_own_method(val_to_sym(args[0])));
                case SYM_call:
                    return argc >= 1 ? call_method(ctx, recv, val_to_sym(args[0]), args + 1, argc - 1) : GdVal::null();
                case SYM_callv:
                    if (argc >= 2 && args[1].kind == GdVal::Kind::Arr && args[1].arr) {
                        return call_method(ctx, recv, val_to_sym(args[0]), args[1].arr->data, static_cast<int>(args[1].arr->len));
                    }
                    return argc >= 1 ? call_method(ctx, recv, val_to_sym(args[0]), nullptr, 0) : GdVal::null();
                case SYM_emit_signal:
                    if (argc >= 1) recv.obj->emit_signal(ctx, val_to_sym(args[0]), args + 1, argc - 1);
                    return GdVal::null();
                case SYM_connect:
                    if (argc >= 3 && args[1].kind == GdVal::Kind::Obj) {
                        GdArr* binds = (argc >= 4 && args[3].kind == GdVal::Kind::Arr) ? args[3].arr : nullptr;
                        recv.obj->connect_signal(ctx.arena, val_to_sym(args[0]), args[1].obj, val_to_sym(args[2]), binds);
                    }
                    return GdVal::null();
                case SYM_disconnect:
                    if (argc >= 3 && args[1].kind == GdVal::Kind::Obj) {
                        recv.obj->disconnect_signal(val_to_sym(args[0]), args[1].obj, val_to_sym(args[2]));
                    }
                    return GdVal::null();
                case SYM_is_connected:
                    if (argc >= 3 && args[1].kind == GdVal::Kind::Obj) {
                        return GdVal::from_bool(recv.obj->is_connected_signal(val_to_sym(args[0]), args[1].obj, val_to_sym(args[2])));
                    }
                    return GdVal::from_bool(false);
                case SYM_get_instance_id:
                    return GdVal::from_int(static_cast<int64_t>(recv.obj->get_instance_id()));
                case SYM_get_script:
                    return GdVal::from_cls(recv.obj->meta());
                case SYM_get_class:
                    return GdVal::from_cstr(ctx.arena, recv.obj->meta()->class_name);
                default:
                    return GdVal::null();
            }
        }
        case GdVal::Kind::ClassRef:
            if (recv.cls) {
                if (m == SYM_new) return construct_class(ctx, recv.cls, args, argc);
                if (recv.cls->call_static_fn) {
                    GdVal out = GdVal::null();
                    if (recv.cls->call_static_fn(ctx, m, args, argc, out)) return out;
                }
            }
            return GdVal::null();
        case GdVal::Kind::Arr: {
            GdArr* a = recv.arr;
            if (!a) return GdVal::null();
            switch (m) {
                case SYM_size: return GdVal::from_int(a->len);
                case SYM_empty: return GdVal::from_bool(a->len == 0);
                case SYM_has: return GdVal::from_bool(argc >= 1 && a->has_val(args[0]));
                case SYM_push_back:
                case SYM_append:
                    if (argc >= 1) a->push_back(ctx.arena, args[0]);
                    return GdVal::null();
                case SYM_insert:
                    if (argc >= 2) a->insert_at(ctx.arena, args[0].as_int(), args[1]);
                    return GdVal::from_int(0);
                case SYM_pop_at:
                    return argc >= 1 ? a->pop_at(args[0].as_int()) : GdVal::null();
                case SYM_append_array:
                    if (argc >= 1 && args[0].kind == GdVal::Kind::Arr) a->append_array(ctx.arena, args[0].arr);
                    return GdVal::null();
                case SYM_pop_front: return a->pop_front();
                case SYM_pop_back: return a->pop_back();
                case SYM_clear: a->len = 0; return GdVal::null();
                case SYM_duplicate: {
                    bool deep = argc >= 1 && gd_truth(args[0]);
                    return GdVal::from_arr(a->duplicate(ctx.arena, deep));
                }
                case SYM_erase:
                    if (argc >= 1) a->erase_val(args[0]);
                    return GdVal::null();
                case SYM_remove:
                    if (argc >= 1) a->remove_at(args[0].as_int());
                    return GdVal::null();
                case SYM_find:
                    return GdVal::from_int(argc >= 1 ? a->find_val(args[0], argc >= 2 ? args[1].as_int() : 0) : -1);
                case SYM_front: return a->len > 0 ? a->data[0] : GdVal::null();
                case SYM_back: return a->len > 0 ? a->data[a->len - 1] : GdVal::null();
                case SYM_resize:
                    if (argc >= 1) a->resize(ctx.arena, args[0].as_int());
                    return GdVal::null();
                case SYM_fill:
                    if (argc >= 1) a->fill(args[0]);
                    return GdVal::null();
                case SYM_invert: a->invert(); return GdVal::null();
                case SYM_count:
                    return GdVal::from_int(argc >= 1 ? a->count_val(args[0]) : 0);
                case SYM_shuffle:
                    shuffle_array(ctx, a);
                    return GdVal::null();
                case SYM_pick_random:
                    return pick_random_array(ctx, a);
                case SYM_sort_custom:
                    if (argc >= 2 && args[0].kind == GdVal::Kind::Obj) {
                        sort_custom_stable(ctx, a, args[0].obj, val_to_sym(args[1]));
                    }
                    return GdVal::null();
                case SYM_join: {
                    std::string_view sep = (argc >= 1 && args[0].kind == GdVal::Kind::Str && args[0].str)
                                               ? std::string_view(args[0].str->data, args[0].str->len)
                                               : std::string_view("");
                    std::string out;
                    for (uint32_t i = 0; i < a->len; ++i) {
                        if (i > 0) out.append(sep);
                        append_gd_str(out, a->data[i]);
                    }
                    return GdVal::from_str(make_str(ctx.arena, out));
                }
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::Dict: {
            GdDict* d = recv.dict;
            if (!d) return GdVal::null();
            switch (m) {
                case SYM_size: return GdVal::from_int(d->len);
                case SYM_empty: return GdVal::from_bool(d->len == 0);
                case SYM_has: return GdVal::from_bool(argc >= 1 && d->has(args[0]));
                case SYM_has_all: {
                    if (argc < 1 || args[0].kind != GdVal::Kind::Arr || !args[0].arr) return GdVal::from_bool(false);
                    for (uint32_t i = 0; i < args[0].arr->len; ++i)
                        if (!d->has(args[0].arr->data[i])) return GdVal::from_bool(false);
                    return GdVal::from_bool(true);
                }
                case SYM_get:
                    return argc >= 1 ? d->get(args[0], argc >= 2 ? args[1] : GdVal::null()) : GdVal::null();
                case SYM_erase:
                    if (argc >= 1) d->erase(args[0]);
                    return GdVal::from_bool(true);
                case SYM_clear: d->clear(); return GdVal::null();
                case SYM_keys: return GdVal::from_arr(d->keys(ctx.arena));
                case SYM_values: return GdVal::from_arr(d->values(ctx.arena));
                case SYM_duplicate:
                    return GdVal::from_dict(d->duplicate(ctx.arena, argc >= 1 && gd_truth(args[0])));
                case SYM_invert:
                    d->invert(ctx.arena);
                    return GdVal::null();
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::Enum: {
            if (!recv.en) return GdVal::null();
            switch (m) {
                case SYM_size: return GdVal::from_int(recv.en->len);
                case SYM_empty: return GdVal::from_bool(recv.en->len == 0);
                case SYM_has:
                    return GdVal::from_bool(argc >= 1 && args[0].kind == GdVal::Kind::Str && args[0].str &&
                                            recv.en->has(std::string_view(args[0].str->data, args[0].str->len)));
                case SYM_keys: return GdVal::from_arr(recv.en->keys_arr(ctx.arena));
                case SYM_values: return GdVal::from_arr(recv.en->values_arr(ctx.arena));
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::Str: {
            std::string_view s = recv.str ? std::string_view(recv.str->data, recv.str->len) : std::string_view("");
            switch (m) {
                case SYM_length: return GdVal::from_int(static_cast<int64_t>(s.size()));
                case SYM_empty: return GdVal::from_bool(s.empty());
                case SYM_begins_with: {
                    if (argc < 1 || args[0].kind != GdVal::Kind::Str || !args[0].str) return GdVal::from_bool(false);
                    return GdVal::from_bool(s.starts_with(std::string_view(args[0].str->data, args[0].str->len)));
                }
                case SYM_ends_with: {
                    if (argc < 1 || args[0].kind != GdVal::Kind::Str || !args[0].str) return GdVal::from_bool(false);
                    return GdVal::from_bool(s.ends_with(std::string_view(args[0].str->data, args[0].str->len)));
                }
                case SYM_find: {
                    if (argc < 1 || args[0].kind != GdVal::Kind::Str || !args[0].str) return GdVal::from_int(-1);
                    size_t from = argc >= 2 ? static_cast<size_t>(std::max<int64_t>(0, args[1].as_int())) : 0;
                    size_t p = s.find(std::string_view(args[0].str->data, args[0].str->len), from);
                    return GdVal::from_int(p == std::string_view::npos ? -1 : static_cast<int64_t>(p));
                }
                case SYM_to_lower: {
                    std::string out(s);
                    for (char& ch : out) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    return GdVal::from_str(make_str(ctx.arena, out));
                }
                case SYM_to_upper: {
                    std::string out(s);
                    for (char& ch : out) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
                    return GdVal::from_str(make_str(ctx.arena, out));
                }
                case SYM_substr: {
                    int64_t start = argc >= 1 ? args[0].as_int() : 0;
                    if (start < 0) start = std::max<int64_t>(0, static_cast<int64_t>(s.size()) + start);
                    if (static_cast<size_t>(start) >= s.size()) return GdVal::from_cstr(ctx.arena, "");
                    if (argc < 2) return GdVal::from_str(make_str(ctx.arena, s.substr(static_cast<size_t>(start))));
                    int64_t ln = args[1].as_int();
                    if (ln < 0) return GdVal::from_cstr(ctx.arena, "");
                    return GdVal::from_str(make_str(ctx.arena, s.substr(static_cast<size_t>(start), static_cast<size_t>(ln))));
                }
                case SYM_replace: {
                    if (argc < 2 || args[0].kind != GdVal::Kind::Str || !args[0].str ||
                        args[1].kind != GdVal::Kind::Str || !args[1].str) {
                        return recv;
                    }
                    std::string_view what(args[0].str->data, args[0].str->len);
                    std::string_view with(args[1].str->data, args[1].str->len);
                    if (what.empty()) return recv;
                    std::string out;
                    out.reserve(s.size());
                    size_t pos = 0;
                    while (true) {
                        size_t p = s.find(what, pos);
                        if (p == std::string_view::npos) {
                            out.append(s.substr(pos));
                            break;
                        }
                        out.append(s.substr(pos, p - pos));
                        out.append(with);
                        pos = p + what.size();
                    }
                    return GdVal::from_str(make_str(ctx.arena, out));
                }
                case SYM_get_slice: {
                    if (argc < 2 || args[0].kind != GdVal::Kind::Str || !args[0].str) return GdVal::from_cstr(ctx.arena, "");
                    std::string_view delim(args[0].str->data, args[0].str->len);
                    int64_t target_idx = args[1].as_int();
                    if (target_idx < 0 || delim.empty()) return GdVal::from_cstr(ctx.arena, "");
                    int64_t cur = 0;
                    size_t pos = 0;
                    while (true) {
                        size_t next = s.find(delim, pos);
                        if (cur == target_idx) {
                            return GdVal::from_str(make_str(ctx.arena, next == std::string_view::npos ? s.substr(pos) : s.substr(pos, next - pos)));
                        }
                        if (next == std::string_view::npos) return GdVal::from_cstr(ctx.arena, "");
                        pos = next + delim.size();
                        ++cur;
                    }
                }
                case SYM_split: {
                    auto* arr = GdArr::create(ctx.arena);
                    if (argc < 1 || args[0].kind != GdVal::Kind::Str || !args[0].str) {
                        arr->push_back(ctx.arena, recv);
                        return GdVal::from_arr(arr);
                    }
                    std::string_view delim(args[0].str->data, args[0].str->len);
                    bool allow_empty = argc >= 2 ? gd_truth(args[1]) : true;
                    size_t pos = 0;
                    while (true) {
                        size_t next = delim.empty() ? std::string_view::npos : s.find(delim, pos);
                        std::string_view part = (next == std::string_view::npos) ? s.substr(pos) : s.substr(pos, next - pos);
                        if (allow_empty || !part.empty()) arr->push_back(ctx.arena, GdVal::from_str(make_str(ctx.arena, part)));
                        if (next == std::string_view::npos) break;
                        pos = next + delim.size();
                    }
                    return GdVal::from_arr(arr);
                }
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::Vec2: {
            const GdVec2& v = recv.v2;
            switch (m) {
                case SYM_length: return GdVal::from_float(std::sqrt(v.x * v.x + v.y * v.y));
                case SYM_length_squared: return GdVal::from_float(v.x * v.x + v.y * v.y);
                case SYM_normalized: {
                    double n = std::sqrt(v.x * v.x + v.y * v.y);
                    return n != 0.0 ? GdVal::from_vec2(v.x / n, v.y / n) : GdVal::from_vec2(0.0, 0.0);
                }
                case SYM_floor: return GdVal::from_vec2(std::floor(v.x), std::floor(v.y));
                case SYM_round: {
                    auto rnd = [](double d) { return d >= 0.0 ? std::floor(d + 0.5) : -std::floor(-d + 0.5); };
                    return GdVal::from_vec2(rnd(v.x), rnd(v.y));
                }
                case SYM_abs: return GdVal::from_vec2(std::abs(v.x), std::abs(v.y));
                case SYM_rotated: {
                    double phi = argc >= 1 ? args[0].as_float() : 0.0;
                    double c = std::cos(phi), sn = std::sin(phi);
                    return GdVal::from_vec2(v.x * c - v.y * sn, v.x * sn + v.y * c);
                }
                case SYM_distance_to: {
                    GdVec2 o = (argc >= 1 && args[0].kind == GdVal::Kind::Vec2) ? args[0].v2 : GdVec2{};
                    double dx = v.x - o.x, dy = v.y - o.y;
                    return GdVal::from_float(std::sqrt(dx * dx + dy * dy));
                }
                case SYM_distance_squared_to: {
                    GdVec2 o = (argc >= 1 && args[0].kind == GdVal::Kind::Vec2) ? args[0].v2 : GdVec2{};
                    double dx = v.x - o.x, dy = v.y - o.y;
                    return GdVal::from_float(dx * dx + dy * dy);
                }
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::Rng: {
            if (!recv.rng) return GdVal::null();
            switch (m) {
                case SYM_randi: return GdVal::from_int(recv.rng->randi());
                case SYM_randi_range:
                    return GdVal::from_int(argc >= 2 ? recv.rng->randi_range(args[0].as_int(), args[1].as_int()) : 0);
                case SYM_randf: return GdVal::from_float(recv.rng->randf());
                case SYM_randd: return GdVal::from_float(recv.rng->randd());
                case SYM_randf_range:
                    return GdVal::from_float(argc >= 2 ? recv.rng->randf_range(args[0].as_float(), args[1].as_float()) : 0.0);
                case SYM_randomize:
                    recv.rng->randomize();
                    return GdVal::null();
                case SYM_set_seed:
                    if (argc >= 1) recv.rng->set_seed(static_cast<uint64_t>(args[0].as_int()));
                    return GdVal::null();
                case SYM_get_seed:
                    return GdVal::from_int(static_cast<int64_t>(recv.rng->get_seed()));
                case SYM_set_state:
                    if (argc >= 1) recv.rng->set_state(static_cast<uint64_t>(args[0].as_int()));
                    return GdVal::null();
                case SYM_get_state:
                    return GdVal::from_int(static_cast<int64_t>(recv.rng->get_state()));
                default: return GdVal::null();
            }
        }
        case GdVal::Kind::FuncRef: {
            if (!recv.fr) return GdVal::null();
            switch (m) {
                case SYM_set_function:
                    if (argc >= 1) recv.fr->method = val_to_sym(args[0]);
                    return recv;
                case SYM_set_instance:
                    if (argc >= 1) recv.fr->instance = (args[0].kind == GdVal::Kind::Obj) ? args[0].obj : nullptr;
                    return recv;
                case SYM_get_instance:
                    return GdVal::from_obj(recv.fr->instance);
                case SYM_is_valid:
                    return GdVal::from_bool(recv.fr->is_valid());
                case SYM_call_func:
                    return recv.fr->call_func(ctx, args, argc);
                case SYM_call_funcv:
                    return argc >= 1 ? recv.fr->call_funcv(ctx, args[0]) : GdVal::null();
                default: return GdVal::null();
            }
        }
        default:
            return GdVal::null();
    }
}

}  // namespace gd

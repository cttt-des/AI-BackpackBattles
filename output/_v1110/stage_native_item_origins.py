"""Export item identity at the same battle boundary as the source recorder."""
from pathlib import Path


path = Path(__file__).resolve().parent / "sim_native/native_sim_cpp/native_sim/engine_wrapper.cpp"
source = path.read_text(encoding="utf8")


def replace(before, after):
    global source
    assert source.count(before) == 1, before
    source = source.replace(before, after)


replace("struct DbgEv { double ts; int32_t type; std::string line; DbgGemOrigin gem_origin; };", """struct DbgItemOrigin {
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
static bool g_dbg_item_origins = false;""")
replace("    g_dbg_events.push_back(DbgEv{ts, type, std::move(line), dbg_gem_origin(ov)});", """    DbgItemOrigin item_origin;
    if (g_dbg_item_origins && ov.kind == gd::GdVal::Kind::Obj && ov.obj) {
        auto* item = dynamic_cast<Gd__gd_core__CoreItem*>(ov.obj);
        if (item && item->f_ownerType.as_int() != 7) item_origin.pending = item;
    }
    g_dbg_events.push_back(DbgEv{ts, type, std::move(line), dbg_gem_origin(ov), std::move(item_origin)});""")
replace("    out.player_wins = gd::gd_truth(combat_obj->fn_playerWins(nullptr, 0)) ? 1 : 0;", """    if (g_dbg_item_origins && g_dbg_enabled.load(std::memory_order_relaxed)) {
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

    out.player_wins = gd::gd_truth(combat_obj->fn_playerWins(nullptr, 0)) ? 1 : 0;""")
anchor = "int32_t gd_sim_dbg_event_gem_origin(int32_t idx, const char** gem, const char** host,"
replace(anchor, """void gd_sim_set_dbg_item_origins(int32_t on) {
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

""" + anchor)
path.write_text(source, encoding="utf8", newline="\n")

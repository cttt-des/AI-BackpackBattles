"""Cache symbol reads per thread and invalidate them after every registry write."""
import argparse
from pathlib import Path


CACHES = '''
// Registered name storage belongs to the process-lifetime static arena.
// Cache entries never retain a caller's potentially temporary string_view.
static std::atomic<uint64_t> sym_revision{1};
struct CachedSymbolName {
    uint64_t revision = 0;
    SymId id = 0;
    const char* name = nullptr;
};
struct CachedInternedSymbol {
    uint64_t revision = 0;
    std::string_view text;
    SymId id = 0;
};
static thread_local CachedSymbolName sym_name_cache[256];
static thread_local CachedInternedSymbol intern_sym_cache[256];
'''

INTERN = '''SymId intern_sym(std::string_view sv) {
    const auto revision = sym_revision.load(std::memory_order_acquire);
    auto& cached = intern_sym_cache[std::hash<std::string_view>{}(sv) & 255u];
    if (cached.revision == revision && cached.text == sv) return cached.id;
    std::lock_guard<std::mutex> lk(sym_mtx());
    ensure_builtin_syms_unlocked();
    auto& m = sym_map();
    auto it = m.find(sv);
    SymId id;
    std::string_view stable;
    if (it != m.end()) {
        id = it->second;
        stable = it->first;
    } else {
        auto& v = sym_names_vec();
        id = static_cast<SymId>(v.size());
        if (id < SYM_BUILTIN_END) id = SYM_BUILTIN_END;
        register_sym_unlocked(id, sv);
        stable = std::string_view(v[id], sv.size());
    }
    cached = {sym_revision.load(std::memory_order_relaxed), stable, id};
    return id;
}
'''

NAME = '''const char* sym_name(SymId id) {
    const auto revision = sym_revision.load(std::memory_order_acquire);
    auto& cached = sym_name_cache[id & 255u];
    if (cached.revision == revision && cached.id == id) return cached.name;
    std::lock_guard<std::mutex> lk(sym_mtx());
    ensure_builtin_syms_unlocked();
    const auto& v = sym_names_vec();
    const char* name = id < v.size() && v[id] ? v[id] : "";
    cached = {sym_revision.load(std::memory_order_relaxed), id, name};
    return name;
}
'''


def optimize(native):
    import re
    path = native / "gd_rt.cpp"
    source = path.read_text("utf8")
    if "sym_revision" in source:
        raise ValueError("Symbol cache is already present")
    for name, replacement in (("intern_sym", INTERN), ("sym_name", NAME)):
        pattern = rf"^(?:SymId|const char\*) {name}\([^\n]*\n.*?^\}}\n"
        source, count = re.subn(pattern, lambda _: replacement, source, flags=re.M | re.S)
        if count != 1:
            raise ValueError(f"Expected one {name} implementation")
    anchor = "    sym_map()[std::string_view(copy, sv.size())] = id;\n"
    if source.count(anchor) != 1:
        raise ValueError("Symbol registry write path changed")
    source = source.replace(anchor, anchor + "    sym_revision.fetch_add(1, std::memory_order_release);\n")
    source = source.replace("namespace gd {\n", "namespace gd {\n" + CACHES, 1)
    source = source.replace('#include <algorithm>\n', '#include <algorithm>\n#include <atomic>\n', 1)
    path.write_text(source, encoding="utf8", newline="\n")
    print("Cached symbol names and interned IDs with registry revision invalidation", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

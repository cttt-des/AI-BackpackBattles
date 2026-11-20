"""Read registered symbols through atomic tables, retaining locked misses and writes."""
import argparse
import hashlib
from pathlib import Path
import re


TABLES = '''
struct FastInternedSymbol {
    std::string_view text;
    SymId id;
};
static std::atomic<const char*> fast_sym_names[8192]{};
static std::atomic<const FastInternedSymbol*> fast_interned_syms[16384]{};
static std::atomic<uint64_t> sym_revision{0};
static std::atomic<bool> sym_reads_ready{false};
struct SymWriteGuard {
    SymWriteGuard() { sym_revision.fetch_add(1, std::memory_order_acq_rel); }
    ~SymWriteGuard() { sym_revision.fetch_add(1, std::memory_order_release); }
};
'''

NAME = '''const char* sym_name(SymId id) {
    if (id < 8192 && sym_reads_ready.load(std::memory_order_acquire)) {
        const auto before = sym_revision.load(std::memory_order_acquire);
        if (!(before & 1u)) {
            const char* name = fast_sym_names[id].load(std::memory_order_acquire);
            if (name && sym_revision.load(std::memory_order_acquire) == before) return name;
        }
    }
    std::lock_guard<std::mutex> lk(sym_mtx());
    ensure_builtin_syms_unlocked();
    const auto& v = sym_names_vec();
    if (id < v.size() && v[id]) return v[id];
    return "";
}
'''

FAST_INTERN = '''
    if (sym_reads_ready.load(std::memory_order_acquire)) {
        const auto before = sym_revision.load(std::memory_order_acquire);
        if (!(before & 1u)) {
            const auto slot = std::hash<std::string_view>{}(sv) & 16383u;
            const auto* entry = fast_interned_syms[slot].load(std::memory_order_acquire);
            if (entry && entry->text == sv &&
                    sym_revision.load(std::memory_order_acquire) == before) return entry->id;
        }
    }
'''

PUBLISH = '''
    // Both the copied text and immutable cache entries live in the static arena.
    // Readers fall back to the mutex if a write overlaps either table read.
    auto* entry = static_arena().make<FastInternedSymbol>();
    entry->text = std::string_view(copy, sv.size());
    entry->id = id;
    fast_interned_syms[std::hash<std::string_view>{}(sv) & 16383u].store(entry, std::memory_order_release);
    if (id < 8192) fast_sym_names[id].store(copy, std::memory_order_release);
'''


def optimize(native):
    path = native / "gd_rt.cpp"
    source = path.read_text("utf8")
    start = source.index("static std::mutex& sym_mtx() {")
    end = source.index("const GdStr* make_str(", start)
    registry_hash = hashlib.sha256(source[start:end].encode()).hexdigest()
    if source.count("sym_map()") != 3 or source.count("sym_names_vec()") != 4:
        raise ValueError("Symbol table access paths changed")
    if "sym_revision" in source:
        if source.count(TABLES) == 1 and registry_hash == "d8be7b7673af208655d98386478ace1f6e7a5333931a3857ecac5b6a7df02b36":
            print("Atomic symbol tables are already applied", flush=True)
            return
        raise ValueError("An unexpected symbol cache is already present")
    if registry_hash != "f470f202cef7c9fef0d4ebae731766246a1698da6d4c6757d6f345bf9fdd5394":
        raise ValueError("The symbol registry implementation changed")
    required = ("namespace gd {\n", "static void register_sym_unlocked(SymId id, std::string_view sv) {\n",
                "    sym_map()[std::string_view(copy, sv.size())] = id;\n", "#undef GD_X_REG\n",
                "SymId intern_sym(std::string_view sv) {\n")
    for anchor in required:
        if source.count(anchor) != 1:
            raise ValueError(f"Unexpected symbol registry anchor: {anchor}")
    source = source.replace(required[0], required[0] + TABLES)
    source = source.replace(required[1], required[1] + "    const SymWriteGuard writing;\n")
    source = source.replace(required[2], required[2] + PUBLISH)
    source = source.replace(required[3], required[3] + "    sym_reads_ready.store(true, std::memory_order_release);\n")
    source = source.replace(required[4], required[4] + FAST_INTERN)
    source, count = re.subn(r"^const char\* sym_name\([^\n]*\n.*?^\}\n", lambda _: NAME,
                            source, flags=re.M | re.S)
    if count != 1:
        raise ValueError("Expected one symbol name lookup")
    source = source.replace('#include <algorithm>\n', '#include <algorithm>\n#include <atomic>\n', 1)
    path.write_text(source, encoding="utf8", newline="\n")
    print("Added atomic symbol tables with locked writes, version validation and locked misses", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)

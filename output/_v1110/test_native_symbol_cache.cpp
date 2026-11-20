#include "gd_rt.hpp"
#include <atomic>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
    constexpr gd::SymId first = 4096;
    gd::register_sym(gd::SYM_size, "before_builtin_initialization");
    assert(std::strcmp(gd::sym_name(gd::SYM_size), "size") == 0);
    assert(std::strcmp(gd::sym_name(first), "") == 0);
    gd::register_sym(first, "cache_test_old");
    for (int i = 0; i < 100; ++i) {
        assert(std::strcmp(gd::sym_name(first), "cache_test_old") == 0);
        assert(gd::intern_sym(std::string("cache_test_old")) == first);
    }
    gd::register_sym(first, "cache_test_new");
    assert(std::strcmp(gd::sym_name(first), "cache_test_new") == 0);
    assert(gd::intern_sym("cache_test_new") == first);
    // The original registry retains old aliases when the name of an ID changes.
    assert(gd::intern_sym("cache_test_old") == first);
    gd::register_sym(first + 1, "cache_test_old");
    assert(gd::intern_sym("cache_test_old") == first + 1);
    assert(std::strcmp(gd::sym_name(first + 1), "cache_test_old") == 0);

    // SymId collisions in the direct-mapped name cache must not alias.
    for (int i = 0; i < 8; ++i) {
        const auto id = first + 100 + i * 256;
        const auto name = "cache_collision_" + std::to_string(i);
        gd::register_sym(id, name);
        assert(name == gd::sym_name(id));
        assert(gd::intern_sym(std::string(name)) == id);
    }
    const std::string embedded("cache\0binary", 12);
    const auto embedded_id = gd::intern_sym(embedded);
    assert(embedded_id == gd::intern_sym(std::string(embedded)));
    assert(std::memcmp(gd::sym_name(embedded_id), embedded.data(), embedded.size()) == 0);

    std::atomic<int> ready{0};
    std::atomic<bool> proceed{false};
    std::vector<std::thread> readers;
    for (int worker = 0; worker < 8; ++worker) {
        readers.emplace_back([&] {
            assert(std::strcmp(gd::sym_name(first), "cache_test_new") == 0);
            assert(gd::intern_sym("cache_test_old") == first + 1);
            ready.fetch_add(1, std::memory_order_release);
            while (!proceed.load(std::memory_order_acquire)) std::this_thread::yield();
            for (int i = 0; i < 1000; ++i) {
                assert(std::strcmp(gd::sym_name(first), "cache_test_concurrent") == 0);
                assert(gd::intern_sym("cache_test_old") == first + 2);
                // Creating additional names also invalidates existing entries.
                const auto text = "cache_thread_" + std::to_string(i % 13);
                const auto id = gd::intern_sym(std::string(text));
                assert(text == gd::sym_name(id));
            }
        });
    }
    while (ready.load(std::memory_order_acquire) != 8) std::this_thread::yield();
    gd::register_sym(first, "cache_test_concurrent");
    gd::register_sym(first + 2, "cache_test_old");
    proceed.store(true, std::memory_order_release);
    for (auto& reader : readers) reader.join();
    gd::register_sym(60000, "outside_name_table");
    assert(std::strcmp(gd::sym_name(60000), "outside_name_table") == 0);
    assert(gd::intern_sym("outside_name_table") == 60000);
    gd::register_sym(first + 3, "cache_live_0");
    std::atomic<bool> stopped{false};
    std::atomic<int> live_ready{0};
    std::thread writer([&] {
        while (live_ready.load(std::memory_order_acquire) != 8) std::this_thread::yield();
        for (int i = 0; i < 1000; ++i) {
            gd::register_sym(first + 3, i % 2 ? "cache_live_1" : "cache_live_0");
            if (i % 16 == 0) std::this_thread::yield();
        }
        stopped.store(true, std::memory_order_release);
    });
    readers.clear();
    for (int worker = 0; worker < 8; ++worker) {
        readers.emplace_back([&] {
            live_ready.fetch_add(1, std::memory_order_release);
            do {
                const std::string name = gd::sym_name(first + 3);
                assert(name == "cache_live_0" || name == "cache_live_1");
                assert(gd::intern_sym("cache_live_0") == first + 3);
            } while (!stopped.load(std::memory_order_acquire));
        });
    }
    writer.join();
    for (auto& reader : readers) reader.join();
    std::cout << "Builtin initialization, replacements, aliases, temporary strings, collisions, binary names, fallback IDs and eight-thread live writes passed\n";
}

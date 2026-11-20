#include "gd_rt.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

struct Allocation {unsigned char* pointer;size_t bytes;unsigned char marker;};
struct Request {size_t bytes,alignment;};

void check(const std::vector<Allocation>& allocations) {
    std::vector<Allocation> sorted=allocations;
    std::sort(sorted.begin(),sorted.end(),[](auto a,auto b){return uintptr_t(a.pointer)<uintptr_t(b.pointer);});
    for(size_t i=1;i<sorted.size();++i)
        assert(uintptr_t(sorted[i-1].pointer)+sorted[i-1].bytes<=uintptr_t(sorted[i].pointer));
    for(const auto& row:allocations)
        for(size_t j=0;j<row.bytes;++j)assert(row.pointer[j]==row.marker);
}

int main() {
    static_assert(sizeof(gd::GdArr)==24);
    std::mt19937 rng(42);
    std::vector<Request> requests;
    for(unsigned i=0;i<12000;++i)requests.push_back({i%17==0?size_t{0}:size_t(rng()%2049),size_t{1}<<(rng()%13)});
    requests.push_back({35000,4096});
    gd::BattleArena arena(8192);
    std::vector<Allocation> initial;
    for(size_t i=0;i<requests.size();++i) {
        const auto request=requests[i];
        auto* p=static_cast<unsigned char*>(arena.alloc_raw(request.bytes,request.alignment));
        const auto size=std::max(size_t{1},request.bytes);const auto marker=static_cast<unsigned char>(i%251+1);
        assert(uintptr_t(p)%request.alignment==0 && arena.owns_storage(p,size));
        std::memset(p,marker,size);initial.push_back({p,size,marker});
    }
    check(initial);
    int outside=0;assert(!arena.owns_storage(&outside,sizeof(outside)));
    arena.reset();
    for(const auto& row:initial)assert(!arena.owns_storage(row.pointer,1));
    std::vector<Allocation> reused;
    for(size_t i=0;i<requests.size();++i) {
        const auto request=requests[i];
        auto* p=static_cast<unsigned char*>(arena.alloc_raw(request.bytes,request.alignment));
        assert(p==initial[i].pointer);
        const auto marker=static_cast<unsigned char>(250-i%251);const auto size=std::max(size_t{1},request.bytes);
        std::memset(p,marker,size);reused.push_back({p,size,marker});
    }
    check(reused);
    gd::BattleArena locked(4096,true);
    std::vector<Allocation> rows[4];std::vector<std::thread> threads;
    for(unsigned worker=0;worker<4;++worker)threads.emplace_back([&,worker] {
        std::mt19937 random(100+worker);
        for(unsigned i=0;i<2000;++i) {
            const size_t size=random()%513,alignment=size_t{1}<<(random()%10);
            auto* p=static_cast<unsigned char*>(locked.alloc_raw(size,alignment));
            const auto bytes=std::max(size_t{1},size);const auto marker=static_cast<unsigned char>(worker+1);
            assert(uintptr_t(p)%alignment==0 && locked.owns_storage(p,bytes));
            std::memset(p,marker,bytes);rows[worker].push_back({p,bytes,marker});
        }
    });
    for(auto& thread:threads)thread.join();
    std::vector<Allocation> combined;
    for(const auto& group:rows)combined.insert(combined.end(),group.begin(),group.end());
    check(combined);
    // Placement constructors may allocate recursively: alloc_raw must release its lock.
    struct Nested {
        int* child;
        explicit Nested(gd::BattleArena& owner):child(owner.alloc_array<int>(2)){child[0]=17;child[1]=29;}
    };
    auto* object=locked.make<Nested>(locked);assert(object->child[0]==17 && object->child[1]==29);
    locked.reset();assert(!locked.owns_storage(object,sizeof(*object)));
    std::cout<<"{\"passed\":true,\"arena_bytes\":"<<sizeof(gd::BattleArena)
             <<",\"serial_requests\":"<<requests.size()<<",\"identical_reset_addresses\":"<<reused.size()
             <<",\"max_alignment\":4096,\"threaded_nonoverlapping_allocations\":"<<combined.size()
             <<",\"zero_bytes_large_blocks_content_ownership_and_nested_constructor\":true}\n";
}

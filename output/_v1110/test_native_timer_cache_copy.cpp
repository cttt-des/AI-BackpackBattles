#include "gd_rt.hpp"
#include <iostream>
#include <utility>
int main() {
    gd::NativeTimerScanCache original;
    uint32_t buffer[2]{1,3};
    original.indices=buffer;original.count=original.capacity=2;original.epoch=9;
    const auto empty=[](const gd::NativeTimerScanCache& cache) {
        return !cache.items && !cache.context && !cache.generation && !cache.epoch &&
            !cache.length && !cache.count && !cache.capacity && !cache.indices;
    };
    gd::NativeTimerScanCache copy(original),assigned;
    assigned=original;
    gd::NativeTimerScanCache moved(std::move(original));
    const bool constructed=empty(copy),assignment=empty(assigned),move=empty(moved);
    original=original;const bool self=empty(original);
    std::cout<<"{\"copy_cleared\":"<<(constructed?"true":"false")
        <<",\"assignment_cleared\":"<<(assignment?"true":"false")
        <<",\"move_cleared\":"<<(move?"true":"false")
        <<",\"self_assignment_cleared\":"<<(self?"true":"false")<<"}\n";
    return constructed && assignment && move && self ? 0 : 1;
}

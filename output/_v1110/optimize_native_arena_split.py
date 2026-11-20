"""Outline arena growth/locking while retaining the original allocation policy."""
import argparse
import hashlib
from pathlib import Path

INPUT_SHA256 = 'bf6ee43ba5c5a40ced3b217602b01444b5324ecabd4977ba42e13266c52903e0'
OUTPUT_SHA256 = '020bf6eb8f45dbfaaacfad3e252eef35c4d28955aff026ba0dd1e10dc3b6f9c9'
OLD_ALLOC = '    void* alloc_raw(size_t bytes, size_t align = 8) {\n        std::unique_lock<std::mutex> lk;\n        if (mtx_) lk = std::unique_lock<std::mutex>(*mtx_);\n        if (bytes == 0) bytes = 1;\n        while (cur_ < blocks_.size()) {\n            ArenaBlock& b = blocks_[cur_];\n            size_t off = (b.used + (align - 1)) & ~(align - 1);\n            if (align > alignof(std::max_align_t)) {\n                const auto base = reinterpret_cast<uintptr_t>(b.ptr);\n                off = ((base + b.used + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n            }\n            if (off + bytes <= b.cap) {\n                b.used = off + bytes;\n                return b.ptr + off;\n            }\n            cur_++;\n        }\n        size_t sz = bytes > block_bytes_ ? (bytes + align) : block_bytes_;\n        if (align > alignof(std::max_align_t) && bytes + align - 1 > sz) sz = bytes + align - 1;\n        ArenaBlock nb;\n        nb.ptr = new uint8_t[sz];\n        nb.cap = sz;\n        size_t initial_offset = 0;\n        if (align > alignof(std::max_align_t)) {\n            const auto base = reinterpret_cast<uintptr_t>(nb.ptr);\n            initial_offset = ((base + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n        }\n        nb.used = initial_offset + bytes;\n        blocks_.push_back(nb);\n        cur_ = blocks_.size() - 1;\n        return nb.ptr + initial_offset;\n    }\n\n'
NEW_ALLOC = '    void* alloc_raw(size_t bytes, size_t align = 8) {\n        if (mtx_) return alloc_raw_locked(bytes, align);\n        if (bytes == 0) bytes = 1;\n        if (cur_ < blocks_.size()) {\n            ArenaBlock& b = blocks_[cur_];\n            size_t off = (b.used + (align - 1)) & ~(align - 1);\n            if (align > alignof(std::max_align_t)) {\n                const auto base = reinterpret_cast<uintptr_t>(b.ptr);\n                off = ((base + b.used + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n            }\n            if (off + bytes <= b.cap) {\n                b.used = off + bytes;\n                return b.ptr + off;\n            }\n        }\n        return alloc_raw_slow(bytes, align);\n    }\n\n'
SLOW_HELPERS = '    __attribute__((noinline)) void* alloc_raw_locked(size_t bytes, size_t align) {\n        std::unique_lock<std::mutex> lk(*mtx_);\n        if (bytes == 0) bytes = 1;\n        return alloc_raw_slow(bytes, align);\n    }\n\n    __attribute__((noinline)) void* alloc_raw_slow(size_t bytes, size_t align) {\n        while (cur_ < blocks_.size()) {\n            ArenaBlock& b = blocks_[cur_];\n            size_t off = (b.used + (align - 1)) & ~(align - 1);\n            if (align > alignof(std::max_align_t)) {\n                const auto base = reinterpret_cast<uintptr_t>(b.ptr);\n                off = ((base + b.used + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n            }\n            if (off + bytes <= b.cap) {\n                b.used = off + bytes;\n                return b.ptr + off;\n            }\n            cur_++;\n        }\n        size_t sz = bytes > block_bytes_ ? (bytes + align) : block_bytes_;\n        if (align > alignof(std::max_align_t) && bytes + align - 1 > sz) sz = bytes + align - 1;\n        ArenaBlock nb;\n        nb.ptr = new uint8_t[sz];\n        nb.cap = sz;\n        size_t initial_offset = 0;\n        if (align > alignof(std::max_align_t)) {\n            const auto base = reinterpret_cast<uintptr_t>(nb.ptr);\n            initial_offset = ((base + (align - 1)) & ~(uintptr_t(align) - 1)) - base;\n        }\n        nb.used = initial_offset + bytes;\n        blocks_.push_back(nb);\n        cur_ = blocks_.size() - 1;\n        return nb.ptr + initial_offset;\n    }\n\n'
ANCHOR = 'private:\n    size_t block_bytes_;\n'


def normalize(source):
    if NEW_ALLOC not in source and SLOW_HELPERS not in source:return source
    if source.count(NEW_ALLOC)!=1 or source.count(SLOW_HELPERS)!=1:
        raise ValueError('An arena split region changed')
    return source.replace(NEW_ALLOC,OLD_ALLOC,1).replace(SLOW_HELPERS,'',1)


def transform(source):
    source=normalize(source)
    if source.count(OLD_ALLOC)!=1 or source.count(ANCHOR)!=1:
        raise ValueError('The verified arena allocation region changed')
    return source.replace(OLD_ALLOC,NEW_ALLOC,1).replace(ANCHOR,'private:\n'+SLOW_HELPERS+'    size_t block_bytes_;\n',1)


def optimize(native):
    path=native/'gd_rt.hpp';source=path.read_text('utf8')
    if hashlib.sha256(normalize(source).encode()).hexdigest()!=INPUT_SHA256:
        raise ValueError('The verified arena header changed')
    output=transform(source)
    assert hashlib.sha256(output.encode()).hexdigest()==OUTPUT_SHA256
    if path.read_bytes()!=output.encode():path.write_text(output,encoding='utf8',newline='\n')
    print('Outlined arena growth and mutex path; allocation order/alignment unchanged',flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)

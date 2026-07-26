"""
收集 BFS 树中所有 script_instance 节点，读取各自 GDScriptInstance::members 向量，
按成员数量排序，找出成员最多的节点（Game 自动加载通常成员最多）。

用法：
  python tools/scan_members_all.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_si(reader, is_inst, node):
    nmem = reader.read(node, 0x400) or b""
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(q) and is_inst(q) and _read_u64(reader, q + 8) == node:
            return q, i
    return None, None


def find_members_vec_stride(reader, is_inst, si, stride):
    simem = reader.read(si, 0x600) or b""
    best = None
    for k in range(0, len(simem) - 8, 8):
        vp = int.from_bytes(simem[k:k + 8], "little")
        if not _is_plausible_ptr(vp):
            continue
        ok = 0
        for m in range(10):
            vh = reader.read(vp + m * stride, 4)
            if not vh:
                break
            t = int.from_bytes(vh, "little")
            if 0 <= t <= 24:
                ok += 1
            else:
                break
        if ok >= 3:
            sd = reader.read(vp + stride // 2, 4) if False else reader.read(vp + 8, 4)
            sz = int.from_bytes(sd, "little") if sd else None
            cand = (ok, vp, k, sz)
            if best is None or ok > best[0]:
                best = cand
    return best


def dump_members(reader, mptr, msize, stride):
    out = []
    for k in range(min(msize, 80)):
        vaddr = mptr + k * stride
        vh = reader.read(vaddr, 4)
        if not vh:
            out.append(None); continue
        t = int.from_bytes(vh, "little")
        if t == 2:
            q = reader.read(vaddr + 8, 8)
            out.append(int.from_bytes(q, "little") if q else None)
        elif t == 3:
            q = reader.read(vaddr + 8, 8)
            out.append(int.from_bytes(q, "little") if q else None)
        else:
            out.append(f"t{t}")
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    args = ap.parse_args()

    reader = MemoryReader(args.pid)
    base = reader.module_base
    secs = read_module_sections(reader)
    text = next(s for s in secs if s[0] == ".text")
    rdata = next(s for s in secs if s[0] == ".rdata")
    data = next(s for s in secs if s[0] == ".data")
    text_lo, text_hi = base + text[1], base + text[1] + text[2]
    rdata_lo, rdata_hi = base + rdata[1], base + rdata[1] + rdata[2]

    _cache = {}
    def is_inst(a):
        if a in _cache:
            return _cache[a]
        r = _is_valid_instance(reader, a, text_lo, text_hi, rdata_lo, rdata_hi)
        _cache[a] = r
        return r

    instances = []
    addr = base + data[1]; end = addr + data[2]
    while addr < end:
        buf = reader.read(addr, min(1024 * 1024, end - addr))
        if not buf:
            break
        off = 0
        while off + 8 <= len(buf):
            obj = int.from_bytes(buf[off:off + 8], "little")
            if _is_plausible_ptr(obj) and is_inst(obj):
                instances.append(obj)
            off += 8
        addr += len(buf)

    chain = None
    for obj in instances:
        s = _read_u64(reader, obj + 0x1d0)
        if not _is_plausible_ptr(s) or not is_inst(s) or s == obj:
            continue
        r = _read_u64(reader, s + 0x230)
        if _is_plausible_ptr(r) and is_inst(r) and r != s:
            chain = (obj, s, r)
            break
    if not chain:
        print("[-] 链路未找到"); return 1
    obj, s, r = chain
    print(f"[*] root={hex(r)}")

    visited = set()
    queue = [(r, 0)]
    visited.add(r)
    si_nodes = []
    while queue:
        node, depth = queue.pop(0)
        if depth >= 2:
            continue
        if not is_inst(node):
            continue
        si, off = find_si(reader, is_inst, node)
        if si is not None:
            si_nodes.append((node, si, off))
        first = _read_u64(reader, node + 0x6c0)
        cur = first
        seen = set()
        for _ in range(400):
            if not _is_plausible_ptr(cur) or cur in seen:
                break
            seen.add(cur)
            v = _read_u64(reader, cur)
            if _is_plausible_ptr(v) and is_inst(v) and v not in visited:
                visited.add(v)
                queue.append((v, depth + 1))
            nxt = _read_u64(reader, cur + 8)
            cur = nxt

    print(f"[*] script_instance 节点数 = {len(si_nodes)}")
    results = []
    for node, si, off in si_nodes:
        best = None
        for stride in (24, 20):
            b = find_members_vec_stride(reader, is_inst, si, stride)
            if b and (best is None or b[0] > best[0]):
                best = b + (stride,)
        if best:
            ok, vp, mk, sz, stride = best
            if sz and 0 < sz < 4000:
                mems = dump_members(reader, vp, sz, stride)
                results.append((sz, node, off, mk, stride, mems))
    results.sort(reverse=True)
    print(f"[*] 有 members 的节点数 = {len(results)}")
    for sz, node, off, mk, stride, mems in results[:20]:
        print(f"  size={sz} node={hex(node)} si_off={hex(off)} moff={hex(mk)} stride={stride}")
        print(f"        {mems[:40]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

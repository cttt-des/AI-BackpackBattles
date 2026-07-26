"""
静态诊断 / 发现 OS::singleton 的 RVA —— 直接解析磁盘上的 Godot exe（无需运行游戏）。

原理（参考逆向结构）：
  OS_Windows::get_name() 返回字符串常量 "Windows"。
  → 在 .text 里找引用该字符串的函数（候选 get_name）
  → 在 rdata 里找包含该函数指针的 vtable（即 OS_Windows 的 vtable）
  → 在 rdata/.data 里找首字段等于该 vtable 的对象（OS_Windows 实例）
  → 在 .data 里找持有该实例指针的全局（OS::singleton）

本工具把 exe 按 PE 装载方式重建成连续映像（RVA 空间），扫描后输出候选 RVA 与证据，
既可用于调试，也可被 godot_probe 复用做「无运行进程」的静态标定。
"""
import struct
import sys
from typing import Dict, List, Optional, Tuple

# ----------------------------------------------------------------------------
# PE 解析：把 exe 重建为连续映像（RVA 可寻址，base=0）
# ----------------------------------------------------------------------------

def load_pe_image(path: str) -> Tuple[int, bytes, Dict[str, Tuple[int, int]]]:
    """返回 (image_base_va, image_bytes[RVA 可寻址], sections_dict[name]= (rva_start, rva_end))。"""
    with open(path, "rb") as f:
        raw = f.read()
    assert raw[:2] == b"MZ", "不是有效的 PE 文件"
    e_lfanew = struct.unpack("<I", raw[0x3C:0x40])[0]
    pe_off = e_lfanew
    assert raw[pe_off:pe_off + 4] == b"PE\x00\x00", "PE 签名缺失"
    coff = pe_off + 4
    machine = struct.unpack("<H", raw[coff:coff + 2])[0]
    num_sections = struct.unpack("<H", raw[coff + 2:coff + 4])[0]
    opt_hdr_size = struct.unpack("<H", raw[coff + 16:coff + 18])[0]
    opt_off = coff + 20
    magic = struct.unpack("<H", raw[opt_off:opt_off + 2])[0]
    assert magic == 0x20B, f"仅支持 PE32+ (x64)，magic={hex(magic)}"
    image_base = struct.unpack("<Q", raw[opt_off + 24:opt_off + 32])[0]
    size_of_image = struct.unpack("<I", raw[opt_off + 56:opt_off + 60])[0]
    sect_off = opt_off + opt_hdr_size
    sections: Dict[str, Tuple[int, int]] = {}
    image = bytearray(size_of_image)
    for i in range(num_sections):
        sh = sect_off + i * 40
        name = raw[sh:sh + 8].split(b"\x00", 1)[0].decode("latin1", "replace")
        vsize = struct.unpack("<I", raw[sh + 8:sh + 12])[0]
        vaddr = struct.unpack("<I", raw[sh + 12:sh + 16])[0]
        rawsize = struct.unpack("<I", raw[sh + 16:sh + 20])[0]
        rawptr = struct.unpack("<I", raw[sh + 20:sh + 24])[0]
        # 把文件原始数据拷到其 RVA 位置（重建装载映像）
        end = min(rawsize, vsize, len(raw) - rawptr)
        if end > 0:
            image[vaddr:vaddr + end] = raw[rawptr:rawptr + end]
        sections[name] = (vaddr, vaddr + vsize)
    return image_base, bytes(image), sections


# ----------------------------------------------------------------------------
# 扫描逻辑
# ----------------------------------------------------------------------------

def find_windows_string_refs(image: bytes, base: int = 0) -> List[int]:
    """找 .text 里 lea reg,[rip+disp32] 引用 "Windows" 字符串的函数地址（base 缺省为 0 即 RVA）。

    注意：'Windows' 是常见子串（WindowsStore/WindowsSDK...），必须要求词边界
    （后接 \\0 或非 [A-Za-z0-9_]），只匹配真正的 OS 名常量 "Windows\\0"。
    """
    positions = [m.start() for m in __import__("re").finditer(rb"Windows", image)]
    if not positions:
        return []
    str_addrs = set()
    for p in positions:
        after = image[p + 7:p + 8]
        # 词边界：后接空字节或非字母数字下划线
        if after == b"" or after[0] in (0,) or not (48 <= after[0] <= 57 or 65 <= after[0] <= 90
                                                  or 97 <= after[0] <= 122 or after[0] == 0x5F):
            str_addrs.add(base + p)
    cands: set = set()
    i = 0
    n = len(image)
    while i < n - 6:
        # REX.W lea reg, [rip+disp32] : 48 8D /r ; /r mod=00 rm=101(rip) -> 05/0D/15/1D/25/2D/35
        if image[i] == 0x48 and image[i + 1] == 0x8D and image[i + 2] in (0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x35):
            disp = struct.unpack("<i", image[i + 3:i + 7])[0]
            target = base + i + 7 + disp
            if target in str_addrs:
                cands.add(base + i)
        # 32-bit lea (无 REX.W): 8D /r
        elif image[i] == 0x8D and image[i + 1] in (0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x35):
            disp = struct.unpack("<i", image[i + 2:i + 6])[0]
            target = base + i + 6 + disp
            if target in str_addrs:
                cands.add(base + i)
        i += 1
    return sorted(cands)


def section_of(rva: int, sections: Dict[str, Tuple[int, int]]) -> Optional[str]:
    for name, (s, e) in sections.items():
        if s <= rva < e:
            return name
    return None


def find_vtable_for_func(image: bytes, func_rva: int, image_base: int,
                         sections: Dict[str, Tuple[int, int]],
                         code_names=(".text",)) -> Optional[int]:
    """在 rdata/.data 里找包含 (image_base+func_rva) 的 vtable，返回 vtable 起点 RVA（向后扫到非函数指针为止）。"""
    target = struct.pack("<Q", image_base + func_rva)
    rdata_names = [n for n in (".rdata", ".data", ".idata") if n in sections]
    # 收集所有命中位置
    hits: List[int] = []
    for nm in rdata_names:
        s, e = sections[nm]
        chunk = image[s:e]
        idx = 0
        while True:
            idx = chunk.find(target, idx)
            if idx == -1:
                break
            hits.append(s + idx)
            idx += 8
    if not hits:
        return None
    # 取第一个命中，向后（低地址）扫到连续函数指针块的起点 = vtable 起点
    best_vt = None
    best_slot = 10 ** 9
    for entry_rva in hits:
        # 向后扫描
        pos = entry_rva
        while True:
            prev = pos - 8
            if prev < 0:
                break
            val = struct.unpack("<Q", image[prev:prev + 8])[0]
            if (val - image_base) < 0 or (val - image_base) >= len(image):
                break
            if section_of(val - image_base, sections) not in code_names:
                break
            pos = prev
        vt = pos
        slot = (entry_rva - vt) // 8
        if slot < best_slot:
            best_slot = slot
            best_vt = vt
    return best_vt


def find_ptr_targets_in_sections(image: bytes, value_va: int,
                                  sections: Dict[str, Tuple[int, int]],
                                  names: List[str]) -> List[int]:
    """在指定段里找 8 字节值 == value_va 的所有 RVA。"""
    target = struct.pack("<Q", value_va)
    out: List[int] = []
    for nm in names:
        if nm not in sections:
            continue
        s, e = sections[nm]
        chunk = image[s:e]
        idx = 0
        while True:
            idx = chunk.find(target, idx)
            if idx == -1:
                break
            out.append(s + idx)
            idx += 8
    return out


def discover_from_image(path: str, verbose: bool = True) -> List[Tuple[int, dict]]:
    image_base, image, sections = load_pe_image(path)
    out: List[Tuple[int, dict]] = []
    funcs = find_windows_string_refs(image, 0)
    if verbose:
        print(f"[*] 字符串 'Windows' 候选引用函数: {[hex(f) for f in funcs]}")
        print(f"[*] 段: { {k: (hex(s), hex(e)) for k,(s,e) in sections.items()} }")
    if not funcs:
        if verbose:
            print("[!] 未找到任何 'Windows' 字符串引用，无法定位 get_name")
        return out
    for f in funcs:
        vt = find_vtable_for_func(image, f, image_base, sections)
        if vt is None:
            if verbose:
                print(f"    [-] 函数 {hex(f)} 未找到 vtable")
            continue
        # OS_Windows 实例：首字段等于 vtable 的全局对象（通常在 .data/.rdata）
        insts = find_ptr_targets_in_sections(image, image_base + vt, sections, [".data", ".rdata"])
        for inst in insts[:3]:
            # OS::singleton 全局：持有实例指针
            singles = find_ptr_targets_in_sections(image, image_base + inst, sections, [".data"])
            for sg in singles[:5]:
                ev = {
                    "get_name_fn": f,
                    "vtable_rva": vt,
                    "instance_rva": inst,
                    "instance_first_field_is_vtable": struct.unpack("<Q", image[inst:inst + 8])[0] == image_base + vt,
                }
                out.append((sg, ev))
    # 去重（按 singleton RVA）
    seen = set()
    uniq = []
    for rva, ev in out:
        if rva in seen:
            continue
        seen.add(rva)
        uniq.append((rva, ev))
    return uniq


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else r"Backpack Battles\BackpackBattles.exe"
    print(f"== 分析 {path} ==")
    cands = discover_from_image(path, verbose=True)
    print(f"\n候选 OS::singleton RVA 数量: {len(cands)}")
    for rva, ev in cands:
        print(f"  RVA={hex(rva)}  get_name={hex(ev['get_name_fn'])}  vtable={hex(ev['vtable_rva'])}  instance={hex(ev['instance_rva'])}  vtable_match={ev['instance_first_field_is_vtable']}")


if __name__ == "__main__":
    main()

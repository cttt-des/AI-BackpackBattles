"""
Godot 结构性读取的一次性标定逻辑（可复用）。

被 bot（自动标定）与 tools/probe_godot.py（CLI 诊断）共用，避免重复实现。

核心：从 OS::singleton 全局定位 SceneTree → Game 单例，再读其 GDScript 成员。
所有扫描/解析都是只读的，不修改游戏进程。

自动发现 OS::singleton 的 RVA 采用「正向链路校验」（runtime forward-chain）：
  OS::singleton 全局
    -> OS 实例（首字段为 vtable，在 rdata）
    -> OS.main_loop（SceneTree，vtable 在 rdata）
    -> SceneTree.root（Viewport，其 parent 为 null = 根视口）
    -> root.children[game_child_index] 是合法节点（Game 单例）
只要每一步指针都落在模块内且形态合法，即判定该全局就是 OS::singleton。
不依赖任何字符串/虚函数名，对 Godot 3.x 各构建都稳健。
"""
import struct
import logging
from typing import Dict, List, Optional, Tuple

from .memory_reader import MemoryReader
from .godot_reader import GodotReader, GODOT_OFFSETS

logger = logging.getLogger(__name__)

# 上次发现的诊断信息（供 bot/GUI 记录失败原因）
last_diag: Dict = {}


def load_module_bytes(reader: MemoryReader) -> Tuple[int, bytes]:
    """返回 (module_base, module_bytes) —— 读整段 PE 映像（连续）。"""
    base = reader.module_base
    if not base:
        return 0, b""
    if reader.read(base, 2) != b"MZ":
        chunk = reader.read(base, 64 * 1024 * 1024)
        return base, chunk or b""
    e_lfanew = struct.unpack("<I", reader.read(base + 0x3C, 4) or b"\x00\x00\x00\x00")[0]
    pe_off = base + e_lfanew
    size_of_image = struct.unpack("<I", reader.read(pe_off + 4 + 20 + 56, 4) or b"\x00\x00\x00\x00")[0]
    if not size_of_image or size_of_image > 512 * 1024 * 1024:
        chunk = reader.read(base, 64 * 1024 * 1024)
        return base, chunk or b""
    data = reader.read(base, size_of_image)
    return base, data or b""


# ---------------------------------------------------------------------------
# PE / 运行时只读辅助
# ---------------------------------------------------------------------------

def _read_u32(reader: MemoryReader, addr: int) -> Optional[int]:
    d = reader.read(addr, 4)
    return struct.unpack("<I", d)[0] if d else None


def _read_u64(reader: MemoryReader, addr: int) -> Optional[int]:
    d = reader.read(addr, 8)
    return struct.unpack("<Q", d)[0] if d else None


def _in_range(addr: int, lo: int, hi: int) -> bool:
    return lo <= addr < hi


def _is_plausible_ptr(addr: Optional[int]) -> bool:
    """用户态指针的粗略判断（非空、不过小、不超用户态上限）。

    注意：OS / SceneTree / 根视口等对象都是堆分配，地址落在模块映像之外，
    因此不能要求对象地址落在 [module_base, module_base+size] 内；
    只需它们是合法用户态指针，且其 vtable 落在模块内即可。
    """
    return addr is not None and 0x10000 <= addr <= 0x7FFFFFFFFFFF


def read_module_sections(reader: MemoryReader) -> List[Tuple[str, int, int]]:
    """从运行进程内存读取 PE 段表，返回 [(name, vaddr, vsize)]。"""
    base = reader.module_base
    if not base:
        return []
    try:
        if reader.read(base, 2) != b"MZ":
            return []
        e_lfanew = _read_u32(reader, base + 0x3C) or 0
        pe = base + e_lfanew
        if _read_u32(reader, pe) != 0x00004550:  # "PE\0\0"
            return []
        coff = pe + 4
        num_sec = struct.unpack("<H", reader.read(coff + 2, 2) or b"\x00\x00")[0]
        opt_size = struct.unpack("<H", reader.read(coff + 16, 2) or b"\x00\x00")[0]
        opt_off = coff + 20
        if struct.unpack("<H", reader.read(opt_off, 2) or b"\x00\x00")[0] != 0x20B:
            return []
        sect_off = opt_off + opt_size
        out = []
        for i in range(num_sec):
            sh = sect_off + i * 40
            name_b = reader.read(sh, 8) or b""
            name = name_b.split(b"\x00", 1)[0].decode("latin1", "replace")
            vsize = _read_u32(reader, sh + 8) or 0
            vaddr = _read_u32(reader, sh + 12) or 0
            out.append((name, vaddr, vsize))
        return out
    except Exception as e:  # noqa: BLE001
        logger.warning("读取 PE 段表失败: %s", e)
        return []


def _is_vtable_ptr(reader: MemoryReader, addr: int, text_lo: int, text_hi: int,
                   rdata_lo: int, rdata_hi: int) -> bool:
    """addr 是否像一个 vtable：必须落在 .rdata 段内，且前 32 个槽里存在一段 ≥8 个连续 .text 函数指针。

    vtable 只在 .rdata 中，绝不会落在堆或 .text；用 .rdata 范围可排除
    「对象地址恰好落在模块 VA 区间内」造成的误判（如某对象的 qw0 指向自身）。
    真 vtable 有数十个连续虚函数指针；随机数据不会凑出 8 连击。
    """
    if not _in_range(addr, rdata_lo, rdata_hi):
        return False
    run = 0
    best = 0
    for i in range(32):
        slot = _read_u64(reader, addr + i * 8)
        if slot is None:
            return False
        if slot != 0 and _in_range(slot, text_lo, text_hi):
            run += 1
            best = max(best, run)
        else:
            run = 0
    return best >= 8


def _is_valid_instance(reader: MemoryReader, addr: int, text_lo: int, text_hi: int,
                       rdata_lo: int, rdata_hi: int) -> bool:
    if not _is_plausible_ptr(addr):
        return False
    vt = _read_u64(reader, addr)
    # vtable 必须落在 .rdata 段内（对象本身可在堆上，地址在模块外也没关系）
    if vt is None or not _in_range(vt, rdata_lo, rdata_hi):
        return False
    return _is_vtable_ptr(reader, vt, text_lo, text_hi, rdata_lo, rdata_hi)


def _get_child(reader: MemoryReader, node: int, index: int, children_off: int) -> Optional[int]:
    """Godot List<Node*>：首元素在 node+children_off；Element{value(Node*), next, prev}。"""
    elem = _read_u64(reader, node + children_off)
    for i in range(index + 1):
        if not elem or elem < 0x10000:
            return None
        if i == index:
            return _read_u64(reader, elem)
        elem = _read_u64(reader, elem + 8)
    return None


def _validate_os_chain(reader: MemoryReader, obj: int, text_lo: int, text_hi: int,
                       rdata_lo: int, rdata_hi: int, ml_off: int, root_off: int,
                       parent_off: int, children_off: int) -> bool:
    """校验 obj 是否 OS 实例：OS -> main_loop(SceneTree) -> root(根视口)。

    OS / SceneTree / 根视口都是堆对象，地址在模块外；只要 vtable 落在 .rdata 即视为合法实例。
    根视口的 parent 必须为 null；并且其 children 列表（首元素）是一个合法实例（至少有一子节点）。
    Game 子节点下标是「读成员」阶段的事，定位 OS::singleton 时不强依赖它。
    """
    if not _is_valid_instance(reader, obj, text_lo, text_hi, rdata_lo, rdata_hi):
        return False
    s = _read_u64(reader, obj + ml_off)
    if not _is_plausible_ptr(s):
        return False
    if not _is_valid_instance(reader, s, text_lo, text_hi, rdata_lo, rdata_hi):
        return False
    r = _read_u64(reader, s + root_off)
    if not _is_plausible_ptr(r):
        return False
    if not _is_valid_instance(reader, r, text_lo, text_hi, rdata_lo, rdata_hi):
        return False
    if _read_u64(reader, r + parent_off) != 0:
        return False  # 根视口的 parent 必须为 null
    # children 列表：首元素指针在 r+children_off，其 value 应为合法实例（至少一子节点）
    first = _read_u64(reader, r + children_off)
    if not _is_plausible_ptr(first):
        return False
    c0 = _read_u64(reader, first)
    if not _is_plausible_ptr(c0):
        return False
    if not _is_valid_instance(reader, c0, text_lo, text_hi, rdata_lo, rdata_hi):
        return False
    return True


# 偏移变体网格：抵御 RE 偏移漂移。优先用 config 指定的，再尝试附近常见值。
# 分别为 (main_loop, root, parent, children)
def _offset_variants(ml: int, ro: int, po: int, co: int):
    # 经验确认值（Backpack Battles / Godot 3.6 x64，2026-07-26 活体标定）：
    #   main_loop=0x1d0, root=0x148(真根视口), parent=0xf0, children=0x108(Vector/CowData)
    # 注：children 校验的「两次解引用」对 List 与 Vector 均成立
    #（List: first=Element*→value；Vector: _ptr→元素0），因此同一网格通吃两种容器。
    mls = [ml, 0x1D0, 0x198, 0x1A0, 0x1A8, 0x1B0, 0x1C0, 0x1D8, 0x1E0]
    ros = [ro, 0x148, 0x140, 0x150, 0x230, 0x198, 0x1A0, 0x1A8, 0x1B0]
    pos = [po, 0xF0, 0xE8, 0xF8, 0x8, 0xC, 0x10]
    cos = [co, 0x108, 0x100, 0x110, 0x6c0, 0x48, 0x50, 0x58, 0x60]
    seen = set()
    out = []
    for a in mls:
        for b in ros:
            for p in pos:
                for c in cos:
                    key = (a, b, p, c)
                    if key in seen:
                        continue
                    seen.add(key)
                    out.append(key)
    return out


def _scan_os_singleton(reader: MemoryReader, offsets: dict) -> Tuple[Optional[int], dict]:
    """扫描 .data 全局，返回 (最先命中的 OS::singleton RVA, 诊断信息)。

    两遍：先收集所有「首字段是 vtable」的全局对象，再对候选尝试偏移变体网格做链路校验。
    这样能用多种偏移组合廉价验证，抵御 RE 偏移漂移。
    """
    base = reader.module_base
    diag = {
        "module_base": hex(base) if base else None,
        "data_scanned": 0,
        "object_globals": 0,
        "valid_instances": 0,
        "reached_scenetree": 0,
        "reached_root": 0,
        "reached_game": 0,
        "candidates": [],
        "variant_used": None,
    }
    if not base:
        return None, diag
    secs = read_module_sections(reader)
    if not secs:
        diag["error"] = "无法读取 PE 段表"
        return None, diag
    size_of_image = max(v + s for _, v, s in secs)
    mod_lo, mod_hi = base, base + size_of_image
    text = next((s for s in secs if s[0] == ".text"), None)
    if not text:
        diag["error"] = "找不到 .text 段"
        return None, diag
    text_lo, text_hi = base + text[1], base + text[1] + text[2]
    rdata = next((s for s in secs if s[0] == ".rdata"), None)
    if not rdata:
        diag["error"] = "找不到 .rdata 段"
        return None, diag
    rdata_lo, rdata_hi = base + rdata[1], base + rdata[1] + rdata[2]
    data = next((s for s in secs if s[0] == ".data"), None)
    if not data:
        diag["error"] = "找不到 .data 段"
        return None, diag

    ml = offsets.get("os_main_loop_off", 0x1A8)
    ro = offsets.get("scenetree_root_off", 0x1A0)
    po = offsets.get("node_parent_off", 0x8)
    co = offsets.get("node_children_off", 0x50)
    variants = _offset_variants(ml, ro, po, co)

    # 第一遍：收集所有「指向合法实例（vtable 在模块内）」的全局指针 (gaddr, obj)。
    # 对象本身可在堆上（模块外），因此不要求 obj 落在模块映像内。
    instances: List[Tuple[int, int]] = []
    addr = base + data[1]
    end = addr + data[2]
    diag["data_scanned"] = data[2]
    chunk = 1024 * 1024
    while addr < end:
        buf = reader.read(addr, min(chunk, end - addr))
        if not buf:
            break
        n = len(buf) - 8
        off = 0
        while off < n:
            obj = struct.unpack("<Q", buf[off:off + 8])[0]
            if _is_plausible_ptr(obj):
                diag["object_globals"] += 1
                gaddr = addr + off
                if _is_valid_instance(reader, obj, text_lo, text_hi, rdata_lo, rdata_hi):
                    diag["valid_instances"] += 1
                    instances.append((gaddr, obj))
            off += 8
        addr += len(buf)

    # 第二遍：按「变体优先」顺序（config 精确值排第一）对全部候选实例做链路校验。
    # 注意循环顺序：外层变体、内层实例——确保精确偏移组合优先于宽松组合，
    # 避免宽松组合在别的全局对象上产生假阳性（曾误报 0x1ea8000）。
    def _semantic_ok(gaddr: int, a: int, b: int) -> bool:
        """语义门槛：用该候选 RVA + 偏移构造 GodotReader，必须能定位到 Game 节点。"""
        try:
            from .godot_reader import GodotReader
            o = dict(offsets)
            o.update({"os_singleton_rva": gaddr - base,
                      "os_main_loop_off": a, "scenetree_root_off": b})
            gr = GodotReader(reader, o)
            return gr.find_game_node() is not None
        except Exception:
            return False

    for (a, b, p, c) in variants:
        for gaddr, obj in instances:
            if _validate_os_chain(reader, obj, text_lo, text_hi, rdata_lo, rdata_hi,
                                  a, b, p, c):
                if not _semantic_ok(gaddr, a, b):
                    continue  # 形态巧合，非真 OS 单例
                rva = gaddr - base
                diag["candidates"].append({"rva": hex(rva), "variant": (hex(a), hex(b), hex(p), hex(c))})
                if diag["variant_used"] is None:
                    diag["variant_used"] = (hex(a), hex(b), hex(p), hex(c))
                return rva, diag
    return None, diag


# ---------------------------------------------------------------------------
# 对外 API
# ---------------------------------------------------------------------------

def discover_os_singleton_rva(reader: MemoryReader, offsets: Optional[dict] = None,
                              diag: bool = False):
    """自动定位 OS::singleton 的 RVA（免手动）。返回 RVA 或 None；diag=True 时返回 (rva, 诊断dict)。"""
    offs = dict(GODOT_OFFSETS)
    if offsets:
        offs.update(offsets)
    rva, d = _scan_os_singleton(reader, offs)
    global last_diag
    last_diag = d
    if diag:
        return rva, d
    return rva


def read_game_members(reader: MemoryReader, rva: int,
                      child_index: int = -1) -> List[Optional[int]]:
    """读 Game 单例的 GDScript 成员整数列表（用于自动匹配下标）。

    首选按脚本路径 res://Core/Game.gd BFS 定位 Game 节点（稳健）；
    child_index >= 0 时作为兜底强制走固定下标。
    """
    offs = dict(GODOT_OFFSETS)
    offs["os_singleton_rva"] = rva
    if child_index is not None and child_index >= 0:
        offs["game_child_index"] = child_index
    gr = GodotReader(reader, offs)
    node = gr.get_game_node()
    if not node:
        return []
    return gr.read_members(node)


def find_game_node_addr(reader: MemoryReader, rva: int) -> Optional[int]:
    """返回 Game 自动载入节点地址（诊断用）。"""
    offs = dict(GODOT_OFFSETS)
    offs["os_singleton_rva"] = rva
    return GodotReader(reader, offs).find_game_node()


def match_member_indices(members: List[Optional[int]], gold: int, hp: int, round_: int) -> Dict[str, int]:
    """根据游戏内当前数值，从成员列表里反推 gold/hp/round 的下标。

    返回 {"gold","hp","round"} 各自的下标；找不到的字段为 -1。
    gold/hp/round 彼此取不同下标以避免冲突。
    平局裁决：round 常有多个候选（值=1 的成员很多），Godot GDScript 的
    成员声明顺序里 round/wins/losses/lives 紧邻成簇（本游戏实测 65/66/67/68），
    因此 round 的多个候选中优先取「离 hp 下标最近」的那个。
    """
    used: set = set()
    out: Dict[str, int] = {"gold": -1, "hp": -1, "round": -1}
    # 先匹配 gold、hp（重复值少，取首个即可）
    for field, value in (("gold", gold), ("hp", hp)):
        best = -1
        for i, v in enumerate(members):
            if v is None:
                continue
            if int(v) == int(value) and i not in used:
                best = i
                break
        out[field] = best
        if best >= 0:
            used.add(best)
    # round：收集全部候选，优先取离 hp 最近的（状态簇启发）
    cands = [i for i, v in enumerate(members)
             if v is not None and int(v) == int(round_) and i not in used]
    if cands:
        if out["hp"] >= 0:
            out["round"] = min(cands, key=lambda i: abs(i - out["hp"]))
        else:
            out["round"] = cands[0]
        used.add(out["round"])
    return out

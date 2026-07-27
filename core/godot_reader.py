"""
Godot 3.6 结构性内存读取器（外置，不修改游戏文件）

为什么需要它
------------
之前用「值差分扫描」定位金币/血量/回合，需要玩家在游戏里反复改变数值来缩小候选，
既麻烦又不可靠（候选可能误命中）。

正确做法（参考逆向解析得到的程序结构）：
  * 游戏把全局状态放在一个名为 `Game` 的 Autoload 单例上（见 extracted/project.binary 的
    autoload 段：`autoload/Game`）。Autoload 是场景树根节点下名字固定的子节点。
  * Godot 的 SceneTree 可从引擎全局 `OS::get_singleton()->get_main_loop()` 稳定定位
    （该全局指针在二进制 data 段，相对模块基址的偏移 RVA 在每次安装中固定）。
  * 因此每条会话都能从「模块基址 + 固定 RVA」找到 OS 单例 → SceneTree 根 → Game 单例，
    再按成员索引直接读取 gold/hp/round，无需扫描、无需手动校准。

所有偏移/索引都集中在 GODOT_OFFSETS，且可被 config.yaml 的 `godot:` 段覆盖，
方便用 tools/probe_godot.py 一次性标定后长期使用。
"""
from __future__ import annotations

import logging
import struct
from typing import Dict, List, Optional

from .memory_reader import MemoryReader

logger = logging.getLogger(__name__)

# Godot 3.6 (x64) 关键类型布局。下列值已用运行进程实测校正（Backpack Battles）。
GODOT_OFFSETS = {
    # --- OS 单例锚点 ---
    # OS::get_singleton() 返回的全局变量相对模块基址的偏移（RVA）。
    # 0 表示尚未标定，需要 probe_godot.py 一次性找出后写入 config。
    "os_singleton_rva": 0,

    # OS 对象中 main_loop (SceneTree*) 成员的偏移（实测 0x1d0）
    "os_main_loop_off": 0x1D0,
    # SceneTree 中 root (Viewport*) 成员的偏移。
    # 实测 0x148 = 真 root Viewport（name='root'，子节点 = 18 个 autoload + Main）。
    # 0x230 是 current_scene（如 'Main'），早期误当 root 导致找不到 Game。
    "scenetree_root_off": 0x148,

    # --- Node 结构 ---
    # Object 中 script_instance (ScriptInstance*) 成员的偏移（实测 0x58）
    "object_script_instance_off": 0x58,
    # Node 中 parent (Node*) 成员的偏移（实测 0xf0；0x8 是误判，真 root 的 0x8 非零）
    "node_parent_off": 0xF0,
    # Node 中 children —— Godot 3.x 里是 Vector<Node*>(CowData)，实测在 0x108。
    # 注意：0x6c0 是 Viewport 的「画布项扁平列表」(canvas items)，不是节点子表，
    # 早期误用 0x6c0 导致找不到 Game 自动载入节点。
    "node_children_off": 0x108,
    # Node.name (StringName) 字段偏移（实测 0x130）；StringName->_Data->String 偏移见下
    "node_name_off": 0x130,
    # StringName._Data 内 String 的偏移（实测 0x10）
    "stringname_data_str_off": 0x10,
    # GDScriptInstance.script (Ref<GDScript>) 偏移；GDScript 对象里含资源路径 String
    "gdscript_script_off": 0x10,

    # --- GDScriptInstance 结构 ---
    # GDScriptInstance.owner (Object*) 偏移 = +8（vtable 占 +0）
    # GDScriptInstance.members (Vector<Variant>) 偏移（实测 0x20）
    "gdscript_members_off": 0x20,
    # Variant 在 x64 下的大小（type 4B + 填充 + union 16B = 24B）
    "variant_size": 24,
    # Vector<T>/CowData 的元素个数存放在 _ptr - 4（uint32），引用计数在 _ptr - 8。
    # 这是 Godot 3.x 的正确约定；早期误以为 size 在 _ptr+8，导致成员读成垃圾/0。
    "cowdata_size_back_off": 4,

    # --- Game 单例定位 ---
    # 首选：按脚本资源路径 BFS 定位 Game 自动载入节点（稳健，无需下标）。
    "game_script_path": "res://Core/Game.gd",
    "game_node_name": "Game",
    "bfs_max_depth": 6,
    # 兜底：root.children 里 Game 单例的子节点下标（实测 =8；BFS 失败时用）
    "game_child_index": 8,

    # --- Node2D / CanvasItem 变换（2026-07-26 活体实测）---
    # Node2D 局部 position (Vector2, 2×float32) 偏移；全局变换 origin 在 0x260。
    # 验证：Player/Inventory local=(50,60)，Stone local=(170,420) → 格(1,4)，
    #       储物箱内被抛掷物品 local≠global（有旋转），其余 local==global。
    "node2d_pos_off": 0x270,
    "node2d_global_pos_off": 0x260,
    # Node2D.rotation (float32)，紧随 position 之后。占多格物品靠它旋转占格。
    "node2d_rot_off": 0x278,
    # 背包格子边长（像素，Inventory TileMap 实测 80）
    "inv_cell_px": 80,

    # --- 成员索引（GDScriptInstance.members 向量里 gold/hp/round 的下标）---
    # 2026-07-26 活体标定（金币13/生命5/回合1，PID 2912）：
    #   [72]=gold(13)  [68]=hp/lives(5)  [65]=round(1，紧邻 66/67 胜负计数簇)
    "member_gold": 72,
    "member_hp": 68,
    "member_round": 65,
}


class GodotReader:
    """通过 Godot SceneTree 结构性读取 Game 单例上的数值。"""

    def __init__(self, reader: MemoryReader, offsets: Optional[dict] = None):
        self.reader = reader
        self.off = dict(GODOT_OFFSETS)
        if offsets:
            self.off.update(offsets)
        self._root_cache: Optional[int] = None

    # ---------------- 基础读写 ----------------
    def _ptr(self, addr: int) -> Optional[int]:
        if not addr:
            return None
        return self.reader.read_int64(addr)

    def _read_int(self, addr: int, size: int = 4) -> Optional[int]:
        data = self.reader.read(addr, size)
        if not data or len(data) < size:
            return None
        if size == 4:
            return struct.unpack("<i", data)[0]
        return struct.unpack("<q", data)[0]

    def _read_double(self, addr: int) -> Optional[float]:
        data = self.reader.read(addr, 8)
        if not data:
            return None
        return struct.unpack("<d", data)[0]

    def module_base(self) -> int:
        """返回主模块（游戏 exe）基址。"""
        return getattr(self.reader, "module_base", 0) or 0

    # ---------------- 锚点定位 ----------------
    def os_singleton_addr(self) -> Optional[int]:
        rva = self.off.get("os_singleton_rva", 0)
        if not rva:
            return None
        return self.module_base() + rva

    def get_root(self) -> Optional[int]:
        """从 OS 单例定位 SceneTree 根节点（Viewport*）。"""
        if self._root_cache:
            return self._root_cache
        os_addr = self.os_singleton_addr()
        if not os_addr:
            return None
        os_obj = self._ptr(os_addr)
        if not os_obj:
            return None
        main_loop = self._ptr(os_obj + self.off["os_main_loop_off"])
        if not main_loop:
            return None
        root = self._ptr(main_loop + self.off["scenetree_root_off"])
        if not root:
            return None
        self._root_cache = root
        return root

    # ---------------- CowData / 字符串工具 ----------------
    def _cow_count(self, ptr: Optional[int]) -> Optional[int]:
        """CowData：元素个数存放在 _ptr - cowdata_size_back_off（uint32）。"""
        if not ptr or ptr < 0x10000:
            return None
        return self._read_int(ptr - self.off["cowdata_size_back_off"], 4)

    def _read_godot_string(self, ptr: Optional[int]) -> Optional[str]:
        """读取 Godot String（CowData<CharType>）。Windows 上按 UTF-16 优先，回退 UTF-32。"""
        if not ptr or ptr < 0x10000:
            return None
        n = self._cow_count(ptr)
        if n is None or n <= 0 or n > 1024:
            return None
        for width, enc in ((2, "utf-16-le"), (4, "utf-32-le")):
            raw = self.reader.read(ptr, n * width)
            if not raw or len(raw) < n * width:
                continue
            try:
                s = raw.decode(enc)
            except Exception:  # noqa: BLE001
                continue
            s = s.split("\x00", 1)[0]
            if s:
                return s
        return None

    # ---------------- 节点遍历 ----------------
    def get_children(self, node: int) -> List[int]:
        """读取 Node 的全部子节点（Vector<Node*> = CowData 连续数组）。"""
        if not node:
            return []
        vec_ptr = self._ptr(node + self.off["node_children_off"])
        cnt = self._cow_count(vec_ptr)
        if not vec_ptr or cnt is None or cnt <= 0 or cnt > 5000:
            return []
        out: List[int] = []
        for i in range(cnt):
            c = self._ptr(vec_ptr + i * 8)
            if c and c > 0x10000:
                out.append(c)
        return out

    def get_child(self, node: int, index: int) -> Optional[int]:
        kids = self.get_children(node)
        if 0 <= index < len(kids):
            return kids[index]
        return None

    def node_name(self, node: int) -> Optional[str]:
        """读取节点名（StringName -> _Data -> String）。"""
        if not node:
            return None
        data = self._ptr(node + self.off["node_name_off"])
        if not data:
            return None
        strptr = self._ptr(data + self.off["stringname_data_str_off"])
        return self._read_godot_string(strptr)

    def node_script_path(self, node: int) -> Optional[str]:
        """读取节点所挂 GDScript 的资源路径（res://...gd）。"""
        si = self._script_instance(node)
        if not si:
            return None
        script = self._ptr(si + self.off["gdscript_script_off"])
        if not script:
            return None
        # 在 script 对象前若干字节里找指向 res://...gd 字符串的指针
        for off in range(0, 0x200, 8):
            p = self._ptr(script + off)
            if not p:
                continue
            s = self._read_godot_string(p)
            if s and s.startswith("res://") and s.endswith(".gd"):
                return s
        return None

    def node_pos(self, node: int, use_global: bool = False) -> Optional[tuple]:
        """读取 Node2D 的 position（局部或全局变换 origin），返回 (x, y)。"""
        if not node:
            return None
        off = self.off.get("node2d_global_pos_off", 0x260) if use_global \
            else self.off.get("node2d_pos_off", 0x270)
        data = self.reader.read(node + off, 8)
        if not data or len(data) < 8:
            return None
        x, y = struct.unpack("<2f", data)
        # NaN / 离谱值防御
        if x != x or y != y or abs(x) > 1e6 or abs(y) > 1e6:
            return None
        return (x, y)

    def find_node_by_name(self, name: str, max_depth: int = 6,
                          start: Optional[int] = None) -> Optional[int]:
        """从 start（默认 root）BFS 按名字找节点。"""
        root = start or self.get_root()
        if not root:
            return None
        from collections import deque
        dq = deque([(root, 0)])
        seen = {root}
        while dq:
            node, depth = dq.popleft()
            if self.node_name(node) == name:
                return node
            if depth < max_depth:
                for c in self.get_children(node):
                    if c not in seen:
                        seen.add(c)
                        dq.append((c, depth + 1))
        return None

    def find_game_node(self) -> Optional[int]:
        """从 root 起 BFS，按脚本路径/节点名定位 Game 自动载入单例。"""
        root = self.get_root()
        if not root:
            return None
        want_path = self.off.get("game_script_path", "res://Core/Game.gd")
        want_name = self.off.get("game_node_name", "Game")
        max_depth = self.off.get("bfs_max_depth", 6)
        from collections import deque
        dq = deque([(root, 0)])
        seen = {root}
        while dq:
            node, depth = dq.popleft()
            sp = self.node_script_path(node)
            if sp and sp == want_path:
                return node
            if want_name and self.node_name(node) == want_name and sp is None:
                # 名字匹配但无脚本时也接受（少见）
                return node
            if depth < max_depth:
                for c in self.get_children(node):
                    if c not in seen:
                        seen.add(c)
                        dq.append((c, depth + 1))
        return None

    def get_game_node(self) -> Optional[int]:
        # 首选 BFS 按脚本路径定位；失败再回退到固定下标（若已标定）。
        node = self.find_game_node()
        if node:
            return node
        idx = self.off.get("game_child_index", -1)
        if idx is not None and idx >= 0:
            root = self.get_root()
            if root:
                return self.get_child(root, idx)
        return None

    # ---------------- GDScript 成员读取 ----------------
    def _script_instance(self, node: int) -> Optional[int]:
        if not node:
            return None
        return self._ptr(node + self.off["object_script_instance_off"])

    def read_members(self, node: int) -> List[Optional[int]]:
        """读取 GDScriptInstance.members 向量里的所有整数/实数成员。"""
        si = self._script_instance(node)
        if not si:
            return []
        mptr = self._ptr(si + self.off["gdscript_members_off"])
        msize = self._cow_count(mptr)
        if not mptr or msize is None or msize <= 0 or msize > 10000:
            return []
        vsize = self.off["variant_size"]
        out: List[Optional[int]] = []
        for i in range(msize):
            out.append(self._read_variant_int(mptr + i * vsize))
        return out

    def _read_variant_int(self, addr: int) -> Optional[int]:
        """从 Variant 读取整数/实数值。"""
        vtype = self._read_int(addr, 4)
        if vtype is None:
            return None
        if vtype == 2:  # INT -> 联合体里是 int64
            return self._read_int(addr + 8, 8)
        if vtype == 3:  # REAL -> double
            d = self._read_double(addr + 8)
            return int(d) if d is not None else None
        return None

    def read_member(self, node: int, index: int) -> Optional[int]:
        if index < 0:
            return None
        si = self._script_instance(node)
        if not si:
            return None
        mptr = self._ptr(si + self.off["gdscript_members_off"])
        msize = self._cow_count(mptr)
        if not mptr or msize is None or index >= msize:
            return None
        return self._read_variant_int(mptr + index * self.off["variant_size"])

    # ---------------- 高层 API ----------------
    def read_stats(self) -> Dict[str, Optional[int]]:
        """读取 gold/hp/round。未标定的字段返回 None。"""
        node = self.get_game_node()
        if not node:
            return {"gold": None, "hp": None, "round": None}
        return {
            "gold": self.read_member(node, self.off["member_gold"]),
            "hp": self.read_member(node, self.off["member_hp"]),
            "round": self.read_member(node, self.off["member_round"]),
        }

    def is_ready(self) -> bool:
        return self.os_singleton_addr() is not None

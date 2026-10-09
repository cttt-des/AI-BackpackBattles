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
import math
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
    # 2026-09-29 活体标定（curClass=2/Berserker，PID 16892）：
    #   Game.gd 成员声明序（var 序，0 起）：curRound=65 / gold=72 / curClass=83
    "member_cur_class": 83,

    # --- Util.rng 定位（docs/rng_truth.md §2 / §5）---
    # Util 是 autoload 列表第 2 个（project.godot:470，0 起下标 =1）；
    # 稳健法：BFS 按脚本路径匹配，节点名/固定下标做兜底。
    "util_script_path": "res://Utility/Util.gd",
    "util_node_name": "Util",
    "util_child_index": 1,
    # rng 的成员槽位 = Util.gd 顶层 var 声明序下标 3：
    #   frameCounter=0(:3) time=1(:4) clockTime=2(:5) rng=3(:6)
    "rng_member_slot": 3,
    # RandomNumberGenerator 对象内 seed/state 双 u64 的偏移：
    #   静态推导为 +0xE0/+0xE8/+0xF0（§2.3），但 2026-10-04 活体标定
    #   （tools/probe_rng_state.py，PID 7996，LCG 不变式 + 20 组差分全命中）
    #   实测 randbase 起点 = +0xE8（比静态推导多 8B 对齐）：
    #   +0xE8 pcg.state（重放唯一所需）  +0xF0 pcg.inc  +0xF8 current_seed
    # 读取时仍经 LCG 不变式活体校验（见 read_rng_state_detail）；校验失败自动
    # 进入 +0x00..scan 上限的 8B 步进扫描标定（§6.1）并更新此处。
    "rng_state_off": 0xE8,
    "rng_inc_off": 0xF0,
    "rng_seed_off": 0xF8,
    "rng_scan_max_off": 0x118,

    # --- Control 全局矩形（read_control_rect，tools/capture_replay.py UI 自动化用）---
    # rect_global_position（Vector2, 2×float32）与 rect_size（Vector2）在 Control
    # 对象内的偏移。标定方法（经验扫描，fail-fast）：在 HistoryButton
    # （Main.tscn TitleScreen/ButtonsNode/HistoryButton，设计矩形
    # (1724,325)-(1889,433)，即 pos=(1724,325) size=(165,108)）对象内存前
    # 0x300 字节以 4B 步进扫描两个 float 对 (x≈1724,y≈325) 与 (w≈165,h≈108)，
    # 再用 ItemLibraryButton（同父 ButtonsNode，(1714,114)-(1892,223)）交叉
    # 验证同一偏移（双按钮同时命中才接受，防单按钮误命中）。
    # 2026-10-05 活体标定（PID 7996，tools/capture_replay.py --probe 实测）：
    #   pos=+0x270 size=+0x278；HistoryButton/ItemLibraryButton 读数与设计
    #   矩形逐位一致，出样 RecipeBookButton (1720,224)+(165,104) 亦吻合
    #   （Main.tscn:12891-12894 设计矩形 (1720,224)-(1885,328)）。
    # 若 0 传入（其他构建偏移漂移），read_control_rect 会自动重新扫描标定。
    "control_rect_pos_off": 0x270,
    "control_rect_size_off": 0x278,
    # rect_rotation（f32，弧度）偏移。标定方法同上（三锚点交叉验证）：
    # 2026-10-05 活体实测（PID 8184）——NextRound=+π/2、PreviousRound=−π/2
    # （BuildHistory.tscn:287/:301 rect_rotation=±90°，内部存弧度）与
    # HistoryButton=0.0 同址命中 +0x2C4。rect_rotation≠0 的按钮
    # （绕 rect_pivot_offset 旋转）其可点击 quad ≠ 裸矩形，点击前必须
    # 变换（tools/capture_replay.py click_control_center）。
    "control_rect_rot_off": 0x2C4,
    # 经验扫描窗口（对象前 N 字节）与 float 对容差（px）
    "control_rect_scan_window": 0x300,
    "control_rect_scan_tol": 3.0,
}

# PCG32 常数（Godot RandomNumberGenerator 底层 RandomPCG，docs/rng_truth.md §2.3）：
# state' = state × 6364136223846793005 + 2885390081777926815 (mod 2^64)；
# inc 在 randomize() 后恒为默认值，可作 rng 对象识别的强校验。
PCG_MULT = 6364136223846793005
PCG_INC = 2885390081777926815
PCG_MOD = 1 << 64


def pcg_next(state: int) -> int:
    """PCG32 单步前进：state' = state × M + inc (mod 2^64)。"""
    return (state * PCG_MULT + PCG_INC) % PCG_MOD


def pcg_match_forward(s0: int, s1: int, max_steps: int = 1 << 20) -> Optional[int]:
    """s0 沿 LCG 前进多少步恰好到达 s1；超限未命中返回 None。

    用途（docs/rng_truth.md §6.1 差分标定）：两次采样之间无论游戏消耗了
    多少步 rng，只要能找到步数 k，就证明两次读到的是同一条 PCG 链的
    pcg.state 字段（而非垃圾或别的对象）。
    """
    s = s0 % PCG_MOD
    s1 %= PCG_MOD
    for k in range(1, max_steps + 1):
        s = (s * PCG_MULT + PCG_INC) % PCG_MOD
        if s == s1:
            return k
    return None

# Game.Classes 枚举（Game.gd:131）：职业下标 → 名称
GAME_CLASSES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer"}


class GodotReader:
    """通过 Godot SceneTree 结构性读取 Game 单例上的数值。"""

    def __init__(self, reader: MemoryReader, offsets: Optional[dict] = None):
        self.reader = reader
        self.off = dict(GODOT_OFFSETS)
        if offsets:
            self.off.update(offsets)
        self._root_cache: Optional[int] = None
        # Util autoload 节点缓存（全程存活，无需失效逻辑）
        self._util_cache: Optional[int] = None
        # 脚本路径缓存（节点地址→脚本路径），场景树不变时避免重复 0x200 扫描
        self._script_path_cache: Dict[int, Optional[str]] = {}

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
        """读取节点所挂 GDScript 的资源路径（res://...gd），带缓存。

        缓存策略：仅在找到有效路径时缓存。None 不缓存，因为读取失败可能
        是瞬时性的（场景加载中），缓存 None 会导致后续轮询永久拿不到物品。
        """
        if not node:
            return None
        # 有效路径缓存命中
        cached = self._script_path_cache.get(node)
        if cached is not None:
            return cached

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
                self._script_path_cache[node] = s
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

    def invalidate_script_cache(self):
        """场景树结构变化时清除脚本路径缓存。"""
        self._script_path_cache.clear()

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

    # ---------------- Util.rng 读取（docs/rng_truth.md §2 / §5）----------------
    def find_util_node(self) -> Optional[int]:
        """从 root BFS 按脚本路径 res://Utility/Util.gd 定位 Util autoload 节点。

        与 find_game_node 同款模式（§2.1）；节点名 Util 做二次确认，BFS 失败
        再回退 root.children[util_child_index]（autoload 列表第 2 个，下标 1）。
        Util 节点全程存活，找到后缓存。
        """
        if self._util_cache:
            return self._util_cache
        root = self.get_root()
        if not root:
            return None
        want_path = self.off.get("util_script_path", "res://Utility/Util.gd")
        want_name = self.off.get("util_node_name", "Util")
        from collections import deque
        dq = deque([(root, 0)])
        seen = {root}
        fallback = None
        while dq:
            node, depth = dq.popleft()
            sp = self.node_script_path(node)
            if sp and sp == want_path:
                self._util_cache = node
                return node
            # 兜底候选：名字匹配（不缓存，等脚本路径命中或最终回退）
            if fallback is None and want_name and self.node_name(node) == want_name:
                fallback = node
            if depth < self.off.get("bfs_max_depth", 6):
                for c in self.get_children(node):
                    if c not in seen:
                        seen.add(c)
                        dq.append((c, depth + 1))
        if fallback:
            return fallback
        # 最后回退：root.children 下标 1（18 个 autoload 的第 2 个）
        idx = self.off.get("util_child_index", 1)
        node = self.get_child(root, idx) if idx >= 0 else None
        if node and self.node_name(node) == want_name:
            self._util_cache = node
            return node
        return node

    def _read_u64(self, addr: int) -> Optional[int]:
        data = self.reader.read(addr, 8)
        if not data or len(data) < 8:
            return None
        return struct.unpack("<Q", data)[0]

    def _variant_object(self, var_addr: int) -> Optional[int]:
        """Variant(OBJECT) → 对象指针。

        本构建（魔改 Godot）的 OBJECT 槽为「union0=槽地址，真对象=*(union0)」
        的间址布局（combatlog_reader.py 同款，_obj_at），+16 直读兜底。
        """
        slot = self._ptr(var_addr + 8)
        if slot and slot > 0x10000:
            obj = self._ptr(slot)
            if obj and obj > 0x10000:
                return obj
        return self._ptr(var_addr + 16) or None

    def _members_addr(self, node: int) -> Optional[int]:
        si = self._script_instance(node)
        if not si:
            return None
        return self._ptr(si + self.off["gdscript_members_off"])

    def read_rng_state(self, util_node: Optional[int] = None) -> Optional[Dict[str, int]]:
        """读取 Util.rng 的 {seed, state}（docs/rng_truth.md §5 定位路径）。

        state = pcg.state（+0xE0）——确定性重放唯一所需；
        seed  = current_seed（+0xF0）——上一次 rand 前进前的 pcg.state。
        读取经 LCG 不变式活体校验（state == seed×M + inc），失败自动扫描
        标定；仍失败返回 None（fail-fast，不猜值）。
        """
        d = self.read_rng_state_detail(util_node)
        if not d:
            return None
        return {"seed": d["seed"], "state": d["state"]}

    def read_rng_state_detail(self, util_node: Optional[int] = None) -> Optional[dict]:
        """read_rng_state 的诊断版：附 rng 对象地址/偏移/校验模式。"""
        node = util_node or self.find_util_node()
        if not node:
            logger.warning("read_rng_state: 未找到 Util autoload 节点")
            return None
        ma = self._members_addr(node)
        if not ma:
            logger.warning("read_rng_state: Util 节点 script_instance/members 不可读")
            return None
        slot = self.off.get("rng_member_slot", 3)
        cnt = self._cow_count(ma)
        if cnt is None or slot >= cnt:
            logger.warning("read_rng_state: members 槽 %s 越界（count=%s）", slot, cnt)
            return None
        va = ma + slot * self.off["variant_size"]
        vtype = self._read_int(va, 4)
        if vtype != 17:
            logger.warning("read_rng_state: members[%s] type=%s（预期 17 OBJECT）",
                           slot, vtype)
            return None
        obj = self._variant_object(va)
        if not obj:
            logger.warning("read_rng_state: members[%s] OBJECT 指针不可读", slot)
            return None
        d = self._read_rng_object(obj)
        if d:
            return d
        # 配置偏移未通过校验 → §6.1 扫描标定（命中后写回 self.off 长期生效）
        d = self._calibrate_rng_object(obj)
        if not d:
            logger.warning("read_rng_state: rng 对象 %#x 上扫描标定失败 "
                           "（LCG 不变式无命中——刚播种未消耗？）", obj)
        return d

    def _read_rng_object(self, obj: int) -> Optional[dict]:
        """按当前配置偏移读 rng 对象并做 LCG 不变式校验。

        校验（docs/rng_truth.md §6.1，误报率≈0）：
          lcg   —— inc==PCG_INC 且 state == current_seed×M + inc
                   （rand() 先存 current_seed=前进前 state 再前进，§2.3）
          fresh —— inc==PCG_INC 且 state == current_seed
                   （set_seed 后尚未消耗任何 rand 的边界）
        """
        so = self.off.get("rng_state_off", 0)
        io = self.off.get("rng_inc_off", 0)
        fo = self.off.get("rng_seed_off", 0)
        if not (so and io and fo):
            return None
        state = self._read_u64(obj + so)
        inc = self._read_u64(obj + io)
        seed = self._read_u64(obj + fo)
        if state is None or inc is None or seed is None:
            return None
        if inc != PCG_INC:
            return None
        if state == (seed * PCG_MULT + PCG_INC) % PCG_MOD:
            mode = "lcg"
        elif state == seed:
            mode = "fresh_seed"
        else:
            return None
        return {"obj": obj, "state": state, "inc": inc, "seed": seed,
                "state_off": so, "seed_off": fo, "mode": mode}

    def _calibrate_rng_object(self, obj: int) -> Optional[dict]:
        """在 rng 对象 +0x00..rng_scan_max_off 以 8B 步进扫描标定（§6.1）。

        不变式：u64[off]==state, u64[off+8]==inc, u64[off+16]==current_seed
        满足 inc==PCG_INC 且 state == current_seed×M + inc。命中即更新
        self.off（本会话内长期生效；如需跨会话请写 config.yaml godot 段）。
        """
        limit = self.off.get("rng_scan_max_off", 0x118)
        for off in range(0, limit + 1, 8):
            a = self._read_u64(obj + off)
            b = self._read_u64(obj + off + 8)
            c = self._read_u64(obj + off + 16)
            if a is None or b is None or c is None:
                continue
            if b == PCG_INC and a == (c * PCG_MULT + PCG_INC) % PCG_MOD:
                logger.warning(
                    "rng 偏移标定命中：state=+0x%X inc=+0x%X seed=+0x%X "
                    "（静态推导 0xE0 被修正，请回填 config.yaml godot 段）",
                    off, off + 8, off + 16)
                self.off["rng_state_off"] = off
                self.off["rng_inc_off"] = off + 8
                self.off["rng_seed_off"] = off + 16
                return {"obj": obj, "state": a, "inc": b, "seed": c,
                        "state_off": off, "seed_off": off + 16, "mode": "scan"}
        return None

    # ---------------- Control 全局矩形（capture_replay UI 自动化用）----------------
    def child_by_name(self, node: int, name: str) -> Optional[int]:
        """按名字取直接子节点；无则返回 None。"""
        if not node:
            return None
        for c in self.get_children(node):
            if self.node_name(c) == name:
                return c
        return None

    def find_main_node(self) -> Optional[int]:
        """定位 Main 场景根节点（Main.tscn:9677 [node name="Main"]）。

        root 子节点 = 18 个 autoload + Main（本文件头注释），故在 root 的
        直接子节点里按名字找；找不到再试 current_scene（0x230，历史标定旁证）。
        """
        root = self.get_root()
        if not root:
            return None
        main = self.child_by_name(root, "Main")
        if main:
            return main
        cur = self._ptr(root + 0x230)
        if cur and cur > 0x10000 and self.node_name(cur) == "Main":
            return cur
        return None

    def find_control_node(self, path: List[str],
                          start: Optional[int] = None) -> Optional[int]:
        """从 Main（或 start）按节点名路径逐级下钻，定位 Control 节点。

        例：["TitleScreen", "ButtonsNode", "HistoryButton"]
        对应 Main.tscn 的 parent 链。任一级缺失返回 None（fail-fast）。
        """
        node = start or self.find_main_node()
        if not node:
            return None
        for name in path:
            node = self.child_by_name(node, name)
            if not node:
                return None
        return node

    @staticmethod
    def _unpack_f32_pair(raw: Optional[bytes]) -> Optional[tuple]:
        if not raw or len(raw) < 8:
            return None
        a, b = struct.unpack("<2f", raw[:8])
        # NaN / 离谱值防御（NaN != NaN）
        if a != a or b != b or abs(a) > 1e6 or abs(b) > 1e6:
            return None
        return (a, b)

    def _calibrate_control_rect_offsets(self) -> Optional[tuple]:
        """经验扫描标定 Control 的 pos/size 偏移（GODOT_OFFSETS 注释中的方法）。

        主锚点 = HistoryButton（设计矩形 (1724,325)-(1889,433)），在其对象前
        control_rect_scan_window 字节内找 (x≈1724,y≈325) 与 (w≈165,h≈108) 的
        float 对；候选再用 ItemLibraryButton ((1714,114)-(1892,223)) 交叉验证
        （同一偏移必须对两个按钮都命中）。命中后回填 self.off 与模块级
        GODOT_OFFSETS。失败返回 None（fail-fast，不猜偏移）。
        """
        main = self.find_main_node()
        if not main:
            logger.warning("control_rect 标定: 未找到 Main 节点")
            return None
        # (节点路径, (pos_x, pos_y, size_w, size_h)) —— Main.tscn:12904-12958 设计矩形
        anchors = (
            (("TitleScreen", "ButtonsNode", "HistoryButton"),
             (1724.0, 325.0, 165.0, 108.0)),
            (("TitleScreen", "ButtonsNode", "ItemLibraryButton"),
             (1714.0, 114.0, 178.0, 109.0)),
        )
        nodes = []
        for path, _ in anchors:
            n = self.find_control_node(list(path), start=main)
            if not n:
                logger.warning("control_rect 标定: 未找到节点 %s", "/".join(path))
                return None
            nodes.append(n)
        (ax, ay, aw, ah), (bx, by, bw, bh2) = anchors[0][1], anchors[1][1]
        win = self.off.get("control_rect_scan_window", 0x300)
        tol = self.off.get("control_rect_scan_tol", 3.0)

        def scan_candidates(node, want):
            """在 node 前 win 字节以 4B 步进找 (≈want[0],≈want[1]) float 对。"""
            data = self.reader.read(node, win)
            if not data or len(data) < win:
                return []
            out = []
            for off in range(0, win - 8, 4):
                pair = self._unpack_f32_pair(data[off:off + 8])
                if pair and abs(pair[0] - want[0]) <= tol \
                        and abs(pair[1] - want[1]) <= tol:
                    out.append(off)
            return out

        pos_cands = scan_candidates(nodes[0], (ax, ay))
        size_cands = scan_candidates(nodes[0], (aw, ah))

        def cross_ok(node, off, want):
            d = self.reader.read(node + off, 8)
            pair = self._unpack_f32_pair(d)
            return bool(pair and abs(pair[0] - want[0]) <= tol
                        and abs(pair[1] - want[1]) <= tol)

        # 交叉验证：同一偏移在 ItemLibraryButton 上也必须命中其设计矩形
        pos_off = next((o for o in pos_cands
                        if cross_ok(nodes[1], o, (bx, by))), None)
        size_off = next((o for o in size_cands
                         if cross_ok(nodes[1], o, (bw, bh2))), None)
        if pos_off is None or size_off is None:
            logger.warning("control_rect 标定失败: pos 候选=%s size 候选=%s "
                           "（交叉验证无命中）", pos_cands, size_cands)
            return None
        for target in (self.off, GODOT_OFFSETS):
            target["control_rect_pos_off"] = pos_off
            target["control_rect_size_off"] = size_off
        logger.warning("control_rect 偏移标定命中（经验扫描+交叉验证，请回填 "
                       "GODOT_OFFSETS）: pos=+0x%X size=+0x%X", pos_off, size_off)
        return (pos_off, size_off)

    def read_control_rect(self, node: int) -> Optional[tuple]:
        """读 Control 节点的全局矩形，返回 ((x, y), (w, h))。

        对应 Godot 3.6 Control 的 rect_global_position / rect_size；偏移用
        GODOT_OFFSETS 的 control_rect_pos_off / control_rect_size_off，
        未标定（=0）时先经 _calibrate_control_rect_offsets() 经验扫描标定。
        任一步失败返回 None（fail-fast，调用方不得拿猜值点击）。
        """
        if not node:
            return None
        po = self.off.get("control_rect_pos_off") or 0
        so = self.off.get("control_rect_size_off") or 0
        if not (po and so):
            cal = self._calibrate_control_rect_offsets()
            if not cal:
                return None
            po, so = cal
        pos = self._unpack_f32_pair(self.reader.read(node + po, 8))
        size = self._unpack_f32_pair(self.reader.read(node + so, 8))
        if not pos or not size or size[0] <= 0 or size[1] <= 0:
            return None
        return (pos, size)

    def read_control_rotation(self, node: int) -> Optional[float]:
        """读 Control 节点的 rect_rotation，返回角度制（度）。

        内部存弧度（f32 @ control_rect_rot_off，标定见 GODOT_OFFSETS 注释）。
        读取失败返回 None（调用方按 0 处理并告警——rect_rotation=0 的按钮
        占绝大多数，但旋转按钮点击前必须已知角度）。
        """
        if not node:
            return None
        ro = self.off.get("control_rect_rot_off") or 0
        if not ro:
            return None
        data = self.reader.read(node + ro, 4)
        if not data or len(data) < 4:
            return None
        rad = struct.unpack("<f", data)[0]
        if rad != rad or abs(rad) > 100.0:   # NaN/离谱值防御
            return None
        return math.degrees(rad)

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

    def read_character(self) -> Optional[str]:
        """读取当前职业名（Game.curClass → Classes 枚举名）。未标定/异常返回 None。"""
        node = self.get_game_node()
        if not node:
            return None
        idx = self.read_member(node, self.off.get("member_cur_class", -1))
        if idx is None:
            return None
        return GAME_CLASSES.get(idx)

    def is_ready(self) -> bool:
        return self.os_singleton_addr() is not None

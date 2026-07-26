"""
一次性标定诊断工具（游戏必须正在运行）。

绝大多数情况下无需手动使用本脚本——程序启动时会自动标定（见 core/godot_probe）。
本脚本保留用于排错：直观看到 OS::singleton 的 RVA、Game 单例成员 dump，并可写回 config。

用法：
  python tools/probe_godot.py                       # 自动定位 RVA + dump Game 成员
  python tools/probe_godot.py --write-config        # 把推断的 os_singleton_rva 写回 config.yaml
  python tools/probe_godot.py --gold 100 --hp 50 --round 3 --write-config
                                                    # 同时自动匹配并写回成员下标
  python tools/probe_godot.py --pid 1234            # 指定进程 PID（否则按窗口标题自动找）

原理（参考逆向结构，正向链路校验）：
  OS::singleton 全局 -> OS 实例 -> OS.main_loop (SceneTree) -> SceneTree.root (根视口)
    -> root.children[game_child_index] = Game 单例 -> 读其 GDScript 成员整数。
不依赖任何字符串/虚函数名，对各 Godot 3.x 构建稳健。
"""
import argparse
import re
import sys
from pathlib import Path
from typing import Optional

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.window_manager import WindowManager
from core.memory_reader import MemoryReader
from core.godot_reader import GODOT_OFFSETS
from core.godot_probe import (
    discover_os_singleton_rva, read_game_members, match_member_indices,
    find_game_node_addr,
)
from core.paths import get_config_path


def find_process() -> Optional[int]:
    wm = WindowManager()
    if not wm.refresh():
        print("ERROR: 未找到 'Backpack Battles' 窗口，请先启动游戏。")
        return None
    return wm.window.pid


def write_config(rva: int, members: Optional[dict] = None):
    """写回 config.yaml 的 godot 段（保留注释，仅替换对应行）。"""
    path = get_config_path()
    text = path.read_text(encoding="utf-8")
    text, n = re.subn(r"^(\s*os_singleton_rva:\s*).*$",
                      lambda m: f"{m.group(1)}{hex(rva)}", text, count=1, flags=re.M)
    if n == 0:
        text = text.rstrip() + f"\n  os_singleton_rva: {hex(rva)}\n"
    if members:
        for key, val in members.items():
            if val is None or val < 0:
                continue
            text, _ = re.subn(rf"^(\s*{key}:\s*).*$",
                              lambda m, v=val: f"{m.group(1)}{v}", text, count=1, flags=re.M)
    path.write_text(text, encoding="utf-8")
    print(f"[+] 已写入 config.yaml: os_singleton_rva={hex(rva)}" +
          (f" 成员={members}" if members else ""))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None, help="指定游戏进程 PID")
    ap.add_argument("--gold", type=int, default=None, help="游戏内当前金币（用于自动匹配成员下标）")
    ap.add_argument("--hp", type=int, default=None, help="游戏内当前生命")
    ap.add_argument("--round", "--round_", dest="round_", type=int, default=None, help="游戏内当前回合")
    ap.add_argument("--rva", type=lambda x: int(x, 0), default=None,
                    help="已知 os_singleton_rva（跳过约80秒的慢速扫描）")
    ap.add_argument("--write-config", action="store_true")
    args = ap.parse_args()

    pid = args.pid or find_process()
    if not pid:
        return 1

    reader = MemoryReader(pid)
    print(f"[*] 模块基址 = {hex(reader.module_base)}")

    if args.rva:
        rva = args.rva
        print(f"[1] 使用指定 os_singleton_rva = {hex(rva)}（跳过扫描）")
    else:
        rva, diag = discover_os_singleton_rva(reader, GODOT_OFFSETS, diag=True)
        print(f"[*] 扫描诊断: {diag}")
        print(f"[1] 推荐 os_singleton_rva = {hex(rva) if rva else 'None'}"
              + (f"  (偏移组合 {diag.get('variant_used')})" if rva else ""))

    if not rva:
        print("[-] 未找到 OS 单例。诊断信息可帮助定位问题（如偏移漂移），"
              "可手动用 Cheat Engine 定位后填入 config.yaml。")
        return 1

    game_addr = find_game_node_addr(reader, rva)
    print(f"[2] Game 节点(按脚本 res://Core/Game.gd 定位) = "
          f"{hex(game_addr) if game_addr else 'None (BFS 未命中)'}")
    members = read_game_members(reader, rva)
    print(f"[2b] Game 成员数 = {len(members)}")
    for i, v in enumerate(members[:60]):
        print(f"      [{i:2d}] = {v}")

    out_members = None
    if None not in (args.gold, args.hp, args.round_):
        idx = match_member_indices(members, args.gold, args.hp, args.round_)
        out_members = idx
        print(f"[3] 成员下标匹配: {idx}")
        print("      （负下标表示该数值在成员里未出现，需手动在面板补校）")

    if args.write_config:
        write_config(rva, out_members)
    else:
        print("\n请把下列内容写入 config.yaml 的 godot: 段（必要时微调 game_child_index 与 member_*）:")
        print(f"  os_singleton_rva: {hex(rva)}")
        if out_members:
            for k in ("member_gold", "member_hp", "member_round"):
                print(f"  {k}: {out_members[k.replace('member_', '')]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

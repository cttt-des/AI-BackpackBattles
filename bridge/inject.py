"""
Backpack Battles 桥接注入器 v2

通过重建游戏 PCK 资源包，注入 bridge.gd GDScript。
桥接脚本在游戏进程内启动 TCP 服务器（端口 19527），
将运行时联动/价格等数据暴露给外部 Python 机器人。

注入方式：备份原 PCK → 解包 → 修改 Main.tscn → 添加 bridge.gd → 重打包

参考 bpb_enhance 的 PCK 补丁方案：https://github.com/bpb-labs/bpb_enhance
"""
from __future__ import annotations

import hashlib
import json
import logging
import os
import shutil
import struct
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple

logger = logging.getLogger("bridge_inject")

# ─── 常量 ───
PCK_MAGIC = b"GDPC"
BRIDGE_RES_PATH = "res://bpb_ai_bridge.gd"
MAIN_TSCN_PATH = "res://Core/Main.tscn"
BACKUP_SUFFIX = ".bak"


# ═══════════════════════════════════════════════════════
# 1. 查找游戏 PCK
# ═══════════════════════════════════════════════════════

def find_game_pck() -> Optional[Path]:
    """通过 Steam 注册表 / ���程 / 默认路径查找游戏 PCK。"""
    # 1) config.yaml 重载
    cfg = _try_load_config()
    if cfg:
        gp = cfg.get("game", {})
        p = gp.get("pck_path") or gp.get("pck")
        if p and Path(p).exists():
            return Path(p)
        chdir = gp.get("chdir") or gp.get("path")
        if chdir:
            cand = Path(chdir) / "BackpackBattles.pck"
            if cand.exists():
                return cand

    # 2) Steam 注册表
    if os.name == "nt":
        try:
            import winreg
            for hive in (winreg.HKEY_LOCAL_MACHINE, winreg.HKEY_CURRENT_USER):
                for key in (r"SOFTWARE\WOW6432Node\Valve\Steam", r"SOFTWARE\Valve\Steam"):
                    try:
                        with winreg.OpenKey(hive, key) as k:
                            sp, _ = winreg.QueryValueEx(k, "InstallPath")
                        found = _find_pck_in_steam_libs(sp)
                        if found: return found[0]
                    except (OSError, FileNotFoundError):
                        continue
        except ImportError:
            pass

    # 3) 常见 Steam 路径
    for base in (Path("C:/Program Files (x86)/Steam"), Path("C:/Program Files/Steam"),
                 Path.home() / ".steam" / "steam"):
        found = _find_pck_in_steam_libs(str(base))
        if found: return found[0]

    # 4) 进程扫描
    try:
        import psutil
        for proc in psutil.process_iter(["name", "exe"]):
            if proc.info.get("name") == "BackpackBattles.exe" and proc.info.get("exe"):
                pck = Path(proc.info["exe"]).parent / "BackpackBattles.pck"
                if pck.exists(): return pck
    except ImportError:
        pass

    return None


def _find_pck_in_steam_libs(steam_root: str) -> List[Path]:
    out = []
    for sub in ("Backpack Battles", "BackpackBattles"):
        pck = Path(steam_root) / "steamapps" / "common" / sub / "BackpackBattles.pck"
        if pck.exists(): out.append(pck)

    lf = Path(steam_root) / "steamapps" / "libraryfolders.vdf"
    if lf.exists():
        try:
            for line in lf.read_text(encoding="utf-8", errors="replace").split("\n"):
                line = line.strip()
                if '"path"' in line:
                    lp = line.split('"')[3] if line.count('"') >= 5 else ""
                    for sub in ("Backpack Battles", "BackpackBattles"):
                        pck = Path(lp.replace("\\\\", "/")) / "steamapps" / "common" / sub / "BackpackBattles.pck"
                        if pck.exists() and pck not in out: out.append(pck)
        except Exception:
            pass
    return out


def _try_load_config() -> dict:
    try:
        import yaml
        for base in (Path("."), Path(__file__).parent.parent):
            p = base / "config.yaml"
            if p.exists():
                with open(p, encoding="utf-8") as f:
                    return yaml.safe_load(f) or {}
    except Exception:
        return {}


# ═══════════════════════════════════════════════════════
# 2. PCK 完整解析 / 重建
# ═══════════════════════════════════════════════════════

def parse_pck(pck_path: Path) -> tuple:
    """完整解析 PCK 文件。

    返回 (header_dict, entries_dict, raw_header, raw_index, raw_data)
    """
    with open(pck_path, "rb") as f:
        all_data = f.read()

    off = 0
    magic = all_data[off:off+4]; off += 4
    assert magic == PCK_MAGIC, f"无效魔数: {magic}"

    pack_ver = struct.unpack("<I", all_data[off:off+4])[0]; off += 4
    major = struct.unpack("<I", all_data[off:off+4])[0]; off += 4
    minor = struct.unpack("<I", all_data[off:off+4])[0]; off += 4
    patch = struct.unpack("<I", all_data[off:off+4])[0]; off += 4
    off += 64  # reserved
    file_count = struct.unpack("<I", all_data[off:off+4])[0]; off += 4

    header = {
        "pack_ver": pack_ver, "major": major, "minor": minor, "patch": patch,
        "file_count": file_count,
    }

    entries: Dict[str, tuple] = {}  # path → (data_offset, size, md5)
    idx_start = off

    for _ in range(file_count):
        path_len = struct.unpack("<I", all_data[off:off+4])[0]; off += 4
        raw_path = all_data[off:off+path_len]; off += path_len
        res_path = raw_path.rstrip(b"\x00").decode("utf-8", errors="replace")
        data_off = struct.unpack("<Q", all_data[off:off+8])[0]; off += 8
        size = struct.unpack("<Q", all_data[off:off+8])[0]; off += 8
        md5 = all_data[off:off+16]; off += 16
        entries[res_path] = (data_off, size, md5)

    raw_header = all_data[:4+4+4+4+4+64+4]
    raw_index = all_data[idx_start:off]

    # 数据区：所有文件数据的范围
    if entries:
        data_start = min(o for o, _, _ in entries.values())
        data_end = max(o + s for o, s, _ in entries.values())
    else:
        data_start, data_end = off, off

    raw_data = all_data[data_start:data_end]

    return header, entries, raw_header, raw_index, raw_data


def read_file(entries: Dict, raw_data: bytes, path: str) -> Optional[bytes]:
    """从解析后的数据中读取指定路径的文件。"""
    e = entries.get(path)
    if not e:
        return None
    data_off, size, _ = e
    # 数据区偏移需要减去 data_start... 但我们有 raw_data 从 data_start 开始
    rel_off = data_off - (min(o for o, _, _ in entries.values()))
    if rel_off < 0 or rel_off + size > len(raw_data):
        # 需要从原始文件再读
        return None
    return raw_data[rel_off:rel_off + size]


def rebuild_pck(entries: Dict[str, tuple], header: dict,
                raw_header: bytes, raw_index: bytes, raw_data: bytes,
                modified_files: Dict[str, bytes],
                new_files: Dict[str, bytes]) -> bytes:
    """重建整个 PCK ��件。

    Args:
        entries: 原索引
        header: 原头部
        raw_header: 原始头部（前 4+4+4+4+4+64+4 字节）
        raw_index: 原始索引
        raw_data: 原始数据区
        modified_files: 需要替换的内容 {path: bytes}
        new_files: 新增的文件 {path: bytes}

    Returns:
        完整的新 PCK 文件 bytes
    """
    # 数据区起始
    data_start = min(o for o, _, _ in entries.values()) if entries else 0

    # 构建所有文件的键列表（保持原顺序，替换/新增追加）
    all_keys = []
    for path in entries:
        if path not in modified_files:
            all_keys.append(path)
    # ���换的文件
    for path in modified_files:
        if path in entries:
            all_keys.append(path)
    # 新增的文件
    for path in new_files:
        if path not in all_keys:
            all_keys.append(path)

    new_file_count = len(all_keys)
    new_entries: List[tuple] = []  # (path, data_bytes, md5)
    cur_off = 0  # data_start 将用作相对 0，但最终偏移需要加上 header+index 长度

    # 先估算 header+index 大小
    est_header_size = len(raw_header)  # 不含 index
    est_index_size = 0
    for path in all_keys:
        path_b = path.encode("utf-8") + b"\x00"
        est_index_size += 4 + len(path_b) + 8 + 8 + 16

    header_index_size = len(raw_header) + est_index_size

    # 实际文件数据偏移
    actual_data_start = header_index_size

    for path in all_keys:
        if path in new_files:
            content = new_files[path]
        elif path in modified_files:
            content = modified_files[path]
        else:
            e = entries[path]
            rel_off = e[0] - data_start
            content = raw_data[rel_off:rel_off + e[1]]
            if len(content) != e[1]:
                logger.warning("文件 %s 读取不完整：期望 %d 字节，实际 %d",
                              path, e[1], len(content))
        md5 = hashlib.md5(content).digest()
        new_entries.append((path, content, md5, len(content)))

    # 构建新索引
    new_index = b""
    off = actual_data_start
    for path, content, md5, size in new_entries:
        path_b = path.encode("utf-8") + b"\x00"
        new_index += struct.pack("<I", len(path_b))
        new_index += path_b
        new_index += struct.pack("<Q", off)
        new_index += struct.pack("<Q", size)
        new_index += md5
        off += size

    # 构建文件头（更新 file_count）
    new_header = bytearray(raw_header)
    # 文件数在 header 尾部 4 字节
    nl = len(new_header)
    struct.pack_into("<I", new_header, nl - 4, new_file_count)

    # 完整文件（用 bytearray 避免 O(n²) 拼接）
    result = bytearray(bytes(new_header) + new_index)
    for _, content, _md5, _size in new_entries:
        result.extend(content)

    return bytes(result)


# ═══════════════════════════════════════════════════════
# 3. Main.tscn 修改
# ═══════════════════════════════════════════════════════

def modify_main_tscn(content: bytes) -> bytes:
    """在 Main.tscn 中添加 BPABridge 节点引用。"""
    import re
    text = content.decode("utf-8", errors="replace")
    lines = text.split("\n")

    if not text.startswith("[gd_scene"):
        logger.warning("Main.tscn 不是标准场景格式，跳过修改")
        return content

    # 1) 解析 ext_resource 找到最大 id
    max_id = 0
    ext_end_idx = 0
    node_start_idx = len(lines)

    for i, line in enumerate(lines):
        m = re.match(r'\[ext_resource.*id=(\d+)', line)
        if m:
            eid = int(m.group(1))
            if eid >= max_id: max_id = eid + 1
            ext_end_idx = i
        if line.startswith("[node") and ext_end_idx > 0 and node_start_idx == len(lines):
            node_start_idx = i

    new_res_id = max_id if max_id >= 1000 else 999

    # 2) 增加 load_steps
    new_lines = []
    for line in lines:
        m = re.match(r'(\[gd_scene.*load_steps=)(\d+)(.*)', line)
        if m:
            old = int(m.group(2))
            line = f"{m.group(1)}{old + 1}{m.group(3)}"
        new_lines.append(line)

    # 3) 在最后一个 ext_resource 之后插入 bridge.gd 引用
    bridge_ext = f'[ext_resource path="{BRIDGE_RES_PATH}" type="Script" id={new_res_id}]'
    new_lines.insert(ext_end_idx + 1, bridge_ext)

    # 4) 在 Main 节点后插入 BPABridge
    main_idx = -1
    for i, line in enumerate(new_lines):
        if re.match(r'\[node name="Main"', line) or re.match(r'\[node name="Main"', line):
            main_idx = i
            break

    if main_idx < 0:
        logger.error("未找到 Main 节点")
        return content

    bridge_node = f'[node name="BPABridge" type="Node" parent="." script={new_res_id}]'
    # 找到 Main 节点的结束（下一个 node 或文件尾）
    insert_at = main_idx + 1
    for i in range(main_idx + 1, len(new_lines)):
        if new_lines[i].startswith("[node") and '"' in new_lines[i]:
            insert_at = i
            break

    new_lines.insert(insert_at, bridge_node)

    return "\n".join(new_lines).encode("utf-8")


def add_autoload_entry(content: bytes) -> bytes:
    """另一种方案：通过修改 project.godot / engine.cfg 添加 autoload。

    但 PCK 里通常没有 project.godot，因此仅作备选。
    """
    return content


# ═══════════════════════════════════════════════════════
# 4. 注入主���程
# ═══════════════════════════════════════════════════════

def inject(pck_path: Optional[str] = None,
           bridge_gd_path: Optional[str] = None,
           dry_run: bool = False) -> bool:
    """注入桥接脚本到游戏 PCK。"""
    # 定位 PCK
    if pck_path:
        pck = Path(pck_path)
    else:
        pck = find_game_pck()
    if not pck or not pck.exists():
        logger.error("未找到 BackpackBattles.pck。可用 --pck 指定路径，或先运行游戏。")
        return False
    logger.info("✅ 找到 PCK: %s", pck)

    # 定位 bridge.gd（支持开发模式 + PyInstaller 打包模式）
    if bridge_gd_path:
        bridge_src = Path(bridge_gd_path)
    else:
        # 开发模式：bridge/inject.py → bridge/bridge.gd
        bridge_src = Path(__file__).parent / "bridge.gd"
        if not bridge_src.exists():
            # PyInstaller 打包模式：bridge.gd 在 sys._MEIPASS/bridge/ 下
            try:
                import sys as _sys
                if hasattr(_sys, '_MEIPASS'):
                    bridge_src = Path(_sys._MEIPASS) / "bridge" / "bridge.gd"
            except Exception:
                pass
    if not bridge_src or not bridge_src.exists():
        logger.error("未找到 bridge.gd: %s", bridge_src)
        return False
    logger.info("✅ 桥接脚本: %s", bridge_src)

    # 检查是否已注入（通过 PCK 中是否已有 bpb_ai_bridge.gd）
    _, entries, _, _, _ = parse_pck(pck)
    already_injected = BRIDGE_RES_PATH in entries
    if already_injected:
        logger.warning("⚠  桥接已注入！如需重新注入请先还原（restore）。")
        if not dry_run:
            ans = input("是否继续覆盖注入？(y/N): ").strip().lower()
            if ans != "y":
                logger.info("已取消")
                return False

    # 读取/修改 Main.tscn
    logger.info("正在解析 PCK...")
    header, entries, raw_header, raw_index, raw_data = parse_pck(pck)
    main_entry = entries.get(MAIN_TSCN_PATH)

    if not main_entry:
        logger.error("PCK 中��找到 Core/Main.tscn！")
        return False

    main_tscn_data = read_file(entries, raw_data, MAIN_TSCN_PATH)
    if main_tscn_data is None:
        logger.error("无法读取 Core/Main.tscn 内容")
        # 回退：直接从文件读取
        with open(pck, "rb") as f:
            f.seek(main_entry[0])
            main_tscn_data = f.read(main_entry[1])

    # ���改 Main.tscn
    logger.info("正在修改 Main.tscn 以加载桥接脚本...")
    modified_tscn = modify_main_tscn(main_tscn_data)
    logger.info("  Main.tscn: %d → %d bytes", len(main_tscn_data), len(modified_tscn))

    # 读取 bridge.gd
    bridge_data = bridge_src.read_bytes()
    logger.info("  bridge.gd: %d bytes", len(bridge_data))

    if dry_run:
        logger.info("[DRY RUN] 将执行以下操作：")
        logger.info("  1. 备份原 PCK → %s.bak", pck)
        logger.info("  2. 替换 Core/Main.tscn（注入 BPABridge 节点）")
        logger.info("  3. 新增 %s (%d bytes)", BRIDGE_RES_PATH, len(bridge_data))
        logger.info("  4. 重写 PCK")
        return True

    # 备份
    backup = pck.with_suffix(pck.suffix + BACKUP_SUFFIX)
    if not backup.exists():
        logger.info("备份原 PCK → %s", backup)
        shutil.copy2(pck, backup)
    else:
        logger.info("备份已存在: %s（跳过）", backup)

    # 重建 PCK
    logger.info("正在重建 PCK 文件...")
    new_pck_data = rebuild_pck(
        entries, header, raw_header, raw_index, raw_data,
        modified_files={MAIN_TSCN_PATH: modified_tscn},
        new_files={BRIDGE_RES_PATH: bridge_data},
    )

    # 写回
    with open(pck, "wb") as f:
        f.write(new_pck_data)
    logger.info("✅ PCK 写入完成！(%d bytes)", len(new_pck_data))

    logger.info("")
    logger.info("=" * 55)
    logger.info(" 注入成功！请重启游戏使桥接生效。")
    logger.info(" 桥接 TCP 服务将在游戏运行后监听 127.0.0.1:19527")
    logger.info(" 恢复方法：运行 restore 子命令，或通过 Steam 验证完整性")
    logger.info("=" * 55)

    return True


def restore(pck_path: Optional[str] = None) -> bool:
    """从备份还原原版 PCK。"""
    if pck_path:
        pck = Path(pck_path)
    else:
        pck = find_game_pck()
    if not pck or not pck.exists():
        logger.error("未找到 PCK")
        return False
    backup = pck.with_suffix(pck.suffix + BACKUP_SUFFIX)
    if not backup.exists():
        logger.error("未找到备份 %s，请通过 Steam 验证游戏完整性恢复", backup)
        return False
    shutil.copy2(backup, pck)
    logger.info("✅ 已还原原版 PCK: %s", pck)
    return True


def status(pck_path: Optional[str] = None) -> bool:
    """检查注入状态。"""
    if pck_path:
        pck = Path(pck_path)
    else:
        pck = find_game_pck()
    if not pck or not pck.exists():
        logger.error("未找到 PCK")
        return False

    _, entries, _, _, _ = parse_pck(pck)
    injected = BRIDGE_RES_PATH in entries
    backup = pck.with_suffix(pck.suffix + BACKUP_SUFFIX)

    logger.info("PCK: %s", pck)
    logger.info("文件数: %d", len(entries))
    logger.info("桥接注入: %s", "✅ 是" if injected else "❌ 否")
    logger.info("备份存在: %s", "✅" if backup.exists() else "❌")

    return True


# ═══════════════════════════════════════════════════════
# CLI
# ═══════════════════════════════════════════════════════

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    import argparse
    ap = argparse.ArgumentParser(description="BPB AI Bridge Injector v2")
    ap.add_argument("action", nargs="?", default="inject",
                    choices=["inject", "restore", "status", "find"],
                    help="操作")
    ap.add_argument("--pck", help="PCK 路径（不指定则自动查找）")
    ap.add_argument("--bridge", help="bridge.gd 路径")
    ap.add_argument("--dry-run", action="store_true", help="仅检查不动文件")
    args = ap.parse_args()

    if args.action == "inject":
        ok = inject(args.pck, args.bridge, args.dry_run)
        sys.exit(0 if ok else 1)
    elif args.action == "restore":
        ok = restore(args.pck)
        sys.exit(0 if ok else 1)
    elif args.action == "status":
        ok = status(args.pck)
        sys.exit(0 if ok else 1)
    elif args.action == "find":
        pck = find_game_pck()
        if pck:
            print(pck)
        else:
            print("NOT_FOUND", file=sys.stderr)
            sys.exit(1)

"""生成 Godot 3.x PCK（pack v1）——只用于工作区内的探针包，绝不写入游戏目录。

格式依据 tools/pck_extractor.py 解析结果：
GDPC | pack_ver(u32) | major/minor/patch(u32) | 16*reserved(u32) | file_count(u32)
条目: path_len(u32) path(utf8) offset(u64) size(u64) md5(16B)
"""
import hashlib
import os
import struct
from pathlib import Path

MAGIC = b"GDPC"
PACK_VERSION = 1
GODOT_VERSION = (3, 6, 0)
RESERVED = 16


def write_pck(out_path: Path, entries: dict[str, bytes], godot_version=GODOT_VERSION) -> Path:
    """entries: {"res://path": bytes}。返回写出的路径。"""
    header_size = 4 + 4 + 4 * 3 + 4 * RESERVED + 4
    index_size = 0
    for key in entries:
        index_size += 4 + len(key.encode("utf-8")) + 8 + 8 + 16
    offset = header_size + index_size

    offsets = {}
    body = b""
    for key, data in entries.items():
        offsets[key] = (offset + len(body), len(data), hashlib.md5(data).digest())
        body += data

    with out_path.open("wb") as f:
        f.write(MAGIC)
        f.write(struct.pack("<I", PACK_VERSION))
        f.write(struct.pack("<III", *godot_version))
        f.write(b"\x00" * (4 * RESERVED))
        f.write(struct.pack("<I", len(entries)))
        for key, data in entries.items():
            raw = key.encode("utf-8")
            f.write(struct.pack("<I", len(raw)))
            f.write(raw)
            off, size, md5 = offsets[key]
            f.write(struct.pack("<QQ", off, size))
            f.write(md5)
        f.write(body)
    return out_path


def build_probe_pck(out_path: Path, gd_path: Path, project_config: bytes = None) -> Path:
    config = project_config or (
        b'config_version=4\n[application]\nconfig/name="BPB Opponent Research"\n'
        b"[logging]\nfile_logging/enable_file_logging=false\n"
    )
    return write_pck(
        out_path,
        {
            "res://project.godot": config,
            "res://fetch_opponents.gd": gd_path.read_bytes(),
        },
    )


if __name__ == "__main__":
    import argparse

    ap = argparse.ArgumentParser(description="Build a probe pck from a GDScript file")
    ap.add_argument("gd", help="GDScript 源文件")
    ap.add_argument("-o", "--out", default="probe.pck")
    args = ap.parse_args()
    p = build_probe_pck(Path(args.out), Path(args.gd))
    print(f"wrote {p} ({p.stat().st_size} bytes)")

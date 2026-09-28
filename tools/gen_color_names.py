# -*- coding: utf-8 -*-
"""gen_color_names.py — 生成 gd_core_py/_colors.py（Godot 3.6-stable 具名色表）。

为什么要这个工具
────────────────
`_rt.Color` 是 gd_core_items 的**构造期依赖**：`Item._init_fields` 里那句
`self.defaultColor = Color.white`（gd_core_items/Item.gd:352）在类字段初始化时
就要求 `Color.white` 存在，缺了就是 `AttributeError`，而且是在 502 件物品的
**基类**上炸 —— 不是「用不到就不实现」的那类东西。

★ 为什么不凭记忆手抄：Godot 的具名色来自 X11 表（140 余条），手抄极易串值。
  而串值**不会报错**，只会让颜色悄悄变错、且几乎无法回查。所以一律从
  3.6-stable 的 `core/color_names.inc`（`Color::hex(0xRRGGBBAA)`）机器抽取，
  通道值按 `Color::hex` 的 **float32 除法**复算（引擎里是 `p_r / 255.0f`），
  与引擎逐位对齐。

★ `Color.White` / `Color.Black`（大写）在本仓库里**并不存在**：
  Godot 的静态色常量全是小写（`Color::white` / `Color::black` 走 `_named_colors`）。
  曾经搜出「`Color.White` 4 处 / `Color.Black` 3 处」是 `grep -E "Color\\.White"`
  把 `PieceColor.White` 一并匹配的**伪足迹**。故本表**不**额外注入大写别名 ——
  那等于杜撰引擎里没有的常量，会让一处笔误静默通过。

用法
────
    python tools/gen_color_names.py            # 从本地缓存生成 gd_core_py/_colors.py
    python tools/gen_color_names.py --fetch    # 先用 gh 拉 3.6-stable 的 color_names.inc
    python tools/gen_color_names.py --check    # 只校验产物与源是否同步（不同步即 EXIT=1）

`--check` 供 tools/run_gd_core.py 的闸门调用：改了生成逻辑或换了 Godot 版本却忘了
重新生成，会在流水线里当场失败，而不是等到物品构造时才炸。
"""
import argparse
import base64
import io
import os
import re
import struct
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GH = os.path.join(ROOT, "gh_tmp", "bin", "gh.exe")
SRC_DIR = os.path.join(ROOT, "output", "godot_src")
SRC_INC = os.path.join(SRC_DIR, "color_names.inc")
OUT_PY = os.path.join(ROOT, "gd_core_py", "_colors.py")

GODOT_REF = "3.6-stable"

HEADER = '''# -*- coding: utf-8 -*-
r"""_colors.py — Godot %(ref)s 的具名色表（**生成文件**，勿手改）。

生成：`python tools/gen_color_names.py`（源：core/color_names.inc @ %(ref)s）
校验：`python tools/gen_color_names.py --check`

★ 不凭记忆手抄：140 余条 X11 色名手抄极易串值，而串值**不会报错**，只会让颜色
  悄悄变错、且很难回查。通道值按 `Color::hex` 的除法复算并**按 float32 舍入**
  （引擎里是 `p_r / 255.0f`），与引擎逐位一致。

用途：GDScript 写 `Color.white` 这类**小写**静态具名颜色（本项目实测只用到
`white`：gd_core_items/Item.gd:352 `var defaultColor = Color.white`）。
整表一并生成，免得下次换个色名再炸一轮。

★ 表里**有** `"white"` / `"black"`（具名查表用），但**没有** `Color.White` /
  `Color.Black` 这类大写别名 —— Godot 的静态色常量全小写。仓库里曾搜出的
  「Color.White 4 处」是 `grep -E "Color\\.White"` 误匹配 `PieceColor.White` 的
  伪足迹。给本类加大写别名等于**杜撰引擎里没有的常量**，会让笔误静默通过，故不做。

★ 注意 `Color("transparent")`（具名查表 → (1,1,1,0)）与想象中的 `Color.transparent`
  不是一回事：核对 color.h @ %(ref)s，**并无**该静态常量（只有具名表里那一条），
  故本表不做特殊化，也不需要。
"""

'''


def f32(x):
    """按 float32 舍入 —— 引擎的通道值是 `float` 运算结果，不是 double。"""
    return struct.unpack("<f", struct.pack("<f", x))[0]


def fetch():
    # 用 gh 拉 Godot GODOT_REF 的 core/color_names.inc 到 output/godot_src/
    if not os.path.exists(GH):
        print("FAIL 找不到 gh：%s" % GH)
        return 1
    r = subprocess.run(
        [GH, "api",
         "repos/godotengine/godot/contents/core/color_names.inc?ref=%s" % GODOT_REF,
         "--jq", ".content"],
        capture_output=True)
    if r.returncode != 0:
        print("FAIL %s" % r.stderr.decode("utf-8", "replace")[:300])
        return 1
    data = base64.b64decode(r.stdout)
    os.makedirs(SRC_DIR, exist_ok=True)
    io.open(SRC_INC, "wb").write(data)
    print("已拉取 %s（%d 字节）" % (SRC_INC, len(data)))
    return 0


def parse_inc(text):
    """抽 `_named_colors.insert("name", Color::hex(0xRRGGBBAA))` 全部条目。"""
    return re.findall(
        r'_named_colors\.insert\("([a-z0-9]+)",\s*Color::hex\(0x([0-9A-Fa-f]{8})\)\)',
        text)


def render():
    """读本地缓存 → 渲染完整的 _colors.py 文本。返回 (文本, 条数)。"""
    if not os.path.exists(SRC_INC):
        raise SystemExit("FAIL 缺 %s —— 先跑 `python tools/gen_color_names.py --fetch`" % SRC_INC)
    text = io.open(SRC_INC, encoding="utf-8", errors="replace").read()
    pairs = parse_inc(text)
    if not pairs:
        raise SystemExit("FAIL %s 里没抽出任何条目 —— 上游格式变了？" % SRC_INC)

    rows = []
    for name, hx in pairs:
        rr, gg, bb, aa = (int(hx[i:i + 2], 16) for i in (0, 2, 4, 6))
        vals = tuple(f32(c / 255.0) for c in (rr, gg, bb, aa))
        rows.append('    "%s": (%s),' % (name, ", ".join(repr(v) for v in vals)))

    body = ("_COLOR_NAMES = {\n" + "\n".join(rows) + "\n}\n")
    return HEADER % {"ref": GODOT_REF} + body, len(rows)


def main():
    ap = argparse.ArgumentParser(description="生成 gd_core_py/_colors.py（Godot 具名色表）")
    ap.add_argument("--fetch", action="store_true", help="先从 GitHub 拉 color_names.inc")
    ap.add_argument("--check", action="store_true", help="只校验产物是否与源同步")
    args = ap.parse_args()

    if args.fetch and fetch() != 0:
        return 1

    src, n = render()

    if args.check:
        cur = io.open(OUT_PY, encoding="utf-8").read() if os.path.exists(OUT_PY) else ""
        if cur == src:
            print("色表同步（%d 条 → gd_core_py/_colors.py）" % n)
            return 0
        print("FAIL gd_core_py/_colors.py 与 %s 不同步（期望 %d 行）" % (SRC_INC, src.count("\n")))
        print("     跑 `python tools/gen_color_names.py` 重新生成")
        return 1

    io.open(OUT_PY, "w", encoding="utf-8").write(src)
    print("写入 gd_core_py/_colors.py（%d 条，%d 行）" % (n, src.count("\n")))
    for probe in ("white", "black", "transparent"):
        hit = [r for r in src.splitlines() if r.startswith('    "%s"' % probe)]
        if hit:
            print("  %s" % hit[0].strip())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

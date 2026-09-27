#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
dump_methods.py — 从原版脚本中抽出指定方法的完整源码体（含起止行号）

用途：为 gd_core 的移植工作生成「移植底稿」。移植时逐字对照原版，
     不做任何逻辑改动，只把单例/节点/视觉调用替换为 ctx 注入与 hooks 钩子。

用法：
    python tools/dump_methods.py <源文件> <方法名文件> [--out 输出文件]

    源文件      相对项目根的路径，如 decompiled_full/Items/Item.gd
    方法名文件  每行一个方法名（# 开头为注释）
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def read_lines(path):
    with io.open(path, encoding="utf-8", errors="replace") as f:
        return f.read().split("\n")


def method_spans(lines):
    """返回 {name: (start_idx, end_idx)}，1-based 闭区间；只取顶层 func。"""
    spans = {}
    starts = []
    for i, line in enumerate(lines):
        m = re.match(r"^(static )?func\s+([A-Za-z_]\w*)", line)
        if m:
            starts.append((i, m.group(2)))
    for n, (i, name) in enumerate(starts):
        end = len(lines) - 1
        for j in range(i + 1, len(lines)):
            # 下一个顶层 func 或顶层 class/enum/const/var 起即为边界
            if re.match(r"^(static )?func\s", lines[j]):
                end = j - 1
                break
        spans.setdefault(name, (i, end))
    return spans


def dedent_block(lines):
    """记录块内最小缩进，用于保持原样输出（此处只做展示，不重排）。"""
    return "\n".join(lines)


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    src = os.path.join(ROOT, sys.argv[1])
    names_file = os.path.join(ROOT, sys.argv[2])
    out_file = None
    if "--out" in sys.argv:
        out_file = os.path.join(ROOT, sys.argv[sys.argv.index("--out") + 1])

    lines = read_lines(src)
    spans = method_spans(lines)

    want = []
    for line in read_lines(names_file):
        s = line.strip()
        if s and not s.startswith("#"):
            want.append(s)

    buf = io.StringIO()
    buf.write("# 移植底稿：%s\n" % sys.argv[1])
    buf.write("# 共 %d 个方法请求，命中 %d 个\n\n"
              % (len(want), sum(1 for w in want if w in spans)))

    missing = [w for w in want if w not in spans]
    for w in want:
        if w not in spans:
            continue
        a, b = spans[w]
        buf.write("### %s  (%s:%d-%d)\n" % (w, os.path.basename(src), a + 1, b + 1))
        buf.write(dedent_block(lines[a:b + 1]))
        buf.write("\n\n")

    text = buf.getvalue()
    if out_file:
        with io.open(out_file, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
        print("写入 %s（%d 字符）" % (out_file, len(text)))
    else:
        sys.stdout.write(text)

    if missing:
        print("!!! 未命中 %d 个：%s" % (len(missing), ", ".join(missing)),
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

# -*- coding: utf-8 -*-
"""check_class_cycles.py — 检测 gd_core 内 class_name 脚本的循环依赖。

背景：Godot 3.x 的 GDScript 不允许 class_name 脚本之间形成循环引用，
一旦成环，运行/编辑时会报
    Parse Error: The class "X" couldn't be fully loaded
                    (script error or cyclic dependency)
由于 class_name 是全局可见的，只要 A 的**类体/函数体**里出现 `B.xxx`
（B 为另一个 class_name），就构成 A→B 的依赖边。

注意：本脚本只认「类名.成员」形式的引用（静态访问 / 类型标注 / is 判断），
`func` 内部对实例方法的调用不算依赖。

用法：
  python tools/check_class_cycles.py
退出码 0 = 无环
"""
import re
import sys
import pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent
CORE = ROOT / "gd_core"
LINE_COMMENT = re.compile(r"#.*$")


def main() -> int:
    files = sorted(CORE.glob("*.gd"))
    classes = {}
    for p in files:
        m = re.search(r"^class_name (\w+)", p.read_text(encoding="utf-8"), re.M)
        if m:
            classes[m.group(1)] = p

    deps = {}
    detail = {}
    for cls, p in classes.items():
        src = "\n".join(
            LINE_COMMENT.sub("", ln) for ln in
            p.read_text(encoding="utf-8").splitlines())
        out = set()
        for other in classes:
            if other == cls:
                continue
            for i, line in enumerate(src.splitlines(), 1):
                if re.search(r"\b%s\b" % re.escape(other), line):
                    out.add(other)
                    detail.setdefault((cls, other), []).append(i)
        deps[cls] = out

    # 找所有环（DFS 回溯）
    cycles = []
    seen = set()

    def walk(node, path, onpath):
        for nxt in sorted(deps.get(node, ())):
            if nxt in onpath:
                idx = path.index(nxt)
                cyc = path[idx:] + [nxt]
                key = tuple(sorted(cyc[:-1]))
                if key not in seen:
                    seen.add(key)
                    cycles.append(cyc)
                continue
            walk(nxt, path + [nxt], onpath | {nxt})

    for cls in sorted(deps):
        walk(cls, [cls], {cls})

    print("gd_core class_name 依赖环检测")
    print("=" * 64)
    print("类：%s" % ", ".join(sorted(classes)))
    if not cycles:
        print("\nOK：无循环依赖")
        return 0

    for cyc in cycles:
        print("\n[环] " + " → ".join(cyc))
        for a, b in zip(cyc, cyc[1:]):
            locs = detail.get((a, b), [])
            show = ", ".join(str(x) for x in locs[:8])
            more = "" if len(locs) <= 8 else " ... +%d" % (len(locs) - 8)
            print("     %s → %s  @ %s.gd:%s%s" % (
                a, b, classes[a].name, show, more))
    print("\n合计 %d 个环，需在源码里断开（改用 CoreConst 常量表 / 鸭子类型判断 /"
          " 或把强耦合类并入同文件的内嵌类）" % len(cycles))
    return 1


if __name__ == "__main__":
    sys.exit(main())

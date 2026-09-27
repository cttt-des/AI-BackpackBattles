# -*- coding: utf-8 -*-
"""audit_gd_core.py — 审计 gd_core 无头内核的接口完整性（编译前静态体检）。

背景：无头内核把「视觉/音频/UI 副作用」统一改走 ctx.hooks、把「全局单例」改成注入对象
（ctx.log / ctx.bus / ctx.rng）、把类名去前缀（Item→CoreItem）。这些改名一旦漏掉，
GDScript 要到运行期才炸，且往往炸在战斗最深处。本脚本在改完代码后立刻兜住。

检查项：
  1. ctx.hooks.X / ctx.log.X / ctx.bus.X / ctx.rng.X 调用的方法是否存在
  2. CoreXxx.method(...) 静态调用、CoreXxx.CONST 常量引用是否存在
  3. CoreXxx.Yyy 内嵌类名引用是否存在（如 CoreRng.BalancedRng）
  4. 有返回值的行为虚方法经 _behavior_call 派发时是否 return 出去（防静默判否）
  5. _behavior_call / _hasBehaviorMethod 派发的**落点是否真实可达**
     —— 名字要么定义在 CoreItem 上（虚方法覆写点，GDScript 多态直达物品脚本），
        要么列入 CoreItem.SELF_BEHAVIOR_METHODS（接缝回落到物品自身）
  6. bool(...) 误用（GDScript 3.x 无此内置，应为 CoreUtil.truth）

已知不计入：
  · `.new()` 构造器
  · `XXX.gd` 文件名（注释里出现，非代码引用）
  · `ctx.<var>.method()` 实例调用（无法静态穷举，由无头 smoke test 覆盖）

用法：
  python tools/audit_gd_core.py          # 退出码 0 = 干净
"""
import re
import sys
import pathlib
from collections import defaultdict

ROOT = pathlib.Path(__file__).resolve().parent.parent
CORE = ROOT / "gd_core"

# 去掉行注释，避免注释里的类名/方法名被当成引用
LINE_COMMENT = re.compile(r"#.*$")

# 有返回值、且返回值参与战斗判定的行为虚方法。这些方法经 _behavior_call 派发时
# **必须把返回值 return 出去**：丢掉返回值不会报错，只会静默判否。
# 历史教训：_behavior_call 曾漏写 return，导致全部联动物品（canAffect）静默失效，
# 而静态审计与冒烟测试都察觉不到。
VALUE_RETURNING_BEHAVIORS = (
    "getTriggerPriority",
    "canAffect", "canAffect_secondary", "canAffect_tertiary", "canAffect_lightning",
    "isAffectingDistinct", "affectsEmpty",
    "getAffectedCellsAfterRotate_primary", "getAffectedCellsAfterRotate_secondary",
)


def strip_comments(src: str) -> str:
    """逐行去 # 之后的内容（gd_core 的字符串里不含 # 号，安全）。"""
    return "\n".join(LINE_COMMENT.sub("", line) for line in src.splitlines())


def methods_of(src: str) -> set:
    """顶层与内嵌类的方法（static func / func，含缩进）。"""
    return set(re.findall(r"^[\t ]*(?:static )?func (\w+)", src, re.M))


def symbols_of(src: str) -> set:
    """常量、枚举、内嵌类名。"""
    out = set(re.findall(r"^[\t ]*(?:const|enum) (\w+)", src, re.M))
    out |= set(re.findall(r"^[\t ]*class (\w+)", src, re.M))
    out |= set(re.findall(r"^[\t ]*signal (\w+)", src, re.M))
    return out


def main() -> int:
    files = sorted(CORE.glob("*.gd"))
    if not files:
        print("gd_core/ 为空")
        return 1

    raw = {p.stem: p.read_text(encoding="utf-8") for p in files}
    code = {k: strip_comments(v) for k, v in raw.items()}
    exposed = {k: methods_of(v) | symbols_of(v) for k, v in code.items()}

    attr2class = {
        "hooks": "CoreHooks",
        "log": "CoreCombatLog",
        "bus": "CoreEventBus",
        "rng": "CoreRng",
    }

    # 行为派发的合法落点（见检查项 5）：
    #   · CoreItem 自身定义 → 虚方法覆写点，物品脚本覆写后经 GDScript 多态直达
    #   · CoreItem.SELF_BEHAVIOR_METHODS → 基类未定义的回调，接缝回落到物品自身
    #     （从源码里读，不另抄一份，避免名单漂移）
    coreitem_methods = methods_of(code.get("CoreItem", ""))
    m_self = re.search(r"SELF_BEHAVIOR_METHODS\s*:=\s*\[(.*?)\]",
                       raw.get("CoreItem", ""), re.S)
    self_behavior_methods = set(re.findall(r'"(\w+)"', m_self.group(1))) if m_self else set()
    if not self_behavior_methods:
        print("[审计自身异常] 未能在 CoreItem.gd 中解析出 SELF_BEHAVIOR_METHODS")
        return 1

    problems = defaultdict(list)
    used_hooks = set()

    for name, src in code.items():
        for i, line in enumerate(src.splitlines(), 1):
            # 1) ctx.<member>.<method>
            for attr, cls in attr2class.items():
                for m in re.finditer(r"\bctx\.%s\.(\w+)" % attr, line):
                    meth = m.group(1)
                    if attr == "hooks":
                        used_hooks.add(meth)
                    if meth not in exposed.get(cls, set()):
                        problems["%s(ctx.%s).%s 未定义" % (cls, attr, meth)].append(
                            "%s.gd:%d" % (name, i))

            # 2) CoreXxx.method / CoreXxx.CONST / CoreXxx.InnerClass
            for m in re.finditer(r"\b(Core\w+)\.(\w+)", line):
                cls, sym = m.group(1), m.group(2)
                if sym in ("new", "gd"):
                    continue
                if cls not in exposed:
                    problems["类 %s 不存在" % cls].append("%s.gd:%d" % (name, i))
                    continue
                if sym in exposed[cls]:
                    continue
                problems["%s.%s 未定义" % (cls, sym)].append("%s.gd:%d" % (name, i))

            # 3) 有返回值的行为虚方法：派发点必须 return（见 VALUE_RETURNING_BEHAVIORS）
            for m in re.finditer(r'_behavior_call\("(\w+)"', line):
                if m.group(1) in VALUE_RETURNING_BEHAVIORS and not line.lstrip().startswith("return"):
                    problems["_behavior_call(\"%s\") 的返回值被丢弃" % m.group(1)].append(
                        "%s.gd:%d" % (name, i))

            # 4) bool(x) 是 GDScript 4 的构造式，3.x 无此内置 → 必须用 CoreUtil.truth(x)
            if re.search(r"(?<![\w.])bool\s*\(", line):
                problems["bool(...) 构造式在 GDScript 3.x 不存在，应改用 CoreUtil.truth(...)"].append(
                    "%s.gd:%d" % (name, i))

    # 5) 行为派发的落点必须真实可达（见文件头检查项 5）
    for name, src in code.items():
        for i, line in enumerate(src.splitlines(), 1):
            for m in re.finditer(r'_(?:behavior_call|hasBehaviorMethod)\("(\w+)"', line):
                called = m.group(1)
                if called in coreitem_methods or called in self_behavior_methods:
                    continue
                problems["_behavior_call(\"%s\") 的落点不可达（既非 CoreItem 方法，"
                         "也不在 SELF_BEHAVIOR_METHODS）" % called].append("%s.gd:%d" % (name, i))

    print("gd_core 接口完整性审计")
    print("=" * 64)
    if problems:
        for key in sorted(problems):
            locs = problems[key]
            print("[缺失] %s" % key)
            for loc in locs[:6]:
                print("        %s" % loc)
            if len(locs) > 6:
                print("        ... 另 %d 处" % (len(locs) - 6))
        print("\n合计 %d 类问题" % len(problems))
    else:
        print("OK：ctx.hooks / ctx.log / ctx.bus / ctx.rng 与全部 Core*. 静态引用均已定义")

    unused = sorted(exposed.get("CoreHooks", set()) - used_hooks)
    unused = [u for u in unused if not u.startswith("_")]
    if unused:
        print("\n[提示] CoreHooks 定义但当前无调用（留给注入游戏进程时覆写）：")
        print("       " + ", ".join(unused))

    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())

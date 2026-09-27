#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""run_gd_core.py — gd_core 无头内核一键校验流水线

依次执行十道闸门，任一失败即中止：

  1. 静态审计  tools/audit_gd_core.py      —— ctx.* 与 Core*. 引用是否都有定义
                                                + 行为派发返回值是否漏传 + bool() 误用
  2. 依赖环检测 tools/check_class_cycles.py —— class_name 之间无循环引用
  3. 全量解析  gd_core_test/ParseAll.gd     —— 内核脚本在 Godot 3.6 下零解析错误
  4. 契约冒烟  gd_core_test/Smoke.gd        —— 基础对拼 / 疲劳时序 / 确定性
  5. 网格子系统 gd_core_test/GridSmoke.gd   —— 受影响格判定链 / 邻接 / 取首项次序
  6. 物品脚本  gd_core_test/ItemParseAll.gd —— gd_core_items/* 全量解析
  7. 单例门面  gd_core_test/FacadeSmoke.gd  —— ItemBook 描述符身份 / 库存查询 /
                                                Game 状态量 / combatTimer 身份
  8. 真实阵容  gd_core_test/LineupBattle.gd —— 8 套真实 lineup 装进内核跑完整对局：
                                                无运行期错误 / 时限内自然收场 /
                                                行为确实触发 / 同种子逐位可复现
  9. 全物品上场 gd_core_test/ItemBattle.gd  —— 517 件可转译物品**逐一**真打一场：
                                                无运行期错误 / 自然收场 / 行为确实触发
                                                ★ 前八道全绿时它仍能抓出成批缺陷
                                                  （首轮 101 条、二轮 288 条），
                                                  因为「解析通过」≠「装上能跑」。
 10. 宝石门面  gd_core_test/GemFacade.gd   —— Socket 折叠等价性 / getGemMode 四分支 /
                                                三种模式的**公式级**效果 /
                                                宝石自身冷却能自行触发

  0/10 前置生成：下面四支幂等生成器每次全量重跑（产物陈旧 = 闸门给旧代码背书）
    gen_core_item_book.py → build_item_scripts.py → gen_lineup_fixture.py
    → gen_test_project.py

★ 跑 Godot 的闸门一律开启 `SCRIPT ERROR` 扫描：Godot 打印脚本错误后**继续执行**，
  退出码仍为 0，光看退出码会漏掉「某行判定静默不执行」这类最危险的偏离。

★ 报错定位陷阱：Godot 的 `SCRIPT ERROR` 形如
      at: <函数名> (res://<脚本路径>:<行号>)
  其中**行号**取自函数真正定义的那个脚本，而**路径**取的是运行期实例的脚本。
  于是内核方法（如 CoreItem.getP_check）出错时，会打印成
  `at: getP_check (res://gd_core_items/PoisonIvy.gd:1441)` —— PoisonIvy.gd 只有
  51 行，1441 指的是 CoreItem.gd。判读时按「函数名 + 行号」回内核脚本里找。

可选：

  --bench   追加吞吐基准 gd_core_test/Bench.gd

用法：
    python tools/run_gd_core.py [--bench]

依赖：output/godot36/Godot_v3.6-stable_win64.exe（无头宿主）
"""
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
TEST_PROJ = os.path.join(ROOT, "gd_core_test")
PY = sys.executable

GODOT_ARGS = ["--no-window", "--audio-driver", "Dummy", "--path", TEST_PROJ]


def _decode(raw: bytes) -> str:
    """Godot 3 在 Windows 控制台按本地代码页（CP936）输出中文，
    而写文件走 UTF-8。故先试 UTF-8，失败回退 CP936。"""
    for enc in ("utf-8", "cp936"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


# 退出期噪声：Godot 的对象/资源清理告警，与测试结论无关
# （Godot 会加 "ERROR: "/"WARNING: " 前缀，故用子串匹配而非前缀匹配）
_NOISE_KEYS = (
    "Godot Engine v", "OpenGL ES", "Async. shader",
    "ObjectDB instances leaked", "Resources still in use",
    '_first != nullptr',
    "at: ~List", "at: cleanup", "at: clear",
)


def run(cmd, label, cwd=None, scan_errors=False):
    print("\n" + "=" * 68)
    print(f"[{label}]")
    print("=" * 68)
    p = subprocess.run(cmd, cwd=cwd or ROOT, capture_output=True)
    out = _decode((p.stdout or b"") + (p.stderr or b""))
    script_errors = []
    for line in out.splitlines():
        s = line.strip()
        if not s:
            continue
        # ★ 脚本运行期错误必须单独抓：Godot 打印 `SCRIPT ERROR: ...` 后**继续执行**，
        #   进程退出码仍是 0 —— 于是「物品行为某一行静默不执行」这种最危险的
        #   偏离（判定少了一次加伤、某个 hook 从未命中）在退出码上完全看不出来。
        #   典型实例：闸门 8 首轮 `spikeDamageSource` 未构造，`setDamage` 报 32 次
        #   `Nonexistent function ... in base 'Nil'`，尖刺/中毒两条伤害整条失效，
        #   而测试自己的断言全过。故凡跑 Godot 的闸门一律开此扫描。
        if "SCRIPT ERROR" in s:
            script_errors.append(s)
        if any(k in s for k in _NOISE_KEYS):
            continue
        print(line)
    if scan_errors and script_errors:
        print(f"\n[闸门失败] 检出 {len(script_errors)} 条脚本运行期错误"
              f"（脚本会继续跑，退出码看不出来）：")
        for s in dict.fromkeys(script_errors):
            print("   " + s)
        return 1
    return p.returncode


def say_file(path, title):
    if os.path.exists(path):
        print(f"\n--- {title} ---")
        with open(path, encoding="utf-8") as fh:
            print(fh.read().rstrip())


def main():
    if not os.path.exists(GODOT):
        print(f"缺少 Godot 无头宿主：{GODOT}")
        return 2

    with_bench = "--bench" in sys.argv

    # ── 0/10 前置生成 ──
    # ★ 为什么把它放进流水线：闸门 3/6/8 验证的是**生成产物**（gd_core 解析、
    #   gd_core_items/*、project.godot 的 class_name 注册表）。产物若陈旧，
    #   闸门就是在给旧代码背书 —— 上一轮 CoreItemBook 加入内核后漏跑
    #   gen_test_project，就报过 `The identifier "CoreItemBook" isn't declared`。
    #   三支生成器都是幂等的，重复跑只花几秒，故每次全量前置。
    if run([PY, os.path.join(ROOT, "tools", "gen_core_item_book.py")],
           "0/10 描述符注册表生成（ItemBook → CoreItemBook）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "build_item_scripts.py")],
           "0/10 物品脚本转译（Items/*.gd → gd_core_items/）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gen_lineup_fixture.py")],
           "0/10 真实阵容夹具（lineups/*.json → LineupFixture.gd）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gen_test_project.py")],
           "0/10 测试工程 class_name 注册表") != 0:
        return 1

    if run([PY, os.path.join(ROOT, "tools", "audit_gd_core.py")], "1/10 静态审计") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "check_class_cycles.py")], "2/10 依赖环检测") != 0:
        return 1
    if run([GODOT] + GODOT_ARGS + ["--script", "ParseAll.gd"],
           "3/10 内核全量解析", scan_errors=True) != 0:
        return 1

    smoke_out = os.path.join(TEST_PROJ, "smoke_result.txt")
    if os.path.exists(smoke_out):
        os.remove(smoke_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "Smoke.gd"],
           "4/10 契约冒烟", scan_errors=True) != 0:
        say_file(smoke_out, "Smoke 报告")
        return 1
    say_file(smoke_out, "Smoke 报告")

    # 网格子系统：受影响格判定链 + 邻接 + 取首项次序（联动物品的判定基础）
    grid_out = os.path.join(TEST_PROJ, "grid_result.txt")
    if os.path.exists(grid_out):
        os.remove(grid_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "GridSmoke.gd"],
           "5/10 网格子系统", scan_errors=True) != 0:
        say_file(grid_out, "GridSmoke 报告")
        return 1
    say_file(grid_out, "GridSmoke 报告")

    # 物品脚本：原版 Items/*.gd 转译成「直挂 CoreItem」的行为脚本。
    # 一个解析错误 = 该物品整类行为不可用，故必须零容忍。
    item_out = os.path.join(TEST_PROJ, "item_parse_result.txt")
    if os.path.exists(item_out):
        os.remove(item_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "ItemParseAll.gd"],
           "6/10 物品脚本全量解析", scan_errors=True) != 0:
        say_file(item_out, "ItemParseAll 报告")
        return 1
    say_file(item_out, "ItemParseAll 报告")

    # 单例门面契约：ItemBook 描述符身份 / 库存类型查询 / Game 状态量映射。
    # 这三者错一个，靠它们跑的物品行为就静默跑偏（isA 恒假、查询恒空），
    # 解析闸门查不出来，必须单独验。
    facade_out = os.path.join(TEST_PROJ, "facade_result.txt")
    if os.path.exists(facade_out):
        os.remove(facade_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "FacadeSmoke.gd"],
           "7/10 单例门面契约", scan_errors=True) != 0:
        say_file(facade_out, "FacadeSmoke 报告")
        return 1
    say_file(facade_out, "FacadeSmoke 报告")

    # 真实阵容端到端：8 套 lineup 装进内核跑完整对局。
    # ★ 这是唯一能抓住「行为装上之后到底跑不跑得起来」的闸门 —— 前面七道
    #   全绿时它首轮仍抓出 4 个真问题（尖刺伤害源未构造 / onready 类型标注丢失 /
    #   Gem 基类解析失败导致 8 个宝石脚本整类漏转译 / Exclusive 系脚本路径拼错）。
    lineup_out = os.path.join(TEST_PROJ, "lineup_result.txt")
    if os.path.exists(lineup_out):
        os.remove(lineup_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "LineupBattle.gd"],
           "8/10 真实阵容端到端", scan_errors=True) != 0:
        say_file(lineup_out, "LineupBattle 报告")
        return 1
    say_file(lineup_out, "LineupBattle 报告")

    # 全物品逐一上场：517 件**每一件**各真打一场（被测物品 1 件 vs 木剑假人）。
    # ★ 这是闸门 8 的「面」的补集：闸门 8 用 8 套真实阵容（16 件）验「搭起来能跑」，
    #   闸门 9 用全量清单验「剩下 501 件单独上场能不能跑」。前八道全绿时它首轮
    #   抓出 101 条运行期错误、二轮（修完第一批后）仍抓出 288 条 —— 因为
    #   「静态解析通过」「某套阵容能跑」都不蕴含「其余每一件装上能跑」：
    #   · 成类缺口：Inventory.changeBuffAmplification_allItems 缺 → Solaris 整套增益静默失效
    #   · 数据错位：params 未按列对齐 → Carrot/Dark Lantern/Brass Knuckles 的 getP1..getP10 全错
    #   · 映射错：GemMode. → CoreConst.GemMode. → 22 支宝石/符文 getGemMode() 全断
    #   这三类都不会让任何一道静态闸门变红，只有逐件真打才暴露。
    itembattle_out = os.path.join(TEST_PROJ, "item_battle_result.txt")
    if os.path.exists(itembattle_out):
        os.remove(itembattle_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "ItemBattle.gd"],
           "9/10 全物品逐一上场", scan_errors=True) != 0:
        say_file(itembattle_out, "ItemBattle 报告")
        return 1
    say_file(itembattle_out, "ItemBattle 报告")

    # 宝石 / Socket 门面：内核把原版的「插座节点」折叠成宿主物品本身
    # （CoreItem.setGem 把 self 当 socket、getItem() 恒返回 self）。
    # ★ 这是又一处「零报错但可能整类无效」的接缝：折叠若没接上，
    #   宝石会安静地跑完一整场却不产生任何效果 —— 而宝石在 gd_core 的
    #   lineup 里出场率很低，靠前面九道闸门撞不见。故单独立闸门，逐条验到
    #   公式级（伤害 100 → +7、57 → +4 为向上取整）与模式分派（四种 getGemMode）。
    #   同时它是覆盖度核算里最后一项「判定路径缺口 initSockets」的验收依据 ——
    #   该缺口已按"折叠后无事可做"闭合，其等价性由本闸门的第 1 节取证。
    gem_out = os.path.join(TEST_PROJ, "gem_result.txt")
    if os.path.exists(gem_out):
        os.remove(gem_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "GemFacade.gd"],
           "10/10 宝石 Socket 门面", scan_errors=True) != 0:
        say_file(gem_out, "GemFacade 报告")
        return 1
    say_file(gem_out, "GemFacade 报告")

    if with_bench:
        bench_out = os.path.join(TEST_PROJ, "bench_result.txt")
        if os.path.exists(bench_out):
            os.remove(bench_out)
        run([GODOT] + GODOT_ARGS + ["--script", "Bench.gd"], "附加 吞吐基准")
        say_file(bench_out, "Bench 报告")

    print("\n全部闸门通过。")
    return 0


if __name__ == "__main__":
    sys.exit(main())

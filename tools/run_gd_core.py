#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""run_gd_core.py — gd_core 无头内核一键校验流水线

依次执行十七道闸门，任一失败即中止（1–10 在 GDScript/Godot 侧，11–14 在 Python 侧，
15 跨两侧）：

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

  ── Python 侧闸门（同一份内核机械转写成 Python 之后的验收） ──

 11. 转写体检  tools/check_gd_py.py         —— 521 个产物 + 10 个手写文件全部语法过关
                                                ★ 手写文件也在体检范围内：生成器由闸门
                                                  守着，人手写的没有任何东西守。
 12. RNG 逐位  tools/verify_godot_rng.py    —— CoreRng 与 Godot 3.6 逐位一致
                                                （不一致 → Python 侧不得用于对照）
 13. Python 端到端 tools/run_gd_py.py       —— 8 套阵容装进 **Python 版内核**跑 56 局，
                                                与闸门 8 产出的 lineup_result.txt 逐字符对照
                                                + 宝石 A/B + 确定性 + RNG 可复现性双侧判据
 14. 模拟器接入 tools/check_gd_core_engine.py —— 模拟器内核（simulator/gd_core_engine.py）
                                                经**生产装配路径**复跑同 56 局，再逐字符对照

  ── 跨两侧闸门（把「摘要一致」升级成「逐事件一致」） ──

 15. 逐事件对照 tools/compare_events.py   —— 取门 8 的 GDScript 事件轨迹与门 13 的
                                                Python 事件轨迹，逐条比对**每一次
                                                logEvent**（56 局 / 4053 条）。
                                                差异分三级：SAME / NUMEQ（仅 int↔float
                                                表示不同、数值相等）/ DIFF（须归因）。
                                                ★ 摘要一致是必要不充分条件：两句不同的
                                                  战斗可以给出完全相同的 win/t/hp/act
                                                  摘要，事件流骗不了人。

  ── 判定路径的运算级取证（静态逐行 + 动态逐帧，两半同属一个闸门） ──

 16. 冷却等价校验 tools/verify_cooldowns_gd.py —— 里程碑 ⑥ 的 `verify_cooldowns`
                                               等价校验。两个半边：
                                                 A 静态：冷却路径 27 对函数逐行对照
                                                   （99 行相等 / 0 行未归因）
                                                 B 动态：读门 9 的 cooldown_battle_result.txt
                                                   （303 件带冷却物品逐帧轮询），
                                                   验证 `triggerTime -= δ × getSpeed()`
                                                   （22.8 万帧 / 0 违背）+ 抖动指纹
                                                   `iterationCooldown/getCooldown()
                                                     ∈ [0.95, 1.05]`
                                               ★ 必须排在门 9 之后（数据源是它的产物）。

  0/17 前置阶段：七支幂等生成器 + 一支前置断言，每次全量重跑
    （产物陈旧 = 闸门给旧代码背书，故不缓存）
    gen_core_item_book.py → build_item_scripts.py → gen_lineup_fixture.py
    → gen_test_project.py → gd_to_py.py → gen_gd_core_data.py → gen_color_names.py
      ★ gen_color_names.py 排最后：它写 gd_core_py/_colors.py，而 gd_to_py.py 会重写
        整个 gd_core_py/ —— 由流水线**生成**而不是「生成后手工补」，链接才不脆弱。
    → survey_gd_syntax.py --verify
      ★ 这支不是生成器，是**前置断言**：守住「可以机械转写」这个前提。它断言
        gd_to_py.py 文档里引用的 21 个语法面数字与实测一致（yield 0 / `%` 1 处 /
        Vector2 198 次 …）。内核算法面变了它就是第一道报警。

★ 闸门 11–14 存在的理由：闸门 1–10 验的是**GDScript 版内核**（`gd_core/` + `gd_core_items/`）。
  模拟器跑的是它的 **Python 转写版**（`gd_core_py/`）。「GDScript 版对」不蕴含
  「Python 版对」—— 转写器的规则命中、运行时垫片的语义、装配次序都可能引入偏差，
  而这些全都不会让闸门 1–10 变红。11–14 是这条链路的独立证据。

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

    # ── 0/17 前置生成 ──
    # ★ 为什么把它放进流水线：闸门 3/6/8 验证的是**生成产物**（gd_core 解析、
    #   gd_core_items/*、project.godot 的 class_name 注册表）。产物若陈旧，
    #   闸门就是在给旧代码背书 —— 上一轮 CoreItemBook 加入内核后漏跑
    #   gen_test_project，就报过 `The identifier "CoreItemBook" isn't declared`。
    #   六支生成器都是幂等的，重复跑只花几十秒，故每次全量前置。
    # ★ 次序不能换：gd_to_py 吃 gd_core/ + gd_core_items/（必须排在
    #   build_item_scripts 之后）；gen_gd_core_data 吃 gd_core_items/ + extracted/。
    if run([PY, os.path.join(ROOT, "tools", "gen_core_item_book.py")],
           "0/17 描述符注册表生成（ItemBook → CoreItemBook）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "build_item_scripts.py")],
           "0/17 物品脚本转译（Items/*.gd → gd_core_items/）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gen_lineup_fixture.py")],
           "0/17 真实阵容夹具（lineups/*.json → LineupFixture.gd）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gen_test_project.py")],
           "0/17 测试工程 class_name 注册表") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gd_to_py.py")],
           "0/17 Python 转写（gd_core* → gd_core_py/）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "gen_gd_core_data.py")],
           "0/17 模拟器运行时数据（→ assets/gd_core_runtime.json）") != 0:
        return 1
    # ★ 排在 gd_to_py 之后：gd_to_py 会重写整个 gd_core_py/，色表必须最后落盘。
    if run([PY, os.path.join(ROOT, "tools", "gen_color_names.py")],
           "0/17 具名色表（→ gd_core_py/_colors.py）") != 0:
        return 1
    # ★ 非生成、而是**前置断言**：gd_to_py.py 文档里引用的语法面数字（21 项）必须
    #   与实测一致。它守的是「可以机械转写」这个前提本身 —— 若有人往内核里加了
    #   `yield` 或第二处 `%` 格式化，转写规则可能已不成立，此时流水线不该继续往下跑。
    if run([PY, os.path.join(ROOT, "tools", "survey_gd_syntax.py"), "--verify"],
           "0/17 语法面断言（gd_to_py.py 文档数字）") != 0:
        return 1

    if run([PY, os.path.join(ROOT, "tools", "audit_gd_core.py")], "1/17 静态审计") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "check_class_cycles.py")], "2/17 依赖环检测") != 0:
        return 1
    if run([GODOT] + GODOT_ARGS + ["--script", "ParseAll.gd"],
           "3/17 内核全量解析", scan_errors=True) != 0:
        return 1

    smoke_out = os.path.join(TEST_PROJ, "smoke_result.txt")
    if os.path.exists(smoke_out):
        os.remove(smoke_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "Smoke.gd"],
           "4/17 契约冒烟", scan_errors=True) != 0:
        say_file(smoke_out, "Smoke 报告")
        return 1
    say_file(smoke_out, "Smoke 报告")

    # 网格子系统：受影响格判定链 + 邻接 + 取首项次序（联动物品的判定基础）
    grid_out = os.path.join(TEST_PROJ, "grid_result.txt")
    if os.path.exists(grid_out):
        os.remove(grid_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "GridSmoke.gd"],
           "5/17 网格子系统", scan_errors=True) != 0:
        say_file(grid_out, "GridSmoke 报告")
        return 1
    say_file(grid_out, "GridSmoke 报告")

    # 物品脚本：原版 Items/*.gd 转译成「直挂 CoreItem」的行为脚本。
    # 一个解析错误 = 该物品整类行为不可用，故必须零容忍。
    item_out = os.path.join(TEST_PROJ, "item_parse_result.txt")
    if os.path.exists(item_out):
        os.remove(item_out)
    if run([GODOT] + GODOT_ARGS + ["--script", "ItemParseAll.gd"],
           "6/17 物品脚本全量解析", scan_errors=True) != 0:
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
           "7/17 单例门面契约", scan_errors=True) != 0:
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
           "8/17 真实阵容端到端", scan_errors=True) != 0:
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
           "9/17 全物品逐一上场", scan_errors=True) != 0:
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
           "10/17 宝石 Socket 门面", scan_errors=True) != 0:
        say_file(gem_out, "GemFacade 报告")
        return 1
    say_file(gem_out, "GemFacade 报告")

    # ── Python 侧 11–14：闸门 1–10 验的是 **GDScript 版内核**，而这四道验的是
    #   它的 **Python 转写版**（模拟器真正跑的那个）。「GDScript 版对」不蕴含
    #    「Python 版对」—— 转写规则命中、运行时垫片语义、装配次序都可能引入偏差，
    #    而这三类都不会让闸门 1–10 变红。故这条链路需要自己的证据。
    if run([PY, os.path.join(ROOT, "tools", "check_gd_py.py")],
           "11/17 转写产物语法体检") != 0:
        return 1
    # ★ 11 的第二、三小步：语法体检只说「这堆代码能编译」，说不了「该有的代码都在」。
    #   缺口面分三类，各是一种「静默失败」：
    #     A 变量遮蔽方法 —— GDScript 里成员变量与方法分属两张表（`self.x` 与
    #       `self.x()` 可以共存），Python 只有一张表，子类 `var speed` 直接遮蔽
    #       基类 `func speed()` → 运行到那行才抛 `'float' object is not callable`。
    #     B 未映射符号 —— 转写映射表没覆盖到的全局名原样落进 Python → `NameError`。
    #       ★ 实测 `load→_load` 那条规则**从写下起一次都没命中过**（判据依赖已被
    #         mask 掉的引号），垫片 `_rt._load` 因此一直是死代码。
    #     C 整行丢失 —— GD 里赋过值、Python 产物里连名字都没有。既没撞名也没引用
    #       未定义符号，A/B 都抓不到。实测 `find_block_end` 按缩进判块结束，多行
    #       字面量的 `}` 写在第 0 列 → `damageSource = ...` 整行被丢。
    if run([PY, os.path.join(ROOT, "tools", "scan_translit_gaps.py")],
           "11/17 转写缺口扫描（撞名 / 未映射 / 丢行）") != 0:
        return 1
    # ★ 上一步是「0 命中即通过」，故必须配正对照 —— 否则扫描器坏掉时，
    #   它和「全库干净」输出得一模一样（本项目已经栽过两次，见工具注释）。
    if run([PY, os.path.join(ROOT, "tools", "check_scan_gaps.py")],
           "11/17 缺口扫描正对照（删 1 行须报出）") != 0:
        return 1
    if run([PY, os.path.join(ROOT, "tools", "verify_godot_rng.py")],
           "12/17 RNG 与 Godot 3.6 逐位对齐") != 0:
        return 1
    # 13：Python 版内核跑同 56 局，与闸门 8 **刚写出**的基准逐字符对照。
    # ★ 必须排在闸门 8 之后：这样基准与本次内核同源同版本，不是拿一份来历不明的
    #   历史文件当判据（历史文件可能是旧内核产的，用它对照只会自证）。
    if run([PY, os.path.join(ROOT, "tools", "run_gd_py.py")],
           "13/17 Python 版内核端到端（56 局 vs Godot 基准）") != 0:
        return 1
    # 14：模拟器内核**经生产装配路径**复跑同 56 局。
    # ★ 13 验的是「驱动器里的装配」（tools/run_gd_py.py），14 验的是「模拟器真正
    #   用的那条装配」（simulator/gd_core_engine.py）。两者是同一次序的两份实现，
    #   任一份写歪都只会在自己那道上变红 —— 实测抓到过一次：occupied 由「已平移的
    #   collision」再算，等于平移两次，第 n 列落成 2n 列，物品相邻联动全错，
    #   而闸门 13 全绿。
    if run([PY, os.path.join(ROOT, "tools", "check_gd_core_engine.py")],
           "14/17 模拟器内核接入一致性（56 局 vs Godot 基准）") != 0:
        return 1
    # ★ 15 是唯一**跨两侧**的闸门：它拿门 8 落下的 GDScript 事件轨迹
    #   （gd_core_test/event_trace.txt）与门 13 落下的 Python 事件轨迹
    #   （output/py_event_trace.txt）逐条比对，故必须排在这两者之后。
    if run([PY, os.path.join(ROOT, "tools", "compare_events.py")],
           "15/17 逐事件对照（4053 条事件，须 0 值差异）") != 0:
        return 1

    # ★ 16 是里程碑 ⑥ 的收尾闸门：`verify_cooldowns` 等价校验。
    #   它与其他闸门都不同 —— **两半都在同一个工具里**：
    #     A 静态半边：把 gd_core/CoreItem.gd 与 decompiled_full/Items/Item.gd 的
    #       冷却路径逐函数规范化后逐行对照（27 对函数 / 99 行相等 / 0 行未归因）。
    #       差异必须落进「已声明映射」「已声明剥离」「内核新增」三类台账，
    #       落不进去即 FAIL；台账项 0 命中同样 FAIL（表笔没接上）。
    #     B 动态半边：读门 9 落下的 cooldown_battle_result.txt（303 件带冷却物品、
    #       逐帧轮询），验证 CoreItem.physicsTick 那一行本身
    #       （`triggerTime -= δ × getSpeed()`，22.8 万帧、0 违背），
    #       加抖动指纹 `iterationCooldown / getCooldown() ∈ [0.95, 1.05]`。
    #   为什么 A、B 缺一不可：A 只说「这行照抄了原版」，说不了「跑起来真是这么算的」；
    #   B 只说「跑起来是这么算的」，说不了「算的是原版那一行」。二者合起来才是
    #   里程碑 ⑥ 要的「等价」。
    #   ★ 必须排在门 9 之后：B 的数据源是门 9 的产物（工具会核对产物比内核新，
    #     陈旧即拒绝给旧内核背书）。
    if run([PY, os.path.join(ROOT, "tools", "verify_cooldowns_gd.py")],
           "16/17 冷却等价校验（A 逐行对照 + B 逐帧恒等式）") != 0:
        return 1

    # ★ 17 补的是**覆盖缺口**，不是新能力：门 9 把 517 件物品逐一带上
    #   GDScript 侧内核的场，而门 13/14 只跑 8 套阵容的 56 局 —— 于是 Python 侧
    #   （模拟器真正跑的那一份）**从未把全部物品过一遍**。代价是实测的：
    #   19 件物品在模拟器里一用就崩，而整条流水线全绿、一行红都不报。
    #   缺口六类（件间有重叠）：`call_deferred` 未映射 8 件 / `typeof`+`TYPE_VECTOR2`
    #   未提供 12 件（棋类）/ 变量名遮蔽基类方法 4 件（`speed` 撞 `CoreItem.speed()`）
    #   / `tr` 未提供 3 件 / `PCG32.randi` 缺失 1 件 / 装配期空值 1 件。
    #   ★ 它与门 9 是**同一次序的两侧实现**：只验一侧，另一侧就是盲区。
    #   ★ 排最后：517 场是全部闸门里最慢的一道，且不产出下游要用的文件。
    if run([PY, os.path.join(ROOT, "tools", "check_gd_py_items.py")],
           "17/17 Python 侧全物品逐一上场（517 件，须零异常）") != 0:
        return 1

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

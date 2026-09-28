# -*- coding: utf-8 -*-
"""battle_simulator.py — 战斗模拟器 GUI 入口（PyInstaller 打包目标）

运行:
    python battle_simulator.py              # 开发态 GUI
    BackpackSimulator.exe                   # 冻结态 GUI（lineups/ 放在 exe 同目录）
    BackpackSimulator.exe --selftest        # 冻结态自检（不开窗口，只跑内核并落报告）

为什么要有 --selftest
====================
三个战斗内核（engine/ / simulator/ / gd_core）在 `simulate._get_combat_engine` 里
**都是延迟导入**的，`gd_core_py` 更是延迟到 `GDCoreEngine.kernel()` 才 import。于是
「打包漏了某个子包 / 漏了 assets 数据」这件事在 GUI 启动时**完全看不出来** ——
窗口正常弹出、示例阵容正常列出，点「开始战斗」才炸。

`--selftest` 就是那条不依赖界面的验收入口：三个内核各真打一场，把结论写到 exe
同目录的 `selftest_report.txt`，并用**退出码**表态。`--windowed` 打包下 stdout
不可见，故结论以报告文件为准。

用法（冻结态）:
    BackpackSimulator.exe --selftest ; echo $?
"""
import sys
import os

# 确保仓库根目录在 path 中（开发态直接运行本脚本时）
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))


def _app_dir() -> str:
    if getattr(sys, 'frozen', False):
        return os.path.dirname(os.path.abspath(sys.executable))
    return os.path.dirname(os.path.abspath(__file__))


def _pick_lineups(app_dir: str):
    """挑两套阵容：优先固定示例，缺了就按名字排序取前两套。"""
    import glob
    d = os.path.join(app_dir, 'lineups')
    want = [os.path.join(d, 'lineup_armor_wall.json'),
            os.path.join(d, 'lineup_dagger_swarm.json')]
    if all(os.path.exists(p) for p in want):
        return want
    got = sorted(glob.glob(os.path.join(d, '*.json')))
    return got[:2] if len(got) >= 2 else []


def _write(app_dir, lines, fails):
    if fails:
        lines.append("")
        for f in fails:
            lines.append("SELFTEST: FAIL  " + str(f))
        lines.append("SELFTEST: FAIL (%d 项)" % len(fails))
    else:
        lines.append("")
        lines.append("SELFTEST: PASS")
    text = "\n".join(lines) + "\n"
    try:
        path = os.path.join(app_dir, 'selftest_report.txt')
        with open(path, 'w', encoding='utf-8') as f:
            f.write(text)
        text += "\n（报告已写到 %s）\n" % path
    except Exception:                             # noqa: BLE001
        pass
    try:
        sys.stdout.write(text)
        sys.stdout.flush()
    except Exception:                             # noqa: BLE001
        pass


def selftest() -> int:
    app_dir = _app_dir()
    out = []
    fails = []

    def say(s):
        out.append(s)

    say("BackpackSimulator 自检报告")
    say("frozen=%s" % bool(getattr(sys, 'frozen', False)))
    say("app_dir=%s" % app_dir)
    say("python=%s" % sys.version.replace("\n", " "))
    try:
        from simulator.simulate import ENGINES, simulate_once, DEFAULT_ENGINE
        from simulator.data import load_items, load_characters
    except Exception as exc:                      # noqa: BLE001
        import traceback
        say("加载 simulator 失败：%r" % exc)
        say(traceback.format_exc())
        _write(app_dir, out, ["simulator 导入失败：%r" % exc])
        return 1

    say("内核清单：%s（默认 %s）" % (", ".join(ENGINES), DEFAULT_ENGINE))

    paths = _pick_lineups(app_dir)
    if len(paths) < 2:
        say("找不到可用阵容（需要 lineups/ 下至少 2 个 json）")
        _write(app_dir, out, ["无可用阵容"])
        return 1
    say("自检阵容：%s vs %s" % (os.path.basename(paths[0]),
                               os.path.basename(paths[1])))

    try:
        item_db = load_items()
        char_db = load_characters()
        say("物品库 %d 件 / 角色库 %d 个" % (len(item_db), len(char_db)))
    except Exception as exc:                      # noqa: BLE001
        import traceback
        say("数据加载失败：%r" % exc)
        say(traceback.format_exc())
        _write(app_dir, out, ["数据加载失败：%r" % exc])
        return 1

    for name in ENGINES:
        try:
            eng = simulate_once(paths[0], paths[1], item_db, char_db,
                                seed=20260923 + 101, max_time=180.0, engine=name)
            s = eng.summary()
            ev = eng.log.to_dict() or []
            txt = eng.log.to_text("zh") or ""
            rj = eng.result_json()
            say("")
            say("[%s] OK" % name)
            say("   胜负=%s 原因=%s 时长=%.2fs  玩家 HP %s/%s  对手 HP %s/%s"
                % (s['winner'], s['reason'], s['time'],
                   s['player']['hp'], s['player']['max_hp'],
                   s['opponent']['hp'], s['opponent']['max_hp']))
            say("   事件 %d 条 / 日志文本 %d 字符 / result_json.version=%s"
                % (len(ev), len(txt), rj.get('version')))
            if not ev:
                fails.append("%s 事件流为空（日志出口没接上）" % name)
            if not txt:
                fails.append("%s 人类可读日志为空" % name)
        except Exception as exc:                  # noqa: BLE001
            import traceback
            say("")
            say("[%s] FAIL %r" % (name, exc))
            say(traceback.format_exc())
            fails.append("%s: %r" % (name, exc))

    if 'gd_core' in ENGINES:
        try:
            from simulator.gd_core_engine import runtime_data, kernel
            d = runtime_data()
            kernel()
            c = d['counts']
            say("")
            say("[gd_core 数据面] 物品库 %d / 可装配 %d / 无脚本 %d / 阵容 %d"
                % (c['db_items'], c['playable_items'], c['unplayable_items'],
                   c['lineups']))
        except Exception as exc:                  # noqa: BLE001
            import traceback
            say("[gd_core 数据面] FAIL %r" % exc)
            say(traceback.format_exc())
            fails.append("gd_core 运行时数据不可读：%r" % exc)

    _write(app_dir, out, fails)
    return 1 if fails else 0


def main():
    if '--selftest' in sys.argv[1:]:
        raise SystemExit(selftest())
    from simulator.gui import main as gui_main
    gui_main()


if __name__ == '__main__':
    main()

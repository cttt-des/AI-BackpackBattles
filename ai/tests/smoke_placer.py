# -*- coding: utf-8 -*-
"""smoke_placer.py — ai/placer.py 冒烟测试（占位保持重排 + 引擎在环语义）

被测语义（ai/placer.py 文件头「语义基线 / 动作空间 / 硬性规则 / 引擎在环」）
==========================================================================
* 输入阵容的**每件物品都必须出现在输出里**：候选物品多重集（含每件的 id）
  与输入严格一致——不丢弃、不新增、不做成员关系推断、不降级；宝石全局
  多重集守恒且只落在带空 socket 的物品上；
* **总占格集合不变**：候选的占位多重集（每件物品旋转后 collision 绝对格集）
  与输入逐格一致（等价于每格被占次数一致、重叠结构不变）；
* 候选过**引擎装配探针**：GDCoreEngine 实测装配数与原阵容相等；
* **引擎在环**：最终 top-k 按引擎实测胜率重排（--verify-seeds seeds/候选，
  每局模拟前 reset_kernel_state）；stdout 每候选一行
  `CAND <rank> <proxyWinRate> <engineWinRate>` + 一行 `BASE <engineWinRate>`；
* 引擎对照（③）只报告，不据此判 PASS/FAIL。

⚠ 上一轮把『根 20 件/袋内 34 件』写死成期望、把「平铺实录必须报错退出」
  和「降级后剩几件」固化成验收标准——那是在给降级行为背书，这类断言已
  **全部删除**。本版所有期望值都从**输入 JSON 独立重算**（ai/encoding 的
  几何是 simulator/grid.py 的已验证镜像，见 ai/tests/test_encoding.py），
  与 placer 内部状态异源；不写死任何实录的件数/构成/胜率。

流程
====
测试①（主流程，任务指定实录 CombatLog_20261001_221048_R19_Loss——引擎可跑，
Player 54 件全为根物品、原布局本身重叠）：placer 全流程后
  校验⓪ stdout 结构：CAND/BASE 行与 JSON 候选（rank/两胜率）逐位一致、
    JSON == ai/placer_out.json；最终 top-k 顺序按引擎实测胜率降序
    （engine_winrate=null 只能垫底）。
  校验① 每个候选：物品多重集 / 宝石全局多重集 / in 承载结构 == 输入；
    占位多重集与每格被占次数 == 输入原布局；宝石数 ≤ socket 数。
  校验② 引擎装配探针独立复核：原阵容 vs 每个候选各构造一次 GDCoreEngine，
    实测装配数与装配 id 多重集逐位一致。
  校验③ 引擎实测原阵容 vs top-1 候选各 20 个 seed（同 seed 配对），在 stdout
    报告两者胜率作对照——**只报告，不据此判 PASS/FAIL**。

测试②（显式 `in` 合成阵容）：成员关系只来自显式 `in` 且原样保留（不推断、
  不改写），⓪/多重集/占位/探针校验同①；每候选引擎 3 seeds 不报错。

测试③（不可装配物品实录 CombatLog_20261001_221856_R19_Loss——Player 侧装配
  抛 _MissingItem）：placer 必须**报错退出**且不产出任何候选——按新语义
  placer 不跳过、不降级任何物品（有物品被静默丢弃才会"照常成功"）。

用法：python ai/tests/smoke_placer.py [--log <combat_log 目录名>] [--iters 500]
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from collections import Counter
from typing import List, Optional, Tuple

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.dirname(os.path.dirname(_HERE))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

# 任务指定的冒烟实录（引擎可跑：实测 Player 装配 54 件 / Opponent 45 件）
NAMED_LOG = "CombatLog_20261001_221048_R19_Loss"
# Player 侧含 GoldCounter（引擎装配抛 _MissingItem）——测 placer 的不降级失败路径
BAD_LOG = "CombatLog_20261001_221856_R19_Loss"


def log_paths(name: str) -> Tuple[str, str, str]:
    d = os.path.join(_REPO, "dist", "output", "combat_logs", name)
    return (os.path.join(d, name + ".Player.json"),
            os.path.join(d, name + ".Opponent.json"), d)


def run_placer(player: str, opp: str, iters: int, topk: int, out_path: str,
               timeout: int) -> Tuple[int, str, str]:
    cmd = [sys.executable, os.path.join(_REPO, "ai", "placer.py"),
           "--lineup", player, "--opponent", opp,
           "--iters", str(iters), "--topk", str(topk), "--out", out_path]
    print("[smoke] run:", " ".join(cmd))
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=_REPO,
                       timeout=timeout)
    return r.returncode, r.stdout, r.stderr


# ─────────────────── stdout 结构校验（校验⓪，引擎在环口径） ───────────────────

_CAND_RE = re.compile(r"^CAND (\d+) (\d+\.\d{4}) (n/a|\d+\.\d{4})$")


def split_stdout(out: str, tag: str) -> Tuple[List[str], Optional[dict]]:
    """placer stdout → (CAND/BASE 行, JSON dict)。

    CAND/BASE 行在前，JSON 从第一个 '{' 起；探针/实测期间引擎的零星 print
    已被 placer 重定向，不会混入 stdout。解析失败返回 (report, None)。"""
    report = [ln for ln in out.strip().splitlines()
              if ln.startswith(("CAND ", "BASE "))]
    try:
        data = json.loads(out[out.index("{"):])
    except (ValueError, json.JSONDecodeError) as e:
        print("%s FAIL: stdout 无合法 JSON: %s" % (tag, e))
        return report, None
    if not isinstance(data, dict):
        print("%s FAIL: stdout JSON 不是对象" % tag)
        return report, None
    return report, data


def check_result_shape(result: Optional[dict], report: List[str], topk: int,
                       tag: str) -> bool:
    """校验⓪：CAND/BASE 行与 JSON 候选逐位一致 + 最终顺序按引擎实测胜率降序。"""
    good = True
    if not isinstance(result, dict):
        print("%s FAIL: stdout JSON 缺失或不是对象" % tag)
        return False
    cands = result.get("candidates") or []
    if len(cands) != topk:
        good = False
        print("%s FAIL: 候选数 %d ≠ topk %d" % (tag, len(cands), topk))
    # 最终顺序：engine_winrate 降序，None（实测报错/--verify-seeds 0）只能垫底
    eng = [c.get("engine_winrate") for c in cands]
    for a, b in zip(eng, eng[1:]):
        if a is None or (b is not None and b > a):
            good = False
            print("%s FAIL: 候选未按 engine_winrate 降序（None 只能垫底）: %s"
                  % (tag, eng))
            break
    # CAND 行：与 JSON 候选（rank/proxy/engine）逐位一致
    cand_lines = [ln for ln in report if ln.startswith("CAND ")]
    if len(cand_lines) != len(cands):
        good = False
        print("%s FAIL: CAND 行数 %d ≠ 候选数 %d" % (tag, len(cand_lines), len(cands)))
    for ln, c in zip(cand_lines, cands):
        m = _CAND_RE.match(ln)
        if not m:
            good = False
            print("%s FAIL: CAND 行格式不符: %r" % (tag, ln))
            continue
        rank, proxy, eng_s = int(m.group(1)), m.group(2), m.group(3)
        want_eng = ("n/a" if c.get("engine_winrate") is None
                    else "%.4f" % c["engine_winrate"])
        if (rank != c.get("rank") or proxy != "%.4f" % c.get("proxy_winrate", float("nan"))
                or eng_s != want_eng):
            good = False
            print("%s FAIL: CAND 行 %r 与候选 JSON 不一致（期望 rank=%s proxy=%.4f engine=%s）"
                  % (tag, ln, c.get("rank"), c.get("proxy_winrate"), want_eng))
    # BASE 行：与 meta.baseline_engine_winrate 一致（--verify-seeds 0 时双方皆无）
    base_lines = [ln for ln in report if ln.startswith("BASE ")]
    meta_base = (result.get("meta") or {}).get("baseline_engine_winrate")
    if meta_base is None:
        if base_lines:
            good = False
            print("%s FAIL: meta.baseline_engine_winrate 缺失却有 BASE 行: %s"
                  % (tag, base_lines))
    elif len(base_lines) != 1 or base_lines[0] != "BASE %.4f" % meta_base:
        good = False
        print("%s FAIL: BASE 行 %s 与 meta.baseline_engine_winrate=%s 不一致"
              % (tag, base_lines, meta_base))
    if good:
        print("%s ⓪通过 ✓  CAND/BASE 行与 JSON 逐位一致，最终序按引擎实测胜率降序" % tag)
    return good


# ─────────────────── 测试② 的显式 in 合成阵容（确定性、全可装配） ───────────────────
# 9 个根物品 + 1 个显式 in 袋内件（Acorn Collar → Leather Bag）+ 1 颗宝石。
# 期望值不写死：全部由 lineup_facts 从这份 JSON 独立重算。
SYNTH_ITEMS = [
    {"id": "Leather Bag",       "at": [0, 0], "r": 0},                 # 容器根, 占 2×2
    {"id": "Bow and Arrow",     "at": [0, 3], "r": 0},
    {"id": "Hero Sword",        "at": [0, 6], "r": 0},
    {"id": "Whetstone",         "at": [2, 6], "r": 0},
    {"id": "Acorn Ace",         "at": [3, 6], "r": 0},
    {"id": "Amethyst Egg",      "at": [4, 6], "r": 0,
     "gems": ["Chipped Ruby"]},                                        # sockets 1
    {"id": "Toad",              "at": [5, 6], "r": 0},
    {"id": "Fanny Pack",        "at": [2, 0], "r": 0},                 # 容器根
    {"id": "Corrupted Crystal", "at": [2, 3], "r": 0},
    {"id": "Acorn Collar",      "at": [0, 0], "r": 0, "in": 0},        # 显式 in 袋内件
]


def synth_lineup(character: str) -> dict:
    return {"version": 4, "name": "smoke-synthetic", "character": character,
            "round": 19, "grid": [7, 9],
            "class_modifiers": {}, "health_override": None, "storage": [],
            "items": [dict(e) for e in SYNTH_ITEMS]}


# ─────────────────── 期望值：从输入 JSON 独立重算（与 placer 异源） ───────────────────

def lineup_facts(lu: dict, item_db: dict) -> dict:
    """阵容 JSON → {ids, gems, struct, occ, cellcnt}。

    * ids：物品 id 多重集（含每件的 id）；
    * gems：宝石全局多重集；
    * struct：排序后的 (id, 承载者 id 或 None) 序列——显式 `in` 承载结构的
      顺序无关指纹（不推断、不改写的验收口径）；
    * occ：占位多重集（每件物品旋转后 collision 绝对格集 → 计数）；
    * cellcnt：每格被占次数（重叠结构）。
    几何用 ai/encoding.item_geometry——simulator/grid.py 的已验证镜像
    （ai/tests/test_encoding.py 逐物品对拍）；对 placer 的内部状态零依赖。
    """
    from ai.encoding import _flatten as enc_flatten, _items_map, item_geometry
    im = _items_map(item_db)
    flat = enc_flatten(lu)
    ids = Counter(e["id"] for e in flat)
    gems = Counter(g for e in flat for g in e["gems"])
    struct = sorted((e["id"],
                     flat[e["parent"]]["id"] if e["parent"] is not None else None)
                    for e in flat)
    occ: Counter = Counter()
    cellcnt: Counter = Counter()
    for e in flat:
        g = item_geometry(e["id"], e["rotation"], im, e["row"], e["col"])
        if g is None:                     # 库外物品按 1×1 占位（与引擎兜底一致）
            cells = frozenset({(e["row"], e["col"])})
        else:
            cells = frozenset(tuple(c) for c in g["collision"])
        occ[cells] += 1
        cellcnt.update(cells)
    return {"ids": ids, "gems": gems, "struct": struct, "occ": occ,
            "cellcnt": cellcnt, "flat": flat}


def check_candidate(c: dict, exp: dict, item_db: dict) -> List[str]:
    """校验①：候选 vs 输入期望。返回违规描述列表（空 = 通过）。"""
    errs: List[str] = []
    got = lineup_facts(c["lineup"], item_db)
    if got["ids"] != exp["ids"]:
        errs.append("物品多重集不一致: 缺 %s 多 %s"
                    % (dict(exp["ids"] - got["ids"]), dict(got["ids"] - exp["ids"])))
    if got["gems"] != exp["gems"]:
        errs.append("宝石全局多重集不一致: 缺 %s 多 %s"
                    % (dict(exp["gems"] - got["gems"]), dict(got["gems"] - exp["gems"])))
    if got["struct"] != exp["struct"]:
        miss = [x for x in exp["struct"] if x not in got["struct"]]
        extra = [x for x in got["struct"] if x not in exp["struct"]]
        errs.append("in 承载结构被改写: 缺 %s 多 %s" % (miss[:3], extra[:3]))
    if got["occ"] != exp["occ"]:
        miss = exp["occ"] - got["occ"]
        extra = got["occ"] - exp["occ"]
        errs.append("占位多重集不一致（总占格集合漂移）: 缺 %d 种 多 %d 种"
                    % (sum(miss.values()), sum(extra.values())))
    if got["cellcnt"] != exp["cellcnt"]:
        diff = {cell: (exp["cellcnt"][cell], got["cellcnt"][cell])
                for cell in set(exp["cellcnt"]) | set(got["cellcnt"])
                if exp["cellcnt"][cell] != got["cellcnt"][cell]}
        errs.append("每格被占次数不一致: %s" % dict(list(diff.items())[:4]))
    # 宝石容量：只落在带 socket 且未超容量的物品上
    from ai.encoding import _items_map
    im = _items_map(item_db)
    for e in got["flat"]:
        entry = im.get(e["id"]) or {}
        try:
            sockets = int((entry.get("descr") or {}).get("sockets", 0) or 0)
        except (TypeError, ValueError):
            sockets = 0
        if len(e["gems"]) > sockets:
            errs.append("物品 %s 宝石 %d 颗 > socket %d" % (e["id"], len(e["gems"]), sockets))
    if c.get("assembled_items") != exp["baseline_assembled"]:
        errs.append("placer 自报装配数 %s ≠ 基线 %s"
                    % (c.get("assembled_items"), exp["baseline_assembled"]))
    return errs


# ─────────────────── 引擎侧独立复核（装配探针 + 实跑） ───────────────────

def engine_assembly(player_v4: dict, opp_v3: dict, seed: int, tmpdir: str
                    ) -> Tuple[int, Counter, str]:
    """装配探针（只构造不跑局）：返回 (引擎装配物品数, 装配 id 多重集, 错误串)。"""
    from simulator.gd_core_engine import GDCoreEngine
    from simulator.lineup import load_lineup
    pfile = os.path.join(tmpdir, "player_probe.json")
    with open(pfile, "w", encoding="utf-8") as f:
        json.dump(player_v4, f, ensure_ascii=False)
    try:
        player_v3 = load_lineup(pfile)
        eng = GDCoreEngine(player_v3, opp_v3, {}, {}, seed=seed)
        return len(eng.player_items), Counter(it.key for it in eng.player_items), ""
    except Exception as exc:                             # noqa: BLE001
        return -1, Counter(), "%s: %s" % (type(exc).__name__, exc)


def engine_run(player_v4: dict, opp_v3: dict, seeds: List[int], tmpdir: str
               ) -> Tuple[object, int, str]:
    """实跑：返回 (胜率或 None, 局数, 信息串)。"""
    from simulator.gd_core_engine import GDCoreEngine
    from simulator.lineup import load_lineup
    from ai.kernel_reset import reset_kernel_state
    pfile = os.path.join(tmpdir, "player_run.json")
    with open(pfile, "w", encoding="utf-8") as f:
        json.dump(player_v4, f, ensure_ascii=False)
    player_v3 = load_lineup(pfile)
    wins, n, fielded, err = 0, 0, set(), ""
    for seed in seeds:
        try:
            reset_kernel_state()   # 局前清内核进程级全局态（ai/kernel_reset.py）
            eng = GDCoreEngine(player_v3, opp_v3, {}, {}, seed=seed)
            fielded.add(len(eng.player_items))
            eng.run()
            wins += 1 if eng.player_wins() else 0
            n += 1
        except Exception as exc:                         # noqa: BLE001
            err = "%s: %s" % (type(exc).__name__, exc)
            break
    wr = (wins / n) if n else None
    return wr, n, err or ("fielded=%s" % sorted(fielded))


# ─────────────────────────── 主流程 ───────────────────────────

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--log", default=NAMED_LOG, help="测试① 实录目录名（须引擎可跑）")
    ap.add_argument("--iters", type=int, default=500)
    ap.add_argument("--topk", type=int, default=3)
    ap.add_argument("--eval-seeds", type=int, default=20, help="测试③ 每方 seed 数")
    ap.add_argument("--sanity-seeds", type=int, default=3, help="测试② 每候选 seed 数")
    ap.add_argument("--seed", type=int, default=101, help="首个引擎 seed（依次 +1）")
    args = ap.parse_args()

    from ai import model as M
    item_db = M.load_item_db()
    ok = True
    out_path = os.path.join(_REPO, "ai", "placer_out.json")
    tmpdir = tempfile.mkdtemp(prefix="smoke_placer_")

    # ════ 测试①：任务指定实录（平铺、允许重叠）→ placer 全流程 ════
    player, opp, _d = log_paths(args.log)
    print("[smoke] 测试① 平铺实录 %s（引擎可跑，原布局允许重叠）→ 重摆 Player 阵容"
          % args.log)
    code, out, err = run_placer(player, opp, args.iters, args.topk, out_path, 3600)
    if code != 0:
        last = [ln for ln in (err or "").strip().splitlines() if ln][-1:] or [""]
        print("[smoke] FAIL: 测试① placer 退出码 %d: %s" % (code, last[0]))
        return 1
    report, result = split_stdout(out, "[smoke] 测试①")
    if result is None:
        return 1
    with open(out_path, encoding="utf-8") as f:
        result_file = json.load(f)
    if result != result_file:
        ok = False
        print("[smoke] FAIL: stdout JSON 与 %s 不一致" % out_path)
    else:
        print("[smoke] 测试① placer OK（stdout=CAND/BASE 行 + JSON，与 %s 一致；iters=%d）"
              % (out_path, args.iters))
    ok = check_result_shape(result, report, args.topk, "[smoke] 测试①") and ok

    # 期望值：从输入 JSON 独立重算（不写死实录件数）
    with open(player, encoding="utf-8") as f:
        base_raw = json.load(f)
    exp = lineup_facts(base_raw, item_db)
    print("[smoke] 期望（从输入独立重算）：物品 %d 件（%d 种 id）/ 宝石 %d 颗 / "
          "占位 %d 种 / 显式 in 件 %d"
          % (sum(exp["ids"].values()), len(exp["ids"]), exp["gems"].total(),
             len(exp["occ"]), sum(1 for e in exp["flat"] if e["parent"] is not None)))

    # 引擎装配基线（校验②的原阵容侧，先行实测供校验①引用）
    from simulator.lineup import load_lineup
    opp_v3 = load_lineup(opp)
    n_orig, ids_orig, err0 = engine_assembly(base_raw, opp_v3, args.seed, tmpdir)
    exp["baseline_assembled"] = n_orig
    if err0:
        ok = False
        print("[smoke] FAIL: 原阵容引擎装配失败: %s" % err0)
    else:
        print("[smoke] 原阵容引擎装配基线：%d 件" % n_orig)

    # 校验①：逐候选硬性规则
    for c in result["candidates"]:
        errs = check_candidate(c, exp, item_db)
        if errs:
            ok = False
            print("[smoke] FAIL: 候选 #%d ①%s" % (c["rank"], errs))
        else:
            print("[smoke] 候选 #%d ①通过 ✓  代理胜率=%.4f  物品 %d 件全部保留、"
                  "占位多重集与原布局逐格一致"
                  % (c["rank"], c["proxy_winrate"], c["n_items"]))

    # 校验②：引擎装配探针独立复核（原 vs 每候选：数量 + 装配 id 多重集逐位一致）
    for c in result["candidates"]:
        n_ai, ids_ai, err1 = engine_assembly(c["lineup"], opp_v3, args.seed, tmpdir)
        if err1:
            ok = False
            print("[smoke] FAIL: 候选 #%d ②引擎装配失败: %s" % (c["rank"], err1))
            continue
        if n_ai != n_orig or ids_ai != ids_orig:
            ok = False
            print("[smoke] FAIL: 候选 #%d ②装配不一致: 原 %d 件 %s vs 候选 %d 件 %s"
                  % (c["rank"], n_orig, dict(ids_orig - ids_ai), n_ai,
                     dict(ids_ai - ids_orig)))
        else:
            print("[smoke] 候选 #%d ②通过 ✓  引擎实测装配 %d 件 == 原阵容，"
                  "装配 id 多重集逐位一致" % (c["rank"], n_ai))

    # 校验③：引擎实测原阵容 vs top-1（20 seeds，同 seed 配对，只报告不判定）
    if not err0:
        eval_seeds = [args.seed + i for i in range(args.eval_seeds)]
        base_wr, base_n, base_info = engine_run(base_raw, opp_v3, eval_seeds, tmpdir)
        top1 = result["candidates"][0]
        top_wr, top_n, top_info = engine_run(top1["lineup"], opp_v3, eval_seeds, tmpdir)
        print("[smoke] ③引擎对照（%d seeds，同 seed 配对，只报告不判定）：" % args.eval_seeds)
        print("[smoke]   原阵容: 胜率 %s（%d 局，%s）"
              % ("n/a" if base_wr is None else "%.3f" % base_wr, base_n, base_info))
        print("[smoke]   top-1 重摆候选（rank %d，代理胜率 %.4f）: 胜率 %s（%d 局，%s）"
              % (top1["rank"], top1["proxy_winrate"],
                 "n/a" if top_wr is None else "%.3f" % top_wr, top_n, top_info))

    # ════ 测试②：显式 in 合成阵容 → 成员结构原样 + 同套校验 ════
    print("[smoke] 测试② 显式 in 合成阵容（成员关系只来自显式 in，原样保留）")
    base_synth = synth_lineup("Ranger")
    synth_path = os.path.join(tmpdir, "synth.Player.json")
    with open(synth_path, "w", encoding="utf-8") as f:
        json.dump(base_synth, f, ensure_ascii=False)
    code, out, err = run_placer(synth_path, opp, args.iters, args.topk,
                                os.path.join(tmpdir, "synth_out.json"), 3600)
    if code != 0:
        last = [ln for ln in (err or "").strip().splitlines() if ln][-1:] or [""]
        ok = False
        print("[smoke] FAIL: 测试② placer 退出码 %d: %s" % (code, last[0]))
    else:
        report2, result2 = split_stdout(out, "[smoke] 测试②")
        all_ok = check_result_shape(result2, report2, args.topk, "[smoke] 测试②")
        if result2 is None:
            ok = False
            result2 = {"candidates": []}
        exp2 = lineup_facts(base_synth, item_db)
        n2, ids2, err02 = engine_assembly(base_synth, opp_v3, args.seed, tmpdir)
        exp2["baseline_assembled"] = n2
        if err02:
            all_ok = False
            ok = False
            print("[smoke] FAIL: 测试② 原阵容引擎装配失败: %s" % err02)
        for c in result2["candidates"]:
            errs = check_candidate(c, exp2, item_db)
            if errs:
                all_ok = False
                print("[smoke] FAIL: 测试② 候选 #%d ①%s" % (c["rank"], errs))
                continue
            n_ai, ids_ai, err1 = engine_assembly(c["lineup"], opp_v3, args.seed, tmpdir)
            if err1:
                all_ok = False
                print("[smoke] FAIL: 测试② 候选 #%d ②引擎装配失败: %s" % (c["rank"], err1))
                continue
            if n_ai != n2 or ids_ai != ids2:
                all_ok = False
                print("[smoke] FAIL: 测试② 候选 #%d ②装配不一致: 原 %d 件 %s vs "
                      "候选 %d 件 %s" % (c["rank"], n2, dict(ids2 - ids_ai),
                                         n_ai, dict(ids_ai - ids2)))
                continue
            print("[smoke] 测试② 候选 #%d ✓  代理胜率=%.4f  多重集/占位/in 结构一致、"
                  "引擎装配 %d 件" % (c["rank"], c["proxy_winrate"], n_ai))
            wr, n, info = engine_run(c["lineup"], opp_v3,
                                     [args.seed + i for i in range(args.sanity_seeds)],
                                     tmpdir)
            if wr is None:
                all_ok = False
                print("[smoke] FAIL: 测试② 候选 #%d 引擎报错: %s" % (c["rank"], info))
            else:
                print("[smoke] 测试② 候选 #%d ✓  引擎 %d seeds 无错误（胜率 %.2f）"
                      % (c["rank"], n, wr))
        if all_ok:
            print("[smoke] 测试② 通过 ✓（显式 in 结构原样、占位/多重集守恒、探针一致）")
        else:
            ok = False

    # ════ 测试③：含不可装配物品的实录 → placer 报错退出、不产出候选 ════
    print("[smoke] 测试③ 不可装配实录 %s（Player 侧装配抛 _MissingItem）→ 必须报错退出"
          % BAD_LOG)
    bplayer, bopp, _bd = log_paths(BAD_LOG)
    code, out, err = run_placer(bplayer, bopp, args.iters, args.topk,
                                os.path.join(tmpdir, "bad.json"), 1200)
    tail = [ln for ln in (err or "").strip().splitlines() if ln][-1:]
    msg = tail[0] if tail else "(无 stderr)"
    if code == 0:
        ok = False
        print("[smoke] FAIL: 不可装配实录 placer 却退出码 0（疑似静默跳过/丢弃物品）")
    elif ("装配失败" not in msg) and ("装配基线" not in msg):
        ok = False
        print("[smoke] FAIL: 非零退出但信息不含「装配失败/装配基线」: %s" % msg)
    else:
        cand_like = None
        try:
            cand_like = json.loads(out)
        except (json.JSONDecodeError, ValueError):
            cand_like = None
        if isinstance(cand_like, dict) and cand_like.get("candidates"):
            ok = False
            print("[smoke] FAIL: 基线都建不起来却输出了 %d 个候选（疑似丢弃物品后照常跑）"
                  % len(cand_like["candidates"]))
        else:
            print("[smoke] 测试③ 退出码 %d（预期非零）✓  无候选输出  %s" % (code, msg))

    print("[smoke] %s" % ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())

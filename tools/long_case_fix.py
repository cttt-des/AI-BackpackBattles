#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""long_case_fix.py — 长场专项验证/修复工具（与主基线完全隔离）。

## 为什么单独一个工具

语料 914 场里有 **54 场长场**（事件数爆炸：中位 6.6 MB、最高 18.4 MB / 48297 事件）。
它们被排除在夹具之外（`gd_core_test/oracle_align_cases.json` 只有 860 场），原因是
**跑得慢**，进不了每轮都要跑的主回路：单场 27-136 s，54 场串起来 ~40 分钟，
放进 `verify_oracle.py` 会把 PR 级迭代拖成小时级。

但它们**从未被验证过**——这是当前最大的覆盖空洞。本工具就干这一件事：

```
python -X utf8 tools/long_case_fix.py --list          # 1) 诊断：这 54 场是谁、多大
python -X utf8 tools/long_case_fix.py --prepare       # 2) 生成长场专属夹具（不动主夹具）
python -X utf8 tools/long_case_fix.py --run           # 3) 三腿验证（gd / py / compare）
python -X utf8 tools/long_case_fix.py --focus run894_r18   # 4) 单场深挖：首分歧定位
python -X utf8 tools/long_case_fix.py --report        # 5) 汇总：按分歧类型聚类
```

## 三条设计约束（都是踩过的坑）

1. **不动主夹具**：靠 `ORACLE_ALIGN_CASES_FILE` 给重放侧另一份夹具。
   改主夹具会污染 859/860 基线，也和别的进程抢文件。
2. **闸值按语料自动抬**：其中 9 场语料事件数 > 25000。py 腿若用默认闸 25000
   会被截断，产生**伪分歧**（`PY_NP22_REC_EV_GATE` 里那 20 场就是为此设的）。
   本工具按「语料 event_count」逐场算闸，不靠手工维护表。
3. **一进程多场**：oracle 项目启动要扫 15419 个文件（≈25 s），每场一进程是
   4.2x 的负优化（见 docs/parallel_workflow.md §2）。故按 `--batch` 成组。

## 产物（全部隔离，不碰主基线）

```
output/oracle/align_long/gdcore/     gd 腿重放产物
output/oracle/align_long/py/         py 腿产物
output/oracle/align_long/_shards/    分片清单与日志
output/oracle/long_cases.json        长场清单 + 元数据（ticks/events/bytes）
output/oracle/long_alignment.json    长场对齐报告（独立于 alignment.json）
```
"""
from __future__ import annotations

import argparse
import io
import json
import os
import subprocess
import sys
import time
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, ROOT)

import godot_headless as gh  # noqa: E402
import verify_oracle as V  # noqa: E402

#: 长场产物根（与主基线 output/oracle/align/ 完全分开）
LONG_DIR = os.path.join(ROOT, 'output', 'oracle', 'align_long')
GD_OUT = os.path.join(LONG_DIR, 'gdcore')
PY_OUT = os.path.join(LONG_DIR, 'py')
SHARD_DIR = os.path.join(LONG_DIR, '_shards')
CASES_JSON = os.path.join(LONG_DIR, 'long_cases_fixture.json')
LIST_JSON = os.path.join(ROOT, 'output', 'oracle', 'long_cases.json')
REPORT_JSON = os.path.join(ROOT, 'output', 'oracle', 'long_alignment.json')

#: 主夹具路径（只读，用来算差集）
MAIN_FIXTURE = os.path.join(ROOT, 'gd_core_test', 'oracle_align_cases.json')

#: 判定长场的阈值（与 docs 一致：事件数超 25000 的必抬闸；这里用体积+事件双判）
LONG_MIN_EVENTS = 8000
LONG_MIN_BYTES = 6 * 1024 * 1024

#: 每片至少几场（oracle 启动 ≈25s，见 docs §2）
MIN_CASES_PER_SHARD = 4

# ═══════════════════════ 1) 诊断：谁被排除了 ═══════════════════════

def _event_count_of(path: str) -> int:
    try:
        return int(json.load(io.open(path, encoding='utf-8')).get('event_count', 0))
    except Exception:  # noqa: BLE001
        return 0


def select_long_cases(only: Optional[List[str]] = None) -> List[Dict[str, Any]]:
    """语料里「不在主夹具内」的场 = 被排除的那批，附带规模元数据。

    为什么用「差集」而不是按体积阈值猜：排除清单是**生成期决定的**，
    差集才是事实来源（体积阈值只能近似）。阈值只用于标注 `is_long`。
    """
    fights = json.load(io.open(os.path.join(ROOT, 'oracle', 'fights.json'),
                               encoding='utf-8'))['cases']
    try:
        main_ids = {c['case_id'] for c in
                    json.load(io.open(MAIN_FIXTURE, encoding='utf-8'))['cases']}
    except Exception:  # noqa: BLE001
        main_ids = set()
    out = []
    for c in fights:
        cid = c['case_id']
        if main_ids and cid in main_ids:
            continue
        if only and cid not in only:
            continue
        p = os.path.join(V.FIGHTS_DIR, cid, 'events.json')
        if not os.path.exists(p):
            continue
        ev = _event_count_of(p)
        size = os.path.getsize(p)
        out.append({
            'case_id': cid,
            'seed': int(c['seed']),
            'round_id': int(c['round_id']),
            'event_count': ev,
            'bytes': size,
            'excluded': True,
            'is_long': ev >= LONG_MIN_EVENTS or size >= LONG_MIN_BYTES,
            # ★ py 腿闸值：默认 25000，语料超过就得抬（否则 py 被截断 → 伪分歧）
            'py_ev_gate': max(25000, int(ev * 1.2) + 1),
        })
    out.sort(key=lambda r: (-r['event_count'], r['case_id']))
    return out


def cmd_list(args) -> int:
    rows = select_long_cases()
    if not rows:
        print('没有「被排除」的场（主夹具已覆盖全部语料）')
        return 0
    need_gate = [r for r in rows if r['event_count'] > 25000]
    print('=== 被排除在夹具之外的场：%d 场 ===' % len(rows))
    print('其中事件数 > 25000（py 腿必须抬闸，否则伪分歧）：%d 场' % len(need_gate))
    print('合计 %.1f MB / %d 事件' % (sum(r['bytes'] for r in rows) / 1048576,
                                     sum(r['event_count'] for r in rows)))
    print()
    print('%-16s %10s %9s %8s %s' % ('case_id', 'events', 'MB', 'py闸', '备注'))
    for r in rows:
        note = []
        if r['event_count'] > 25000:
            note.append('超默认闸')
        if r['bytes'] >= LONG_MIN_BYTES:
            note.append('大体积')
        print('%-16s %10d %9.2f %8d %s' % (r['case_id'], r['event_count'],
                                           r['bytes'] / 1048576,
                                           r['py_ev_gate'], ','.join(note)))
    os.makedirs(os.path.dirname(LIST_JSON), exist_ok=True)
    with io.open(LIST_JSON, 'w', encoding='utf-8', newline='\n') as fh:
        json.dump({'tool': 'long_case_fix.py', 'count': len(rows),
                   'note': '语料中不在主夹具内的场（生成期排除，原因是运行慢）',
                   'cases': rows}, fh, ensure_ascii=False, indent=1)
        fh.write('\n')
    print()
    print('清单 -> %s' % os.path.relpath(LIST_JSON, ROOT))
    return 0


# ═══════════════════════ 2) 生成长场专属夹具 ═══════════════════════

def cmd_prepare(args) -> int:
    """从**原始** lineups.json 生成长场夹具（复用生成器的转换逻辑）。

    ★ 不能直接把 output/oracle/align/lineups/ 里的文件拷进来：那是**转换后**
      格式（backpack.items 嵌套），而夹具要的是扁平结构（items/rotation/...）。
      这里直接调 gen_fixture_from_lineup.oracle_mode，与主夹具同一套代码路径。
    ★ 绝不写主夹具：输出指向 align_long/ 下的独立文件，靠 ORACLE_ALIGN_CASES_FILE 注入。
    """
    import gen_fixture_from_lineup as G  # noqa: E402

    rows = select_long_cases()
    if args.limit:
        rows = rows[:args.limit]
    if not rows:
        print('没有长场可准备')
        return 2
    case_dirs = [os.path.join(V.FIGHTS_DIR, r['case_id']) for r in rows]
    missing = [d for d in case_dirs if not os.path.exists(os.path.join(d, 'lineups.json'))]
    if missing:
        print('缺 lineups.json 的场：%s' % ','.join(os.path.basename(d) for d in missing[:6]))
        case_dirs = [d for d in case_dirs if d not in set(missing)]
    os.makedirs(LONG_DIR, exist_ok=True)

    rc = G.oracle_mode(case_dirs, os.path.join(LONG_DIR, 'lineups'), CASES_JSON)
    if rc != 0:
        print('[prepare] 生成器返回 %s' % rc, file=sys.stderr)
        return rc

    # 生成器产出的 cases 不含闸值元数据，这里补进去（py 腿要用）
    data = json.load(io.open(CASES_JSON, encoding='utf-8'))
    gate_of = {r['case_id']: r['py_ev_gate'] for r in rows}
    for c in data['cases']:
        c['py_ev_gate'] = gate_of.get(c['case_id'], 25000)
    with io.open(CASES_JSON, 'w', encoding='utf-8', newline='\n') as fh:
        json.dump(data, fh, ensure_ascii=False)
        fh.write('\n')

    n_items = sum(len(c['player'].get('items', [])) for c in data['cases'])
    print('长场夹具 -> %s（%d 场，player 物品合计 %d 件）'
          % (os.path.relpath(CASES_JSON, ROOT), len(data['cases']), n_items))
    if not data['cases']:
        print('夹具为空（全部被生成期剔除）', file=sys.stderr)
        return 2
    return 0

# ═══════════════════════ 3) 三腿验证 ═══════════════════════

def _fixture_rows() -> Dict[str, Dict[str, Any]]:
    data = json.load(io.open(CASES_JSON, encoding='utf-8'))
    return {c['case_id']: c for c in data['cases']}


class _LongContext:
    """在**工具内部**临时接管 verify_oracle 的模块级配置，退出时原样还原。

    ★ 为什么不在 verify_oracle.py 里加"若环境变量则换夹具"的开关：
      主人明确要求长场工具独立、不改进原有对拍工具。故这里用「调用前改模块
      全局、调用后无条件还原」的方式复用它的能力，主流程源码零改动。

    接管的三项：
      · CASES_JSON          —— run_py 用它判断"该场在不在夹具内"，不换就会 skip 长场
      · PY_NP22_REC_EV_GATE —— 闸值表；长场逐场内联在夹具里（py_ev_gate）
      · GD_OUT / PY_OUT     —— 产物目录指向 align_long，不污染主基线
    """

    def __init__(self, gd_out: str, py_out: str, fixture: Dict[str, Dict[str, Any]]):
        self.gd_out = gd_out
        self.py_out = py_out
        self.fixture = fixture
        self._saved = {}

    def __enter__(self):
        self._saved = {
            'CASES_JSON': V.CASES_JSON,
            'GD_OUT': V.GD_OUT,
            'PY_OUT': V.PY_OUT,
            'GATE': dict(V.PY_NP22_REC_EV_GATE),
        }
        V.CASES_JSON = CASES_JSON
        V.GD_OUT = self.gd_out
        V.PY_OUT = self.py_out
        # 长场闸值：逐场按语料算（夹具内联 py_ev_gate），覆盖表里的默认值
        for cid, c in self.fixture.items():
            gate = c.get('py_ev_gate')
            if gate:
                V.PY_NP22_REC_EV_GATE[cid] = int(gate)
        return self

    def __exit__(self, *exc):
        V.CASES_JSON = self._saved['CASES_JSON']
        V.GD_OUT = self._saved['GD_OUT']
        V.PY_OUT = self._saved['PY_OUT']
        V.PY_NP22_REC_EV_GATE.clear()
        V.PY_NP22_REC_EV_GATE.update(self._saved['GATE'])
        return False


def cmd_run(args) -> int:
    """跑 gd 腿 + py 腿 + 比对（三步，产物全落 align_long/）。

    gd 腿：经 gh 起 Godot，用 ORACLE_ALIGN_CASES_FILE 指向长场夹具，
           用 ORACLE_ALIGN_CASES 只跑本片；按 --batch 成组摊薄启动成本。
    py  腿：直接调 V.run_py，但逐场传**按语料算出的闸值**（否则长场被截断）。
    compare：直接复用 V.compare_case（读三份 events.json 作 canonical 比对）。
    """
    if not os.path.exists(CASES_JSON):
        print('缺长场夹具：先跑 --prepare', file=sys.stderr)
        return 2
    fixture = _fixture_rows()
    ids = list(fixture.keys())
    if args.limit:
        ids = ids[:args.limit]
    if not ids:
        print('无场可跑', file=sys.stderr)
        return 2

    os.makedirs(GD_OUT, exist_ok=True)
    os.makedirs(PY_OUT, exist_ok=True)
    os.makedirs(SHARD_DIR, exist_ok=True)
    if args.force:
        import shutil
        for cid in ids:
            for d in (GD_OUT, PY_OUT):
                shutil.rmtree(os.path.join(d, cid), ignore_errors=True)
        print('[force] 已删 %d 场的长场产物' % len(ids))

    # ── gd 腿 ──
    jobs = gh.effective_jobs(len(ids), gh.auto_jobs(len(ids), args.jobs),
                             MIN_CASES_PER_SHARD)
    groups = [ids[i:i + max(1, args.batch)] for i in range(0, len(ids), args.batch)]
    # 注意：不用 os.environ 传夹具，改为在 _LongContext 里显式接管 V 的模块级配置，
    # 避免把长场口径泄漏给同进程里其它逻辑。
    print('[long] gd 腿：%d 场 -> %d 组（每组 <=%d 场），并行 %d 路'
          % (len(ids), len(groups), args.batch, jobs))
    t0 = time.time()
    specs = []
    for gi, grp in enumerate(groups):
        specs.append({
            'cmd': gh.cmd(project='gd_core_test', script='OracleAlignBattleLong.gd'),
            'tag': 'long%d' % gi,
            'env_extra': {
                'ORACLE_ALIGN_OUT': GD_OUT,
                'ORACLE_ALIGN_CASES': ','.join(grp),
                # ★ 关键：让重放侧读**长场专属夹具**，不动主夹具
                'ORACLE_ALIGN_CASES_FILE': CASES_JSON,
            },
        })
    rc_all = 0
    for r in gh.run_many(specs, label='long_gd', max_parallel=jobs):
        print('  组 %d rc=%s（累计 %.0fs）' % (r['index'], r['rc'], time.time() - t0))
        if r['rc'] and not rc_all:
            rc_all = r['rc']
            for t in r['tail']:
                print('      ' + t[:150])
    gd_done = sum(1 for c in ids
                  if V._event_count(os.path.join(GD_OUT, c, 'events.json')) > 0)
    print('[long] gd 就绪 %d/%d（%.0fs）' % (gd_done, len(ids), time.time() - t0))

    # ── py 腿（逐场按语料抬闸）──
    t1 = time.time()
    ok = 0
    # ★ 在 _LongContext 里跑 py 腿：它临时把 V.CASES_JSON / 闸值表 / 产物目录
    #   换成"长场口径"，跑完立刻还原 —— 主流程源码零改动，也不会污染主基线。
    with _LongContext(GD_OUT, PY_OUT, fixture):
        for cid in ids:
            f = fixture[cid]
            out_path = os.path.join(PY_OUT, cid, 'events.json')
            if os.path.exists(out_path) and V._event_count(out_path) > 0 and not args.force:
                ok += 1
                continue
            if V._event_count(os.path.join(GD_OUT, cid, 'events.json')) <= 0:
                print('  [py][skip] %s 缺 gd 产物' % cid)
                continue
            try:
                if V.run_py([f]) == 0:
                    ok += 1
            except Exception as exc:  # noqa: BLE001
                print('  [py][FAIL] %s %s: %s' % (cid, type(exc).__name__, exc))
    print('[long] py 就绪 %d/%d（%.0fs）' % (ok, len(ids), time.time() - t1))

    # ── 比对 ──
    print('[long] 比对…')
    et = V._et_names()
    per = []
    for i, cid in enumerate(ids, 1):
        try:
            per.append(V.compare_case(cid, et))
        except Exception as exc:  # noqa: BLE001
            per.append({'caseId': cid, 'match': '比对异常',
                        'error': '%s: %s' % (type(exc).__name__, exc),
                        'firstDivergence': None})
        if i % 10 == 0:
            print('  [compare] %d/%d' % (i, len(ids)))
    return _write_report(per, ids) if (rc_all or True) else 1

def _write_report(per: List[Dict[str, Any]], ids: List[str]) -> int:
    """写长场对齐报告（独立文件，不碰 alignment.json）。"""
    aligned = sum(1 for r in per if r.get('match') == '三方一致')
    dist: Dict[str, int] = {}
    for r in per:
        dist[r.get('match', '?')] = dist.get(r.get('match', '?'), 0) + 1
    # 首分歧聚类：按「哪一对、分歧在什么事件类型」分组，便于按类修
    clusters: Dict[str, List[str]] = {}
    for r in per:
        if r.get('match') == '三方一致':
            continue
        fd = r.get('firstDivergence') or {}
        pair = fd.get('pair') or r.get('match', '?')
        at = (fd.get('at_idx') or {})
        key = '%s | type=%s' % (pair, at.get('type', '?'))
        clusters.setdefault(key, []).append(r.get('caseId', '?'))

    report = {
        'tool': 'long_case_fix.py',
        'scope': '被主夹具排除的长场（独立于 alignment.json 的 860 场基线）',
        'total': len(per),
        'aligned': aligned,
        'match_distribution': dist,
        'clusters': {k: {'count': len(v), 'cases': v[:12]}
                     for k, v in sorted(clusters.items(), key=lambda kv: -len(kv[1]))},
        'perCase': per,
    }
    os.makedirs(os.path.dirname(REPORT_JSON), exist_ok=True)
    with io.open(REPORT_JSON, 'w', encoding='utf-8', newline='\n') as fh:
        json.dump(report, fh, ensure_ascii=False, indent=1)
        fh.write('\n')
    print()
    print('=== 长场对齐：%d/%d 三方一致 ===' % (aligned, len(per)))
    for m, n in sorted(dist.items(), key=lambda kv: -kv[1]):
        print('  %-24s %d' % (m, n))
    if clusters:
        print()
        print('首分歧聚类（按类修，先修最大的那簇）：')
        for k, v in sorted(clusters.items(), key=lambda kv: -len(kv[1]))[:8]:
            print('  %-42s %d 场  例：%s' % (k, len(v), v[0]))
    print()
    print('报告 -> %s' % os.path.relpath(REPORT_JSON, ROOT))
    return 0 if aligned == len(per) else 1


def cmd_report(args) -> int:
    if not os.path.exists(REPORT_JSON):
        print('尚无报告：先跑 --run', file=sys.stderr)
        return 2
    d = json.load(io.open(REPORT_JSON, encoding='utf-8'))
    print('=== 长场报告（%s）===' % d.get('total'))
    print('三方一致 %d/%d' % (d['aligned'], d['total']))
    for m, n in sorted(d['match_distribution'].items(), key=lambda kv: -kv[1]):
        print('  %-24s %d' % (m, n))
    for k, v in list(d.get('clusters', {}).items())[:10]:
        print('  [簇] %-40s %d 场' % (k, v['count']))
    return 0 if d['aligned'] == d['total'] else 1


def cmd_focus(args) -> int:
    """单场深挖：跑一场并打印首分歧事件 + 上下文（修复时的主要入口）。"""
    cid = args.focus
    if not os.path.exists(CASES_JSON):
        print('缺长场夹具：先跑 --prepare', file=sys.stderr)
        return 2
    fixture = _fixture_rows()
    if cid not in fixture:
        print('%s 不在长场夹具内（用 --list 看清单）' % cid, file=sys.stderr)
        return 2
    os.makedirs(GD_OUT, exist_ok=True)
    os.makedirs(PY_OUT, exist_ok=True)
    if args.force:
        import shutil
        for d in (GD_OUT, PY_OUT):
            shutil.rmtree(os.path.join(d, cid), ignore_errors=True)

    print('[focus] %s：gd 腿重放…' % cid)
    t0 = time.time()
    spec = {
        'cmd': gh.cmd(project='gd_core_test', script='OracleAlignBattleLong.gd'),
        'tag': 'focus',
        'env_extra': {'ORACLE_ALIGN_OUT': GD_OUT,
                      'ORACLE_ALIGN_CASES': cid,
                      'ORACLE_ALIGN_CASES_FILE': CASES_JSON},
    }
    r = gh.run_many([spec], label='focus_gd')[0]
    print('[focus] gd rc=%s（%.0fs）' % (r['rc'], time.time() - t0))
    for t in r['tail']:
        print('   ' + t[:150])

    print('[focus] py 腿重放…')
    t1 = time.time()
    # ★ _LongContext：临时把 V 的夹具/闸值/产物目录换成长场口径（跑完自动还原）
    with _LongContext(GD_OUT, PY_OUT, fixture):
        try:
            V.run_py([fixture[cid]])
        except Exception as exc:  # noqa: BLE001
            print('[focus] py 失败：%s: %s' % (type(exc).__name__, exc))
    print('[focus] py 完成（%.0fs）' % (time.time() - t1))
    # 比对也要在长场口径下（compare_case 读的是 V.GD_OUT / V.PY_OUT）
    V.GD_OUT = GD_OUT
    V.PY_OUT = PY_OUT

    et = V._et_names()
    res = V.compare_case(cid, et)
    print()
    print('=== %s：%s ===' % (cid, res.get('match')))
    for tag, p in (('oracle', os.path.join(V.FIGHTS_DIR, cid, 'events.json')),
                   ('gdcore', os.path.join(GD_OUT, cid, 'events.json')),
                   ('py', os.path.join(PY_OUT, cid, 'events.json'))):
        print('  %-7s %d 事件' % (tag, V._event_count(p)))
    fd = res.get('firstDivergence') or {}
    if fd:
        print()
        print('  首分歧对：%s（kind=%s, index=%s）'
              % (fd.get('pair'), fd.get('kind'), fd.get('index')))
        for side in ('oracle', 'gdcore', 'py'):
            ctx = fd.get(side)
            if ctx:
                at = ctx.get('at_idx') or {}
                print('  %-7s idx=%s type=%s t=%s' % (side, at.get('t'),
                                                      at.get('type'), at.get('t')))
                for w in (ctx.get('window') or [])[:2]:
                    print('           %s' % w[:140])
        if fd.get('first_line_diff'):
            d = fd['first_line_diff']
            print('  首行分歧 line=%s' % d.get('line_index'))
            for side in ('oracle_line', 'gdcore_line', 'py_line'):
                if d.get(side):
                    print('    %-12s %s' % (side, d[side][:140]))
    _write_report([res], [cid])
    return 0 if res.get('match') == '三方一致' else 1

# ═══════════════════════ 4) 前缀重放迭代（提速核心）═══════════════════════

#: 迭代账本：记录每场每轮的首分歧位置，用来判断「这轮修改有没有让分歧前移/消失」
PROGRESS_JSON = os.path.join(LONG_DIR, 'progress.json')


def _load_progress() -> Dict[str, Any]:
    try:
        return json.load(io.open(PROGRESS_JSON, encoding='utf-8'))
    except Exception:  # noqa: BLE001
        return {'cases': {}}


def _save_progress(p: Dict[str, Any]) -> None:
    os.makedirs(os.path.dirname(PROGRESS_JSON), exist_ok=True)
    with io.open(PROGRESS_JSON, 'w', encoding='utf-8', newline='\n') as fh:
        json.dump(p, fh, ensure_ascii=False, indent=1)
        fh.write('\n')


def _corpus_prefix_stats(cid: str, upto_idx: int) -> Dict[str, Any]:
    """吃语料前 upto_idx 个事件，算它们的 tick 范围（用来定前缀重放上限）。"""
    p = os.path.join(V.FIGHTS_DIR, cid, 'events.json')
    try:
        ev = json.load(io.open(p, encoding='utf-8')).get('events') or []
    except Exception:  # noqa: BLE001
        return {'ticks': None}
    if not ev:
        return {'ticks': None}
    idx = max(0, min(upto_idx, len(ev) - 1))
    t = ev[idx].get('timestamp')
    try:
        tick = int(round(float(t) * 60))
    except Exception:  # noqa: BLE001
        tick = None
    return {'ticks': tick, 'event_index': idx,
            'event_t': float(t) if t is not None else None}


def _run_gd_prefix(cid: str, out_root: str, max_ticks: Optional[int],
                   fixture: Dict[str, Dict[str, Any]]) -> Dict[str, Any]:
    """跑一次 gd 重放（可限 tick），返回产物路径与耗时。"""
    os.makedirs(out_root, exist_ok=True)
    env_extra = {
        'ORACLE_ALIGN_OUT': out_root,
        'ORACLE_ALIGN_CASES': cid,
        'ORACLE_ALIGN_CASES_FILE': CASES_JSON,
    }
    if max_ticks:
        env_extra['ORACLE_ALIGN_MAX_TICKS'] = str(int(max_ticks))
    t0 = time.time()
    r = gh.run_many([{
        'cmd': gh.cmd(project='gd_core_test', script='OracleAlignBattleLong.gd'),
        'tag': 'pfx',
        'env_extra': env_extra,
    }], label='prefix_gd')[0]
    return {'rc': r['rc'], 'secs': time.time() - t0,
            'events_path': os.path.join(out_root, cid, 'events.json'),
            'tail': r['tail']}


def cmd_prefix(args) -> int:
    """**前缀重放**：只跑到「上次首分歧 + 余量」就停，秒级验证修复是否让分歧前移。

    这是长场修复的主要提速手段。原理：
      · 长场跑满 27-136 s，但首分歧往往在很前面（几百~几千事件）；
      · 本轮改动只需回答一个问题：**分歧位置有没有前移/消失**；
      · 故把重放上限压到「上次首分歧 tick + --margin」，跑完只看前缀是否一致。

    判据：拿前缀产物与语料**同样前缀**逐事件比：
      · 全等 → 分歧已推到前缀之外（说明这轮修复有效，实际比记录更靠后或已消失）；
      · 在某 idx 不等 → 新首分歧位置，前移=好，**后移=退步要立刻回滚**。

    账本（align_long/progress.json）记每场每轮的位置，跨轮对比。
    """
    cid = args.prefix
    if not os.path.exists(CASES_JSON):
        print('缺长场夹具：先跑 --prepare', file=sys.stderr)
        return 2
    fixture = _fixture_rows()
    if cid not in fixture:
        print('%s 不在长场夹具内（--list 看清单）' % cid, file=sys.stderr)
        return 2

    prog = _load_progress()
    rec = prog['cases'].get(cid) or {}
    known_idx = rec.get('first_div_idx')

    # 首轮（账本里没有记录）：先全量跑一次拿到真实首分歧位置
    if known_idx is None or args.force_full:
        print('[prefix] %s：账本无记录，先跑一次**全量**定位首分歧…' % cid)
        full_out = os.path.join(LONG_DIR, 'gdcore')
        run = _run_gd_prefix(cid, full_out, None, fixture)
        print('[prefix] gd rc=%s（%.0fs）' % (run['rc'], run['secs']))
        V.GD_OUT = full_out
        V.PY_OUT = os.path.join(LONG_DIR, 'py')
        res = V.compare_case(cid, V._et_names())
        fd = res.get('firstDivergence') or {}
        idx = fd.get('index')
        if idx is None:
            # ★ length 型分歧（如语料截断：语料=重放严格前缀）kind='length' 但
            #   index=None——不能与「三方一致」混同（2026-11-06 run1374_r18 实测误读）。
            if res.get('match') == '三方一致':
                print('[prefix] %s 已三方一致，无需迭代' % cid)
            else:
                print('[prefix] %s 无事件级分歧但未一致（match=%s，%s）'
                      '——长度型分歧（语料截断/超录），修复在语料侧非引擎侧'
                      % (cid, res.get('match'), fd.get('detail')))
            return 0
        rec.update({'first_div_idx': idx, 'first_div_type': (fd.get('at_idx') or {}).get('type'),
                    'match': res.get('match'), 'round': int(rec.get('round', 0)) + 1,
                    'full_secs': round(run['secs'], 1)})
        prog['cases'][cid] = rec
        _save_progress(prog)
        print('[prefix] 首分歧 idx=%s，已记入账本。之后每轮用 --prefix 只跑前缀。' % idx)
        return 1

    # 后续轮：覆盖到「上次分歧 + margin 个事件」所对应的 tick
    # ★ 用事件数而不是 tick 直接加：180 tick 里可能只有 6 个事件（长场前期事件稀疏），
    #   按 tick 加余量会算出「前缀比分歧点还短」，判定就失去意义。
    st = _corpus_prefix_stats(cid, int(known_idx) + args.margin)
    ticks = st.get('ticks')
    if not ticks:
        print('[prefix] 算不出前缀 tick，退回全量', file=sys.stderr)
        ticks = None
    pfx_out = os.path.join(LONG_DIR, 'prefix')
    print('[prefix] %s：上次分歧 idx=%s -> 语料 t=%s (%s tick)，重放前 %s tick'
          % (cid, known_idx, st.get('event_t'), ticks, ticks or '全部'))
    run = _run_gd_prefix(cid, pfx_out, ticks, fixture)
    print('[prefix] gd rc=%s（%.1fs，全量约 %.0fs）'
          % (run['rc'], run['secs'], rec.get('full_secs', 0) or 0))
    for t in run['tail']:
        if 'prefix' in t or 'PASS' in t or 'FAIL' in t:
            print('   ' + t[:140])

    # 比对前缀：产物 vs 语料同前缀
    prod = run['events_path']
    if not os.path.exists(prod) or V._event_count(prod) <= 0:
        print('[prefix] 产物为空（rc=%s），看上面的 tail' % run['rc'], file=sys.stderr)
        return 2
    et = V._et_names()
    a = V.canonical_stream(os.path.join(V.FIGHTS_DIR, cid, 'events.json'), et)
    b = V.canonical_stream(prod, et)
    n = min(len(a), len(b))
    new_idx = None
    for i in range(n):
        if V._tuple_of(a[i]) != V._tuple_of(b[i]):
            new_idx = i
            break

    # ★ 覆盖度闸（关键）：前缀产物必须**越过**上次分歧点，判定才有意义。
    #   否则「前 N 个事件全等」只是因为 N < 上次分歧位置 —— 什么都没证明，
    #   却会被误读成「修复有效」（2026-11-05 实测踩到：分歧 idx=6，前缀只覆盖 6 条）。
    need = int(known_idx) + 1
    if len(b) < need:
        print('[prefix] ⚠ 覆盖不足：前缀产物只有 %d 个事件，尚未越过上次分歧 idx=%s'
              '（至少要 %d 个）。加大 --margin 重跑。' % (len(b), known_idx, need))
        rec.update({'last_verdict': '覆盖不足', 'round': int(rec.get('round', 0)) + 1,
                    'prefix_secs': round(run['secs'], 1)})
        prog['cases'][cid] = rec
        _save_progress(prog)
        return 2

    if new_idx is None:
        verdict = '前缀全等（已越过上次分歧点）'
        if len(b) < len(a):
            print('[prefix] ✔ 前 %d 事件全等，分歧已推到 %s 之后（本轮修复有效）'
                  % (n, known_idx))
        else:
            print('[prefix] ✔ 前 %d 事件全等（覆盖到语料末，可能已完全一致）' % n)
    else:
        verdict = '分歧前移到 %d' % new_idx if new_idx < int(known_idx) else \
                  ('分歧后移到 %d（退步！）' % new_idx if new_idx > int(known_idx) else '同位置')
        print('[prefix] %s：new_idx=%d vs 上次 %s' % (
            '✔ 前移' if new_idx < int(known_idx) else
            ('✘ 退步' if new_idx > int(known_idx) else '= 未动'), new_idx, known_idx))
        if new_idx < n:
            x, y = V._tuple_of(a[new_idx]), V._tuple_of(b[new_idx])
            print('   语料  : %s' % (str(x)[:160]))
            print('   产物  : %s' % (str(y)[:160]))

    rec.update({
        'first_div_idx': new_idx if new_idx is not None else rec.get('first_div_idx'),
        'last_verdict': verdict,
        'round': int(rec.get('round', 0)) + 1,
        'prefix_secs': round(run['secs'], 1),
    })
    prog['cases'][cid] = rec
    _save_progress(prog)
    return 0 if (new_idx is None or new_idx < int(known_idx)) else 1



# ═══════════════════════ 5) 长场重录（①分档 + ③并行）═══════════════════════

#: 重录产物落这里（**不覆盖** output/oracle/fights 冻结语料）
REC_DIR = os.path.join(LONG_DIR, 'record')


def cmd_record(args) -> int:
    """长场**重录**：① 分档（每进程只对首场做确定性复跑）+ ③ 并行分片。

    ## 为什么这样提速（两笔账，都是实测）

    **① 分档：53/54 场自动只跑一遍**
      `oracle_fight.gd` 的确定性自证（`determinism_check`）**只对 cases[0] 执行**
      （oracle_fight.gd:342 紧邻复跑 + :355 批尾复跑）。所以过去「一场一进程」时
      每场都白跑一遍复跑；现在把 N 场塞进**同一个进程**，只有第 1 场付复跑成本，
      其余 N-1 场只跑一遍。单场 117s -> 60s 的效果就从这里来。
      **不需要改 oracle 任何代码** —— 只是换个喂法。

    **③ 并行：按事件数 LPT 分桶，一进程一桶**
      长场 54 场游戏时间合计 2543.7s（42.4 分钟单进程下界），4 路并行 ~10.6 分钟。

    ## 两道安全闸

    **批要小**：`oracle_fight.gd` 的 MessageQueue 只在帧末 flush，跨场累积会溢出
      （文档 M11 实测 ~116 场普通场后溢出；长场事件多，故默认 --batch 3）。
    **产物隔离**：写 `output/oracle/align_long/record/`，**绝不覆盖**冻结语料
      `output/oracle/fights/`。要替换语料请人工确认后再搬运。
    """
    fights = json.load(io.open(os.path.join(ROOT, 'oracle', 'fights.json'),
                               encoding='utf-8'))['cases']
    main_ids = set()
    try:
        main_ids = {c['case_id'] for c in
                    json.load(io.open(MAIN_FIXTURE, encoding='utf-8'))['cases']}
    except Exception:  # noqa: BLE001
        pass
    rows = []
    for c in fights:
        cid = c['case_id']
        if args.only:
            if cid not in args.only:
                continue
        elif not args.all_long and main_ids and cid in main_ids:
            continue
        p = os.path.join(V.FIGHTS_DIR, cid, 'events.json')
        if not os.path.exists(p):
            continue
        rows.append({
            'case_id': cid,
            'seed': int(c['seed']),
            'event_count': _event_count_of(p),
            'bytes': os.path.getsize(p),
        })
    if not rows:
        print('没有可重录的场', file=sys.stderr)
        return 2
    # ③ LPT：事件多的先投给最轻的桶（事件数是耗时的最好代理）
    jobs = gh.effective_jobs(len(rows), gh.auto_jobs(len(rows), args.jobs),
                             max(1, args.batch))
    buckets, load = gh.lpt_buckets([r['case_id'] for r in rows], jobs,
                                   {r['case_id']: r['event_count'] for r in rows})
    by_id = {r['case_id']: r for r in rows}
    print('[record] %d 场 -> %d 桶（并行 %d 路），桶负载（事件数）：%s'
          % (len(rows), len(buckets), jobs,
             ', '.join('%.0f' % x for x in load)))
    print('[record] 每进程最多 %d 场：首场付确定性复跑，其余只跑一遍' % args.batch)

    os.makedirs(REC_DIR, exist_ok=True)
    specs = []
    for bi, bucket in enumerate(buckets):
        # 桶内再按 batch 切段：每段一个进程（段首场付复跑）
        for si in range(0, len(bucket), max(1, args.batch)):
            seg = bucket[si:si + max(1, args.batch)]
            specs.append({
                'cmd': gh.cmd(project='oracle', script='oracle_fight.gd'),
                'tag': 'rec%d_%d' % (bi, si),
                'env_extra': {'ORACLE_FIGHTS_ROOT': REC_DIR,
                              'ORACLE_ONLY_CASES': ','.join(seg)},
            })
    t0 = time.time()
    rc_all = 0
    done = 0
    for r in gh.run_many(specs, label='long_rec', max_parallel=jobs):
        done += 1
        print('  段 %d/%d rc=%s（累计 %.0f 分钟）'
              % (done, len(specs), r['rc'], (time.time() - t0) / 60), flush=True)
        if r['rc'] and not rc_all:
            rc_all = r['rc']
            for t in r['tail']:
                print('     ' + t[:150])

    # 汇总：逐场对照语料（产物在 REC_DIR，语料在 FIGHTS_DIR）
    ok = miss = diff = 0
    worst = []
    for r in rows:
        cid = r['case_id']
        new = os.path.join(REC_DIR, cid, 'events.json')
        old = os.path.join(V.FIGHTS_DIR, cid, 'events.json')
        if not os.path.exists(new):
            miss += 1
            continue
        d = json.load(io.open(new, encoding='utf-8'))
        if int(d.get('event_count', 0)) == r['event_count']:
            ok += 1
        else:
            diff += 1
            worst.append((cid, int(d.get('event_count', 0)), r['event_count']))
    print()
    print('[record] 完成：事件数一致 %d / 缺失 %d / 不一致 %d（共 %d 场，墙钟 %.1f 分钟）'
          % (ok, miss, diff, len(rows), (time.time() - t0) / 60))
    for cid, got, want in worst[:8]:
        print('   [差异] %-16s 重录 %d vs 语料 %d' % (cid, got, want))
    print('[record] 产物 -> %s（**未覆盖冻结语料**，需人工确认后再搬）'
          % os.path.relpath(REC_DIR, ROOT))
    return 0 if (rc_all == 0 and miss == 0 and diff == 0) else 1


# ═══════════════════════ main ═══════════════════════

def main() -> int:
    ap = argparse.ArgumentParser(
        description='长场专项验证/修复（与主基线隔离；不拖慢主回路）')
    g = ap.add_mutually_exclusive_group()
    g.add_argument('--list', action='store_true', help='列被排除的长场及规模')
    g.add_argument('--prepare', action='store_true', help='生成长场专属夹具')
    g.add_argument('--run', action='store_true', help='三腿验证（gd/py/compare）')
    g.add_argument('--report', action='store_true', help='汇总长场对齐报告')
    g.add_argument('--focus', default='', metavar='CASE',
                   help='单场深挖：跑 gd+py 并打印首分歧事件与上下文')
    g.add_argument('--prefix', default='', metavar='CASE',
                   help='**前缀重放**：只跑到上次分歧点+余量，秒级验证修复是否前移（修复迭代主入口）')
    g.add_argument('--record', action='store_true',
                   help='**长场重录**：分档（每进程只首场付复跑）+ 并行分片，产物写 align_long/record（不覆盖冻结语料）')
    ap.add_argument('--jobs', type=int, default=0,
                    help='并行度（0=自动，上限 %d）' % gh.PARALLEL_MAX_JOBS)
    ap.add_argument('--batch', type=int, default=4,
                    help='一个 Godot 进程跑几场（默认 4；oracle 启动 ≈25s 要摊薄）')
    ap.add_argument('--limit', type=int, default=0, help='只处理前 N 场')
    ap.add_argument('--force', action='store_true', help='先删长场产物重跑')
    ap.add_argument('--margin', type=int, default=300,
                    help='前缀重放的余量（事件数，默认 300）：必须覆盖到'
                         '「上次分歧 + margin 个事件」，否则前缀太短判不了')
    ap.add_argument('--force-full', action='store_true',
                    help='--prefix 时忽略账本，重新全量定位首分歧')
    ap.add_argument('--only', default='',
                    help='--record 时只重录逗号分隔的 case_id')
    ap.add_argument('--all-long', action='store_true',
                    help='--record 时连主夹具内的场也重录（默认只重录被排除的 54 场）')
    args = ap.parse_args()

    if args.list:
        return cmd_list(args)
    if args.prepare:
        return cmd_prepare(args)
    if args.run:
        return cmd_run(args)
    if args.report:
        return cmd_report(args)
    if args.focus:
        return cmd_focus(args)
    if args.prefix:
        return cmd_prefix(args)
    if args.record:
        args.only = {x for x in (getattr(args, 'only', '') or '').split(',') if x}
        return cmd_record(args)
    ap.print_help()
    return 0


if __name__ == '__main__':
    sys.exit(main())
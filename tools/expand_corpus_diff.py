#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
expand_corpus_diff.py — 重录后语料差量对比（np51⑤ 收尾辅助）

对比新语料 vs 备份（output/_expand/corpus_backup_np51_pre_rerecord）逐场 events.json：
  SAME     事件流逐字节同（清洁场，重录零变化）
  CHANGED  事件流变化（原泄漏污染场）→ 列出清单供删除 gd/py 陈旧产物
  MISSING  新语料缺场（重录失败，需补跑）
用法：
    python -X utf8 tools/expand_corpus_diff.py            # 只汇总
    python -X utf8 tools/expand_corpus_diff.py --prune    # 并删除 CHANGED 场的 gd/py 产物
"""
from __future__ import annotations

import io
import json
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NEW = os.path.join(ROOT, "output", "oracle", "expand", "fights")
OLD = os.path.join(ROOT, "output", "_expand", "corpus_backup_np51_pre_rerecord")
GD = os.path.join(ROOT, "output", "oracle", "align_expand", "gdcore")
PY = os.path.join(ROOT, "output", "oracle", "align_expand", "py")


def sig(p):
    try:
        return io.open(p, "rb").read()
    except OSError:
        return None


def main() -> int:
    prune = "--prune" in sys.argv
    changed, same, missing = [], [], []
    for d in sorted(os.listdir(NEW)):
        if not d.startswith("run"):
            continue
        a = sig(os.path.join(NEW, d, "events.json"))
        b = sig(os.path.join(OLD, d, "events.json"))
        if a is None:
            missing.append(d)
        elif a == b:
            same.append(d)
        else:
            changed.append(d)
    print("SAME %d | CHANGED %d | MISSING %d" % (len(same), len(changed), len(missing)))
    if changed:
        out = os.path.join(ROOT, "output", "_expand", "rerecord_changed.json")
        json.dump(changed, io.open(out, "w", encoding="utf-8"), indent=1)
        print("CHANGED 清单 →", out)
        print("样例:", changed[:10])
    if missing:
        print("缺失样例:", missing[:10])
    if prune:
        n = 0
        for d in changed:
            for base in (GD, PY):
                p = os.path.join(base, d)
                if os.path.isdir(p):
                    shutil.rmtree(p)
                    n += 1
        print("已删 CHANGED 场 gd/py 产物 %d 个目录" % n)
    return 0 if not missing else 1


if __name__ == "__main__":
    raise SystemExit(main())

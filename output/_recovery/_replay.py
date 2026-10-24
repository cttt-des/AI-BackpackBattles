# -*- coding: utf-8 -*-
"""恢复重放器：从 cli/artifacts 重建仓库 np4-np22 终态。

策略：每文件取 cutoff 前最晚一笔事件（大小写归一路径），Write 取 afterContent，
Edit 取 beforeContent+structuredPatch 应用；写入仓库；输出清单与异常。
"""
import json
import os
import glob
import collections

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = r"D:\文件资料\学习\自动背包AI"
CUTOFF = "2026-10-24T07:30:00"  # np22 账房终笔 07:25 之后、今日清理开始之前


def norm(p: str) -> str:
    return p.replace("\\", "/").lower()


REPO_N = norm(REPO) + "/"

events = []  # (createdAt, relpath, toolName, entry, sess)
per_day = collections.Counter()
for d in sorted(os.listdir(ROOT)):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp):
        continue
    for f in glob.glob(os.path.join(dp, "*.json")):
        try:
            j = json.load(open(f, encoding="utf-8"))
        except Exception:
            continue
        t = j.get("createdAt") or ""
        for fe in j.get("files", []) or []:
            p = norm(fe.get("path") or "")
            if not p.startswith(REPO_N):
                continue
            rel = fe.get("path").replace("\\", "/")[len(REPO_N):]
            # 原始大小写路径恢复：用 entry 原文截取
            orig = fe.get("path")
            rel = orig.replace("\\", "/").split("自动背包AI/", 1)[-1]
            events.append((t, rel, j.get("toolName"), fe, d))
            per_day[t[:10]] += 1

print("=== 每日事件直方图 ===")
for day in sorted(per_day):
    print(day, per_day[day])

events.sort(key=lambda e: e[0])
latest = {}
for t, rel, tool, fe, d in events:
    if t >= CUTOFF:
        continue
    if rel not in latest or t > latest[rel][0]:
        latest[rel] = (t, tool, fe)


def apply_patch(before: str, hunks) -> str:
    lines = before.splitlines(keepends=True)
    out = []
    pos = 0
    for h in hunks:
        old_start = h["oldStart"] - 1
        if old_start < pos:
            raise ValueError("hunk 重叠")
        out.extend(lines[pos:old_start])
        new_lines = [ln[1:] if ln[:1] in "+- " else ln for ln in h["lines"] if not ln.startswith("-")]
        # 校验删除行匹配
        dels = [ln[1:] for ln in h["lines"] if ln.startswith("-")]
        seg = lines[old_start:old_start + len(dels)]
        if [l.rstrip("\r\n") for l in seg] != [x.rstrip("\r\n") for x in dels]:
            raise ValueError("删除段不匹配 @oldStart=%d" % h["oldStart"])
        joined = "".join(new_lines)
        if joined and not joined.endswith("\n"):
            joined += "\n"
        out.append(joined)
        pos = old_start + h["oldLines"]
    out.extend(lines[pos:])
    return "".join(out)


written = []
errors = []
for rel, (t, tool, fe) in sorted(latest.items()):
    try:
        if tool == "Write":
            content = fe.get("afterContent", "")
        elif tool == "Edit":
            content = apply_patch(fe.get("beforeContent", ""), fe.get("structuredPatch") or [])
        else:
            continue
    except Exception as exc:
        errors.append((rel, str(exc)))
        continue
    dest = os.path.join(REPO, rel.replace("/", os.sep))
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    base_exists = os.path.exists(dest)
    with open(dest, "w", encoding="utf-8", newline="") as fh:
        fh.write(content)
    written.append((rel, t[:16], tool, "new" if not base_exists else
                    ("changed" if open(dest, "rb").read()[:0] == b"" else "written")))

print("\n=== 重放完成 ===")
print("文件数:", len(written), "异常:", len(errors))
for rel, t, tool, st in errors[:10]:
    print("ERR", rel, t)
# 关键文件核对清单
keys = ["gd_core_test/OracleAlignBattle.gd", "gd_core/CoreBuff.gd", "gd_core/CoreItem.gd",
        "gd_core_items/Exclusive/AmuletofAgility.gd", "tools/verify_oracle.py",
        "simulator/gd_core_engine.py", "output/alignment_fix_log.md",
        "output/oracle/wf_notes/np21_fix.md", "output/oracle/wf_notes/np22_fix.md"]
for k in keys:
    hit = [w for w in written if w[0].lower().endswith(k.lower())]
    print("KEY", ("OK " if hit else "MISS"), k, hit[0][1] if hit else "")

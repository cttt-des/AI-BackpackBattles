#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diff_draw_trace.py — 神谕 rng_log ↔ 内核 rng_trace 逐抽对位 diff（阶段3 消歧主仪器）

前提：两侧从同一链态起跑（阶段1 注入 / 阶段2 装配零残差），每次消耗的都是同一
PCG32 流 ⇒ **值相等 = 链位对齐**（标签/范围差异不影响链位，只影响打印串）。
对位规则：
  · EVENT 标记行必须同型同值（事件流对齐）；
  · 抽取行比较「方法族 + 返回值」——oracle 的 randInBox.x/y、pickRandomElement、
    roll、flip 等标签在内核侧统一落为 randf_range/randi_range/randf，按值归一。
用法：
  python -X utf8 tools/diff_draw_trace.py <case_id> [oracle_log kernel_trace]
锚点：oracle 取 rng_state.txt 导出之后的首条抖动抽（自动定位：跳过装配段——
  内核 trace 前部的注入前装配抽以「与 oracle 后段无法对齐」为特征，故这里用
  oracle 侧 jitter 段（首个 (0.95,1.05)/(0.975,1.05) 行）作为对齐锚起点，
  kernel 侧从注入完成后的第一行起（trace 文件头部注入前抽由 --kernel-skip 跳过，默认 2）。
"""
import io
import sys


def load_rows(p, val_idx):
    """EVENT 行 token 数两侧不同（oracle=5、kernel=4，空列被 split 吞掉），
    先判 EVENT（len>=3）再判抽取行。val_idx 为抽取行返回值列。"""
    rows = []
    for ln in io.open(p, encoding="utf-8", errors="replace"):
        parts = ln.split()
        if len(parts) < 3:
            continue
        if parts[1] == "EVENT":
            rows.append({"kind": "EVENT", "tag": "EVENT", "args": parts[2], "val": parts[2]})
        elif len(parts) > val_idx:
            rows.append({"kind": "draw", "tag": parts[1], "args": parts[2] + "," + parts[3],
                         "val": parts[val_idx]})
    return rows


def load_oracle(p):
    return load_rows(p, 5)


def load_kernel(p):
    return load_rows(p, 5)


def norm_family(row):
    """抽取方法族归一：内核侧统一 randf_range/randi_range/randf/randi；
    oracle 的包装标签（randInBox/pickRandomElement/roll/randPitch/flip…）映射过去。"""
    tag = row["tag"]
    if row["kind"] == "EVENT":
        return "EVENT"
    if tag in ("randInBox.x", "randInBox.y", "randInBox", "randInCircle", "randInCircle.rot",
               "roll", "randRange", "randPitch", "flipWeighted", "randf_range",
               "randBuffLabelDir"):
        return "randf_range"
    if tag in ("pickRandomElement", "randString", "randi_range", "randi"):
        return "irange"
    if tag == "flip" or tag == "randf":
        return "randf"
    return tag


def main():
    case_id = sys.argv[1] if len(sys.argv) > 1 else "run1029_r2"
    oracle_log = sys.argv[2] if len(sys.argv) > 2 else \
        "output/oracle/fights/%s/rng_log.txt" % case_id
    kernel_trace = sys.argv[3] if len(sys.argv) > 3 else \
        "gd_core_test/output/oracle/align/gdcore_trace3/%s/rng_trace.txt" % case_id
    kernel_skip_arg = int(sys.argv[4]) if len(sys.argv) > 4 else -1   # -1=自动

    O_all = load_oracle(oracle_log)
    K_all = load_kernel(kernel_trace)

    # oracle 锚：第一条 (0.95,1.05)/(0.975,1.05) 抽 = 开战 jitter 段首抽
    anchor = 0
    for i, r in enumerate(O_all):
        if r["kind"] == "draw" and r["args"] in ("0.95,1.05", "0.975,1.05"):
            anchor = i
            break
    O = O_all[anchor:]

    # 内核锚：注入前装配抽以「与 oracle 抖动首抽对不上」为特征——在内核前部
    # 找第一处「连续 3 行与 oracle 锚起 3 行同族同值」的位置；找不到再退回 arg。
    kstart = 0
    if kernel_skip_arg < 0:
        probe = [(norm_family(r), r["val"]) for r in O[:3]]
        for i in range(min(len(K_all) - 3, 400)):
            if [(norm_family(K_all[i + j]), K_all[i + j]["val"]) for j in range(3)] == probe:
                kstart = i
                break
        if kstart == 0 and not [(norm_family(K_all[0]), K_all[0]["val"])] == probe[:1]:
            kstart = 0
    else:
        kstart = kernel_skip_arg
    K = K_all[kstart:]

    print("oracle anchor=%d battle rows=%d  kernel start=%d rows=%d"
          % (anchor, len(O), kstart, len(K)))
    n = min(len(O), len(K))
    i = 0
    while i < n:
        a, b = O[i], K[i]
        if a["kind"] != b["kind"]:
            break
        if a["kind"] == "EVENT":
            if a["val"] != b["val"]:
                break
        else:
            if norm_family(a) != norm_family(b) or a["val"] != b["val"]:
                break
        i += 1
    print("aligned rows: %d" % i)

    for j in range(max(0, i - 4), min(n, i + 18)):
        mark = "  " if j < i else ">>"
        o_cell = ("EVENT " + O[j]["val"]) if O[j]["kind"] == "EVENT" \
            else "%s(%s)=>%s" % (O[j]["tag"], O[j]["args"], O[j]["val"])
        k_cell = ("EVENT " + K[j]["val"]) if K[j]["kind"] == "EVENT" \
            else "%s(%s)=>%s" % (K[j]["tag"], K[j]["args"], K[j]["val"])
        print("%s O%3d %-42s |K%3d %s" % (mark, j, o_cell[:42], j, k_cell[:42] if j < len(K) else "-"))

    # 未对齐后的「值回归」诊断：内核后面哪里重新出现 oracle 当前值 → 步进差
    if i < n:
        target = O[i]["val"]
        for j2 in range(i, min(i + 40, len(K))):
            if K[j2]["kind"] == "draw" and K[j2]["val"] == target:
                print("[value-regression] oracle 行 %d 的值在内核 %d 行重现（内核多/少 %d 抽）"
                      % (i, j2, j2 - i))
                break


if __name__ == "__main__":
    main()

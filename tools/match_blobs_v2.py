#!/usr/bin/env python3
"""
match_blobs_v2.py — 改进版 GDEC 明文匹配器。

核心问题：内存扫描捕获的 GDSC 缓冲在 Vector<uint8_t> 分配中常带「尾随垃圾」
（分配尺寸 > 实际内容）。上一版只比对 整块 MD5，导致带垃圾的 blob 无法命中。

本版做法：对每条 GDEC 记录的 (plain_len, md5)，尝试 md5(blob[:plain_len])，
命中即说明该 blob 是此脚本的明文，且 plain_len 是精确长度 -> 截断为 .gdc。

用法:
  python match_blobs_v2.py [--dump DIR] [--extracted DIR] [--out DIR]
"""
import argparse, glob, hashlib, os, struct, sys

def read_gdec_index(extracted_dir):
    """返回 {(md5hex): (relpath, plain_len)} 以及 len 索引。"""
    by_md5 = {}
    by_len = {}   # plain_len -> list of (md5hex, relpath)
    count = 0
    gdes = glob.glob(os.path.join(extracted_dir, "**", "*.gde"), recursive=True)
    for gde in gdes:
        try:
            with open(gde, "rb") as f:
                head = f.read(40)
            if len(head) < 32 or head[0:4] != b"GDEC":
                continue
            md5 = head[8:24]
            plain_len = struct.unpack("<Q", head[24:32])[0]
            rel = os.path.relpath(gde, extracted_dir)
            by_md5[md5.hex()] = (rel, plain_len)
            by_len.setdefault(plain_len, []).append((md5.hex(), rel))
            count += 1
        except Exception as e:
            print("ERR read", gde, e, file=sys.stderr)
    print(f"[index] parsed {count} GDEC entries; unique md5={len(by_md5)} unique_len={len(by_len)}")
    return by_md5, by_len

def try_match_blob(data, by_md5, by_len):
    """返回 (relpath, plain_len) 或 None。"""
    n = len(data)
    # 1) 整块无垃圾
    m = hashlib.md5(data).hexdigest()
    if m in by_md5:
        return by_md5[m]
    # 2) 带尾随垃圾：仅在接近实际长度的候选里试
    #    只检查 len <= n 且接近 n 的记录（差 <= 64KB 视为同一分配）
    candidates = []
    for L, lst in by_len.items():
        if L <= n and (n - L) <= 65536:
            candidates.append(L)
    # 从最接近 n 的 L 开始（垃圾越大，L 越小）
    candidates.sort(reverse=True)
    for L in candidates:
        m = hashlib.md5(data[:L]).hexdigest()
        for md5hex, rel in by_len[L]:
            if m == md5hex:
                return (rel, L)
    return None

def main():
    ap = argparse.ArgumentParser()
    here = os.path.dirname(os.path.abspath(__file__))
    root = os.path.dirname(here)
    ap.add_argument("--dump", default=os.path.join("C:/tmp/bb/dump"))
    ap.add_argument("--extracted", default=os.path.join(root, "extracted"))
    ap.add_argument("--out", default=os.path.join(root, "extracted_gdc"))
    args = ap.parse_args()

    by_md5, by_len = read_gdec_index(args.extracted)
    os.makedirs(args.out, exist_ok=True)

    blobs = sorted(glob.glob(os.path.join(args.dump, "*.bin")))
    print(f"[scan] {len(blobs)} blobs in {args.dump}")
    matched = 0
    for b in blobs:
        data = open(b, "rb").read()
        res = try_match_blob(data, by_md5, by_len)
        if res:
            rel, L = res
            matched += 1
            out_rel = rel + ".gdc"
            out_path = os.path.join(args.out, out_rel)
            os.makedirs(os.path.dirname(out_path), exist_ok=True)
            with open(out_path, "wb") as f:
                f.write(data[:L])
            print(f"[OK ] {os.path.basename(b)} ({len(data)}B) -> {out_rel}  trunc={L}")
        else:
            print(f"[-- ] {os.path.basename(b)} ({len(data)}B) no match")
    print(f"[done] matched {matched}/{len(blobs)}")

if __name__ == "__main__":
    main()

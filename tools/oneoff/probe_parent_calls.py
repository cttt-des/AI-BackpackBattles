# 一次性探针：统计「原版有父类调用、产物却被剥成 pass」的函数（影子覆盖风险）
import re, os, io, sys, collections
sys.stdout.reconfigure(encoding="utf-8")
ROOT = r"D:/文件资料/学习/自动背包AI"
SRC = os.path.join(ROOT, "decompiled_full", "Items")
GEN = os.path.join(ROOT, "gd_core_items")
FUNC_RE = re.compile(r"^\s*func ")
NAME_RE = re.compile(r"^\s*func ([A-Za-z_]\w*)")
PCALL_RE = re.compile(r"^\s*\.\s*[A-Za-z_]\w*\s*\(")

def harvest(lines):
    """→ {func_name: [body_lines]}"""
    out = {}
    cur = None
    for l in lines:
        if FUNC_RE.match(l):
            m = NAME_RE.match(l)
            cur = m.group(1) if m else "?"
            out.setdefault(cur, [])
        elif cur is not None:
            out[cur].append(l)
    return out

hits = collections.Counter(); sites = collections.defaultdict(list)
for dp, _, fs in os.walk(SRC):
    for fn in fs:
        if not fn.endswith(".gd"):
            continue
        rel = os.path.relpath(os.path.join(dp, fn), SRC).replace(os.sep, "/")
        g = os.path.join(GEN, rel)
        if not os.path.exists(g):
            continue
        orig = harvest(io.open(os.path.join(dp, fn), encoding="utf-8", errors="replace").read().splitlines())
        gen = harvest(io.open(g, encoding="utf-8", errors="replace").read().splitlines())
        for name, body in orig.items():
            if name not in gen:
                continue
            if not any(PCALL_RE.match(x) for x in body):
                continue
            real = [x for x in gen[name] if x.strip()]
            if len(real) == 1 and real[0].strip() == "pass":
                hits[name] += 1
                sites[name].append(rel)
print("原版有父类调用、产物却已剥成 pass 的函数（%d 种 / %d 处）：" % (len(hits), sum(hits.values())))
for k, v in hits.most_common():
    print("   %-36s %2d  例：%s" % (k, v, sites[k][0]))

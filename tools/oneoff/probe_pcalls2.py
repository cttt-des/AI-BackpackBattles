import re, os, io, sys, collections
sys.stdout.reconfigure(encoding="utf-8")
ROOT = r"D:/文件资料/学习/自动背包AI"
SRC = os.path.join(ROOT, "decompiled_full", "Items")
GEN = os.path.join(ROOT, "gd_core_items")
FUNC_RE = re.compile(r"^\s*func "); NAME_RE = re.compile(r"^\s*func ([A-Za-z_]\w*)")
PCALL_RE = re.compile(r"^\s*\.\s*([A-Za-z_]\w*)\s*\(")
def harvest(lines):
    out = {}; cur = None
    for l in lines:
        if FUNC_RE.match(l):
            m = NAME_RE.match(l); cur = m.group(1) if m else "?"; out.setdefault(cur, [])
        elif cur is not None:
            out[cur].append(l)
    return out
rows = []
for dp, _, fs in os.walk(SRC):
    for fn in fs:
        if not fn.endswith(".gd"): continue
        rel = os.path.relpath(os.path.join(dp, fn), SRC).replace(os.sep, "/")
        g = os.path.join(GEN, rel)
        if not os.path.exists(g): continue
        orig = harvest(io.open(os.path.join(dp, fn), encoding="utf-8", errors="replace").read().splitlines())
        gen = harvest(io.open(g, encoding="utf-8", errors="replace").read().splitlines())
        for name, body in orig.items():
            if name not in gen: continue
            calls = [x.strip() for x in body if PCALL_RE.match(x)]
            if not calls: continue
            real = [x for x in gen[name] if x.strip()]
            if len(real) == 1 and real[0].strip() == "pass":
                rows.append((rel, name, calls[0]))
for rel, name, call in sorted(rows):
    print("%-44s %-28s %s" % (rel, name, call))

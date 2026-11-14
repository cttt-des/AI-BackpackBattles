# -*- coding: utf-8 -*-
"""A.1 装配链逐抽对齐：oracle [BARE]+[ITEMINIT]/[ITEMREADY]/[CONNREADY] vs py [GDRAW]+[ITEM]。

用法（先各跑一次取证，再对齐）:
    python -X utf8 tools/_a1_oracle_bare_case.py <case_id>
    ORACLE_ALIGN_DRAWSEQ=1 A1_GDRAW=1 A1_ITEM_MARK=1 python -X utf8 tools/_a1_measure_asm_steps.py <case_id> > <pylog>
    python -X utf8 tools/_a1_align_asm.py <case_id> <pylog> [--ctx N]
"""
import sys, os, io, re, json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
M = 6364136223846793005
INC = 2885390081777926815
MASK = (1 << 64) - 1


def pcg_seed(v):
    s = 0
    s = (s * M + INC) & MASK
    s = (s + v) & MASK
    s = (s * M + INC) & MASK
    return s


def parse_oracle(cid):
    """返回 (seq, seed)。seq: [(kind, a1, a2, owner_item, marker)]，owner=INIT 锚定的物品名。"""
    st_path = os.path.join(ROOT, 'output', '_a1', 'bare_oracle', cid, cid, 'rng_state.txt')
    state_target = None
    for ln in io.open(st_path, encoding='utf-8'):
        if ln.startswith('state='):
            state_target = int(ln.strip()[6:]) & MASK
    cs = json.load(io.open(os.path.join(ROOT, 'output/oracle/expand/cases.json'), encoding='utf-8'))
    if isinstance(cs, dict) and 'cases' in cs:
        cs = cs['cases']
    seed = next(int(c['seed']) for c in cs if c['case_id'] == cid)
    first_state = pcg_seed(seed)
    for _ in range(2):
        first_state = (first_state * M + INC) & MASK

    pat = re.compile(r'\[BARE\] (\S+) ?(\S*) ?(\S*) => (\S+) st=(-?\d+)')
    ev = []
    for ln in io.open(os.path.join(ROOT, 'output', '_a1', 'bare_stdout_%s.log' % cid),
                      encoding='utf-8', errors='replace'):
        for m in pat.finditer(ln):
            kind = m.group(1)
            a1, a2 = m.group(2), m.group(3)
            if kind in ('randf', 'randi'):
                a1, a2 = '0', '0'
            ev.append(('B', (kind, a1, a2), int(m.group(5)) & MASK))
        for tag in ('[ITEMINIT]', '[ITEMREADY]', '[CONNREADY]'):
            i = ln.rfind(tag)
            if i >= 0:
                ev.append((tag, ln[i + len(tag):].strip(), None))
    fi = next(i for i, e in enumerate(ev) if e[0] == 'B' and e[2] == first_state)
    # 取下一次出现 battle-start 的 BARE 为终点（同 pass 内）
    bi = next(i for i, e in enumerate(ev) if i > fi and e[0] == 'B' and e[2] == state_target)

    seq = []
    pending = []          # INIT 前的 ctor 抽（挂到 INIT 的物品）
    cur = ['?']           # READY 后的当前物品（_ready 期抽）
    for e in ev[fi:bi + 1]:
        if e[0] == 'B':
            tup = (e[1][0], e[1][1], e[1][2])
            if tup == ('randf_range', '0.2', '-0.2'):
                # ctor 抽：INIT 前的实例初始化（挂下一 INIT）或 READY 后下一物品的实例
                pending.append([e[1][0], e[1][1], e[1][2], None, ''])
                seq.append(pending[-1])
            else:
                seq.append([e[1][0], e[1][1], e[1][2], cur[0], ''])
        elif e[0] == '[ITEMINIT]':
            name = _name_of(e[1])
            for row in pending:
                row[3] = name
            pending = []
        elif e[0] == '[ITEMREADY]':
            cur[0] = _name_of(e[1])
        elif e[0] == '[CONNREADY]':
            pass
    # 尾部 pending（无 INIT 的战斗首抽等）不归属
    for row in seq:
        if row[0] not in ('INIT', 'READY', 'CONN') and row[3] is None:
            pass  # 保持 None（character 的 4 抽等）
    return seq, seed


def _name_of(path):
    p = path.strip().rstrip('@0123456789')
    p = p.split('/')[-1]
    return p if p else '?'


def parse_py(pylog):
    stack = []
    seq = []
    for ln in io.open(pylog, encoding='utf-8', errors='replace'):
        if ln.startswith('[ITEM+]'):
            stack.append(' '.join(ln.split()[1:]))
        elif ln.startswith('[ITEM-]'):
            if stack:
                stack.pop()
        elif ln.startswith('[SIDE+]') or ln.startswith('[SIDE-]'):
            continue
        elif ln.startswith('[GDRAW]'):
            m = re.match(r'\[GDRAW\]\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S+)', ' '.join(ln.split()))
            if int(m.group(1)) >= 5:
                seq.append([m.group(2), m.group(3), m.group(4),
                            stack[-1] if stack else '?', ''])
    return seq


def main():
    cid = sys.argv[1]
    pylog = sys.argv[2]
    oseq, seed = parse_oracle(cid)
    pseq = parse_py(pylog)
    print('oracle draws: %d   py draws: %d' % (len(oseq), len(pseq)))
    # 逐位对齐（序齐：两侧装配抽一笔对应一笔，除 py 多笔外应全同）
    ctx = int(sys.argv[sys.argv.index('--ctx') + 1]) if '--ctx' in sys.argv else 3
    i = j = 0
    diffs = 0
    while i < len(oseq) and j < len(pseq):
        o = oseq[i]
        p = pseq[j]
        if (o[0], o[1], o[2]) == (p[0], p[1], p[2]):
            i += 1
            j += 1
            continue
        # 尝试跳过 py 侧多笔（连续不同），或 oracle 侧多笔
        print('DIVERGENCE at o[%d] vs p[%d]:' % (i, j))
        for k in range(max(0, i - ctx), min(len(oseq), i + ctx + 2)):
            o_ = oseq[k]
            print('  O%4d %-11s %-6s %-6s @%s' % (k, o_[0], o_[1], o_[2], o_[3] or '-'))
        print()
        for k in range(max(0, j - ctx), min(len(pseq), j + ctx + 2)):
            p_ = pseq[k]
            print('  P%4d %-11s %-6s %-6s @%s' % (k, p_[0], p_[1], p_[2], p_[3] or '-'))
        diffs += 1
        break
    if not diffs:
        print('FULLY ALIGNED (draw-for-draw)')


if __name__ == '__main__':
    main()

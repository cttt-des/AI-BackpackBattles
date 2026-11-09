# -*- coding: utf-8 -*-
"""np51㊳终⑬ 全裸流对位：gd [GDRAW]（含伤害掷点可见化）vs oracle [BARE]（BareRngLog）。
用法（分片并行）:
    python -X utf8 tools/_np51_bare_align.py --worker <bucket_file>
    python -X utf8 tools/_np51_bare_align.py <case_id>        # 单场
每场产 output/_expand/forensic/<case>/bare_align.txt：
  首个失配窗 ±6 行 + gd 缺/多判读。前提：oracle 侧 replay 需先行跑过
  （tools/_np51_oracle_bare.py），产物 output/_expand/forensic/<case>/bare/oracle/<case>/rng_log.txt。
"""
import sys, os, re, io, json, glob, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + '/tools')
import godot_headless as gh


def parse_gdraw_lastpass(L):
    g = []
    for l in io.open(L, encoding='utf-8', errors='replace'):
        m = re.match(r'\[GDRAW\] (\d+) (\S+) (\S+) (\S+) => (\S+)', l.strip())
        if m:
            g.append((int(m.group(1)), m.group(2), m.group(3), m.group(4), m.group(5)))
    ps = []
    cur = []
    prev = 10 ** 9
    for r in g:
        if r[0] < prev:
            if cur:
                ps.append(cur)
            cur = []
        cur.append(r)
        prev = r[0]
    if cur:
        ps.append(cur)
    gp = max(ps, key=len)
    return [(r[1], r[2], r[3], r[4]) for r in gp]


def parse_bare_all(L):
    O = []
    for l in io.open(L, encoding='utf-8', errors='replace'):
        s = l.strip()
        if not s.startswith('[BARE]'):
            continue
        m = re.match(r'\[BARE\] randf_range (\S+) (\S+) => (\S+)', s)
        if m:
            O.append(('randf_range', m.group(1), m.group(2), m.group(3)))
            continue
        m = re.match(r'\[BARE\] randi_range (\S+) (\S+) => (\S+)', s)
        if m:
            O.append(('randi_range', m.group(1), m.group(2), m.group(3)))
            continue
        m = re.match(r'\[BARE\] (randf|randi) => (\S+)', s)
        if m:
            O.append((m.group(1), '0', '0', m.group(2)))
    return O


def main():
    args = sys.argv[1:]
    cids = []
    if args and args[0] == '--worker':
        cids = [x.strip() for x in io.open(args[1], encoding='utf-8').read().split() if x.strip()]
    else:
        cids = [x.strip() for x in args if x.strip()]
    for cid in cids:
        fdir = os.path.join(ROOT, 'output', '_expand', 'forensic', cid)
        # 1) gd 重放（当前门控表 + DRAWSEQ）
        gdir = os.path.join(fdir, 'bare_gd')
        shutil.rmtree(gdir, ignore_errors=True)
        os.makedirs(gdir, exist_ok=True)
        env = {'ORACLE_ALIGN_CASES_JSON': os.path.join(ROOT, 'gd_core_test', 'expand_align_cases.json').replace(os.sep, '/'),
               'ORACLE_ALIGN_FIGHTS_ROOT': os.path.join(ROOT, 'output/oracle/expand/fights').replace(os.sep, '/'),
               'ORACLE_ALIGN_OUT': gdir.replace(os.sep, '/'), 'ORACLE_ALIGN_CASES': cid,
               'ORACLE_ALIGN_CHUNK': '0', 'ORACLE_ALIGN_DRAWSEQ': '1'}
        rc, _, log = gh.run(gh.cmd(project=os.path.join(ROOT, 'gd_core_test'), script='OracleAlignBattle.gd'),
                            label='ba_g_%d' % os.getpid(), env_extra=env, timeout=900)
        logs = sorted(glob.glob(os.path.join(ROOT, 'output', '_recovery', 'godot_logs', 'ba_g_%d_*.log' % os.getpid())),
                      key=os.path.getmtime)
        if not logs:
            print('[ba][FAIL]', cid, 'no gd log')
            continue
        G = parse_gdraw_lastpass(logs[-1])
        # 2) oracle [BARE]（复用先行 replay 的 stdout 日志：label 前缀 ba_o_）
        ologs = sorted(glob.glob(os.path.join(ROOT, 'output', '_recovery', 'godot_logs', 'ba_o_*.log')),
                       key=os.path.getmtime)
        if not ologs:
            print('[ba][FAIL]', cid, 'oracle bare log missing（先跑 _np51_oracle_bare.py）')
            continue
        # 取内容含本 case 的最新日志
        O = None
        for L in reversed(ologs):
            txt = io.open(L, encoding='utf-8', errors='replace').read()
            if cid in txt and '[BARE]' in txt:
                O = parse_bare_all(L)
                break
        if not O:
            print('[ba][FAIL]', cid, 'oracle bare rows not found')
            continue
        # 3) 战斗段起点：各自最后一段 ≥8 连续 (0.95,1.05)（开战 prepareItems
        #    jitter 签名；bootstrap/generation 段在前，正式战斗段在后）。
        def battle_start(rows):
            # 自尾部向前的第一处命中 = 最后一段战斗（官方 pass）；再回退到该
            # ≥8 连 (0.95,1.05) run 的【起始】——两侧 run 长度可能差 1，取
            # 起点（前一行非 (0.95,1.05)）保证锚位语义一致。
            i = len(rows) - 8
            while i >= 0:
                if all(rows[i + k][:3] == ('randf_range', '0.95', '1.05') for k in range(8)):
                    st = i
                    while st > 0 and rows[st - 1][:3] == ('randf_range', '0.95', '1.05'):
                        st -= 1
                    return st
                i -= 1
            return None
        i0 = battle_start(G)
        j0 = battle_start(O)
        if i0 is None or j0 is None:
            print('[ba][FAIL]', cid, 'battle-prep signature not found')
            continue
        # 对齐：从战斗段起点线性扫，首个失配即报
        bad = None
        for k in range(0, min(len(G) - i0, len(O) - j0)):
            if G[i0 + k][1:] != O[j0 + k][1:]:
                bad = k
                break
        rep = io.open(os.path.join(fdir, 'bare_align.txt'), 'w', encoding='utf-8')
        rep.write('case=%s\ngd_battle_draws=%d oracle_battle_window=%d anchor=(%d,%d)\n' % (cid, len(G), len(O), i0, j0))
        if bad is None:
            rep.write('FULLY ALIGNED after anchor (min window %d)\n' % min(len(G) - i0, len(O) - j0))
            rep.close()
            print('[ba]', cid, 'FULLY ALIGNED after anchor')
            continue
        rep.write('first mismatch at +%d\n' % bad)
        for x in range(max(1, bad - 6), min(min(len(G) - i0, len(O) - j0), bad + 8)):
            mark = '>>' if x == bad else '  '
            rep.write(' %s K+%d %s\n %s O+%d %s\n' % (mark, x, G[i0 + x][1:], mark, x, O[j0 + x][1:]))
        rep.close()
        print('[ba]', cid, 'mismatch at +%d → bare_align.txt' % bad)


if __name__ == '__main__':
    main()

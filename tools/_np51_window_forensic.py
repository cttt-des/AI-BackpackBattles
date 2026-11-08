# -*- coding: utf-8 -*-
"""np51㊲ 窗口取证批扫：oracle 计数器重放 + gd 栈重放 + EVENT-st 对位 → 首失配窗报告
用法（分片并行）:
    python -X utf8 tools/_np51_window_forensic.py --worker <bucket_file>
    python -X utf8 tools/_np51_window_forensic.py <case_id>        # 单场
每个 case 产 output/_expand/forensic/<case>/window_report.txt：
  - 首个 EVENT st 失配序号与两侧 3 行上下文
  - 失配窗内 oracle [DRAW] 全序列（含隐形笔）vs gd 可见抽行
"""
import sys, os, re, json, io, shutil, glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + '/tools')
import godot_headless as gh


def oracle_replay(cid, outdir):
    outdir = os.path.join(outdir, 'oracle')  # ★ np51㊲：oracle/gd 分目录——gd rmtree 曾删 oracle 产物
    cs = json.load(io.open(os.path.join(ROOT, 'output/oracle/expand/cases.json'), encoding='utf-8'))
    cs = cs['cases'] if isinstance(cs, dict) else cs
    entry = next(c for c in cs if c['case_id'] == cid)
    proj = os.path.join(ROOT, 'output', '_expand', 'oracle_proj')
    d = os.path.join(outdir, cid)
    if os.path.isdir(d):
        shutil.rmtree(d)
    lbl = 'wf_o_%d' % os.getpid()
    env = {'ORACLE_ONLY_CASES': cid, 'ORACLE_FIGHTS_ROOT': outdir.replace(os.sep, '/'),
           'ORACLE_FIGHT_CHUNK': '60', 'ORACLE_RNG_TRACE': '1', 'ORACLE_STACKTRACE': '1',
           'ORACLE_CASE_ENTRY': json.dumps(entry, ensure_ascii=False)}
    rng_log = os.path.join(outdir, cid, 'rng_log.txt')  # ORACLE_FIGHTS_ROOT=outdir ⇒ outdir/<case>/
    if os.path.exists(rng_log):
        logs = sorted(glob.glob(os.path.join(ROOT, 'output', '_recovery', 'godot_logs', lbl + '_*.log')),
                      key=os.path.getmtime)
        return rng_log, logs[-1] if logs else None
    rc, _, log = gh.run(gh.cmd(project=proj, script='oracle_fight.gd'), label=lbl,
                        env_extra=env, timeout=900)
    logs = sorted(glob.glob(os.path.join(ROOT, 'output', '_recovery', 'godot_logs', lbl + '_*.log')),
                  key=os.path.getmtime)
    return rng_log, logs[-1] if logs else None


def gd_replay(cid, outdir):
    d = os.path.join(outdir, cid)
    if os.path.exists(os.path.join(d, 'rng_trace.txt')):
        return os.path.join(d, 'rng_trace.txt'), None  # 复用已有 gd 产物
    if os.path.isdir(d):
        shutil.rmtree(d)
    # ★ np51㊲修：ORACLE_FIGHTS_ROOT 须指 oracle 子目录（rng_state.txt 注入源
    #   在该处——子目录隔离后 fdir 根下已无产物，漏指致注入静默失效）。
    env = {'ORACLE_ALIGN_CASES_JSON': os.path.join(ROOT, 'gd_core_test', 'expand_align_cases.json').replace(os.sep, '/'),
           'ORACLE_ALIGN_FIGHTS_ROOT': os.path.join(outdir, 'oracle').replace(os.sep, '/'),
           'ORACLE_ALIGN_OUT': outdir, 'ORACLE_ALIGN_CASES': cid, 'ORACLE_ALIGN_CHUNK': '0',
           'ORACLE_ALIGN_TRACE': '1', 'ORACLE_ALIGN_STACKTRACE': '1',
           'ORACLE_ALIGN_DRAWSEQ': '1'}
    rc, _, glog = gh.run(gh.cmd(project=os.path.join(ROOT, 'gd_core_test'), script='OracleAlignBattle.gd'),
                      label='wf_g_%d' % os.getpid(), env_extra=env, timeout=900)
    return os.path.join(d, cid, 'rng_trace.txt'), glog


def parse_oracle_states(rng_log):
    """EVENT 行 → (log行号, type, st)"""
    evs = []
    for i, ln in enumerate(io.open(rng_log, encoding='utf-8', errors='replace')):
        m = re.match(r'\s*(\d+)\s+EVENT\s+(\S+)\s+=>.*st=(-?\d+)', ln)
        if m:
            evs.append((i + 1, m.group(2), m.group(3)))
    return evs


def parse_gd_states(trace):
    evs = []
    rows = []
    for i, ln in enumerate(io.open(trace, encoding='utf-8', errors='replace')):
        t = [x for x in ln.split() if x != '']
        rows.append((i + 1, t))
        if len(t) >= 3 and t[1] == 'EVENT':
            evs.append((i + 1, t[2], t[-1]))
    return evs, rows


def main():
    args = sys.argv[1:]
    cids = []
    if args and args[0] == '--worker':
        cids = [x.strip() for x in io.open(args[1], encoding='utf-8').read().split() if x.strip()]
    else:
        cids = [x.strip() for x in args if x.strip()]
    for cid in cids:
        fdir = os.path.join(ROOT, 'output', '_expand', 'forensic', cid, 'window')
        os.makedirs(fdir, exist_ok=True)
        try:
            ora_log, cnt_log = oracle_replay(cid, fdir)
            gd_trace, gd_log = gd_replay(cid, fdir)
        except Exception as e:
            print('[wf][FAIL]', cid, e)
            continue
        if gd_log and os.path.exists(gd_log):
            gdraws = [l.strip() for l in io.open(gd_log, encoding='utf-8', errors='replace') if l.strip().startswith('[GDRAW]')]
            with io.open(os.path.join(fdir, 'gdraw.txt'), 'w', encoding='utf-8') as gf:
                gf.write('\n'.join(gdraws))
        o_evs = parse_oracle_states(ora_log)
        g_evs, g_rows = parse_gd_states(gd_trace)
        n = min(len(o_evs), len(g_evs))
        bad = next((i for i in range(n) if o_evs[i][2] != g_evs[i][2]), None)
        rep = io.open(os.path.join(fdir, 'window_report.txt'), 'w', encoding='utf-8')
        rep.write('case=%s\nEVENT: oracle=%d gd=%d\n' % (cid, len(o_evs), len(g_evs)))
        if bad is None:
            rep.write('EVENT st 全部一致（分歧在事件内容层）\n')
            rep.close()
            print('[wf]', cid, 'EVENT 全对（内容层分歧）')
            continue
        rep.write('首个 EVENT st 失配序号=%d\n' % bad)
        for x in range(max(0, bad - 2), min(n, bad + 3)):
            mark = '>>' if x == bad else '  '
            rep.write(' %s O(line=%d,type=%s) | K(line=%d,type=%s)\n' % (
                mark, o_evs[x][0], o_evs[x][1], g_evs[x][0], g_evs[x][1]))
        # 失配窗：oracle 前 mismatch EVENT 的行号 → 当前 EVENT 行号；gd 同理
        o_from = o_evs[bad - 1][0] if bad >= 1 else 1
        o_to = o_evs[bad][0]
        g_from = g_evs[bad - 1][0] if bad >= 1 else 1
        g_to = g_evs[bad][0]
        rep.write('\n=== oracle log %d..%d 行 ===\n' % (o_from, o_to))
        for i, ln in enumerate(io.open(ora_log, encoding='utf-8', errors='replace')):
            if o_from <= i + 1 <= o_to:
                rep.write('  ' + ln.rstrip()[:170] + '\n')
        rep.write('\n=== gd trace %d..%d 行 ===\n' % (g_from, g_to))
        for i, ln in enumerate(io.open(gd_trace, encoding='utf-8', errors='replace')):
            if g_from <= i + 1 <= g_to:
                rep.write('  ' + ln.rstrip()[:170] + '\n')
        # oracle 计数器窗口（[DRAW] 行按时间过滤——窗为 EVENT 间，取 t 在窗口内）
        if cnt_log and os.path.exists(cnt_log):
            rep.write('\n=== oracle [DRAW]（全部 pass，按 seq）===\n')
            for ln in io.open(cnt_log, encoding='utf-8', errors='replace'):
                if '[DRAW]' in ln:
                    rep.write('  ' + ln.rstrip()[:170] + '\n')
        rep.close()
        print('[wf]', cid, 'bad@%d → window_report.txt' % bad)


if __name__ == '__main__':
    main()

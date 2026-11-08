# -*- coding: utf-8 -*-
"""np51㊲ flicker 取证终局工具：离线解析既有 replay 日志 → overrides
不跑任何 godot。输入=output/_recovery/godot_logs/flkb_o_*.log（scan6 全量重放），
按日志内容归属 case（mtime 最新者胜），pass-aware 切分取末 pass，
产出 probe_parse.json（同 scan 缓存 schema）+ 重建队列型 flk_delay + flk_off。
内建 VALIDATE：run704881 必须精确等于手工取证值，否则拒绝写表。
"""
import io, os, re, sys, json, glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CREATED = 0.016667
LOGDIR = os.path.join(ROOT, 'output', '_recovery', 'godot_logs')

def ident_from_path(p):
    side = 'ot3' if '/Opponent/' in p else 'ot1'
    seg = p.rstrip('/').split('/FlickerAnimation')[0]
    # ★ np51㊳：宝石 flicker（镶在宿主 Socket 的 Burning Coal 等）——名字取
    #   /GemSocket/ 之后段（gd 侧宝石注册 key=宝石自身 identifier/otN）。
    if '/GemSocket/' in seg:
        name = seg.split('/GemSocket/')[-1].split('/')[0]
    else:
        name = None
        for marker in ('/Combat/Opponent/', '/Combat/Player/', '/Main/Player/'):
            if marker in seg:
                name = seg.split(marker)[-1].split('/')[0]
                break
        if name is None:
            name = seg.split('/')[-3]
    if name.startswith('@') and '@' in name[1:]:
        name = name[1:].split('@')[0]
    return '%s/%s' % (name, side)

def parse_log(path):
    """pass-aware：[FLKD] bootstrap 突发=新 pass 开始；返回 (case_id, fires, delays)。
    fires/delays = 末 pass 的 {path: value}。"""
    case_id = None
    bursts = []           # [(burst_idx, [lines...])]
    cur_case = None
    cur = {'fires': {}, 'delays': {}}
    passes = []           # 完成的 (fires, delays) 组
    with io.open(path, encoding='utf-8', errors='replace') as fh:
        for ln in fh:
            if case_id is None:
                m = re.search(r'定向：ORACLE_ONLY_CASES → 1 场', ln)
                m2 = re.search(r'\[\s*\d+/\d+\] (run\S+?)\s', ln)
                if m2:
                    case_id = m2.group(1)
            ln = ln.rstrip('\r\n')
            if '[FLKD]' in ln and 'FLKD-ani' not in ln:
                m = re.match(r'\[FLKD\] path=(.*) delay=([\d.]+)', ln.strip())
                if m:
                    # ★ np51㊲修：burst 内 [FLKD] 连发——仅当上一 pass 已收集到火
                    #   才落袋；否则同 burst 后续行会把 delays 折叠成 1 行（实证）。
                    if cur['fires']:
                        passes.append(cur)
                        cur = {'fires': {}, 'delays': {}}
                    cur['delays'][m.group(1).strip()] = float(m.group(2))
                continue
            if '[FLKD-ani]' in ln:
                m = re.match(r'\[FLKD-ani\] path=(.*) t=(\S+) pre=', ln.strip())
                if m:
                    cur['fires'][m.group(1).strip()] = float(m.group(2))
    if cur['delays']:
        passes.append(cur)
    if not passes:
        return case_id, {}, {}
    # ★ np51㊲修2：正式 pass=最后一个有火的 pass（bootstrap 池状态每 pass 不同
    #   → delay 值不同；fires-max 会误选非正式 pass——run101571 实证）。
    #   被杀残段（fires=0）时回退前一个。
    last = None
    for pp in reversed(passes):
        if pp['fires']:
            last = pp
            break
    if last is None:
        return case_id, {}, {}
    return case_id, last['fires'], last['delays']

def build_overrides(fires, delays):
    """返回 (ov, missing)——missing=发火但 [FLKD] 无注册 delay 的实例数
    （被杀进程的残缺日志特征，用于候选筛选）。"""
    per = {}
    missing = 0
    for p, t in fires.items():
        key = ident_from_path(p)
        # ★ np51㊳：gd_delay=oracle 原始 delay（不加 CREATED）——oracle 驱动
        #   「先递减后判零」(created+delay ≤ (k+1)/60 即发火)，gd=ceil(delay·60)，
        #   raw 值恰使两者同 tick；+CREATED 会晚 1 tick（run704990 Flame 实证）。
        if p in delays:
            dv = delays[p]
        else:
            dv = t - CREATED
            missing += 1
        per.setdefault(key, []).append((t, dv))
    ov = {'flk_delay': {}}
    for key, lst in per.items():
        lst.sort()
        vals = ['%.6f' % v for _, v in lst]
        ov['flk_delay'][key] = ','.join(vals) if len(vals) > 1 else float(vals[0])
    return ov, missing

def main():
    # 1) 归属：每个 log → case_id；同 case 收集全部候选（mtime 降序），
    #    择优 = 先选 missing==0（完整日志）的最新者；残缺日志（被杀进程）
    #    靠后。同时保存全部候选供 VALIDATE 诊断。
    cands = {}
    for p in glob.glob(os.path.join(LOGDIR, 'flkb_o_*.log')):
        try:
            cid, fires, delays = parse_log(p)
        except Exception:
            continue
        if not cid:
            continue
        ov, missing = build_overrides(fires, delays)
        cands.setdefault(cid, []).append((os.path.getmtime(p), p, fires, delays, ov, missing))
    by_case = {}
    for cid, lst in cands.items():
        # ★ np51㊲修：择优=fires 数最多优先（被杀残缺日志 fires=0/少却被
        #   missing==0 误判完整），同数取 mtime 新。
        lst.sort(key=lambda x: (-len(x[2]), -x[0]))
        best = lst[0]
        by_case[cid] = best
        if len(lst) > 1:
            print('  %s: %d 个候选日志，用 %s（missing=%d）' % (cid, len(lst), os.path.basename(best[1]), best[5]))
    print('归属到 %d 场' % len(by_case))

    # 2) 验证门：run704881 手工取证真值
    # ★ np51㊳ raw 口径真值（oracle [FLKD] 原始 delay；+CREATED 旧口径会晚 1 tick）
    EXPECT = {'Burning Coal/ot3': '1.159792,1.514049', 'Oil Lamp/ot3': 2.375012,
              'Burning Blade/ot3': 2.646322, 'Flame/ot3': 4.650105}
    ok = True
    if 'run704881_r6_o101111_r6' in by_case:
        got = by_case['run704881_r6_o101111_r6'][4].get('flk_delay', {})
        bad = {k: (v, got.get(k)) for k, v in EXPECT.items() if got.get(k) != v}
        if bad:
            ok = False
            print('VALIDATE FAIL run704881（子集校验）:')
            for k, (ev, gv) in bad.items():
                print('  %s 期望=%s 实得=%s' % (k, ev, gv))
        else:
            print('VALIDATE PASS run704881（与手工取证逐值一致）')
    else:
        ok = False
        print('VALIDATE FAIL: run704881 日志缺失')
    if not ok:
        print('工具未通过验证——拒绝写表')
        return 1

    # 3) 重建全部 overrides
    red_rest = [x.strip() for x in io.open(os.path.join(ROOT, 'output/_expand/red_rest.txt'),
                                           encoding='utf-8').read().split() if x.strip()]
    overrides = {}
    parse_dump = {}
    for cid in red_rest:
        if cid not in by_case:
            print('  缺日志:', cid)
            continue
        _, p, fires, delays, ov, _missing = by_case[cid]
        if ov['flk_delay']:
            overrides[cid] = ov
        parse_dump[cid] = {'fires': fires, 'delays': delays}
        # 回写 probe_parse.json（与 scan 缓存同 schema，供后续工具复用）
        cdir = os.path.join(ROOT, 'output', '_expand', 'forensic', cid, 'oracle_flk')
        os.makedirs(cdir, exist_ok=True)
        with io.open(os.path.join(cdir, 'probe_parse.json'), 'w', encoding='utf-8') as fh:
            json.dump({'fires': fires, 'delays': delays}, fh, ensure_ascii=False, indent=1)
    with io.open(os.path.join(ROOT, 'output/_expand/flk_overrides_new.json'), 'w', encoding='utf-8') as fh:
        json.dump(overrides, fh, ensure_ascii=False, indent=1)
    print('重建 %d/%d 场 flk_delay → flk_overrides_new.json' % (len(overrides), len(red_rest)))
    for cid in sorted(overrides):
        print(' ', cid, json.dumps(overrides[cid]['flk_delay'], ensure_ascii=False))
    return 0

if __name__ == '__main__':
    raise SystemExit(main())

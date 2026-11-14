# -*- coding: utf-8 -*-
"""A.1 取证：单场 oracle [BARE] 全裸流重放（隔离工程副本）。

用法:
    python -X utf8 tools/_a1_oracle_bare_case.py <case_id> [case_id ...]

产物: output/_a1/bare_oracle/<case_id>/rng_log.txt 等（正式语料文件不触碰）
     + output/_a1/bare_stdout_<case_id>.log（含 [BARE]/[FLKD] 行）
"""
import sys, os, io, json, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + '/tools')
import godot_headless as gh

PROJ_DST = os.path.join(ROOT, 'output', '_a1', 'oracle_proj')
OUT_ROOT = os.path.join(ROOT, 'output', '_a1', 'bare_oracle')


def ensure_proj(case_ids):
    """复制 oracle/ 工程副本并注入单场 fights.json + expand history.db。
    旧语料场（oracle/fights.json 内，如 run583_r11）直接用原工程不复制。"""
    cases_raw = json.load(io.open(os.path.join(ROOT, 'output/oracle/expand/cases.json'), encoding='utf-8'))
    if isinstance(cases_raw, dict) and 'cases' in cases_raw:
        cases_raw = cases_raw['cases']
    sel = [c for c in cases_raw if c['case_id'] in set(case_ids)]
    missing = set(case_ids) - {c['case_id'] for c in sel}
    old_raw = json.load(io.open(os.path.join(ROOT, 'oracle/fights.json'), encoding='utf-8'))
    if isinstance(old_raw, dict) and 'cases' in old_raw:
        old_raw = old_raw['cases']
    if not missing:
        pass
    else:
        old_sel = [c for c in old_raw if c['case_id'] in missing]
        if len(old_sel) != len(missing):
            raise SystemExit('cases.json 缺场: %s' % (missing - {c['case_id'] for c in old_sel}))
        # 旧语料场合并进选表（统一走打补丁的副本，取证标记必须生效）
        sel = sel + old_sel
        missing = set(case_ids) - {c['case_id'] for c in sel}
        if missing:
            raise SystemExit('cases.json 缺场: %s' % missing)
    if os.path.isdir(PROJ_DST):
        shutil.rmtree(PROJ_DST)
    shutil.copytree(os.path.join(ROOT, 'oracle'), PROJ_DST)
    old_ids = {c['case_id'] for c in old_raw}
    if all(c['case_id'] in old_ids for c in sel):
        # 纯旧语料：fights.json 已含这些场、原 history.db 即其库——只注入选场表
        json.dump({'cases': sel}, io.open(os.path.join(PROJ_DST, 'fights.json'), 'w', encoding='utf-8'))
    else:
        json.dump({'cases': sel}, io.open(os.path.join(PROJ_DST, 'fights.json'), 'w', encoding='utf-8'))
        os.makedirs(os.path.join(PROJ_DST, 'data'), exist_ok=True)
        shutil.copyfile(os.path.join(ROOT, 'output/oracle/expand/data/history.db'),
                        os.path.join(PROJ_DST, 'data', 'history.db'))
    _patch_bare_stack()
    return PROJ_DST


def _patch_bare_stack():
    """给副本 BareRngLog 加 ORACLE_BARESTACK=1 栈帧打印（取证用，零 rng 消耗）。"""
    import re
    p = os.path.join(PROJ_DST, 'Utility', 'BareRngLog.gd')
    s = io.open(p, encoding='utf-8', newline='').read()
    if '_bare_stack' in s:
        return
    s = re.sub(
        r'print\("\[BARE\] (randf_range|randf|randi_range|randi) ", from, " ", to, " => ", r, " st=", get_state\(\)\)',
        lambda m: 'print("[BARE] %s ", from, " ", to, " => ", r, " st=", get_state(), '
                  '("] [" + _bare_frames() + "]" if _bare_stack else ""))' % m.group(1),
        s)
    s = s.replace('var _barelog := false',
                  'var _barelog := false\nvar _bare_stack := false\n\n\n'
                  'func _bare_frames() -> String:\n'
                  '\tvar frames := []\n'
                  '\tvar st = get_stack()\n'
                  '\tif st != null:\n'
                  '\t\tfor i in range(1, min(8, st.size())):\n'
                  '\t\t\tframes.append("%s:%d:%s" % [String(st[i]["source"]).get_file(),\n'
                  '\t\t\t\t\tint(st[i]["line"]), String(st[i]["function"])])\n'
                  '\treturn PoolStringArray(frames).join("<-")')
    s = s.replace('_barelog = OS.get_environment("ORACLE_BARELOG") != ""',
                  '_barelog = OS.get_environment("ORACLE_BARELOG") != ""\n'
                  '\t_bare_stack = OS.get_environment("ORACLE_BARESTACK") != ""')
    io.open(p, 'w', encoding='utf-8', newline='').write(s)
    # Item._ready 入口打 [ITEMREADY] 路径标记（ORACLE_ITEMMARK，零 rng 消耗）——
    # 与 [BARE] 行交错后可做 oracle 侧逐抽→物品归属。
    p2 = os.path.join(PROJ_DST, 'Items', 'Item.gd')
    s2 = io.open(p2, encoding='utf-8', newline='').read()
    if 'ORACLE_ITEMMARK' not in s2:
        for nl in ('\r\n', '\n'):
            anchor = 'func _ready() -> void :%s\tif not pooled:' % nl
            if anchor in s2:
                s2 = s2.replace(anchor, 'func _ready() -> void :%s'
                                '\tif OS.get_environment("ORACLE_ITEMMARK") != "":%s'
                                '\t\tprint("[ITEMREADY] ", get_path())%s'
                                '\tif not pooled:' % (nl, nl, nl), 1)
                break
        io.open(p2, 'w', encoding='utf-8', newline='').write(s2)
    # Item._init（成员初始化器之后）打 [ITEMINIT]——ctor 抽归属锚（附脚本路径）
    if '[ITEMINIT]' not in s2:
        for nl in ('\r\n', '\n'):
            anchor = 'func _ready() -> void :%s' % nl
            if anchor in s2:
                s2 = s2.replace(anchor, 'func _init() -> void :%s'
                                '\tif OS.get_environment("ORACLE_ITEMMARK") != "":%s'
                                '\t\tprint("[ITEMINIT] ", get_script().resource_path, " ", get_class())%s'
                                '%s%s' % (nl, nl, nl, nl, anchor), 1)
                break
        io.open(p2, 'w', encoding='utf-8', newline='').write(s2)
    # PotionConnector._ready 打 [CONNREADY]——connector (0.9,1.1) 抽归属锚
    p3 = os.path.join(PROJ_DST, 'Items', 'Animations', 'PotionConnector.gd')
    s3 = io.open(p3, encoding='utf-8', newline='').read()
    if 'ORACLE_ITEMMARK' not in s3:
        for nl in ('\r\n', '\n'):
            anchor = 'func _ready() -> void :%s\tmodulate.g' % nl
            if anchor in s3:
                s3 = s3.replace(anchor, 'func _ready() -> void :%s'
                                '\tif OS.get_environment("ORACLE_ITEMMARK") != "":%s'
                                '\t\tprint("[CONNREADY] ", get_path())%s'
                                '\tmodulate.g' % (nl, nl, nl), 1)
                break
        io.open(p3, 'w', encoding='utf-8', newline='').write(s3)
    # Item.trigger 入口打 [TRIG]（ORACLE_TRIGMARK）——冷却触发相位取证
    p4 = os.path.join(PROJ_DST, 'Items', 'Item.gd')
    s4 = io.open(p4, encoding='utf-8', newline='').read()
    if 'ORACLE_TRIGMARK' not in s4:
        for nl in ('\r\n', '\n'):
            anchor = 'func trigger():%s\titerationCooldown = adjustCooldown()' % nl
            if anchor in s4:
                s4 = s4.replace(anchor, 'func trigger():%s'
                                '\tif OS.get_environment("ORACLE_TRIGMARK") != "":%s'
                                '\t\tprint("[TRIG] t=", Util.time, " ph=",%s'
                                '\t\t\t\tEngine.get_physics_frames(), " ", get_path())%s'
                                '\titerationCooldown = adjustCooldown()' % (nl, nl, nl, nl), 1)
                break
        io.open(p4, 'w', encoding='utf-8', newline='').write(s4)


def main():
    cids = [x.strip() for x in sys.argv[1:] if x.strip()]
    if not cids:
        raise SystemExit(__doc__)
    proj = ensure_proj(cids)
    os.makedirs(OUT_ROOT, exist_ok=True)
    for cid in cids:
        outdir = os.path.join(OUT_ROOT, cid)
        shutil.rmtree(outdir, ignore_errors=True)
        os.makedirs(outdir, exist_ok=True)
        env = {'ORACLE_ONLY_CASES': cid,
               'ORACLE_FIGHTS_ROOT': outdir.replace(os.sep, '/'),
               'ORACLE_FIGHT_CHUNK': '1',
               'ORACLE_RNG_TRACE': '1',
               'ORACLE_BARELOG': '1',
               'ORACLE_BARESTACK': os.environ.get('A1_BARESTACK', ''),
               'ORACLE_ITEMMARK': '1',
               'ORACLE_FLKPROBE': '1',
               'ORACLE_TIMER_POLL': os.environ.get('A1_TIMER_POLL', ''),
               'ORACLE_DEBUG': os.environ.get('A1_TIMER_DEBUG', ''),
               'ORACLE_TRIGMARK': os.environ.get('A1_TRIGMARK', '')}
        rc, out, log = gh.run(gh.cmd(project=proj, script='oracle_fight.gd'),
                              label='a1o_%s' % cid[:20], env_extra=env, timeout=1200)
        stdout_path = os.path.join(ROOT, 'output', '_a1', 'bare_stdout_%s.log' % cid)
        io.open(stdout_path, 'w', encoding='utf-8').write(out or '')
        n_bare = sum(1 for l in (out or '').splitlines() if l.startswith('[BARE]'))
        n_flkd = sum(1 for l in (out or '').splitlines() if l.startswith('[FLKD]'))
        ok = os.path.exists(os.path.join(outdir, cid, 'rng_state.txt'))
        print('[a1o]', cid, 'rc', rc, 'rng_state', ok, '[BARE]', n_bare, '[FLKD]', n_flkd)


if __name__ == '__main__':
    main()

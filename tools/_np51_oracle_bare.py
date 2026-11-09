# -*- coding: utf-8 -*-
"""np51㊳终⑬ oracle [BARE] 取证批扫：ORACLE_BARELOG=1 重放（label=ba_o_，供
_np51_bare_align.py 消费）。用法（分片并行）:
    python -X utf8 tools/_np51_oracle_bare.py --worker <bucket_file>
    python -X utf8 tools/_np51_oracle_bare.py <case_id>
产物：output/_expand/forensic/<case>/bare/oracle/<case>/rng_log.txt（stdout 日志含 [BARE] 行）。
"""
import sys, os, io, json, glob, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + '/tools')
import godot_headless as gh


def main():
    args = sys.argv[1:]
    cids = []
    if args and args[0] == '--worker':
        cids = [x.strip() for x in io.open(args[1], encoding='utf-8').read().split() if x.strip()]
    else:
        cids = [x.strip() for x in args if x.strip()]
    cs = json.load(io.open(os.path.join(ROOT, 'output/oracle/expand/cases.json'), encoding='utf-8'))
    cs = cs['cases'] if isinstance(cs, dict) and 'cases' in cs else cs
    for cid in cids:
        entry = next((c for c in cs if c['case_id'] == cid), None)
        if entry is None:
            print('[ob][FAIL]', cid, 'not in cases.json')
            continue
        outdir = os.path.join(ROOT, 'output', '_expand', 'forensic', cid, 'bare')
        shutil.rmtree(outdir, ignore_errors=True)
        os.makedirs(outdir + '/oracle', exist_ok=True)
        env = {'ORACLE_ONLY_CASES': cid, 'ORACLE_FIGHTS_ROOT': (outdir + '/oracle').replace(os.sep, '/'),
               'ORACLE_FIGHT_CHUNK': '60', 'ORACLE_RNG_TRACE': '1', 'ORACLE_BARELOG': '1',
               'ORACLE_CASE_ENTRY': json.dumps(entry, ensure_ascii=False)}
        rc, _, log = gh.run(gh.cmd(project=os.path.join(ROOT, 'output', '_expand', 'oracle_proj'),
                                   script='oracle_fight.gd'), label='ba_o', env_extra=env, timeout=1200)
        ok = os.path.exists(outdir + '/oracle/' + cid + '/rng_log.txt')
        print('[ob]', cid, 'rc', rc, 'rng_log', ok)


if __name__ == '__main__':
    main()

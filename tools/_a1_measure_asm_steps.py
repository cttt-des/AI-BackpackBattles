# -*- coding: utf-8 -*-
"""A.1 诊断：py 装配期 PCG 总步数 vs oracle（rng_state 反推）。

用法:
    python -X utf8 tools/_a1_measure_asm_steps.py <case_id> [case_id ...]
    python -X utf8 tools/_a1_measure_asm_steps.py --file <ids.txt>

对每场输出: oracle_steps / py_steps / delta。
oracle_steps = advance(post_seed_state → rng_state.txt state) 的步数。
py_steps     = 引擎装配完成（未注入 rng_state）时 ctx.rng 相对 post_seed_state 的步数。
"""
import sys, os, io, json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

M = 6364136223846793005
INC = 2885390081777926815
MASK = (1 << 64) - 1


def pcg_seed(v):
    s = 0
    s = (s * M + INC) & MASK
    s = (s + v) & MASK
    s = (s * M + INC) & MASK
    return s


def steps_from(st_seed, st_target, cap=100000):
    s = st_seed
    for k in range(1, cap):
        s = (s * M + INC) & MASK
        if s == (st_target & MASK):
            return k
    return None


def main():
    args = sys.argv[1:]
    cids = []
    if args and args[0] == '--file':
        cids = [x.strip() for x in io.open(args[1], encoding='utf-8').read().split() if x.strip()]
    else:
        cids = [x.strip() for x in args if x.strip()]

    from simulator.data import load_items, load_characters
    from simulator.lineup import load_lineup
    from simulator.gd_core_engine import GDCoreEngine

    if os.environ.get('A1_GDRAW') == '1':
        # py 侧全量逐抽 [GDRAW]（镜像 gd 宿主 ORACLE_ALIGN_DRAWSEQ=1）
        from gd_core_py.gd_core import CoreRng as _crng_mod
        _orig_fields = _crng_mod.CoreRng._init_fields

        def _fields2(self):
            _orig_fields(self)
            self.draw_seq = 0
        _crng_mod.CoreRng._init_fields = _fields2

    if os.environ.get('A1_ITEM_MARK') == '1':
        # 物品归属标记：_place 前后打 [ITEM] 行，与 [GDRAW] 交错定位每笔抽的归属
        import simulator.gd_core_engine as _eng

        _orig_place = _eng.GDCoreEngine._place

        def _place2(self, ctx, chr_, key, row, col, rot, owner_type, ready=True,
                    sockets=None):
            print('[ITEM+] %s' % key)
            it = _orig_place(self, ctx, chr_, key, row, col, rot, owner_type,
                             ready=ready, sockets=sockets)
            print('[ITEM-] %s' % key)
            return it

        _eng.GDCoreEngine._place = _place2

        _orig_build = _eng.GDCoreEngine._build_side

        def _build2(self, ctx, chr_, lineup, owner_type, gem_lens=None):
            print('[SIDE+] %s' % owner_type)
            r = _orig_build(self, ctx, chr_, lineup, owner_type, gem_lens=gem_lens)
            print('[SIDE-] %s' % owner_type)
            return r

        _eng.GDCoreEngine._build_side = _build2

    item_db = load_items()
    character_db = load_characters()
    cases_raw = json.load(io.open(os.path.join(ROOT, 'output/oracle/expand/cases.json'), encoding='utf-8'))
    if isinstance(cases_raw, dict) and 'cases' in cases_raw:
        cases_raw = cases_raw['cases']
    cids_entry_seed = {c['case_id']: int(c['seed']) for c in cases_raw}
    fixture = {c['case_id']: c for c in json.load(
        io.open(os.path.join(ROOT, 'gd_core_test', 'expand_align_cases.json'), encoding='utf-8'))['cases']}

    for cid in cids:
        st_path = os.path.join(ROOT, 'output/oracle/expand/fights', cid, 'rng_state.txt')
        if not os.path.exists(st_path):
            print('%-40s 缺 rng_state.txt' % cid)
            continue
        # 注意：rng_state.txt 的 seed= 行是 current_seed（最后一笔前的 state），
        # 不是原始种子；真种子取 cases.json 的 seed 字段（= result.txt 的 seed 行）。
        state = None
        for ln in io.open(st_path, encoding='utf-8'):
            if ln.startswith('state='):
                state = int(ln.strip()[6:])
        seed = int(cids_entry_seed.get(cid))
        st_seed = pcg_seed(seed)
        o_steps = steps_from(st_seed, state)
        if o_steps is None:
            print('%-40s oracle state 不在 seed 轨迹上（seed=%d）' % (cid, seed))
            continue

        c = fixture[cid]
        player = load_lineup(os.path.join(ROOT, 'output/oracle/align_expand/lineups/oracle_%s_player.json' % cid))
        opponent = load_lineup(os.path.join(ROOT, 'output/oracle/align_expand/lineups/oracle_%s_opponent.json' % cid))
        p_gem_lens = [len(e.get('gems') or []) for e in c['player']['items']]
        o_gem_lens = [len(e.get('gems') or []) for e in c['opponent']['items']]
        eng = GDCoreEngine(player, opponent, item_db, character_db,
                           seed=seed, max_time=90.0,
                           below_master=True,
                           p_gem_lens=p_gem_lens, o_gem_lens=o_gem_lens,
                           reseed_after_player_character=True, post_seed_draws=0,
                           rng_state=None, label_rng_enabled=True)
        st_py = eng.ctx.rng.rng.get_state() & MASK
        p_steps = steps_from(st_seed, st_py)
        if p_steps is None:
            print('%-40s py state 不在 seed 轨迹上！' % cid)
            continue
        # 未传 activation_order 时 startBattle 内部自洗牌：消耗 (np-1)+(no-1) 笔
        # randi（CoreRng.shuffle，无 GDRAW 打点）——从总差里扣除即纯装配差。
        p_asm = p_steps - (len(eng.player_items) - 1) - (len(eng.opponent_items) - 1)
        print('%-40s seed=%d  oracle=%5d  py_asm=%5d  asm_delta=%+d   (py_total=%d)'
              % (cid, seed, o_steps, p_asm, p_asm - o_steps, p_steps))


if __name__ == '__main__':
    main()

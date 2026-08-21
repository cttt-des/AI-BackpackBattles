# -*- coding: utf-8 -*-
"""gui.py — 背包乱斗 战斗模拟器 桌面 GUI（tkinter）

从目录下的 lineups/ 文件夹选择任意两个阵容 JSON 进行战斗，
展示战斗过程日志与结果。可配置种子与模拟场数（蒙特卡洛）。

用法:
    python -m simulator.gui          # 开发态（lineups/ 在仓库根目录）
    打包后 BackpackSimulator.exe      # 冻结态（lineups/ 放在 exe 同目录）
"""
from __future__ import annotations

import json
import os
import random
import sys
import threading
import time
from typing import Dict, List, Optional, Tuple

import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox, filedialog

from . import simulate as sim
from .data import load_items, load_characters
from .lineup import load_lineup, LineupError, resolve_items


# ---------------- 路径解析 ----------------
def _app_dir() -> str:
    """程序所在目录：冻结态取 exe 目录，开发态取仓库根目录"""
    if getattr(sys, 'frozen', False):
        return os.path.dirname(os.path.abspath(sys.executable))
    return os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _lineups_dir() -> str:
    return os.path.join(_app_dir(), 'lineups')


# ---------------- 阵容扫描 ----------------
def scan_lineups(directory: str) -> List[Dict]:
    """扫描目录下的阵容 JSON，返回 [{path, name, character, items}]"""
    out = []
    if not os.path.isdir(directory):
        return out
    for fn in sorted(os.listdir(directory)):
        if not fn.lower().endswith('.json'):
            continue
        path = os.path.join(directory, fn)
        try:
            data = load_lineup(path)
        except Exception:
            continue
        meta = data.get('meta', {}) or {}
        name = meta.get('name') or os.path.splitext(fn)[0]
        char = data.get('character', '?')
        items = data.get('backpack', {}).get('items', [])
        out.append({
            'path': path,
            'filename': fn,
            'name': name,
            'character': char,
            'item_count': len(items),
        })
    return out


# ---------------- GUI ----------------
class BattleSimulatorGUI:
    def __init__(self, root: tk.Tk):
        self.root = root
        self.root.title('背包乱斗 战斗模拟器')
        self.root.geometry('1080x720')
        self.root.minsize(900, 600)
        try:
            self.root.iconbitmap()
        except Exception:
            pass

        self.item_db = load_items()
        self.char_db = load_characters()
        self.lineups = scan_lineups(_lineups_dir())
        self.running = False

        self._build_styles()
        self._build_widgets()
        self._refresh_lineup_lists()
        self._log('欢迎使用背包乱斗战斗模拟器。\n'
                  f'已从 {_lineups_dir()} 载入 {len(self.lineups)} 个阵容。\n'
                  '请选择「玩家」与「对手」两个阵容，然后点击「开始战斗」。\n')

    # ---------- 样式 ----------
    def _build_styles(self):
        self.style = ttk.Style()
        try:
            self.style.theme_use('clam')
        except Exception:
            pass
        self.style.configure('TLabel', font=('Microsoft YaHei', 10))
        self.style.configure('TButton', font=('Microsoft YaHei', 10))
        self.style.configure('Title.TLabel', font=('Microsoft YaHei', 16, 'bold'))
        self.style.configure('Head.TLabel', font=('Microsoft YaHei', 11, 'bold'))

    # ---------- 控件 ----------
    def _build_widgets(self):
        top = ttk.Frame(self.root, padding=10)
        top.pack(fill=tk.X)
        ttk.Label(top, text='⚔ 背包乱斗 战斗模拟器', style='Title.TLabel').pack(side=tk.LEFT)

        # 选择区
        sel = ttk.LabelFrame(self.root, text='选择阵容', padding=8)
        sel.pack(fill=tk.X, padx=10, pady=(0, 6))

        left = ttk.Frame(sel)
        left.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 8))
        right = ttk.Frame(sel)
        right.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.player_list = self._make_list(left, '玩家（左侧）')
        self.opp_list = self._make_list(right, '对手（右侧）')

        mid = ttk.Frame(sel)
        mid.pack(side=tk.LEFT, fill=tk.Y, padx=6)
        ttk.Button(mid, text='⇄\n交换', command=self._swap).pack(pady=20)
        ttk.Button(mid, text='↻\n刷新', command=self._refresh_lineup_lists).pack(pady=6)

        # 控制区
        ctrl = ttk.Frame(self.root, padding=(10, 4))
        ctrl.pack(fill=tk.X)
        ttk.Label(ctrl, text='种子:').pack(side=tk.LEFT)
        self.seed_var = tk.StringVar(value='')
        ttk.Entry(ctrl, textvariable=self.seed_var, width=12).pack(side=tk.LEFT, padx=4)
        ttk.Button(ctrl, text='随机', command=self._random_seed).pack(side=tk.LEFT)
        ttk.Label(ctrl, text='场数:').pack(side=tk.LEFT, padx=(12, 0))
        self.runs_var = tk.StringVar(value='1')
        ttk.Entry(ctrl, textvariable=self.runs_var, width=8).pack(side=tk.LEFT, padx=4)
        ttk.Button(ctrl, text='开始战斗', command=self._start_battle).pack(side=tk.LEFT, padx=(14, 0))
        ttk.Button(ctrl, text='保存日志', command=self._save_logs).pack(side=tk.LEFT, padx=4)

        # 日志语言（复刻原版：默认英文）
        ttk.Label(ctrl, text='语言:').pack(side=tk.LEFT, padx=(14, 0))
        self.lang_var = tk.StringVar(value='English')
        self.lang_choices = {'English': 'en', '中文': 'zh'}
        lang_cb = ttk.Combobox(ctrl, textvariable=self.lang_var, width=8,
                               values=list(self.lang_choices.keys()),
                               state='readonly')
        lang_cb.pack(side=tk.LEFT, padx=4)

        # 结果区
        res = ttk.LabelFrame(self.root, text='战斗结果', padding=8)
        res.pack(fill=tk.X, padx=10, pady=(0, 6))
        self.result_text = tk.StringVar(value='—')
        ttk.Label(res, textvariable=self.result_text, style='Head.TLabel',
                  anchor=tk.W, justify=tk.LEFT).pack(fill=tk.X)

        # 日志区
        logf = ttk.LabelFrame(self.root, text='战斗过程日志', padding=8)
        logf.pack(fill=tk.BOTH, expand=True, padx=10, pady=(0, 8))
        self.log_box = scrolledtext.ScrolledText(
            logf, wrap=tk.WORD, font=('Consolas', 10), state=tk.DISABLED)
        self.log_box.pack(fill=tk.BOTH, expand=True)

        self.battle_data = None  # 缓存最近一次战斗结果，用于保存

    def _make_list(self, parent, title) -> tk.Listbox:
        f = ttk.Frame(parent)
        f.pack(fill=tk.BOTH, expand=True)
        ttk.Label(f, text=title, style='Head.TLabel').pack(anchor=tk.W)
        lb = tk.Listbox(f, height=10, font=('Microsoft YaHei', 10),
                        exportselection=False, selectmode=tk.SINGLE)
        sb = ttk.Scrollbar(f, orient=tk.VERTICAL, command=lb.yview)
        lb.configure(yscrollcommand=sb.set)
        lb.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        sb.pack(side=tk.RIGHT, fill=tk.Y)
        lb.bind('<<ListboxSelect>>', lambda e, l=lb: self._on_select(l))
        return lb

    # ---------- 列表刷新 ----------
    def _refresh_lineup_lists(self):
        self.lineups = scan_lineups(_lineups_dir())
        for lb in (self.player_list, self.opp_list):
            lb.delete(0, tk.END)
            for lu in self.lineups:
                lb.insert(tk.END, f"{lu['name']}  [{lu['character']}]  ({lu['item_count']}件)")
        if self.lineups:
            self.player_list.selection_set(0)
            if len(self.lineups) > 1:
                self.opp_list.selection_set(1)
            else:
                self.opp_list.selection_set(0)
        self._log(f'已刷新：共 {len(self.lineups)} 个阵容。\n')

    def _selected_index(self, lb) -> Optional[int]:
        sel = lb.curselection()
        if not sel:
            return None
        return sel[0]

    def _on_select(self, changed_lb):
        # 防止两侧选到同一个文件
        pi = self._selected_index(self.player_list)
        oi = self._selected_index(self.opp_list)
        if pi is not None and oi is not None and pi == oi:
            other = self.opp_list if changed_lb is self.player_list else self.player_list
            # 把另一个挪到不同项
            n = len(self.lineups)
            if n > 1:
                other.selection_clear(0, tk.END)
                other.selection_set((oi + 1) % n)

    def _swap(self):
        pi = self._selected_index(self.player_list)
        oi = self._selected_index(self.opp_list)
        if pi is None or oi is None:
            return
        self.player_list.selection_clear(0, tk.END)
        self.opp_list.selection_clear(0, tk.END)
        self.player_list.selection_set(oi)
        self.opp_list.selection_set(pi)

    # ---------- 工具 ----------
    def _random_seed(self):
        self.seed_var.set(str(random.randint(1, 999999)))

    def _log(self, msg: str):
        self.log_box.configure(state=tk.NORMAL)
        self.log_box.insert(tk.END, msg)
        self.log_box.see(tk.END)
        self.log_box.configure(state=tk.DISABLED)

    def _selected_paths(self) -> Tuple[Optional[str], Optional[str], Optional[str], Optional[str]]:
        pi = self._selected_index(self.player_list)
        oi = self._selected_index(self.opp_list)
        if pi is None or oi is None or pi == oi:
            return None, None, None, None
        pa = self.lineups[pi]['path']
        pb = self.lineups[oi]['path']
        na = self.lineups[pi]['name']
        nb = self.lineups[oi]['name']
        return pa, pb, na, nb

    # ---------- 战斗 ----------
    def _start_battle(self):
        if self.running:
            return
        pa, pb, na, nb = self._selected_paths()
        if pa is None:
            messagebox.showwarning('提示', '请选择两个不同的阵容（玩家与对手）。')
            return

        # 解析 seed / runs
        seed_raw = self.seed_var.get().strip()
        seed = int(seed_raw) if seed_raw.isdigit() else None
        runs_raw = self.runs_var.get().strip()
        try:
            runs = max(1, int(runs_raw)) if runs_raw else 1
        except ValueError:
            runs = 1

        # 预校验
        try:
            load_lineup(pa); load_lineup(pb)
        except LineupError as e:
            messagebox.showerror('阵容错误', str(e))
            return

        self.running = True
        self.result_text.set('战斗进行中…')
        self.log_box.configure(state=tk.NORMAL)
        self.log_box.delete('1.0', tk.END)
        self.log_box.configure(state=tk.DISABLED)
        lang = self.lang_choices.get(self.lang_var.get(), 'en')
        self.current_lang = lang
        self._log(f'⚔ {na}（玩家）vs {nb}（对手）\n')
        self._log(f'种子={seed if seed is not None else "随机"}  场数={runs}  '
                  f'语言={self.lang_var.get()}\n')
        self._log('—' * 30 + '\n')

        t = threading.Thread(target=self._run_battle, args=(pa, pb, seed, runs, na, nb, lang),
                             daemon=True)
        t.start()

    def _run_battle(self, pa, pb, seed, runs, na, nb, lang):
        try:
            player = load_lineup(pa)
            opponent = load_lineup(pb)
            wins = 0
            last_eng = None
            start = time.time()
            for run in range(runs):
                s = seed + run if seed is not None else None
                eng = sim.simulate_once(pa, pb, self.item_db, self.char_db, s)
                last_eng = eng
                if eng.player_wins():
                    wins += 1
                if runs == 1:
                    self._append_log(eng.log.to_text(lang))
                    self.root.after(0, self._show_result, eng, None)
                else:
                    self.root.after(0, self._append_progress, run + 1, runs,
                                    '玩家胜' if eng.player_wins() else '玩家败')
            if runs > 1:
                rate = wins / runs * 100
                summary = (f'{runs} 场统计：玩家胜率 {rate:.1f}%  ({wins}/{runs})  '
                           f'耗时 {time.time()-start:.1f}s\n')
                self.root.after(0, self._show_monte_result, last_eng, summary, wins, runs)
        except Exception as e:
            self.root.after(0, self._show_error, repr(e))
        finally:
            self.running = False

    def _append_log(self, text: str):
        self.log_box.configure(state=tk.NORMAL)
        self.log_box.insert(tk.END, text + '\n')
        self.log_box.see(tk.END)
        self.log_box.configure(state=tk.DISABLED)

    def _append_progress(self, cur, total, outcome):
        self._append_log(f'  第 {cur}/{total} 场: {outcome}\n')

    def _show_result(self, eng, _unused):
        s = eng.summary()
        p, o = s['player'], s['opponent']
        won = eng.player_wins()
        def stat(d):
            st = d['stats']
            return (f"HP {d['hp']}/{d['max_hp']}  体力 {d['stamina']}  "
                    f"伤害 {st['damage_dealt']} 治疗 {st['healing_done']} "
                    f"暴击 {st['crits']} 未命中 {st['misses']}")
        head = (f"结果: {'🟢 玩家胜 ✅' if won else '🔴 玩家败 ❌'}   原因: {s['reason']}   耗时: {s['time']}s\n"
                f"🟦 玩家（{p['name']}）: {stat(p)}\n"
                f"🟥 对手（{o['name']}）: {stat(o)}\n"
                f"疲劳计数: {s['fatigue_counter']}")
        self.result_text.set(head)
        self.battle_data = {
            'eng': eng, 'player': pa_name(eng), 'opponent': opp_name(eng),
            'seed': eng.seed, 'runs': 1,
        }

    def _show_monte_result(self, eng, summary, wins, runs):
        s = eng.summary()
        p, o = s['player'], s['opponent']
        head = (f"蒙特卡洛 {runs} 场：玩家胜率 {wins/runs*100:.1f}% ({wins}/{runs})\n"
                f"（末场参考）🟦 玩家 {p['hp']}/{p['max_hp']}  "
                f"🟥 对手 {o['hp']}/{o['max_hp']}  原因 {s['reason']}")
        self.result_text.set(head)
        self._append_log('\n' + summary)
        self.battle_data = {'eng': eng, 'runs': runs, 'wins': wins,
                            'summary': summary, 'seed': eng.seed}

    def _show_error(self, msg):
        self.result_text.set('战斗出错')
        self._append_log('❌ 错误: ' + msg + '\n')
        messagebox.showerror('战斗错误', msg)

    # ---------- 保存 ----------
    def _save_logs(self):
        if not self.battle_data:
            messagebox.showinfo('提示', '请先进行一次战斗。')
            return
        eng = self.battle_data['eng']
        outdir = _app_dir()
        lang = getattr(self, 'current_lang', None) or self.lang_choices.get(
            self.lang_var.get(), 'en')
        try:
            paths = sim.save_outputs(eng, _safe_path(eng, 'player'),
                                     _safe_path(eng, 'opponent'), outdir, eng.seed, lang)
            messagebox.showinfo('已保存',
                                '战斗日志已保存到：\n' + '\n'.join(paths))
            self._log('💾 已保存日志到: ' + outdir + '\n')
        except Exception as e:
            messagebox.showerror('保存失败', repr(e))


def pa_name(eng):
    return eng.player.display_name()


def opp_name(eng):
    return eng.opponent.display_name()


def _safe_path(eng, side):
    """保存时使用内存中的阵容显示名构造伪路径（仅用于文件名）"""
    if side == 'player':
        return f"lineup_{eng.player.display_name()}.json"
    return f"lineup_{eng.opponent.display_name()}.json"


def main():
    root = tk.Tk()
    try:
        BattleSimulatorGUI(root)
        root.mainloop()
    except Exception as e:
        messagebox.showerror('启动失败', repr(e))
        raise


if __name__ == '__main__':
    main()

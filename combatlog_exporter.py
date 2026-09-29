# -*- coding: utf-8 -*-
"""combatlog_exporter.py — 战斗日志自动导出 GUI

游戏《背包乱斗》不把战斗日志落盘，只存在内存里（CombatLog.events）。
本工具在游戏运行期间轮询该数组，战斗结束（最后一条事件为 Win/Loss）
后自动把整场日志导出为游戏同格式文本（中文/英文）+ 原始事件 JSON。

用法：游戏开启后运行
    python combatlog_exporter.py
输出目录：output/combat_logs/
"""
from __future__ import annotations

import json
import os
import sys
import threading
import tkinter as tk
from datetime import datetime
from pathlib import Path
from tkinter import ttk

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from core.combatlog_reader import CombatLogReader  # noqa: E402
from core.combatlog_text import render_log  # noqa: E402
from core.paths import get_base_dir, get_config_path  # noqa: E402

POLL_MS = 800
WIN_LOSS = (111, 112)
# 冻结成 exe 时指向 exe 所在目录（onefile 的 __file__ 在临时解压目录里）
OUT_DIR = get_base_dir() / "output" / "combat_logs"


def load_godot_offsets() -> dict:
    """从 config.yaml 读 godot 段（RVA 等标定值），缺失则自动发现。"""
    try:
        import yaml
        cfg = yaml.safe_load(get_config_path().read_text(encoding="utf-8")) or {}
        off = cfg.get("godot") or {}
        return {k: v for k, v in off.items() if isinstance(v, int)}
    except Exception:  # noqa: BLE001
        return {}


class Exporter:
    """导出逻辑（与 GUI 解耦，便于命令行复用）。"""

    def __init__(self):
        self.reader = CombatLogReader()
        self.exported: set = set()       # (len, last_type, last_ts)
        self.exported_base: set = set()  # (poll计数, last_type) 快速判重
        self.skipped: set = set()
        self.skipped_base: set = set()
        self.pending: Optional[dict] = None   # 已捕获待用户选择的战斗
        self._prev_fp: tuple = ()
        self.auto_export = False              # True=不询问直接写盘

    def _fingerprint(self, events: list) -> tuple:
        if not events:
            return ()
        last = events[-1]
        return (len(events), last.get("type"), round(last.get("t", 0.0), 2))

    def _write(self, events: list, round_num) -> Path:
        OUT_DIR.mkdir(parents=True, exist_ok=True)
        last = events[-1]
        result = {111: "Win", 112: "Loss"}.get(last.get("type"), "Partial")
        ts = datetime.now().strftime("%Y%m%d_%H%M%S")
        rnd = f"R{round_num}" if round_num is not None else "R?"
        base = OUT_DIR / f"CombatLog_{ts}_{rnd}_{result}"
        meta = {
            "exported_at": datetime.now().isoformat(timespec="seconds"),
            "game_pid": self.reader.pid,
            "round": round_num,
            "event_count": len(events),
            "result": result,
            "format": "Backpack Battles CombatLog (memory dump, "
                      "rendered per CombatEvent.asText)",
        }
        path = base.parent / (base.name + ".json")
        path.write_text(json.dumps({"meta": meta, "events": events},
                                   ensure_ascii=False, indent=1),
                        encoding="utf-8")
        for lang, suffix in (("zh", ".zh.txt"), ("en", ".en.txt")):
            text = render_log(events, lang)
            header = (f"# Backpack Battles 战斗日志 (第{round_num}回合 · "
                      f"{result} · {len(events)}事件)\n"
                      if lang == "zh" else
                      f"# Backpack Battles combat log (round {round_num} · "
                      f"{result} · {len(events)} events)\n")
            (base.parent / (base.name + suffix)).write_text(
                header + text + "\n", encoding="utf-8")
        self.exported.add(self._fingerprint(events))
        return base

    def export_now(self) -> tuple:
        """手动导出当前日志（战斗未结束也可导出部分）。返回 (路径, 错误)。"""
        try:
            events = self.reader.read_events()
        except ValueError as e:
            return None, f"读取失败（战斗进行中属正常，稍后重试）: {e}"
        except Exception as e:  # noqa: BLE001
            return None, f"读取异常: {e}"
        if not events:
            return None, "当前没有可导出的事件（不在对局或已清空）"
        try:
            path = self._write(events, self.reader.read_round())
            return path, None
        except Exception as e:  # noqa: BLE001
            return None, f"写入失败: {e}"

    def poll_and_autoexport(self) -> dict:
        """轮询一次；战斗结束后捕获完整事件，按 auto_export 决定直接写盘
        还是置入 pending 等待用户选择。

        返回状态 dict: {status, connected, round, count, finished,
                       last_type, last_id, exported_path, note, error}
        状态: waiting_game / error / no_fight / in_fight /
              pending_choice(待选择) / skipped / exported / exported_done
        """
        st = self.reader.poll()
        out = {
            "connected": bool(st.get("connected")),
            "round": st.get("round"),
            "count": st.get("event_count") or 0,
            "finished": st.get("finished"),
            "last_type": st.get("last_type"),
            "last_id": None,
            "exported_path": None, "note": None, "error": st.get("error"),
        }
        if not out["connected"]:
            out["status"] = "waiting_game"
            return out
        if out["error"]:
            out["status"] = "error"
            return out
        if out["count"] == 0:
            out["status"] = "no_fight"
            return out
        last_type = out["last_type"]
        finished = bool(out["finished"])
        fp_now = (out["count"], st.get("last_ts"))
        stable = fp_now == self._prev_fp
        self._prev_fp = fp_now
        # 触发条件：合并流的终局事件(Win/Loss)；或 loggingFinished 且
        # 事件数连续两轮稳定（覆盖终局事件被丢弃的边界情形）
        ended = (last_type in WIN_LOSS) or \
                (finished and stable and fp_now[0] > 0)
        if not ended:
            out["status"] = "in_fight" if not finished else "ended_no_result"
            return out

        fp_base = (out["count"], last_type)
        if self.pending and self.pending.get("fp_base") == fp_base:
            out["status"] = "pending_choice"
            return out
        if fp_base in self.exported_base:
            out["status"] = "exported_done"
            return out
        if fp_base in self.skipped_base:
            out["status"] = "skipped"
            return out

        # 捕获完整事件（半态则下一轮重试）
        try:
            events = self.reader.read_events()
        except ValueError as e:
            out["status"] = "reading"
            out["note"] = f"重读中: {e}"
            return out
        except Exception as e:  # noqa: BLE001
            out["status"] = "error"
            out["error"] = str(e)
            return out
        if not events:
            out["status"] = "no_fight"
            return out
        fp = self._fingerprint(events)
        if fp in self.exported or fp_base in \
                {(f[0], f[1]) for f in self.exported}:
            out["status"] = "exported_done"
            return out
        if self.auto_export:
            try:
                path = self._write(events, out["round"])
                out["exported_path"] = path
                out["status"] = "exported"
            except Exception as e:  # noqa: BLE001
                out["status"] = "error"
                out["error"] = f"写入失败: {e}"
            self.exported.add(fp)
            self.exported_base.add(fp_base)
            return out
        # 置入待选择（新一轮战斗结束会覆盖未作答的旧待选）
        out["last_id"] = events[-1].get("id")
        self.pending = {"fp": fp, "fp_base": fp_base,
                        "events": events, "round": out["round"]}
        out["count"] = len(events)
        out["status"] = "pending_choice"
        return out

    def export_pending(self) -> tuple:
        """把待选择的战斗写盘。返回 (路径, 错误)。"""
        if not self.pending:
            return None, "没有待导出的战斗"
        p = self.pending
        try:
            path = self._write(p["events"], p["round"])
        except Exception as e:  # noqa: BLE001
            return None, f"写入失败: {e}"
        self.exported.add(p["fp"])
        self.exported_base.add(p["fp_base"])
        self.pending = None
        return path, None

    def skip_pending(self):
        if self.pending:
            self.skipped.add(self.pending["fp"])
            self.skipped_base.add(self.pending["fp_base"])
            self.pending = None


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("背包乱斗 · 战斗日志自动导出")
        self.geometry("860x560")
        self.minsize(700, 460)
        self.exporter: Exporter | None = None
        self._preview_fp = None
        self._build()
        self._start()

    # ---------------- UI ----------------
    BG, FG, MUT, ACC, OK = "#1e1f22", "#d8d9da", "#9a9ca3", "#4a9eff", "#3fbf6f"

    def _build(self):
        self.configure(bg=self.BG)
        top = tk.Frame(self, bg=self.BG)
        top.pack(fill="x", padx=12, pady=(10, 4))

        self.lbl_status = tk.Label(
            top, text="正在连接游戏…", font=("Microsoft YaHei", 11, "bold"),
            bg=self.BG, fg=self.ACC, anchor="w")
        self.lbl_status.pack(side="left")

        self.auto_var = tk.BooleanVar(value=False)
        tk.Checkbutton(top, text="自动导出，不询问", variable=self.auto_var,
                       bg=self.BG, fg=self.FG, selectcolor="#2a2b30",
                       activebackground=self.BG, activeforeground=self.FG,
                       highlightthickness=0).pack(side="right")

        # 战斗结束后的「是否导出」选择条（默认隐藏）
        self.prompt = tk.Frame(self, bg="#4a3b1e")
        self.lbl_prompt = tk.Label(self.prompt, text="", bg="#4a3b1e",
                                   fg="#ffd479", font=("Microsoft YaHei", 10))
        self.lbl_prompt.pack(side="left", padx=(12, 8), pady=6)
        for text, cmd, color in (("导出本场", self.on_export_pending, "#2f6f3f"),
                                 ("跳过本场", self.on_skip_pending, "#5a2e2e")):
            tk.Button(self.prompt, text=text, command=cmd, bg=color,
                      fg="#ffffff", activebackground=color, relief="flat",
                      padx=14, pady=2,
                      font=("Microsoft YaHei", 9)).pack(side="right", padx=4,
                                                        pady=6)

        btns = tk.Frame(self, bg=self.BG)
        btns.pack(fill="x", padx=12, pady=4)
        self._btns = btns
        for text, cmd in (("立即导出最近战斗", self.on_manual),
                          ("打开导出目录", self.on_open_dir)):
            tk.Button(btns, text=text, command=cmd, bg="#2a2b30", fg=self.FG,
                      activebackground="#3a3b40", activeforeground="#ffffff",
                      relief="flat", padx=12, pady=3,
                      font=("Microsoft YaHei", 9)).pack(side="left", padx=(0, 8))

        self.lbl_out = tk.Label(
            btns, text=f"输出: {OUT_DIR}", bg=self.BG, fg=self.MUT,
            font=("Microsoft YaHei", 8))
        self.lbl_out.pack(side="left", padx=(8, 0))

        mid = tk.Frame(self, bg=self.BG)
        mid.pack(fill="both", expand=True, padx=12, pady=(4, 10))
        left = tk.Frame(mid, bg=self.BG)
        left.pack(side="left", fill="both", expand=True)
        self.lbl_preview = tk.Label(left, text="战斗日志预览（实时读取当前战斗 · 中文）",
                                    bg=self.BG, fg=self.MUT,
                                    font=("Microsoft YaHei", 9))
        self.lbl_preview.pack(anchor="w")
        pf = tk.Frame(left, bg=self.BG)
        pf.pack(fill="both", expand=True, pady=(2, 0))
        self.txt = tk.Text(pf, bg="#141518", fg=self.FG, relief="flat",
                           font=("Consolas", 10), state="disabled",
                           wrap="none", padx=8, pady=6)
        sb = tk.Scrollbar(pf, command=self.txt.yview, bg="#2a2b30",
                          troughcolor="#141518", activebackground="#3a3b40",
                          width=14)
        sb.pack(side="right", fill="y")
        self.txt.configure(yscrollcommand=sb.set)
        self.txt.pack(side="left", fill="both", expand=True)
        right = tk.Frame(mid, bg=self.BG, width=250)
        right.pack(side="right", fill="y", padx=(10, 0))
        right.pack_propagate(False)
        tk.Label(right, text="导出记录", bg=self.BG, fg=self.MUT,
                 font=("Microsoft YaHei", 9)).pack(anchor="w")
        self.listbox = tk.Listbox(right, bg="#141518", fg=self.FG,
                                  relief="flat", font=("Consolas", 9),
                                  activestyle="none")
        self.listbox.pack(fill="both", expand=True, pady=(2, 0))

        self.lbl_note = tk.Label(self, text="", bg=self.BG, fg=self.MUT,
                                 font=("Microsoft YaHei", 8), anchor="w")
        self.lbl_note.pack(fill="x", padx=12, pady=(0, 6))

    # ---------------- 轮询 ----------------
    def _start(self):
        def boot():
            # 先把 config.yaml 的 RVA 标定并入默认表，再实例化读取器
            from core.godot_reader import GODOT_OFFSETS
            for k, v in load_godot_offsets().items():
                GODOT_OFFSETS.setdefault(k, v)
            self.exporter = Exporter()
            self.after(0, self._tick)
        threading.Thread(target=boot, daemon=True).start()

    def _tick(self):
        if self.exporter is None:
            return
        exp = self.exporter
        exp.auto_export = bool(self.auto_var.get())
        if not exp.reader.ensure_connected():
            self._hide_prompt()
            self._set_status("未找到游戏（请先启动 Backpack Battles）", self.MUT)
        else:
            try:
                st = exp.poll_and_autoexport()
            except Exception as e:  # noqa: BLE001
                st = {"status": "error", "error": str(e)}
            self._apply_state(st)
        self.after(POLL_MS, self._tick)

    def _apply_state(self, st: dict):
        s = st.get("status")
        rnd = st.get("round")
        rtxt = f"第{rnd}回合" if rnd is not None else ""
        if s == "waiting_game":
            self._hide_prompt()
            self._set_status("未找到游戏（请先启动 Backpack Battles）", self.MUT)
        elif s == "no_fight":
            self._set_status(f"已连接 (PID {self.exporter.reader.pid}) · "
                             f"{rtxt} · 等待战斗…", self.MUT)
        elif s == "in_fight":
            self._set_status(f"战斗进行中 {rtxt} · 已记录 {st['count']} 条事件",
                             self.OK)
        elif s == "ended_no_result":
            self._set_status(f"战斗结束 {rtxt} · {st['count']} 条（等待胜负判定）",
                             self.ACC)
        elif s == "pending_choice":
            self._show_prompt(rnd, st["count"])
            self._set_status(f"战斗结束 {rtxt} · 共 {st['count']} 条事件 · "
                             f"等待你的选择", self.ACC)
            # 本场战斗完成后刷新一次预览（同一战斗不重复渲染）
            exp = self.exporter
            if exp.pending is not None:
                fp = exp.pending.get("fp")
                if fp != self._preview_fp:
                    self._preview_fp = fp
                    self._load_events_preview(exp.pending["events"])
        elif s == "skipped":
            self._hide_prompt()
            self._set_status(f"已跳过 {rtxt} 的战斗日志", self.MUT)
        elif s == "exported":
            path = st.get("exported_path")
            self._hide_prompt()
            self._set_status(f"✔ 已导出 {rtxt} · {st['count']} 条事件", self.OK)
            self._add_record(str(path))
            self._load_preview(path)
            self._set_note("")
        elif s == "exported_done":
            self._hide_prompt()
            self._set_status(f"战斗日志已导出 {rtxt} · {st['count']} 条", self.MUT)
        elif s == "reading":
            self._set_note("日志读取中（游戏正在写入，稍后自动重试）")
        elif s == "error":
            self._set_status("读取异常", "#e06c75")
            self._set_note(st.get("error") or st.get("note") or "")

    def _show_prompt(self, rnd, count):
        rtxt = f"第{rnd}回合" if rnd is not None else "本场"
        self.lbl_prompt.config(
            text=f"  ⚔ {rtxt}战斗结束 · 共 {count} 条事件 · 导出这份战斗日志吗？")
        self.prompt.pack(fill="x", before=self._btns)

    def _hide_prompt(self):
        self.prompt.pack_forget()

    def _set_status(self, text, color):
        self.lbl_status.config(text=text, fg=color)

    def _set_note(self, text):
        self.lbl_note.config(text=text)

    def _add_record(self, path_str: str):
        p = Path(path_str)
        self.listbox.insert(0, p.name)
        self.listbox.itemconfig(0, fg=self.OK)

    def _load_events_preview(self, events):
        """战斗完成时刷新一次：渲染本场捕获的事件（不自动滚底）。"""
        try:
            txt = render_log(events, "zh")
        except Exception:  # noqa: BLE001
            return
        self.lbl_preview.config(
            text=f"战斗日志预览（本场战斗 · {len(events)} 事件 · 中文）")
        self.txt.config(state="normal")
        self.txt.delete("1.0", "end")
        self.txt.insert("1.0", txt)
        self.txt.yview_moveto(0)
        self.txt.config(state="disabled")

    def _load_preview(self, base_path: Path):
        p = Path(base_path)
        zh = p if str(p).endswith(".zh.txt") else Path(str(p) + ".zh.txt")
        if not zh.exists():
            return
        try:
            content = zh.read_text(encoding="utf-8")
        except Exception:  # noqa: BLE001
            return
        self.lbl_preview.config(text="战斗日志预览（已导出文件 · 中文）")
        self.txt.config(state="normal")
        self.txt.delete("1.0", "end")
        self.txt.insert("1.0", content)
        self.txt.yview_moveto(0)
        self.txt.config(state="disabled")

    # ---------------- 按钮 ----------------
    def on_export_pending(self):
        if self.exporter is None:
            return
        path, err = self.exporter.export_pending()
        if err:
            self._set_note(err)
            return
        self._set_note("")
        self._set_status(f"✔ 已导出 · {Path(path).name}", self.OK)
        self._add_record(str(path))
        self._load_preview(Path(path))
        self._hide_prompt()

    def on_skip_pending(self):
        if self.exporter is None:
            return
        self.exporter.skip_pending()
        self._hide_prompt()
        self._set_status("已跳过本场战斗日志（不写盘）", self.MUT)

    def on_manual(self):
        if self.exporter is None:
            return
        def work():
            path, err = self.exporter.export_now()
            self.after(0, lambda: self._manual_done(path, err))
        threading.Thread(target=work, daemon=True).start()

    def _manual_done(self, path, err):
        if err:
            self._set_note(err)
            return
        self._set_note("")
        self._set_status(f"✔ 已手动导出 · {path.stem}", self.OK)
        self._add_record(str(path))
        self._load_preview(path)

    def on_open_dir(self):
        OUT_DIR.mkdir(parents=True, exist_ok=True)
        os.startfile(OUT_DIR)  # noqa: S606


def main():
    app = App()
    app.mainloop()


if __name__ == "__main__":
    main()

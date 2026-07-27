"""
桥接注入器 —— 背包乱斗 AI 游戏桥接管理工具

独立的桌面程序，用于：
1. 自动搜索游戏安装目录并显示 PCK 路径
2. 一键注入桥接 GDScript（修改 Main.tscn + 添加 bridge.gd）
3. 从备份还原原版 PCK

用法： python -m bridge.injector_app
打包： build_bridge_injector.py → dist/BackpackAI-BridgeInjector.exe
"""
from __future__ import annotations

import logging
import os
import sys
import threading
import tkinter as tk
from tkinter import ttk, scrolledtext
from pathlib import Path
from typing import Optional

# ─── 确保能找到项目根目录 ───
_THIS_DIR = Path(__file__).resolve().parent
_PROJECT_DIR = _THIS_DIR.parent
if str(_PROJECT_DIR) not in sys.path:
    sys.path.insert(0, str(_PROJECT_DIR))

# ─── 颜色方案 ───
COLORS = {
    "bg": "#1e1e2e",
    "panel": "#2a2a3e",
    "panel_light": "#36364a",
    "text": "#e0e0e0",
    "text_dim": "#8888aa",
    "accent": "#7c9bff",
    "success": "#50c878",
    "warning": "#f5c542",
    "danger": "#ff6b6b",
    "border": "#444466",
}

FONTS = {
    "title": ("Segoe UI", 16, "bold"),
    "subtitle": ("Segoe UI", 12, "bold"),
    "body": ("Consolas", 10),
    "small": ("Segoe UI", 9),
    "button": ("Segoe UI", 11),
}

SPRITE_DIR = "assets/sprites"


# ─── 注入器逻辑（桥接到 bridge.inject） ───
class InjectorLogic:
    """封装注入/还原/状态检查逻辑。"""

    @staticmethod
    def find_pck() -> Optional[Path]:
        try:
            from bridge import inject as inj
            return inj.find_game_pck()
        except Exception:
            return None

    @staticmethod
    def check_status(pck_path: Path) -> dict:
        result = {
            "exists": pck_path.exists(),
            "size": pck_path.stat().st_size if pck_path.exists() else 0,
            "injected": False,
            "backup": False,
            "bridge_path": None,
        }
        if not result["exists"]:
            return result
        try:
            from bridge import inject as inj
            _, entries, _, _, _ = inj.parse_pck(pck_path)
            result["injected"] = inj.BRIDGE_RES_PATH in entries
            backup = pck_path.with_suffix(pck_path.suffix + inj.BACKUP_SUFFIX)
            result["backup"] = backup.exists()
            result["bridge_path"] = str(_PROJECT_DIR / "bridge" / "bridge.gd")
        except Exception:
            pass
        return result

    @staticmethod
    def do_inject(pck_path: Path) -> str:
        try:
            from bridge import inject as inj
            # 配置 logging 到回调
            log_catcher = []
            class Handler(logging.Handler):
                def emit(self, record):
                    log_catcher.append(self.format(record))
            h = Handler()
            h.setFormatter(logging.Formatter("%(message)s"))
            inj.logger.addHandler(h)
            inj.logger.setLevel(logging.INFO)

            ok = inj.inject(str(pck_path))
            inj.logger.removeHandler(h)
            if ok:
                return "\n".join(log_catcher)
            return "注入失败（无报错信息）"
        except Exception as e:
            import traceback
            return f"注入出错: {e}\n{traceback.format_exc()}"

    @staticmethod
    def do_restore(pck_path: Path) -> str:
        try:
            from bridge import inject as inj
            ok = inj.restore(str(pck_path))
            return "✅ 已还原原版 PCK" if ok else "还原失败"
        except Exception as e:
            return f"还原出错: {e}"

    @staticmethod
    def bridge_gd_exists() -> bool:
        return (_PROJECT_DIR / "bridge" / "bridge.gd").exists()


# ─── GUI 主窗口 ───
class BridgeInjectorApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("背包乱斗 AI — 桥接注入器")
        self.configure(bg=COLORS["bg"])
        self.geometry("700x520")
        self.minsize(620, 440)
        self.resizable(True, True)

        self.pck_path: Optional[Path] = None
        self._busy = False

        self._build_ui()
        self.after(200, self._auto_detect)

    # ─── UI 构建 ───
    def _build_ui(self):
        # 标题
        header = tk.Frame(self, bg=COLORS["panel"], height=54)
        header.pack(fill="x")
        header.pack_propagate(False)
        tk.Label(header, text="背包乱斗 AI — 桥接注入器", font=FONTS["title"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left", padx=18, pady=10)

        body = tk.Frame(self, bg=COLORS["bg"])
        body.pack(fill="both", expand=True, padx=14, pady=10)

        # ── 游戏路径 ──
        path_frame = tk.LabelFrame(body, text=" 游戏 PCK 路径 ", font=FONTS["subtitle"],
                                   bg=COLORS["panel"], fg=COLORS["text"],
                                   relief="flat", padx=10, pady=8)
        path_frame.pack(fill="x", pady=(0, 8))

        self.path_var = tk.StringVar(value="正在搜索...")
        self.path_label = tk.Label(path_frame, textvariable=self.path_var,
                                   font=FONTS["body"], bg=COLORS["panel"],
                                   fg=COLORS["text_dim"], wraplength=600, anchor="w")
        self.path_label.pack(fill="x")

        btn_row = tk.Frame(path_frame, bg=COLORS["panel"])
        btn_row.pack(fill="x", pady=(6, 0))

        self.browse_btn = tk.Button(btn_row, text="浏览...", font=FONTS["button"],
                                    bg=COLORS["panel_light"], fg=COLORS["text"],
                                    relief="flat", cursor="hand2",
                                    command=self._on_browse)
        self.browse_btn.pack(side="left", padx=(0, 6))

        self.detect_btn = tk.Button(btn_row, text="重新检测", font=FONTS["button"],
                                    bg=COLORS["panel_light"], fg=COLORS["text"],
                                    relief="flat", cursor="hand2",
                                    command=self._auto_detect)
        self.detect_btn.pack(side="left")

        # ── 状态信息 ──
        info_frame = tk.LabelFrame(body, text=" 注入状态 ", font=FONTS["subtitle"],
                                   bg=COLORS["panel"], fg=COLORS["text"],
                                   relief="flat", padx=10, pady=8)
        info_frame.pack(fill="x", pady=(0, 8))

        self.status_lines = []
        for label, key in [("游戏版本:", "version"), ("桥接注入:", "injected"),
                           ("备份文件:", "backup"), ("桥接脚本:", "bridge_script")]:
            row = tk.Frame(info_frame, bg=COLORS["panel"])
            row.pack(fill="x", pady=1)
            tk.Label(row, text=label, font=FONTS["small"],
                     bg=COLORS["panel"], fg=COLORS["text_dim"], width=12, anchor="e").pack(side="left", padx=(0, 8))
            var = tk.StringVar(value="—")
            setattr(self, f"_info_{key}", var)
            tk.Label(row, textvariable=var, font=FONTS["small"],
                     bg=COLORS["panel"], fg=COLORS["text"], anchor="w").pack(side="left", fill="x")

        # ── 操作按钮 ──
        action_frame = tk.Frame(body, bg=COLORS["bg"])
        action_frame.pack(fill="x", pady=(0, 8))

        self.inject_btn = tk.Button(action_frame, text="🚀 注入桥接", font=FONTS["button"],
                                    bg=COLORS["accent"], fg="#ffffff", relief="flat",
                                    cursor="hand2", padx=20, pady=8,
                                    command=self._on_inject)
        self.inject_btn.pack(side="left", padx=(0, 8))

        self.restore_btn = tk.Button(action_frame, text="↩ 还原原版", font=FONTS["button"],
                                     bg=COLORS["warning"], fg="#222222", relief="flat",
                                     cursor="hand2", padx=20, pady=8,
                                     command=self._on_restore)
        self.restore_btn.pack(side="left", padx=(0, 8))

        self.open_btn = tk.Button(action_frame, text="📂 打开目录", font=FONTS["button"],
                                  bg=COLORS["panel_light"], fg=COLORS["text"], relief="flat",
                                  cursor="hand2", padx=12, pady=8,
                                  command=self._on_open_dir)
        self.open_btn.pack(side="right")

        # ── 日志 ──
        log_frame = tk.LabelFrame(body, text=" 操作日志 ", font=FONTS["subtitle"],
                                  bg=COLORS["panel"], fg=COLORS["text"],
                                  relief="flat", padx=10, pady=8)
        log_frame.pack(fill="both", expand=True)

        self.log_text = scrolledtext.ScrolledText(
            log_frame, font=FONTS["body"], bg=COLORS["bg"],
            fg=COLORS["text"], relief="flat", wrap="word",
            padx=8, pady=6, height=8)
        self.log_text.pack(fill="both", expand=True)
        self.log_text.insert("1.0", "就绪。正在搜索游戏路径...\n")
        self.log_text.configure(state="disabled")

        # 初始按钮状态
        self._set_buttons(enabled=False)

    def _set_buttons(self, enabled: bool = True):
        state = "normal" if enabled else "disabled"
        self.inject_btn.configure(state=state)
        self.restore_btn.configure(state=state)

    def _log(self, msg: str):
        self.log_text.configure(state="normal")
        self.log_text.insert("end", msg + "\n")
        self.log_text.see("end")
        self.log_text.configure(state="disabled")
        self.update_idletasks()

    # ─── 事件处理 ───
    def _auto_detect(self):
        self.path_var.set("正在搜索游戏安装目录...")
        self._log("搜索 Steam 库与注册表中...")
        threading.Thread(target=self._do_detect, daemon=True).start()

    def _do_detect(self):
        try:
            from bridge import inject as inj
            pck = inj.find_game_pck()
            if pck:
                self.pck_path = pck
                self.after(0, self._on_pck_found)
            else:
                self.after(0, self._on_pck_not_found)
        except Exception as e:
            self.after(0, lambda: self._log(f"检测出错: {e}"))

    def _on_pck_found(self):
        self.path_var.set(str(self.pck_path))
        self._log(f"✅ 找到游戏 PCK: {self.pck_path}")
        self._refresh_status()
        self._set_buttons(enabled=True)

    def _on_pck_not_found(self):
        self.path_var.set("❌ 未找到游戏。可手动点击「浏览...」选择游戏目录。")
        self._log("未在 Steam 库或常见位置找到 BackpackBattles.pck")
        self._set_buttons(enabled=False)

    def _on_browse(self):
        from tkinter import filedialog
        path = filedialog.askopenfilename(
            title="选择 BackpackBattles.pck",
            filetypes=[("PCK 文件", "*.pck"), ("所有文件", "*.*")])
        if path:
            self.pck_path = Path(path)
            self.path_var.set(path)
            self._log(f"手动选择: {path}")
            self._refresh_status()
            self._set_buttons(enabled=True)

    def _refresh_status(self):
        if not self.pck_path or not self.pck_path.exists():
            return
        try:
            from bridge import inject as inj
            _, entries, _, _, _ = inj.parse_pck(self.pck_path)
            injected = inj.BRIDGE_RES_PATH in entries
            backup = self.pck_path.with_suffix(self.pck_path.suffix + inj.BACKUP_SUFFIX).exists()
            bridge_ok = InjectorLogic.bridge_gd_exists()

            self._info_injected.set("✅ 已注入" if injected else "❌ 未注入")
            self._info_backup.set("✅ 存在" if backup else "❌ 无")
            self._info_bridge_script.set("✅ 就绪" if bridge_ok else "❌ 缺失（需 bridge/bridge.gd）")
            self._info_version.set(f"{len(entries)} 文件")
        except Exception as e:
            self._log(f"状态刷新失败: {e}")

    def _on_inject(self):
        if not self.pck_path:
            return
        if self._busy:
            return
        self._busy = True
        self._set_buttons(enabled=False)
        self.inject_btn.configure(text="注入中...")
        self._log("=" * 40)
        self._log("开始注入桥接脚本...")

        def _inject_thread():
            try:
                msg = InjectorLogic.do_inject(self.pck_path)
                self.after(0, lambda: self._inject_done(msg))
            except Exception as e:
                import traceback
                self.after(0, lambda: self._inject_done(f"失败: {e}\n{traceback.format_exc()}"))

        threading.Thread(target=_inject_thread, daemon=True).start()

    def _inject_done(self, msg: str):
        self._log(msg)
        self._log("✅ 注入完成！请重启游戏使桥接生效。")
        self.inject_btn.configure(text="🚀 注入桥接")
        self._busy = False
        self._refresh_status()
        self._set_buttons(enabled=True)

    def _on_restore(self):
        if not self.pck_path or self._busy:
            return
        from tkinter import messagebox
        if not messagebox.askyesno("确认还原", "此操作将从备份恢复原版 PCK。\n确定继续？",
                                   parent=self):
            return
        self._busy = True
        self._set_buttons(enabled=False)
        self._log("还原原版 PCK...")
        msg = InjectorLogic.do_restore(self.pck_path)
        self._log(msg)
        self._busy = False
        self._refresh_status()
        self._set_buttons(enabled=True)

    def _on_open_dir(self):
        if self.pck_path:
            os.startfile(str(self.pck_path.parent))


# ─── 入口 ───
def run():
    app = BridgeInjectorApp()
    app.mainloop()


if __name__ == "__main__":
    run()

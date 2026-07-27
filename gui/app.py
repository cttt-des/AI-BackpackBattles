"""
背包乱斗 AI — 原生 GUI 控制台应用
基于 tkinter，无需浏览器，点击即用

布局（2026-07-26 二次重构，落实用户 8 项需求）
--------------------------------------------------
* 左侧窄栏：游戏状态 + 控制按钮（2×3 网格，避免被裁切）+ 渲染模式切换。
  手动标定金币/HP/回合的面板已移除（结构性读取自动完成）。
* 右侧主区：
  - 背包摆盘（放大 · 仿游戏渲染：格子素材 Slot/FilledSlot + 物品贴图/染色）
  - 储物箱 / 商店在售：纯文字分区；商店物品显示价格。
  - 运行日志。

背包渲染（仿游戏：进程读状态 → GUI 复现）
  图层顺序（底→顶）：背包底框 → 背包(容器)贴图 → 格子素材(每个格子一张 FilledSlot) → 普通物品
    （格子叠在背包之上，便于分辨同一背包占用的不同格子）
  模式 A（贴图）：每个物品用游戏内贴图渲染，中文名标注；背包允许略超出格子(不变形)，普通物品严格不超出。
  模式 B（染色）：每个物品占用的每一格用同色半透明填充(stipple) + 居中文字（自动换行/字号），
                  相邻物品自动分配不同颜色；背包用贴图渲染。

  ┌─────────────── 标题栏 + 状态灯 ───────────────┐
  ├───────────┬──────────────────────────────────┤
  │  游戏状态 │  背包摆盘（放大 · 仿游戏渲染）      │
  │  控制按钮 ├──────────────┬───────────────────┤
  │  渲染模式 │  储物箱(文字) │  商店在售(文字+价格) │
  │           ├──────────────┴───────────────────┤
  │           │  运行日志                          │
  └───────────┴──────────────────────────────────┘
"""

import os
import sys
import math
import time
import queue
import logging
import threading
from collections import defaultdict
from pathlib import Path
from itertools import product

import tkinter as tk
from tkinter import ttk, messagebox, font as tkfont

# 允许以脚本或模块方式运行
if not getattr(sys, "frozen", False):
    sys.path.insert(0, str(Path(__file__).parent.parent))

from gui.theme import COLORS, CATEGORY_COLORS, FONTS, FONT_FAMILY
from core.bot import BackpackBot
from core.paths import get_config_path
from core.item_db import ItemDB

logger = logging.getLogger(__name__)

# 贴图渲染依赖 PIL；若运行环境缺失则退化为纯色块 + 文字。
try:
    from PIL import Image, ImageTk
    _HAS_PIL = True
except Exception:  # noqa: BLE001
    _HAS_PIL = False


class QueueLogHandler(logging.Handler):
    """把日志记录推入队列，供 GUI 主线程消费"""

    def __init__(self, log_queue):
        super().__init__()
        self.log_queue = log_queue

    def emit(self, record):
        try:
            msg = self.format(record)
            self.log_queue.put(("log", record.levelname.lower(), msg))
        except Exception:
            pass


# 渲染模式 B（染色）用的调色板（相邻物品不会同色，靠邻接图着色保证）
_PALETTE = [
    (242, 114, 84), (95, 201, 104), (97, 175, 239), (188, 140, 255),
    (235, 159, 57), (236, 99, 156), (110, 200, 190), (200, 170, 90),
    (150, 200, 120), (230, 120, 120), (120, 150, 230), (180, 180, 200),
    (160, 120, 200), (100, 190, 160), (210, 160, 90), (140, 210, 140),
]
# 背包空格底色（COLORS["grid_empty"] = #2a2f3a）
_BG_RGB = (0x2A, 0x2F, 0x3A)


class BackpackAIApp(tk.Tk):
    """背包乱斗 AI 主窗口"""

    GRID_ROWS = 7
    GRID_COLS = 9
    CELL = 52          # 每格像素（放大显示，便于观察；与游戏 80px 格子成比例）
    GAP = 4
    COLOR_ALPHA = 0.5   # 模式 B 半透明填充强度（不遮住后面的背包/格子素材）

    def __init__(self):
        super().__init__()
        self.title("背包乱斗 AI 控制台")
        self.configure(bg=COLORS["bg"])
        self.geometry("1360x900")
        self.minsize(1180, 800)

        # 运行时状态
        self.bot: BackpackBot | None = None
        self.bot_thread: threading.Thread | None = None
        self.ui_queue: queue.Queue = queue.Queue()
        self._initialized = False
        self._closing = False
        self._state_thread: threading.Thread | None = None
        self._heartbeat = time.time()  # 主线程存活心跳（看门狗用）

        # 物品资源库（贴图 + 中文名 + 占格形状 + 格子素材）
        self.item_db = ItemDB()
        self._img_cache: dict = {}      # sprite 路径 -> PIL.Image
        self._bp_refs: list = []        # 背包贴图 PhotoImage 引用（防 GC）
        self._cell_cache: dict = {}     # "empty"/"filled" -> PhotoImage

        self._setup_style()
        self._build_layout()
        self._bind_keys()

        self.after(100, self._process_queue)
        self._start_state_poller()
        self._start_exit_watchdog()

        self.protocol("WM_DELETE_WINDOW", self._on_close)
        if _HAS_PIL:
            self._log("info", "欢迎使用背包乱斗 AI 控制台。请先启动游戏，再点击「初始化」。")
        else:
            self._log("warning", "未检测到 PIL，贴图将退化为色块显示（请安装 Pillow 后重试）。")

    # ---------- 样式 ----------
    def _setup_style(self):
        style = ttk.Style(self)
        try:
            style.theme_use("clam")
        except Exception:
            pass
        style.configure("TCombobox",
                        fieldbackground=COLORS["panel_light"],
                        background=COLORS["panel_light"],
                        foreground=COLORS["text"],
                        arrowcolor=COLORS["text"],
                        borderwidth=0)
        style.map("TCombobox",
                  fieldbackground=[("readonly", COLORS["panel_light"])],
                  foreground=[("readonly", COLORS["text"])])

    # ---------- 布局 ----------
    def _build_layout(self):
        header = tk.Frame(self, bg=COLORS["panel"], height=54)
        header.pack(fill="x", side="top")
        header.pack_propagate(False)

        tk.Label(header, text="背包乱斗 AI", font=FONTS["title"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left", padx=18)

        self.status_dot = tk.Canvas(header, width=14, height=14, bg=COLORS["panel"],
                                    highlightthickness=0)
        self.status_dot.pack(side="right", padx=(6, 18))
        self._dot = self.status_dot.create_oval(2, 2, 12, 12,
                                                fill=COLORS["text_dim"], outline="")
        self.status_text = tk.Label(header, text="未连接", font=FONTS["small"],
                                    bg=COLORS["panel"], fg=COLORS["text_dim"])
        self.status_text.pack(side="right")

        body = tk.Frame(self, bg=COLORS["bg"])
        body.pack(fill="both", expand=True, padx=10, pady=10)

        left = tk.Frame(body, bg=COLORS["bg"], width=370)
        left.pack(side="left", fill="y")
        left.pack_propagate(False)

        right = tk.Frame(body, bg=COLORS["bg"])
        right.pack(side="left", fill="both", expand=True, padx=(10, 0))

        self._build_stats(left)
        self._build_controls(left)
        self._build_backpack(right)
        self._build_storage_shop(right)
        self._build_log(right)

    def _build_stats(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="x", pady=(0, 8))

        tk.Label(panel, text="游戏状态", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(anchor="w", padx=12, pady=(10, 4))

        row = tk.Frame(panel, bg=COLORS["panel"])
        row.pack(fill="x", padx=8, pady=(0, 8))

        self.stat_vars = {}
        for key, label, color in [
            ("gold", "金币", COLORS["warning"]),
            ("hp", "生命", COLORS["danger"]),
            ("round", "回合", COLORS["accent"]),
        ]:
            cell = tk.Frame(row, bg=COLORS["panel_light"])
            cell.pack(side="left", expand=True, fill="both", padx=3)
            var = tk.StringVar(value="—")
            self.stat_vars[key] = var
            tk.Label(cell, textvariable=var, font=FONTS["stat_value"],
                     bg=COLORS["panel_light"], fg=color).pack(pady=(8, 0))
            tk.Label(cell, text=label, font=FONTS["stat_label"],
                     bg=COLORS["panel_light"], fg=COLORS["text_dim"]).pack(pady=(0, 8))

        info = tk.Frame(panel, bg=COLORS["panel"])
        info.pack(fill="x", padx=12, pady=(0, 8))
        self.phase_var = tk.StringVar(value="阶段: —")
        tk.Label(info, textvariable=self.phase_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")

    # ---------- 控制按钮（2×3 网格，避免被宽度裁切）----------
    def _build_controls(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="x", pady=(8, 0))

        tk.Label(panel, text="控制", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(anchor="w", padx=12, pady=(10, 4))

        # 策略选择
        top = tk.Frame(panel, bg=COLORS["panel"])
        top.pack(fill="x", padx=12, pady=(0, 6))
        tk.Label(top, text="AI 策略:", font=FONTS["body"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")
        self.strategy_var = tk.StringVar(value="heuristic")
        combo = ttk.Combobox(top, textvariable=self.strategy_var, state="readonly",
                             values=["heuristic", "llm"], width=12)
        combo.pack(side="left", padx=(8, 0))

        # 渲染模式切换（请求 #8）
        mrow = tk.Frame(panel, bg=COLORS["panel"])
        mrow.pack(fill="x", padx=12, pady=(0, 6))
        tk.Label(mrow, text="背包渲染:", font=FONTS["body"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")
        self.render_mode_var = tk.StringVar(value="sprite")
        mcombo = ttk.Combobox(mrow, textvariable=self.render_mode_var, state="readonly",
                              values=["sprite", "color"], width=12)
        mcombo.pack(side="left", padx=(8, 0))
        tk.Label(mrow, text="贴图 / 染色", font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left", padx=(6, 0))

        # 按钮 2×3 网格
        btns = tk.Frame(panel, bg=COLORS["panel"])
        btns.pack(fill="x", padx=10, pady=(4, 12))
        specs = [
            ("init", "初始化", COLORS["accent"], self._on_init),
            ("start", "开始", COLORS["success"], self._on_start),
            ("pause", "暂停", COLORS["warning"], self._on_pause),
            ("step", "单步", COLORS["accent"], self._on_step),
            ("stop", "停止", COLORS["border"], self._on_stop),
            ("estop", "紧急停止", COLORS["danger"], self._on_emergency),
        ]
        self.buttons = {}
        for i, (key, label, color, cmd) in enumerate(specs):
            r, c = divmod(i, 3)
            b = tk.Button(btns, text=label, font=FONTS["button"], relief="flat",
                          bg=color, fg="#ffffff", cursor="hand2",
                          activebackground=color, activeforeground="#ffffff",
                          command=cmd, padx=6, pady=7)
            b.grid(row=r, column=c, padx=3, pady=3, sticky="nsew")
            btns.columnconfigure(c, weight=1)
            btns.rowconfigure(r, weight=1)
            self.buttons[key] = b

        self._set_buttons_state(running=False, initialized=False)

    # ---------- 背包大图（仿游戏：格子素材 + 物品）----------
    def _build_backpack(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="both", expand=True)

        head = tk.Frame(panel, bg=COLORS["panel"])
        head.pack(fill="x", padx=12, pady=(10, 4))
        tk.Label(head, text="背包摆盘  9×7", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left")
        self.bp_count_var = tk.StringVar(value="物品 0")
        tk.Label(head, textvariable=self.bp_count_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["accent"]).pack(side="right")

        cw = self.GRID_COLS * (self.CELL + self.GAP) + self.GAP
        ch = self.GRID_ROWS * (self.CELL + self.GAP) + self.GAP
        self.grid_canvas = tk.Canvas(panel, width=cw, height=ch,
                                     bg=COLORS["panel"], highlightthickness=0)
        self.grid_canvas.pack(padx=12, pady=(0, 6))

        self.legend = tk.Label(panel, text="", font=FONTS["small"],
                               bg=COLORS["panel"], fg=COLORS["text_dim"])
        self.legend.pack(anchor="w", padx=12, pady=(0, 6))

    def _cell_img(self, kind: str):
        """缓存的格子素材 PhotoImage（Slot / FilledSlot），尺寸对齐 CELL。"""
        if kind in self._cell_cache:
            return self._cell_cache[kind]
        path = (self.item_db.cell_empty_path() if kind == "empty"
                else self.item_db.cell_filled_path())
        if path and _HAS_PIL:
            try:
                img = Image.open(path).convert("RGBA").resize(
                    (self.CELL, self.CELL), Image.LANCZOS)
                photo = ImageTk.PhotoImage(img)
                self._cell_cache[kind] = photo
                return photo
            except Exception:
                pass
        self._cell_cache[kind] = None
        return None

    def _draw_backpack(self, items):
        """仿游戏渲染，严格分层（底→顶）：背包底框 → 背包(容器) → 格子素材 → 普通物品。

        渲染顺序即 z 序：
          1) 背包底框（每个格子底色）
          2) 背包(容器)贴图 —— 放在最底层，使其上能叠出它占用的每一个格子
          3) 格子素材(FilledSlot) —— 渲染在背包之上，便于分辨同一背包的不同格子
          4) 普通物品（贴图 / 半透明染色） —— 显示在最上层
        """
        self._bp_refs = []
        self.grid_canvas.delete("all")

        # 收集被占用的格子（用于决定用 Slot 还是 FilledSlot）
        occupied = set()
        for it in items:
            for (r, c) in (it.get("cells") or []):
                if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS:
                    occupied.add((r, c))

        # 图层 1：背包底框（所有格子底色）
        self._draw_base_layer()

        mode = self.render_mode_var.get()
        bags = [it for it in items if it.get("is_bag")]
        regulars = [it for it in items if not it.get("is_bag")]

        # 图层 2：背包(容器)贴图 —— 画在格子之下，让格子能叠在它上面
        for it in bags:
            self._draw_bag(it, mode)

        # 图层 3：格子素材 —— 渲染在背包之上（仅占用格画 FilledSlot）
        self._draw_cell_layer(occupied)

        # 图层 4：普通物品 —— 显示在最上层
        if mode == "color":
            self.legend.configure(
                text="染色模式：背包用贴图、物品用半透明同色+文字（相邻不同色）；格子素材只画占用格")
            self._draw_items_color(regulars)
        else:
            self.legend.configure(
                text="贴图模式：游戏内资源渲染（按旋转对齐网格）；蓝框=占用格；格子素材只画占用格")
            self._draw_items_sprite(regulars)

    def _draw_base_layer(self):
        """背包底框：所有格子的底色框（最底层）。"""
        for r in range(self.GRID_ROWS):
            for c in range(self.GRID_COLS):
                x0 = self.GAP + c * (self.CELL + self.GAP)
                y0 = self.GAP + r * (self.CELL + self.GAP)
                x1 = x0 + self.CELL
                y1 = y0 + self.CELL
                self.grid_canvas.create_rectangle(
                    x0, y0, x1, y1, fill=COLORS["grid_empty"],
                    outline=COLORS["grid_border"])

    def _draw_cell_layer(self, occupied):
        """格子素材：仅对「被物品占用的格子」渲染 FilledSlot；空格子不渲染。
        渲染在背包(容器)之上，便于分辨同一背包占用的不同格子。"""
        filled = self._cell_img("filled")
        if not filled:
            return
        for (r, c) in occupied:
            if not (0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS):
                continue
            x0 = self.GAP + c * (self.CELL + self.GAP)
            y0 = self.GAP + r * (self.CELL + self.GAP)
            self.grid_canvas.create_image(
                x0 + self.CELL / 2, y0 + self.CELL / 2, image=filled)

    def _draw_bag(self, it, mode):
        """绘制背包(容器)：贴图渲染，允许略微超出格子(不变形)；小标签放底部。"""
        reg = self._item_region(it)
        if not reg:
            return
        cells, x0, y0, bw, bh = reg
        # 背包允许稍微超出格子（仍等比不变形），普通物品 overflow_px=0 严格不超出
        self._draw_sprite_scaled(it, x0, y0, bw, bh,
                                 overflow_px=max(8, int(self.CELL * 0.3)))
        self._draw_name_label(x0, y0, bw, bh, it.get("zh") or it["name"],
                              bold=(mode == "color"), pos="bottom")

    def _item_region(self, it):
        cells = [(r, c) for (r, c) in (it.get("cells") or [])
                 if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS]
        if not cells:
            a = it.get("row"), it.get("col")
            if a and 0 <= a[0] < self.GRID_ROWS and 0 <= a[1] < self.GRID_COLS:
                cells = [a]
            else:
                return None
        rs = [r for r, _ in cells]
        cs = [c for _, c in cells]
        minr, maxr = min(rs), max(rs)
        minc, maxc = min(cs), max(cs)
        x0 = self.GAP + minc * (self.CELL + self.GAP)
        y0 = self.GAP + minr * (self.CELL + self.GAP)
        bw = (maxc - minc + 1) * self.CELL + (maxc - minc) * self.GAP
        bh = (maxr - minr + 1) * self.CELL + (maxr - minr) * self.GAP
        return cells, x0, y0, bw, bh

    def _draw_sprite_scaled(self, it, x0, y0, bw, bh, overflow_px=0):
        """绘制单个物品的贴图：按内存 rotation 旋转、等比缩放(contain，不变形)、居中。

        旋转约定：item_db.occupied_cells 用游戏(Godot)约定——正角=顺时针(屏幕 y 向下)。
        已实测 PIL rotate(正角) 为逆时针，故此处取 -degrees(rot) 使其与游戏占格一致。
        缩放：contain（取小边），保持宽高比不变形；居中放在占用格包围盒里。
        overflow_px>0 时允许在包围盒基础上向外扩张少量(背包可稍微超出格子，
        但仍等比不变形)；普通物品 overflow_px=0，严格限制在格子内。
        """
        sp = self.item_db.sprite_path(it["name"])
        if not (sp and sp.exists() and _HAS_PIL):
            self._draw_fallback_tile(x0, y0, bw, bh, it.get("is_bag"))
            return
        img = self._load_image(sp)
        if img is None:
            self._draw_fallback_tile(x0, y0, bw, bh, it.get("is_bag"))
            return
        rot = it.get("rotation") or 0.0
        if abs(rot) > 1e-4:
            # 负号：与 Godot 顺时针旋转一致（PIL rotate 默认逆时针）
            img = img.rotate(-math.degrees(rot), expand=True, resample=Image.BICUBIC)
            bb = img.getbbox()
            if bb:
                img = img.crop(bb)
        # 等比缩放（contain，不变形）；overflow 时允许稍微超出格子
        box_w = bw + overflow_px * 2
        box_h = bh + overflow_px * 2
        iw, ih = img.size
        if iw > 0 and ih > 0:
            scale = min(box_w / iw, box_h / ih)
            if scale > 0 and abs(scale - 1.0) > 1e-3:
                nw = max(1, int(round(iw * scale)))
                nh = max(1, int(round(ih * scale)))
                img = img.resize((nw, nh), Image.LANCZOS)
        photo = ImageTk.PhotoImage(img)
        self._bp_refs.append(photo)
        # 始终以原包围盒中心为锚点居中（overflow 时向外略微溢出，仍不变形）
        self.grid_canvas.create_image(x0 + bw / 2, y0 + bh / 2, image=photo)

    def _draw_items_sprite(self, items):
        for it in items:
            reg = self._item_region(it)
            if not reg:
                continue
            cells, x0, y0, bw, bh = reg
            # 贴图（旋转 + 对齐网格，严格在格子内）；不绘制占用格边框高亮
            self._draw_sprite_scaled(it, x0, y0, bw, bh)
            self._draw_name_label(x0, y0, bw, bh, it.get("zh") or it["name"])

    def _draw_items_color(self, items):
        colors = self._assign_colors(items)
        for it in items:
            reg = self._item_region(it)
            if not reg:
                continue
            cells, x0, y0, bw, bh = reg
            rgb = _PALETTE[colors.get(it["name"], 0)]
            fill_hex = "#%02x%02x%02x" % rgb
            stroke = self._blend(_BG_RGB, rgb, 0.85)
            # 每个占用的格子：半透明同色填充(stipple 让底下的背包/格子素材透出) + 描边
            for (r, c) in cells:
                cx0 = self.GAP + c * (self.CELL + self.GAP)
                cy0 = self.GAP + r * (self.CELL + self.GAP)
                self.grid_canvas.create_rectangle(
                    cx0 + 1, cy0 + 1, cx0 + self.CELL - 1, cy0 + self.CELL - 1,
                    fill=fill_hex, stipple="gray50",
                    outline=stroke, width=1)
            # 居中文字（自动换行/字号）
            zh = it.get("zh") or it["name"]
            self._draw_name_label(x0, y0, bw, bh, zh, bold=True)

    def _draw_name_label(self, x0, y0, bw, bh, zh, bold=False, pos="center"):
        label = zh[:10]
        size, lines = self._fit_text(label, bw - 6, bh - 6, base=7)
        line_h = size + 2
        total_h = line_h * len(lines)
        if pos == "bottom":
            ty = y0 + bh - total_h / 2 - 2
        else:
            ty = y0 + bh / 2 - total_h / 2 + line_h / 2
        # 半透明底提高可读性
        self.grid_canvas.create_rectangle(
            x0 + 2, ty - line_h / 2 - 1, x0 + bw - 2, ty + total_h / 2 + 1,
            fill=COLORS["bg"], outline="", stipple="gray50")
        for ln in lines:
            self.grid_canvas.create_text(x0 + bw / 2, ty, text=ln,
                                         fill=COLORS["text"],
                                         font=(FONT_FAMILY, size, "bold" if bold else "normal"),
                                         anchor="center")
            ty += line_h

    def _draw_fallback_tile(self, x0, y0, bw, bh, is_bag):
        color = CATEGORY_COLORS["bag"] if is_bag else CATEGORY_COLORS["unknown"]
        self.grid_canvas.create_rectangle(x0 + 1, y0 + 1, x0 + bw - 1, y0 + bh - 1,
                                          fill=color, outline="")

    # ---------- 邻接着色（保证相邻物品不同色）----------
    def _assign_colors(self, items):
        occ = {}
        for it in items:
            for (r, c) in (it.get("cells") or []):
                if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS:
                    occ[(r, c)] = it["name"]
        neigh = defaultdict(set)
        for (r, c), nm in occ.items():
            for dr, dc in product((-1, 0, 1), (-1, 0, 1)):
                if dr == 0 and dc == 0:
                    continue
                o = occ.get((r + dr, c + dc))
                if o and o != nm:
                    neigh[nm].add(o)
                    neigh[o].add(nm)
        assigned = {}
        for nm in sorted(neigh, key=lambda n: -len(neigh[n])):
            used = {assigned.get(x) for x in neigh[nm] if x in assigned}
            for i in range(len(_PALETTE)):
                if i not in used:
                    assigned[nm] = i
                    break
            else:
                assigned[nm] = 0
        return assigned

    @staticmethod
    def _blend(bg, fg, a):
        return "#%02x%02x%02x" % tuple(
            int(bg[i] * (1 - a) + fg[i] * a) for i in range(3))

    # ---------- 自动字号 / 换行 ----------
    def _fit_text(self, text, box_w, box_h, base=7):
        for size in range(base, 6, -1):
            f = tkfont.Font(family=FONT_FAMILY, size=size)
            lines, cur = [], ""
            for ch in text:
                if f.measure(cur + ch) > box_w * 0.94 and cur:
                    lines.append(cur)
                    cur = ch
                else:
                    cur += ch
            if cur:
                lines.append(cur)
            if lines and len(lines) * (size + 2) <= box_h * 0.94:
                return size, lines
        # 兜底：最小字号，强制换行
        f = tkfont.Font(family=FONT_FAMILY, size=7)
        lines, cur = [], ""
        for ch in text:
            if f.measure(cur + ch) > box_w * 0.94 and cur:
                lines.append(cur)
                cur = ch
            else:
                cur += ch
        if cur:
            lines.append(cur)
        return 7, lines

    def _load_image(self, path: Path):
        if not _HAS_PIL:
            return None
        p = str(path)
        img = self._img_cache.get(p)
        if img is None:
            try:
                img = Image.open(path).convert("RGBA")
                self._img_cache[p] = img
            except Exception:
                return None
        return img

    # ---------- 储物箱 / 商店（纯文字分区；商店显示价格）----------
    def _build_storage_shop(self, parent):
        # 专门区域：固定高度 + 强调边框，确保不会被背包/日志挤压到不可见
        row = tk.Frame(parent, bg=COLORS["bg"], height=200)
        row.pack(fill="x", pady=(0, 6))
        row.pack_propagate(False)

        self.storage_text, self.storage_count = self._make_text_panel(
            row, "储物箱", COLORS["warning"])
        self.shop_text, self.shop_count = self._make_text_panel(
            row, "商店在售", COLORS["success"])

    def _make_text_panel(self, parent, title, accent):
        panel = tk.Frame(parent, bg=COLORS["panel"],
                         highlightbackground=accent, highlightthickness=1)
        panel.pack(side="left", fill="both", expand=True, padx=(0, 6))
        panel.pack_propagate(False)

        head = tk.Frame(panel, bg=COLORS["panel"])
        head.pack(fill="x", padx=12, pady=(8, 4))
        tk.Label(head, text=title, font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=accent).pack(side="left")
        count_var = tk.StringVar(value="0")
        tk.Label(head, textvariable=count_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="right")

        wrap = tk.Frame(panel, bg=COLORS["border"])
        wrap.pack(fill="both", expand=True, padx=12, pady=(0, 8))
        txt = tk.Text(wrap, bg=COLORS["bg"], fg=COLORS["text"],
                      font=FONTS["body"], relief="flat", wrap="word",
                      insertbackground=COLORS["bg"], padx=8, pady=6,
                      state="disabled")
        scroll = tk.Scrollbar(wrap, command=txt.yview)
        txt.configure(yscrollcommand=scroll.set)
        scroll.pack(side="right", fill="y")
        txt.pack(side="left", fill="both", expand=True)
        txt.tag_config("bag", foreground=COLORS["accent"])
        txt.tag_config("dim", foreground=COLORS["text_dim"])
        return txt, count_var

    def _refresh_text_panel(self, txt, items, count_var):
        txt.configure(state="normal")
        txt.delete("1.0", "end")
        if not items:
            txt.insert("end", "（暂无物品）\n", "dim")
            txt.configure(state="disabled")
            count_var.set("0")
            return
        for it in items:
            zh = it.get("zh") or it["name"]
            line = zh
            if it.get("is_bag"):
                line += "  [容器]"
            txt.insert("end", line + "\n")
        txt.configure(state="disabled")
        count_var.set(str(len(items)))

    # ---------- 日志 ----------
    def _build_log(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="both", expand=True)

        bar = tk.Frame(panel, bg=COLORS["panel"])
        bar.pack(fill="x", padx=12, pady=(10, 4))
        tk.Label(bar, text="运行日志", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left")
        tk.Button(bar, text="清空", font=FONTS["small"], relief="flat",
                  bg=COLORS["panel_light"], fg=COLORS["text_dim"],
                  activebackground=COLORS["border"], activeforeground=COLORS["text"],
                  cursor="hand2", command=self._clear_log).pack(side="right")

        wrap = tk.Frame(panel, bg=COLORS["border"])
        wrap.pack(fill="both", expand=True, padx=12, pady=(0, 12))
        self.log_text = tk.Text(wrap, bg=COLORS["bg"], fg=COLORS["text"],
                                font=FONTS["mono"], relief="flat", wrap="word",
                                insertbackground=COLORS["text"], padx=8, pady=6,
                                state="disabled")
        scroll = tk.Scrollbar(wrap, command=self.log_text.yview)
        self.log_text.configure(yscrollcommand=scroll.set)
        scroll.pack(side="right", fill="y")
        self.log_text.pack(side="left", fill="both", expand=True)

        self.log_text.tag_config("info", foreground=COLORS["text"])
        self.log_text.tag_config("warning", foreground=COLORS["warning"])
        self.log_text.tag_config("error", foreground=COLORS["danger"])
        self.log_text.tag_config("debug", foreground=COLORS["text_dim"])
        self.log_text.tag_config("success", foreground=COLORS["success"])

    # ---------- 按钮状态 ----------
    def _set_buttons_state(self, running: bool, initialized: bool):
        def en(b, ok):
            b.configure(state="normal" if ok else "disabled")
        en(self.buttons["init"], not running)
        en(self.buttons["start"], initialized and not running)
        en(self.buttons["pause"], running)
        en(self.buttons["step"], initialized and not running)
        en(self.buttons["stop"], running)
        en(self.buttons["estop"], True)

    def _set_status(self, text: str, color: str):
        self.status_text.configure(text=text, fg=color)
        self.status_dot.itemconfig(self._dot, fill=color)

    # ---------- 控制回调 ----------
    def _on_init(self):
        if self.bot is None:
            try:
                self.bot = BackpackBot(get_config_path())
            except Exception as e:
                messagebox.showerror("错误", f"创建机器人失败:\n{e}")
                return
        self._apply_strategy()

        self._set_status("初始化中...", COLORS["warning"])
        self._log("info", "开始初始化...")

        def worker():
            try:
                ok = self.bot.initialize()
                if ok and not self.bot.needs_auto_calibration:
                    self.bot.scan_memory_values()
                self.ui_queue.put(("init_done", ok, None))
            except Exception as e:
                import traceback
                self.ui_queue.put(("init_done", False, traceback.format_exc()))

        threading.Thread(target=worker, daemon=True).start()

    def _apply_strategy(self):
        from core.ai_interface import HeuristicStrategy, LLMStrategy
        if not self.bot:
            return
        cfg = self.bot.config.get("ai", {})
        if self.strategy_var.get() == "llm":
            self.bot.strategy = LLMStrategy(cfg)
        else:
            self.bot.strategy = HeuristicStrategy(cfg)

    def _on_start(self):
        if not self.bot or not self._initialized:
            messagebox.showwarning("提示", "请先初始化")
            return
        if self.bot_thread and self.bot_thread.is_alive():
            return
        self._apply_strategy()
        self.bot.step_mode = False
        self.bot.paused = False

        def worker():
            try:
                self.bot.start()
            except Exception as e:
                import traceback
                self.ui_queue.put(("log", "error", traceback.format_exc()))
            finally:
                self.ui_queue.put(("bot_stopped", None, None))

        self.bot_thread = threading.Thread(target=worker, daemon=True)
        self.bot_thread.start()
        self._set_status("运行中", COLORS["success"])
        self._set_buttons_state(running=True, initialized=True)

    def _on_pause(self):
        if not self.bot:
            return
        if self.bot.paused:
            self.bot.resume()
            self.buttons["pause"].configure(text="暂停")
            self._set_status("运行中", COLORS["success"])
        else:
            self.bot.pause()
            self.buttons["pause"].configure(text="继续")
            self._set_status("已暂停", COLORS["warning"])

    def _toggle_pause(self):
        if self.bot and self.bot.running:
            self._on_pause()

    def _on_step(self):
        if not self.bot or not self._initialized:
            messagebox.showwarning("提示", "请先初始化")
            return
        if self.bot_thread and self.bot_thread.is_alive():
            self._log("warning", "机器人正在运行，无法单步")
            return
        self._apply_strategy()
        self._log("info", "执行单步...")

        def worker():
            try:
                self.bot.running = True
                self.bot._stop_event.clear()
                self.bot.run_round()
            except Exception as e:
                import traceback
                self.ui_queue.put(("log", "error", traceback.format_exc()))
            finally:
                self.bot.running = False
                self.ui_queue.put(("bot_stopped", None, None))

        self.bot_thread = threading.Thread(target=worker, daemon=True)
        self.bot_thread.start()
        self._set_status("单步执行", COLORS["accent"])

    def _on_stop(self):
        if self.bot:
            self.bot.stop()
        self._set_status("已停止", COLORS["text_dim"])
        self._set_buttons_state(running=False, initialized=self._initialized)
        self.buttons["pause"].configure(text="暂停")

    def _on_emergency(self):
        if self.bot:
            self.bot.stop()
        try:
            import pyautogui
            pyautogui.mouseUp()
        except Exception:
            pass
        self._set_status("紧急停止", COLORS["danger"])
        self._set_buttons_state(running=False, initialized=self._initialized)
        self.buttons["pause"].configure(text="暂停")
        self._log("warning", "⚠ 紧急停止已触发")

    # ---------- 日志 ----------
    def _log(self, level: str, msg: str):
        self.log_text.configure(state="normal")
        self.log_text.insert("end", msg + "\n", level)
        self.log_text.see("end")
        self.log_text.configure(state="disabled")

    def _clear_log(self):
        self.log_text.configure(state="normal")
        self.log_text.delete("1.0", "end")
        self.log_text.configure(state="disabled")

    # ---------- 队列消费 ----------
    def _process_queue(self):
        self._heartbeat = time.time()  # 主线程存活心跳（看门狗用）
        try:
            while True:
                kind, a, b = self.ui_queue.get_nowait()
                if kind == "log":
                    self._log(a, b)
                elif kind == "init_done":
                    self._on_init_done(a, b)
                elif kind == "bot_stopped":
                    self._on_bot_stopped()
                elif kind == "auto_cal_rva":
                    self._on_auto_cal_rva(a)
                elif kind == "state":
                    self._apply_state(a)
        except queue.Empty:
            pass
        self.after(100, self._process_queue)

    def _on_init_done(self, ok: bool, err: str):
        if ok:
            self._initialized = True
            self._log("success", "✓ 初始化完成，可以开始")
            if self.bot and self.bot.godot_reader and self.bot.godot_reader.is_ready():
                self._set_status("已就绪", COLORS["success"])
                self._log("success", "✓ 结构性读取已启用：金币/血量/回合自动读取")
                self._set_buttons_state(running=False, initialized=True)
            elif self.bot and self.bot.needs_auto_calibration:
                self._start_auto_calibration()
            else:
                self._set_status("已就绪", COLORS["success"])
                self._set_buttons_state(running=False, initialized=True)
        else:
            self._initialized = False
            self._set_status("初始化失败", COLORS["danger"])
            if err:
                self._log("error", err)
            self._log("error", "初始化失败：请确认游戏已启动，并以管理员权限运行本程序")
            self._set_buttons_state(running=False, initialized=False)

    # ---------- 自动标定（仅定位 OS 结构，无需手动填金币等值）----------
    def _start_auto_calibration(self):
        self._set_status("自动标定中...", COLORS["warning"])
        self._set_buttons_state(running=False, initialized=False)
        self._log("info", "正在自动定位游戏数据结构（OS::singleton）...")

        def worker():
            try:
                rva = self.bot.discover_godot_rva()
            except Exception as e:  # noqa: BLE001
                rva = None
                self.ui_queue.put(("log", "error", f"自动标定失败: {e}"))
            self.ui_queue.put(("auto_cal_rva", rva, None))

        threading.Thread(target=worker, daemon=True).start()

    def _on_auto_cal_rva(self, rva):
        if not rva:
            self._log("error", "自动标定失败：未能定位 OS::singleton，统计值将不可用（无需手动填值）。")
            self._set_status("已就绪（无统计）", COLORS["text_dim"])
            self._set_buttons_state(running=False, initialized=True)
            return
        self._log("success", f"✓ 已定位游戏数据结构 (RVA={hex(rva)})，统计值将自动读取")
        self._set_status("已就绪", COLORS["success"])
        self._set_buttons_state(running=False, initialized=True)

    def _on_bot_stopped(self):
        self._set_status("已停止", COLORS["text_dim"])
        self._set_buttons_state(running=False, initialized=self._initialized)

    # ---------- 状态刷新（后台线程轮询，避免阻塞主线程导致无法响应关闭）----------
    def _start_state_poller(self):
        """启动后台守护线程周期性读取游戏状态并推入 UI 队列。

        关键：get_state() 内部会调用 ReadProcessMemory，可能阻塞；
        若在主线程上阻塞，窗口事件循环卡死，点击关闭(X)无法触发 _on_close，
        进程便残留。改到后台线程后，主线程事件循环永远可响应关闭。
        """
        if self._state_thread and self._state_thread.is_alive():
            return

        def _poll():
            while not self._closing:
                try:
                    if self.bot and self._initialized:
                        state = self.bot.get_state()
                        self.ui_queue.put(("state", state, None))
                except Exception:
                    # 单次读取失败不应终止轮询线程
                    pass
                try:
                    time.sleep(0.5)
                except Exception:
                    pass

        self._state_thread = threading.Thread(target=_poll, daemon=True)
        self._state_thread.start()

    def _start_exit_watchdog(self):
        """『生命看门狗』守护线程：作为进程退出的终极兜底。

        即便 _on_close 因任何原因未被触发（事件循环卡死、WM_DELETE_WINDOW 未派发
        等），只要出现以下任一情况就强制 os._exit(0) 终止整个进程，杜绝残留：
          1) 已请求关闭（_closing 为真）；
          2) 主窗口已被销毁（winfo_exists() 为假）——无论因何种方式关闭；
          3) 主线程心跳超时（>8s 未更新）——说明主线程疑似卡死（如绘制/读取异常），
             此时强制退出，避免进程变成僵尸。
        看门狗本身不依赖任何 GUI 调用能否成功，异常也照常退出。
        """
        def _watch():
            while True:
                try:
                    time.sleep(0.3)
                except Exception:
                    pass
                try:
                    if self._closing:
                        os._exit(0)
                    if not self.winfo_exists():
                        os._exit(0)
                    if time.time() - self._heartbeat > 15:
                        os._exit(0)
                except Exception:
                    # 连 winfo_exists 都抛异常（窗口已半销毁）→ 直接退出
                    try:
                        os._exit(0)
                    except Exception:
                        pass
        threading.Thread(target=_watch, daemon=True).start()

    def _apply_state(self, state):
        cal = state.get("calibrated", {})
        gold = state.get("gold") if cal.get("gold") else "—"
        hp = state.get("hp") if cal.get("hp") else "—"
        rnd = state.get("round") if cal.get("round") else "—"
        self.stat_vars["gold"].set(str(gold))
        self.stat_vars["hp"].set(
            f"{hp}/{state.get('max_hp', 5)}" if hp != "—" else "—/5")
        self.stat_vars["round"].set(
            f"{rnd}/{state.get('max_rounds', 18)}" if rnd != "—" else "—/18")
        phase = "商店" if state.get("phase") == "shop" else "战斗"
        live = state.get("live_items")
        if live is not None:
            n_bp = state.get("live_backpack_count", 0)
            n_st = state.get("live_storage_count", 0)
            self.phase_var.set(f"阶段: {phase}  |  摆盘: {n_bp}  储物箱: {n_st}")
            self.bp_count_var.set(f"物品 {n_bp}")
            bp = live.get("backpack", [])
            self._draw_backpack(bp)
            self._refresh_text_panel(self.storage_text, live.get("storage", []),
                                     self.storage_count)
            self._refresh_text_panel(self.shop_text, live.get("shop", []),
                                     self.shop_count)

    def _on_close(self):
        # 1) 立刻置关闭标志（生命看门狗会据此在 0.3s 内强制退出）
        self._closing = True
        # 2) 看门狗：独立 daemon 线程，短延时后无条件 os._exit(0)。
        #    即使本函数后续任何步骤卡死/抛错，进程也必然终止。
        def _kill():
            try:
                time.sleep(0.25)
            except Exception:
                pass
            os._exit(0)
        threading.Thread(target=_kill, daemon=True).start()
        # 3) bot.stop() 放到【独立后台线程】，绝不让主线程阻塞
        #    （避免 CloseHandle / 等待游戏进程 等任何意外卡死主线程，进而卡死看门狗）。
        def _stop_bot():
            try:
                if self.bot:
                    self.bot.stop()
            except Exception:
                pass
        threading.Thread(target=_stop_bot, daemon=True).start()
        # 4) 主线程只做轻量退出（不调用任何可能阻塞的操作）
        try:
            self.quit()
        except Exception:
            pass
        try:
            self.destroy()
        except Exception:
            pass
        # 5) 同步兜底：主线程若顺利走到这里，立刻结束。
        os._exit(0)

    def _bind_keys(self):
        self.bind("<space>", lambda e: self._toggle_pause())
        self.bind("<Escape>", lambda e: self._on_emergency())


def run():
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(message)s",
        datefmt="%H:%M:%S",
    )
    app = BackpackAIApp()

    handler = QueueLogHandler(app.ui_queue)
    handler.setFormatter(logging.Formatter("%(asctime)s %(message)s", datefmt="%H:%M:%S"))
    logging.getLogger().addHandler(handler)

    app.mainloop()


if __name__ == "__main__":
    run()

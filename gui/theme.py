"""
GUI 主题与配色 — 深色主题
"""

# 配色方案（深色）
COLORS = {
    "bg": "#1a1d24",           # 主背景
    "panel": "#232730",         # 面板背景
    "panel_light": "#2c313c",   # 次级面板
    "border": "#363b47",        # 边框
    "text": "#e4e7eb",          # 主文字
    "text_dim": "#8b93a1",      # 次级文字
    "accent": "#4f9cf9",        # 强调蓝
    "accent_hover": "#6fb0ff",
    "success": "#3fb950",       # 绿
    "warning": "#d29922",       # 黄
    "danger": "#f85149",        # 红
    "grid_empty": "#2a2f3a",    # 空格子
    "grid_border": "#3a4150",
}

# 物品分类配色
CATEGORY_COLORS = {
    "weapon": "#f85149",     # 武器 - 红
    "armor": "#4f9cf9",      # 护甲 - 蓝
    "food": "#3fb950",       # 食物 - 绿
    "potion": "#bc8cff",     # 药水 - 紫
    "accessory": "#d29922",  # 饰品 - 黄
    "bag": "#8b93a1",        # 背包 - 灰
    "unknown": "#6e7681",    # 未知 - 深灰
}

# 字体
FONT_FAMILY = "Microsoft YaHei UI"
FONT_MONO = "Consolas"

FONTS = {
    "title": (FONT_FAMILY, 15, "bold"),
    "subtitle": (FONT_FAMILY, 11, "bold"),
    "body": (FONT_FAMILY, 10),
    "small": (FONT_FAMILY, 9),
    "stat_value": (FONT_FAMILY, 20, "bold"),
    "stat_label": (FONT_FAMILY, 9),
    "mono": (FONT_MONO, 9),
    "button": (FONT_FAMILY, 10, "bold"),
}

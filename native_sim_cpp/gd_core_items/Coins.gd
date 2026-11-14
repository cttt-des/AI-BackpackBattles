# Coins（一堆金币）：原版无脚本（oracle/Items/ 只有 Coins.tscn，无 Coins.gd）
# ——纯惰性库存件，战斗面零行为（battle_items.json: can_activate=false、
# effect.type=none）。此件只为让描述符/夹具链能装配它（np51：扩样语料 25 场
# 持有 Coins，此前 gd_core 描述符表无此件 ⇒ 夹具期硬剔除），语义=基类 Item 原样。
extends Item

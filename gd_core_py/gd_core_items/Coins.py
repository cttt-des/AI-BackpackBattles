# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Coins(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Coins.gd"

	# Coins（一堆金币）：原版无脚本（oracle/Items/ 只有 Coins.tscn，无 Coins.gd）
	# ——纯惰性库存件，战斗面零行为（battle_items.json: can_activate=false、
	# effect.type=none）。此件只为让描述符/夹具链能装配它（np51：扩样语料 25 场
	# 持有 Coins，此前 gd_core 描述符表无此件 ⇒ 夹具期硬剔除），语义=基类 Item 原样。


_R.reg("res://gd_core_items/Coins.gd", Coins)
_R.reg("Coins", Coins)

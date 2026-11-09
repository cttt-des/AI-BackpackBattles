# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DragonskinBoots(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DragonskinBoots.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")

		self.character().changeResistChance(_H_1, self.getChance())


	def onBattleRageStarted(self, event):
		self.cleanseRandomDebuffs(self.getP1(), event)
		self.giveEmpower(self.getP2(), event)
		self.giveBlock(self.getBlock(), True, event)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DragonskinBoots.gd", Exclusive__DragonskinBoots)
_R.reg("DragonskinBoots", Exclusive__DragonskinBoots)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
    _H_1 = _HoistPending(_he)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Wand(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Wand.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None
		self.manaNeeded = None
		self.luckNeeded = None
		self.regenNeeded = None
		self.empower = None
		self.buffsToUse = None


	def doCooldownEffect(self):
		self.giveLeastBuffs(1, self.character(), None, self.buffs)

		mana = self.character().getMana()
		luck = self.character().getLucky()
		regen = self.character().getRegeneration()

		if (mana >= self.manaNeeded or 
			luck >= self.luckNeeded or 
			regen >= self.regenNeeded):

				event = self.removeMostBuffs(self.buffsToUse, None, True, self.buffs)
				self.giveEmpower(self.empower, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.buffs = [_H_1, _H_2, _H_3]
		self.manaNeeded = int(self.getP("manat"))
		self.luckNeeded = int(self.getP("luckt"))
		self.regenNeeded = int(self.getP("regent"))
		self.empower = int(self.getP("empower"))
		self.buffsToUse = int(self.getP("use"))


_R.reg("res://gd_core_items/Exclusive/Wand.gd", Exclusive__Wand)
_R.reg("Wand", Exclusive__Wand)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
    _H_3 = _HoistPending(_he)

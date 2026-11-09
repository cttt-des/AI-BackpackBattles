# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__IceFlower(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/IceFlower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.cold = None
		self.mana = None


	def canAffect(self, item):
		return item.isWeapon()


	def canAffect_secondary(self, item):
		return item.hasType(_H_1) or (item.hasType(_H_4) and item.canActivate())


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_H_2)):
			self.connectForCombat(item, "attacked", "onWeaponAttacked")

		for item in _iter(self.getAffectedItems(_H_3)):
			self.connectForCombat(item, "activated", "onShieldOrArmorActivated")


	def onWeaponAttacked(self, damageRes):
		if self.character().getMana() >= self.manaNeeded and self.rollChance():
			event = self.useMana(self.manaNeeded)
			self.inflictCold(self.cold, event)
			self.miniActivate()


	def onShieldOrArmorActivated(self, event):
		if self.rollChance2():
			self.giveMana(self.mana)
			self.giveBlock()
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.cold = int(self.getP("cold"))
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/IceFlower.gd", Exclusive__IceFlower)
_R.reg("IceFlower", Exclusive__IceFlower)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Shield
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Type.Armor
except AttributeError as _he:
    _H_4 = _HoistPending(_he)

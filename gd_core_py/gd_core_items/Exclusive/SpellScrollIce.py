# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollIce(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollIce.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.coldInflicted = 0
		self.cold = None
		self.maxCold = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Shield) or (item.hasType(_R.C("CoreConst").Type.Armor) and item.canActivate())


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "pre_take_damage_late", "onCharacterAttacked")

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onShieldOrArmorActivated")
		self.coldInflicted = 0


	def onCharacterAttacked(self, damageRes):
		if not self.activated:
			if damageRes.willBeLethal(self.character()):
				opponentCold = self.opponent().getCold()
				if opponentCold > 0:
					self.activated = True
					self.opponent().loseCold(opponentCold, self, damageRes.event)
					self.giveBlock(round(self.getBlock() * opponentCold), True, damageRes.event)
					self.consume()


	def onShieldOrArmorActivated(self, event):
		if self.coldInflicted < self.maxCold and self.rollChance():
			self.coldInflicted = min(self.cold, self.maxCold - self.coldInflicted)
			self.inflictCold(self.cold, event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.cold = self.getP("cold")
		self.maxCold = self.getP("max")


_R.reg("res://gd_core_items/Exclusive/SpellScrollIce.gd", Exclusive__SpellScrollIce)
_R.reg("SpellScrollIce", Exclusive__SpellScrollIce)

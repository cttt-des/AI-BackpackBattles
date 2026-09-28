# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__KingGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/Exclusive/KingGoobert.gd"

	CrownState = EnumDict("CrownState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self.invuCharges = 0
		self.protectedBuffs = None
		self.manaCost = None
		self.activationParticles = None
		self.buffTimer = None
		self.light = None


	def prepare(self):
		gemPower = _div(self.getP('gempower'), 100.0)
		for gem in _iter(self.getGemsNoNull()):
			gem.changeGemPower(gemPower)

		self.invuCharges = self.getP("charges")
		self.setState(self.CrownState.Inactive)
		super().prepare()


	def doCooldownEffect(self):
		self.character().changeBuffProtectStacks(self.protectedBuffs)
		self.heal()
		if self.invuCharges > 0 and self.character().isVulnerable() and self.checkMana(self.manaCost):
			self.invuCharges -= 1
			self.setState(self.CrownState.Active, True)
			invuDur = self.getP_m("dur_invu")
			event = self.character().makeInvulnerable(invuDur, self)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, event)


	def buffEnded(self):
		if self.invuCharges > 0:
			self.setState(self.CrownState.Inactive, True)
		else:
			self.setState(self.CrownState.Used, True)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.CrownState.Inactive)


	def onStateChanged(self, _crownState):
		if _crownState == self.CrownState.Inactive:
			pass

		elif _crownState == self.CrownState.Active:
			pass

		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.protectedBuffs = self.getP("buffs")
		self.manaCost = self.getP("mana")
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)


_R.reg("res://gd_core_items/Exclusive/KingGoobert.gd", Exclusive__KingGoobert)
_R.reg("KingGoobert", Exclusive__KingGoobert)

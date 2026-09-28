# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DeathScythe(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/DeathScythe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.critBonusActive = False
		self.poisonThreshold = 0
		self.activationParticles = None


	def canAffect(self, item):
		return item.gainsStack(_R.C("CoreConst").Stack.Poison)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.opponent(), "character_poison_changed", "onOpponentPoisonChanged")
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Poison, 1)


	def onOpponentPoisonChanged(self, _amount, _event):
		curPoison = self.opponent().getPoison()

		if not self.critBonusActive and curPoison >= self.poisonThreshold:
			self.setState(True)
			self.changeCritChancePercent(self.getChance())


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _critBonusActive):
		if _critBonusActive:
			pass
		else:
			pass
		self.critBonusActive = _critBonusActive

	def _readyInit(self):
		super()._readyInit()
		self.poisonThreshold = self.getP1()


_R.reg("res://gd_core_items/DeathScythe.gd", DeathScythe)
_R.reg("DeathScythe", DeathScythe)

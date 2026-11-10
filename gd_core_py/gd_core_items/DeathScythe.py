# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DeathScythe_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/DeathScythe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.critBonusActive = False
		self._poisonThreshold = 0
		self.activationParticles = None

	@property
	def poisonThreshold(self):
		return self._poisonThreshold
	@poisonThreshold.setter
	def poisonThreshold(self, v):
		self._poisonThreshold = int(v)

	def canAffect(self, item):
		return item.gainsStack(_H_1)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.opponent(), "character_poison_changed", "onOpponentPoisonChanged")
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_2, 1)


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


_R.reg("res://gd_core_items/DeathScythe.gd", DeathScythe_2)
_R.reg("DeathScythe", DeathScythe_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Poison
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

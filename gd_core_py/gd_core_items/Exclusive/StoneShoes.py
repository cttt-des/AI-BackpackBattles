# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StoneShoes(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/StoneShoes.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.luck = None
		self.empower = None
		self.damReduction = None
		self.healthThreshold = None
		self.buffTimer = None
		self.activationParticles = None


	def onPrepare(self):
		self.setState(False)
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.giveLucky(self.getP2(), event)
			self.giveEmpower(self.getP3(), event)
			self.giveBlock(self.getBlock(), True, event)
			self.buffTimer.start(self.getP_m("dur"))
			self.setState(True)
			self.opponent().changeTypedDamageFactor(_H_1, - self.damReduction)
			self.opponent().changeEffectDamageFactor( - self.damReduction)
			self.consume()


	def onBuffTimeout(self):
		self.opponent().changeTypedDamageFactor(_H_1, self.damReduction)
		self.opponent().changeEffectDamageFactor(self.damReduction)
		self.setState(False)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, damResActive):
		if damResActive:
			pass
		else:
			pass


	def getTriggerPriority(self):
		return _H_2 + 3

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.luck = self.getP("luck")
		self.empower = self.getP("empower")
		self.damReduction = _div__loc(self.getP('damreduction'), 100.0)
		self.healthThreshold = _div__loc(self.getP1(), 100.0) - 0.0001
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffTimeout", False)


_R.reg("res://gd_core_items/Exclusive/StoneShoes.gd", Exclusive__StoneShoes)
_R.reg("StoneShoes", Exclusive__StoneShoes)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreDamageSource").Type.Ranged
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

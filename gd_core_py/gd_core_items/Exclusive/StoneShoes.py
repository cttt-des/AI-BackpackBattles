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
			self.opponent().changeTypedDamageFactor(_R.C("CoreDamageSource").Type.Ranged, - self.damReduction)
			self.opponent().changeEffectDamageFactor( - self.damReduction)
			self.consume()


	def onBuffTimeout(self):
		self.opponent().changeTypedDamageFactor(_R.C("CoreDamageSource").Type.Ranged, self.damReduction)
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
		return _R.C("CoreConst").Priority.High + 3

	def _readyInit(self):
		super()._readyInit()
		self.luck = self.getP("luck")
		self.empower = self.getP("empower")
		self.damReduction = _div(self.getP('damreduction'), 100.0)
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffTimeout", False)


_R.reg("res://gd_core_items/Exclusive/StoneShoes.gd", Exclusive__StoneShoes)
_R.reg("StoneShoes", Exclusive__StoneShoes)

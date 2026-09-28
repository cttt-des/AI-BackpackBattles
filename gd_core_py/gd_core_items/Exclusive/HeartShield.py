# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HeartShield(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/Exclusive/HeartShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.regenGiven = 0
		self.fillAnimation = None
		self.healamp = None
		self.blockFactor = None
		self.regenNeeded = None
		self.regenOnBlock = None
		self.regenMax = None


	def canAffect(self, item):
		return (item.canBlock() or 
				item.canHealOrLifesteal() or 
				item.gainsStack(_R.C("CoreConst").Stack.Regeneration))


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Block, self.blockFactor)
			item.changeHealAmp(self.healamp)
			item.changeAmplificiationChancePercent(_R.C("CoreConst").EventType.Regeneration, self.getChance2())

		self.setState(False)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.regenGiven = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)

		if self.regenGiven < self.regenMax:
			self.giveRegeneration(self.regenOnBlock, self.blockedDamageRes.event)
			self.regenGiven += self.regenOnBlock
		self.activate()


	def onRegenChanged(self, amount, event):
		if amount > 0 and not self.activated and self.character().getRegeneration() >= self.regenNeeded:
			self.setState(True, True)
			event2 = self.useRegeneration(self.regenNeeded, event)
			self.giveMaxHealth(self.getP_m("maxhealth"), event2)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, filled):
		if self.activated == filled:
			return
		self.activated = filled

		if filled:
			pass
		else:
			pass



	def preTakeDamage(self, damageRes):
		if self.activated:
			if damageRes.damageSource.isAttackOrEffect() and self.rollChance():
				self.blockedDamageRes = damageRes
				self.beforeBlock()
		else:
			super().preTakeDamage(damageRes)

	def _readyInit(self):
		super()._readyInit()
		self.healamp = _div(self.getP('healamp'), 100.0)
		self.blockFactor = _div(self.getP('block'), 100.0)
		self.regenNeeded = int(self.getP("regent"))
		self.regenOnBlock = int(self.getP("regen"))
		self.regenMax = int(self.getP("max_regen"))


_R.reg("res://gd_core_items/Exclusive/HeartShield.gd", Exclusive__HeartShield)
_R.reg("HeartShield", Exclusive__HeartShield)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StoneGolem(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/StoneGolem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.hasStunned = False
		self.empower = None
		self.regenThreshold = None
		self.bagOfStonesDescriptor = None
		self.activationParticles1 = None
		self.activationParticles2 = None


	def canAffect(self, item):
		return item.isA(self.bagOfStonesDescriptor)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.setState(False)


	def onPreCombatStart(self):
		self.addBonusDamage(self.getP("bonusdam") * self.getNumAffectedItems())


	def onRegenChanged(self, amount, event):
		if not self.activated and amount > 0:
			if self.character().getRegeneration() >= self.regenThreshold:
				self.setState(True, True)
				event2 = self.useRegeneration(self.regenThreshold, event)
				self.giveBlock(self.getBlock(), True, event2)
				self.baseCooldownOverride = self.getP4()
				self.updateBaseCooldown()


	def attack(self, triggerEvent=None):
		self.hasStunned = False
		res = self.dealDamage(triggerEvent)
		if self.hasStunned:
			self.activate(res, True, False, self.ActivationAni.Tackle)
		else:
			self.activate(res)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveEmpower(self.empower)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.hasStunned = True
				self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.activated = active


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 1

	def _readyInit(self):
		super()._readyInit()
		self.empower = self.getP("empower")
		self.regenThreshold = self.getP("regen")
		self.bagOfStonesDescriptor = self.ctx.item_book.getDescriptor("Bag of Stones")


_R.reg("res://gd_core_items/Exclusive/StoneGolem.gd", Exclusive__StoneGolem)
_R.reg("StoneGolem", Exclusive__StoneGolem)

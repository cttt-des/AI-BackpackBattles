# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Wisp(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Exclusive/Wisp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.luck = None
		self.regen = None
		self.natureSpeed = None
		self.damageForSpikes = None
		self.spikes = None

	gemColor = Color(0.783203, 0.972054, 1)

	def hasCooldown(self):
		return (self.getGemMode() == self.GemMode.Inventory or 
				self.getGemMode() == self.GemMode.Armor)


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def prepareInventory(self):
		self.addSpeed(self.getNumAffectedItems() * self.natureSpeed)


	def prepareWeapon(self):
		self.damageAcc = 0
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			self.damageAcc += damageRes.damage
			numProccs = _div(self.damageAcc, self.damageForSpikes)
			if numProccs > 0:
				self.damageAcc %= self.damageForSpikes
				self.giveSpikes(self.spikes * numProccs)
				self.miniActivate()


	def combatStart(self):
		if self.getGemMode() == self.GemMode.Inventory:
				self.baseCooldownOverride = self.getBaseCooldownIndex(0)
		elif self.getGemMode() == self.GemMode.Armor:
				self.baseCooldownOverride = self.getBaseCooldownIndex(1)
		super().combatStart()


	def doCooldownEffect(self):
		if self.getGemMode() == self.GemMode.Inventory:
				self.giveLucky(self.luck)
				self.giveRegeneration(self.regen)
				self.onAfterEffectFinished()

		elif self.getGemMode() == self.GemMode.Armor:
				bonusHealth = _div(self.getP_m('maxhealth'), 100.0) * self.character().getCurrentHealth()
				bonusHealth *= self.getGemPower()
				self.giveMaxHealth(bonusHealth)
				self.onAfterEffectFinished(False)
				self.consumed = True
				self.miniActivate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))
		self.natureSpeed = _div(self.getP('speed'), 100.0)
		self.damageForSpikes = int(self.getP("dam"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/Wisp.gd", Exclusive__Wisp)
_R.reg("Wisp", Exclusive__Wisp)

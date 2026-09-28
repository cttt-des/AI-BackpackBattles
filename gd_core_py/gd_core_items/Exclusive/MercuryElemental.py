# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MercuryElemental(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MercuryElemental.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaRegen = 0.0
		self.staminaUsed = 0.0
		self.poison = None
		self.selfPoison = None
		self.staminaThreshold = None
		self.distortion = None


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return color == _R.C("CoreConst").Affected.Primary


	def canAffect(self, item):
		return item.descriptor.isMeleeWeapon()


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentAttacked")
		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")

		self.staminaRegen = self.getP("stamina") * self.getNumDistinctAffectedItems()
		self.staminaUsed = 0


	def onOpponentAttacked(self, damageRes):
		if damageRes.triggerOnAttacked():
			self.giveBlock(_div(self.getBlock(), 100.0) * damageRes.damage)


	def doCooldownEffect(self):
		self.giveStamina(self.staminaRegen)
		self.activate()


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount
		ticks = floor(_div(self.staminaUsed, self.staminaThreshold))
		if ticks > 0:
			self.inflictPoison(ticks * self.poison)
			self.selfInflictPoison(ticks * self.selfPoison)
			self.staminaUsed -= ticks * self.staminaThreshold
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.selfPoison = int(self.getP("poison2"))
		self.staminaThreshold = self.getP("staminat")
		if self.ownerType == _R.C("CoreConst").Owner.GridStorage:
			pass
		else:
			pass



_R.reg("res://gd_core_items/Exclusive/MercuryElemental.gd", Exclusive__MercuryElemental)
_R.reg("MercuryElemental", Exclusive__MercuryElemental)

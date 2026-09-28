# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PerpetuumMobile(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PerpetuumMobile.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.staminaUsed = 0.0
		self.stamina = None
		self.buffRefund = None
		self.staminaRefund = None
		self.speed_v = None


	def canAffect(self, item):
		return item.isClassItem(_R.C("CoreConst").Classes_Full.Engineer)


	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffChanged")
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.usedStacks[buff] = 0.0

		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")
		self.staminaUsed = 0

		self.addSpeed(self.speed_v * self.getNumAffectedItems())


	def onCombatStart(self):
		self.giveMaxStaminaTemporary(self.stamina, None, False)
		self.activate()


	def onBuffChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount


	def doCooldownEffect(self):

		for buffType in _iter(self.usedStacks):
			toRefund = int(round(self.usedStacks[buffType] * self.buffRefund))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund)

		self.giveStamina(self.staminaUsed * self.staminaRefund)
		self.staminaUsed = 0

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.stamina = self.getP("stamina")
		self.buffRefund = _div(self.getP('refund_buffs'), 100.0)
		self.staminaRefund = _div(self.getP('refund_stamina'), 100.0)
		self.speed_v = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PerpetuumMobile.gd", Exclusive__PerpetuumMobile)
_R.reg("PerpetuumMobile", Exclusive__PerpetuumMobile)

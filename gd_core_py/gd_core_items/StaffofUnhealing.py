# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StaffofUnhealing(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/StaffofUnhealing.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffActive = False
		self.activationParticles = None
		self.unhealingTimer = None
		self.manaCost = None


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			healAmount = self.getP_m("heal")
			if self.character().getMana() >= self.manaCost:
				if not self.buffActive:
					self.setState(True, True)
					self.character().giveUnhealing(1.0)
				self.unhealingTimer.start(self.getP_m("dur_unhealing"))
				event = self.useMana(self.manaCost)
				self.heal(healAmount, event)
			else:
				self.heal(healAmount)

			self.activate()


	def buffEnded(self):
		self.character().reduceUnhealing(1.0)
		self.setState(False)


	def onCombatEnd(self):
		self.unhealingTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.buffActive = active

	def _readyInit(self):
		super()._readyInit()
		self.unhealingTimer = self.newItemTimer("UnhealingTimer", "buffEnded", False)
		self.manaCost = self.getP2()


_R.reg("res://gd_core_items/StaffofUnhealing.gd", StaffofUnhealing)
_R.reg("StaffofUnhealing", StaffofUnhealing)

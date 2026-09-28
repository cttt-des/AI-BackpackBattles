# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HogusBogus(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/HogusBogus.gd"

	def _init_fields(self):
		super()._init_fields()
		self.phase = 0
		self.maxStaminaUsed = None
		self.buffsPerStamina = None


	def onPrepare(self):
		self.phase = 0


	def trigger(self):
		self.setState(self.phase + 1)
		super().trigger()




	def canUseStamina(self):
		return True


	def doCooldownEffect(self):
		if self.phase == 1:
			curStamina = self.character().getCurrentStamina()
			step = _div(1.0, self.buffsPerStamina)
			if curStamina >= step:
				numProccs = floor(_div(curStamina, step))
				staminaToUse = min(curStamina, min(numProccs * step, self.maxStaminaUsed))
				self.useStamina(staminaToUse)
				self.giveRandomBuffs(round(staminaToUse * self.buffsPerStamina))
			self.activate()

		elif self.phase == 2:
			self.stun(self.getP_m("dur_stun"))
			self.character().stun(self.getP_m("dur_self_stun"), self)
			self.activate()

		else:
			curHealth = self.opponent().getCurrentHealth()
			self.heal(_div(curHealth * self.getP_m('heal'), 100.0))
			self.onAfterEffectFinished()


	def onStateChanged(self, _phase):
		self.phase = _phase
		if self.phase == 0:
			self.baseCooldownOverride = self.getBaseCooldownIndex(0)
		elif self.phase < 3:
			self.baseCooldownOverride = self.getBaseCooldownIndex(self.phase) - self.getBaseCooldownIndex(self.phase - 1)


	def _readyInit(self):
		super()._readyInit()
		self.maxStaminaUsed = self.getP("stamina")
		self.buffsPerStamina = self.getP("buffs")


_R.reg("res://gd_core_items/Exclusive/HogusBogus.gd", Exclusive__HogusBogus)
_R.reg("HogusBogus", Exclusive__HogusBogus)

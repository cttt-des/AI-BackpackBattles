# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RubyChonk(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/RubyChonk.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatThresholdReached = False
		self.hasStunned = False
		self.activationParticles = None
		self.heatThreshold = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if not self.heatThresholdReached:
			if self.character().getHeat() >= self.heatThreshold:
				self.setState(True, False, event)
		elif self.character().getHeat() < self.heatThreshold:
			self.setState(False, False, event)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			self.hasStunned = False
			res = self.dealDamage()
			if self.hasStunned:
				self.activate(res, False, False, self.ActivationAni.Tackle)
			else:
				self.activate(res, False)
			if res.hasHit():
				if self.hasStunned:
					pass
				else:
					pass
			else:
				pass


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.giveHeat(1, damageRes.event)
			if self.heatThresholdReached:
				if self.rollChance():
					self.stun(self.getP_m("dur_stun"), damageRes.event)
					self.hasStunned = True


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _heatThresholdReached):
		if _heatThresholdReached:
			pass
		else:
			pass

		self.heatThresholdReached = _heatThresholdReached


	def getCraftingOffset(self, forDirection):
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2(0, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2.ZERO
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		self.heatThreshold = int(self.getP1())


_R.reg("res://gd_core_items/RubyChonk.gd", RubyChonk)
_R.reg("RubyChonk", RubyChonk)

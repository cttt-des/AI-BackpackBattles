# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Greatsword_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Greatsword.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffed = False
		self.buffParticles = None
		self.empowerNeeded = None
		self.buffedStamina = None
		self.buffedCooldown = None


	def isBuffed(self):
		return self.buffed



	def getStaminaCost(self):
		override = self.statDisplayOverrides[_H_1]
		if override:
			return override

		if self.isBuffed():
			return self.buffedStamina * self.staminaFactor
		else:
			return super().getStaminaCost()


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_empower_changed", "empowerChanged")


	def empowerChanged(self, amount, event):
		if not self.buffed and self.character().getEmpower() >= self.empowerNeeded:
			self.setState(True)
			self.setBaseCooldown(self.buffedCooldown)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)

		elif self.buffed and self.character().getEmpower() < self.empowerNeeded:
			self.setState(False)
			self.resetBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _buffed):
		self.buffed = _buffed
		if self.buffed:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.empowerNeeded = int(self.getP1())
		self.buffedStamina = self.getP2()
		self.buffedCooldown = self.getP3()


_R.reg("res://gd_core_items/Greatsword.gd", Greatsword_2)
_R.reg("Greatsword", Greatsword_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").ItemStat.StaminaCost
except AttributeError as _he:
    _H_1 = _HoistPending(_he)

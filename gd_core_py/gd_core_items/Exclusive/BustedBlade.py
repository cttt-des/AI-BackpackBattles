# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BustedBlade(_R.C("res://gd_core_items/Greatsword.gd")):

	resource_path = "res://gd_core_items/Exclusive/BustedBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusDamPerEmpower = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")


	def onEmpowerChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.bonusDamPerEmpower)


	def onBattleRageStarted(self, _event):
		if not self.buffed:
			self.setState(True)
			self.baseCooldownOverride = self.getP3()
			self.updateBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.StaminaCost)


	def onBattleRageEnded(self, _event):
		if self.buffed:
			self.setState(False)
			self.baseCooldownOverride = self.getBaseCooldown()
			self.updateBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.StaminaCost)

	def _readyInit(self):
		super()._readyInit()
		self.bonusDamPerEmpower = self.getP1()


_R.reg("res://gd_core_items/Exclusive/BustedBlade.gd", Exclusive__BustedBlade)
_R.reg("BustedBlade", Exclusive__BustedBlade)

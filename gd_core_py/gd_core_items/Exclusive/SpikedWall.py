# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpikedWall(_R.C("res://gd_core_items/SpikedShield.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpikedWall.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesLimit = None
		self.staminaRegenMalus = None


	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnAttacked()


	def onPrepare(self):
		super().onPrepare()
		self.character().addBattleRageDuration(self.getP_m("dur_rage"))
		self.character().changeRangedSpikesLimit(self.spikesLimit)
		self.character().changeMeleeSpikesLimit(self.spikesLimit)
		baseStaminaRegen = self.character().baseStaminaRegen
		self.character().giveStaminaRegeneration(self.staminaRegenMalus * baseStaminaRegen)

	def _readyInit(self):
		super()._readyInit()
		self.spikesLimit = _div(self.getP('spikedam'), 100.0)
		self.staminaRegenMalus = _div(-self.getP('staminaregen'), 100.0)


_R.reg("res://gd_core_items/Exclusive/SpikedWall.gd", Exclusive__SpikedWall)
_R.reg("SpikedWall", Exclusive__SpikedWall)

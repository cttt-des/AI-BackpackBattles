# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PlasticCube(_R.C("res://gd_core_items/Exclusive/Cube.gd")):

	resource_path = "res://gd_core_items/Exclusive/PlasticCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikes = None


	def canAffect(self, item):
		return item.hasCooldown()


	def doCooldownEffect(self):
		self.deactivateCooldown()

		affectedItem = self.getFirstAffectedItem()
		if affectedItem != None:
			if not affectedItem in self.ctx.cube_advanced:
				self.ctx.cube_advanced[affectedItem] = self
				affectedItem.advanceCooldownPercent(self.cdAdvance)
			else:
				affectedItem.advanceCooldownPercent(self.cdAdvance * self.penaltyFactor)

		self.giveSpikes(self.spikes)
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/PlasticCube.gd", Exclusive__PlasticCube)
_R.reg("PlasticCube", Exclusive__PlasticCube)

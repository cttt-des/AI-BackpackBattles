# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Goobert(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Goobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activations = 0
		self.goobertAnimation = None
		self.activationsToTrigger = None


	def logCooldown(self):
		return True


	def canAffect(self, item):
		return item.canActivate()


	def prepare(self):
		self.activations = 0
		self.iterationCooldown = self.activationsToTrigger
		self.triggerTime = self.iterationCooldown
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")
		super().prepare()


	def doCooldownEffect(self):
		self.heal()


	def onItemActivated(self, event):
		self.activations += 1

		if self.activations == self.getP1():
			self.activations = 0
			self.doCooldownEffect()
			self.activate()

			if self.doubleActivationChance > 0 and self.ctx.util.flip(self.doubleActivationChance):
				self.doCooldownEffect()
				self.activate()

			self.showCooldownSmooth(_div(self.activations, self.activationsToTrigger), True)
		else:
			self.showCooldownSmooth(_div(self.activations, self.activationsToTrigger), False)

		self.triggerTime = self.activationsToTrigger - self.activations
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown, None, False, event)











	def _readyInit(self):
		super()._readyInit()
		self.activationsToTrigger = self.getP1()


_R.reg("res://gd_core_items/Goobert.gd", Goobert)
_R.reg("Goobert", Goobert)
_R.reg("Goobert", Goobert)

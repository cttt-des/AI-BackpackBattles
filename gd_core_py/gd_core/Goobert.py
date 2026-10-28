# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Goobert(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core/Goobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self._activations = 0
		self.goobertAnimation = None
		self.activationsToTrigger = None

	@property
	def activations(self):
		return self._activations
	@activations.setter
	def activations(self, v):
		self._activations = int(v)

	def logCooldown(self):
		return True


	def canAffect(self, item):
		return item.canActivate()


	def prepare(self):
		self.activations = 0
		self.iterationCooldown = self.activationsToTrigger
		self.triggerTime = f32(self.iterationCooldown)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")
		super().prepare()


	def doCooldownEffect(self):
		self.heal()


	def onItemActivated(self, event):
		# ★ np25 诊断（受控，双门控零耗链）：Goobert 计数器入口——接收者/计数/
		#   阈值/触发源（对拍 py 侧无 TRIG doCooldownEffect 串扰，run874_r7）。
		_gsrc = "?"
		if event != None and event.origin != None:
			_gsrc = String(event.origin.name)
		self.ctx.rng.trace_diag('GACT', String(self.descriptor.identifier) + '/ot' + str(int(self.ownerType)), str(self.activations + 1) + '/' + str(self.getP1()), 'src=' + _gsrc)
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


_R.reg("res://gd_core/Goobert.gd", Goobert)
_R.reg("Goobert", Goobert)
_R.reg("Goobert", Goobert)

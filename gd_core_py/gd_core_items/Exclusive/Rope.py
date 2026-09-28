# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Rope(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Rope.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedUpItem = None
		self.speedTimer = None
		self.speedPerTrigger = None
		self.maxSpeed = None


	def canAffect(self, item):
		return item.canActivate()


	def canAffect_secondary(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			self.speedUpItem = item

		if self.speedUpItem != None:
			for triggerItem in _iter(self.getAffectedItems()):
				self.connectForCombat(triggerItem, "activated", "onTriggerItemActivated")


	def onTriggerItemActivated(self, event):
		curSpeed = self.ctx.rope_speedups.get(self.speedUpItem, 0.0)
		speedLeft = self.maxSpeed - curSpeed
		if speedLeft > 0:
			self.speedUpItem.addSpeed(min(speedLeft, self.speedPerTrigger))

		self.ctx.util.dictAdd(self.ctx.rope_speedups, self.speedUpItem, self.speedPerTrigger)
		self.speedTimer.start(self.getP_m("dur"))
		self.miniActivate()


	def onSpeedTimeout(self):
		self.ctx.util.dictSub(self.ctx.rope_speedups, self.speedUpItem, self.speedPerTrigger)
		curSpeed = self.ctx.rope_speedups.get(self.speedUpItem, 0.0)
		speedLeft = self.maxSpeed - curSpeed
		if speedLeft > 0:
			self.speedUpItem.reduceSpeed(min(speedLeft, self.speedPerTrigger))


	def onCombatEnd(self):
		self.speedTimer.stop()
		self.speedUpItem = None

	def _readyInit(self):
		super()._readyInit()
		self.speedTimer = self.newItemTimer("SpeedTimer", "onSpeedTimeout", True)
		self.speedPerTrigger = _div(self.getP('speed'), 100.0)
		self.maxSpeed = _div(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Rope.gd", Exclusive__Rope)
_R.reg("Rope", Exclusive__Rope)

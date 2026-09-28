# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Bazooka(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Bazooka.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationsLeft = 0
		self.stunResistActive = False
		self.heatNeeded = None
		self.luck = None
		self.luckNeeded = None
		self.uses = None


	def onPrepare(self):
		self.activationsLeft = self.uses
		self.stunResistActive = False
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if (self.activationsLeft > 0 and 
				self.character().getHeat() >= self.heatNeeded):

				self.activationsLeft -= 1

				self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
				self.useHeat(self.heatNeeded, damageRes.event)
				self.giveLucky(self.luck, damageRes.event)
				self.giveBlock(self.getBlock(), True, damageRes.event)
				self.ctx.bus.flushLoggingQueue()

				self.stun(self.getP_m("dur_stun"), damageRes.event)
				self.character().stun(self.getP_m("dur_stunself"), self, damageRes.event)


	def onLuckChanged(self, amount, event):
		if amount > 0 and not self.stunResistActive and self.character().getLucky() >= self.luckNeeded:
			self.character().changeStunResistance(self.getChance())
			self.stunResistActive = True

		elif amount < 0 and self.stunResistActive and self.character().getLucky() < self.luckNeeded:
			self.character().changeStunResistance( - self.getChance())
			self.stunResistActive = False

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP("heatt"))
		self.luck = int(self.getP("luck"))
		self.luckNeeded = int(self.getP("luckt"))
		self.uses = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/Bazooka.gd", Exclusive__Bazooka)
_R.reg("Bazooka", Exclusive__Bazooka)

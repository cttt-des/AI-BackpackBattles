# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class GingerbreadMan(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/GingerbreadMan.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = 0
		self.heatNeeded = 0
		self.manaNeeded = 0


	def onCombatStart(self):
		self.giveMaxHealth()
		self.activate()


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			if self.character().getHeat() >= self.heatNeeded:
				if self.character().getMana() >= self.manaNeeded:

					self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
					self.useLucky(self.luckNeeded)
					self.useHeat(self.heatNeeded)
					self.useMana(self.manaNeeded)
					self.giveEmpower(self.getP5())
					self.giveRegeneration(self.getP6())
					self.ctx.bus.flushLoggingQueue()

					self.giveMaxHealth(self.getP_m("maxhealth_use"))

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = self.getP2()
		self.heatNeeded = self.getP3()
		self.manaNeeded = self.getP4()


_R.reg("res://gd_core_items/GingerbreadMan.gd", GingerbreadMan)
_R.reg("GingerbreadMan", GingerbreadMan)

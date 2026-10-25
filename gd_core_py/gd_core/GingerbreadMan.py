# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class GingerbreadMan(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core/GingerbreadMan.gd"

	def _init_fields(self):
		super()._init_fields()
		self._luckNeeded = 0
		self._heatNeeded = 0
		self._manaNeeded = 0

	@property
	def luckNeeded(self):
		return self._luckNeeded
	@luckNeeded.setter
	def luckNeeded(self, v):
		self._luckNeeded = int(v)
	@property
	def heatNeeded(self):
		return self._heatNeeded
	@heatNeeded.setter
	def heatNeeded(self, v):
		self._heatNeeded = int(v)
	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)

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


_R.reg("res://gd_core/GingerbreadMan.gd", GingerbreadMan)
_R.reg("GingerbreadMan", GingerbreadMan)

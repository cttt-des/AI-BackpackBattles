# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class EvilCap(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/EvilCap.gd"

	def _init_fields(self):
		super()._init_fields()
		self.nullifyApplied = False
		self.buffsActive = 0
		self.buffTimer = None
		self.activationParticles = None
		self.damReduction = None


	def onPrepare(self):
		self.opponent().reduceHealingEfficiency(_div(self.getP3(), 100.0))
		self.nullifyApplied = False


	def onPreCombatStart(self):
		self.character().changeDamageResistance(self.damReduction)


	def onCombatStart(self):
		if not self.nullifyApplied:
			self.nullifyApplied = True
			self.opponent().changeBuffNullifyChances(self.getChance())

		self.buffTimer.start(self.getP_m("dur"))
		self.buffsActive += 1
		self.setState(self.buffsActive)
		self.activate()


	def buffEnded(self):
		self.character().changeDamageResistance( - self.damReduction)
		self.buffsActive -= 1
		self.setState(self.buffsActive)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.buffsActive = 0
		self.onStateChanged(self.buffsActive)


	def onStateChanged(self, _buffsActive):
		if _buffsActive > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", True)
		self.damReduction = self.getP1()


_R.reg("res://gd_core_items/EvilCap.gd", EvilCap)
_R.reg("EvilCap", EvilCap)

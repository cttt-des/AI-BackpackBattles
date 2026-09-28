# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LeatherHelm(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/LeatherHelm.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffsActive = 0
		self.buffTimer = None
		self.activationParticles = None
		self.damReduction = None


	def getStunProtectChance(self):
		return self.getChance()


	def onPrepare(self):
		self.character().changeCritResistance(self.getChance())
		self.character().changeStunResistance(self.getStunProtectChance())


	def onPreCombatStart(self):

		self.character().changeDamageResistance(self.damReduction)
		self.buffsActive += 1
		self.setState(self.buffsActive)
		self.buffTimer.start(self.getBuffDur())









	def getBuffDur(self):
		return self.getP_m("dur")


	def onCombatStart(self):
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


_R.reg("res://gd_core_items/LeatherHelm.gd", LeatherHelm)
_R.reg("LeatherHelm", LeatherHelm)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Darksaber(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Darksaber.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damPerDebuff = None


	def onPrepare(self):
		self.connectToOpponentDebuffs("onDebuffsChanged")


	def onDebuffsChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.damPerDebuff)


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.getP2())
		if event != None:
			self.inflictBlind(self.getP3(), event)

	def _readyInit(self):
		super()._readyInit()
		self.damPerDebuff = self.getP1()


_R.reg("res://gd_core_items/Darksaber.gd", Darksaber)
_R.reg("Darksaber", Darksaber)

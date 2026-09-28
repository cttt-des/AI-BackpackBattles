# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PoisonIvy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/PoisonIvy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageIncreaseActive = False
		self.activationParticles = None
		self.poisonPerSpike = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")
		self.connectForCombat(self.opponent(), "character_poison_changed", "onOpponentPoisonChanged")





		self.character().changeDebuffResistChances(self.getChance() * self.getNumAffectedItems())



	def onSpikesChanged(self, amount, event):
		if amount > 0:
			self.inflictPoison(amount * self.poisonPerSpike, event)
			self.miniActivate()


	def onOpponentPoisonChanged(self, amount, event):
		curPoison = self.opponent().getPoison()

		if not self.damageIncreaseActive and curPoison >= self.getP1():
			self.opponent().changeDamageResistance( - self.getP2())
			self.setState(True, False, event)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.damageIncreaseActive = active

	def _readyInit(self):
		super()._readyInit()
		self.poisonPerSpike = self.getP4()


_R.reg("res://gd_core_items/PoisonIvy.gd", PoisonIvy)
_R.reg("PoisonIvy", PoisonIvy)

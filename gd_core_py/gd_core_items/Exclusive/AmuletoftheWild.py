# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletoftheWild(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletoftheWild.gd"

	amuletColor = Color(0.470588, 0.952941, 0.2)

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPrepare(self):
		spikesLimit = _div(self.getP('spikedam'), 100.0)
		self.character().changeRangedSpikesLimit(spikesLimit)
		self.character().changeMeleeSpikesLimit(spikesLimit)


	def doCooldownEffect(self):
		self.giveSpikes(self.getP("spikes"))
		for item in _iter(self.getAffectedItems()):
			item.doCooldownEffect()
		self.onAfterEffectFinished()



	def _readyInit(self):
		super()._readyInit()
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletoftheWild.gd", Exclusive__AmuletoftheWild)
_R.reg("AmuletoftheWild", Exclusive__AmuletoftheWild)

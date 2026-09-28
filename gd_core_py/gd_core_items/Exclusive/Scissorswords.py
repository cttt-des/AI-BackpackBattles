# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Scissorswords(_R.C("res://gd_core_items/Lightsaber.gd")):

	resource_path = "res://gd_core_items/Exclusive/Scissorswords.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.bonusDam = None
		self.luck = None
		self.regen = None


	def inflict(self, duration, event):
		super().inflict(duration, event)
		self.giveStacksTemporary(self.character(), _R.C("CoreConst").EventType.Blind, 
			self.blind, duration, event)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.character().getLucky() >= self.luckNeeded:
				event = self.useLucky(self.luckNeeded, damageRes.event)
				self.addBonusDamage(self.bonusDam)
				self.giveRegeneration(self.regen, event)
		else:
			self.giveLucky(self.luck, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.bonusDam = self.getP("dam")
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Scissorswords.gd", Exclusive__Scissorswords)
_R.reg("Scissorswords", Exclusive__Scissorswords)

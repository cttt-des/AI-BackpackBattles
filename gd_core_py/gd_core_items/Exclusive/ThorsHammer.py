# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ThorsHammer(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ThorsHammer.gd"

	def _init_fields(self):
		super()._init_fields()
		self.effectDmgSource = None
		self.manaNeeded = None
		self.effectDmg = None
		self.blind = None


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), damageRes.event)

			if self.character().getMana() >= self.manaNeeded:
				event = self.useMana(self.manaNeeded, damageRes.event)
				self.dealEffectDamage(self.effectDmg, event, self.effectDmgSource)
				duration = self.getP_m("dur_blind")
				self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
					self.blind, duration, event)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.effectDmg = int(self.getP("dam"))
		self.blind = int(self.getP("blind"))
		self.effectDmgSource = _R.C("CoreDamageSource")().init(self, 
			_R.C("CoreDamageSource").Type.Effect, self.effectDmg)



_R.reg("res://gd_core_items/Exclusive/ThorsHammer.gd", Exclusive__ThorsHammer)
_R.reg("ThorsHammer", Exclusive__ThorsHammer)

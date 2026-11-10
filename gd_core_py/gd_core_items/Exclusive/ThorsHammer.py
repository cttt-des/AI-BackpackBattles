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
				self.giveStacksTemporary(self.opponent(), _H_3, 
					self.blind, duration, event)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.effectDmg = int(self.getP("dam"))
		self.blind = int(self.getP("blind"))
		self.effectDmgSource = _H_1().init(self, 
			_H_2, self.effectDmg)



_R.reg("res://gd_core_items/Exclusive/ThorsHammer.gd", Exclusive__ThorsHammer)
_R.reg("ThorsHammer", Exclusive__ThorsHammer)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")
try:
	_H_2 = _R.C("CoreDamageSource").Type.Effect
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

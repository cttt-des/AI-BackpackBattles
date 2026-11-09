# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WandofDissonance(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/WandofDissonance.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthUsed = None
		self.effectDmg = None
		self.availableBuffs = None


	def doCooldownEffect(self):
		if self.character().getCurrentHealth() > self.healthUsed:
			event = self.character().loseHealth(self.healthUsed, self)
			dam = self.descriptor.minDam
			res = self.dealEffectDamage(dam, event)

			maxBuffs = self.getMostStacks(self.character(), list(self.availableBuffs.keys()))
			buffToGive = self.ctx.util.pickRandomElement(maxBuffs)
			amount = self.availableBuffs[buffToGive]
			self.giveStacks(self.character(), buffToGive, amount, event)


		self.activate()


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		bonusEffectDmg = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_H_6):
				bonusEffectDmg += self.effectDmg * 2.0
			else:
				bonusEffectDmg += self.effectDmg

		self.character().changeEffectDamageFactor(bonusEffectDmg)

	def _readyInit(self):
		super()._readyInit()
		self.healthUsed = int(self.getP("healtht"))
		self.effectDmg = _div(self.getP('dam'), 100.0)
		self.availableBuffs = {
		_H_2: int(self.getP("mana")), 
		_H_3: int(self.getP("luck")), 
		_H_4: int(self.getP("regen"))
	}
		self.damageSource = _H_5().setItem(self)



_R.reg("res://gd_core_items/Exclusive/WandofDissonance.gd", Exclusive__WandofDissonance)
_R.reg("WandofDissonance", Exclusive__WandofDissonance)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
_H_5 = _R.C("CoreDamageSource")
try:
    _H_6 = _R.C("CoreConst").Type.Spell
except AttributeError as _he:
    _H_6 = _HoistPending(_he)

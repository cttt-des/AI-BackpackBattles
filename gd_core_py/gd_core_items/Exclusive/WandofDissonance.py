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
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		bonusEffectDmg = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Spell):
				bonusEffectDmg += self.effectDmg * 2.0
			else:
				bonusEffectDmg += self.effectDmg

		self.character().changeEffectDamageFactor(bonusEffectDmg)

	def _readyInit(self):
		super()._readyInit()
		self.healthUsed = int(self.getP("healtht"))
		self.effectDmg = _div(self.getP('dam'), 100.0)
		self.availableBuffs = {
		_R.C("CoreConst").EventType.Mana: int(self.getP("mana")), 
		_R.C("CoreConst").EventType.Lucky: int(self.getP("luck")), 
		_R.C("CoreConst").EventType.Regeneration: int(self.getP("regen"))
	}
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/WandofDissonance.gd", Exclusive__WandofDissonance)
_R.reg("WandofDissonance", Exclusive__WandofDissonance)

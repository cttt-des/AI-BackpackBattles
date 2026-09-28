# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SerpentStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SerpentStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.manaUseEvents = []
		self.manaCost = None
		self.permDamBonus = None
		self.poison = None
		self.damageForPoison = None


	def onPrepare(self):
		self.manaUseEvents.clear()
		self.opponent().changeResistChance(_R.C("CoreConst").EventType.Poison, - self.getChance())


	def onPreDealDamage_early(self, damageRes):
		manaUseEvent = self.tryUseMana(self.manaCost)
		if manaUseEvent != None:
			self.addBonusDamage(self.permDamBonus)
			self.manaUseEvents.append(manaUseEvent)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit() and not (not self.manaUseEvents):
			self.damageAcc += damageRes.damage
			curPoison = _div(self.damageAcc, self.damageForPoison)
			if curPoison > 0:
				self.damageAcc %= self.damageForPoison
				self.inflictPoison(curPoison, damageRes.event)
			self.manaUseEvents.pop()

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP("mana")
		self.permDamBonus = self.getP("dam")
		self.poison = self.getP("poison")
		self.damageForPoison = int(self.getP("damforpoison"))


_R.reg("res://gd_core_items/Exclusive/SerpentStaff.gd", Exclusive__SerpentStaff)
_R.reg("SerpentStaff", Exclusive__SerpentStaff)

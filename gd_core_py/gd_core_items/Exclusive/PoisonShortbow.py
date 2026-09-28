# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoisonShortbow(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoisonShortbow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poison = 0


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			randomDebuff = self.ctx.util.pickRandomElement(_R.C("CoreConst").getDebuffs())
			if randomDebuff == _R.C("CoreConst").EventType.Poison:
				self.inflictPoison(self.poison + 1)
			else:
				self.inflictPoison(self.poison)
				self.giveStacks(self.opponent(), randomDebuff, 1)

	def _readyInit(self):
		super()._readyInit()
		self.poison = self.getP1()


_R.reg("res://gd_core_items/Exclusive/PoisonShortbow.gd", Exclusive__PoisonShortbow)
_R.reg("PoisonShortbow", Exclusive__PoisonShortbow)

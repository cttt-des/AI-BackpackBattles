# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SapphireWhelp(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SapphireWhelp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = None


	def onCombatStart(self):
		self.giveMana(self.getP1())
		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			event = self.tryUseMana(self.getP2())
			if event:
				self.giveBlock(self.getBlock(), True, event)
				self.giveRandomBuffs(1, event, self.stackTypes)

	def _readyInit(self):
		super()._readyInit()
		self.stackTypes = _R.C("CoreConst").getBuffs()
		_erase(self.stackTypes, _R.C("CoreConst").EventType.Mana)



_R.reg("res://gd_core_items/Exclusive/SapphireWhelp.gd", Exclusive__SapphireWhelp)
_R.reg("SapphireWhelp", Exclusive__SapphireWhelp)

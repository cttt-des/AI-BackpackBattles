# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CouragePuppy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/CouragePuppy.gd"


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPreCombatStart(self):
		self.addBonusDamage(self.getP1() * self.getNumAffectedItems())


	def doCooldownEffect(self):
		res = self.dealDamage()
		self.activate(res)

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/CouragePuppy.gd", Exclusive__CouragePuppy)
_R.reg("CouragePuppy", Exclusive__CouragePuppy)

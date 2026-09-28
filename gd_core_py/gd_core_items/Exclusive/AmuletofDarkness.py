# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofDarkness(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofDarkness.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.damageThreshold = None

	amuletColor = Color(0.580392, 0.266667, 0.960784)

	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		self.damageAcc = 0
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onItemActivated(self, event):
		pass

	def onOpponentDamaged(self, damageRes):
		if damageRes.hasHit() and damageRes.damageSource.isEffectDamage():
			self.damageAcc += damageRes.damage

			proccs = _div(self.damageAcc, self.damageThreshold)
			if proccs > 0:
				self.damageAcc %= self.damageThreshold
				self.inflictRandomDebuffs(proccs)
				self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.damageThreshold = int(self.getP("damt"))
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/AmuletofDarkness.gd", Exclusive__AmuletofDarkness)
_R.reg("AmuletofDarkness", Exclusive__AmuletofDarkness)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofFortune(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofFortune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusChance = None
		self.numBuffs = None

	amuletColor = Color(0.266667, 0.960784, 0.667953)

	def canAffect(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusChance(self.bonusChance)


	def doCooldownEffect(self):
		self.giveMostBuffs(self.numBuffs)
		self.onAfterEffectFinished()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 5

	def _readyInit(self):
		super()._readyInit()
		self.bonusChance = self.getP("chance")
		self.numBuffs = int(self.getP("buffs"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofFortune.gd", Exclusive__AmuletofFortune)
_R.reg("AmuletofFortune", Exclusive__AmuletofFortune)

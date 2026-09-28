# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofAlchemy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofAlchemy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.potionsToTrigger = []
		self.potionTriggerTimer = None
		self.delay = None

	amuletColor = Color(0.266667, 0.309804, 0.960784)

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "potion_emptied", "onPotionEmptied")


	def onCombatStart(self):
		self.giveRandomBuffs(self.getP("buffs"))
		self.activate()


	def onPotionEmptied(self, potion):
		if self.rollChance():
			self.potionsToTrigger.append(potion)
			self.potionTriggerTimer.start(self.delay)


	def triggerNextPotion(self):
		potion = self.potionsToTrigger.pop(0)
		potion.triggerPotion()
		potion.miniActivate()
		self.activate()


	def onCombatEnd(self):
		self.potionTriggerTimer.stop()
		self.potionsToTrigger.clear()

	def _readyInit(self):
		super()._readyInit()
		self.potionTriggerTimer = self.newItemTimer("PotionTriggerTimer", "triggerNextPotion", True)
		self.delay = self.getP("delay")
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofAlchemy.gd", Exclusive__AmuletofAlchemy)
_R.reg("AmuletofAlchemy", Exclusive__AmuletofAlchemy)

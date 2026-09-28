# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofSteel(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofSteel.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockAcc = 0
		self.blockForEmpower = None
		self.empowerForBlock = None

	amuletColor = Color(0.34902, 0.415686, 0.45098)

	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		self.blockAcc = 0
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "gave_block", "onItemGaveBlock")


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		empower = _div(self.blockAcc, self.blockForEmpower)
		self.blockAcc %= self.blockForEmpower
		if empower > 0:
			self.giveEmpower(empower * self.empowerForBlock, event)
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.blockForEmpower = int(self.getP("blockt"))
		self.empowerForBlock = int(self.getP("empower"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofSteel.gd", Exclusive__AmuletofSteel)
_R.reg("AmuletofSteel", Exclusive__AmuletofSteel)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ManaOrb_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/ManaOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = []
		self.activated = False
		self._bonusBuffs = 0
		self.mana = None
		self._manaNeeded = 0
		self.buffs = None
		self.light = None

	@property
	def bonusBuffs(self):
		return self._bonusBuffs
	@bonusBuffs.setter
	def bonusBuffs(self, v):
		self._bonusBuffs = int(v)
	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)

	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		# ★ np25 evt105 f09 面 AFFL 探针（双门控零耗链）：ManaOrb 连接集定谳——
		#   夹具 affected=(5,3),(5,5),(7,3),(7,5)，gd 漏连 (7,5) Piggybank
		#   （BUS activated 0 listeners 铁证）。打印逐格命中与受影响物品集。
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			_cells = self.getAffectedCellsInInventory()
			_hit = ""
			for _c in _iter(_cells):
				_it = self.getOwnOrPlayerInventory().getItemInCell(_c)
				_hit += '[' + str(_c) + '=' + ('null' if _it == None else String(_it.descriptor.identifier) + '/ot' + str(int(_it.ownerType)) + ' p' + str(int(_it.placed))) + ']'
			_aff = self.getAffectedItems()
			_aff_names = ""
			for _a in _iter(_aff):
				_aff_names += String(_a.descriptor.identifier) + ","
			self.ctx.rng.trace_diag('AFFL', String(self.descriptor.identifier) + '/ot' + str(int(self.ownerType)), str(_cells), _hit + ' aff=' + _aff_names)
		self.bonusBuffs = 0
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onItemActivated(self, event):
		if self.rollChance():
			self.miniActivate()
			self.giveMana(self.mana)


	def onManaChanged(self, amount, triggerEvent):
		if not self.activated and amount > 0 and self.character().getMana() >= self.manaNeeded:
			self.setState(True)
			event = self.useMana(self.manaNeeded, triggerEvent)
			self.giveRandomBuffs(self.buffs + self.bonusBuffs, event, self.stackTypes)
			self.activate()



	def onShopEntered(self):
		self.onStateChanged(False)


	def addBonusRandomBuffs(self, amount):
		self.bonusBuffs += amount


	def onStateChanged(self, _activated):
		self.activated = _activated

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP1())
		self.manaNeeded = self.getP2()
		self.buffs = int(self.getP3())
		self.stackTypes = _R.C("CoreConst").getBuffs()
		_erase(self.stackTypes, _R.C("CoreConst").EventType.Mana)



_R.reg("res://gd_core_items/ManaOrb.gd", ManaOrb_2)
_R.reg("ManaOrb", ManaOrb_2)

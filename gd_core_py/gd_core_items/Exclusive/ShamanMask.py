# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShamanMask(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShamanMask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.runes = ["Badger Rune", "Elephant Rune", "Hawk Rune"]
		self._luckNeeded = 0

	@property
	def luckNeeded(self):
		return self._luckNeeded
	@luckNeeded.setter
	def luckNeeded(self, v):
		self._luckNeeded = int(v)

	def onCombatStart(self):
		# ★ 诊断标记（不消耗链）：幸运计数的逐物品宝石明细
		if self.ctx.rng.oracle_trace:
			detail = []
			for it in _iter(self.inventory.items):
				detail.append(String(it.descriptor.identifier) + "=" +
						str(len(it.getGemsNoNull())))
			self.ctx.rng.oracle_trace_log.append([len(self.ctx.rng.oracle_trace_log),
					"GEMS", str(self.inventory.countSocketedGems()),
					_join(PoolStringArray(detail), ","), "", ""])
		self.giveLucky(self.inventory.countSocketedGems())


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			self.giveRandomBuffs(self.getP3(), event)
		self.activate()


	def getGatedDescriptor(self, rarity):
		return self.ctx.item_book.getDescriptor(self.ctx.util.pickRandomElement(self.runes))



	def getRelatedItemHeight(self):
		return 90

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = self.getP2()
		if not self.pooled:
			self.runes.append("Tiger Rune")



_R.reg("res://gd_core_items/Exclusive/ShamanMask.gd", Exclusive__ShamanMask)
_R.reg("ShamanMask", Exclusive__ShamanMask)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BookofNature(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BookofNature.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regenNeeded = None
		self.lucky = None
		self.spikes = None
		self.spellSpeed = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		speed = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_H_2):
				speed += self.spellSpeed * 2
			else:
				speed += self.spellSpeed
		self.addSpeed(speed)


	def doCooldownEffect(self):
		if self.character().getRegeneration() >= self.regenNeeded:
			event = self.useRegeneration(self.regenNeeded)
			self.giveLucky(self.lucky, event)
			self.giveSpikes(self.spikes, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP("regen"))
		self.lucky = int(self.getP("luck"))
		self.spikes = int(self.getP("spikes"))
		self.spellSpeed = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/BookofNature.gd", Exclusive__BookofNature)
_R.reg("BookofNature", Exclusive__BookofNature)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Spell
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

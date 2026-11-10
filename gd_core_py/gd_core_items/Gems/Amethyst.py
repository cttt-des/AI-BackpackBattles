# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Amethyst(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Amethyst.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healReduction = None
		self.buffRemoval = None

	gemColor = Color(1.977344, 0.8, 3)

	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(1)
		self.activate()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.removeRandomBuffs(self.buffRemoval, damageRes.event)
			self.miniActivate()


	def prepareArmor(self):
		self.opponent().reduceHealingEfficiency(self.getGemPower() * self.healReduction)


	def getBaseDescription(self, wrapInColor=True):
		if self.getRarity() == _H_1:
			return self.insertParameters(self.ctx.util.tra("Perfect Amethyst_DESCR"), wrapInColor)
		else:
			return super().getBaseDescription(wrapInColor)

	def _readyInit(self):
		super()._readyInit()
		self.healReduction = _div(self.getP1(), 100.0)
		self.buffRemoval = int(self.getP2())


_R.reg("res://gd_core_items/Gems/Amethyst.gd", Gems__Amethyst)
_R.reg("Amethyst", Gems__Amethyst)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Godly
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

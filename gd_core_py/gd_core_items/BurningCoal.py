# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BurningCoal_2(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/BurningCoal.gd"

	gemColor = Color(1.5, 1, 0.7)

	def canBlock(self):
		return False


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_early", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			damageRes.damage += self.getP1()
			self.giveHeat(self.getP2())
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeResistStacks(_H_1, round(self.getP3() * self.getGemPower()))


	def combatStartArmor(self):
		self.giveBlock(self.getBlock() * self.getGemPower())
		self.miniActivate()


	def doCooldownEffect(self):
		self.giveHeat(self.getP4())
		self.cleanseRandomDebuffs(self.getP5())
		self.onAfterEffectFinished()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BurningCoal.gd", BurningCoal_2)
_R.reg("BurningCoal", BurningCoal_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
    _H_1 = _HoistPending(_he)

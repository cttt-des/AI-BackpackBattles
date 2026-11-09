# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HawkRune(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Exclusive/HawkRune.gd"

	gemColor = Color(0.267323, 0.624508, 0.970703)

	def prepareWeapon(self):
		self.getItem().addCritChancePercent(self.getP("critchance"))
		self.getItem().addCritSeverity(_div(self.getP('critdam'), 100.0))


	def prepareArmor(self):
		self.character().changeResistChance(_H_1, 
			self.getGemPower() * self.getChance())


	def doCooldownEffect(self):
		self.inflictBlind(1)
		self.activate()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/HawkRune.gd", Exclusive__HawkRune)
_R.reg("HawkRune", Exclusive__HawkRune)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
    _H_1 = _HoistPending(_he)

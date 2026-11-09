# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DeerTotem(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DeerTotem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.normalTex = None


	def canAffect(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.setState(False)
		self.character().changeDamageResistance(self.getP1())

		numNatureItems = self.getNumAffectedItems()
		self.character().addBattleRageDuration(self.getP_m("dur_rage") * numNatureItems)

		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def onBattleRageStarted(self, _event):
		self.setState(True)
		self.activateCooldown()


	def onBattleRageEnded(self, _event):
		self.setState(False)
		self.deactivateCooldown()


	def doCooldownEffect(self):
		self.heal()
		self.giveMana(self.getP4())

		self.activate()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass


	def getTriggerPriority(self):
		return _H_1

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DeerTotem.gd", Exclusive__DeerTotem)
_R.reg("DeerTotem", Exclusive__DeerTotem)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Priority.Highest
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
    _H_2 = _HoistPending(_he)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DarkLantern(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DarkLantern.gd"

	def _init_fields(self):
		super()._init_fields()
		self.deathPrevented = False
		self.normalSprite = None
		self.invuTimer = None
		self.lanternLight = None


	def canAffect(self, item):
		return item.hasType(_H_2)


	def canAffect_secondary(self, item):
		return item.hasType(_H_3)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "reincarnated", "onReincarnate")


	def onDamaged(self, _damage, event):
		if self.deathPrevented:
			return

		if self.character().getCurrentHealth() <= 0:
			self.setState(True)
			duration = self.getP_m("dur_invu")
			self.invuTimer.start(duration)
			self.character().makeInvulnerable(duration, self, event)
			healAmount = round(_div(self.getP2(), 100.0) * self.character().getMaxHealth())
			event2 = self.character().reincarnate(healAmount, False, self, event)

			self.activate()


	def onCombatStart(self):
		self.character().loseHealth(_div(self.getP1(), 100.0) * self.character().getMaxHealth(), self)


		self.activate()


	def onReincarnate(self, event):
		dam = self.getMinDamage() * self.getNumAffected_type(_H_2)
		if dam > 0:
			damageRes = self.dealEffectDamage(dam, event)

		numDebuffs = self.getP5() * self.getNumAffectedItems(_H_5)
		self.inflictRandomDebuffs(numDebuffs, event)




	def invuEnded(self):
		pass



	def onCombatEnd(self):
		self.invuTimer.stop()



	def getTriggerPriority(self):
		return _H_1


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _deathPrevented):
		self.deathPrevented = _deathPrevented
		if self.deathPrevented:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.invuTimer = self.newItemTimer("InvuTimer", "invuEnded", False)

		self.damageSource = _H_4().setItem(self)



_R.reg("res://gd_core_items/Exclusive/DarkLantern.gd", Exclusive__DarkLantern)
_R.reg("DarkLantern", Exclusive__DarkLantern)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
_H_4 = _R.C("CoreDamageSource")
try:
    _H_5 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_5 = _HoistPending(_he)

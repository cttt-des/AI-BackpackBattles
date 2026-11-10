# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WaterElemental(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/WaterElemental.gd"

	def _init_fields(self):
		super()._init_fields()
		self._manaUsed = 0
		self.activeEffects = 0
		self.coldParticles = None
		self.distortion = None
		self.manaOnHit = None
		self.bonusManaOnHit = None
		self.iceSpeed = None
		self.bonusDam = None
		self.coldOnHit = None
		self.manaNeeded1 = None
		self.manaNeeded2 = None
		self.manaNeeded3 = None

	@property
	def manaUsed(self):
		return self._manaUsed
	@manaUsed.setter
	def manaUsed(self, v):
		self._manaUsed = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def canAffect_secondary(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")
		self.manaUsed = 0
		self.addSpeed(self.iceSpeed * self.getNumAffectedItems(_H_5))
		self.activeEffects = 0
		self.setState(self.activeEffects)


	def onManaChanged(self, amount, event):
		if (amount < 0 and 
			event.type == _H_4 and 
			event.getParam("used", False)):

			self.manaUsed += abs(amount)

			before = self.activeEffects

			if self.activeEffects == 0 and self.manaUsed >= self.manaNeeded1:
				self.activeEffects = 1

			if self.activeEffects == 1 and self.manaUsed >= self.manaNeeded2:
				self.activeEffects = 2
				self.addBonusDamage(self.bonusDam)

			if self.activeEffects == 2 and self.manaUsed >= self.manaNeeded3:
				self.activeEffects = 3

			if before != self.activeEffects:
				self.setState(self.activeEffects)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			mana = self.manaOnHit
			chance = self.getChance() * self.getNumAffectedItems()
			if self.rollChance(chance):
				mana += self.bonusManaOnHit
			self.giveMana(mana, damageRes.event)

			if self.activeEffects >= 1:
				self.heal(self.getP_m("heal"), damageRes.event)
			if self.activeEffects == 3:
				self.inflictCold(self.coldOnHit, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _activeEffects):
		_activeEffects = int(_activeEffects)
		self.activeEffects = _activeEffects
		if self.activeEffects == 3:
			pass
		else:
			pass



	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		colors = [self.ctx.util.triggerColor, self.ctx.util.triggerColor, self.ctx.util.triggerColor]

		if self.placed:
			for i in (self.activeEffects if self.activeEffects.__class__ is list else _iter(self.activeEffects)):
				colors[i] = self.ctx.util.modifiedColor

		descr = self.getModeDescription(descr, colors, False, wrapInColor)
		return descr


	def playPickupSound(self):
		# decomp Items/Exclusive/WaterElemental.gd:101 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/WaterElemental.gd:105 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.manaOnHit = int(self.getP("mana"))
		self.bonusManaOnHit = int(self.getP("mana2"))
		self.iceSpeed = _div(self.getP('speed'), 100.0)
		self.bonusDam = self.getP("dam")
		self.coldOnHit = int(self.getP("cold"))
		self.manaNeeded1 = int(self.getP("manat1"))
		self.manaNeeded2 = int(self.getP("manat2"))
		self.manaNeeded3 = int(self.getP("manat3"))
		if self.ownerType == _H_3:
			pass
		else:
			pass



_R.reg("res://gd_core_items/Exclusive/WaterElemental.gd", Exclusive__WaterElemental)
_R.reg("WaterElemental", Exclusive__WaterElemental)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Owner.GridStorage
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_5 = _HoistPending(_he)

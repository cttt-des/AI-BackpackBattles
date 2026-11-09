# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Automanaton(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Automanaton.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.manaNeeded = None
		self.blind = None
		self.numDebuffs = None
		self.dmgReductionTimer = None
		self.healthThreshold = None
		self.bonusSpeed = None
		self.damReduction = None


	def canAffect(self, item):
		return item.hasCooldown() or item.gainsStack(_H_2)


	def onPrepare(self):
		self.updateShaderRotation()
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDealtDamage(self, damageRes):
		if (damageRes.hasHit() and 
			self.character().getMana() >= self.manaNeeded):

			event = self.useMana(self.manaNeeded, damageRes.event)
			duration = self.getP_m("dur_blind")
			self.giveStacksTemporary(self.opponent(), _H_3, 
				self.blind, duration, event)

			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), event)

			self.cleanseRandomDebuffs(self.numDebuffs, event)


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.bonusSpeed)
				item.changeAmplificiationChancePercent(_H_4, self.getChance2())

			self.dmgReductionTimer.start(self.getP_m("dur_dmgreduction"))
			self.character().changeDamageResistance(self.damReduction)

			self.giveBlock(self.getBlock(), True, event)



	def getTriggerPriority(self):
		return _H_1 + 2


	def onDmgReductionTimerTimeout(self):
		self.character().changeDamageResistance( - self.damReduction)


	def onCombatEnd(self):
		self.dmgReductionTimer.stop()


	def showCooldown(self, progress):

		progress = self.rotateProgress(progress * 1.0 + 0.05)


	def clearSpriteMaterial(self):
		pass


	def giveProgressMaterial(self):
		pass


	def updateShaderRotation(self):
		super().updateShaderRotation()

	def getTextureSize(self):
		return Vector2.ZERO

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.blind = int(self.getP("blind"))
		self.numDebuffs = int(self.getP("cleanse"))
		self.dmgReductionTimer = self.newItemTimer("DmgReductionTimer", "onDmgReductionTimerTimeout", False)
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0) - 0.0001
		self.bonusSpeed = _div__loc(self.getP('speed'), 100.0)
		self.damReduction = self.getP("dmgreduction")
		pass



_R.reg("res://gd_core_items/Exclusive/Automanaton.gd", Exclusive__Automanaton)
_R.reg("Automanaton", Exclusive__Automanaton)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Stack.Mana
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
    _H_4 = _HoistPending(_he)

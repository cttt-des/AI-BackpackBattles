# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self._usedBuffs = 0
		self.buffsNeeded = None
		self.numPotions = None
		self.buffsPerStaff = None
		self.manaPerBook = None
		self.staminaPerBook = None

	@property
	def usedBuffs(self):
		return self._usedBuffs
	@usedBuffs.setter
	def usedBuffs(self, v):
		self._usedBuffs = int(v)

	def canAffect_global(self, item):
		return item.hasType(_H_7) and item != self


	def getAffectedCellsAfterRotate_primary(self, rotatedCells):
		if self.faceDirection == _H_1:
			return [rotatedCells[1] + Vector2.UP]
		else:
			return [rotatedCells[0] + Vector2.UP]


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_2
		return color == _H_5 or color == _H_6


	def canAffect_secondary(self, item):
		return item.hasType(_H_3)


	def canAffect_tertiary(self, item):
		return item.hasTag(_H_4)


	def onTriggerPotion(self, event=None):

		_iter__loc = _iter
		allPotions = []
		for item in _iter__loc(self.inventory.getItems()):
			if self.canAffect_global(item):
				allPotions.append(item)
		self.ctx.rng.shuffleEngine(allPotions, 'Exclusive/RainbowPotion.gd:37')







		potionsToTrigger = []
		for potion in (allPotions if allPotions.__class__ is list else _iter__loc(allPotions)):
			typeExists = False
			for triggeredPotion in (potionsToTrigger if potionsToTrigger.__class__ is list else _iter__loc(potionsToTrigger)):
				if potion.isA(triggeredPotion.descriptor):
					typeExists = True
					break
			if typeExists:
				continue
			potionsToTrigger.append(potion)
			if len(potionsToTrigger) == self.numPotions:
				break

		for potion in (potionsToTrigger if potionsToTrigger.__class__ is list else _iter__loc(potionsToTrigger)):

			potion.triggerPotion(event)



	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffsChanged")
		self.usedBuffs = 0


	def onCombatStart(self):
		books = self.getNumDistinctAffectedItems(_H_5)
		if books > 0:
			self.giveMana(books * self.manaPerBook)
			self.giveMaxStaminaTemporary(books * self.staminaPerBook)

		staffs = self.getNumDistinctAffectedItems(_H_6)
		if staffs > 0:
			self.giveRandomBuffs(self.buffsPerStaff * staffs)


		self.activate(None, False, False, None, False)


	def onBuffsChanged(self, amount, event):
		if self.isEmpty():
			return

		if amount < 0 and event.getParam("used", False):

			self.usedBuffs += int(abs(amount))
			if self.usedBuffs > self.buffsNeeded:
				self.consumePotion(event)


	def getGatedDescriptor(self, _rarity):
		return None

	def getStarPosition(self):
		return Vector2.ZERO

	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 3


	def getRelatedItemHeight(self):
		return 250

	def _readyInit(self):
		super()._readyInit()
		self.buffsNeeded = int(self.getP("buffst"))
		self.numPotions = int(self.getP("potions"))
		self.buffsPerStaff = int(self.getP("buffs"))
		self.manaPerBook = int(self.getP("mana"))
		self.staminaPerBook = int(self.getP("stamina"))


_R.reg("res://gd_core_items/Exclusive/RainbowPotion.gd", Exclusive__RainbowPotion)
_R.reg("RainbowPotion", Exclusive__RainbowPotion)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Book
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Tag.Staff
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C("CoreConst").Affected.Tertiary
except AttributeError as _he:
    _H_6 = _HoistPending(_he)
try:
    _H_7 = _R.C("CoreConst").Type.Potion
except AttributeError as _he:
    _H_7 = _HoistPending(_he)

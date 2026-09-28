# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedBuffs = 0
		self.buffsNeeded = None
		self.numPotions = None
		self.buffsPerStaff = None
		self.manaPerBook = None
		self.staminaPerBook = None


	def canAffect_global(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion) and item != self


	def getAffectedCellsAfterRotate_primary(self, rotatedCells):
		if self.faceDirection == _R.C("CoreConst").FaceDirection.LEFT:
			return [rotatedCells[1] + Vector2.UP]
		else:
			return [rotatedCells[0] + Vector2.UP]


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return color == _R.C("CoreConst").Affected.Secondary or color == _R.C("CoreConst").Affected.Tertiary


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Book)


	def canAffect_tertiary(self, item):
		return item.hasTag(_R.C("CoreConst").Tag.Staff)


	def onTriggerPotion(self, event=None):

		allPotions = []
		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				allPotions.append(item)
		_shuffle(allPotions)







		potionsToTrigger = []
		for potion in _iter(allPotions):
			typeExists = False
			for triggeredPotion in _iter(potionsToTrigger):
				if potion.isA(triggeredPotion.descriptor):
					typeExists = True
					break
			if typeExists:
				continue
			potionsToTrigger.append(potion)
			if len(potionsToTrigger) == self.numPotions:
				break

		for potion in _iter(potionsToTrigger):

			potion.triggerPotion(event)



	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffsChanged")
		self.usedBuffs = 0


	def onCombatStart(self):
		books = self.getNumDistinctAffectedItems(_R.C("CoreConst").Affected.Secondary)
		if books > 0:
			self.giveMana(books * self.manaPerBook)
			self.giveMaxStaminaTemporary(books * self.staminaPerBook)

		staffs = self.getNumDistinctAffectedItems(_R.C("CoreConst").Affected.Tertiary)
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

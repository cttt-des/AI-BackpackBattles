# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Card(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Card.gd"

	def _init_fields(self):
		super()._init_fields()
		self.back = None
		self.activeFront = None
		self.curActivationDelay = 0.0
		self.faceUp = True
		self.activating = False
		self.chainPosition = - 1
		self.deck = None
		self.cardAnimation = None
		self.front = None
		self.connector = None
		self.notInChainMark = None


	def setFaceUp(self):
		if not self.faceUp:
			self.faceUp = True


	def setFaceDown(self):
		if self.faceUp:
			self.faceUp = False


	def updateTexture(self):
		if self.faceUp:
			if self.deck and self.activeFront and self.cardSecondaryEffectActive():
				pass
			else:
				pass
		else:
			pass


	def cardSecondaryEffectActive(self):
		return False


	def canAffect(self, item):
		if self.placed:
			return (self.deck and 
				item.hasType(_R.C("CoreConst").Type.Card) and 
				(item.chainPosition > self.chainPosition or item.chainPosition == - 1))
		else:
			return item.hasType(_R.C("CoreConst").Type.Card) and not item.deck


	def prepare(self):
		super().prepare()
		self.setState(False)


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def getNextCard(self):


		affected = self.getItemsInAffectedCells_cached()
		if not (not affected) and affected[0].hasType(_R.C("CoreConst").Type.Card):
			return affected[0]
		else:
			return None


	def startActivation(self):
		if self.activating or self.faceUp:
			return

		self.activating = True
		self.iterationCooldown = self.getCooldown()
		self.triggerTime = self.iterationCooldown
		self.activateCooldown()
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)



	def playActivationAnimation(self, aniType=GD_DEFAULT, consume=False):
		if aniType is GD_DEFAULT:
			aniType = self.descriptor.activationAni
		pass



	def onStateChanged(self, _faceUp):
		if _faceUp:

			if self.faceUp:
				pass
			else:
				pass
		else:
			if self.faceUp:
				pass

		self.faceUp = _faceUp


	def doRevealEffect(self):
		pass


	def trigger(self):
		self.activating = False
		self.showCooldown(0)
		nextCard = self.getNextCard()
		if nextCard:
			nextCard.startActivation()

		self.triggerTime = self.iterationCooldown

		self.setState(True, True)
		self.deactivateCooldown()
		self.doRevealEffect()




	def combatEnd(self):
		super().combatEnd()
		self.activating = False


	def shopEntered(self, craft):
		super().shopEntered(craft)
		self.setFaceUp()


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)


	def onRemoveFromInventory(self):
		self.deck = None
		self.updateTexture()



	def notifyChainPosition(self, _deck, _chainPos, chainLength):
		self.chainPosition = _chainPos

		if self.chainPosition == - 1:
			self.deck = None
			if self.placed:
				pass
		else:
			self.deck = _deck

			if self.chainPosition != chainLength - 1:
				pass
			else:
				pass

		self.updateTexture()



	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		return self.getCardDescription(descr)


	def getCardDescription(self, descr):
		if self.deck:
			descr += "\n\n" + self.insertParameter(self.ctx.util.tra("CARD_COUNT"), "num", self.chainPosition, _R.C("CoreConst").StatModified.No, False)
		elif self.placed:
			descr += "\n\n" + self.ctx.util.wrapInColor(self.ctx.util.tra("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Card.gd", Card)
_R.reg("Card", Card)
_R.reg("Card", Card)

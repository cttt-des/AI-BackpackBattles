# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DeckofCards(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/DeckofCards.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cards = []
		self.cardActivations = 0
		self.chainStarted = False
		self.connector = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Card)


	def onAddToInventory(self):
		self.updateCards()


	def onRemoveFromInventory(self):
		self.resetChain()


	def resetChain(self):
		for card in _iter(self.cards):
			card.notifyChainPosition(self, - 1, len(self.cards))
		self.cards.clear()



	def countDuplicates(self, untilCardIndex):
		descriptors = []
		for i in _iter(untilCardIndex):
			descriptors.append(self.cards[i].descriptor)
		return self.ctx.util.countDuplicates(descriptors)


	def updateCards(self):
		self.resetChain()
		affected = self.getAffectedItems()
		if not (not affected):
			self.cards.append(affected[0])

			nextCard = self.cards[0].getNextCard()
			while (nextCard and not nextCard in self.cards):
				self.cards.append(nextCard)
				nextCard = nextCard.getNextCard()
		else:
			pass

		chainLength = len(self.cards)

		for i in _iter(chainLength):
			self.cards[i].notifyChainPosition(self, i, chainLength)


	def onItemAdded(self, item):
		super().onItemAdded(item)
		if isinstance(item, _R.C("Card")):
			self.updateCards()


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		if isinstance(item, _R.C("Card")):
			self.updateCards()


	def onPrepare(self):
		self.chainStarted = False


	def onCombatStart(self):
		self.giveLucky(self.getP1())
		if not self.chainStarted:
			self.chainStarted = True
			self.cardActivations = 0
			if not (not self.cards):

				self.ctx.defer(self.cards[0], "startActivation", [])
		self.activate()


	def notifyActivation(self):
		self.cardActivations += 1


	def getGatedDescriptor(self, rarity):
		return None

	def getRelatedItemColumns(self):
		return 4


	def getRelatedItemHeight(self):
		return 120

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/DeckofCards.gd", DeckofCards)
_R.reg("DeckofCards", DeckofCards)

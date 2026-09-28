# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Joker(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/Exclusive/Joker.gd"

	def _init_fields(self):
		super()._init_fields()
		self.quads = 0
		self.triplets = 0
		self.pairs = 0
		self.activationParticles = None
		self.staminaReduction = None
		self.revealsPerQuad = None


	def countChain(self):
		self.quads = 0
		self.triplets = 0
		self.pairs = 0

		if self.chainPosition > 0:
			counter = Dictionary()
			for i in _iter(self.chainPosition):
				self.ctx.util.dictAdd(counter, self.deck.cards[i].descriptor)

			for cardType in _iter(counter):
				self.quads += _div(counter[cardType], 4)
				rest = _mod(counter[cardType], 4)
				self.triplets += _div(rest, 3)
				rest = _mod(rest, 3)
				self.pairs += _div(rest, 2)


	def notifyChainPosition(self, _deck, _chainPos, chainLength):
		super().notifyChainPosition(_deck, _chainPos, chainLength)
		self.countChain()


	def doRevealEffect(self):
		self.giveRandomBuffs(self.getP("buffs"))
		if self.pairs > 0:
			self.character().gainCritResistStacks(self.pairs)

		if self.triplets > 0:
			for item in _iter(self.inventory.getItems()):

				item.changeStaminaFactor( - self.staminaReduction * self.triplets)

		if self.quads > 0:
			legitCards = []
			for i in _iter(self.chainPosition):
				if self.deck.cards[i].descriptor != self.descriptor:
					legitCards.append(self.deck.cards[i])


			for i in _iter(self.quads * self.revealsPerQuad):
				if not (not legitCards):
					revealedCard = self.ctx.util.pickRandomElement(legitCards)
					revealedCard.doRevealEffect()
					if len(legitCards) > 1:
						_erase(legitCards, revealedCard)

		self.activate()


	def getCardDescription(self, descr):
		if self.deck:
			counterText = self.ctx.util.tra("Joker_COUNTER")
			state = _R.C("CoreConst").StatModified.No
			if self.pairs > 0:
				state = _R.C("CoreConst").StatModified.Positive
			else:
				state = _R.C("CoreConst").StatModified.Negative
			counterText = self.insertParameter(counterText, "pairs", self.pairs, state, False)

			if self.triplets > 0:
				state = _R.C("CoreConst").StatModified.Positive
			else:
				state = _R.C("CoreConst").StatModified.Negative
			counterText = self.insertParameter(counterText, "triplets", self.triplets, state, False)

			if self.quads > 0:
				state = _R.C("CoreConst").StatModified.Positive
			else:
				state = _R.C("CoreConst").StatModified.Negative
			counterText = self.insertParameter(counterText, "quadruples", self.quads, state, False)

			descr += "\n" + counterText

		elif self.placed:
			descr += "\n" + self.ctx.util.wrapInColor(tr("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		self.staminaReduction = self.getP("stamina")
		self.revealsPerQuad = int(self.getP("cards"))


_R.reg("res://gd_core_items/Exclusive/Joker.gd", Exclusive__Joker)
_R.reg("Joker", Exclusive__Joker)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShinyMantle(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShinyMantle.gd"

	def _init_fields(self):
		super()._init_fields()
		self.invuProcced = 0
		self.gemDurFactor = 0.0
		self.manaNeeded = None
		self.activationParticles = None
		self.buffTimer = None
		self.blind = None
		self.manaNeeded_base = None
		self.manaCostIncrease = None
		self.maxUses = None


	def canAffect(self, item):
		return not item.isBag()


	def readyToFuse(self):
		return not (not self.bondedIngredients)


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def getCounterValue(self):
		gold = 0
		inv = self.inventory if self.placed else self.ctx.player.INVENTORY
		for item in _iter(inv.getItemsAndGems()):
			if item.isGem():
				gold += item.getPrice()

		if self.dragged:
			for gem in _iter(self.getGemsNoNull()):
				gold += gem.getPrice()

		return gold


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_invulnerable_start", "onInvuStarted")



		self.manaNeeded = self.manaNeeded_base
		self.invuProcced = 0
		self.gemDurFactor = floor(_div(self.getCounterValue(), self.getP('gold')))
		self.setState(False)




	def doCooldownEffect(self):
		if self.character().isVulnerable() and self.character().getMana() >= self.manaNeeded:
			self.setState(True)
			self.invuProcced += 1
			invuDur = self.getP_m("dur_base") + self.getP_m("dur_bonus") * self.gemDurFactor
			self.buffTimer.start(invuDur)
			event = self.character().makeInvulnerable(invuDur, self)
			self.useMana(self.manaNeeded, event)
			self.manaNeeded += self.manaCostIncrease

			if self.invuProcced == self.maxUses:
				self.onAfterEffectFinished()
				return

		self.activate()






	def onInvuStarted(self, event):
		self.inflictBlind(self.blind, event)










	def onStateChanged(self, invuActive):
		if invuActive:
			pass
		else:
			pass


	def buffEnded(self):
		self.setState(False)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))
		self.manaNeeded_base = int(self.getP("manat"))
		self.manaCostIncrease = int(self.getP("mana"))
		self.maxUses = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/ShinyMantle.gd", Exclusive__ShinyMantle)
_R.reg("ShinyMantle", Exclusive__ShinyMantle)

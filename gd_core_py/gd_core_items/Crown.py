# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Crown(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Crown.gd"

	CrownState = EnumDict("CrownState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self.crownState = 0
		self.activationParticles = None
		self.buffTimer = None
		self.manaCost = None
		self.light = None


	def onPrepare(self):
		self.setState(self.CrownState.Inactive)
		self.connectForCombat(self.character(), "character_mana_changed", "checkTrigger")
		self.connectForCombat(self.character(), "character_invulnerable_end", "onInvuEnded")


	def onInvuEnded(self, triggerEvent):
		self.checkTrigger(0, triggerEvent)


	def checkTrigger(self, _amount, triggerEvent):
		if (self.crownState == self.CrownState.Inactive and 
			self.character().isVulnerable() and 
			self.checkMana(self.manaCost)):

			self.setState(self.CrownState.Active, True)
			invuDur = self.getP_m("dur_invu")
			event = self.character().makeInvulnerable(invuDur, self, triggerEvent)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, event)
			self.activate()


	def buffEnded(self):
		self.setState(self.CrownState.Used, True)


	def doCooldownEffect(self):
		self.cleanseBlind(1)
		self.heal()
		self.activate()


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.CrownState.Inactive)


	def onStateChanged(self, _crownState):
		if _crownState == self.CrownState.Inactive:
			pass

		elif _crownState == self.CrownState.Active:
			pass

		else:
			pass

		self.crownState = _crownState

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.manaCost = self.getP("mana")


_R.reg("res://gd_core_items/Crown.gd", Crown)
_R.reg("Crown", Crown)

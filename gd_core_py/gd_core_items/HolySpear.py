# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HolySpear(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/HolySpear.gd"

	SpearState = EnumDict("SpearState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self.blockRemoval = 0
		self.cleanses = 0
		self.spearState = 0
		self.activationParticles = None
		self.buffTimer = None
		self.blockRemovalPerSlot = 0
		self.buffedSpeed = None
		self.manaCost = 0
		self.light = None


	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		numSlots = self.getNumEmptyAffectedCells() + self.getNumAffectedItems()
		self.blockRemoval = self.blockRemovalPerSlot * numSlots
		self.cleanses = numSlots

		self.setState(self.SpearState.Inactive)
		self.connectForCombat(self.character(), "character_mana_changed", "checkTrigger")
		self.connectForCombat(self.character(), "character_invulnerable_end", "onInvuEnded")


	def onPreDealDamage_late(self, damageRes):
		if damageRes.hasHit():
			self.removeBlock(self.blockRemoval)
			self.cleanseRandomDebuffs(self.cleanses)


	def onInvuEnded(self, triggerEvent):
		self.checkTrigger(0, triggerEvent)


	def checkTrigger(self, _amount, triggerEvent):
		if (self.spearState == self.SpearState.Inactive and 
			self.character().isVulnerable() and 
			self.checkMana(self.manaCost)):

			self.setState(self.SpearState.Active, True)
			invuDur = self.getP_m("dur_invu")
			self.character().makeInvulnerable(invuDur, self, triggerEvent)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, triggerEvent)
			self.addSpeed(_div(self.buffedSpeed, 100.0))



	def buffEnded(self):
		self.setState(self.SpearState.Used, True)
		self.reduceSpeed(_div(self.buffedSpeed, 100.0))


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.SpearState.Inactive)


	def onStateChanged(self, _spearState):
		if _spearState == self.SpearState.Inactive:
			pass

		elif _spearState == self.SpearState.Active:
			pass

		else:
			pass

		self.spearState = _spearState


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.Normal + 2

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blockRemovalPerSlot = self.getP1()
		self.buffedSpeed = self.getP3()
		self.manaCost = self.getP2()


_R.reg("res://gd_core_items/HolySpear.gd", HolySpear)
_R.reg("HolySpear", HolySpear)

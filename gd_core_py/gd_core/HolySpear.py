# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HolySpear(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core/HolySpear.gd"

	SpearState = EnumDict("SpearState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self._blockRemoval = 0
		self._cleanses = 0
		self._spearState = 0
		self.activationParticles = None
		self.buffTimer = None
		self._blockRemovalPerSlot = 0
		self.buffedSpeed = None
		self._manaCost = 0
		self.light = None

	@property
	def blockRemoval(self):
		return self._blockRemoval
	@blockRemoval.setter
	def blockRemoval(self, v):
		self._blockRemoval = int(v)
	@property
	def cleanses(self):
		return self._cleanses
	@cleanses.setter
	def cleanses(self, v):
		self._cleanses = int(v)
	@property
	def spearState(self):
		return self._spearState
	@spearState.setter
	def spearState(self, v):
		self._spearState = int(v)
	@property
	def blockRemovalPerSlot(self):
		return self._blockRemovalPerSlot
	@blockRemovalPerSlot.setter
	def blockRemovalPerSlot(self, v):
		self._blockRemovalPerSlot = int(v)
	@property
	def manaCost(self):
		return self._manaCost
	@manaCost.setter
	def manaCost(self, v):
		self._manaCost = int(v)

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


_R.reg("res://gd_core/HolySpear.gd", HolySpear)
_R.reg("HolySpear", HolySpear)

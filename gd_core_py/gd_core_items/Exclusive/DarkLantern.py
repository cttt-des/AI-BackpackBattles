# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DarkLantern(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DarkLantern.gd"

	def _init_fields(self):
		super()._init_fields()
		self.deathPrevented = False
		self.normalSprite = None
		self.invuTimer = None
		self.lanternLight = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Fire)


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "reincarnated", "onReincarnate")


	def onDamaged(self, _damage, event):
		if self.deathPrevented:
			return

		if self.character().getCurrentHealth() <= 0:
			self.setState(True)
			duration = self.getP_m("dur_invu")
			self.invuTimer.start(duration)
			self.character().makeInvulnerable(duration, self, event)
			healAmount = round(_div(self.getP2(), 100.0) * self.character().getMaxHealth())
			event2 = self.character().reincarnate(healAmount, False, self, event)

			self.activate()


	def onCombatStart(self):
		self.character().loseHealth(_div(self.getP1(), 100.0) * self.character().getMaxHealth(), self)


		self.activate()


	def onReincarnate(self, event):
		dam = self.getMinDamage() * self.getNumAffected_type(_R.C("CoreConst").Type.Fire)
		if dam > 0:
			damageRes = self.dealEffectDamage(dam, event)

		numDebuffs = self.getP5() * self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary)
		self.inflictRandomDebuffs(numDebuffs, event)




	def invuEnded(self):
		pass



	def onCombatEnd(self):
		self.invuTimer.stop()



	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _deathPrevented):
		self.deathPrevented = _deathPrevented
		if self.deathPrevented:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.invuTimer = self.newItemTimer("InvuTimer", "invuEnded", False)

		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/DarkLantern.gd", Exclusive__DarkLantern)
_R.reg("DarkLantern", Exclusive__DarkLantern)

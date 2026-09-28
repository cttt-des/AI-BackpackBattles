# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Phoenix(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Phoenix.gd"

	def _init_fields(self):
		super()._init_fields()
		self.ashSprite = None
		self.deathPrevented = False
		self.normalSprite = None
		self.selfDam = 0
		self.reincarnateHealth = 0


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.deathPrevented:
			return

		if self.character().getCurrentHealth() <= 0:
			heat = self.character().getHeat()
			if heat > 0:
				self.setState(True)

				event2 = self.character().reincarnate(self.reincarnateHealth * heat, False, self, event)
				self.useHeat(heat, event2)
				self.activate()


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			if self.character().getCurrentHealth() > self.selfDam:
				self.character().loseHealth(self.selfDam, self)
				res = self.dealDamage()
				self.activate(res)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _deathPrevented):
		if _deathPrevented:
			pass
		else:
			pass
		self.deathPrevented = _deathPrevented

	def _readyInit(self):
		super()._readyInit()
		self.selfDam = self.getP("selfdam")
		self.reincarnateHealth = self.getP("reincarnate_health")


_R.reg("res://gd_core_items/Exclusive/Phoenix.gd", Exclusive__Phoenix)
_R.reg("Phoenix", Exclusive__Phoenix)

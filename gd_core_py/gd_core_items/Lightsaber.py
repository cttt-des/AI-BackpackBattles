# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Lightsaber(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Lightsaber.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blindingLightTimer = None
		self.activationParticles = None
		self.regenNeeded = None
		self.blind = None
		self.damPerBlind = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "blinding_light_ended", "onBlindingLightEnded")
		self.connectForCombat(self.opponent(), "character_blind_changed", "onOpponentBlindChanged")
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")


	def inflict(self, duration, event):
		self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
				self.blind, duration, event)


	def onRegenChanged(self, amount, triggerEvent):
		if amount < 0:
			return

		if not self.character().blindingLightActive and self.character().getRegeneration() >= self.regenNeeded:

			self.setState(True, True)
			self.character().startBlindingLight()
			event = self.useRegeneration(self.regenNeeded, triggerEvent)
			duration = self.getP_m("dur_blind")
			self.inflict(duration, event)

			self.activate(None, False)
			self.blindingLightTimer.start(duration)


	def onOpponentBlindChanged(self, amount, event):
		self.changeVaryingDamage(self.damPerBlind * amount)


	def onCombatEnd(self):
		self.blindingLightTimer.stop()


	def onBlindingLightTimeout(self):
		self.setState(False)


		self.ctx.util.callNextFrame(self.character(), "endBlindingLight")


	def onBlindingLightEnded(self, event):
		self.onRegenChanged(0, event)



	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.blindingLightTimer = self.newItemTimer("BlindingLightTimer", "onBlindingLightTimeout", False)
		self.regenNeeded = int(self.getP("regent"))
		self.blind = int(self.getP("blind"))
		self.damPerBlind = self.getP("dam_blind")


_R.reg("res://gd_core_items/Lightsaber.gd", Lightsaber)
_R.reg("Lightsaber", Lightsaber)

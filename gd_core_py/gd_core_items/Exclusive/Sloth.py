# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Sloth(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Sloth.gd"

	def _init_fields(self):
		super()._init_fields()
		self.awakenNow = False
		self.speed_v = None
		self.buffs = None
		self.buffsAmulet = None
		self.light1 = None
		self.light2 = None
		self.particles1 = None
		self.particles2 = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.speed_v)


	def onCombatStart(self):
		m = self.getP_m("maxhealth_base")
		m += self.getNumAffectedItems() * self.getP_m("maxhealth_item")
		m = round(_div(m, 100.0) * self.character().getMaxHealth())
		self.giveMaxHealth(m)
		self.activate()


	def trigger(self):
		self.awakenNow = True
		super().trigger()


	def doCooldownEffect(self):
		if self.awakenNow:
			self.setState(True)
			self.giveAllBuffs(self.buffs)
			self.stun(self.getP_m("dur_stun"))
			self.awakenNow = False
			self.onAfterEffectFinished()
		else:
			self.giveAllBuffs(self.buffsAmulet)
			self.stun(self.getP_m("dur_stun_amulet"))
			self.activate()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, awakened):
		if awakened:
			pass
		else:
			pass


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		descr = descr.replace("$s[", "[shake]")
		descr = descr.replace('$s]', '[/shake]')
		return descr


	def _readyInit(self):
		super()._readyInit()
		self.speed_v = _div(self.getP('speed'), 100.0)
		self.buffs = int(self.getP("buffs"))
		self.buffsAmulet = int(self.getP("buffs_amulet"))


_R.reg("res://gd_core_items/Exclusive/Sloth.gd", Exclusive__Sloth)
_R.reg("Sloth", Exclusive__Sloth)

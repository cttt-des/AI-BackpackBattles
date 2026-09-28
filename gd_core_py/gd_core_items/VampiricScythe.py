# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class VampiricScythe(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/VampiricScythe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.lastSpeedBonus = 0.0


	def canAffect(self, item):
		return item.gainsStack(_R.C("CoreConst").Stack.Vampirism)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Vampirism, 1)
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")


	def onVampirismChanged(self, _amount, _event):
		scytheSpeedBonus = min(self.getP1() * self.character().getVampirism(), self.getP2())
		scytheSpeedBonus /= 100.0
		self.addSpeed(scytheSpeedBonus - self.lastSpeedBonus)
		self.lastSpeedBonus = scytheSpeedBonus


	def onShopEntered(self):
		self.lastSpeedBonus = 0.0

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/VampiricScythe.gd", VampiricScythe)
_R.reg("VampiricScythe", VampiricScythe)

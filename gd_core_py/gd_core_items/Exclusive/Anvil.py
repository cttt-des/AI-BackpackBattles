# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Anvil(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Anvil.gd"


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)


	def onRemoveFromInventory(self):
		pass

	def onCraft(self, _itemDescriptor):
		pass

	def canAffect(self, item):
		return item.isCrafted()


	def canAffect_secondary(self, item):
		return item.isWeapon()


	def onPreCombatStart(self):
		numCrafted = len(self.getAffectedItems())
		if numCrafted > 0:
			bonusDamage = self.getP1() * numCrafted
			staminaReduction = - self.getP2() * numCrafted
			for affectedWeapon in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
				if affectedWeapon.canBeEmpowered():
					affectedWeapon.addBonusDamage(bonusDamage)
					event = self.ctx.combat_log.createEvent_DamageBuff(self, affectedWeapon, bonusDamage, self.character().playerId)
					self.ctx.bus.logEvent(event)

				affectedWeapon.changeStaminaFactor(staminaReduction)
		self.activate()


	def getRelatedItems(self):
		return [self.ctx.item_book.getDescriptor("Flame")]

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Anvil.gd", Exclusive__Anvil)
_R.reg("Anvil", Exclusive__Anvil)

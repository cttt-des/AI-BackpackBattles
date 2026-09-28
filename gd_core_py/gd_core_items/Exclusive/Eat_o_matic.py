# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Eat_o_matic(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Eat-o-matic.gd"

	ArmState = EnumDict("ArmState", {"Off": 0, "Slow": 1, "Fast": 2})



	def _init_fields(self):
		super()._init_fields()
		self.affectedFood = None
		self.otherFood = []
		self.armTween = None
		self.armState = 0
		self.foodSpeed = None
		self.chargedSpeed = None
		self.otherSpeed = None
		self.arm = None
		self.armAnimation = None

	SLOW_SPEED = 0.2
	FAST_SPEED = 1.0

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def canAffect_global(self, item):
		if not item.hasType(_R.C("CoreConst").Type.Food):
			return False
		if item in self.currentAffectedItems[_R.C("CoreConst").Affected.Primary]:
			return False

		return True


	def onPrepare(self):
		self.setState(self.ArmState.Off)
		self.affectedFood = self.getFirstAffectedItem()
		if self.affectedFood != None:
			self.affectedFood.addSpeed(self.foodSpeed)

		self.otherFood.clear()
		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item) and item != self.affectedFood:
				self.otherFood.append(item)



	def combatStart(self):
		super().combatStart()
		if self.armState != self.ArmState.Fast:
			self.setState(self.ArmState.Slow)


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(self.ArmState.Fast)
			if self.affectedFood != None:
				self.affectedFood.addSpeed(self.chargedSpeed - self.foodSpeed)
			for food in _iter(self.otherFood):
				food.addSpeed(self.otherSpeed)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(self.ArmState.Slow)
			if self.affectedFood != None:
				self.affectedFood.reduceSpeed(self.chargedSpeed - self.foodSpeed)
			for food in _iter(self.otherFood):
				food.reduceSpeed(self.otherSpeed)


	def onCombatEnd(self):
		self.setState(self.ArmState.Off)


	def onShopEntered(self):
		self.onStateChanged(self.ArmState.Off)


	def stopArmAni(self):
		pass


	def onStateChanged(self, _armState):
		self.armState = _armState
		if self.armState == self.ArmState.Off:
			pass


		else:

			if self.armState == self.ArmState.Slow:
				pass
			else:
				pass



	def _readyInit(self):
		super()._readyInit()
		self.foodSpeed = _div(self.getP('speed'), 100.0)
		self.chargedSpeed = _div(self.getP('speed2'), 100.0)
		self.otherSpeed = _div(self.getP('speed3'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Eat-o-matic.gd", Exclusive__Eat_o_matic)
_R.reg("Eat-o-matic", Exclusive__Eat_o_matic)

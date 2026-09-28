# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RatChef(_R.C("res://gd_core_items/Exclusive/Rat.gd")):

	resource_path = "res://gd_core_items/Exclusive/RatChef.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stamina = None
		self.empower = None


	def initRat(self):
		pass


	def onCombatStart(self):
		numAffectedFood = 0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Food):
				numAffectedFood += 1

		self.giveRegeneration(numAffectedFood)


	def doCooldownEffect(self):
		self.giveStamina(self.stamina)
		self.giveEmpower(self.empower)
		self.activate()


	def getCraftingOffset(self, forDirection):
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2(0, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2(1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2( - 1, 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2(0, 0)

	def _readyInit(self):
		super()._readyInit()
		self.stamina = self.getP("stamina")
		self.empower = self.getP("empower")


_R.reg("res://gd_core_items/Exclusive/RatChef.gd", Exclusive__RatChef)
_R.reg("RatChef", Exclusive__RatChef)

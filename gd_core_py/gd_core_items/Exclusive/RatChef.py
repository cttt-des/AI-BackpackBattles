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
			if item.hasType(_H_2):
				numAffectedFood += 1

		self.giveRegeneration(numAffectedFood)


	def doCooldownEffect(self):
		self.giveStamina(self.stamina)
		self.giveEmpower(self.empower)
		self.activate()


	def getCraftingOffset(self, forDirection):
		if forDirection == _H_1:
				return Vector2(0, - 1)
		elif forDirection == _H_3:
				return Vector2(1, 0)
		elif forDirection == _H_4:
				return Vector2( - 1, 1)
		elif forDirection == _H_5:
				return Vector2(0, 0)

	def _readyInit(self):
		super()._readyInit()
		self.stamina = self.getP("stamina")
		self.empower = self.getP("empower")


_R.reg("res://gd_core_items/Exclusive/RatChef.gd", Exclusive__RatChef)
_R.reg("RatChef", Exclusive__RatChef)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").FaceDirection.DOWN
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").FaceDirection.RIGHT
except AttributeError as _he:
    _H_5 = _HoistPending(_he)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Pandamonium(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core/Pandamonium.gd"


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onFoodActivated")

		self.opponent().changePoisonCritChancePercent(self.getNumAffectedItems() * self.getChance())


	def onFoodActivated(self, event):

		self.inflictPoison(self.getP1())


	def getCraftingOffset(self, forDirection):
		if forDirection == _H_2:
				return Vector2( - 1, 1)
		elif forDirection == _H_3:
				return Vector2.ZERO
		elif forDirection == _H_4:
				return Vector2(1, 0)
		elif forDirection == _H_5:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core/Pandamonium.gd", Pandamonium)
_R.reg("Pandamonium", Pandamonium)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").FaceDirection.UP
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

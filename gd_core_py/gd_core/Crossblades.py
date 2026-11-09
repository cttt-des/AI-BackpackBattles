# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Crossblades(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core/Crossblades.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems(_H_2)):
			item.addBonusDamage(self.getP1())

		for item in _iter(self.getAffectedItems(_H_3)):
			item.addSpeed(_div(self.getP2(), 100.0))

		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.getP3())
			self.addSpeed(_div(self.getP4(), 100.0))


	def getCraftingOffset(self, forDirection):
		if forDirection == _H_1:
				return Vector2( - 1, 0)
		elif forDirection == _H_4:
				return Vector2( - 1, 0)
		elif forDirection == _H_5:
				return Vector2(0, - 1)
		elif forDirection == _H_6:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core/Crossblades.gd", Crossblades)
_R.reg("Crossblades", Crossblades)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").FaceDirection.DOWN
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C("CoreConst").FaceDirection.RIGHT
except AttributeError as _he:
    _H_6 = _HoistPending(_he)

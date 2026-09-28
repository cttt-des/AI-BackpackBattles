# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Crossblades(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Crossblades.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Primary)):
			item.addBonusDamage(self.getP1())

		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			item.addSpeed(_div(self.getP2(), 100.0))

		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.getP3())
			self.addSpeed(_div(self.getP4(), 100.0))


	def getCraftingOffset(self, forDirection):
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2(0, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Crossblades.gd", Crossblades)
_R.reg("Crossblades", Crossblades)

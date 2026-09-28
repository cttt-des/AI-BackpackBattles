# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HeroLongsword(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/HeroLongsword.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.getP1())
		self.activate(None, False)


	def getCraftingOffset(self, forDirection):
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2(0, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2.ZERO
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/HeroLongsword.gd", HeroLongsword)
_R.reg("HeroLongsword", HeroLongsword)

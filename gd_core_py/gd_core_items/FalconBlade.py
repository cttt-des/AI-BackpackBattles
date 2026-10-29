# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class FalconBlade_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/FalconBlade.gd"


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(_div(self.getP1(), 100))

		self.activate(None, False)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			res = self.dealDamage()
			self.activate(res, False)
			res2 = self.dealDamage()
			self.activate(res2, False)
			hits = 0
			if res.hasHit():
				hits += 1
			if res2.hasHit():
				hits += 1

			if hits == 2:
				pass
			elif hits == 1:
				pass
			else:
				pass

			# ★ RNG 链消耗还原（r2_1）：decomp Items/FalconBlade.gd:24-25 createAnimation()+ani.randomizePosition() ——
			#   ItemAnimation.gd:26-28 恒抽 3 次（(30,100)/5.0 export 默认；直调不经 intialize 无 playback_speed）。
			#   run631_r9/701_r11/722_r7 逐抽对位实证 + 台账第 24 轮 run634 同根。
			self.ctx.rng.randf_range( - 30.0, 30.0)
			self.ctx.rng.randf_range( - 100.0, 100.0)
			self.ctx.rng.randf_range( - 5.0, 5.0)


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


_R.reg("res://gd_core_items/FalconBlade.gd", FalconBlade_2)
_R.reg("FalconBlade", FalconBlade_2)

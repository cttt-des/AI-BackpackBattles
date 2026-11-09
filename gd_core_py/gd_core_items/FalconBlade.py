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
		if self.useStamina() == _H_1:
			res = self.dealDamage()
			self.activate(res, False)
			res2 = self.dealDamage()
			self.activate(res2, False)
			hits = 0
			if res.hasHit():
				hits += 1
			if res2.hasHit():
				hits += 1

			# ★ np29fI（同 RubyChonk 定谳）：原版攻击尾 createAnimation+randomize
			#   Position（Item.gd:5336/Animations/ItemAnimation.gd:26-28）= 3 笔
			#   Util.rng 裸抽不入账；内核此前整块剥离 → 每双击缺 6 步。
			self.ctx.rng.bare_randf_range(-30.0, 30.0)
			self.ctx.rng.bare_randf_range(-100.0, 100.0)
			self.ctx.rng.bare_randf_range(-5.0, 5.0)


	def getCraftingOffset(self, forDirection):
		if forDirection == _H_2:
				return Vector2(0, - 1)
		elif forDirection == _H_3:
				return Vector2.ZERO
		elif forDirection == _H_4:
				return Vector2( - 1, 0)
		elif forDirection == _H_5:
				return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/FalconBlade.gd", FalconBlade_2)
_R.reg("FalconBlade", FalconBlade_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").StaminaResult.Sufficient
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

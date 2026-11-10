# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RubyChonk_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/RubyChonk.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatThresholdReached = False
		self.hasStunned = False
		self.activationParticles = None
		self.heatThreshold = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if not self.heatThresholdReached:
			if self.character().getHeat() >= self.heatThreshold:
				self.setState(True, False, event)
		elif self.character().getHeat() < self.heatThreshold:
			self.setState(False, False, event)


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			self.hasStunned = False
			res = self.dealDamage()
			if self.hasStunned:
				self.activate(res, False, False, self.ActivationAni.Tackle)
			else:
				self.activate(res, False)
			# ★ np29fI（run1514_r18 fd@36 定谳）：原版攻击尾的攻击动画块在此处照常
			#   消耗主链——`var ani = createAnimation(); ani.randomizePosition()`
			#   （Item.gd:5336-5353 + Animations/ItemAnimation.gd:26-28）：
			#   createAnimation=ObjectPool.instance（零抽）+ randomizePosition=
			#   Util.rng.randf_range ×3 **裸调不入账**（rng_log 零痕迹，与 np24
			#   ItemAnimation 同款）。内核此前整块剥离 → 每攻击缺 3 抽；另有尾随
			#   1 抽（PCG 解算 oracle 在 randomizePosition 与下一拍 adjustCooldown
			#   之间恒多 2 步，调用点未名——数值不入事件流，仅链位推进）。3 笔合计
			#   6 步/攻击（IRND 探针态==row218 post 实证；playback_speed 属 intialize、
			#   RC 走 createAnimation+randomizePosition 直调不含它）。实证：run1514 oracle 在 RC 攻击#1 激活音与攻击#2
			#   adjustCooldown 之间恰多 8 步（状态前向解算 adv0→adv8），gd trace
			#   同窗 0 抽（ANIMDBG pc=False as=True——RC 的 activate(res,false)
			#   playCombatAni 闸本来就不走 ANIM 块，块在 doCooldownEffect 尾）。
			self.ctx.rng.bare_randf_range(-30.0, 30.0)
			self.ctx.rng.bare_randf_range(-100.0, 100.0)
			self.ctx.rng.bare_randf_range(-5.0, 5.0)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.giveHeat(1, damageRes.event)
			if self.heatThresholdReached:
				if self.rollChance():
					self.stun(self.getP_m("dur_stun"), damageRes.event)
					self.hasStunned = True


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _heatThresholdReached):
		if _heatThresholdReached:
			pass
		else:
			pass

		self.heatThresholdReached = _heatThresholdReached


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
		self.heatThreshold = int(self.getP1())


_R.reg("res://gd_core_items/RubyChonk.gd", RubyChonk_2)
_R.reg("RubyChonk", RubyChonk_2)


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

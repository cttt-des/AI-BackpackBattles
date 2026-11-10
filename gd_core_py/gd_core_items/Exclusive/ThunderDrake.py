# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ThunderDrake(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ThunderDrake.gd"

	def _init_fields(self):
		super()._init_fields()
		self.active = False
		self._curHitCount = 0
		self.lightningMultiplicity = {}
		self.numHits = None
		self.buffSpeed = None
		self.buffTimer = None
		self.buffParticles = None

	@property
	def curHitCount(self):
		return self._curHitCount
	@curHitCount.setter
	def curHitCount(self, v):
		self._curHitCount = int(v)

	def canAffect_lightning(self, item):
		return item.hasCooldown() or item.reactsToCharges()


	def onPrepare(self):
		self.setState(False)
		self.curHitCount = 0
		self.lightningMultiplicity = self.countItemsInAffectedCells_cached(_H_1)


	def onDealtDamage(self, damageRes):
		_iter__loc = _iter
		if damageRes.hasHit():
			self.curHitCount += 1

			if self.curHitCount == self.numHits:


				if self.active:
					for item in _iter__loc(self.getAffectedItems(_H_1)):
						item.chargeLeft(self)
						self.zapItem(item)
				else:
					self.setState(True)
					for item in _iter__loc(self.getAffectedItems(_H_1)):
						item.addSpeed(self.buffSpeed * self.lightningMultiplicity[item])
						self.zapItem(item)

				self.buffTimer.stop()
				self.buffTimer.start(self.getP_m("dur"))
				self.curHitCount = 0


	def zapItem(self, item):
		item.chargeReceived(self)
		if item.hasOnChargeReceivedEffect:
			# ★ np27 破案（EVENT state 哨兵+GCOIL/ZDBG 双桩，run1102_r13）：原版此处
			#   ObjectPool.instance(Util.zapScene)+zap.zap(...) → Zap.gd:32 的
			#   randf_range(4.0,4.02)（1 抽=2 步）——转写剥表现层时把 rng 消耗一并
			#   剥掉：oracle 偷1(Coil×2 层 106) 后 zap 2 步（-8602→7014，PCG 全链
			#   自洽）→ 偷2 pick(2,1)；gd 无 zap → 偷2 pick(3,0) → 偷栈类型分叉
			#   （语料 106/105/104 v gd 106/106/101）。补消耗（表现层照剥）。
			self.ctx.rng.randf_range(4.0, 4.02)
			targetPos = item.getGlobalCenter()


	def onBuffEnded(self):
		self.setState(False)

		for item in _iter(self.getAffectedItems(_H_1)):
			item.reduceSpeed(self.buffSpeed * self.lightningMultiplicity[item])
			item.chargeLeft(self)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, chargeActive):
		self.active = chargeActive
		if chargeActive:
			pass
		else:
			pass


	def getCraftingOffset(self, forDirection):
		if forDirection == _H_2:
				return Vector2( - 1, - 1)
		elif forDirection == _H_3:
				return Vector2.ZERO
		elif forDirection == _H_4:
				return Vector2( - 1, 0)
		elif forDirection == _H_5:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		self.numHits = int(self.getP("hits"))
		self.buffSpeed = _div(self.getP('speed'), 100.0)
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffEnded", False)


_R.reg("res://gd_core_items/Exclusive/ThunderDrake.gd", Exclusive__ThunderDrake)
_R.reg("ThunderDrake", Exclusive__ThunderDrake)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Lightning
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

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
		self.lightningMultiplicity = self.countItemsInAffectedCells_cached(_R.C("CoreConst").Affected.Lightning)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.curHitCount += 1

			if self.curHitCount == self.numHits:


				if self.active:
					for item in _iter(self._lightningOrdered()):
						item.chargeLeft(self)
						self.zapItem(item)
				else:
					self.setState(True)
					for item in _iter(self._lightningOrdered()):
						item.addSpeed(self.buffSpeed * self.lightningMultiplicity[item])
						self.zapItem(item)

				self.buffTimer.stop()
				self.buffTimer.start(self.getP_m("dur"))
				self.curHitCount = 0


	# ★ np31W2：TD 的 Lightning 受影响循环序=tile_data 静态涂色序（x 分组升、
	#   组内 y 降）——1097 fAffC oracle 实测；TD 是全场唯一 Lightning 色遍历者，
	#   局部排序副本零全局风险（全局按色分曾致 -62 退步已回滚 9c447568）。
	def _lightningOrdered(self):
		arr = self.getAffectedItems(_R.C("CoreConst").Affected.Lightning)
		_sort_custom(arr, _R.C("CoreUtil"), "vec2_tile_data")
		return arr


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

		for item in _iter(self._lightningOrdered()):
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
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2( - 1, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2.ZERO
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		self.numHits = int(self.getP("hits"))
		self.buffSpeed = _div(self.getP('speed'), 100.0)
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffEnded", False)


_R.reg("res://gd_core_items/Exclusive/ThunderDrake.gd", Exclusive__ThunderDrake)
_R.reg("ThunderDrake", Exclusive__ThunderDrake)

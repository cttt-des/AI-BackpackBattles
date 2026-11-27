# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _has_behavior_cache_get,
    _has_behavior_cache_put,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__TeslaCoil" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__TeslaCoil





class Exclusive__TeslaCoil(_base_cls_Exclusive__TeslaCoil):

	resource_path = "res://gd_core_items/Exclusive/TeslaCoil.gd"

	def _init_fields(self):
		super()._init_fields()
		self.itemsToAdvance = []
		self.numCollectedCharges = 0
		self.advanceItemCounter = 0
		self.collectCharges = True
		self.cdAdvance = None
		self.salesChance = None
		self.engineerWeight = None
		self.chargeCounter = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(0)
		self.collectCharges = True
		self.numCollectedCharges = 0
		self.advanceItemCounter = 0
		self.itemsToAdvance = _dup(self.getAffectedItems())
		self.ctx.rng.shuffleEngine(self.itemsToAdvance, 'Exclusive/TeslaCoil.gd:26')

		otherItems = []
		for item in _iter(self.inventory.getItems()):
			if item != self and not item in self.itemsToAdvance:
				if item.hasCooldown():
					otherItems.append(item)

		self.ctx.rng.shuffleEngine(otherItems, 'Exclusive/TeslaCoil.gd:34')
		self.itemsToAdvance.extend(otherItems)


	def onChargeReceived(self, _charge):
		if self.collectCharges:
			self.numCollectedCharges += 1
			self.setState(self.numCollectedCharges)
			self.miniActivate()
		else:
			self.advanceItem()


	def doCooldownEffect(self):
		self.collectCharges = False
		for i in (self.numCollectedCharges if self.numCollectedCharges.__class__ is list else _iter(self.numCollectedCharges)):
			self.advanceItem()

		self.onStateChanged(None)
		done = (len(self.itemsToAdvance) < self.advanceItemCounter + 1)
		self.onAfterEffectFinished(done)
		if not done:
			self.activate()


	def advanceItem(self):
		while True:
			if len(self.itemsToAdvance) < self.advanceItemCounter + 1:
				return

			item = self.itemsToAdvance[self.advanceItemCounter]
			self.advanceItemCounter += 1

			if item.isCooldownActive():
				item.advanceCooldownSeconds(self.cdAdvance)
				# ★ np33（EATI 双侧对拍定谳，同 np27 zapItem 剥抽同构）：原版此处
				#   ObjectPool.instance(Util.zapScene)+zap.zap(...) → Zap.gd:32
				#   randf_range(4.0,4.02)=2 步——转写剥表现层时把 rng 消耗一并剥掉
				#   （隐形 +2/次）。补消耗（表现层照剥）。
				self.ctx.rng.randf_range(4.0, 4.02)


				if len(self.itemsToAdvance) < self.advanceItemCounter + 1:
					self.consumed = True

				self.miniActivate()
				return


	def onStateChanged(self, _numCollectedCharges):
		if _numCollectedCharges == None:
			pass
		else:
			pass


	def onShopEntered(self):
		self.onStateChanged(None)


	def onSaleRoll(self, item):
		pass

	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("cdadvance")
		self.salesChance = _div(self.getP('sales'), 100.0)
		self.engineerWeight = self.getP("weight")
		pass



_R.reg("res://gd_core_items/Exclusive/TeslaCoil.gd", Exclusive__TeslaCoil)
_R.reg("TeslaCoil", Exclusive__TeslaCoil)

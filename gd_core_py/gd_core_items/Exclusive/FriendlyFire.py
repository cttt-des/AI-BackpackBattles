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
if "_base_cls_Exclusive__FriendlyFire" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__FriendlyFire





class Exclusive__FriendlyFire(_base_cls_Exclusive__FriendlyFire):

	resource_path = "res://gd_core_items/Exclusive/FriendlyFire.gd"

	def _init_fields(self):
		super()._init_fields()
		self._maxHeatReached = 0
		self._manaNeeded = 0
		self._threshold1 = 0
		self._threshold2 = 0
		self._threshold3 = 0

	@property
	def maxHeatReached(self):
		return self._maxHeatReached
	@maxHeatReached.setter
	def maxHeatReached(self, v):
		self._maxHeatReached = int(v)
	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)
	@property
	def threshold1(self):
		return self._threshold1
	@threshold1.setter
	def threshold1(self, v):
		self._threshold1 = int(v)
	@property
	def threshold2(self):
		return self._threshold2
	@threshold2.setter
	def threshold2(self, v):
		self._threshold2 = int(v)
	@property
	def threshold3(self):
		return self._threshold3
	@threshold3.setter
	def threshold3(self, v):
		self._threshold3 = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffected_type(_H_3) * self.getP3(), 100.0))
		self.maxHeatReached = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, _amount, event):
		newMaxHeat = max(self.maxHeatReached, self.character().getHeat())
		if newMaxHeat >= self.threshold3 and self.maxHeatReached < self.threshold3:
			self.maxHeatReached = newMaxHeat
			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam, event)
			self.activate()
		elif newMaxHeat >= self.threshold2 and self.maxHeatReached < self.threshold2:
			self.maxHeatReached = newMaxHeat
			self.giveRegeneration(self.getP7(), event)
			self.activate()
		elif newMaxHeat >= self.threshold1 and self.maxHeatReached < self.threshold1:
			self.maxHeatReached = newMaxHeat
			self.giveLucky(self.getP5(), event)
			self.activate()



	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			self.useMana(self.manaNeeded)
			self.giveHeat(self.getP2())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = self.getP1()
		self.threshold1 = self.getP4()
		self.threshold2 = self.getP6()
		self.threshold3 = self.getP8()
		self.damageSource = _H_2().setItem(self)



_R.reg("res://gd_core_items/Exclusive/FriendlyFire.gd", Exclusive__FriendlyFire)
_R.reg("FriendlyFire", Exclusive__FriendlyFire)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreDamageSource")
try:
	_H_3 = _R.C('CoreConst').Type.Fire
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

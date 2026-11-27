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
if "_base_cls_Exclusive__Coil" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Coil





class Exclusive__Coil(_base_cls_Exclusive__Coil):

	resource_path = "res://gd_core_items/Exclusive/Coil.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.numBuffs = None
		self.maxActivations = None

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)

	def onPrepare(self):
		self.numActivations = 0


	def onChargeReceived(self, _charge):
		if self.numActivations < self.maxActivations:
			self.numActivations += 1
			self.stealRandomBuff(self.numBuffs)
			if self.numActivations == self.maxActivations:
				self.consumed = True
			self.miniActivate()


































	def _readyInit(self):
		super()._readyInit()
		self.numBuffs = int(self.getP("buffs"))
		self.maxActivations = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/Coil.gd", Exclusive__Coil)
_R.reg("Coil", Exclusive__Coil)

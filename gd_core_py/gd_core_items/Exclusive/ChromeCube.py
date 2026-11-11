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
if "_base_cls_Exclusive__ChromeCube" not in globals():
	from .Cube import Cube as _base_cls_Exclusive__ChromeCube





class Exclusive__ChromeCube(_base_cls_Exclusive__ChromeCube):

	resource_path = "res://gd_core_items/Exclusive/ChromeCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.healthThreshold = None
		self.healReduction = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.hasActivated = False
		self.affectedItem = self.getFirstAffectedItem()
		self.connectForCombat(self.opponent(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.opponent().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			if self.affectedItem != None:
				self.advanceAffectedItem()

			self.opponent().reduceHealingEfficiency(self.healReduction)
			self.consume()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0) - 0.0001
		self.healReduction = _div__loc(self.getP('healreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ChromeCube.gd", Exclusive__ChromeCube)
_R.reg("ChromeCube", Exclusive__ChromeCube)

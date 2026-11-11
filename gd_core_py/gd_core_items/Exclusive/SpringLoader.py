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
if "_base_cls_Exclusive__SpringLoader" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SpringLoader





class Exclusive__SpringLoader(_base_cls_Exclusive__SpringLoader):

	resource_path = "res://gd_core_items/Exclusive/SpringLoader.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speed1 = None
		self.speed2 = None
		self.cdAdvance = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.speed1)


	def doCooldownEffect(self):
		self.deactivateCooldown()

		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.speed1 + self.speed2)
			item.advanceCooldownSeconds(self.cdAdvance)

		self.onAfterEffectFinished()


	def getTextureSize(self):
		return Vector2.ZERO

	def getSpriteOffset(self):
		return Vector2.ZERO

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speed1 = _div__loc(self.getP('speed'), 100.0)
		self.speed2 = _div__loc(self.getP('speed2'), 100.0)
		self.cdAdvance = self.getP("cdadvance")


_R.reg("res://gd_core_items/Exclusive/SpringLoader.gd", Exclusive__SpringLoader)
_R.reg("SpringLoader", Exclusive__SpringLoader)

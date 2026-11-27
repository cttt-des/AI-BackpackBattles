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
if "_base_cls_Exclusive__Everburning" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Everburning





class Exclusive__Everburning(_base_cls_Exclusive__Everburning):

	resource_path = "res://gd_core_items/Exclusive/Everburning.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numFlames = None
		self.burningSwordDescr = None
		self.burningBladeDescr = None
		self.staminaReduction = None


	def onPrepare(self):
		_iter__loc = _iter
		self.numFlames = self.countAllInInventoryOfType(self.ctx.item_book.getDescriptor("Flame"))

		for item in _iter__loc(self.getAllInInventoryOfType(self.burningSwordDescr)):
			item.changeStaminaFactor(self.staminaReduction)

		for item in _iter__loc(self.getAllInInventoryOfType(self.burningBladeDescr)):
			item.changeStaminaFactor(self.staminaReduction)


	def doCooldownEffect(self):
		if self.numFlames > 0:
			self.giveHeat(self.getP("heat") * self.numFlames)
		self.onAfterEffectFinished()


	def canAffect_global(self, item):
		return (item.isA(self.ctx.item_book.getDescriptor("Flame")) or 
				item.isA(self.burningBladeDescr) or 
				item.isA(self.burningSwordDescr))

	def _readyInit(self):
		super()._readyInit()
		self.burningSwordDescr = self.ctx.item_book.getDescriptor("Burning Sword")
		self.burningBladeDescr = self.ctx.item_book.getDescriptor("Burning Blade")
		self.staminaReduction = - self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Everburning.gd", Exclusive__Everburning)
_R.reg("Everburning", Exclusive__Everburning)

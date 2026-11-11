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
if "_base_cls_Exclusive__TimeDilator" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__TimeDilator





class Exclusive__TimeDilator(_base_cls_Exclusive__TimeDilator):

	resource_path = "res://gd_core_items/Exclusive/TimeDilator.gd"

	def _init_fields(self):
		super()._init_fields()
		self._tickI = 0
		self.slow = None
		self.speedUp = None

	@property
	def tickI(self):
		return self._tickI
	@tickI.setter
	def tickI(self, v):
		self._tickI = int(v)

	def onPrepare(self):
		self.tickI = 0
		allItems = self.ctx.player.INVENTORY.getItems() + self.ctx.opponent.INVENTORY.getItems()
		for item in (allItems if allItems.__class__ is list else _iter(allItems)):
			if item.isWeapon():
				item.reduceSpeed(self.slow)


	def doCooldownEffect(self):
		slowestCd = 0.0
		slowestItem = None

		for item in _iter(self.inventory.getItems()):
			if item.hasCooldown() and item.isCooldownActive():
				cd = item.getModifiedCooldown()
				if cd > slowestCd:
					slowestCd = cd
					slowestItem = item


		slowestItem.addSpeed(self.speedUp)
		self.activate()
		self.tickI += 1


	def playActivationSound(self):
		pitch = 1.0 if _mod(self.tickI, 2) == 0 else 0.7


	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.slow = _div__loc(self.getP('slow'), 100.0)
		self.speedUp = _div__loc(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/TimeDilator.gd", Exclusive__TimeDilator)
_R.reg("TimeDilator", Exclusive__TimeDilator)

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
if "_base_cls_Exclusive__HolyCollar" not in globals():
	from ..RangerCollar import RangerCollar_2 as _base_cls_Exclusive__HolyCollar





class Exclusive__HolyCollar(_base_cls_Exclusive__HolyCollar):

	resource_path = "res://gd_core_items/Exclusive/HolyCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luck = None
		self.regen = None


	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		for item in (self.affectedItems if self.affectedItems.__class__ is list else _iter(self.affectedItems)):
			self.connectForCombat(item, "activated", "onItemActivated")

		if not (not self.affectedItems):
			self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyOrRegenChanged")
			self.connectForCombat(self.character(), "character_regeneration_changed", "onLuckyOrRegenChanged")


	def onLuckyOrRegenChanged(self, amount, _event):
		for item in (self.affectedItems if self.affectedItems.__class__ is list else _iter(self.affectedItems)):
			item.changeCritChancePercent(amount * self.getChance2())


	def onItemActivated(self, event):
		if self.rollChance():
			self.giveLucky(self.luck, event)
			self.giveRegeneration(self.regen, event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/HolyCollar.gd", Exclusive__HolyCollar)
_R.reg("HolyCollar", Exclusive__HolyCollar)

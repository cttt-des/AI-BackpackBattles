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
if "_base_cls_Exclusive__MagiteccArmor" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__MagiteccArmor





class Exclusive__MagiteccArmor(_base_cls_Exclusive__MagiteccArmor):

	resource_path = "res://gd_core_items/Exclusive/MagiteccArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedPerAffected = None
		self.manaNeeded = None
		self.numDebuffs = None
		self.block2 = None


	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_2)


	def onPrepare(self):
		self.addSpeed(self.getNumAffectedItems() * self.speedPerAffected)


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.cleanseRandomDebuffs(self.numDebuffs, event)
			self.giveBlock(self.block2, True, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedPerAffected = _div(self.getP('speed'), 100.0)
		self.manaNeeded = int(self.getP("manat"))
		self.numDebuffs = int(self.getP("cleanse"))
		self.block2 = int(self.getP("block"))


_R.reg("res://gd_core_items/Exclusive/MagiteccArmor.gd", Exclusive__MagiteccArmor)
_R.reg("MagiteccArmor", Exclusive__MagiteccArmor)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Magic
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

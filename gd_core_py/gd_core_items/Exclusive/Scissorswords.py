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
if "_base_cls_Exclusive__Scissorswords" not in globals():
	from ..Lightsaber import Lightsaber_2 as _base_cls_Exclusive__Scissorswords





class Exclusive__Scissorswords(_base_cls_Exclusive__Scissorswords):

	resource_path = "res://gd_core_items/Exclusive/Scissorswords.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.bonusDam = None
		self.luck = None
		self.regen = None


	def inflict(self, duration, event):
		super().inflict(duration, event)
		self.giveStacksTemporary(self.character(), _H_1, 
			self.blind, duration, event)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.character().getLucky() >= self.luckNeeded:
				event = self.useLucky(self.luckNeeded, damageRes.event)
				self.addBonusDamage(self.bonusDam)
				self.giveRegeneration(self.regen, event)
		else:
			self.giveLucky(self.luck, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.bonusDam = self.getP("dam")
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Scissorswords.gd", Exclusive__Scissorswords)
_R.reg("Scissorswords", Exclusive__Scissorswords)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

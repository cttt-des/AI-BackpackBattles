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
if "_base_cls_Exclusive__Rat" not in globals():
	from .ForestFriend import Exclusive__ForestFriend as _base_cls_Exclusive__Rat





class Exclusive__Rat(_base_cls_Exclusive__Rat):

	resource_path = "res://gd_core_items/Exclusive/Rat.gd"

	def _init_fields(self):
		super()._init_fields()
		self._poison = 0
		self._blind = 0

	@property
	def poison(self):
		return self._poison
	@poison.setter
	def poison(self, v):
		self._poison = int(v)
	@property
	def blind(self):
		return self._blind
	@blind.setter
	def blind(self, v):
		self._blind = int(v)

	def initRat(self):
		self.damageSource = _H_1().setItem(self)
		self.poison = int(self.getP("poison"))
		self.blind = int(self.getP("blind"))


	def doCooldownEffect(self):
		dam = self.descriptor.minDam
		res = self.dealEffectDamage(dam)
		if self.rollChance():
			self.inflictPoison(self.poison, res.event)
		if self.rollChance2():
			self.inflictBlind(self.blind, res.event)

		self.activate(res)


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.initRat()



_R.reg("res://gd_core_items/Exclusive/Rat.gd", Exclusive__Rat)
_R.reg("Rat", Exclusive__Rat)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")

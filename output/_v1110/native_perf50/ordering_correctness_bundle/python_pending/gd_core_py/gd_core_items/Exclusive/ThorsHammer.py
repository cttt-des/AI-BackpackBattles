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
if "_base_cls_Exclusive__ThorsHammer" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__ThorsHammer





class Exclusive__ThorsHammer(_base_cls_Exclusive__ThorsHammer):

	resource_path = "res://gd_core_items/Exclusive/ThorsHammer.gd"

	def _init_fields(self):
		super()._init_fields()
		self.effectDmgSource = None
		self.manaNeeded = None
		self.effectDmg = None
		self.blind = None


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), damageRes.event)

			if self.character().getMana() >= self.manaNeeded:
				event = self.useMana(self.manaNeeded, damageRes.event)
				self.dealEffectDamage(self.effectDmg, event, self.effectDmgSource)
				duration = self.getP_m("dur_blind")
				self.giveStacksTemporary(self.opponent(), _H_3, 
					self.blind, duration, event)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.effectDmg = int(self.getP("dam"))
		self.blind = int(self.getP("blind"))
		self.effectDmgSource = _H_1().init(self, 
			_H_2, self.effectDmg)



_R.reg("res://gd_core_items/Exclusive/ThorsHammer.gd", Exclusive__ThorsHammer)
_R.reg("ThorsHammer", Exclusive__ThorsHammer)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")
try:
	_H_2 = _R.C("CoreDamageSource").Type.Effect
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

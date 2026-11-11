# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_TheLovers_2" not in globals():
	from .Card import Card_2 as _base_cls_TheLovers_2





class TheLovers_2(_base_cls_TheLovers_2):

	resource_path = "res://gd_core_items/TheLovers.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heartParticles = None
		self.healAmp = None
		self.dam = None
		self.regen = None


	def cardSecondaryEffectActive(self):
		return _mod(self.chainPosition, 2) == 0


	def doRevealEffect(self):
		if self.cardSecondaryEffectActive():
			self.character().addHealingEfficiency(self.healAmp)

		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0))

		if self.cardSecondaryEffectActive():
			self.giveRegeneration(self.regen)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healAmp = _div(self.getP('healamp'), 100.0)
		self.dam = self.getP("dam")
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/TheLovers.gd", TheLovers_2)
_R.reg("TheLovers", TheLovers_2)

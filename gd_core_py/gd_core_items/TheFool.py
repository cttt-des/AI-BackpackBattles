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
if "_base_cls_TheFool_2" not in globals():
	from .Card import Card_2 as _base_cls_TheFool_2





class TheFool_2(_base_cls_TheFool_2):

	resource_path = "res://gd_core_items/TheFool.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None


	def cardSecondaryEffectActive(self):
		return self.chainPosition == 0


	def doRevealEffect(self):
		bonusSpeed = _div(self.getP('revealspeed'), 100.0)
		for card in (self.deck.cards if self.deck.cards.__class__ is list else _iter(self.deck.cards)):
			card.addSpeed(bonusSpeed)

		if self.cardSecondaryEffectActive():
			self.giveEmpower(self.getP("empower"))

		self.activate()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/TheFool.gd", TheFool_2)
_R.reg("TheFool", TheFool_2)

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
if "_base_cls_AceofSpades_2" not in globals():
	from .Card import Card_2 as _base_cls_AceofSpades_2





class AceofSpades_2(_base_cls_AceofSpades_2):

	resource_path = "res://gd_core_items/AceofSpades.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spadesParticles = None
		self.luck = None
		self.spikes = None


	def cardSecondaryEffectActive(self):
		return _mod(self.chainPosition, 2) == 1


	def doRevealEffect(self):
		self.giveCritTokens(1)

		if self.cardSecondaryEffectActive():
			self.giveLucky(self.luck)
			self.giveSpikes(self.spikes)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/AceofSpades.gd", AceofSpades_2)
_R.reg("AceofSpades", AceofSpades_2)

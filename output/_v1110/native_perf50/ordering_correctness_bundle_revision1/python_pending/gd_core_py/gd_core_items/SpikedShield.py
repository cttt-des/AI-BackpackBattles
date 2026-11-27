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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_SpikedShield_2" not in globals():
	from .Shield import Shield_2 as _base_cls_SpikedShield_2





class SpikedShield_2(_base_cls_SpikedShield_2):

	resource_path = "res://gd_core_items/SpikedShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self._spikesGiven = 0
		self.spikes = None
		self.maxSpikes = None

	@property
	def spikesGiven(self):
		return self._spikesGiven
	@spikesGiven.setter
	def spikesGiven(self, v):
		self._spikesGiven = int(v)

	def onPrepare(self):
		self.spikesGiven = 0


	def beforeBlock(self):
		super().beforeBlock()
		spikesLeft = self.maxSpikes - self.spikesGiven
		if spikesLeft > 0:
			spikesToGive = min(spikesLeft, self.spikes)
			self.spikesGiven += spikesToGive
			self.giveSpikes(spikesToGive)


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.maxSpikes = int(self.getP("maxspikes"))


_R.reg("res://gd_core_items/SpikedShield.gd", SpikedShield_2)
_R.reg("SpikedShield", SpikedShield_2)

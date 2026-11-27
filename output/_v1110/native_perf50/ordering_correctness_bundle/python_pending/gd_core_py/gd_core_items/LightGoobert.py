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
if "_base_cls_LightGoobert_2" not in globals():
	from .Goobert import Goobert_2 as _base_cls_LightGoobert_2





class LightGoobert_2(_base_cls_LightGoobert_2):

	resource_path = "res://gd_core_items/LightGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.particleTimer = None
		self.activationParticles = None
		self.blindAmount = None


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		self.setState(True, True)
		self.heal()
		duration = self.getP_m("dur_blind")
		self.giveStacksTemporary(self.opponent(), _H_1, 
			self.blindAmount, duration)
		self.particleTimer.stop()
		self.particleTimer.start(duration)


	def onCombatEnd(self):
		self.particleTimer.stop()


	def onParticleTimeout(self):
		self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.particleTimer = self.newItemTimer("ParticleTimer", "onParticleTimeout", False)
		self.blindAmount = self.getP3()


_R.reg("res://gd_core_items/LightGoobert.gd", LightGoobert_2)
_R.reg("LightGoobert", LightGoobert_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

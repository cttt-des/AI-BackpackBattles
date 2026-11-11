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
if "_base_cls_Exclusive__FrogPrince" not in globals():
	from .Toad import Exclusive__Toad as _base_cls_Exclusive__FrogPrince





class Exclusive__FrogPrince(_base_cls_Exclusive__FrogPrince):

	resource_path = "res://gd_core_items/Exclusive/FrogPrince.gd"

	FrogState = EnumDict("FrogState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self._frogState = 0
		self.activationParticles = None
		self.buffTimer = None
		self.light = None
		self.blind = None

	@property
	def frogState(self):
		return self._frogState
	@frogState.setter
	def frogState(self, v):
		self._frogState = int(v)

	def onGainThresholdReached(self, ticks, event):
		self.cleanseBlind(self.blind, event)
		self.heal(ticks * self.getP_m("heal"), event)
		self.miniActivate()


	def onUseThresholdReached(self, ticks, event):
		if self.frogState == self.FrogState.Inactive:
			self.setState(self.FrogState.Active, True)
			self.giveLucky(self.luck, event)
			self.giveMana(self.mana, event)
			invuDur = self.getP_m("dur_1")
			self.character().makeInvulnerable(invuDur, self, event)
			self.buffTimer.start(invuDur)
			self.miniActivate()


	def onPrepare(self):
		super().onPrepare()
		self.setState(self.FrogState.Inactive)


	def buffEnded(self):
		self.setState(self.FrogState.Used, True)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.FrogState.Inactive)


	def onStateChanged(self, _frogState):
		if _frogState == self.FrogState.Inactive:
			pass

		elif _frogState == self.FrogState.Active:
			pass

		else:
			pass

		self.frogState = _frogState

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/FrogPrince.gd", Exclusive__FrogPrince)
_R.reg("FrogPrince", Exclusive__FrogPrince)

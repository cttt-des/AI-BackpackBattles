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
if "_base_cls_Exclusive__DraconicOrb" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__DraconicOrb





class Exclusive__DraconicOrb(_base_cls_Exclusive__DraconicOrb):

	resource_path = "res://gd_core_items/Exclusive/DraconicOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.counter = 0
		self.activationParticles = None
		self._heatThreshold = 0
		self._spikeRemoval = 0
		self._heatPerSpike = 0

	@property
	def heatThreshold(self):
		return self._heatThreshold
	@heatThreshold.setter
	def heatThreshold(self, v):
		self._heatThreshold = int(v)
	@property
	def spikeRemoval(self):
		return self._spikeRemoval
	@spikeRemoval.setter
	def spikeRemoval(self, v):
		self._spikeRemoval = int(v)
	@property
	def heatPerSpike(self):
		return self._heatPerSpike
	@heatPerSpike.setter
	def heatPerSpike(self, v):
		self._heatPerSpike = int(v)

	def onPrepare(self):
		self.counter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if self.counter < self.heatThreshold:
			self.counter += amount

			if self.counter >= self.heatThreshold:
				self.giveCritTokens(self.getP2())


	def doCooldownEffect(self):
		oppoSpikes = self.opponent().getSpikes()
		if oppoSpikes > 0:
			event = self.opponent().loseSpikes(self.spikeRemoval, self)
			self.giveHeat(min(oppoSpikes, self.spikeRemoval) * self.heatPerSpike, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.heatThreshold = self.getP1()
		self.spikeRemoval = self.getP3()
		self.heatPerSpike = self.getP4()


_R.reg("res://gd_core_items/Exclusive/DraconicOrb.gd", Exclusive__DraconicOrb)
_R.reg("DraconicOrb", Exclusive__DraconicOrb)

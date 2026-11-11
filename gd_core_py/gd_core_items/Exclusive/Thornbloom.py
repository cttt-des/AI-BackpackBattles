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
if "_base_cls_Exclusive__Thornbloom" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Thornbloom





class Exclusive__Thornbloom(_base_cls_Exclusive__Thornbloom):

	resource_path = "res://gd_core_items/Exclusive/Thornbloom.gd"

	def _init_fields(self):
		super()._init_fields()
		self._spikes = 0
		self._empower = 0
		self.damPerSpike = None

	@property
	def spikes(self):
		return self._spikes
	@spikes.setter
	def spikes(self, v):
		self._spikes = int(v)
	@property
	def empower(self):
		return self._empower
	@empower.setter
	def empower(self, v):
		self._empower = int(v)

	def onPrepare(self):
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(self.damPerSpike * amount)


	def onEmpowerChanged(self, amount, event):
		if amount > 0:
			self.giveMaxHealth(self.getP_m("maxhealth") * amount, event)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveSpikes(self.spikes)

			if self.rollChance():
				self.giveEmpower(self.empower)
			else:
				pass

	def _readyInit(self):
		super()._readyInit()
		self.spikes = self.getP("spikes")
		self.empower = self.getP("empower")
		self.damPerSpike = self.getP("damperspike")


_R.reg("res://gd_core_items/Exclusive/Thornbloom.gd", Exclusive__Thornbloom)
_R.reg("Thornbloom", Exclusive__Thornbloom)

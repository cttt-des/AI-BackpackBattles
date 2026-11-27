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
if "_base_cls_Exclusive__SpikedWall" not in globals():
	from ..SpikedShield import SpikedShield_2 as _base_cls_Exclusive__SpikedWall





class Exclusive__SpikedWall(_base_cls_Exclusive__SpikedWall):

	resource_path = "res://gd_core_items/Exclusive/SpikedWall.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesLimit = None
		self.staminaRegenMalus = None


	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnAttacked()


	def onPrepare(self):
		_ch = self.character()
		super().onPrepare()
		_ch.addBattleRageDuration(self.getP_m("dur_rage"))
		_ch.changeRangedSpikesLimit(self.spikesLimit)
		_ch.changeMeleeSpikesLimit(self.spikesLimit)
		baseStaminaRegen = _ch.baseStaminaRegen
		_ch.giveStaminaRegeneration(self.staminaRegenMalus * baseStaminaRegen)

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.spikesLimit = _div__loc(self.getP('spikedam'), 100.0)
		self.staminaRegenMalus = _div__loc(-self.getP('staminaregen'), 100.0)


_R.reg("res://gd_core_items/Exclusive/SpikedWall.gd", Exclusive__SpikedWall)
_R.reg("SpikedWall", Exclusive__SpikedWall)

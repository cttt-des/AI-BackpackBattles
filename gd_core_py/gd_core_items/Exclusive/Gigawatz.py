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
if "_base_cls_Exclusive__Gigawatz" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Gigawatz





class Exclusive__Gigawatz(_base_cls_Exclusive__Gigawatz):

	resource_path = "res://gd_core_items/Exclusive/Gigawatz.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numSpeedboosts = 0
		self._curDamageBonus = 0
		self.maxNumSpeedBoosts = None
		self.speedBonus = None
		self.damageBonus = None
		self.blind = None

	@property
	def numSpeedboosts(self):
		return self._numSpeedboosts
	@numSpeedboosts.setter
	def numSpeedboosts(self, v):
		self._numSpeedboosts = int(v)
	@property
	def curDamageBonus(self):
		return self._curDamageBonus
	@curDamageBonus.setter
	def curDamageBonus(self, v):
		self._curDamageBonus = int(v)

	def onPrepare(self):
		self.curDamageBonus = 0
		self.numSpeedboosts = 0


	def onChargeReceived(self, _charge):
		if self.numSpeedboosts < self.maxNumSpeedBoosts:
			self.addSpeed(self.speedBonus)
			self.numSpeedboosts += 1


	def doCooldownEffect(self):
		self.inflictBlind(self.blind)
		dam = self.descriptor.minDam + self.curDamageBonus
		res = self.dealEffectDamage(dam)
		self.activate()
		self.curDamageBonus += self.damageBonus


	def _readyInit(self):
		super()._readyInit()
		self.maxNumSpeedBoosts = int(self.getP("max"))
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.damageBonus = self.getP("damincrease")
		self.blind = int(self.getP("blind"))
		self.damageSource = _H_1().setItem(self)



_R.reg("res://gd_core_items/Exclusive/Gigawatz.gd", Exclusive__Gigawatz)
_R.reg("Gigawatz", Exclusive__Gigawatz)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")

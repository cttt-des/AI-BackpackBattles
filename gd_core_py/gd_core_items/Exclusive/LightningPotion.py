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
if "_base_cls_Exclusive__LightningPotion" not in globals():
	from ..Potion import Potion_2 as _base_cls_Exclusive__LightningPotion





class Exclusive__LightningPotion(_base_cls_Exclusive__LightningPotion):

	resource_path = "res://gd_core_items/Exclusive/LightningPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blind = None
		self.lightningAni = None


	def canAffect_secondary(self, item):
		return item.hasType(_H_1)


	def onTriggerPotion(self, triggerEvent=None):
		dam = self.descriptor.minDam
		res = self.dealEffectDamage(dam)


		self.giveStacksTemporary(self.opponent(), _H_2, 
			self.blind, self.getP_m("dur_blind"), triggerEvent)

		self.heal(self.getP_m("heal") * self.getNumAffectedItems(_H_4))


	def onPrepare(self):
		self.baseCooldownOverride = self.ctx.rng.randf_range(
			self.getBaseCooldownIndex(0), self.getBaseCooldownIndex(1))




	def doCooldownEffect(self):
		self.consumePotion(None, False)
		self.onAfterEffectFinished()


	def fill(self):
		super().fill()


	def empty(self):
		super().empty()

	def _readyInit(self):
		super()._readyInit()
		self.blind = int(self.getP("blind"))
		self.damageSource = _H_3().setItem(self)



_R.reg("res://gd_core_items/Exclusive/LightningPotion.gd", Exclusive__LightningPotion)
_R.reg("LightningPotion", Exclusive__LightningPotion)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
_H_3 = _R.C("CoreDamageSource")
try:
	_H_4 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_4 = _HoistPending(_he)

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
if "_base_cls_Exclusive__SpellScrollFrostbolt" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SpellScrollFrostbolt





class Exclusive__SpellScrollFrostbolt(_base_cls_Exclusive__SpellScrollFrostbolt):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollFrostbolt.gd"

	def _init_fields(self):
		super()._init_fields()
		self._maxUses = 0
		self._uses = 0
		self.coldAmount = None

	@property
	def maxUses(self):
		return self._maxUses
	@maxUses.setter
	def maxUses(self, v):
		self._maxUses = int(v)
	@property
	def uses(self):
		return self._uses
	@uses.setter
	def uses(self, v):
		self._uses = int(v)

	def canAffect(self, item):
		return item.hasType(_H_2) and not item.isA(self.descriptor)


	def onPrepare(self):
		self.uses = 0
		self.maxUses = int(self.getP1()) + self.getNumAffectedItems()


	def doCooldownEffect(self):
		if self.uses < self.maxUses:
			self.uses += 1
			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam)
			self.giveStacksTemporary(self.opponent(), _H_3, 
				self.coldAmount, self.getP_m("dur_cold"), damageRes.event)
			if self.uses == self.maxUses:
				self.onAfterEffectFinished()
			else:
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.coldAmount = int(self.getP3())
		self.damageSource = _H_1().setItem(self)



_R.reg("res://gd_core_items/Exclusive/SpellScrollFrostbolt.gd", Exclusive__SpellScrollFrostbolt)
_R.reg("SpellScrollFrostbolt", Exclusive__SpellScrollFrostbolt)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")
try:
	_H_2 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

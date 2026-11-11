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
if "_base_cls_Exclusive__Generator" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Generator





class Exclusive__Generator(_base_cls_Exclusive__Generator):

	resource_path = "res://gd_core_items/Exclusive/Generator.gd"

	def _init_fields(self):
		super()._init_fields()
		self.flatSpeed = None
		self.speedPerTile = None

	chargeCells = [Vector2( - 1, - 1), Vector2( - 1, - 2),
		Vector2( - 2, - 3), Vector2( - 2, - 4), Vector2( - 1, - 5), Vector2(0, - 5)]

	def canAffect_lightning(self, item):
		return item.hasCooldown() or item.reactsToCharges()


	def onCombatStart(self):
		self.emitCharge()
		self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells, speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.flatSpeed, self.speedPerTile)


	def chargedItemStatChange(self, item, value):
		item.addSpeed(value)


	def getTriggerPriority(self):
		return _H_2 + 5

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.flatSpeed = _div__loc(self.getP('speed'), 100)
		self.speedPerTile = _div__loc(self.getP('speed2'), 100)


_R.reg("res://gd_core_items/Exclusive/Generator.gd", Exclusive__Generator)
_R.reg("Generator", Exclusive__Generator)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

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
if "_base_cls_Exclusive__PerpetuumMobile" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__PerpetuumMobile





class Exclusive__PerpetuumMobile(_base_cls_Exclusive__PerpetuumMobile):

	resource_path = "res://gd_core_items/Exclusive/PerpetuumMobile.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.staminaUsed = 0.0
		self.stamina = None
		self.buffRefund = None
		self.staminaRefund = None
		self.speed_v = None


	def canAffect(self, item):
		return item.isClassItem(_H_1)


	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffChanged")
		for buff in _iter(_H_2.getBuffs()):
			self.usedStacks[buff] = 0.0

		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")
		self.staminaUsed = 0

		self.addSpeed(self.speed_v * self.getNumAffectedItems())


	def onCombatStart(self):
		self.giveMaxStaminaTemporary(self.stamina, None, False)
		self.activate()


	def onBuffChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount


	def doCooldownEffect(self):

		for buffType in (self.usedStacks if self.usedStacks.__class__ is list else _iter(self.usedStacks)):
			toRefund = int(gd_round(self.usedStacks[buffType] * self.buffRefund))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund)

		self.giveStamina(self.staminaUsed * self.staminaRefund)
		self.staminaUsed = 0

		self.activate()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.stamina = self.getP("stamina")
		self.buffRefund = _div__loc(self.getP('refund_buffs'), 100.0)
		self.staminaRefund = _div__loc(self.getP('refund_stamina'), 100.0)
		self.speed_v = _div__loc(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PerpetuumMobile.gd", Exclusive__PerpetuumMobile)
_R.reg("PerpetuumMobile", Exclusive__PerpetuumMobile)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Classes_Full.Engineer
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreConst")

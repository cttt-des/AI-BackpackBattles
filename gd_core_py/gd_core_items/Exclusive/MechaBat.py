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
if "_base_cls_Exclusive__MechaBat" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__MechaBat





class Exclusive__MechaBat(_base_cls_Exclusive__MechaBat):

	resource_path = "res://gd_core_items/Exclusive/MechaBat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.lifestealActive = False
		self.lifestealParticles = None
		self.lifestealLight = None
		self.vampirism1 = None
		self.luckNeeded = None
		self.luckUsed = None
		self.vampirism2 = None


	def canAffect(self, item):
		return item.canDamage()


	def doCooldownEffect(self):
		numVamp = 0
		if self.character().getLucky() >= self.luckNeeded:
			self.useLucky(self.luckUsed)
			numVamp += self.vampirism2

		if self.useStamina() == _H_1:
			numVamp += self.vampirism1

		if numVamp > 0:
			self.giveVampirism(numVamp)
			self.activate()


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onOpponentDamaged(self, damageRes):
		if self.lifestealActive:
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				if damageRes.damageSource.origin in self.getAffectedItems():
					self.heal(ceil(_div(damageRes.damage * self.getP_m('lifesteal'), 100.0)), damageRes.event)


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(True)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _lifestealActive):
		self.lifestealActive = _lifestealActive
		if self.lifestealActive:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.vampirism1 = int(self.getP("vampirism"))
		self.luckNeeded = int(self.getP("luckt"))
		self.luckUsed = int(self.getP("luck"))
		self.vampirism2 = int(self.getP("vampirism2"))


_R.reg("res://gd_core_items/Exclusive/MechaBat.gd", Exclusive__MechaBat)
_R.reg("MechaBat", Exclusive__MechaBat)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

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
if "_base_cls_Exclusive__MercuryElemental" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__MercuryElemental





class Exclusive__MercuryElemental(_base_cls_Exclusive__MercuryElemental):

	resource_path = "res://gd_core_items/Exclusive/MercuryElemental.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaRegen = 0.0
		self.staminaUsed = 0.0
		self.poison = None
		self.selfPoison = None
		self.staminaThreshold = None
		self.distortion = None


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_1
		return color == _H_1


	def canAffect(self, item):
		return item.descriptor.isMeleeWeapon()


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentAttacked")
		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")

		self.staminaRegen = self.getP("stamina") * self.getNumDistinctAffectedItems()
		self.staminaUsed = 0


	def onOpponentAttacked(self, damageRes):
		if damageRes.triggerOnAttacked():
			self.giveBlock(_div(self.getBlock(), 100.0) * damageRes.damage)


	def doCooldownEffect(self):
		self.giveStamina(self.staminaRegen)
		self.activate()


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount
		ticks = floor(_div(self.staminaUsed, self.staminaThreshold))
		if ticks > 0:
			self.inflictPoison(ticks * self.poison)
			self.selfInflictPoison(ticks * self.selfPoison)
			self.staminaUsed -= ticks * self.staminaThreshold
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.selfPoison = int(self.getP("poison2"))
		self.staminaThreshold = self.getP("staminat")
		if self.ownerType == _H_2:
			pass
		else:
			pass



_R.reg("res://gd_core_items/Exclusive/MercuryElemental.gd", Exclusive__MercuryElemental)
_R.reg("MercuryElemental", Exclusive__MercuryElemental)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Owner.GridStorage
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

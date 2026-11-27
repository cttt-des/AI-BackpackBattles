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
if "_base_cls_Exclusive__JynxStaff" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__JynxStaff





class Exclusive__JynxStaff(_base_cls_Exclusive__JynxStaff):

	resource_path = "res://gd_core_items/Exclusive/JynxStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.manaCost = None
		self.permDamBonus = None
		self.speedBonus = None
		self.maxActivations = None
		self.luckRemoval = None

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)

	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.numActivations = 0


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			self.addBonusDamage(self.permDamBonus)
			if self.numActivations < self.maxActivations:
				for item in _iter(self.getAffectedItems()):

					item.addSpeed(self.speedBonus)

				self.numActivations += 1

			if self.opponent().getLucky() > 0:
				self.removeLucky(self.luckRemoval)


	def _readyInit(self):
		super()._readyInit()
		self.manaCost = int(self.getP("manat"))
		self.permDamBonus = self.getP("dam")
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))
		self.luckRemoval = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/JynxStaff.gd", Exclusive__JynxStaff)
_R.reg("JynxStaff", Exclusive__JynxStaff)

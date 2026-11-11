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
if "_base_cls_Exclusive__StaffofFire" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__StaffofFire





class Exclusive__StaffofFire(_base_cls_Exclusive__StaffofFire):

	resource_path = "res://gd_core_items/Exclusive/StaffofFire.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.activationParticles = None
		self._manaCost = 0
		self._heatCost = 0
		self._damBonus = 0

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)
	@property
	def manaCost(self):
		return self._manaCost
	@manaCost.setter
	def manaCost(self, v):
		self._manaCost = int(v)
	@property
	def heatCost(self):
		return self._heatCost
	@heatCost.setter
	def heatCost(self, v):
		self._heatCost = int(v)
	@property
	def damBonus(self):
		return self._damBonus
	@damBonus.setter
	def damBonus(self, v):
		self._damBonus = int(v)

	def onPrepare(self):
		self.numActivations = 0


	def onPreDealDamage_early(self, damageRes):
		if self.character().getHeat() >= self.heatCost:
			event = self.tryUseMana(self.manaCost)
			if event != None:
				self.useHeat(self.heatCost, event)
				self.addBonusDamage(self.damBonus)
				self.numActivations += 1


	def onShopEntered(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP1()
		self.heatCost = self.getP2()
		self.damBonus = self.getP3()
		pass



_R.reg("res://gd_core_items/Exclusive/StaffofFire.gd", Exclusive__StaffofFire)
_R.reg("StaffofFire", Exclusive__StaffofFire)

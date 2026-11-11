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
if "_base_cls_Exclusive__CriticalPoison" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__CriticalPoison





class Exclusive__CriticalPoison(_base_cls_Exclusive__CriticalPoison):

	resource_path = "res://gd_core_items/Exclusive/CriticalPoison.gd"

	def _init_fields(self):
		super()._init_fields()
		self._damageAcc = 0
		self._damagePerPoison = 0
		self._poison = 0

	@property
	def damageAcc(self):
		return self._damageAcc
	@damageAcc.setter
	def damageAcc(self, v):
		self._damageAcc = int(v)
	@property
	def damagePerPoison(self):
		return self._damagePerPoison
	@damagePerPoison.setter
	def damagePerPoison(self, v):
		self._damagePerPoison = int(v)
	@property
	def poison(self):
		return self._poison
	@poison.setter
	def poison(self, v):
		self._poison = int(v)

	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onWeaponAttacked")
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			self.damageAcc += damageRes.damage

			poisonStacks = _div(self.damageAcc, self.damagePerPoison)
			if poisonStacks > 0:
				self.inflictPoison(poisonStacks * self.poison, damageRes.event)
				self.damageAcc %= self.damagePerPoison
				self.miniActivate()


	def onLuckChanged(self, amount, event):
		self.opponent().changePoisonCritChancePercent(amount * self.getChance())

	def _readyInit(self):
		super()._readyInit()
		self.damagePerPoison = self.getP("damt")
		self.poison = self.getP("poison")


_R.reg("res://gd_core_items/Exclusive/CriticalPoison.gd", Exclusive__CriticalPoison)
_R.reg("CriticalPoison", Exclusive__CriticalPoison)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_BowandArrow_2" not in globals():
	from .Bow import Bow_2 as _base_cls_BowandArrow_2





class BowandArrow_2(_base_cls_BowandArrow_2):

	resource_path = "res://gd_core_items/BowandArrow.gd"

	def _init_fields(self):
		super()._init_fields()
		self._bonusDmg = 0
		self._bonusDmgPerHit = 0
		self._maxDmg = 0

	@property
	def bonusDmg(self):
		return self._bonusDmg
	@bonusDmg.setter
	def bonusDmg(self, v):
		self._bonusDmg = int(v)
	@property
	def bonusDmgPerHit(self):
		return self._bonusDmgPerHit
	@bonusDmgPerHit.setter
	def bonusDmgPerHit(self, v):
		self._bonusDmgPerHit = int(v)
	@property
	def maxDmg(self):
		return self._maxDmg
	@maxDmg.setter
	def maxDmg(self, v):
		self._maxDmg = int(v)

	def hasAttackEffect(self):
		return True


	def onPrepare(self):
		self.bonusDmg = 0
		self.setState(0)


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			dmgAdded = False
			attackEffectCount = 1 + self.rollDoubleAttackEffect()
			for i in (attackEffectCount if attackEffectCount.__class__ is list else _iter(attackEffectCount)):
				if self.bonusDmg < self.maxDmg:
					self.bonusDmg += self.bonusDmgPerHit
					self.addBonusDamage(self.bonusDmgPerHit)
					dmgAdded = True

			if dmgAdded:
				self.setState(self.bonusDmg, False, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _bonusDmg):
		if _bonusDmg > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.bonusDmgPerHit = self.getP1()
		self.maxDmg = self.getP2()


_R.reg("res://gd_core_items/BowandArrow.gd", BowandArrow_2)
_R.reg("BowandArrow", BowandArrow_2)

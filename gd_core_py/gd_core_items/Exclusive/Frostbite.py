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
if "_base_cls_Exclusive__Frostbite" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Frostbite





class Exclusive__Frostbite(_base_cls_Exclusive__Frostbite):

	resource_path = "res://gd_core_items/Exclusive/Frostbite.gd"

	def _init_fields(self):
		super()._init_fields()
		self.gaveVampirism = False
		self.damagePerCold = None
		self.coldNeeded = None
		self.vampirism = None


	def onPrepare(self):
		self.gaveVampirism = False
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
		self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")


	def onVampirismChanged(self, amount, _event):
		self.changeVaryingDamage(amount)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.inflictCold(self.getP1())


	def onOpponentColdChanged(self, amount, event):
		self.changeVaryingDamage(self.damagePerCold * amount)

		if not self.gaveVampirism and self.opponent().getCold() >= self.coldNeeded:
			self.gaveVampirism = True
			self.giveVampirism(self.vampirism, event)

	def _readyInit(self):
		super()._readyInit()
		self.damagePerCold = self.getP2()
		self.coldNeeded = int(self.getP3())
		self.vampirism = int(self.getP4())


_R.reg("res://gd_core_items/Exclusive/Frostbite.gd", Exclusive__Frostbite)
_R.reg("Frostbite", Exclusive__Frostbite)

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
if "_base_cls_Exclusive__VampiricCollar" not in globals():
	from ..RangerCollar import RangerCollar_2 as _base_cls_Exclusive__VampiricCollar





class Exclusive__VampiricCollar(_base_cls_Exclusive__VampiricCollar):

	resource_path = "res://gd_core_items/Exclusive/VampiricCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItems_dict = {}
		self.maxLifesteal = None


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		if not (not self.affectedItems):
			self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
			self.connectForCombat(self.opponent(), "character_attacked", "onOpponentAttacked")

		self.affectedItems_dict = self.ctx.util.arrayAsIndexDict(self.affectedItems)


	def onVampirismChanged(self, amount, event):
		for item in (self.affectedItems if self.affectedItems.__class__ is list else _iter(self.affectedItems)):
			item.changeCritChancePercent(amount * self.getChance())


	def onOpponentAttacked(self, damageRes):
		if (damageRes.getDamage() > 0 and 
			damageRes.damageSource.canApplyLifesteal() and 
			damageRes.damageSource.origin in self.affectedItems_dict):

			lifestealFactor = _div(self.getP_m('lifesteal'), 100.0) * self.character().getLucky()
			if lifestealFactor > 0:
				lifestealFactor = min(lifestealFactor, self.maxLifesteal)
				lifesteal = max(1, damageRes.damage * lifestealFactor)
				self.heal(lifesteal, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.maxLifesteal = _div(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/VampiricCollar.gd", Exclusive__VampiricCollar)
_R.reg("VampiricCollar", Exclusive__VampiricCollar)

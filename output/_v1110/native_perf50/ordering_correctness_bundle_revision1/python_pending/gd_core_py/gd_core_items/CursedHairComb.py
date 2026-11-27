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
if "_base_cls_CursedHairComb_2" not in globals():
	from .Item import Item_2 as _base_cls_CursedHairComb_2





class CursedHairComb_2(_base_cls_CursedHairComb_2):

	resource_path = "res://gd_core_items/CursedHairComb.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.character().addHealingEfficiency(_div(self.getP3(), 100.0))


		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onAffectedAttacked")


	def onCombatStart(self):
		self.giveVampirism(self.getP1())
		self.activate()


	def onAffectedAttacked(self, damageRes):
		if damageRes.hasHit():
			bonusLifesteal = self.getNumAffectedItems(_H_2) * self.getP_m("lifesteal_scaling")
			self.heal(ceil(damageRes.damage * (self.getP_m("lifesteal") + bonusLifesteal) / 100.0), 
				damageRes.event)










	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/CursedHairComb.gd", CursedHairComb_2)
_R.reg("CursedHairComb", CursedHairComb_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

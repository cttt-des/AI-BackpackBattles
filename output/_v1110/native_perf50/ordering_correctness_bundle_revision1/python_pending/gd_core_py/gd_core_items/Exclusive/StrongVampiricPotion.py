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
if "_base_cls_Exclusive__StrongVampiricPotion" not in globals():
	from .VampiricPotion import Exclusive__VampiricPotion as _base_cls_Exclusive__StrongVampiricPotion





class Exclusive__StrongVampiricPotion(_base_cls_Exclusive__StrongVampiricPotion):

	resource_path = "res://gd_core_items/Exclusive/StrongVampiricPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.curLifesteal = 0.0
		self.lifestealGiven = []
		self.lifestealTimer = None
		self.lifestealPerTrigger = None


	def onPrepare(self):
		super().onPrepare()
		self.curLifesteal = 0.0
		self.lifestealGiven.clear()
		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onTriggerPotion(self, triggerEvent=None):

		amount = _div(self.getP_m('lifesteal'), 100.0)
		self.curLifesteal += amount
		self.lifestealGiven.append(amount)
		self.lifestealTimer.start(self.getP_m("dur"))
		self.giveVampirism(self.getP2(), triggerEvent)


	def onOpponentDamaged(self, damageRes):
		if self.curLifesteal > 0:
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				self.heal(ceil(damageRes.damage * self.curLifesteal), damageRes.event)


	def onLifestealTimeout(self):
		self.curLifesteal -= self.lifestealGiven.pop(0)


	def onCombatEnd(self):
		self.lifestealTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.lifestealTimer = self.newItemTimer("LifestealTimer", "onLifestealTimeout", True)
		self.lifestealPerTrigger = _div(self.getP3(), 100.0)


_R.reg("res://gd_core_items/Exclusive/StrongVampiricPotion.gd", Exclusive__StrongVampiricPotion)
_R.reg("StrongVampiricPotion", Exclusive__StrongVampiricPotion)

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
if "_base_cls_CritwoodStaff_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_CritwoodStaff_2





class CritwoodStaff_2(_base_cls_CritwoodStaff_2):

	resource_path = "res://gd_core_items/CritwoodStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffActive = False
		self.activationParticles = None
		self.critTimer = None
		self.manaCost = None
		self.tempDamBonus = None


	def onPrepare(self):
		self.setState(False)


	def onPreDealDamage_early(self, damageRes):
		if self.character().getMana() >= self.manaCost:
			if not self.buffActive:
				self.setState(True, True)
				for item in _iter(self.inventory.getItems()):
					item.addCritChancePercent(100)

			self.useMana(self.manaCost)
			damageRes.damage += self.tempDamBonus
			critBuffDur = self.getP_m("dur")
			self.ctx.util.changeTimer(self.critTimer, critBuffDur)


	def buffEnded(self):
		for item in _iter(self.inventory.getItems()):
			item.reduceCritChancePercent(100)
		self.setState(False)


	def onCombatEnd(self):
		self.critTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.buffActive = active

	def _readyInit(self):
		super()._readyInit()
		self.critTimer = self.newItemTimer("CritBuffTimer", "buffEnded", False)
		self.manaCost = self.getP1()
		self.tempDamBonus = self.getP2()


_R.reg("res://gd_core_items/CritwoodStaff.gd", CritwoodStaff_2)
_R.reg("CritwoodStaff", CritwoodStaff_2)

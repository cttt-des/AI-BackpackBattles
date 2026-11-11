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
if "_base_cls_Exclusive__BrassKnuckles" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__BrassKnuckles





class Exclusive__BrassKnuckles(_base_cls_Exclusive__BrassKnuckles):

	resource_path = "res://gd_core_items/Exclusive/BrassKnuckles.gd"

	def _init_fields(self):
		super()._init_fields()
		self.extraAccuracy = None
		self.battleRageSpeed = None


	def canAffect(self, item):
		return item.canDamage()


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.addCritChancePercent(self.getChance2())
			self.addAccuracy(self.extraAccuracy)
			for item in _iter(self.getAffectedItems()):
				item.addCritChancePercent(self.getChance2())
				if item.isWeapon():
					item.addAccuracy(self.extraAccuracy)
			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onPrepare(self):
		_ch = self.character()
		self.connectForCombat(_ch, "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(_ch, "battle_rage_ended", "onBattleRageEnded")


	def onBattleRageStarted(self, _event):
		self.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.reduceSpeed(self.battleRageSpeed)

	def _readyInit(self):
		super()._readyInit()
		self.extraAccuracy = self.getP2()
		self.battleRageSpeed = _div(self.getP4(), 100.0)


_R.reg("res://gd_core_items/Exclusive/BrassKnuckles.gd", Exclusive__BrassKnuckles)
_R.reg("BrassKnuckles", Exclusive__BrassKnuckles)

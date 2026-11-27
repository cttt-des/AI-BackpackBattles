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
if "_base_cls_DeathScythe_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_DeathScythe_2





class DeathScythe_2(_base_cls_DeathScythe_2):

	resource_path = "res://gd_core_items/DeathScythe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.critBonusActive = False
		self._poisonThreshold = 0
		self.activationParticles = None

	@property
	def poisonThreshold(self):
		return self._poisonThreshold
	@poisonThreshold.setter
	def poisonThreshold(self, v):
		self._poisonThreshold = int(v)

	def canAffect(self, item):
		return item.gainsStack(_H_1)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.opponent(), "character_poison_changed", "onOpponentPoisonChanged")
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_2, 1)


	def onOpponentPoisonChanged(self, _amount, _event):
		curPoison = self.opponent().getPoison()

		if not self.critBonusActive and curPoison >= self.poisonThreshold:
			self.setState(True)
			self.changeCritChancePercent(self.getChance())


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _critBonusActive):
		if _critBonusActive:
			pass
		else:
			pass
		self.critBonusActive = _critBonusActive

	def _readyInit(self):
		super()._readyInit()
		self.poisonThreshold = self.getP1()


_R.reg("res://gd_core_items/DeathScythe.gd", DeathScythe_2)
_R.reg("DeathScythe", DeathScythe_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Poison
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

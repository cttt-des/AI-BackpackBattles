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
if "_base_cls_Exclusive__InnerPower" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__InnerPower





class Exclusive__InnerPower(_base_cls_Exclusive__InnerPower):

	resource_path = "res://gd_core_items/Exclusive/InnerPower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healAmpAcc = 0.0
		self.speedAcc = 0.0
		self.luck = None
		self.empower = None
		self.healAmpPerLuck = None
		self.speedPerEmpower = None
		self.healAmpMax = None
		self.speedMax = None


	def canAffect(self, item):
		return item.hasCooldown() or item.canHealOrLifesteal()


	def onCombatStart(self):
		self.giveLucky(self.luck)
		self.giveEmpower(self.empower)
		self.activate()


	def onPrepare(self):
		self.healAmpAcc = 0
		self.speedAcc = 0
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")


	def onLuckChanged(self, amount, event):
		before = min(self.healAmpAcc, self.healAmpMax)
		dif = amount * self.healAmpPerLuck
		self.healAmpAcc += dif

		healAmpToGive = min(self.healAmpAcc, self.healAmpMax) - before
		if healAmpToGive != 0:
			for item in _iter(self.getAffectedItems()):
				item.changeHealAmp(healAmpToGive)



	def onEmpowerChanged(self, amount, event):
		before = min(self.speedAcc, self.speedMax)
		dif = amount * self.speedPerEmpower
		self.speedAcc += dif

		speedToGive = min(self.speedAcc, self.speedMax) - before
		if speedToGive != 0:
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(speedToGive)


	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))
		self.healAmpPerLuck = _div__loc(self.getP('healamp'), 100.0)
		self.speedPerEmpower = _div__loc(self.getP('speed'), 100.0)
		self.healAmpMax = _div__loc(self.getP('max1'), 100.0)
		self.speedMax = _div__loc(self.getP('max2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/InnerPower.gd", Exclusive__InnerPower)
_R.reg("InnerPower", Exclusive__InnerPower)

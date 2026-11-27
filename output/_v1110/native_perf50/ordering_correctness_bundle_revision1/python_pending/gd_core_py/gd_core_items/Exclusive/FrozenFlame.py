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
if "_base_cls_Exclusive__FrozenFlame" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__FrozenFlame





class Exclusive__FrozenFlame(_base_cls_Exclusive__FrozenFlame):

	resource_path = "res://gd_core_items/Exclusive/FrozenFlame.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affected2Item = None
		self._heatCounter = 0
		self.gatedItems = { "Spell Scroll Frostbolt": 2, "Book of Ice": 2, "Frostbite": 1, "Frozen Buckler": 1, "Ice Armor": 1, "Ice Dragon": 1, "Spell Scroll Ice": 1, "Magic Mirror": 1, "Ice Flower": 1, "Devouring Sphere": 1, "Snowmaster": 1 }
		self._heatNeeded = 0
		self._coldPerHeat = 0
		self.critSeverityPerCold = None

	@property
	def heatCounter(self):
		return self._heatCounter
	@heatCounter.setter
	def heatCounter(self, v):
		self._heatCounter = int(v)
	@property
	def heatNeeded(self):
		return self._heatNeeded
	@heatNeeded.setter
	def heatNeeded(self, v):
		self._heatNeeded = int(v)
	@property
	def coldPerHeat(self):
		return self._coldPerHeat
	@coldPerHeat.setter
	def coldPerHeat(self, v):
		self._coldPerHeat = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def canAffect_secondary(self, item):
		return item.canDamage()


	def onPrepare(self):
		self.heatCounter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")

		self.affected2Item = self.getFirstAffectedItem(_H_2)
		if self.affected2Item:
			self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")


	def onCombatStart(self):
		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveBlock(numAffected * self.getBlock())
		self.activate()


	def onHeatChanged(self, amount, event):
		_div__loc = _div
		if amount > 0:
			self.heatCounter += amount
			relHeat = _div__loc(float(self.heatCounter), self.heatNeeded)
			cold = int(relHeat) * self.coldPerHeat
			self.heatCounter %= self.heatNeeded
			if cold > 0:
				self.inflictCold(cold, event)
				self.showCooldownSmooth(_div__loc(float(self.heatCounter), self.heatNeeded), True)
			else:
				self.showCooldownSmooth(relHeat, False)


	def onOpponentColdChanged(self, amount, _event):

		self.affected2Item.changeCritChancePercent(amount * self.getChance())
		self.affected2Item.addCritSeverity(amount * self.critSeverityPerCold)


	def getGatedDescriptor(self, rarity):
		return None

	def getRelatedItemColumns(self):
		return 4


	def getRelatedItemHeight(self):
		return 200

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = self.getP("heat")
		self.coldPerHeat = self.getP("cold")
		self.critSeverityPerCold = _div(self.getP('critdam'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/FrozenFlame.gd", Exclusive__FrozenFlame)
_R.reg("FrozenFlame", Exclusive__FrozenFlame)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

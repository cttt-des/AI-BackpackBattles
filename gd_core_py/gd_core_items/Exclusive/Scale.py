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
if "_base_cls_Exclusive__Scale" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Scale





class Exclusive__Scale(_base_cls_Exclusive__Scale):

	resource_path = "res://gd_core_items/Exclusive/Scale.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regen = None
		self.mana = None
		self.speedPerGold = None
		self.maxGoldDif = None
		self.equilibriumSpeed = None
		self.leftCounter = None
		self.rightCounter = None
		self.leftCounterDefaultPos = None
		self.rightCounterDefaultPos = None


	def ready_deferred(self):
		super().ready_deferred()
		self.updateCounterPositions()


	def canAffect(self, item):
		return True


	def canAffect_secondary(self, item):
		return True


	def getCounterValue(self, color=GD_DEFAULT):
		_iter__loc = _iter
		if color is GD_DEFAULT:
			color = _H_1
		gold = 0
		if self.placed:
			for item in _iter__loc(self.getAffectedItems(color)):
				gold += item.getPrice()
		else:
			for item in _iter__loc(self.getAffectedItems_nocache(color)):
				gold += item.getPrice()
		return gold


	def getCounterValue2(self):
		return self.getCounterValue(_H_2)


	def onPrepare(self):
		_iter__loc = _iter
		c1 = self.getCounterValue()
		c2 = self.getCounterValue2()
		self.addSpeed(self.speedPerGold * min(c1, c2))
		if abs(c1 - c2) <= self.maxGoldDif:
			for item in _iter__loc(self.getAffectedItems()):
				item.addSpeed(self.equilibriumSpeed)
			for item in _iter__loc(self.getAffectedItems(_H_2)):
				item.addSpeed(self.equilibriumSpeed)


	def doCooldownEffect(self):
		curRegen = self.character().getRegeneration()
		curMana = self.character().getMana()
		if curMana < curRegen:
			self.giveMana(self.mana)
		elif curRegen < curMana:
			self.giveRegeneration(self.regen)
		else:
			if self.ctx.util.flip():
				self.giveMana(self.mana)
			else:
				self.giveRegeneration(self.regen)
		self.activate()


	def updateScale(self):
		c1 = self.getCounterValue()
		c2 = self.getCounterValue2()
		if abs(c1 - c2) <= self.maxGoldDif:
			pass
		elif c1 > c2:
			pass
		else:
			pass


	def onAffectedItemAdded(self, item, color):
		color = int(color)
		self.updateScale()


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		self.updateScale()


	def onAddToInventory(self):
		self.updateScale()


	def onRemoveFromInventory(self):
		pass


	def updateCounterPositions(self):
		pass


	def rotateTo(self, targetRotation, duration=0.15):
		super().rotateTo(targetRotation, duration)
		self.updateCounterPositions()


	def onDraggedWithParentEnd(self):
		super().onDraggedWithParentEnd()
		self.updateCounterPositions()


	def onCalcTradeChance(self):
		pass

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.mana = int(self.getP("mana"))
		self.speedPerGold = _div__loc(self.getP('speed'), 100.0)
		self.maxGoldDif = int(self.getP("gold"))
		self.equilibriumSpeed = _div__loc(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Scale.gd", Exclusive__Scale)
_R.reg("Scale", Exclusive__Scale)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

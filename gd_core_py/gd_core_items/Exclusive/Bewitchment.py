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
if "_base_cls_Exclusive__Bewitchment" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Bewitchment





class Exclusive__Bewitchment(_base_cls_Exclusive__Bewitchment):

	resource_path = "res://gd_core_items/Exclusive/Bewitchment.gd"

	def _init_fields(self):
		super()._init_fields()
		self.typesDict = None
		self.manaNeeded = None
		self.numDebuffs = None
		self.bonusPoison = None
		self.bonusBlind = None
		self.bonusCold = None


	def canAffect(self, item):
		return (item.hasType(_H_1) or 
				item.hasType(_H_2) or 
				item.hasType(_H_3))


	def onPrepare(self):
		self.typesDict = self.countTypes(self.getAffectedItems())


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_nature", "")
			descr = descr.replace("$n_dark", "")
			descr = descr.replace("$n_ice", "")
			return descr

		self.typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_H_1])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_H_2])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_H_3])

		return descr


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)

			leastStacks = self.getLeastStacks(self.numDebuffs, self.opponent(),
				_H_4.getDebuffs())

			if self.rollChance(self.getChance() * self.typesDict[_H_1]):
				self.ctx.util.dictAdd(leastStacks, _H_5, self.bonusPoison)

			if self.rollChance(self.getChance() * self.typesDict[_H_2]):
				self.ctx.util.dictAdd(leastStacks, _H_6, self.bonusBlind)

			if self.rollChance(self.getChance() * self.typesDict[_H_3]):
				self.ctx.util.dictAdd(leastStacks, _H_7, self.bonusCold)

			for debuffType in (leastStacks if leastStacks.__class__ is list else _iter(leastStacks)):
				self.giveStacks(self.opponent(), debuffType, leastStacks[debuffType], event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.numDebuffs = int(self.getP("debuffs"))
		self.bonusPoison = int(self.getP("poison"))
		self.bonusBlind = int(self.getP("blind"))
		self.bonusCold = int(self.getP("cold"))


_R.reg("res://gd_core_items/Exclusive/Bewitchment.gd", Exclusive__Bewitchment)
_R.reg("Bewitchment", Exclusive__Bewitchment)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
_H_4 = _R.C("CoreConst")
try:
	_H_5 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_7 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_7 = _HoistPending(_he)

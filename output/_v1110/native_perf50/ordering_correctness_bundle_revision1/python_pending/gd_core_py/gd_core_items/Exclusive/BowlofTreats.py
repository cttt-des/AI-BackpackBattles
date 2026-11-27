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
if "_base_cls_Exclusive__BowlofTreats" not in globals():
	from ..Food import Food_2 as _base_cls_Exclusive__BowlofTreats





class Exclusive__BowlofTreats(_base_cls_Exclusive__BowlofTreats):

	resource_path = "res://gd_core_items/Exclusive/BowlofTreats.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedBonusGiven = 0.0
		self.speedBonus = None
		self.maxSpeedBonus = None


	def canAffect_global(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.speedBonusGiven = 0.0

		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				item.giveDoubleActivationChance(self.getChance())


	def doCooldownEffect(self):
		self.giveRandomBuffs(self.getP1())
		if self.speedBonusGiven < self.maxSpeedBonus:
			for item in _iter(self.getAffectedItems()):
				curBonus = min(self.speedBonus, self.maxSpeedBonus - self.speedBonusGiven)
				item.addSpeed(_div(curBonus, 100))

			self.speedBonusGiven += self.speedBonus
		self.activate()


	def getGatedDescriptor(self, rarity):
		itemName = None

		if rarity >= _H_2:
			rarity = self.ctx.util.pickRandomElement([_H_3, _H_4, _H_5])

		if rarity == _H_3:
				itemName = "Rat"
		elif rarity == _H_4:
				itemName = "Squirrel"
		elif rarity == _H_5:
				itemName = "Hedgehog"

		return self.ctx.item_book.getDescriptor(itemName)

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = self.getP2()
		self.maxSpeedBonus = self.getP3()


_R.reg("res://gd_core_items/Exclusive/BowlofTreats.gd", Exclusive__BowlofTreats)
_R.reg("BowlofTreats", Exclusive__BowlofTreats)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Rarity.Legendary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Rarity.Common
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Rarity.Rare
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Rarity.Epic
except AttributeError as _he:
	_H_5 = _HoistPending(_he)

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
if "_base_cls_Exclusive__RandomLoadoutBag" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__RandomLoadoutBag





class Exclusive__RandomLoadoutBag(_base_cls_Exclusive__RandomLoadoutBag):

	resource_path = "res://gd_core_items/Exclusive/RandomLoadoutBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mainBags = { _H_1: ["Ranger Bag", "Vineweave Basket"], _H_2: ["Storage Coffin", "Relic Case"], _H_3: ["Fire Pit", "Portable Altar"], _H_4: ["Berserker Bag", "Toolbox"], _H_5: ["Scholar Bag", "Puzzlebox"], _H_6: ["Bag of Giving", "Sewing Case"], _H_7: ["Engineer Box", "Engineer Bag 2"] }
		self.compensationValue = { _H_1: [0, 0], _H_2: [1, 0], _H_3: [2, 1], _H_4: [1, 0], _H_5: [0, 0], _H_6: [0, 0], _H_7: [0, 0] }
		self.excludeNames = [ "Acorn Collar", "Unstable Recombobulator", "Draconic Orb", "Stone Skin Potion", "Divine Potion" ]
		self.bagCells = []

	bagRarityWeights = {
		_R.C("CoreConst").Rarity.Common: 2, 
		_R.C("CoreConst").Rarity.Rare: 0.5, 
		_R.C("CoreConst").Rarity.Epic: 0.2, 
		_R.C("CoreConst").Rarity.Legendary: 0.1, 
		_R.C("CoreConst").Rarity.Godly: 0.05, 
	}

	def addBagWherePossible(self, bag, startPos):
		pass

	def addItemWherePossible(self, item):
		pass

	def shopOpened(self):
		pass

	def prepareParticles(self):
		if self.ownerType == _H_8:
			self.ctx.util.callDelayed(self, "createRevealParticles", 0.4)


	def createRevealParticles(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass



_R.reg("res://gd_core_items/Exclusive/RandomLoadoutBag.gd", Exclusive__RandomLoadoutBag)
_R.reg("RandomLoadoutBag", Exclusive__RandomLoadoutBag)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Classes.Ranger
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Classes.Reaper
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Classes.Pyromancer
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Classes.Berserker
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Classes_Full.Mage
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").Classes_Full.Adventurer
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_7 = _R.C("CoreConst").Classes_Full.Engineer
except AttributeError as _he:
	_H_7 = _HoistPending(_he)
try:
	_H_8 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_8 = _HoistPending(_he)

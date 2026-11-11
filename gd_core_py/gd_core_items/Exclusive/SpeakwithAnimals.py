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
if "_base_cls_Exclusive__SpeakwithAnimals" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SpeakwithAnimals





class Exclusive__SpeakwithAnimals(_base_cls_Exclusive__SpeakwithAnimals):

	resource_path = "res://gd_core_items/Exclusive/SpeakwithAnimals.gd"

	def _init_fields(self):
		super()._init_fields()
		self.petDescriptors = [[], [], [], [], []]
		self.salesChance = None

	pets = [
		"Rat", "Squirrel", "Rat Chef", "Hedgehog", "Squirrel Archer", 
		"Hyper Hedgehog", "Carrot Goobert", "Snowmaster", "Forest Dragon", 
		"Toad", "Poison Goobert", "Poison Frog", "Ruby Chonk", "Frog Prince", 
		"Crow", "Ice Dragon", 
		"Courage Puppy", "Wisdom Puppy", "Power Puppy", 
		"Armored Courage Puppy", "Armored Wisdom Puppy", "Armored Power Puppy", 
		"Cheese Goobert", "Steel Dragon", 
		"Chili Goobert", "Fire Shelly", "Phoenix", "Phoenix2", 
		"Emerald Whelp", "Sapphire Whelp", "Amethyst Whelp", "Obsidian Dragon", 
		"Cat Spirit", "Owl Spirit", "Badger Spirit", "Cupcake Goobert", "Cupcake Dragon", 
		"Broccoli Goobert", "Dragon Knight", "Jynx Staff", 
		"Robodog", "Toast Goobert", "Mecha Bat", "Thunder Drake", 
		"Goobling", "Shelly", "Steel Goobert", "Blood Goobert", "Ruby Whelp", 
	]

	def onSaleRoll(self, item):
		pass

	def getGatedDescriptor(self, rarity):
		pass

	def canAffect(self, item):
		return item.hasType(_H_1)


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItems()):
			item.giveDoubleActivationChance(self.getChance())

		self.activate()


	def getRelatedItems(self):
		return self.ctx.util.flatten(self.petDescriptors)


	def getRelatedItemColumns(self):
		return 6


	def getRelatedItemHeight(self):
		return 100

	def _readyInit(self):
		super()._readyInit()
		self.salesChance = _div(self.getP('sale'), 100.0)
		for pet in (self.pets if self.pets.__class__ is list else _iter(self.pets)):
			desc = self.ctx.item_book.getDescriptor(pet)
			if desc.isReleased():
				self.petDescriptors[desc.getRarity()].append(desc)



_R.reg("res://gd_core_items/Exclusive/SpeakwithAnimals.gd", Exclusive__SpeakwithAnimals)
_R.reg("SpeakwithAnimals", Exclusive__SpeakwithAnimals)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

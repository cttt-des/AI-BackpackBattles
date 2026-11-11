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
if "_base_cls_Piggybank_2" not in globals():
	from .Item import Item_2 as _base_cls_Piggybank_2





class Piggybank_2(_base_cls_Piggybank_2):

	resource_path = "res://gd_core_items/Piggybank.gd"

	def _init_fields(self):
		super()._init_fields()
		self.piggyPinataDescriptor = None
		self.hammerDescriptor = None
		self.thorsHammerDescriptor = None


	def onShopEntered(self):
		self.giveGold(self.getP1())
		self.explodeRandomly()


	def explodeRandomly(self):
		if not self.isBaseItem() and not self.isBoundAsIngredient() and self.hasPinata():
			if self.ctx.util.flipPercent(self.piggyPinataDescriptor.shopChance):
				self.explode()
				self.inventory.removeItem(self)
				self.discard()


	def canAffect(self, item):
		return item.hasStartofBattle()


	def onCombatStart(self):
		self.giveMaxHealth(self.getP_m("maxhealth") * self.getNumAffectedItems())
		self.consume()


	def hasPinata(self):
		return self.ctx.item_book.isItemInInventory(self.piggyPinataDescriptor)


	def isSmashRecipe(self):
		return (self.curRecipe.ingredients[0] == self.hammerDescriptor or 
				self.curRecipe.ingredients[0] == self.thorsHammerDescriptor)


	def getFusionItemName(self):
		if self.isSmashRecipe() and self.hasPinata():
			return self.ctx.util.tr("Piggy Pinata_CRAFT")
		return super().getFusionItemName()


	def allowGeneratingFusionItem(self):
		if self.isSmashRecipe() and self.hasPinata():
			return False
		return True


	def explode(self):
		pass

	def finishFusing(self):

		if self.isSmashRecipe():
			self.explode()

		super().finishFusing()


	def getShopPriority(self):
		return _H_1

	def _readyInit(self):
		super()._readyInit()
		self.piggyPinataDescriptor = self.ctx.item_book.getDescriptor("Piggy Pinata")
		self.hammerDescriptor = self.ctx.item_book.getDescriptor("Hammer")
		self.thorsHammerDescriptor = self.ctx.item_book.getDescriptor("Thors Hammer")


_R.reg("res://gd_core_items/Piggybank.gd", Piggybank_2)
_R.reg("Piggybank", Piggybank_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.Lowest
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

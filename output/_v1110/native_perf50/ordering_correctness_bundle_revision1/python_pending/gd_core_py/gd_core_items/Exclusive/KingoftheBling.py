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
if "_base_cls_Exclusive__KingoftheBling" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__KingoftheBling





class Exclusive__KingoftheBling(_base_cls_Exclusive__KingoftheBling):

	resource_path = "res://gd_core_items/Exclusive/KingoftheBling.gd"

	def _init_fields(self):
		super()._init_fields()
		self.amuletsBoosted = 0
		self.chanceAcc = 0.0
		self.relatedItems = None
		self.salesChance = None


	def canAffect(self, item):
		return (item.isA(self.ctx.item_book.getDescriptor("Magic Ring")) or 
				item.isA(self.ctx.item_book.getDescriptor("Superior Ring")))


	def onBought(self):
		pass

	def getData(self):
		return self.amuletsBoosted


	def setData(self, data):
		if data != None:
			self.amuletsBoosted = data


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.ctx.item_book.getDescriptor("Amulet Unidentified"):
			self.amuletsBoosted -= 1


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())
			item.changeAmplificiationChancePercent_allDebuffs(self.getChance())


	def onSaleRoll(self, item):
		pass

	def getRestockItem(self):
		pass

	def getRelatedItems(self):
		return self.relatedItems


	def rollShopChance(self, shopChance=GD_DEFAULT):
		if shopChance is GD_DEFAULT:
			shopChance = self.descriptor.shopChance
		if self.chanceAcc > self.ctx.rng.randf_range(85, 125):
			self.chanceAcc = 0
			return True

		roll = super().rollShopChance(shopChance)
		if roll:
			self.chanceAcc = 0
			return True
		else:
			self.chanceAcc += shopChance
			return False

	def _readyInit(self):
		super()._readyInit()
		self.relatedItems = [
			self.ctx.item_book.getDescriptor("Magic Ring"), 
			self.ctx.item_book.getDescriptor("Amulet Unidentified"), 
			self.ctx.item_book.getDescriptor("Blood Amulet"), 
		]
		self.salesChance = _div(self.getP('sales'), 100.0)


_R.reg("res://gd_core_items/Exclusive/KingoftheBling.gd", Exclusive__KingoftheBling)
_R.reg("KingoftheBling", Exclusive__KingoftheBling)

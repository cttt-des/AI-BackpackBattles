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
if "_base_cls_Exclusive__Stoned" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Stoned





class Exclusive__Stoned(_base_cls_Exclusive__Stoned):

	resource_path = "res://gd_core_items/Exclusive/Stoned.gd"

	def _init_fields(self):
		super()._init_fields()
		self.protectionActive = False
		self.boostedStones = 0
		self.damReductionGiven = 0.0
		self.stoneDescriptor = None
		self.stoneGolemDescriptor = None
		self.stoneArmorDescriptor = None
		self.blockFactor = None
		self.damReduction = None


	def getData(self):
		return self.boostedStones


	def setData(self, data):
		if data != None:
			self.boostedStones = data


	def onBought(self):
		self.boostedStones = 4


	def canBlock(self):
		return True


	def canAffect_global(self, item):
		return item.hasTag(_H_1) or item.isA(self.stoneGolemDescriptor)


	def onPrepare(self):

		self.connectForCombat(self.character(), "character_block_changed", "onBlockChanged")
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.protectionActive = False
		self.damReductionGiven = 0.0

		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				self.connectForCombat(item, "attacked", "onStoneAttacked")


	def onStoneAttacked(self, damageRes):
		if damageRes.hasHit():
			self.giveBlock(ceil(damageRes.damage * self.blockFactor), True, damageRes.event)
			self.miniActivate()


	def onDamaged(self, _healthChange, _event):
		self.checkBlock()


	def onBlockChanged(self, _amount, _event):
		self.checkBlock()


	def checkBlock(self):
		if self.protectionActive:
			if self.character().getBlock() == 0:
				self.protectionActive = False

				self.character().changeDamageResistance( - self.damReduction)
				self.damReductionGiven -= self.damReduction
		else:
			if self.character().getBlock() > 0:
				self.protectionActive = True

				self.character().changeDamageResistance(self.damReduction)
				self.damReductionGiven += self.damReduction






	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.stoneDescriptor:
			self.boostedStones -= 1

	def _readyInit(self):
		super()._readyInit()
		self.stoneDescriptor = self.ctx.item_book.getDescriptor("Stone")
		self.stoneGolemDescriptor = self.ctx.item_book.getDescriptor("Stone Golem")
		self.stoneArmorDescriptor = self.ctx.item_book.getDescriptor("Stone Armor")
		self.blockFactor = _div(self.getP('blockfordam'), 100.0)
		self.damReduction = self.getP("damreduction")


_R.reg("res://gd_core_items/Exclusive/Stoned.gd", Exclusive__Stoned)
_R.reg("Stoned", Exclusive__Stoned)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Tag.Stone
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

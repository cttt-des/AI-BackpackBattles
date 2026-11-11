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
if "_base_cls_Exclusive__UniquelyUnique" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__UniquelyUnique





class Exclusive__UniquelyUnique(_base_cls_Exclusive__UniquelyUnique):

	resource_path = "res://gd_core_items/Exclusive/UniquelyUnique.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.baseSpeed = None
		self.bonusSpeed = None


	def onBought(self):
		self.boosted = 2


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_secondary(self, item):
		return (item.getRarity() == _H_1 or 
			item.isA(self.ctx.item_book.getDescriptor("Platin Customer Card")) or 
			item.isA(self.ctx.item_book.getDescriptor("Customer Card")))


	def onPrepare(self):
		affectedItems = self.getAffectedItems()
		if not (not affectedItems):
			affectedItems[0].addSpeed(self.baseSpeed + self.getNumAffectedItems(_H_2) * self.bonusSpeed)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.ctx.item_book.getDescriptor("Customer Card"):
			self.boosted -= 1

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.baseSpeed = _div__loc(self.getP('speed'), 100.0)
		self.bonusSpeed = _div__loc(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/UniquelyUnique.gd", Exclusive__UniquelyUnique)
_R.reg("UniquelyUnique", Exclusive__UniquelyUnique)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Unique
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

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
if "_base_cls_Exclusive__Halberd" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Halberd





class Exclusive__Halberd(_base_cls_Exclusive__Halberd):

	resource_path = "res://gd_core_items/Exclusive/Halberd.gd"

	def _init_fields(self):
		super()._init_fields()
		self._totalBlockRemoval = 0
		self.dam = None
		self.blockRemoval = None
		self.blockFactor = None

	@property
	def totalBlockRemoval(self):
		return self._totalBlockRemoval
	@totalBlockRemoval.setter
	def totalBlockRemoval(self, v):
		self._totalBlockRemoval = int(v)

	def canBlock(self):
		return True


	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		self.totalBlockRemoval = self.blockRemoval * (self.getNumAffectedItems() + self.getNumEmptyAffectedCells())

		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_1, self.blockFactor)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.dam)


	def onPreDealDamage_late(self, damageRes):

		curBlock = self.opponent().getBlock()
		toRemove = min(curBlock, self.totalBlockRemoval)
		self.removeBlock(toRemove, damageRes.event)
		toGive = self.totalBlockRemoval - toRemove
		if toGive > 0:
			self.giveBlock(toGive, True, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.dam = self.getP("dam")
		self.blockRemoval = self.getP("blockremoval")
		self.blockFactor = _div(self.getP('blockfactor'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Halberd.gd", Exclusive__Halberd)
_R.reg("Halberd", Exclusive__Halberd)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Block
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

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
if "_base_cls_PotionBelt_2" not in globals():
	from .Bag import Bag_2 as _base_cls_PotionBelt_2





class PotionBelt_2(_base_cls_PotionBelt_2):

	resource_path = "res://gd_core_items/PotionBelt.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedPotions = []
		self._numConsumed = 0

	@property
	def numConsumed(self):
		return self._numConsumed
	@numConsumed.setter
	def numConsumed(self, v):
		self._numConsumed = int(v)

	def onPrepare(self):
		self.numConsumed = 0
		self.affectedPotions.clear()
		affectedItems = self.getItemsInside()
		for item in (affectedItems if affectedItems.__class__ is list else _iter(affectedItems)):
			if self.canApplyEffect(item):
				self.affectedPotions.append(item)
				self.connectForCombat(item, "potion_emptied", "onPotionEmptied")


	def onPotionEmptied(self, _potion):
		numBuffs = 0
		active = False
		self.numConsumed += 1

		if self.numConsumed == 1:
			numBuffs = 1
			active = True

		elif self.numConsumed == 4:
			self.cleanseRandomDebuffs(self.getP1())
			active = True

		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			numBuffs += int(self.ctx.item_book.getDescriptor("Bagtacular").getP("buffs"))
			active = True

		if numBuffs > 0:
			self.giveRandomBuffs(numBuffs)

		if active:
			self.activate()










	def canApplyEffect(self, toItem):
		return toItem.hasType(_H_1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PotionBelt.gd", PotionBelt_2)
_R.reg("PotionBelt", PotionBelt_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Potion
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

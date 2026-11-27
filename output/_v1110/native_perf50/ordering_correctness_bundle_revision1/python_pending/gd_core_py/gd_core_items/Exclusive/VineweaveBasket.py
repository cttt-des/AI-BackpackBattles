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
if "_base_cls_Exclusive__VineweaveBasket" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__VineweaveBasket





class Exclusive__VineweaveBasket(_base_cls_Exclusive__VineweaveBasket):

	resource_path = "res://gd_core_items/Exclusive/VineweaveBasket.gd"

	def _init_fields(self):
		super()._init_fields()
		self.salesRound1 = None
		self.salesRound2 = None
		self.salesChance = None
		self.salesParticles = None


	def canApplyEffect(self, toItem):
		return toItem.hasType(_H_1)


	def onPrepare(self):
		healAmp = self.getP("healamp")
		healAmp += self.getP("ampbonus") * self.getNumAffectedInside()
		self.character().addHealingEfficiency(_div(healAmp, 100.0))


	def onShopOpened(self):
		if self.ctx.cur_round == self.salesRound1 or self.ctx.cur_round == self.salesRound2:
			pass


	def onSaleRoll(self, _item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.salesRound1 = int(self.getP("round1"))
		self.salesRound2 = int(self.getP("round2"))
		self.salesChance = _div(self.getP('sales'), 100.0)
		if self.ownerType == _H_2:
			pass



_R.reg("res://gd_core_items/Exclusive/VineweaveBasket.gd", Exclusive__VineweaveBasket)
_R.reg("VineweaveBasket", Exclusive__VineweaveBasket)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

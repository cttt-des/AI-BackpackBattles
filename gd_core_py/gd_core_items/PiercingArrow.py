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
if "_base_cls_PiercingArrow_2" not in globals():
	from .Item import Item_2 as _base_cls_PiercingArrow_2





class PiercingArrow_2(_base_cls_PiercingArrow_2):

	resource_path = "res://gd_core_items/PiercingArrow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.critDam = None
		self.blockRemoval = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.canActivate()


	def onPrepare(self):
		_iter__loc = _iter
		for item in _iter__loc(self.getAffectedItems()):
			item.addCritSeverity(self.critDam)

			self.connectForCombat(item, "pre_deal_damage_late", "onItemAttacks")

		for item in _iter__loc(self.getAffectedItems(_H_1)):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onItemAttacks(self, damageRes):
		if damageRes.wasCriticalHit():
			damageRes.damageSource.origin.removeBlock(self.blockRemoval)


	def onItemActivated(self, event):
		if self.rollChance():
			self.giveLucky(1)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.critDam = _div(self.getP1(), 100.0)
		self.blockRemoval = int(self.getP2())


_R.reg("res://gd_core_items/PiercingArrow.gd", PiercingArrow_2)
_R.reg("PiercingArrow", PiercingArrow_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

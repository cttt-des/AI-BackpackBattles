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
if "_base_cls_Exclusive__PuzzlebagT" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__PuzzlebagT





class Exclusive__PuzzlebagT(_base_cls_Exclusive__PuzzlebagT):

	resource_path = "res://gd_core_items/Exclusive/PuzzlebagT.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.affectedInside = []
		self.refund = None


	def canApplyEffect(self, toItem):
		return toItem.usesBuffs()


	def onPrepare(self):
		self.affectedInside = self.getAffectedItemsInside()
		if not (not self.affectedInside):
			self.connectToCharacterBuffs("onBuffChanged")
			for buff in _iter(_H_1.getBuffs()):
				self.usedStacks[buff] = 0.0


	def onBuffChanged(self, amount, event):
		if (amount < 0 and event.getParam("used", False) and 
			event.origin in self.affectedInside):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used * self.refund
			toRefund = int(gd_round(self.usedStacks[buffType]))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund, event)
				self.miniActivate()


	def getBagEffect(self, number):
		descr = self.ctx.util.tra(self.getName() + "_BAGEFFECT")
		descr = self.insertParameter(descr, "p_buff", self.getP("buff") * number)
		return descr

	def _readyInit(self):
		super()._readyInit()
		self.refund = _div(self.getP('buff'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PuzzlebagT.gd", Exclusive__PuzzlebagT)
_R.reg("PuzzlebagT", Exclusive__PuzzlebagT)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")

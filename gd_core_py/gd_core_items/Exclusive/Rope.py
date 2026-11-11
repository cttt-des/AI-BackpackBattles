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
if "_base_cls_Exclusive__Rope" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Rope





class Exclusive__Rope(_base_cls_Exclusive__Rope):

	resource_path = "res://gd_core_items/Exclusive/Rope.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedUpItem = None
		self.speedTimer = None
		self.speedPerTrigger = None
		self.maxSpeed = None


	def canAffect(self, item):
		return item.canActivate()


	def canAffect_secondary(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		_iter__loc = _iter
		for item in _iter__loc(self.getAffectedItems(_H_1)):
			self.speedUpItem = item

		if self.speedUpItem != None:
			for triggerItem in _iter__loc(self.getAffectedItems()):
				self.connectForCombat(triggerItem, "activated", "onTriggerItemActivated")


	def onTriggerItemActivated(self, event):
		curSpeed = self.ctx.rope_speedups.get(self.speedUpItem, 0.0)
		speedLeft = self.maxSpeed - curSpeed
		if speedLeft > 0:
			self.speedUpItem.addSpeed(min(speedLeft, self.speedPerTrigger))

		self.ctx.util.dictAdd(self.ctx.rope_speedups, self.speedUpItem, self.speedPerTrigger)
		self.speedTimer.start(self.getP_m("dur"))
		self.miniActivate()


	def onSpeedTimeout(self):
		self.ctx.util.dictSub(self.ctx.rope_speedups, self.speedUpItem, self.speedPerTrigger)
		curSpeed = self.ctx.rope_speedups.get(self.speedUpItem, 0.0)
		speedLeft = self.maxSpeed - curSpeed
		if speedLeft > 0:
			self.speedUpItem.reduceSpeed(min(speedLeft, self.speedPerTrigger))


	def onCombatEnd(self):
		self.speedTimer.stop()
		self.speedUpItem = None

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedTimer = self.newItemTimer("SpeedTimer", "onSpeedTimeout", True)
		self.speedPerTrigger = _div__loc(self.getP('speed'), 100.0)
		self.maxSpeed = _div__loc(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Rope.gd", Exclusive__Rope)
_R.reg("Rope", Exclusive__Rope)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

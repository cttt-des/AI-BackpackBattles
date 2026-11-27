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
if "_base_cls_Exclusive__AmuletofAgility" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__AmuletofAgility





class Exclusive__AmuletofAgility(_base_cls_Exclusive__AmuletofAgility):

	resource_path = "res://gd_core_items/Exclusive/AmuletofAgility.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.bonusSpeed = None
		self.buffTimer = None
		self.refund = None

	amuletColor = Color(0.639216, 0.635294, 0.215686)

	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffChanged")
		for buff in _iter(_H_1.getBuffs()):
			self.usedStacks[buff] = 0.0


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		self.buffTimer.start(self.getP_m("dur"))
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.bonusSpeed)
		self.activate()


	def onBuffTimeout(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onBuffChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used * self.refund
			toRefund = int(gd_round(self.usedStacks[buffType]))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund, event)
				self.miniActivate()


	def onCombatEnd(self):
		self.buffTimer.stop()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.bonusSpeed = _div__loc(self.getP('speed'), 100.0)
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffTimeout", True)
		self.refund = _div__loc(self.getP('refund'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofAgility.gd", Exclusive__AmuletofAgility)
_R.reg("AmuletofAgility", Exclusive__AmuletofAgility)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")

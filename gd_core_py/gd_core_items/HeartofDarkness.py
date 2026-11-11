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
if "_base_cls_HeartofDarkness_2" not in globals():
	from .Item import Item_2 as _base_cls_HeartofDarkness_2





class HeartofDarkness_2(_base_cls_HeartofDarkness_2):

	resource_path = "res://gd_core_items/HeartofDarkness.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.regenNeeded = None
		self.numStealedBuffs = None
		self.fillAnimation = None


	def canAffect(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP('darkspeed'), 100.0))


	def doCooldownEffect(self):
		self.stealRandomBuff(self.numStealedBuffs, None, _H_3.getBuffs(), _H_4)
		self.activate()


	def onRegenChanged(self, amount, event):
		if amount > 0 and not self.activated and self.character().getRegeneration() >= self.regenNeeded:
			self.setState(True, True)
			self.useRegeneration(self.regenNeeded, event)
			self.giveMaxHealth(self.getP_m("maxhealth"), event)
			self.giveEmpower(self.getP("empower"), event)
			self.opponent().reduceHealingEfficiency(_div(self.getP('healreduction'), 100.0))


	def onShopEntered(self):
		self.onStateChanged(False)


	def getTriggerPriority(self):
		return _H_1


	def onStateChanged(self, filled):
		if self.activated == filled:
			return
		self.activated = filled

		if filled:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP("regent"))
		self.numStealedBuffs = int(self.getP("buffsteal"))


_R.reg("res://gd_core_items/HeartofDarkness.gd", HeartofDarkness_2)
_R.reg("HeartofDarkness", HeartofDarkness_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
_H_3 = _R.C("CoreConst")
try:
	_H_4 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_4 = _HoistPending(_he)

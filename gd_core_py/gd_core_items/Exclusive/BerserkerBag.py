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
if "_base_cls_Exclusive__BerserkerBag" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__BerserkerBag





class Exclusive__BerserkerBag(_base_cls_Exclusive__BerserkerBag):

	resource_path = "res://gd_core_items/Exclusive/BerserkerBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.battleRageSpeed = None
		self.damageResistance = None


	def canApplyEffect(self, toItem):
		return toItem.hasCooldown()


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onDamaged(self, _damage, event):
		if not self.activated:
			if self.character().getRelativeHealth() < self.healthThreshold:
				self.activated = True
				self.character().startBattleRage(self, self.getP_m("dur_rage"), event)
				self.activate()


	def onBattleRageStarted(self, _event):
		self.character().changeDamageResistance(self.damageResistance)
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.character().changeDamageResistance( - self.damageResistance)
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.reduceSpeed(self.battleRageSpeed)


	def getTriggerPriority(self):
		return _H_1 + 10

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0) - 0.0001
		self.battleRageSpeed = _div__loc(self.getP('speed_rage'), 100.0)
		self.damageResistance = self.getP("damresistance")


_R.reg("res://gd_core_items/Exclusive/BerserkerBag.gd", Exclusive__BerserkerBag)
_R.reg("BerserkerBag", Exclusive__BerserkerBag)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

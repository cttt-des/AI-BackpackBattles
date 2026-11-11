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
if "_base_cls_Exclusive__WolfBadge" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__WolfBadge





class Exclusive__WolfBadge(_base_cls_Exclusive__WolfBadge):

	resource_path = "res://gd_core_items/Exclusive/WolfBadge.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.battleRageSpeed = None
		self.battleRageDamReduction = None


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onDamaged(self, _damage, event):
		if not self.activated:
			if self.character().getRelativeHealth() < self.healthThreshold:
				self.activated = True
				self.character().startBattleRage(self, self.getP_m("dur"), event)
				self.activate()


	def onBattleRageStarted(self, _event):
		self.character().changeDamageResistance(self.battleRageDamReduction)
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.character().changeDamageResistance( - self.battleRageDamReduction)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.battleRageSpeed)


	def getTriggerPriority(self):
		return _H_1 + 10


	def getRelatedItems(self):
		pass

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healthThreshold = _div__loc(self.getP1(), 100.0) - 0.0001
		self.battleRageSpeed = _div__loc(self.getP3(), 100.0)
		self.battleRageDamReduction = self.getP4()


_R.reg("res://gd_core_items/Exclusive/WolfBadge.gd", Exclusive__WolfBadge)
_R.reg("WolfBadge", Exclusive__WolfBadge)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

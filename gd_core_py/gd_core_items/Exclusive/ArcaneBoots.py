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
if "_base_cls_Exclusive__ArcaneBoots" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ArcaneBoots





class Exclusive__ArcaneBoots(_base_cls_Exclusive__ArcaneBoots):

	resource_path = "res://gd_core_items/Exclusive/ArcaneBoots.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedTimer = None
		self.healthThreshold = None
		self.manaNeeded = None
		self.luck = None
		self.empower = None
		self.bonusSpeed = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			if self.character().getMana() >= self.manaNeeded:
				self.hasActivated = True
				event2 = self.useMana(self.manaNeeded)
				self.giveLucky(self.luck, event2)
				self.giveEmpower(self.empower, event2)
				self.giveBlock(self.getBlock(), True, event2)

				for item in _iter(self.getAffectedItems()):
					item.addSpeed(self.bonusSpeed)

				self.speedTimer.start(self.getP_m("dur_speed"))

				self.consume()


	def getTriggerPriority(self):
		return _H_1 + 2


	def onSpeedTimerTimeout(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onCombatEnd(self):
		self.speedTimer.stop()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedTimer = self.newItemTimer("SpeedTimer", "onSpeedTimerTimeout", False)
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0) - 0.0001
		self.manaNeeded = int(self.getP("manat"))
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))
		self.bonusSpeed = _div__loc(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ArcaneBoots.gd", Exclusive__ArcaneBoots)
_R.reg("ArcaneBoots", Exclusive__ArcaneBoots)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

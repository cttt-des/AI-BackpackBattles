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
if "_base_cls_Exclusive__BadgerSpirit" not in globals():
	from .SpiritCompanion import SpiritCompanion as _base_cls_Exclusive__BadgerSpirit





class Exclusive__BadgerSpirit(_base_cls_Exclusive__BadgerSpirit):

	resource_path = "res://gd_core_items/Exclusive/BadgerSpirit.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.manaNeeded = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _healthChange, event):
		if not self.activated and self.character().getRelativeHealth() < self.healthThreshold:
			self.activated = True
			self.heal(_div(self.character().getMaxHealth() * self.getP_m('heal'), 100.0), event)


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveMaxHealth(self.getP_m("maxhealth") + self.getNumAffectedItems() * 
				self.getP_m("maxhealth_bonus"), event)
		self.activate()


	def playPickupSound(self):
		# decomp Items/Exclusive/BadgerSpirit.gd:30 Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/BadgerSpirit.gd:34 Sound.playSound(dropSound, volume - 6, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0)
		self.manaNeeded = int(self.getP("manat"))


_R.reg("res://gd_core_items/Exclusive/BadgerSpirit.gd", Exclusive__BadgerSpirit)
_R.reg("BadgerSpirit", Exclusive__BadgerSpirit)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

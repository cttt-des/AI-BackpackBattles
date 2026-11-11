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
if "_base_cls_DemonicFlask_2" not in globals():
	from .Potion import Potion_2 as _base_cls_DemonicFlask_2





class DemonicFlask_2(_base_cls_DemonicFlask_2):

	resource_path = "res://gd_core_items/DemonicFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None


	def canDamage(self):
		return True


	def onTriggerPotion(self, triggerEvent=None):
		dam = self.opponent().getDebuffStacks()
		dam *= self.getP2()
		dam = ceil(dam)
		self.dealEffectDamage(dam, triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_damaged", "onDamaged")


	def onDamaged(self, healthChange, event):
		if self.isEmpty():
			return

		if self.opponent().getRelativeHealth() < self.healthThreshold:

			self.drink()

			self.triggerPotion(event)

			affected = self.getAffectedItems()
			if not (not affected):
				affected[0].triggerPotion(event)
				affected[0].miniActivate()

			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001
		self.damageSource = _H_1().setItem(self)




_R.reg("res://gd_core_items/DemonicFlask.gd", DemonicFlask_2)
_R.reg("DemonicFlask", DemonicFlask_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")

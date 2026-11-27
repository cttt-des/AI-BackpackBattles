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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_DragonEgg_2" not in globals():
	from .Item import Item_2 as _base_cls_DragonEgg_2





class DragonEgg_2(_base_cls_DragonEgg_2):

	resource_path = "res://gd_core_items/DragonEgg.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hatchParticles = None
		self.firePulse = None
		self.whelpName = None
		self.roundsToHatch = None
		self.reflectionStacks = None


	def getData(self):
		return self.roundsToHatch


	def setData(self, data):
		self.roundsToHatch = data
		self.updateEgg()


	def updateEgg(self):
		if self.canHatch():
			self.showCooldownSmooth(1.0, False)
		else:
			self.showCooldownSmooth(1.0 - _div(self.roundsToHatch, self.getP2()), False)


	def isNextToNest(self):
		if self.placed:
			for item in _iter(self.inventory.getItems()):
				if item.getName() == "Dragon Nest":
					return self in item.getAffectedItems()

		return False


	def readyToTransform(self):
		return self.canHatch()


	def canHatch(self):
		return (self.roundsToHatch == 0 or 
				(self.roundsToHatch == 1 and self.isNextToNest()))


	def shopEntered(self, craft):
		super().shopEntered(craft)

	def startHatching(self):
		self.ctx.util.callDelayed(self, "hatch", self.TRANSFORMATION_DUR - 0.1)
		for shadow in (self.shadows if self.shadows.__class__ is list else _iter(self.shadows)):
			shadow.offset = Vector2(0, - 138)


	def hatch(self):
		self.ctx.defer(self, "hatch_deferred", [])


	def hatch_deferred(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.roundsToHatch = self.getP2()
		self.updateEgg()



_R.reg("res://gd_core_items/DragonEgg.gd", DragonEgg_2)
_R.reg("DragonEgg", DragonEgg_2)
_R.reg("DragonEgg", DragonEgg_2)

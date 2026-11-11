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
if "_base_cls_Exclusive__SmithingForDummies" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SmithingForDummies





class Exclusive__SmithingForDummies(_base_cls_Exclusive__SmithingForDummies):

	resource_path = "res://gd_core_items/Exclusive/SmithingForDummies.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boostedWhetstones = 0
		self.whetstoneDescriptor = None
		self.staminaReduction = None
		self.bonusDamage = None


	def getData(self):
		return self.boostedWhetstones


	def setData(self, data):
		if data != None:
			self.boostedWhetstones = data


	def canAffect(self, item):
		return item.isWeapon() and item.isCrafted()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.changeStaminaFactor(self.staminaReduction)
			if item.canDamage():
				item.addBonusDamage(self.bonusDamage)
		self.activate()


	def onBought(self):
		pass

	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.whetstoneDescriptor:
			self.boostedWhetstones -= 1


	def _readyInit(self):
		super()._readyInit()
		self.whetstoneDescriptor = self.ctx.item_book.getDescriptor("Whetstone")
		self.staminaReduction = - self.getP("stamina")
		self.bonusDamage = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/SmithingForDummies.gd", Exclusive__SmithingForDummies)
_R.reg("SmithingForDummies", Exclusive__SmithingForDummies)

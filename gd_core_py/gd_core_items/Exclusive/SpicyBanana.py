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
if "_base_cls_Exclusive__SpicyBanana" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SpicyBanana





class Exclusive__SpicyBanana(_base_cls_Exclusive__SpicyBanana):

	resource_path = "res://gd_core_items/Exclusive/SpicyBanana.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaUsed = 0.0
		self.boostedBananas = 0
		self.bananaDescriptor = None
		self.manananaDescriptor = None
		self.heatPerActivation = None
		self.staminaForHeal = None


	def canAffect(self, item):
		return item.isA(self.bananaDescriptor) or item.isA(self.manananaDescriptor)


	def onBought(self):
		self.boostedBananas = 3


	def getData(self):
		return self.boostedBananas


	def setData(self, data):
		if data != None:
			self.boostedBananas = data


	def onPrepare(self):

		for banana in _iter(self.getAffectedItems()):
			self.connectForCombat(banana, "activated", "onBananaActivated")

		self.staminaUsed = 0
		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")


	def onBananaActivated(self, event):
		if self.rollChance():
			self.giveHeat(self.heatPerActivation, event)
			self.activate()


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount
		healTicks = floor(_div(self.staminaUsed, self.staminaForHeal))
		if healTicks > 0:
			self.heal(healTicks * self.getP_m("heal"))
			self.staminaUsed -= healTicks * self.staminaForHeal
			self.miniActivate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.bananaDescriptor:
			self.boostedBananas -= 1

	def _readyInit(self):
		super()._readyInit()
		self.bananaDescriptor = self.ctx.item_book.getDescriptor("Banana")
		self.manananaDescriptor = self.ctx.item_book.getDescriptor("Mananana")
		self.heatPerActivation = int(self.getP("heat"))
		self.staminaForHeal = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/SpicyBanana.gd", Exclusive__SpicyBanana)
_R.reg("SpicyBanana", Exclusive__SpicyBanana)

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
if "_base_cls_Exclusive__Bazooka" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Bazooka





class Exclusive__Bazooka(_base_cls_Exclusive__Bazooka):

	resource_path = "res://gd_core_items/Exclusive/Bazooka.gd"

	def _init_fields(self):
		super()._init_fields()
		self._activationsLeft = 0
		self.stunResistActive = False
		self.heatNeeded = None
		self.luck = None
		self.luckNeeded = None
		self.uses = None

	@property
	def activationsLeft(self):
		return self._activationsLeft
	@activationsLeft.setter
	def activationsLeft(self, v):
		self._activationsLeft = int(v)

	def onPrepare(self):
		self.activationsLeft = self.uses
		self.stunResistActive = False
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if (self.activationsLeft > 0 and 
				self.character().getHeat() >= self.heatNeeded):

				self.activationsLeft -= 1

				self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
				self.useHeat(self.heatNeeded, damageRes.event)
				self.giveLucky(self.luck, damageRes.event)
				self.giveBlock(self.getBlock(), True, damageRes.event)
				self.ctx.bus.flushLoggingQueue()

				self.stun(self.getP_m("dur_stun"), damageRes.event)
				self.character().stun(self.getP_m("dur_stunself"), self, damageRes.event)


	def onLuckChanged(self, amount, event):
		if amount > 0 and not self.stunResistActive and self.character().getLucky() >= self.luckNeeded:
			self.character().changeStunResistance(self.getChance())
			self.stunResistActive = True

		elif amount < 0 and self.stunResistActive and self.character().getLucky() < self.luckNeeded:
			self.character().changeStunResistance( - self.getChance())
			self.stunResistActive = False

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP("heatt"))
		self.luck = int(self.getP("luck"))
		self.luckNeeded = int(self.getP("luckt"))
		self.uses = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/Bazooka.gd", Exclusive__Bazooka)
_R.reg("Bazooka", Exclusive__Bazooka)

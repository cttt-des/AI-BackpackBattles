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
if "_base_cls_Exclusive__Sloth" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Sloth





class Exclusive__Sloth(_base_cls_Exclusive__Sloth):

	resource_path = "res://gd_core_items/Exclusive/Sloth.gd"

	def _init_fields(self):
		super()._init_fields()
		self.awakenNow = False
		self.speed_v = None
		self.buffs = None
		self.buffsAmulet = None
		self.light1 = None
		self.light2 = None
		self.particles1 = None
		self.particles2 = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.speed_v)


	def onCombatStart(self):
		m = self.getP_m("maxhealth_base")
		m += self.getNumAffectedItems() * self.getP_m("maxhealth_item")
		m = gd_round(_div(m, 100.0) * self.character().getMaxHealth())
		self.giveMaxHealth(m)
		self.activate()


	def trigger(self):
		self.awakenNow = True
		super().trigger()


	def doCooldownEffect(self):
		if self.awakenNow:
			self.setState(True)
			self.giveAllBuffs(self.buffs)
			self.stun(self.getP_m("dur_stun"))
			self.awakenNow = False
			self.onAfterEffectFinished()
		else:
			self.giveAllBuffs(self.buffsAmulet)
			self.stun(self.getP_m("dur_stun_amulet"))
			self.activate()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, awakened):
		if awakened:
			pass
		else:
			pass


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		descr = descr.replace("$s[", "[shake]")
		descr = descr.replace('$s]', '[/shake]')
		return descr


	def _readyInit(self):
		super()._readyInit()
		self.speed_v = _div(self.getP('speed'), 100.0)
		self.buffs = int(self.getP("buffs"))
		self.buffsAmulet = int(self.getP("buffs_amulet"))


_R.reg("res://gd_core_items/Exclusive/Sloth.gd", Exclusive__Sloth)
_R.reg("Sloth", Exclusive__Sloth)

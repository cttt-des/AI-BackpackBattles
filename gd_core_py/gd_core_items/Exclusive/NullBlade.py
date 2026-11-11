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
if "_base_cls_Exclusive__NullBlade" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__NullBlade





class Exclusive__NullBlade(_base_cls_Exclusive__NullBlade):

	resource_path = "res://gd_core_items/Exclusive/NullBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.regenNeeded = None
		self.dam = None
		self.buffs = None
		self.speedBonus = None
		self.distortion = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getLucky() >= self.luckNeeded:
				self.useLucky(self.luckNeeded)
				damageRes.damage += self.dam
				self.addBonusDamage(self.dam)

			if self.character().getRegeneration() >= self.regenNeeded:
				self.useRegeneration(self.regenNeeded)
				self.removeRandomBuffs(self.buffs)
				if self.opponent().getBuffStacks() == 0:
					self.addSpeed(self.speedBonus)



	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()
		return res

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.regenNeeded = int(self.getP("regent"))
		self.dam = int(self.getP("dam"))
		self.buffs = int(self.getP("buffs"))
		self.speedBonus = _div(self.getP('speed'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/NullBlade.gd", Exclusive__NullBlade)
_R.reg("NullBlade", Exclusive__NullBlade)

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
if "_base_cls_Exclusive__ObsidianDragon" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__ObsidianDragon





class Exclusive__ObsidianDragon(_base_cls_Exclusive__ObsidianDragon):

	resource_path = "res://gd_core_items/Exclusive/ObsidianDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatCounter = 0
		self.affectedWeapon = None
		self.heatNeeded = None
		self.bonusDam = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.affectedWeapon = self.getFirstAffectedItem()
		self.heatCounter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if amount > 0:
			self.heatCounter += amount
			proccs = _div(self.heatCounter, self.heatNeeded)
			if proccs > 0:
				self.heatCounter %= self.heatNeeded

				self.addBonusDamage(self.bonusDam * proccs)
				if self.affectedWeapon != None:
					self.affectedWeapon.addCritTokens(proccs)

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP1())
		self.bonusDam = int(self.getP2())


_R.reg("res://gd_core_items/Exclusive/ObsidianDragon.gd", Exclusive__ObsidianDragon)
_R.reg("ObsidianDragon", Exclusive__ObsidianDragon)

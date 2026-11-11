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
if "_base_cls_Exclusive__VampiricPotion" not in globals():
	from ..Potion import Potion_2 as _base_cls_Exclusive__VampiricPotion





class Exclusive__VampiricPotion(_base_cls_Exclusive__VampiricPotion):

	resource_path = "res://gd_core_items/Exclusive/VampiricPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None
		self.dam = None
		self.vampirism = None


	def onPrepare(self):

		self.connectForCombat(self.character(), "character_damaged", "onPlayerDamaged")
		self.connectForCombat(self.opponent(), "character_damaged", "onPlayerDamaged")



	def onPlayerDamaged(self, _healthChange, event):
		if self.isEmpty():
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			relHealth2 = self.opponent().getRelativeHealth()
			if relHealth2 < self.healthThreshold:
				self.consumePotion()


	def onTriggerPotion(self, triggerEvent=None):

		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0), triggerEvent)
		self.giveVampirism(self.vampirism, triggerEvent)


	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0)
		self.dam = self.getP3()
		self.vampirism = int(self.getP2())


_R.reg("res://gd_core_items/Exclusive/VampiricPotion.gd", Exclusive__VampiricPotion)
_R.reg("VampiricPotion", Exclusive__VampiricPotion)

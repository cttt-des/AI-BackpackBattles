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
if "_base_cls_Manathirst_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_Manathirst_2





class Manathirst_2(_base_cls_Manathirst_2):

	resource_path = "res://gd_core_items/Manathirst.gd"

	def _init_fields(self):
		super()._init_fields()
		self._manaGained = 0
		self.fillingTween = None
		self.filling = None
		self.fillingGlow = None
		self.fillingHeight = None
		self.fillingAnimation = None
		self.manaNeededForLifesteal = None
		self.dam = None
		self.mana = None

	@property
	def manaGained(self):
		return self._manaGained
	@manaGained.setter
	def manaGained(self, v):
		self._manaGained = int(v)

	def onPrepare(self):
		self.manaGained = 0

		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")
		self.tweenFilling(0)


	def tweenFilling(self, relHeight):
		pass

	def onManaChanged(self, amount, event):
		_div__loc = _div
		if amount > 0:
			self.manaGained += amount
			if self.manaGained >= self.manaNeededForLifesteal:
				self.manaGained -= self.manaNeededForLifesteal
				self.stealLife(self.dam + self.character().getVampirism(), _div__loc(self.getP_m('lifesteal'), 100.0), event)

			relHeight = _div__loc(self.manaGained, self.manaNeededForLifesteal)
			self.tweenFilling(relHeight)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.giveMana(self.mana, damageRes.event)


	def onShopEntered(self):
		self.tweenFilling(1)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeededForLifesteal = self.getP1()
		self.dam = self.getP("dam")
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Manathirst.gd", Manathirst_2)
_R.reg("Manathirst", Manathirst_2)

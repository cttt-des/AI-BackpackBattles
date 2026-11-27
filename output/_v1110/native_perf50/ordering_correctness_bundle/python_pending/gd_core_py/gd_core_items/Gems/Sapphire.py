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
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Gems__Sapphire" not in globals():
	from .Gem import Gem as _base_cls_Gems__Sapphire





class Gems__Sapphire(_base_cls_Gems__Sapphire):

	resource_path = "res://gd_core_items/Gems/Sapphire.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaCounter = 0
		self.spectral = False
		self.manaNeeded = None

	gemColor = Color(0.8, 0.8, 3)

	def doCooldownEffect(self):
		self.inflictCold(self.getP5())
		self.onAfterEffectFinished()


	def prepareWeapon(self):
		self.spectral = False
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_late", "preAttack")
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def preAttack(self, damageRes):

		self.spectral = self.rollChance()
		if self.spectral:
			damageRes.damageSource.makeSpectral()


	def onAttack(self, damageRes):
		if self.spectral and damageRes.hasHit():
			self.giveMana(self.getP1(), damageRes.event)
			self.inflictCold(self.getP4(), damageRes.event)
			self.miniActivate()


	def prepareArmor(self):
		self.manaCounter = 0
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onManaChanged(self, amount, event):
		if amount > 0:
			self.manaCounter += amount
			relMana = _div(self.manaCounter, self.manaNeeded)
			block = relMana * self.getP3()
			self.manaCounter %= self.manaNeeded
			if block > 0:
				self.giveBlock(self.getGemPower() * block, event)
				self.miniActivate()
				self.showCooldownSmooth(relMana, True)
			else:
				self.showCooldownSmooth(relMana, False)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP2())


_R.reg("res://gd_core_items/Gems/Sapphire.gd", Gems__Sapphire)
_R.reg("Sapphire", Gems__Sapphire)

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
if "_base_cls_Exclusive__BadgerRune" not in globals():
	from ..Gems.Gem import Gem as _base_cls_Exclusive__BadgerRune





class Exclusive__BadgerRune(_base_cls_Exclusive__BadgerRune):

	resource_path = "res://gd_core_items/Exclusive/BadgerRune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackSpeedBonus = None
		self._damageReduction = 0
		self.staminaReduction = None

	@property
	def damageReduction(self):
		return self._damageReduction
	@damageReduction.setter
	def damageReduction(self, v):
		self._damageReduction = int(v)
	gemColor = Color(0.845703, 0.420593, 0.062767)

	def isBattleRageItem(self):
		return self.getGemMode() == self.GemMode.Armor


	def prepareWeapon(self):
		self.connectForCombat(self.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			self.getItem().addSpeed(self.attackSpeedBonus)
			self.miniActivate()


	def prepareArmor(self):
		self.connectForCombat(self.character(), "pre_take_damage", "preTakeDamage")


	def preTakeDamage(self, damageRes):
		if damageRes.triggerOnAttacked() and self.character().isBattleRaging():
			damageRes.applyDamageReduction(gd_round(self.getGemPower() * self.damageReduction), self)
			self.miniActivate()


	def hasCooldown(self):
		return False


	def prepareInventory(self):
		for item in _iter(self.inventory.getItems()):

			item.changeStaminaFactor( - self.staminaReduction)











	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.attackSpeedBonus = _div(self.getP('attackspeed'), 100.0)
		self.damageReduction = self.getP("damreduction")
		self.staminaReduction = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/BadgerRune.gd", Exclusive__BadgerRune)
_R.reg("BadgerRune", Exclusive__BadgerRune)

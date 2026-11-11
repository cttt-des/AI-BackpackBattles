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
if "_base_cls_Gems__Skull" not in globals():
	from .Gem import Gem as _base_cls_Gems__Skull





class Gems__Skull(_base_cls_Gems__Skull):

	resource_path = "res://gd_core_items/Gems/Skull.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None

	gemColor = Color(0.912109, 0.904984, 0.904984)

	def prepareInventory(self):
		self.activated = False
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onOpponentDamaged(self, _healthChange, event):
		if not self.activated:
			if self.opponent().getRelativeHealth() <= self.healthThreshold:
				self.activated = True
				self.heal(self.getP_m("heal"), event)
				self.giveEmpower(self.getP3(), event)
				self.activate()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance2():
			self.stealRandomBuff(1)
			self.miniActivate()


	def prepareArmor(self):
		_ch = self.character()
		_ch.changeDebuffResistChances(self.getGemPower() * self.getChance())
		_ch.changeCritResistance(self.getGemPower() * self.getChance())


	def hasCooldown(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001


_R.reg("res://gd_core_items/Gems/Skull.gd", Gems__Skull)
_R.reg("Skull", Gems__Skull)

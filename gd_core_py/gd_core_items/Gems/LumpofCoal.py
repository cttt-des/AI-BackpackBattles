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
if "_base_cls_Gems__LumpofCoal" not in globals():
	from .Gem import Gem as _base_cls_Gems__LumpofCoal





class Gems__LumpofCoal(_base_cls_Gems__LumpofCoal):

	resource_path = "res://gd_core_items/Gems/LumpofCoal.gd"

	gemColor = Color(0.132813, 0.132813, 0.132813)

	def canBlock(self):
		return False


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_early", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			damageRes.damage += self.getP1()
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeDebuffResistStacks(gd_round(self.getGemPower()))


	def combatStartArmor(self):
		self.giveBlock(gd_round(self.getGemPower() * self.getBlock()))
		self.miniActivate()


	def doCooldownEffect(self):
		self.giveRandomBuffs(1)
		self.inflictRandomDebuffs(1)
		self.onAfterEffectFinished()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Gems/LumpofCoal.gd", Gems__LumpofCoal)
_R.reg("LumpofCoal", Gems__LumpofCoal)

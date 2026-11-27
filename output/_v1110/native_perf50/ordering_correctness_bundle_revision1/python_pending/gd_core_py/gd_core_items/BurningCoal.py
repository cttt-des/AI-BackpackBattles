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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_BurningCoal_2" not in globals():
	from .Gems.Gem import Gem as _base_cls_BurningCoal_2





class BurningCoal_2(_base_cls_BurningCoal_2):

	resource_path = "res://gd_core_items/BurningCoal.gd"

	gemColor = Color(1.5, 1, 0.7)

	def canBlock(self):
		return False


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_early", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			damageRes.damage += self.getP1()
			self.giveHeat(self.getP2())
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeResistStacks(_H_1, gd_round(self.getP3() * self.getGemPower()))


	def combatStartArmor(self):
		self.giveBlock(self.getBlock() * self.getGemPower())
		self.miniActivate()


	def doCooldownEffect(self):
		self.giveHeat(self.getP4())
		self.cleanseRandomDebuffs(self.getP5())
		self.onAfterEffectFinished()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BurningCoal.gd", BurningCoal_2)
_R.reg("BurningCoal", BurningCoal_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

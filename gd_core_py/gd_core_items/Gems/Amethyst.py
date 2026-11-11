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
if "_base_cls_Gems__Amethyst" not in globals():
	from .Gem import Gem as _base_cls_Gems__Amethyst





class Gems__Amethyst(_base_cls_Gems__Amethyst):

	resource_path = "res://gd_core_items/Gems/Amethyst.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healReduction = None
		self.buffRemoval = None

	gemColor = Color(1.977344, 0.8, 3)

	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(1)
		self.activate()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.removeRandomBuffs(self.buffRemoval, damageRes.event)
			self.miniActivate()


	def prepareArmor(self):
		self.opponent().reduceHealingEfficiency(self.getGemPower() * self.healReduction)


	def getBaseDescription(self, wrapInColor=True):
		if self.getRarity() == _H_1:
			return self.insertParameters(self.ctx.util.tra("Perfect Amethyst_DESCR"), wrapInColor)
		else:
			return super().getBaseDescription(wrapInColor)

	def _readyInit(self):
		super()._readyInit()
		self.healReduction = _div(self.getP1(), 100.0)
		self.buffRemoval = int(self.getP2())


_R.reg("res://gd_core_items/Gems/Amethyst.gd", Gems__Amethyst)
_R.reg("Amethyst", Gems__Amethyst)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Godly
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

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
if "_base_cls_Exclusive__LightningStaff" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__LightningStaff





class Exclusive__LightningStaff(_base_cls_Exclusive__LightningStaff):

	resource_path = "res://gd_core_items/Exclusive/LightningStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackCounter = 0
		self.manaCost = None
		self.permDamBonus = None
		self.chargeDamBase = None
		self.chargeDamPerTile = None
		self.numAttacks = None

	chargeCells = [Vector2(0, - 2), Vector2(1, - 2), Vector2(2, - 1), Vector2(3, - 2), Vector2(4, - 1), Vector2(5, 0), Vector2(4, 1)]

	def onPrepare(self):
		self.attackCounter = 0


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			self.addBonusDamage(self.permDamBonus)

		self.attackCounter += 1

		if self.attackCounter == self.numAttacks:
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])
			self.attackCounter = 0


	def canAffect_lightning(self, item):
		return item.canBeEmpowered() or item.reactsToCharges()


	def emitCharge(self, speedFactor=1.0):
		event = self.activate(None, False)
		self.sendCharge(self.getP_m("dur"), self.chargeCells, speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.chargeDamBase, self.chargeDamPerTile)


	def chargedItemStatChange(self, item, value):
		item.addBonusDamage(value, False)

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = int(self.getP("manat"))
		self.permDamBonus = self.getP("dam")
		self.chargeDamBase = self.getP("dam_flat")
		self.chargeDamPerTile = self.getP("dam_tile")
		self.numAttacks = self.getP("num")


_R.reg("res://gd_core_items/Exclusive/LightningStaff.gd", Exclusive__LightningStaff)
_R.reg("LightningStaff", Exclusive__LightningStaff)

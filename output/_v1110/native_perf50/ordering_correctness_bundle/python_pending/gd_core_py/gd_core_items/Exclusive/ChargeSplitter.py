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
if "_base_cls_Exclusive__ChargeSplitter" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ChargeSplitter





class Exclusive__ChargeSplitter(_base_cls_Exclusive__ChargeSplitter):

	resource_path = "res://gd_core_items/Exclusive/ChargeSplitter.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.heatNeeded = None
		self.luck = None

	chargeCells1 = [Vector2( - 1, - 1), Vector2( - 2, - 1), Vector2( - 2, 0), Vector2( - 2, 1), Vector2( - 3, 1), Vector2( - 4, 1), Vector2( - 4, 0)]
	chargeCells2 = [Vector2( - 1, - 1), Vector2(0, - 1), Vector2(0, - 2), Vector2(0, - 3), Vector2(1, - 3), Vector2(2, - 3), Vector2(2, - 2)]

	def onPrepare(self):
		self.hasActivated = False


	def doCooldownEffect(self):
		if self.character().getHeat() >= self.heatNeeded:
			event = self.useHeat(self.heatNeeded)
			self.giveLucky(self.luck, event)
			self.giveBlock(self.getBlock(), True, event)

		self.onAfterEffectFinished()


	def canAffect_lightning(self, item):
		return item.gainsBuffs() or item.reactsToCharges()


	def onChargeReceived(self, _charge):
		if not self.hasActivated:
			self.hasActivated = True
			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells1, speedFactor, event)
		self.sendCharge(self.getP_m("dur"), self.chargeCells2, speedFactor, event)



	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.getChance(), self.getChance2())


	def chargedItemStatChange(self, item, value):
		item.changeAmplificiationChancePercent_allBuffs(value)

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP("heatt"))
		self.luck = int(self.getP("luck"))


_R.reg("res://gd_core_items/Exclusive/ChargeSplitter.gd", Exclusive__ChargeSplitter)
_R.reg("ChargeSplitter", Exclusive__ChargeSplitter)

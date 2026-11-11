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
if "_base_cls_Exclusive__ConTrapTron" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ConTrapTron





class Exclusive__ConTrapTron(_base_cls_Exclusive__ConTrapTron):

	resource_path = "res://gd_core_items/Exclusive/ConTrapTron.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedMalus = None
		self.cdAdvanceBase = None
		self.cdAdvanceBonus = None
		self.healthThreshold = None

	chargeCells1 = [Vector2( - 1, - 1), Vector2(0, - 2), Vector2(1, - 3), Vector2(2, - 2), Vector2(2, - 1)]
	chargeCells2 = [Vector2( - 1, 0), Vector2( - 1, 1), Vector2(0, 2), Vector2(1, 1), Vector2(2, 1)]

	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_lightning(self, item):
		return item.gainsBuffs() or item.reactsToCharges()


	def onPrepare(self):
		self.hasActivated = False
		item = self.getFirstAffectedItem()
		if item != None:
			item.reduceSpeed(self.speedMalus)

		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			self.emitCharge()
			self.ctx.bus.emitSignal(self, "charge_emitted", [self])

			item = self.getFirstAffectedItem()
			if item != None:
				cdAdvance = self.cdAdvanceBase
				if not item.isWeapon():
					cdAdvance += self.cdAdvanceBonus

				item.advanceCooldownSeconds(cdAdvance)


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		self.sendCharge(self.getP_m("dur"), self.chargeCells1, speedFactor, event)
		self.sendCharge(self.getP_m("dur"), self.chargeCells2, speedFactor, event)



	def onChargeEnteredCell(self, charge, cellIndex):
		self.changeChargedItemStat(charge, cellIndex, self.getChance(), self.getChance2())


	def chargedItemStatChange(self, item, value):
		item.changeAmplificiationChancePercent_allBuffs(value)


	def getTextureSize(self):
		return Vector2.ZERO

	def getSpriteOffset(self):
		return Vector2.ZERO

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedMalus = _div__loc(self.getP('speed'), 100.0)
		self.cdAdvanceBase = self.getP("cdadvance_base")
		self.cdAdvanceBonus = self.getP("cdadvance_bonus")
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0) - 0.0001


_R.reg("res://gd_core_items/Exclusive/ConTrapTron.gd", Exclusive__ConTrapTron)
_R.reg("ConTrapTron", Exclusive__ConTrapTron)

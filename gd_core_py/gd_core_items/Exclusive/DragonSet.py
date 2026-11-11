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
if "_base_cls_Exclusive__DragonSet" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__DragonSet





class Exclusive__DragonSet(_base_cls_Exclusive__DragonSet):

	resource_path = "res://gd_core_items/Exclusive/DragonSet.gd"

	def _init_fields(self):
		super()._init_fields()
		self.dragonArmorDescr = None
		self.dragonBootsDescr = None
		self.dragonClawsDescr = None
		self.armorDescr = None
		self.bootsDescr = None
		self.glovesDescr = None
		self.heat = None
		self.lifestealMax = None
		self.activeLight1 = None
		self.activeLight2 = None


	def onItemAdded(self, item):
		super().onItemAdded(item)
		self.checkItems()


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		self.checkItems()








	def onRemoveFromInventory(self):
		pass


	def checkItems(self):
		if self.countAllPlacedOfType(self.dragonArmorDescr) > 0:
			if self.countAllPlacedOfType(self.dragonBootsDescr) > 0:
				if self.countAllPlacedOfType(self.dragonClawsDescr) > 0:
					return



	def onPrepare(self):
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")

		if self.countAllInInventoryOfType(self.dragonArmorDescr) > 0:
			if self.countAllInInventoryOfType(self.dragonBootsDescr) > 0:
				if self.countAllInInventoryOfType(self.dragonClawsDescr) > 0:
						self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def onBattleRageStarted(self, _event):

		self.activateCooldown()


	def onBattleRageEnded(self, _event):

		self.deactivateCooldown()


	def doCooldownEffect(self):
		self.giveHeat(self.heat)
		self.activate()


	def onOpponentDamaged(self, damageRes):
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			curLifesteal = min(_div(self.getP_m("lifesteal"), 100.0) * self.character().getHeat(),
									self.lifestealMax)
			self.heal(ceil(curLifesteal * damageRes.damage), damageRes.event)


	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.dragonArmorDescr = self.ctx.item_book.getDescriptor("Dragonscale Armor")
		self.dragonBootsDescr = self.ctx.item_book.getDescriptor("Dragonskin Boots")
		self.dragonClawsDescr = self.ctx.item_book.getDescriptor("Dragon Claws")
		self.armorDescr = self.ctx.item_book.getDescriptor("Leather Armor")
		self.bootsDescr = self.ctx.item_book.getDescriptor("Leather Boots")
		self.glovesDescr = self.ctx.item_book.getDescriptor("Gloves of Haste")
		self.heat = int(self.getP("heat"))
		self.lifestealMax = _div(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/DragonSet.gd", Exclusive__DragonSet)
_R.reg("DragonSet", Exclusive__DragonSet)

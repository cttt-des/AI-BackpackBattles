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
if "_base_cls_DjinnLamp_2" not in globals():
	from .Item import Item_2 as _base_cls_DjinnLamp_2





class DjinnLamp_2(_base_cls_DjinnLamp_2):

	resource_path = "res://gd_core_items/DjinnLamp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.affectedWeapon = None
		self.stacksNeeded = None
		self.healthNeeded = None
		self.activationParticles = None

	numIngredients = 5.0

	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.activated = False
		self.affectedWeapon = None
		affectedItems = self.getAffectedItems()
		if not (not affectedItems):
			self.affectedWeapon = affectedItems[0]
			self.connectForCombat(self.character(), "character_block_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_spikes_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_mana_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_lucky_changed", "checkStacks")
			self.connectForCombat(self.character(), "character_damaged", "checkStacks")
			self.connectForCombat(self.character(), "character_healed", "checkStacks")


	def checkStacks(self, changeAmount, event):
		_div__loc = _div
		if self.activated:
			return

		progress = 0.0
		progress += _div__loc(min(self.character().getBlock(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div__loc(min(self.character().getSpikes(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div__loc(min(self.character().getMana(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div__loc(min(self.character().getLucky(), self.stacksNeeded), float(self.stacksNeeded))
		progress += _div__loc(min(self.character().getCurrentHealth() - 1, self.healthNeeded), float(self.healthNeeded))
		progress /= self.numIngredients

		if changeAmount > 0:

			if progress >= 0.9999:
				self.activated = True
				self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
				self.useBlock(self.stacksNeeded, event)
				self.useSpikes(self.stacksNeeded, event)
				self.useMana(self.stacksNeeded, event)
				self.useLucky(self.stacksNeeded, event)
				self.character().loseHealth(self.healthNeeded, self, event)
				bonusDamage = self.getP3()
				self.affectedWeapon.addBonusDamage(bonusDamage)
				dmgBuffEvent = self.ctx.combat_log.createEvent_DamageBuff(self, self.affectedWeapon, bonusDamage, self.character().playerId, event)
				self.ctx.bus.logEvent(dmgBuffEvent)
				self.ctx.bus.flushLoggingQueue()
				self.activate()


	def doCooldownEffect(self):
		_ch = self.character()
		numLucky = _ch.getLucky()
		numSpikes = _ch.getSpikes()
		numMana = _ch.getMana()

		if numLucky < numSpikes:
			if numLucky < numMana:

				self.giveLucky(1)
			else:

				self.giveMana(1)
		else:

			if numSpikes < numMana:

				self.giveSpikes(1)
			else:

				self.giveMana(1)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.stacksNeeded = self.getP1()
		self.healthNeeded = self.getP2()


_R.reg("res://gd_core_items/DjinnLamp.gd", DjinnLamp_2)
_R.reg("DjinnLamp", DjinnLamp_2)

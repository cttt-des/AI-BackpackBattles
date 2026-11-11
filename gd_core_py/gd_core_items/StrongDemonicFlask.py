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
if "_base_cls_StrongDemonicFlask_2" not in globals():
	from .Potion import Potion_2 as _base_cls_StrongDemonicFlask_2





class StrongDemonicFlask_2(_base_cls_StrongDemonicFlask_2):

	resource_path = "res://gd_core_items/StrongDemonicFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healingReductionTimer = None
		self.healingDebuff = None
		self.damPerDebuff = None
		self.playerHealthThreshold = None
		self.opponentHealthThreshold = None


	def canDamage(self):
		return True


	def onTriggerPotion(self, triggerEvent=None):
		self.opponent().reduceHealingEfficiency(self.healingDebuff)
		dam = self.opponent().getDebuffStacks() * self.damPerDebuff
		dam = ceil(dam)
		self.stealLife(dam, _div(self.getP_m('lifesteal'), 100.0), triggerEvent)
		self.healingReductionTimer.start(self.getP_m("dur"))


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_damaged", "onPlayerDamaged")
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onPlayerDamaged(self, healthChange, event):
		if self.isEmpty():
			return
		if self.character().getRelativeHealth() < self.playerHealthThreshold:
			self.drinkStrongDemonicFlask(event)


	def onOpponentDamaged(self, healthChange, event):
		if self.isEmpty():
			return
		if self.opponent().getRelativeHealth() < self.opponentHealthThreshold:
			self.drinkStrongDemonicFlask(event)


	def drinkStrongDemonicFlask(self, event):
		# ★ np25 evt12 面 AFFL 探针（双门控零耗链）：SDF 喝毒的 affected[0] 链定谳
		_aff = self.getAffectedItems()
		_aff_names = ""
		for _a in (_aff if _aff.__class__ is list else _iter(_aff)):
			_aff_names += String(_a.descriptor.identifier) + ","
		self.ctx.rng.trace_diag("AFFL", String(self.descriptor.identifier), "n=" + str(len(_aff)), _aff_names)

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion(event)
			affected[0].miniActivate()

		self.activate()


	def healingReductionTimeout(self):
		self.opponent().addHealingEfficiency(self.healingDebuff)


	def onCombatEnd(self):
		self.healingReductionTimer.stop()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healingReductionTimer = self.newItemTimer("HealingReductionTimer", "healingReductionTimeout", True)
		self.healingDebuff = _div__loc(self.getP3(), 100.0)
		self.damPerDebuff = self.getP("dam")
		self.playerHealthThreshold = _div__loc(self.getP('ownhpt'), 100.0) - 0.0001
		self.opponentHealthThreshold = _div__loc(self.getP('opphpt'), 100.0) - 0.0001


_R.reg("res://gd_core_items/StrongDemonicFlask.gd", StrongDemonicFlask_2)
_R.reg("StrongDemonicFlask", StrongDemonicFlask_2)

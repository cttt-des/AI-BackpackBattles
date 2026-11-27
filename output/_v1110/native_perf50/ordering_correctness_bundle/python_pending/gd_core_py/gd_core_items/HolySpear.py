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
if "_base_cls_HolySpear_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_HolySpear_2





class HolySpear_2(_base_cls_HolySpear_2):

	resource_path = "res://gd_core_items/HolySpear.gd"

	SpearState = EnumDict("SpearState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self._blockRemoval = 0
		self._cleanses = 0
		self._spearState = 0
		self.activationParticles = None
		self.buffTimer = None
		self._blockRemovalPerSlot = 0
		self.buffedSpeed = None
		self._manaCost = 0
		self.light = None

	@property
	def blockRemoval(self):
		return self._blockRemoval
	@blockRemoval.setter
	def blockRemoval(self, v):
		self._blockRemoval = int(v)
	@property
	def cleanses(self):
		return self._cleanses
	@cleanses.setter
	def cleanses(self, v):
		self._cleanses = int(v)
	@property
	def spearState(self):
		return self._spearState
	@spearState.setter
	def spearState(self, v):
		self._spearState = int(v)
	@property
	def blockRemovalPerSlot(self):
		return self._blockRemovalPerSlot
	@blockRemovalPerSlot.setter
	def blockRemovalPerSlot(self, v):
		self._blockRemovalPerSlot = int(v)
	@property
	def manaCost(self):
		return self._manaCost
	@manaCost.setter
	def manaCost(self, v):
		self._manaCost = int(v)

	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		numSlots = self.getNumEmptyAffectedCells() + self.getNumAffectedItems()
		self.blockRemoval = self.blockRemovalPerSlot * numSlots
		self.cleanses = numSlots

		self.setState(self.SpearState.Inactive)
		self.connectForCombat(self.character(), "character_mana_changed", "checkTrigger")
		self.connectForCombat(self.character(), "character_invulnerable_end", "onInvuEnded")


	def onPreDealDamage_late(self, damageRes):
		if damageRes.hasHit():
			self.removeBlock(self.blockRemoval)
			self.cleanseRandomDebuffs(self.cleanses)


	def onInvuEnded(self, triggerEvent):
		self.checkTrigger(0, triggerEvent)


	def checkTrigger(self, _amount, triggerEvent):
		if (self.spearState == self.SpearState.Inactive and 
			self.character().isVulnerable() and 
			self.checkMana(self.manaCost)):

			self.setState(self.SpearState.Active, True)
			invuDur = self.getP_m("dur_invu")
			self.character().makeInvulnerable(invuDur, self, triggerEvent)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, triggerEvent)
			self.addSpeed(_div(self.buffedSpeed, 100.0))



	def buffEnded(self):
		self.setState(self.SpearState.Used, True)
		self.reduceSpeed(_div(self.buffedSpeed, 100.0))


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.SpearState.Inactive)


	def onStateChanged(self, _spearState):
		if _spearState == self.SpearState.Inactive:
			pass

		elif _spearState == self.SpearState.Active:
			pass

		else:
			pass

		self.spearState = _spearState


	def getTriggerPriority(self):
		return _H_2 + 2

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blockRemovalPerSlot = self.getP1()
		self.buffedSpeed = self.getP3()
		self.manaCost = self.getP2()


_R.reg("res://gd_core_items/HolySpear.gd", HolySpear_2)
_R.reg("HolySpear", HolySpear_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Priority.Normal
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

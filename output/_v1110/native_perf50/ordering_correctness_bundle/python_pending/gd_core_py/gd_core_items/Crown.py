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
if "_base_cls_Crown_2" not in globals():
	from .Item import Item_2 as _base_cls_Crown_2





class Crown_2(_base_cls_Crown_2):

	resource_path = "res://gd_core_items/Crown.gd"

	CrownState = EnumDict("CrownState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self._crownState = 0
		self.activationParticles = None
		self.buffTimer = None
		self.manaCost = None
		self.light = None

	@property
	def crownState(self):
		return self._crownState
	@crownState.setter
	def crownState(self, v):
		self._crownState = int(v)

	def onPrepare(self):
		self.setState(self.CrownState.Inactive)
		self.connectForCombat(self.character(), "character_mana_changed", "checkTrigger")
		self.connectForCombat(self.character(), "character_invulnerable_end", "onInvuEnded")


	def onInvuEnded(self, triggerEvent):
		self.checkTrigger(0, triggerEvent)


	def checkTrigger(self, _amount, triggerEvent):
		if (self.crownState == self.CrownState.Inactive and 
			self.character().isVulnerable() and 
			self.checkMana(self.manaCost)):

			self.setState(self.CrownState.Active, True)
			invuDur = self.getP_m("dur_invu")
			event = self.character().makeInvulnerable(invuDur, self, triggerEvent)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, event)
			self.activate()


	def buffEnded(self):
		self.setState(self.CrownState.Used, True)


	def doCooldownEffect(self):
		self.cleanseBlind(1)
		self.heal()
		self.activate()


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.CrownState.Inactive)


	def onStateChanged(self, _crownState):
		if _crownState == self.CrownState.Inactive:
			pass

		elif _crownState == self.CrownState.Active:
			pass

		else:
			pass

		self.crownState = _crownState

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.manaCost = self.getP("mana")


_R.reg("res://gd_core_items/Crown.gd", Crown_2)
_R.reg("Crown", Crown_2)

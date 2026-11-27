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
if "_base_cls_Exclusive__BurningSpikes" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__BurningSpikes





class Exclusive__BurningSpikes(_base_cls_Exclusive__BurningSpikes):

	resource_path = "res://gd_core_items/Exclusive/BurningSpikes.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesAcc = 0
		self.affectedItemsDict = {}
		self.spikes = None
		self.heat = None
		self.spikesNeeded = None
		self.heatForSpikes = None


	def canAffect(self, item):
		return item.gainsStack(_H_1)


	def onPrepare(self):
		self.spikesAcc = 0
		self.affectedItemsDict = self.ctx.util.arrayAsIndexDict(self.getAffectedItems())

		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, amount, event):
		if amount > 0 and event.origin in self.affectedItemsDict:
			self.spikesAcc += amount
			numProccs = _div(self.spikesAcc, self.spikesNeeded)
			if numProccs > 0:
				self.giveHeat(self.heatForSpikes * numProccs)
				self.spikesAcc %= self.spikesNeeded
				self.miniActivate()


	def onCombatStart(self):
		self.giveSpikes(self.spikes)
		self.giveHeat(self.heat)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.heat = int(self.getP("heat"))
		self.spikesNeeded = int(self.getP("spikest"))
		self.heatForSpikes = int(self.getP("heat2"))


_R.reg("res://gd_core_items/Exclusive/BurningSpikes.gd", Exclusive__BurningSpikes)
_R.reg("BurningSpikes", Exclusive__BurningSpikes)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Spikes
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

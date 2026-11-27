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
if "_base_cls_ClawsofAttack_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_ClawsofAttack_2





class ClawsofAttack_2(_base_cls_ClawsofAttack_2):

	resource_path = "res://gd_core_items/ClawsofAttack.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackCounter = 0
		self.lastSpeedBonus = 0.0
		self.speedPerSpike = None
		self.numHits = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, _amount, _event):
		clawsBonus = min(self.speedPerSpike * self.character().getSpikes(), self.getP2())
		clawsBonus /= 100.0
		self.addSpeed(clawsBonus - self.lastSpeedBonus)
		self.lastSpeedBonus = clawsBonus


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.attackCounter += 1
			if self.attackCounter == self.numHits:
				self.giveEmpower(1)
				self.attackCounter = 0


	def onShopEntered(self):
		self.lastSpeedBonus = 0.0
		self.attackCounter = 0

	def _readyInit(self):
		super()._readyInit()
		self.speedPerSpike = self.getP1()
		self.numHits = int(self.getP3())


_R.reg("res://gd_core_items/ClawsofAttack.gd", ClawsofAttack_2)
_R.reg("ClawsofAttack", ClawsofAttack_2)

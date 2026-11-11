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
if "_base_cls_Exclusive__BigBloodthorne" not in globals():
	from ..Greatsword import Greatsword_2 as _base_cls_Exclusive__BigBloodthorne





class Exclusive__BigBloodthorne(_base_cls_Exclusive__BigBloodthorne):

	resource_path = "res://gd_core_items/Exclusive/BigBloodthorne.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damPerVampOrSpike = None
		self.regenNeeded = None
		self.vampirism = None
		self.spikes = None


	def onPrepare(self):
		super().onPrepare()
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onVampirismChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.damPerVampOrSpike)


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.damPerVampOrSpike)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getRegeneration() >= self.regenNeeded:
				self.useRegeneration(self.regenNeeded)
				self.giveVampirism(self.vampirism)
				self.giveSpikes(self.spikes)

	def _readyInit(self):
		super()._readyInit()
		self.damPerVampOrSpike = self.getP("dam")
		self.regenNeeded = int(self.getP("regent"))
		self.vampirism = int(self.getP("vampirism"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/BigBloodthorne.gd", Exclusive__BigBloodthorne)
_R.reg("BigBloodthorne", Exclusive__BigBloodthorne)

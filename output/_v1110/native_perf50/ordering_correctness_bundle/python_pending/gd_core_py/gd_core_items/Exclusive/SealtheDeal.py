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
if "_base_cls_Exclusive__SealtheDeal" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SealtheDeal





class Exclusive__SealtheDeal(_base_cls_Exclusive__SealtheDeal):

	resource_path = "res://gd_core_items/Exclusive/SealtheDeal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regenNeeded = None
		self.vampirism = None
		self.luckNeeded = None
		self.spikes = None
		self.manaNeeded = None
		self.empower = None
		self.tradeBonusValue = None


	def onCalcTradeChance(self):
		pass

	def doCooldownEffect(self):

		if self.character().getRegeneration() >= self.regenNeeded:
			event = self.useRegeneration(self.regenNeeded)
			self.giveVampirism(self.vampirism, event)

		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			self.giveSpikes(self.spikes, event)

		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveEmpower(self.empower, event)


		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP("regent"))
		self.vampirism = int(self.getP("vamp"))
		self.luckNeeded = int(self.getP("luckt"))
		self.spikes = int(self.getP("spikes"))
		self.manaNeeded = int(self.getP("manat"))
		self.empower = int(self.getP("empower"))
		self.tradeBonusValue = int(self.getP("gold"))


_R.reg("res://gd_core_items/Exclusive/SealtheDeal.gd", Exclusive__SealtheDeal)
_R.reg("SealtheDeal", Exclusive__SealtheDeal)

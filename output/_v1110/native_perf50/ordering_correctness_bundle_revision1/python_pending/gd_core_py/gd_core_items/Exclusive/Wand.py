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
if "_base_cls_Exclusive__Wand" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Wand





class Exclusive__Wand(_base_cls_Exclusive__Wand):

	resource_path = "res://gd_core_items/Exclusive/Wand.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None
		self.manaNeeded = None
		self.luckNeeded = None
		self.regenNeeded = None
		self.empower = None
		self.buffsToUse = None


	def doCooldownEffect(self):
		self.giveLeastBuffs(1, self.character(), None, self.buffs)

		mana = self.character().getMana()
		luck = self.character().getLucky()
		regen = self.character().getRegeneration()

		if (mana >= self.manaNeeded or 
			luck >= self.luckNeeded or 
			regen >= self.regenNeeded):

				event = self.removeMostBuffs(self.buffsToUse, None, True, self.buffs)
				self.giveEmpower(self.empower, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.buffs = [_H_1, _H_2, _H_3]
		self.manaNeeded = int(self.getP("manat"))
		self.luckNeeded = int(self.getP("luckt"))
		self.regenNeeded = int(self.getP("regent"))
		self.empower = int(self.getP("empower"))
		self.buffsToUse = int(self.getP("use"))


_R.reg("res://gd_core_items/Exclusive/Wand.gd", Exclusive__Wand)
_R.reg("Wand", Exclusive__Wand)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

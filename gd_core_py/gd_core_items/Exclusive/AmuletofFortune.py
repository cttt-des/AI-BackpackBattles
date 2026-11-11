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
if "_base_cls_Exclusive__AmuletofFortune" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__AmuletofFortune





class Exclusive__AmuletofFortune(_base_cls_Exclusive__AmuletofFortune):

	resource_path = "res://gd_core_items/Exclusive/AmuletofFortune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusChance = None
		self.numBuffs = None

	amuletColor = Color(0.266667, 0.960784, 0.667953)

	def canAffect(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		_iter__loc = _iter
		_aff = self.getAffectedItems()
		# ★ np51㊳终⑪ 增伤面探针（GD_FORTPROBE 门控，零 rng 消耗）
		if _os_environ_get("GD_FORTPROBE") != "":
			_names = ""
			for _a in (_aff if _aff.__class__ is list else _iter__loc(_aff)):
				_names += String(_a.descriptor.identifier) + ","
			print("[FORT] t=prepare bonusChance=", self.bonusChance, " affected=", _names,
					" mult=", self.bonusChancePercent_mult)
		for item in (_aff if _aff.__class__ is list else _iter__loc(_aff)):
			item.addBonusChance(self.bonusChance)


	def doCooldownEffect(self):
		self.giveMostBuffs(self.numBuffs)
		self.onAfterEffectFinished()


	def getTriggerPriority(self):
		return _H_1 + 5

	def _readyInit(self):
		super()._readyInit()
		self.bonusChance = self.getP("chance")
		self.numBuffs = int(self.getP("buffs"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofFortune.gd", Exclusive__AmuletofFortune)
_R.reg("AmuletofFortune", Exclusive__AmuletofFortune)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

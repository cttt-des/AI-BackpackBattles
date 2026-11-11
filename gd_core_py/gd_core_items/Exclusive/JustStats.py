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
if "_base_cls_Exclusive__JustStats" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__JustStats





class Exclusive__JustStats(_base_cls_Exclusive__JustStats):

	resource_path = "res://gd_core_items/Exclusive/JustStats.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaRegen = None


	def onCombatStart(self):
		self.giveMaxHealth(gd_round(_div(self.getP_m('maxhealth'), 100.0) * self.character().getMaxHealth()))
		self.character().giveStaminaRegeneration(self.staminaRegen)
		self.activate()


	def getTriggerPriority(self):
		return _H_1


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		string = None
		if wrapInColor:
			string = self.ctx.util.tr("TOOLTIP_Always Offered").format(
				{"round": None})
		else:
			string = self.ctx.util.tr("TOOLTIP_Always Offered").format(
				{"round": self.descriptor.appearRounds[0]})

		descr += "\n\n" + string
		return descr


	def getSalesMultiplier(self):
		return 0.2

	def _readyInit(self):
		super()._readyInit()
		self.staminaRegen = _div(self.getP('stamina'), 100.0)


_R.reg("res://gd_core_items/Exclusive/JustStats.gd", Exclusive__JustStats)
_R.reg("JustStats", Exclusive__JustStats)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.Low
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

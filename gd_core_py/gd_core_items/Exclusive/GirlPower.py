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
if "_base_cls_Exclusive__GirlPower" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__GirlPower





class Exclusive__GirlPower(_base_cls_Exclusive__GirlPower):

	resource_path = "res://gd_core_items/Exclusive/GirlPower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.empower = None
		self.regen = None
		self.speed_v = None


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_1
		return color == _H_1


	def canAffect(self, item):
		return item.isClassItem()


	def onPrepare(self):
		self.addSpeed(self.speed_v * self.getNumDistinctAffectedItems())


	def doCooldownEffect(self):
		curEmpower = self.character().getEmpower()
		curRegen = self.character().getRegeneration()

		if curRegen < curEmpower:
			self.giveRegeneration(self.regen)
		elif curRegen > curEmpower:
			self.giveEmpower(self.empower)
		else:
			if self.ctx.util.flip():
				self.giveRegeneration(self.regen)
			else:
				self.giveEmpower(self.empower)

		self.activate()


	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.empower = int(self.getP("empower"))
		self.regen = int(self.getP("regen"))
		self.speed_v = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/GirlPower.gd", Exclusive__GirlPower)
_R.reg("GirlPower", Exclusive__GirlPower)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

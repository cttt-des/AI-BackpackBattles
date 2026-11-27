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
if "_base_cls_Exclusive__Ultima" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Ultima





class Exclusive__Ultima(_base_cls_Exclusive__Ultima):

	resource_path = "res://gd_core_items/Exclusive/Ultima.gd"

	def _init_fields(self):
		super()._init_fields()
		self.typesDict = None
		self.speedPerSpell = None


	def canAffect(self, item):
		return (item.hasType(_H_1) or 
				item.hasType(_H_2) or 
				item.hasType(_H_3) or 
				item.hasType(_H_4) or 
				item.hasType(_H_5))


	def onPrepare(self):
		self.typesDict = self.countTypes(self.getAffectedItems())

		if self.typesDict[_H_5] > 0:
			self.addSpeed(self.speedPerSpell * self.typesDict[_H_5])


	def doCooldownEffect(self):

		if self.typesDict[_H_1] > 0:
			self.giveLucky(self.typesDict[_H_1] * self.getP("luck"))
			self.giveSpikes(self.typesDict[_H_1] * self.getP("spikes"))

		if self.typesDict[_H_2] > 0:
			self.giveBlock(self.typesDict[_H_2] * self.getBlock())
			self.inflictCold(self.typesDict[_H_2] * self.getP("cold"))

		if self.typesDict[_H_3] > 0:
			self.giveRegeneration(self.typesDict[_H_3] * self.getP("regen"))

		if self.typesDict[_H_4] > 0:
			self.stealRandomBuff(self.typesDict[_H_4])

		self.onAfterEffectFinished()


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_nature", "")
			descr = descr.replace("$n_ice", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")

			return descr

		self.typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_H_1])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_H_2])
		descr = self.insertCounter(descr, "n_holy", self.typesDict[_H_3])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_H_4])


		return descr

	def _readyInit(self):
		super()._readyInit()
		self.speedPerSpell = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Ultima.gd", Exclusive__Ultima)
_R.reg("Ultima", Exclusive__Ultima)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Type.Spell
except AttributeError as _he:
	_H_5 = _HoistPending(_he)

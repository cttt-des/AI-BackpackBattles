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
if "_base_cls_Exclusive__RainbowOrb" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__RainbowOrb





class Exclusive__RainbowOrb(_base_cls_Exclusive__RainbowOrb):

	resource_path = "res://gd_core_items/Exclusive/RainbowOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None


	def canAffect(self, item):

		return (item.hasType(_H_1) or 
				item.hasType(_H_2) or 
				item.hasType(_H_3) or 
				item.hasType(_H_4))


	def onCombatStart(self):
		typesDict = self.countTypes(self.getAffectedItems())

		if typesDict[_H_1] > 0:
			self.giveVampirism(typesDict[_H_1] * self.getP("vampirism"))

		if typesDict[_H_2] > 0:
			self.giveMana(typesDict[_H_2] * self.getP("mana"))

		if typesDict[_H_3] > 0:
			self.character().addHealingEfficiency(_div(typesDict[_H_5] * self.getP('healamp'), 100.0))

		if typesDict[_H_4] > 0:
			self.inflictRandomDebuffs(typesDict[_H_4] * self.getP("debuffs"))

		self.activate()


	def doCooldownEffect(self):
		self.giveAllBuffs()
		self.activate()


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_magic", "")
			descr = descr.replace("$n_vampiric", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")
			return descr

		typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_magic", typesDict[_H_2])
		descr = self.insertCounter(descr, "n_vampiric", typesDict[_H_1])
		descr = self.insertCounter(descr, "n_holy", typesDict[_H_3])
		descr = self.insertCounter(descr, "n_dark", typesDict[_H_4])

		return descr


	def _readyInit(self):
		super()._readyInit()
		self.buffs = self.getP("buffs")


_R.reg("res://gd_core_items/Exclusive/RainbowOrb.gd", Exclusive__RainbowOrb)
_R.reg("RainbowOrb", Exclusive__RainbowOrb)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Magic
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
	_H_5 = _R.C('CoreConst').Type.Holy
except AttributeError as _he:
	_H_5 = _HoistPending(_he)

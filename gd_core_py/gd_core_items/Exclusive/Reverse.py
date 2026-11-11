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
if "_base_cls_Exclusive__Reverse" not in globals():
	from ..Card import Card_2 as _base_cls_Exclusive__Reverse





class Exclusive__Reverse(_base_cls_Exclusive__Reverse):

	resource_path = "res://gd_core_items/Exclusive/Reverse.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None


	def cardSecondaryEffectActive(self):
		return self.deck and self.deck.countDuplicates(self.chainPosition) == 0


	def doRevealEffect(self):
		self.giveReflectStacks(self.getP("reflect"))

		if self.cardSecondaryEffectActive():
			self.stealRandomBuff(self.getP("steal"))

		self.activate()


	def getCardDescription(self, descr):
		if self.deck:
			duplicates = self.deck.countDuplicates(self.chainPosition)
			state = _H_1
			if duplicates == 0:
				state = _H_2
			else:
				state = _H_3
			descr += "\n" + self.insertParameter(tr("CARD_DUPLICATES"), "num", duplicates, state, False)
		elif self.placed:
			descr += "\n" + self.ctx.util.wrapInColor(tr("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Reverse.gd", Exclusive__Reverse)
_R.reg("Reverse", Exclusive__Reverse)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").StatModified.Positive
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").StatModified.Negative
except AttributeError as _he:
	_H_3 = _HoistPending(_he)

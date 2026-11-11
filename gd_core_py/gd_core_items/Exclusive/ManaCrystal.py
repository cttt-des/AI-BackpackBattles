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
if "_base_cls_Exclusive__ManaCrystal" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ManaCrystal





class Exclusive__ManaCrystal(_base_cls_Exclusive__ManaCrystal):

	resource_path = "res://gd_core_items/Exclusive/ManaCrystal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana1 = None
		self.mana2 = None

	chargeCells = [
		[Vector2(0, 0), Vector2( - 1, 0), Vector2( - 2, 0), Vector2( - 3, 0)], 
		[Vector2(0, 0), Vector2(0, - 1), Vector2(0, - 2)], 
		[Vector2(0, 0), Vector2(1, 0), Vector2(2, 0), Vector2(3, 0)], 
		[Vector2(0, 0), Vector2(0, 1), Vector2(0, 2)]
		]

	def canAffect_lightning(self, item):
		return True


	def doCooldownEffect(self):
		self.emitCharge()
		self.ctx.bus.emitSignal(self, "charge_emitted", [self])


	def emitCharge(self, speedFactor=1.0):
		event = self.activate()
		for i in _iter(len(self.chargeCells)):
			self.sendCharge(self.getP_m("dur"), self.chargeCells[i], speedFactor, event)


	def onChargeEnteredCell(self, charge, cellIndex):
		if (charge.curChargedItem != None and 
			charge.curChargedItem != charge.lastChargedItem):

			if charge.curChargedItem.hasType(_H_1):
				self.giveMana(self.mana2)
			else:
				self.giveMana(self.mana1)


	def _readyInit(self):
		super()._readyInit()
		self.mana1 = int(self.getP("mana1"))
		self.mana2 = int(self.getP("mana2"))


_R.reg("res://gd_core_items/Exclusive/ManaCrystal.gd", Exclusive__ManaCrystal)
_R.reg("ManaCrystal", Exclusive__ManaCrystal)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Magic
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

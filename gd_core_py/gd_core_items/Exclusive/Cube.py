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
if "_base_cls_Cube" not in globals():
	from ..Item import Item_2 as _base_cls_Cube





class Cube(_base_cls_Cube):

	resource_path = "res://gd_core_items/Exclusive/Cube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItem = None
		self.cdAdvance = None
		self.penaltyFactor = None


	def getDescription(self, wrapInColor=True):
		descr = self.descriptor.getDescription()
		descr += "\n\n" + self.ctx.util.tra("Cube_HINT")
		return self.insertParameters(descr, wrapInColor)


	def advanceAffectedItem(self):
		if not self.affectedItem in self.ctx.cube_advanced:
			self.ctx.cube_advanced[self.affectedItem] = self
			self.affectedItem.advanceCooldownSeconds(self.cdAdvance)
		else:
			self.affectedItem.advanceCooldownSeconds(self.cdAdvance * self.penaltyFactor)


	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("cdadvance")
		self.penaltyFactor = 1.0 - _div(self.getP('penalty'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Cube.gd", Cube)
_R.reg("Cube", Cube)
_R.reg("Cube", Cube)

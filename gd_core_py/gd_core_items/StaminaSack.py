# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_StaminaSack_2" not in globals():
	from .Bag import Bag_2 as _base_cls_StaminaSack_2





class StaminaSack_2(_base_cls_StaminaSack_2):

	resource_path = "res://gd_core_items/StaminaSack.gd"


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)
		if self.ownerType == _H_1:
			self.character().changeBaseMaxStamina()


	def onRemoveFromInventory(self):
		super().onRemoveFromInventory()
		if self.ownerType != _H_2:
			self.character().changeBaseMaxStamina()


	def onPrepare(self):
		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			stamina = _div(self.ctx.item_book.getDescriptor('Bagtacular').getP('stamina'), 100.0)
			self.character().giveStaminaRegeneration(stamina)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StaminaSack.gd", StaminaSack_2)
_R.reg("StaminaSack", StaminaSack_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Owner.BuildViewer
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import (  # noqa: F401

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
	from ...._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .... import _registry as _R
if "_base_cls_Exclusive__Chess__WhiteKnight" not in globals():
	from .ChessPiece import ChessPiece as _base_cls_Exclusive__Chess__WhiteKnight





class Exclusive__Chess__WhiteKnight(_base_cls_Exclusive__Chess__WhiteKnight):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteKnight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boardSpeed = None
		self.stamina = None


	def doCapturingEffect(self, _eliminatedPiece):
		self.board.addSpeed(self.boardSpeed)



	def doEliminatedEffect(self, _capturingPiece):
		self.giveMaxStaminaTemporary(self.stamina)


	def canBeBlocked(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.boardSpeed = _div(self.getP('speed'), 100.0)
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteKnight.gd", Exclusive__Chess__WhiteKnight)
_R.reg("WhiteKnight", Exclusive__Chess__WhiteKnight)

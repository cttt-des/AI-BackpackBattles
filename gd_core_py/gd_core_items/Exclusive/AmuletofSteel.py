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
if "_base_cls_Exclusive__AmuletofSteel" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__AmuletofSteel





class Exclusive__AmuletofSteel(_base_cls_Exclusive__AmuletofSteel):

	resource_path = "res://gd_core_items/Exclusive/AmuletofSteel.gd"

	def _init_fields(self):
		super()._init_fields()
		self._blockAcc = 0
		self.blockForEmpower = None
		self.empowerForBlock = None

	@property
	def blockAcc(self):
		return self._blockAcc
	@blockAcc.setter
	def blockAcc(self, v):
		self._blockAcc = int(v)
	amuletColor = Color(0.34902, 0.415686, 0.45098)

	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		self.blockAcc = 0
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "gave_block", "onItemGaveBlock")


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		empower = _div(self.blockAcc, self.blockForEmpower)
		self.blockAcc %= self.blockForEmpower
		if empower > 0:
			self.giveEmpower(empower * self.empowerForBlock, event)
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.blockForEmpower = int(self.getP("blockt"))
		self.empowerForBlock = int(self.getP("empower"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofSteel.gd", Exclusive__AmuletofSteel)
_R.reg("AmuletofSteel", Exclusive__AmuletofSteel)

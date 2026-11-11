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
if "_base_cls_Exclusive__DevouringSphere" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__DevouringSphere





class Exclusive__DevouringSphere(_base_cls_Exclusive__DevouringSphere):

	resource_path = "res://gd_core_items/Exclusive/DevouringSphere.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirism = None
		self.blindSpeed = None
		self.coldSpeed = None
		self.dam = None
		self.distortion = None


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")
		self.connectForCombat(self.opponent(), "character_blind_changed", "onOpponentBlindChanged")


	def doCooldownEffect(self):
		self.giveVampirism(self.vampirism)
		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0))
		self.activate()


	def onOpponentColdChanged(self, amount, event):
		self.addSpeed(amount * self.coldSpeed)


	def onOpponentBlindChanged(self, amount, event):
		self.addSpeed(amount * self.blindSpeed)


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()
		return res

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.vampirism = int(self.getP("vampirism"))
		self.blindSpeed = _div__loc(self.getP('speed_blind'), 100.0)
		self.coldSpeed = _div__loc(self.getP('speed_cold'), 100.0)
		self.dam = self.getP("dam")
		pass



_R.reg("res://gd_core_items/Exclusive/DevouringSphere.gd", Exclusive__DevouringSphere)
_R.reg("DevouringSphere", Exclusive__DevouringSphere)

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
if "_base_cls_Exclusive__ChainWhip" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__ChainWhip





class Exclusive__ChainWhip(_base_cls_Exclusive__ChainWhip):

	resource_path = "res://gd_core_items/Exclusive/ChainWhip.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffsPurged = 0


	def onPrepare(self):
		self.buffsPurged = 0
		self.connectToOpponentBuffs("onOpponentBuffsChanged")


	def onOpponentBuffsChanged(self, amount, event):
		if amount < 0:
			if isinstance(event.getOrigin(), _H_1) and event.getOrigin().character() == self.character():
				self.buffsPurged += - amount
				self.addBonusDamage( - amount * self.getP3())


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.removeRandomBuffs(self.getP1())
			if self.character().isBattleRaging():
				self.heal()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ChainWhip.gd", Exclusive__ChainWhip)
_R.reg("ChainWhip", Exclusive__ChainWhip)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("Item")

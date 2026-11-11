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
if "_base_cls_Exclusive__Chainsaw" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Chainsaw





class Exclusive__Chainsaw(_base_cls_Exclusive__Chainsaw):

	resource_path = "res://gd_core_items/Exclusive/Chainsaw.gd"

	def _init_fields(self):
		super()._init_fields()
		self.sawFrame = 0
		self.sawTween = None
		self.removeBuffs = None
		self.slowdown = None
		self.sawAnimation = None

	sawSpeed = 8.0

	def onPrepare(self):
		self.setState(False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.numCharges > 0:
				self.stealBuffsFraction(self.removeBuffs, 1000)
			else:
				self.removeBuffsFraction(self.removeBuffs, 1000)

			self.reduceSpeed(self.slowdown)


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()

		return res


	def setSawTexture(self):
		self.sawFrame += 1
		self.sawFrame %= 4
		self.updateShadowTexture()


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(True)
			self.playPickupSound()


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, charged):
		if charged:
			pass
		else:
			pass


	def playPickupSound(self):
		# decomp Items/Exclusive/Chainsaw.gd:72 Sound.playSound(pickupSound, 0, Util.randPitch(0.1) + 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.removeBuffs = _div__loc(self.getP('buffs'), 100.0)
		self.slowdown = _div__loc(self.getP('slow'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Chainsaw.gd", Exclusive__Chainsaw)
_R.reg("Chainsaw", Exclusive__Chainsaw)

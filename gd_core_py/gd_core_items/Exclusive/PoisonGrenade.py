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
if "_base_cls_Exclusive__PoisonGrenade" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__PoisonGrenade





class Exclusive__PoisonGrenade(_base_cls_Exclusive__PoisonGrenade):

	resource_path = "res://gd_core_items/Exclusive/PoisonGrenade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonCritActive = False
		self.tween = None
		self.poison = None
		self.selfPoison = None
		self.cdAdvance = None
		self.luckNeeded = None
		self.light = None
		self.lightAni = None


	def onPrepare(self):
		self.setState(False)

		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def doCooldownEffect(self):
		self.inflictPoison(self.poison)
		self.selfInflictPoison(self.selfPoison)
		self.onAfterEffectFinished()



	def onChargeReceived(self, _charge):
		self.advanceCooldownSeconds(self.cdAdvance)
		self.miniActivate()


	def onLuckChanged(self, amount, event):
		if amount > 0 and not self.poisonCritActive and self.character().getLucky() >= self.luckNeeded:
			self.opponent().changePoisonCritChancePercent(self.getChance())
			self.setState(True)

		elif amount < 0 and self.poisonCritActive and self.character().getLucky() < self.luckNeeded:
			self.opponent().changePoisonCritChancePercent( - self.getChance())
			self.setState(False)


	def onShopEntered(self):
		pass

	def onStateChanged(self, _poisonCritActive):
		self.poisonCritActive = _poisonCritActive
		if self.poisonCritActive:
			pass

		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.selfPoison = int(self.getP("poison2"))
		self.cdAdvance = self.getP("cdadvance")
		self.luckNeeded = int(self.getP("luckt"))


_R.reg("res://gd_core_items/Exclusive/PoisonGrenade.gd", Exclusive__PoisonGrenade)
_R.reg("PoisonGrenade", Exclusive__PoisonGrenade)

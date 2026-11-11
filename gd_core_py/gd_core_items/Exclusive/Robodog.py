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
if "_base_cls_Exclusive__Robodog" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Robodog





class Exclusive__Robodog(_base_cls_Exclusive__Robodog):

	resource_path = "res://gd_core_items/Exclusive/Robodog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.digUpItems = { "Stone": 4, "Garlic": 3, "Blueberries": 2, "Lump of Coal": 3, "Pocket Sand": 3, "Chipped Ruby": 1, "Chipped Sapphire": 1, "Chipped Emerald": 1, "Chipped Topaz": 1, "Chipped Amethyst": 1, "Healing Herbs": 0.5, "Bag of Stones": 0.5, "Walrus Tusk": 0.2, "Whetstone": 0.2, "Piggybank": 0.2, "Pan": 0.2, "Customer Card": 0.2, "Gloves of Haste": 0.2, "Dagger": 0.2, "Protective Purse": 0.1, "Flawed Ruby": 0.2, "Flawed Sapphire": 0.2, "Flawed Emerald": 0.2, "Flawed Topaz": 0.2, "Flawed Amethyst": 0.2, }
		self.spawnPos = None
		self.luck = None
		self.heat = None
		self.cdIncrease = None


	def onShopEntered(self):
		pass

	def onPrepare(self):
		pass



	def onChargeReceived(self, _charge):
		self.resetBaseCooldown()
		if self.numCharges == 1:
			self.setState(True)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def doCooldownEffect(self):
		self.giveLucky(self.luck)
		self.giveHeat(self.heat)
		if self.numCharges == 0:
			self.setBaseCooldown(self.baseCooldownOverride + self.cdIncrease)
		self.activate()


	def onStateChanged(self, charged):
		if charged:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.heat = int(self.getP("heat"))
		self.cdIncrease = self.getP("cdincrease")
		pass



_R.reg("res://gd_core_items/Exclusive/Robodog.gd", Exclusive__Robodog)
_R.reg("Robodog", Exclusive__Robodog)

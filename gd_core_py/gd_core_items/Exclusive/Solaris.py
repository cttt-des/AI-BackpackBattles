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
if "_base_cls_Exclusive__Solaris" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Solaris





class Exclusive__Solaris(_base_cls_Exclusive__Solaris):

	resource_path = "res://gd_core_items/Exclusive/Solaris.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.sunShieldDescriptor = None
		self.sunArmorDescriptor = None
		self.holyArmorDescriptor = None
		self.shieldOfValorDescriptor = None
		self.heatPerShieldBlock = None


	def canAffect(self, item):
		return item.isA(self.sunShieldDescriptor) or item.isA(self.sunArmorDescriptor)


	def onBought(self):
		self.boosted = 1


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onPrepare(self):
		self.inventory.changeBuffAmplification_allItems(_H_1, self.getChance2())

		for item in _iter(self.getAffectedItems()):
			if item.isA(self.sunShieldDescriptor):
				self.connectForCombat(item, "blocked", "onShieldBlocked")
			else:
				self.connectForCombat(item, "used_heat", "onArmorUsedHeat")


	def onArmorUsedHeat(self, event):
		self.giveBlock(self.getBlock(), True, event)
		self.miniActivate()


	def onShieldBlocked(self, blockedDamageRes):
		if self.rollChance():
			self.giveHeat(self.heatPerShieldBlock)
			self.activate()








	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if (descr == self.shieldOfValorDescriptor or 
			descr == self.holyArmorDescriptor):
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.sunShieldDescriptor = self.ctx.item_book.getDescriptor("Sun Shield")
		self.sunArmorDescriptor = self.ctx.item_book.getDescriptor("Sun Armor")
		self.holyArmorDescriptor = self.ctx.item_book.getDescriptor("Holy Armor")
		self.shieldOfValorDescriptor = self.ctx.item_book.getDescriptor("Shield of Valor")
		self.heatPerShieldBlock = int(self.getP("heat"))


_R.reg("res://gd_core_items/Exclusive/Solaris.gd", Exclusive__Solaris)
_R.reg("Solaris", Exclusive__Solaris)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Heat
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

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
if "_base_cls_Exclusive__AcornAce" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__AcornAce





class Exclusive__AcornAce(_base_cls_Exclusive__AcornAce):

	resource_path = "res://gd_core_items/Exclusive/AcornAce.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedDescriptors = None
		self.boostedCollars = 0
		self.collarDescriptors = None
		self.acornCollarDescriptor = None
		self.critwoodStaffDescriptor = None
		self.staminaReduction = None


	def getData(self):
		return self.boostedCollars


	def setData(self, data):
		if data != None:
			self.boostedCollars = data


	def onBought(self):
		self.boostedCollars = 1


	def canAffect_global(self, item):
		return item.descriptor in self.affectedDescriptors


	def onItemInstantiated(self, item):
		if (self.placed and 
			isinstance(item, _R.C("RangerCollar")) and 
			
			item.isOwnable()):
				item.activateExtendedAffectedCells()


	def onAddToInventory(self):
		self.ctx.defer(self, "onAddToInventory_deferred", [])


	def onAddToInventory_deferred(self):
		pass

	def onRemoveFromInventory(self):
		self.ctx.defer(self, "onRemoveFromInventory_deferred", [])


	def onRemoveFromInventory_deferred(self):
		pass

	def onPrepare(self):
		for staff in _iter(self.getAllInInventoryOfType(self.critwoodStaffDescriptor)):
			staff.changeStaminaFactor(self.staminaReduction)



	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.acornCollarDescriptor:
			self.boostedCollars -= 1

	def _readyInit(self):
		super()._readyInit()
		self.collarDescriptors = [
		self.ctx.item_book.getDescriptor("Acorn Collar"), 
		self.ctx.item_book.getDescriptor("Magic Collar"), 
		self.ctx.item_book.getDescriptor("Holy Collar"), 
		self.ctx.item_book.getDescriptor("Vampiric Collar")
	]
		self.acornCollarDescriptor = self.collarDescriptors[0]
		self.critwoodStaffDescriptor = self.ctx.item_book.getDescriptor("Critwood Staff")
		self.staminaReduction = - self.getP("stamina2")
		self.affectedDescriptors = self.ctx.util.arrayAsIndexDict(self.collarDescriptors)
		self.affectedDescriptors[self.critwoodStaffDescriptor] = 4



_R.reg("res://gd_core_items/Exclusive/AcornAce.gd", Exclusive__AcornAce)
_R.reg("AcornAce", Exclusive__AcornAce)

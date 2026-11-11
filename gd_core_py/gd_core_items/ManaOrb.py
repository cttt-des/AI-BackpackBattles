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
if "_base_cls_ManaOrb_2" not in globals():
	from .Item import Item_2 as _base_cls_ManaOrb_2





class ManaOrb_2(_base_cls_ManaOrb_2):

	resource_path = "res://gd_core_items/ManaOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = []
		self.activated = False
		self._bonusBuffs = 0
		self.mana = None
		self._manaNeeded = 0
		self.buffs = None
		self.light = None

	@property
	def bonusBuffs(self):
		return self._bonusBuffs
	@bonusBuffs.setter
	def bonusBuffs(self, v):
		self._bonusBuffs = int(v)
	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)

	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		# ★ np25 evt105 f09 面 AFFL 探针（双门控零耗链）：ManaOrb 连接集定谳——
		#   夹具 affected=(5,3),(5,5),(7,3),(7,5)，gd 漏连 (7,5) Piggybank
		#   （BUS activated 0 listeners 铁证）。打印逐格命中与受影响物品集。
		_iter__loc = _iter
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			_cells = self.getAffectedCellsInInventory()
			_hit = ""
			for _c in (_cells if _cells.__class__ is list else _iter__loc(_cells)):
				_it = self.getOwnOrPlayerInventory().getItemInCell(_c)
				_hit += '[' + str(_c) + '=' + ('null' if _it == None else String(_it.descriptor.identifier) + '/ot' + str(int(_it.ownerType)) + ' p' + str(int(_it.placed))) + ']'
			_aff = self.getAffectedItems()
			_aff_names = ""
			for _a in (_aff if _aff.__class__ is list else _iter__loc(_aff)):
				_aff_names += String(_a.descriptor.identifier) + ","
			self.ctx.rng.trace_diag('AFFL', String(self.descriptor.identifier) + '/ot' + str(int(self.ownerType)), str(_cells), _hit + ' aff=' + _aff_names)
		self.bonusBuffs = 0
		self.setState(False)
		for item in _iter__loc(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onItemActivated(self, event):
		if self.rollChance():
			self.miniActivate()
			self.giveMana(self.mana)


	def onManaChanged(self, amount, triggerEvent):
		if not self.activated and amount > 0 and self.character().getMana() >= self.manaNeeded:
			self.setState(True)
			event = self.useMana(self.manaNeeded, triggerEvent)
			self.giveRandomBuffs(self.buffs + self.bonusBuffs, event, self.stackTypes)
			self.activate()



	def onShopEntered(self):
		self.onStateChanged(False)


	def addBonusRandomBuffs(self, amount):
		amount = int(amount)
		self.bonusBuffs += amount


	def onStateChanged(self, _activated):
		self.activated = _activated

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP1())
		self.manaNeeded = self.getP2()
		self.buffs = int(self.getP3())
		self.stackTypes = _H_1.getBuffs()
		_erase(self.stackTypes, _H_2)



_R.reg("res://gd_core_items/ManaOrb.gd", ManaOrb_2)
_R.reg("ManaOrb", ManaOrb_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
	_H_2 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

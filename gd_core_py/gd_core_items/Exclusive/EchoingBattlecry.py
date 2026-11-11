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
if "_base_cls_Exclusive__EchoingBattlecry" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__EchoingBattlecry





class Exclusive__EchoingBattlecry(_base_cls_Exclusive__EchoingBattlecry):

	resource_path = "res://gd_core_items/Exclusive/EchoingBattlecry.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItems = []
		self.speedPerItem = None


	def canAffect(self, item):
		return item.hasStartofBattle()


	def onPrepare(self):
		_iter__loc = _iter
		self.affectedItems = self.getAffectedItems()
		# ★ np25 evt105 f09 面 EBARR 探针（双门控零耗链）：EB 洗牌输入/输出序定谳
		#   ——首分歧=EB 首弹弹了不同 Piggybank（全局链 j 值 or 输入序差）。
		_b = ""
		_aft = ""
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			for _a in (self.affectedItems if self.affectedItems.__class__ is list else _iter__loc(self.affectedItems)):
				_b += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells[0]) + ","
		self.ctx.rng.shuffleEngine(self.affectedItems, 'Exclusive/EchoingBattlecry.gd:14')
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			for _a in (self.affectedItems if self.affectedItems.__class__ is list else _iter__loc(self.affectedItems)):
				_aft += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells[0]) + ","
			self.ctx.rng.trace_diag("EBARR", "ot" + str(int(self.ownerType)), _b, _aft)

		self.addSpeed(self.speedPerItem * len(self.affectedItems))


	def doCooldownEffect(self):
		if not (not self.affectedItems):
			item = self.affectedItems.pop()
			item.repeatCombatStart()
			if (not self.affectedItems):
				self.onAfterEffectFinished()
			else:
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedPerItem = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/EchoingBattlecry.gd", Exclusive__EchoingBattlecry)
_R.reg("EchoingBattlecry", Exclusive__EchoingBattlecry)

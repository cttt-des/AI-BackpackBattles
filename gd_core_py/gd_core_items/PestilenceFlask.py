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
if "_base_cls_PestilenceFlask_2" not in globals():
	from .Potion import Potion_2 as _base_cls_PestilenceFlask_2





class PestilenceFlask_2(_base_cls_PestilenceFlask_2):

	resource_path = "res://gd_core_items/PestilenceFlask.gd"


	def onTriggerPotion(self, triggerEvent=None):
		self.inflictPoison(self.getP1(), triggerEvent)
		self.selfInflictPoison(self.getP2(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_healed", "onOpponentHeal")


	def onOpponentHeal(self, _amount, event):
		if self.isEmpty():
			return

		# ★ np25 evt12 面 AFFL 探针（双门控零耗链）：反制投掷链定谳——
		#   getAffectedItems 运行时值（gd 3 投 v oracle 2 投，affected[0] 链
		#   是否多执行一级）。定谳后可移除或保留（零耗不影响行为）。
		_aff = self.getAffectedItems()
		_aff_names = ""
		for _a in (_aff if _aff.__class__ is list else _iter(_aff)):
			_aff_names += String(_a.descriptor.identifier) + ","
		self.ctx.rng.trace_diag("AFFL", String(self.descriptor.identifier), "n=" + str(len(_aff)), _aff_names)

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion(event)
			affected[0].miniActivate()

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PestilenceFlask.gd", PestilenceFlask_2)
_R.reg("PestilenceFlask", PestilenceFlask_2)

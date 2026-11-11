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
if "_base_cls_StrongPestilenceFlask_2" not in globals():
	from .PestilenceFlask import PestilenceFlask_2 as _base_cls_StrongPestilenceFlask_2





class StrongPestilenceFlask_2(_base_cls_StrongPestilenceFlask_2):

	resource_path = "res://gd_core_items/StrongPestilenceFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonTimer = None


	def getAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_1
		# ★ np25 evt12 面 GRD 探针（双门控零耗）：aff 格级真值——faceDirection/
		#   collision 全局格/cache 格/命中物品，定 getAffectedItems 错位。
		_r = super().getAffectedItems(color)
		if self.ctx != None and self.ctx.rng != None:
			_cp = self.getCollisionPoints()
			_rc = self.getCellsForGlobalPositions(_cp)
			_cc = self.getAffectedCellsInInventory_cached(color)
			_names = ""
			for _a in (_r if _r.__class__ is list else _iter(_r)):
				_names += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells) + ","
			self.ctx.rng.trace_diag("GRD", String(self.descriptor.identifier),
					"fd=" + str(self.faceDirection) + " cp=" + str(_cp) + " aff=" + str(_cc), _names + "n=" + str(len(_r)))
		return _r

	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.poisonTimer.start(self.getP3())


	def poisonTimerTimeout(self):
		self.inflictPoison(self.getP4())


	def onCombatEnd(self):
		self.poisonTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.poisonTimer = self.newItemTimer("PoisonTimer", "poisonTimerTimeout", True)


_R.reg("res://gd_core_items/StrongPestilenceFlask.gd", StrongPestilenceFlask_2)
_R.reg("StrongPestilenceFlask", StrongPestilenceFlask_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)

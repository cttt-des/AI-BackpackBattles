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




class CoreEvent(GodotObject):

	resource_path = "res://gd_core/CoreEvent.gd"

	Target = EnumDict("Target", {"Player": 0, "Opponent": 1})



	def _init_fields(self):
		super()._init_fields()
		self._id = 0
		self.timestamp = None
		self.parentEvent = None
		self.origin = None
		self.type = None
		self.target = None
		self.params = {}
		self.formatParams = {}

	@property
	def id(self):
		return self._id
	@id.setter
	def id(self, v):
		self._id = int(v)
	# =============================================================================
	# CoreEvent.gd — 无头战斗内核：战斗事件
	# =============================================================================
	# 对齐源码：Core/CombatEvent.gd（全文 208 行）
	#
	# 保留（参与判定/被物品行为读取）：id / timestamp / parentEvent / origin / type /
	#   target / params，以及 getType / setTarget / setParam / getParam / getAmount /
	#   getAmountWithDefault / hasParam / getMainActor / getOrigin / fromCharacter / getDepth
	#
	# 剥离内容（纯呈现，判定不读）：
	#   · formatParams 的文案填充（Util.tra / Util.getIcon / 颜色包裹）
	#   · asText()（HTML/魔法文本渲染，1279 行的 CombatLog 职责）
	#   · damageColor* 常量与 damageFormat
	#   → 事项：`formatParams` 字段保留但不填充，避免任何外部代码因字段缺失崩溃。
	# =============================================================================





	def _init(self, _id, _timestamp=0.0, _parentEvent=None, _origin=None, _type=None):

		self.id = _id
		self.timestamp = _timestamp
		self.parentEvent = _parentEvent
		self.origin = _origin
		self.type = _type


	def getType(self):
		return self.type


	def setTarget(self, _target):
		self.target = _target


	def setParam(self, paramName, paramVal):
		self.params[paramName] = paramVal


	def getParam(self, paramName, default):
		return self.params.get(paramName, default)


	def getAmount(self):
		return self.params["amount"]


	def getAmountWithDefault(self, default):
		return self.params.get("amount", default)


	def hasParam(self, param):
		return param in self.params


	def getMainActor(self):
		if isinstance(self.origin, _H_1):
			return self.origin.character().playerId
		elif self.target:
			return self.target
		else:
			return _H_2


	def getOrigin(self):
		return self.origin


	def fromCharacter(self, character):
		return isinstance(self.origin, _H_1) and self.origin.character() == character


	def getDepth(self):
		if self.parentEvent:
			return self.parentEvent.getDepth() + 1
		else:
			return 0


_R.reg("res://gd_core/CoreEvent.gd", CoreEvent)
_R.reg("CoreEvent", CoreEvent)
_R.reg("CoreEvent", CoreEvent)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreItem")
try:
	_H_2 = _R.C("CoreCharacter").ID.PLAYER
except AttributeError as _he:
	_H_2 = _HoistPending(_he)

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
if "_base_cls_Exclusive__Sandbag" not in globals():
	from ..LeatherHelm import LeatherHelm_2 as _base_cls_Exclusive__Sandbag





class Exclusive__Sandbag(_base_cls_Exclusive__Sandbag):

	resource_path = "res://gd_core_items/Exclusive/Sandbag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blind = None


	def onPrepare(self):
		pass


	def onPreCombatStart(self):
		if not self.ctx.sandbag_active:
			self.ctx.sandbag_active = True
			super().onPreCombatStart()
			self.opponent().changeDamageResistance(self.damReduction)
		elif self.buffsActive > 0:
			self.ctx.util.changeTimer(self.buffTimer, self.getBuffDur())


	def onCombatStart(self):
		self.inflictBlind(self.blind)
		self.giveStacks(self.character(), _H_1, self.blind)
		self.activate()


	def buffEnded(self):
		if self.buffsActive > 0:
			super().buffEnded()
			self.opponent().changeDamageResistance( - self.damReduction)
			self.ctx.sandbag_active = False



	def _readyInit(self):
		super()._readyInit()
		# ★ np49（run602_r14 fd@334）：oracle 的 Sandbag.tscn BuffTimer=**普通 one_shot
		#   Timer（无脚本）+ timeout→buffEnded**（Exclusive/Sandbag.tscn:70-73,89——区别于
		#   父类 LeatherHelm.tscn 的 MultiTimer+multi_timeout）。此前继承 LH 的
		#   newItemTimer(..., multi=true)：changeTimer 延长（start(t+left)）走 CoreTimer
		#   multi 运行中分支=仅 push timestamps、引擎读数不改写 ⇒ 注册表 eng==e[1] 不
		#   重同步 ⇒ 按原截止期提前 fire（EB 回声 changeTimer@5.5 后 SB 仍 7.017 炸，
		#   oracle 实证 eng→8.5167 重同步、14.017 才炸）→ damageResistance 窗口错位
		#   → 14 处疲劳 dmg 分歧。修=按 tscn 真身重建为非 multi。
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/Sandbag.gd", Exclusive__Sandbag)
_R.reg("Sandbag", Exclusive__Sandbag)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
